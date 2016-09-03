#include "Strings.h"
#include "CommandList.h"
#include "ApartmentList.h"
#include "Files.h"
#include "Date.h"

void getInput(APT_LIST *APTLst, CMD_LIST *CMDLst) {
	char *input; // input string to enter
	char *short_term_history[N]; // queue of short term history of commands
	int sthSize; // short term history size
	BOOL exit; // true iff program is finished

	initShortTermHistoryQueue(short_term_history, &sthSize);
	exit = FALSE;
	openCommandFile("CmdList.txt", short_term_history,&sthSize, CMDLst);
	openApartmentsFile("Apartments.bin", APTLst);

	printf("Please enter one of the following commands:\n");
	printf("add-apt, find-apt, buy-apt or delete-apt\nFor reconstruction commands, please enter:\n");
	printf("!!, !num, history, short_history or !^str1^str2\n");

	while (exit == FALSE) {

		//input
		printf(">> ");
		input = getInputString();

		//evaluate user input and commit proper application
		exit = evaluateUserInput(APTLst, input, short_term_history, &sthSize, CMDLst);

		free(input);
	}

	printf("Good Bye!\n");

	writeCmdListToTextFile(CMDLst, short_term_history);

	freeShortTermHistoryQueue(short_term_history, &sthSize);

	writeApartmentsToBinaryFile(APTLst);


}//getInput


char *getInputString() {
	char in; // next char in input
	int size; // resulted string size
	char *res; // resulted string
	int i;

	//init
	i = 0;
	size = INIT_SIZE;
	in = getchar();
	res = (char *)malloc(sizeof(char) * INIT_SIZE);
	checkMemoryAllocation(res);


	//insert to string while untill enter or EOF
	while ((in != '\n') && (in != EOF)) {
		if (i == size) {
			size *= 2;
			res = realloc(res, sizeof(char)*size);
			checkMemoryAllocation(res);
		}
		res[i] = in;

		in = getchar();
		i++;
	}

	//update size and res to actual size
	size = i;
	res = realloc(res, sizeof(char)*size + 1);
	checkMemoryAllocation(res);

	res[size] = '\0'; //insert NULL terminator

	return res;
}//getInputString

BOOL evaluateUserInput(APT_LIST *lst, char *input, char *short_term_history[N], int *sthSize, CMD_LIST *cmdLst) {
	BOOL res;// true iff program finished successfully
	char *tempInput; // tmp string to hold input (for strtok)
	char *currToken; // current token (command)
	char *queryInCommand; //query wanted in command
	
	if ((strstr(input, "!") == NULL) && (strstr(input, "history") == NULL) && (strstr(input, "exit") == NULL))
		insertCommandToHistory(input, short_term_history, sthSize, cmdLst);

	res = FALSE;
	tempInput = strdup(input);
	checkMemoryAllocation(tempInput);
	//get command
	currToken = strtok(tempInput, " ");

	//check for input validity
	if (currToken == NULL)
		return TRUE;

	//shorten string without command
	queryInCommand = input + strlen(currToken) + 1;

	//find-apt
	if (strcmp(currToken, "find-apt") == 0)
		findApartment(lst, queryInCommand);
	//add-apt
	else if (strcmp(currToken, "add-apt") == 0)
		addApartment(lst, queryInCommand);
	//buy-apt
	else if ((strcmp(currToken, "buy-apt") == 0))
		buyApartment(lst, queryInCommand);
	//delete-apt
	else if (strcmp(currToken, "delete-apt") == 0)
		deleteApartmentsInInterval(lst, queryInCommand);
	/*FOR TEST */
	else if (strcmp(currToken, "print") == 0)
		printAPTList(lst);

	else if (strcmp(currToken, "exit") == 0) {
		res = TRUE;
	}

	//history
	else if ((strstr(input, "!") != NULL) || (strstr(input, "history") != NULL)) {
		evaluateHistoryInput(lst, input, short_term_history, sthSize, cmdLst);
	}

	//free
	free(tempInput);

	return res;
}//evaluateUserInput


