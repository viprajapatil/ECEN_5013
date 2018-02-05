#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <time.h>

void main()
{
	struct timeval tv;
	struct timezone *tz;
	printf("Current process ID= %ld\n", syscall(39));
	printf("Current user ID= %ld\n", syscall(102));

	int r = syscall(96,&tv,NULL);
	if (r == 0)
	{
		printf("Current date and time= %ld\n",tv.tv_sec );
	}
	else
	{
		printf("syscall for gettiemofday failed\n");
	}

	time_t t;
 	int32_t arr[256], arr1[256];

	/* Intializes random number generator */
  srand((unsigned) time(&t));

  for( int i = 0 ; i <256 ; i++ ) {
     arr[i] = 48 + (rand() % 79);
  }
  int32_t *str = arr;
  int32_t *str_sort = arr1;

	int s = syscall(334,str, 256, str_sort);
	if (r == 0)
	{
		printf("System call for sorting array successful\n");
	}
	else
	{
		printf("syscall for sortvp failed\n");
	}	


}

