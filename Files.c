#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Files.h"
#include "GeneralDefs.h"
#include "ApartmentList.h"
#include "Date.h"
#include "CommandList.h"


#include <stdlib.h>
long int fileSize(FILE *fp) {
	long int res, saver;
	saver = ftell(fp);
	fseek(fp, 0, SEEK_END);
	res = ftell(fp);
	fseek(fp, saver, SEEK_SET);
	return res;

}


void checkOpenFile(FILE * fp) {
	if (fp == NULL) {
		printf("Error: File didn't open properly\n");
		exit(1);
	}
}//checkOpenFile

void checkMemoryAllocation(void * ptr) {
	if (ptr == NULL) {
		printf("Error: Memory allocation failed\n");
		exit(1);
	}
}//checkAlloc

void writeApartmentToBinaryFile(APARTMENT *apt, FILE *output) {
	BYTE b1, b2, b3; // (entrance date) bytes to write to file
	BYTE b4, b5, b6; // (insertion date) bytes to write to file 
	SI addressLen; // length of address

	//write code
	fwrite(&(apt->code), sizeof(SI), 1, output);

	//write address
	addressLen = (SI)(strlen(apt->address));
	fwrite(&addressLen, sizeof(SI), 1, output);
	fwrite(apt->address, sizeof(char), addressLen, output);

	//wrote price
	fwrite(&(apt->price), sizeof(int), 1, output);

	//write bytes
	getBytesFromApartment(apt, &b1, &b2, &b3, TRUE);

	fwrite(&b1, sizeof(BYTE), 1, output);
	fwrite(&b2, sizeof(BYTE), 1, output);
	fwrite(&b3, sizeof(BYTE), 1, output);


	getBytesFromApartment(apt, &b4, &b5, &b6, FALSE);

	fwrite(&b4, sizeof(BYTE), 1, output);
	fwrite(&b5, sizeof(BYTE), 1, output);
	fwrite(&b6, sizeof(BYTE), 1, output);
}//writeApartmentToBinaryFile

void writeApartmentsToBinaryFile(APT_LIST *aptLst) {
	APT_NODE *curr = aptLst->head;

	FILE *output = fopen("Apartments.bin", "wb");
	checkOpenFile(output);

	while (curr != NULL) {
		writeApartmentToBinaryFile(curr->data, output);
		curr = curr->next;
	}

	fclose(output);

}//writeApartmentsToBinaryFile



void getBytesFromApartment(APARTMENT *apt, BYTE *b1, BYTE *b2,BYTE *b3, BOOL entranceDate) {
	BYTE mask1 = 0x01;
	BYTE mask2 = 0b00011110;
	BYTE mask3 = 0b01110000;
	
	DATE * date; // kind date to insert

	if (entranceDate == TRUE)
		date = apt->entranceDate;
	else
		date = apt->insertionDate;
	
	*b1 = apt->amountOfRooms << 4;
	*b1 |= ((date->day & mask2) >> 1);

	*b2 = (mask1 & date->day);
	*b2 <<= 4;
	*b2 |= date->month;
	*b2 <<= 3;
	*b2 |= (((date->year - MILLENNIUM) & mask3) >> 4);

	*b3 = date->year << 4;
}//getBytesFromApartment

void writeCmdListToTextFile(CMD_LIST *cmdLst, char *short_term_history[N]) {
	FILE *output = fopen("CmdList.txt", "w"); // output file
	checkOpenFile(output);
	CMD_NODE *curr = cmdLst->head; // current node in travese
	int i;
	
	//print shortlist to file 
	for (i = 0; i  <N ; i++) {
		if (short_term_history[i] != '\0') {
			fputs(short_term_history[i],output);
			fputc('\n',output);
		}
	}

	//print cmd list to file 
	while (curr != NULL) {
		fputs(curr->data, output);
		fputc('\n', output);
		curr = curr->next;
	}


	rewind(output);

	fclose(output);
}

APARTMENT* getApartmentFromFile(FILE *input){
	APARTMENT *res; // functions result
	SI addressLen; // address length
	BYTE b1, b2, b3; // bytes 
	SI numOfRooms; // number of rooms
	char *address; // address in apartment

	//not long enough file
	if (fileSize(input) - ftell(input) < sizeof(APARTMENT))
		return NULL;

	res = (APARTMENT *)malloc(sizeof(APARTMENT));
	checkMemoryAllocation(res);

	//code
	fread(&(res->code), sizeof(SI), 1, input);
	
	//address
	fread(&addressLen, sizeof(SI), 1, input);
	address = (char *)malloc(sizeof(char)*(addressLen+1));
	checkMemoryAllocation(address);

	fread(address, sizeof(char), addressLen, input);
	address[addressLen] = '\0';
	res->address = address;

	//price
	fread(&(res->price), sizeof(int), 1, input);

	//first 3 bytes
	fread(&b1, sizeof(BYTE), 1, input);
	fread(&b2, sizeof(BYTE), 1, input);
	fread(&b3, sizeof(BYTE), 1, input);

	res->entranceDate = getParamsFromBytes(b1, b2, b3, &numOfRooms);

	res->amountOfRooms = numOfRooms;

	//second 3 bytes
	fread(&b1, sizeof(BYTE), 1, input);
	fread(&b2, sizeof(BYTE), 1, input);
	fread(&b3, sizeof(BYTE), 1, input);

	res->insertionDate = getParamsFromBytes(b1, b2, b3, &numOfRooms);

	return res;
}//getApartmentFromFile

