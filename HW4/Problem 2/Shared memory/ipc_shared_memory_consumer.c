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
    
    message *ptr;  
    message mesg_struct;
   
    
    //shared memory file descriptor
    int shm_fd;
    
    //pointer to shared memory object
    void *mptr;
    
    //create the shared memory object
    shm_fd = shm_open(name, O_RDWR | O_CREAT , 0666);
    if (shm_fd < 0)
	printf("ERROR shm_open");
    
    // mapping of memory segment
    mptr = mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
    if (mptr == NULL)
	printf("ERROR mmap");

    sem_t* sem = sem_open(semname, O_CREAT, 0666, 0);
    if (sem == NULL)
	printf("ERROR sem_open");

	// lock semaphore
	sem_wait(sem);

	message buff = {0};
	ptr = (char*)&buff;
	memcpy(ptr,(char*)mptr, size);
	printf("Consumer string: %s, String length = %d, USR led status: %d\n", ptr->string, ptr->string_length, ptr->USR_Led_Control);

	message buff1 = {0};
	ptr = (char*)&buff1;	

	strcpy(mesg_struct.string, "From consumer to producer msg");
        mesg_struct.string_length = strlen(mesg_struct.string);
        mesg_struct.USR_Led_Control = 1;

	memcpy(mptr, &mesg_struct, size);
	
	sem_post(sem);

	close(shm_fd);
	sem_unlink(name);
	
	

    return 0;
    
    
}
