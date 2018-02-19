/*

 * Author: Vipraja Patil

 * Date: 02/17/2018

 *  

 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/syscall.h>

// Create a thread info struct to pass in arguments to your threads

struct thread_info {

    pthread_t tid;         // the thread identifier

    char* filename;
    char* log_file;

};

FILE *file_log;
FILE *file_log2;
//initialize mutex

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// initialize other variables

struct node {

struct node * prev;

struct node * next;

};

struct info {

char data;

struct node obj;

};

struct info* insert_at_end(struct info *head, char userdata)

{

    struct info* newNode;

    newNode = (struct info*)malloc(sizeof(struct info));

    newNode->data = userdata; 

    if (head == NULL)

    {

        newNode->obj.prev = NULL;

        newNode = head;

    }

    else 

    {

        struct info* temp = head;

        while (temp->obj.next != NULL)

        {

            temp = temp->obj.next;                 //reach the end of the list

        }

        temp->obj.next = newNode;

        newNode->obj.prev = temp;

    }

    return head;

}

void log_print(FILE *fptr_,int parent_id, int pthread_id, int thread_id, char* s, char* a, char* b)
{

	FILE *fptr = fopen("hw3_log.log","a");
	time_t currenttime;
	time(&currenttime);
	fprintf(fptr,"Parent ID:%ld, Posix thread ID:%ld, Linux Thread ID:%ld, ",parent_id, pthread_id, thread_id);
	fprintf(fptr,"%s ",s);
	fprintf(fptr,"%s %s\n",a,b);
	//char *timeStr = ctime(&currenttime);
	//fprintf(fptr,"Time: %s",timeStr);
fflush(fptr);
	fclose(fptr);
}



void check_char(struct info *head)

{

    struct info* temp = (struct info*)malloc(sizeof(struct info));
    struct info* temp1 = (struct info*)malloc(sizeof(struct info));
    struct info* temp2 = (struct info*)malloc(sizeof(struct info));

    temp2 = head;
    int count = 0;
    int i = 0;
    char c,d,e,f;
    char arr[10];
    int flag;

    printf("The characters which occur 3 times are");

        while (head->obj.next != NULL)

        { 

            temp = temp2;

            while(temp->obj.next != NULL)

            {

                char b = temp->data;

                c = (char)((int)b + 32);

                d = (char)((int)b - 32);

                if (temp1->data == temp->data || head->data == c || head->data == d)

                {

                    count++;

                }

                

                temp = temp->obj.next;

            }

            

            if (count == 3)

                {

                    for(int j=0; j<i; j++)

                    {

                        char b = temp1->data;

                        e = (char)((int)b + 32);

                        f = (char)((int)b - 32);

                        if(arr[j] == temp1 -> data || arr[j] == e || arr[j] == f)

                        {

                            flag = 1;

                        }

                    }

                    if(flag == 0)

                    {
                    printf("%c", head -> data);
                    arr[i] = head -> data;

                    i++;
                    }

                    flag = 0;

                }

            head = head->obj.next;

            temp1 = head;

            count =0;

        }

}

 

// function for counting characters

void* thread1_function(void *arg)

{

    //pthread_t pthread1_self = pthread_self();

    //pid_t pid1 = getpid();

    //pid_t pthread1_linuxID = syscall(SYS_gettid);

    struct thread_info * thread1 = (struct thread_info *)arg;

    struct info* head = (struct info*)malloc(sizeof(struct info));

    FILE *f;
    log_print(file_log,getppid(),getpid(),syscall(SYS_gettid),"Thread 1 executing","","");

    f = fopen("Valentinesday.txt", "r");

    if(f == NULL)
{
	printf("File open error");
}
    while (!feof(f))

    {

        char a = fgetc(f);

        head = insert_at_end(head,a);

    }

    check_char(head);

    printf("\n");

    //pthread_mutex_lock(&mutex);

    //pthread_mutex_unlock(&mutex);
	
	fclose(f);
    
    log_print(file_log,getppid(),getpid(),syscall(SYS_gettid),"Thread 1 exiting","","");
    pthread_exit(NULL);

    

}

void signal_handler(int sig)

{
	
        printf("\n");
	if(sig == SIGUSR1 || sig == SIGUSR2)
	{
		printf("SIGUSR1 or SIGUSR2 received, exiting the thread.\n");
		pthread_exit(NULL);
	} 
	else if (sig == SIGVTALRM)
	{
    	char *command = "cat /proc/stat | head -n 5";
        FILE * cptr = popen(command, "r");
	log_print(file_log,getppid(),getpid(),syscall(SYS_gettid),"SIGVTALRM received, CPU utilization is ","","");
        	if(cptr)
		{
        		while(!feof(cptr))
        		{    
			file_log = fopen("hw3_log.log","a");
            		char temp = fgetc(cptr);
            		printf("%c", temp);
			fprintf(file_log,"%c",temp);
			fclose(file_log);
        		}
			fclose(cptr);
		}
	
	}

}

void* thread2_function(void *arg)

{
printf("\n");
    struct thread_info *thread2 = (struct thread_info*)arg;

    //pthread_t pthread2_self = pthread_self();

    //pid_t pid2 = getpid();

    //pid_t pthread2_linuxID = syscall(SYS_gettid);

    struct itimerval timer;
    struct sigevent signal;
    struct itimerspec timer_spec;
    timer_t timer_id;
    struct sigaction sig_act;
    log_print(file_log,getppid(),getpid(),syscall(SYS_gettid),"Thread 2 executing","","");

    memset(&sig_act, 0, sizeof(sig_act));
    sig_act.sa_handler = &signal_handler;
    sigaction(SIGVTALRM, &sig_act, NULL);
    sigaction(SIGUSR1, &sig_act, NULL);
    sigaction(SIGUSR2, &sig_act, NULL);

    timer.it_value.tv_sec=0;
    timer.it_value.tv_usec=100000;
    timer.it_interval.tv_sec=0;
    timer.it_interval.tv_usec=100000;

    setitimer (ITIMER_VIRTUAL, &timer, NULL);


    while(1);  

    log_print(file_log,getppid(),getpid(),syscall(SYS_gettid),"Thread 2 exiting","","");
    pthread_exit(NULL);

}

 

int main()

{

    pthread_t thread_first, thread_second;

    struct thread_info* thread1 = (struct thread_info *)malloc(sizeof(struct thread_info));

    struct thread_info* thread2 = (struct thread_info *)malloc(sizeof(struct thread_info));

    FILE *file = fopen("Valentinesday.txt", "r");
    thread1->filename = "hw3_log.log";
    thread2->filename = "hw3_log.log";
    file_log = fopen(thread1->log_file, "a");


    if(pthread_create (&thread_first, NULL, thread1_function, (void *)thread1))
    {
        printf("Child Thread 1 creation failed");
	log_print(file_log,getppid(),getpid(),syscall(SYS_gettid),"Child Thread 1 creation failed","","");
    }   

	pthread_join(thread_first, NULL);

    if(pthread_create (&thread_second, NULL, thread2_function, (void*)thread2))
    {
        printf("Child Thread 2 creation failed");
	log_print(file_log,getppid(),getpid(),syscall(SYS_gettid),"Child Thread 2 creation failed","","");
    }

   
    
    pthread_join(thread_second, NULL);
}
