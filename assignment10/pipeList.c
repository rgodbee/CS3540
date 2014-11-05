#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	MAXLINE	4096 /* max line length */

void err_sys (const char* message);

int main(void)
{
  int n;
  int fd[2];
  pid_t	pid;
  char line[MAXLINE];
  // int counter = 0;
  // int counter2 = 0;

  if (pipe(fd) < 0)
    err_sys("pipe error");
  if ((pid = fork()) < 0)
  {
    err_sys("fork error");
  } 
  else if (pid > 0) 
  {	/* parent */
    close(fd[0]);
    FILE *ls = popen("ls -l", "r");
    char buf[MAXLINE];
    
    while (fgets(buf, sizeof(buf), ls) != 0) {
      // counter++;
      write(fd[1], buf, MAXLINE);
    }
    // printf("counter: %d", counter);
    pclose(ls);  
  } 
  else
  {	/* child */
    close(fd[1]);
    do
    {
      // counter2++;
      n = read(fd[0], line, MAXLINE);
      write(STDOUT_FILENO, line, n);
    }while(n != 0);
    // printf("counter2: %d\n", counter2);
    // n = read(fd[0], line, MAXLINE);
    // write(STDOUT_FILENO, line, n);
  }
  exit(0);
}

void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (1);
}