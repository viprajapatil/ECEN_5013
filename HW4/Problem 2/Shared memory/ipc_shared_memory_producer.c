#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<semaphore.h>
#include<sys/wait.h>

typedef struct{
    char string[50];
    int string_length;
    int USR_Led_Control;
}message;

int main()
{
    //size of shared memory object (bytes)
    const int size = sizeof(message);
    
    //name of shared memory object
    const char *name = "/shared_memory_vp";
    const char *semname = "/my_sem";
    
    message mesg_struct;
   message *ptr;
    
    //shared memory file descriptor
    int shm_fd;
    
    //pointer to shared memory object
    void *mptr;
    
    //create the shared memory object
    shm_fd = shm_open(name, O_RDWR | O_CREAT , 0666);
    if (shm_fd < 0)
	printf("ERROR shm_open");

    //Config size of share dmemeory
    int ft = ftruncate(shm_fd, size);
    if (ft < 0)
	printf("ERROR ftruncate");
   
    // mapping of memory segment
    mptr = mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
    if (mptr == NULL)
	printf("ERROR mmap");
     
    sem_t* sem = sem_open(semname, O_CREAT, 0666, 0);
    if (sem == NULL)
	printf("ERROR sem_open");
 	
	message buff = {0};
	ptr = (char*)&buff;

        strcpy(mesg_struct.string, "From producer to consumer msg");
        mesg_struct.string_length = strlen(mesg_struct.string);
        mesg_struct.USR_Led_Control = 0;
	memcpy(mptr, &mesg_struct, size);

	//unlock the semaphore
	sem_post(sem);

	// locks semaphore
	sem_wait(sem);

	message buff1 = {0};
	ptr = (char*)&buff1;
	memcpy(ptr, (char*)mptr, size);
	printf("Producer string: %s, String length = %d, USR led status: %d\n", ptr->string, ptr->string_length, ptr->USR_Led_Control);
	
	int shul = shm_unlink(name);
	if (shul < 0)
		printf("ERROR shm_unlink");
	
    return 0;
    
    
}


