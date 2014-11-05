#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMESIZE 15


static const char DUMMY[] = "0123456789abcd";


typedef struct
{
	char  name[NAMESIZE];
	double price;
	int count;
}entry;

void err_sys(const char* message);
int addEntryToTransaction(entry newEntry, FILE* logFile);
int positionToWrite(FILE* logFile);
int deleteFirstOccuranceOfEntryFromTransaction(entry deleteEntry, FILE* logFile);
int positionToDelete(entry deleteEntry, FILE* logFile);
void printReport(FILE* logFile);

int main(int argc, const char* argv[])
{
	if (argc < 2)
	    err_sys ("missing command line argument");
	// create file if not already created
	FILE* initialize_file = fopen(argv[1],"a+");
	fclose(initialize_file);

	FILE* logFile = fopen(argv[1],"r+");
	if(logFile == NULL)
		err_sys("error in opening file");
	char* command = argv[2];
	if(strcmp("add", command) == 0)
	{
		if(argc != 6)
			err_sys ("missing command line argument: ./a.out FILE add name price count");
		entry* newEntry = malloc(sizeof(entry));
		char* temp;
		strncpy(newEntry -> name, argv[3], NAMESIZE -1);
		newEntry -> price = strtod(argv[4], &temp);
		newEntry -> count = atoi(argv[5]);
		addEntryToTransaction(*newEntry, logFile);
	}
	else if(strcmp("report", command) == 0)
	{
		if(argc != 3)
			err_sys ("missing command line argument: ./a.out FILE report");
		printReport(logFile);
	}
	else if(strcmp("delete", command) == 0)
	{
		if(argc != 4)
			err_sys ("missing command line argument: ./a.out FILE delete name");
		entry* deleteEntry = malloc(sizeof(entry));
		strncpy(deleteEntry -> name, argv[3], NAMESIZE -1);
		deleteEntry -> price = 0.0;
		deleteEntry -> count = 0;
		deleteFirstOccuranceOfEntryFromTransaction(*deleteEntry, logFile);
	}
	else
		err_sys("invalid command argument");
	fclose(logFile);

	return 0;
}

/*
 * addEntryToTransaction
 * Adds a record to the tranaction log contained in the log records.dat
 * pram: *newEntry The entry that you wish to add to the log file
 * pram: logFile The location of the log file you wish to store the newEntry 
 */
int addEntryToTransaction(entry newEntry, FILE* logFile)
{
	if(logFile == NULL)
		return 0;
	int result;
	int position = positionToWrite(logFile)*sizeof(entry);
	result = fseek(logFile, position, SEEK_SET);
	if(result != 0)
	{
		err_sys("error seeking in file");
		return -1;
	}
	result = fwrite(&newEntry, sizeof(entry), 1, logFile);
	if(result == 0)
	{
		err_sys("error writting to file");
		return -1;
	}
	return result;
}

/*
 * positionToWrite
 * return: >=0  record you would like to write to
 * return: -1 file you would like to write to is NULL
 */
int positionToWrite(FILE* logFile)
{
	if(logFile == NULL)
	{
		err_sys("file you would like to write to is NULL when looking for a position");
		return -1;
	}
	entry readEntry;
	int counter;
	while(fread(&readEntry , sizeof(entry), 1, logFile) == 1)
	{// will check to see if the readEntry is a dummy location
		if(strcmp(DUMMY, readEntry.name) == 0)
			return counter;
		counter++;	
	} 
	if(feof(logFile))
	{
		return counter;	
	}
	else
	{
		err_sys("error reading from file, position of record to overwrite could not be found");
		return -1;
	}
}	

int deleteFirstOccuranceOfEntryFromTransaction(entry deleteEntry, FILE* logFile)
{
	if(logFile == NULL)
		return 0;
	int result;
	int position = positionToDelete(deleteEntry, logFile)*sizeof(entry);
	// dummy entry
	// entry* dummyEntry = malloc(sizeof(entry));
	// strncpy(dummyEntry -> name, DUMMY, NAMESIZE -1);
	// dummyEntry -> price = NULL;
	// dummyEntry -> count = NULL;

	result = fseek(logFile, position, SEEK_SET);
	if(result != 0)
	{
		err_sys("error seeking in file");
		return -1;
	}
	result = fwrite(&DUMMY, sizeof(entry), 1, logFile);
	if(result == 0)
	{
		err_sys("error writting to file");
		return -1;
	}
	return result;
}
/*
 * positionToDelete
 * return: >=0  record you would like to delete
 * return: -1 file you would like to delete from is NULL
 * return: -2 if record was not in file
 */
int positionToDelete(entry deleteEntry, FILE* logFile)
{
	if(logFile == NULL)
	{
		err_sys("file you would like to write to is NULL when looking for a position");
		return -1;
	}
	entry readEntry;
	int counter;
	while(fread(&readEntry , sizeof(entry), 1, logFile) == 1)
	{// will check to see if the readEntry is a dummy location
		if(strcmp(deleteEntry.name, readEntry.name) == 0)
			return counter;
		counter++;	
	} 
	if(feof(logFile))
	{
		err_sys("record was not found in the file, and could not be deleted");
		return -2;	
	}
	else
	{
		err_sys("error reading from file, position of record to overwrite could not be found");
		return -1;
	}
}

void printReport(FILE* logFile)
{
	if(logFile == NULL)
	{
		err_sys("file you would like to repot is NULL");
	}
	entry readEntry;
	double total = 0;
	while(fread(&readEntry , sizeof(entry), 1, logFile) == 1)
	{
		if(strcmp(DUMMY, readEntry.name) != 0)
		{
			double product = readEntry.price * readEntry.count;
			printf("%s\t%8.2f X\t%d = %8.2f\n", readEntry.name, readEntry.price, readEntry.count, product);
			total += product;
		}
	} 
	printf("\t\t\tTotal:%8.2f\n", total);
}


void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (0);
}
