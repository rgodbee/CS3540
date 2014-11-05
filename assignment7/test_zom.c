// #include <stdio.h>
// #include <unistd.h>
// #include <sys/wait.h>

// void ChildProc(void)
// {
//     int i;
//     for(i = 0; i < 100; i++)
//     {
//          printf("Child : %d from process <%d> : Parent <%d>\n",i, getpid(), getppid());
//     }
// }

// void ParentProc(void)
// {
//     int i;
//     for(i = 0; i < 20; i++)
//     {
//          printf("Parent : %d from process <%d> : Parent <%d>\n",i, getpid(), getppid());
//     }
// }

// int main(void)
// {
//      pid_t child;
//      child = fork();

//      if(child == 0)
//      {
//           ChildProc();
//      }
//      else
//      {
//           ParentProc();
//           system("ps");
//           waitpid(child,NULL,0);
//           system("ps");
//      }
//      return 0;
// }

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main ()
{ 
  pid_t child_pid;

  child_pid = fork ();
  if (child_pid > 0) {
    sleep(20);
  }
  else {
    exit(0);
  }
  system("ps");
  return 0;
}