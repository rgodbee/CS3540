#ifndef _RECORD_H
#define _RECORD_H

#define NAMESIZE 15
#define PRICESIZE 8
#define COUNTSIZE 4


typedef struct
{
  char name[NAMESIZE];
  double price;
  signed int count : COUNTSIZE;
} record;

record* create_record (char* n, double p, int c);

void display_record (record* r);

void remove_record (record* r);

#endif
