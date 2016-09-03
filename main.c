/*
	main.c

	This project handels an apartment database and enables various application with database.

	Dor Grinshpan & 
	Nikita Malkin
	19 June 2016
*/
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#include "GeneralDefs.h"
#include "Date.h"
#include "ApartmentList.h"
#include "CommandList.h"
#include "Files.h"
#include "Strings.h"


void main() {
	//allocate command list and apt list
	APT_LIST *aptLst = (APT_LIST *)malloc(sizeof(APT_LIST));
	checkMemoryAllocation(aptLst);
	CMD_LIST *cmdLst = (CMD_LIST *)malloc(sizeof(CMD_LIST));
	checkMemoryAllocation(cmdLst);

	makeEmptyAPTList(aptLst);
	makeEmptyCMDList(cmdLst);

	//base function
	getInput(aptLst,cmdLst);
	
	//free
	freeAPTList(aptLst);
	freeCMDList(cmdLst);
}//main
