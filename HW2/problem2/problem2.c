#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>


void main()
{
	FILE *fptr;
	int f;
	
	//Print to standard out an interesting string using printf
	printf("APES Homework 2 \n");
	
	//Create a file
	char *new_file = "example.txt";
	
	//Modify the permissions of the file to be read/write
	/*read     = 4
	write    = 2
	execute  = 1
	owner    = read | write | execute = 7
	group    = read | write | execute = 7
	other    = read | write | execute = 7 */
	
	f = chmod("example.txt", 0777);
	if (f == 0)
	{
		printf("File permissions change successful \n");
	}
	else printf("File permissions change not successful \n");
	
	//Open the file (for writing)
	 fptr = fopen(new_file, "w");   // open example.txt in write mode
	 if (fptr == NULL)
    {
        printf("File does not exists \n");
    }
	
	//Write a character to the file
	char *data = "a";
	f = fwrite(&data, 1, sizeof(data), fptr);
	if (f != sizeof(data))
	{
		printf("Error in writing a character \n");
	}
	else printf("Write successful \n");
	
	//Close the file
	f = fclose(fptr);
	if (f != 0)
	{
		printf("Error in closing the file\n");
	}
	else printf("File is successfully closed \n");
	
	//Open the file (in append mode)
	fptr = fopen(new_file, "a");
	if (fptr == NULL)
    {
        printf("Error in opening the file in append mode \n");
    }
	
	//Dynamically allocate an array of memory
	char *str = malloc(sizeof(char*)*100);
	
	//Read and input string from the command line and write to the string
	fptr = fopen(new_file, "r");
	scanf("%[^\n]s",str);
	char* fg = fgets(str, 100, fptr);
	if (!(fg))
	{
		printf("Successly read the string from input \n");
	}
	
	//Write the string to the file
	f = fwrite(str, 1, sizeof(str), fptr);
	if (f = 0)
	{
		printf("Error in writing string \n");
	}
	else printf("Write successful \n");
	
	//Flush file output
	fflush(fptr);
	
	//Close the file
    fclose(fptr);
	
	//Open the file (for reading)
	fptr = fopen(new_file, "r");
	
	//Read a single character (getc)
	char user_read = getc(fptr);
	if (user_read != EOF)
	{
		printf("Read successful = %c \n", user_read);
	}
	else printf("Read unsuccessful \n");
	
	//Read a string of characters (gets)
	fgets(str,100, fptr);
	/*if (s != EOF)
	{
		printf("Character read successful");
	}
	else printf("No character has been read");*/
	
	//Close the file
	fclose(fptr);
	
	//Free the memory
	free(fptr);
	
}