void evaluateHistoryInput(APT_LIST * lst, char *input, char *short_term_history[N], int *sthSize, CMD_LIST *cmdLst) {
	char *resCommand; // resulted command (after change)
	int commandNum; // requested command number
	char dummy;
	char *token; //current token
	char *str1, *str2; // strings to replace
	char *tempInput = strdup(input); // temporary input
	checkMemoryAllocation(tempInput);

	 //short_history
	if (strstr(input, "short_history") != NULL)
		printShortTermHistoryQueue(short_term_history, *sthSize, cmdLst->size);
	//short_history
	else if (strstr(input, "history") != NULL) {
		printCMDList(cmdLst);
		printShortTermHistoryQueue(short_term_history, *sthSize, cmdLst->size);
	}
	//last command
	else if (strstr(input, "!!") != NULL) {
		evaluateUserInput(lst, short_term_history[0], short_term_history, sthSize, cmdLst);
	}
	//command num
	else if (strstr(input, "!") != NULL) {
		token = strtok(tempInput, "^");
		//get start
		sscanf(token, "%c%d", &dummy, &commandNum);
		token = strtok(NULL, "^");

		//short version
		resCommand = getCommandFromStart(commandNum, short_term_history, *sthSize, cmdLst);
		//long version (!num^str^str)
		if (token != NULL) {
			str1 = strdup(token);
			checkMemoryAllocation(str1);
			token = strtok(NULL, "^");
			if (token != NULL) {
				str2 = strdup(token);
				checkMemoryAllocation(str2);
				resCommand = replaceWordInString(resCommand, str1, str2);
			}
			else {
				printf("Illegal input!\n");
				free(str1);
				return;
			}
			//free help strings
			free(str1);
			free(str2);
		}

		evaluateUserInput(lst, resCommand, short_term_history, sthSize, cmdLst);
	}
	free(tempInput);
}//evaluateHistoryInput

char* replaceWordInString(char *str, char *find, char *replaceTo) {
	char *res; // function's result
	char *pos; // position of find in str

	res = (char *)malloc(strlen(str) - strlen(find) + strlen(replaceTo) + 1);
	checkMemoryAllocation(res);

	//copy string to res
	strcpy(res, str);
	//find first apperance of find in str
	pos = strstr(res, find);

	//replace word and copy rest of string
	if (pos != '\0') {
		memmove(pos + strlen(replaceTo), pos + strlen(find), strlen(pos + strlen(find)) + 1);
		strncpy(pos, replaceTo, strlen(replaceTo));
	}

	return res;
}//replaceWordInString

void evaluateFindInput(char *input, SI *maxNumRooms, SI *minNumRooms, int *maxPrice, int *dayDiff, DATE *wantedDate, int *sortKind) {
	char *command; //current command 
	char *token; // token of strtok
	int dateInDigits; // date in digits 

	//init
	*maxNumRooms = NOT_DEFINED;
	*maxPrice = NOT_DEFINED;
	*minNumRooms = 0;
	*dayDiff = NOT_DEFINED;
	*sortKind = NO_SORT;
	
	char *tempInput = strdup(input);
	checkMemoryAllocation(tempInput);

	//get first token 
	token = strtok(tempInput, "-");
	command = (char *)malloc(sizeof(char) * strlen(tempInput) + 1);
	checkMemoryAllocation(command);

	//check command of each token
	while (token != NULL) {
		if (strstr(token, "MaxNumRooms") != NULL) {
			sscanf(token, "%s %hd", command, maxNumRooms);
		}
		else if (strstr(token, "MinNumRooms") != NULL) {
			sscanf(token, "%s %hd", command, minNumRooms);
		}
		else if (strstr(token, "MaxPrice") != NULL) {
			sscanf(token, "%s %d", command, maxPrice);
		}
		else if (strstr(token, "Date") != NULL) {
			sscanf(token, "%s %d", command, &dateInDigits);
			getDateFromDigits(dateInDigits,wantedDate);
		}
		else if (strstr(token, "Enter") != NULL) {
			sscanf(token, "%s %d", command, dayDiff);
		}
		else if (strcmp(token, "s") == 0) {
			*sortKind = LOWEST_FIRST;
		}
		else if (strcmp(token, "sr") == 0) {
			*sortKind = HIGHEST_FIRST;
		}
		else {
			printf("Unkown command!\n");
		}
		//get next token
		token = strtok(NULL, "-");

	}//while

	free(command);
	free(tempInput);
}//evaluateFindInput

void findApartment(APT_LIST * aptLst, char *input) {
	/*params for output*/
	SI maxNumRooms; // maximum number of rooms in apt.
	SI minNumRooms; // minumum number of rooms in apt.
	int maxPrice; // max price of apt.
	int dayDiff; // max difference between local time and insertion time
	int sortKind; // kind of sort wanted
	DATE *wantedDate; // date of wanted apt.
	APARTMENT ** output; // output array to print
	int outputSize; // size of output array

	wantedDate = (DATE *)malloc(sizeof(DATE));
	checkMemoryAllocation(wantedDate);
	
	//evaluate input and get sizes
	evaluateFindInput(input, &maxNumRooms, &minNumRooms, &maxPrice, &dayDiff, wantedDate, &sortKind);

	//get output array to print
	output = getApartmentsWithParams(aptLst, &outputSize, maxNumRooms, minNumRooms, maxPrice, dayDiff, wantedDate);

	// sort and print
	if (outputSize > 0) {
		if (sortKind == HIGHEST_FIRST) {
			mergeSort(output, outputSize, TRUE);
		}
		else if (sortKind == LOWEST_FIRST) {
			mergeSort(output, outputSize, FALSE);
		}

		printApartmentArray(output, outputSize);
	}
	else
		printf("No apratments found\n");

	//free
	free(output);
	free(wantedDate);

}//findApartment

