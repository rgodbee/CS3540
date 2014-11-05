#include <stdio.h>
#include "record.h"
#include <stdlib.h>

void err_sys (const char* message);

int main (int argc, char* argv[])
{
  if (argc == 6) //add
  {
    FILE* f = fopen (argv[1], "a");
    if (f == NULL)
      err_sys ("error in opening file");
    record r;
    /* 
    Bring in information from the user and add it to the record struct
    The infomation that is stored is done incorrectly I think, because
    the binary I\O file does not seems to have the correct info
    */
    double price = atof(argv[4]);
    int count = atoi(argv[5]);
    create_record(argv[3], price, count);
    
    int size = fwrite (&r, sizeof(record), 1, f);
    if (size != 1)
      err_sys ("error in writing to the file");
      
    fclose (f); 
  } 
  else if (argc == 3) //repot
  {
    FILE* f = fopen (argv[1], "r");
    if (f == NULL)
      err_sys ("error in opening file");
    record r;
    int size = fread (&r, sizeof(record), 1, f);
    if (size != 1)
      err_sys ("error in reading from file");
    else               
    {
      while (fread(&r,sizeof(record),1,f)) {
        display_record (&r);
      }
    }
    fclose (f);
  }
  else if(argc == 4) //removal
  {
    FILE* f = fopen (argv[1], "r+");
    FILE *f_tmp;
    // record r;

    f=fopen("records.dat", "rb");
    if (!f) {
      err_sys("Unable to open file");
    }

    f_tmp=fopen("tmp.bin", "wb");
    if (!f_tmp) {
      err_sys("Unable to open file temp file.");
    }
    // ***second idea (didnt work, doesn't compile)***
    // while (fread(&r,sizeof(record),1,f)) {
    //   String nameDelete;
    //   strncpy (nameDelete, argv[3], 14);
    //   int result = strcmp (nameDelete, r -> name)
    //   if (result == 0) {
    //     printf("deleted\n");
    //   } else {
    //     fwrite(&r, sizeof(record), 1, f_tmp);
    //   }
    // }

    // ***first idea (didnt work, doesn't compile)***
    // while (fread(&r,sizeof(record),1,f)) {
    //   char nameDelete[15];
    //   strcpy(nameDelete, argv[3]);
    //   if (strcmp (nameDelete, r -> name) == 0) {
    //     printf("deleted\n");
    //   } else {
    //     fwrite(&r, sizeof(record), 1, f_tmp);
    //   }
    // }

    fclose(f);
    fclose(f_tmp);

    remove("records.dat");
    rename("tmp.bin", "records.dat");
    
  }
  else // error
    err_sys ("missing command line argument");      

  return 0;
}                           

void err_sys (const char* message)
{                   
  printf ("%s\n", message);
  exit (0);         
}
