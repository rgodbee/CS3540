#include "record.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

record* create_record (char* n, double p, int c)
{
  assert (n != NULL);
  record* r = malloc (sizeof(record));
  if (r != NULL)
  {
    strncpy (r -> name, n, NAMESIZE - 1);
    r -> price = p;
    r -> count = c;
  }
  return r;
}

void display_record (record* r)
{
  assert (r != NULL);
  printf ("%s\t%fX\t%d =\ttotal\n", r -> name, r -> price, r -> count);
}
