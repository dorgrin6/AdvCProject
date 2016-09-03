#ifndef __STRINGS_H
#define __STRINGS_H

#include "GeneralDefs.h"
#include "ApartmentList.h"
#include "CommandList.h"

/* getInput:
	Recieves an apartment list and commits a series of users commands on it.
	Assumption: input length is less than SIZE.
*/
void getInput(APT_LIST *aptLst, CMD_LIST *cmdLst);


/* evaluateUserInput:
	Recieves a command currCommand and the query in the commnad (add-apt,find-apt,etc.)
		and commits the proper action.
	Returns TRUE iff input is valid and program exited successfully.
	Assumption: currCommand and query are legal.
*/
BOOL evaluateUserInput(APT_LIST *lst, char *input, char *short_term_history[N], int *sthSize, CMD_LIST *cmdLst);

//apartment
/*evaluateFindInput:
	Recieves search apt. parameters and updates them according to input.
	Assumptions: input string is in correct format.
*/
void evaluateFindInput(char *input, SI *maxNumRooms, SI *minNumRooms, int *maxPrice, int *dayDiff, DATE *wantedDate, int *sortKind);

/*evaluateHistoryInput:
	Recieves an apartment list, an input (history string), short_term_history array, 
		its size and the command list.
	Inserts and evaluates the input.
	Assumption: input is a valid history string. 
*/
void evaluateHistoryInput(APT_LIST * lst, char *input, char *short_term_history[N], int *sthSize, CMD_LIST *cmdLst);

/*	replaceWordInString:
	Recieves a string str, a word to find and a word to replace to.
	And replaces the word find to the word in replaceTo.
	Assumption: string is not NULL, find is in string.
*/
char* replaceWordInString(char *str, char *find, char *replaceTo);

/*
	Returns input string from user.
*/
char *getInputString();

#endif
