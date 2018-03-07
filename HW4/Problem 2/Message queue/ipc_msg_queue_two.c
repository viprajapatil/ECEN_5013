
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>


typedef struct{
	char string[50];
	int string_length;
	int USR_Led_Control;
}message;

#define SERVER_QUEUE_NAME   "/my_msg_queue_server"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

int main()
{
	mqd_t server, client;   // queue descriptors   
    struct mq_attr attr;
	
	message *ptr;
    message mesg_struct;
    ptr = &mesg_struct;
	 char buff[sizeof(message)] = {0};
	
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;
	
	server = mq_open (SERVER_QUEUE_NAME, O_RDWR | O_CREAT, 0666, &attr);
	if (server < 0)
		printf("ERROR opening message queue\n");
	
	//char* buffrec = (char*)(&mesg_struct);

	//send message to process 2
	strcpy(mesg_struct.string, "From Process 1 to Process 2 msg\n");
    mesg_struct.string_length = strlen(mesg_struct.string);
    mesg_struct.USR_Led_Control = 0;
	char* buffptr = (char*)(&mesg_struct);
	if (mq_send (server, buffptr, sizeof(message), 0) < 0)
		printf("ERROR mq_send\n");
	else printf("Process 1: message sent\n");
	//receive a message from a message queue
	char *buffrec;
    	message buffer = {0};
    	buffrec = (char*)&buffer;
	
	if (mq_receive (server, buffrec, sizeof(mesg_struct), 0) < 0)
		printf("ERROR mq_receive\n");
	else printf ("Process 1: message received.\n");
	
	ptr = (message*)(buffrec);
    printf("Process1 Received string: %s, String length = %d, USR led status: %d\n", ptr->string, ptr->string_length, ptr->USR_Led_Control);
	
	

	mq_close(server);
	
	
	return 0;
}
