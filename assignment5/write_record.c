#include <stdio.h>
#include "record.h"
#include <stdlib.h>

void err_sys (const char* message);

int main (int argc, char* argv[])
{
  if (argc < 2)
    err_sys ("missing command line argument");
  FILE* f = fopen (argv[1], "w");
  if (f == NULL)
    err_sys ("error in opening file");
  record r;
  int size = fread (&r, sizeof(record), 1, f);
  if (size != 1)
    err_sys ("error in reading from file");
  else
    display_record (&r);
  fclose (f);
  return 0;
}

void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (0);
}
