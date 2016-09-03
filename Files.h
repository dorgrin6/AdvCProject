#define _CRT_SECURE_NO_WARNINGS
#ifndef __FILES_H
#define __FILES_H
#include "ApartmentList.h"
#include "CommandList.h"
#include <stdio.h>

/*fileSize:
	recieves a file pointer fp, and returns files size.

*/
long int fileSize(FILE *fp);

/*checkOpenFile:
	recieves a file pointer and prints error message if file wasnt opened correctly,
	in such case, program will then quit (exit(1)).
*/
void checkOpenFile(FILE * fp);

/*checkMemoryAllocation:
	recieves a pointer and prints error message if memory allocation failed.
	In such case, program will then quit (exit(1)).
*/
void checkMemoryAllocation(void * ptr);

/* writeApartmentsToBinaryFile:
	recieves an apartment list and writes it to binary file.
*/
void writeApartmentsToBinaryFile(APT_LIST *aptLst);

/* writeCmdListToTextFile:
	recieves a command list and writes it to text file.
*/
void writeCmdListToTextFile(CMD_LIST *cmdLst, char *short_term_history[N]);

/* getBytesFromApartment:
	recieves an apartment and and returns as output params:
		b1,b2,b3: bytes as requested in assignment (respective to their number from left to right).
		entranceDate: true if the date to return is entrance date, other will update as insertion date. 
*/
void getBytesFromApartment(APARTMENT *apt, BYTE *b1, BYTE *b2, BYTE *b3, BOOL entranceDate);

/* getApartmentFromFile: 
	recieves an apartment file and returns next apartment (to file indicator).
*/
APARTMENT* getApartmentFromFile(FILE *input);


/* getParamsFromBytes: 
	recieves the 3 bytes printed by getBytesFromApartment
		and converts them back to date.
*/
DATE * getParamsFromBytes(BYTE b1, BYTE b2, BYTE b3, SI *numOfRooms);

/*isEmptyFile:
	Returns TRUE iff the file is empty.
*/
BOOL isEmptyFile(FILE*fp);

/* getTextFileLineNum:
	Returns the number of lines in file fp.
*/
int getTextFileLineNum(FILE *fp);

/*openCommandFile:
	Recieves a command file name, opens it and insert command to history.
	If the file doesnt exist a new one will be created.
*/
void openCommandFile(char *TextFileName, char *short_history[N],int *sthSize, CMD_LIST *cmdLst);


/*openApartmentsFile:
	Recieves a apartment file name, opens it and insert command to aptList.
	If the file doesnt exist a new one will be created.
*/
void openApartmentsFile(char *binFileName, APT_LIST *aptLst);


/*getNextLineLength:
	Recieves a file pointer and returns the length of the next line in file.
*/
int getNextLineLength(FILE *fp);


#endif