#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void err_sys (const char* message);

int main(void)
{
	// making the file
	// FILE* f = fopen ("letters.txt", "w+");
	// if (f == NULL)
	// 	err_sys ("error in opening file");
	
	// making the child
	pid_t pid;

	// filling the file
	if((pid = fork()) < 0)
	{
		 err_sys("fork error");
	}
	else if(pid == 0)
	{
		FILE* f = fopen ("letters.txt", "w+");
		if (f == NULL)
			err_sys ("error in opening file");
		char letters = 'a';
		int counter;
		int pos = 2;
		for(counter = 0; counter <= 25; counter++)
		{
			fseek(f, pos, SEEK_SET);
			int size = fwrite (&letters, sizeof(char), 1, f);
			if (size != 1)
				err_sys ("error in writing to file");
			
			// printf("%c", letters);
			letters++;
			pos+=2;
		}
		fclose (f);
	}
	else
	{
		FILE* f = fopen ("letters.txt", "w+");
		if (f == NULL)
			err_sys ("error in opening file");
		char letters = 'A';
		int counter;
		int pos = 1;
		for(counter = 0; counter <= 25; counter++)
		{
			fseek(f, pos, SEEK_SET);
			int size = fwrite (&letters, sizeof(char), 1, f);
			if (size != 1)
				err_sys ("error in writing to file");
			
			// printf("%c", letters);
			letters++;
			pos+=2;
		}
		fclose (f);
	}

	return 0;
}

void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (0);
}