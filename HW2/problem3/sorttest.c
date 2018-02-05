
#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>

int main()
{
	
  int i, n, j;
  time_t t;
  int32_t arr[256], arr1[256];
  int32_t temp;

  printf("Invoking syscall mysort\n");

  /* Intializes random number generator */
  srand((unsigned) time(&t));

  /* Print 5 random numbers from 0 to 49 */
  for( i = 0 ; i <256 ; i++ ) {
     arr[i] = 48 + (rand() % 79);
     //printf("%c", (char)(48 + (rand() % 79)));
  }
 
  for( i = 0 ; i <256 ; i++ ) {
     //arr[i] = 48 + (rand() % 79);
     printf("%c", arr[i]);
  }
  printf("/n");
  int32_t *str = arr;
  int32_t *str_sort = arr1;

  int ret = syscall(334, str, 256, str_sort);

  printf("\n");
  if (ret == 0)
	{
		printf("\nSyscall successful\n");
	}
	else	printf("\nSyscall failed\n");

  for( i = 0 ; i <256 ; i++ ) {
     //arr[i] = 48 + (rand() % 79);
     printf("%c", *(str_sort+i));
  }
printf("\n");

  


return 0;
}