DATE * getParamsFromBytes(BYTE b1, BYTE b2, BYTE b3, SI *numOfRooms) {
	BYTE mask1 = 0x0F;
	BYTE mask2 = 0b01111000;
	BYTE mask3 = 0b00000111;
	BYTE mask4 = 0b10000000;

	DATE * resDate = (DATE *)malloc(sizeof(DATE));
	checkMemoryAllocation(resDate);
	SI day;
	SI month;
	SI year;
	
	*numOfRooms = b1 >> 4;

	day = b1 & mask1;
	day <<= 1;
	day |= ((b2 & mask4)>>7);

	month = (b2 & mask2);
	month >>= 3;

	year = b2 & mask3;
	year <<= 4;
	year |= (b3 >> 4);

	//update result
	resDate->day = day;
	resDate->month = month;
	resDate->year = year + MILLENNIUM;

	return resDate;
}//getBytesFromApartment

void openCommandFile(char *TextFileName, char *short_history[N], int *sthSize, CMD_LIST *cmdLst) {
	FILE *cmdFile; // file to open
	int i = 0;
	int lines; // number of lines in file
	int lineLen; // length of line in file
	char *newCommand; // new command to insert

	cmdFile = fopen(TextFileName, "a+");
	checkOpenFile(cmdFile);

	if (isEmptyFile(cmdFile) == TRUE)
		return;

	lines = getTextFileLineNum(cmdFile);

	//insert short history
	while (i < MIN(lines, N)) {
		lineLen = getNextLineLength(cmdFile);
		newCommand = (char *)malloc(sizeof(char) * (lineLen + 2));
		checkMemoryAllocation(newCommand);

		fgets(newCommand, lineLen + 2, cmdFile);
		newCommand[lineLen] = '\0';
		if (strcmp(newCommand, "\n") != 0 && strcmp(newCommand, "") != 0) {
			short_history[i++] = newCommand;
			(*sthSize)++;
		}
		else
			free(newCommand);
	}


	// insert rest of history
	i = N;
	while (i < lines) {
		lineLen = getNextLineLength(cmdFile);
		newCommand = (char *)malloc(sizeof(char) * (lineLen + 2));
		checkMemoryAllocation(newCommand);

		fgets(newCommand, lineLen + 2, cmdFile);
		newCommand[lineLen] = '\0';

		if (strcmp(newCommand, "\n") != 0 && strcmp(newCommand, "") != 0){
			insertCommandToEndCMDLst(newCommand, cmdLst);
			i++;
		}
		else
			free(newCommand);

	}

	rewind(cmdFile);
	fclose(cmdFile);
}

//get num of lines in file
int getTextFileLineNum(FILE *fp) {
	int res = 0; // functions result
	char ch; // temp char
	long int saver = ftell(fp); // save current location indicator
	fseek(fp, 0, SEEK_END);
	long int end = ftell(fp);

	fseek(fp, 0, SEEK_SET);
	while (ftell(fp) < end) {
		ch = fgetc(fp);
		if (ch == '\n')
			res++;
	}

	fseek(fp, saver, SEEK_SET);
	return res;
}
//get length of line Starting in the position of file indicator
int getNextLineLength(FILE *fp) {
	int res = 0; // functions result
	char ch; // temp char
	long int saver = ftell(fp);
	long int end = fileSize(fp);


	//traverse through file
	ch = fgetc(fp);

	while ((ftell(fp) < end) && (ch != '\n')) {
		ch = fgetc(fp);
		res++;
	}



	fseek(fp, saver, SEEK_SET);
	return res;
}


void openApartmentsFile(char *binFileName, APT_LIST *aptLst) {
	FILE *aptFile = fopen(binFileName, "ab+");
	checkOpenFile(aptFile);
	APARTMENT *apt;

	//check if empty
	if (isEmptyFile(aptFile)) {
		fclose(aptFile);
		return;
	}

	//insert apartments
	apt = getApartmentFromFile(aptFile);

	while (apt != NULL) {
		insertApartmentToEndList(apt, aptLst);
		apt = getApartmentFromFile(aptFile);
	}

	rewind(aptFile);
	fclose(aptFile);
}

BOOL isEmptyFile(FILE*fp) {
	BOOL res; // functions result
	long int saver; // saves current place
	long int start;
	long int end;
	if (feof(fp))
		return TRUE;
	saver = ftell(fp);

	fseek(fp, 0, SEEK_SET);
	start = ftell(fp);
	fseek(fp, 0, SEEK_END);
	end = ftell(fp);

	if (start == end) // file is empty
		res = TRUE;
	else
		res = FALSE;

	fseek(fp, saver, SEEK_SET);
	return res;
}