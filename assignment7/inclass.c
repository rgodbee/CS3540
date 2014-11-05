// p 355 in text
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <unistd.h>
#include <signal.h>

void err_sys (const char* message);
static void sig_alarm(int signo);

static jmp_buf timer_alrm;

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		err_sys("wrong set of arguments");
	}
	char *ptr;

	int timer = strtol(argv[1], &ptr, 10);


	if(signal (SIGALRM, sig_alarm) == SIG_ERR)
		err_sys("shit broke");
	alarm(1);
	if(sigsetjmp(timer_alrm, 1) != 0)
	{
		timer--;
		if(timer <= 0)
		{
			printf("BOOM\n");
			exit(0);
		}
		
		else
		{
			printf("%d\n", timer);	
			alarm(1);
		}
	}

	while(1);
	exit(0);
}

static void sig_alarm(int signo)
{
	siglongjmp(timer_alrm, 1);
}

void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (0);
}