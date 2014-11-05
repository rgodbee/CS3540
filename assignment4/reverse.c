#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>

void err_sys(const char* message);

int main(int argc, char *argv[]) {

    int source_file, destination, n;
    char buf;
    int filesize;
    int i;

    if (argc != 3) {
        err_sys("usage: reverse <source_file> <destination>");
        exit(-1);
    }
    // read permission for user on source_file
    if ((source_file = open(argv[1], 0400)) < 0) { 
        err_sys("cannot open source_file");
        exit(-1);
    }
    // read, write, exicute permission for user on destination
    if ((destination = creat(argv[2], 0700)) < 0) { 
        err_sys("cannot create destination");
        exit(-1);
    }

    filesize = lseek(source_file, (off_t) 0, SEEK_END); //filesize is lastby +offset

    for (i = filesize - 1; i >= 0; i--) { //read byte by byte from end
        lseek(source_file, (off_t) i, SEEK_SET);
        n = read(source_file, &buf, 1);
        if (n != 1) {
            err_sys("read error");
            exit(-1);
        }
        n = write(destination, &buf, 1);
        if (n != 1) {
            err_sys("write error");
            exit(-1);
        }
    }
    printf("done\n"); 
    close(source_file);
    close(destination);

    return 0;
}

void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit(0);
}
