#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>

typedef struct{
    char string[50];
    int string_length;
    int USR_Led_Control;
}message; 

int flag;

int main()
{
    // from parent to child, parent write, child read
   int pipe_parent2child[2];                                      //0- reading, 1- writing
    
   // from child to parent, child write, parent read
   int pipe_child2parent[2];                                      //0- reading, 1- writing
    
    pid_t pid;                                                     // pid of child process    
	if (pipe(pipe_parent2child) < 0)                             // create the pipe
    {                            
       perror("pipe error");
        printf("pipe_parent2child pipe error\n");
    }    if (pipe(pipe_child2parent) < 0)                            // create the pipe
    {                             
       perror("pipe error");
        printf("pipe_child2parent pipe error\n");
    }
        
    pid = fork();
    
    if (pid == 0)
    {
flag = 0;
        // child process
        printf("Child process\n");
	message *ptr;
	message mesg_struct;
	ptr = &mesg_struct;

        // child process read
        //close(pipe_child2parent[1]);
        char buff[sizeof(message)] = {0};
        read(pipe_parent2child[0], buff, sizeof(message));
        ptr = (message*)(buff);
        printf("Child Received string: %s, String length = %d, USR led status: %d\n", ptr->string, ptr->string_length, ptr->USR_Led_Control);
	close(pipe_parent2child[0]);
        
        // child process write        
	strcpy(mesg_struct.string, "From child to parent msg");
        mesg_struct.string_length = strlen(mesg_struct.string);
        mesg_struct.USR_Led_Control = 0;
	close(pipe_child2parent[0]);
	ptr = &mesg_struct;
        int ret = write(pipe_child2parent[1], ptr, sizeof(message));
	perror("write child");
	printf("Send:%d\n",ret);
	printf("Parent send string: %s, String length = %d, USR led status: %d\n", ptr->string, ptr->string_length, ptr->USR_Led_Control);
        printf("Data sent from child to parent\n");
        close(pipe_child2parent[1]);
        exit(1);
    }
    else
    {
flag = 1;
        // parent process
        printf("Parent process\n");
        
	// parent process write
	message *ptr;
        message mesg_struct;
	ptr = &mesg_struct;
	strcpy(mesg_struct.string, "From parent to child msg");
        mesg_struct.string_length = strlen(mesg_struct.string);
        mesg_struct.USR_Led_Control = 1;
        
        close(pipe_parent2child[0]); //close read pipe
        write(pipe_parent2child[1], ptr, sizeof(message));
        printf("Data sent from parent to child\n");
        close(pipe_parent2child[1]);
        //open(pipe_parent2child[0]);

	while(!flag);
        
        // parent process read
        close(pipe_child2parent[1]);
        char buff[sizeof(message)] = {0};
        int ret = read(pipe_child2parent[0], buff, sizeof(message));
        ptr = (message*)(buff);
        printf("Parent Received string: %s, String length = %d, USR led status: %d\n", ptr->string, ptr->string_length, ptr->USR_Led_Control);
        close(pipe_child2parent[0]);
        
        
    }    
}
