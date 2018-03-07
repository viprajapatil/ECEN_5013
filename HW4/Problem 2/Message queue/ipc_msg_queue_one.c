#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>


typedef struct{
	char string[50];
	int string_length;
	int USR_Led_Control;
}message;

#define SERVER_QUEUE_NAME   "/my_msg_queue_server"
#define QUEUE_PERMISSIONS 0666
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

int main()
{
    mqd_t server;   // queue descriptors   
    struct mq_attr attr;
	
	message *ptr;
    message mesg_struct;
    ptr = &mesg_struct;
	 char buff[sizeof(message)] = {0};
	
    //attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = sizeof(message);
    //attr.mq_curmsgs = 0;
	
	server = mq_open (SERVER_QUEUE_NAME, O_RDWR | O_CREAT, QUEUE_PERMISSIONS, &attr);
	if (server < 0) 
        printf("ERROR opening message queue\n");
	
	if (mq_receive (server, buff, sizeof(message), NULL) < 0)
		printf("ERROR mq_receive\n");
	else printf ("Process 2: message received.\n");
	//send message
	char* buffptr = (char*)&mesg_struct;
	strcpy(mesg_struct.string, "From Process 2 to Process 1 msg\n");
    mesg_struct.string_length = strlen(mesg_struct.string);
    mesg_struct.USR_Led_Control = 1;
	
	if (mq_send (server, buffptr, sizeof(mesg_struct), 0) == -1)
		printf("ERROR mq_send\n");
	else printf("Process 2: message sent\n");
	
	
	//receive message
	//char* buffrec = (char*)(&buff);
	
	ptr = (message*)(buff);
    printf("Process2 Received string: %s, String length = %d, USR led status: %d\n", ptr->string, ptr->string_length, ptr->USR_Led_Control);

	mq_unlink(SERVER_QUEUE_NAME);
	
}


  
