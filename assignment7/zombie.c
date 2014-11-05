#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void err_sys (const char* message);

int main(void)
{
    pid_t pid;

    if((pid = fork()) < 0)
    {
         err_sys("fork error");
    }
    else if(pid == 0)
    {
        pid_t pid2;
        if((pid2 = fork()) < 0)
        {
             err_sys("fork error");
        }
        else if(pid > 0)
        {
            waitpid(pid2,NULL,0);  
        }
        else
        {
            exit(0);
        }
        
    }
    else
    {
        system("ps -l");
        // sleep(1);   
        system("ps");
        // exit(0);
    }
    system("ps");
    return 0;
}

void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (0);
}