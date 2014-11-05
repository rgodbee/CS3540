/*
Richard Godbee
Linux and C
Assignment 9
07/20/2014
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>
#include <signal.h>

static void sig_pause (int signo);
static void sig_alarm (int signo);
void err_sys (const char* message);

static jmp_buf alarm_jmp;
static jmp_buf sleep_jmp;

int main(int argc, char* argv[])
{
	int counter = 0;
	int toggle = 1;
	
	if (signal (SIGINT, sig_pause) == SIG_ERR)
		err_sys ("pause signal error");
	if (signal (SIGALRM, sig_alarm) == SIG_ERR)
		err_sys ("alarm signal error");
	
	alarm (1);
	if (sigsetjmp (alarm_jmp, 1) != 0)
	{
		counter++;
		printf ("%d\n", counter);
		alarm (1);
	}
	if (sigsetjmp (sleep_jmp, 1) != 0)
	{
		if(toggle)
		{
			alarm(0);
			printf ("paused\n");
			toggle = 0;
		}
		else
		{
			printf ("unpaused\n");
			toggle = 1;
			alarm(1);
			// siglongjmp (alarm_jmp, 0);
		}
	}
	while (1);
	exit(0);
}

static void sig_pause (int signo)
{
	siglongjmp (sleep_jmp, 1);
}

static void sig_alarm (int signo)
{
	siglongjmp (alarm_jmp, 1);
}

void err_sys (const char* message)
{
	printf ("%s\n", message);
	exit (0);
}