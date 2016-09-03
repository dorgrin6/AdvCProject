#define _CRT_NONSTDC_NO_DEPRECATE
#include "CommandList.h"
#include "GeneralDefs.h"
#include "Files.h"

void makeEmptyCMDList(CMD_LIST *lst)
{
	lst->head = NULL;
	lst->tail = NULL;
	lst->size = 0;
}//makeEmptyCMDList

BOOL isEmptyCMDList(CMD_LIST *lst) {
	if ( lst->head == NULL)
		return TRUE;
	else
		return FALSE;
}//isEmptyCMDList

void insertCommandToHistory(char *command, char *short_term_history[N], int *sthSize, CMD_LIST *cmdLst) {
	char *toInsert; //string to insert to cmdLst (if needed) 
	
	toInsert = pushStringToQueue(command, short_term_history, sthSize);

	//short_term_histort is full
	if (toInsert != NULL) {
		insertCommandToEndCMDLst(toInsert, cmdLst);
	}


}//insertCommand

char *pushStringToQueue(char *elem, char *queue[N], int *size) {
	int i;
	char *res; // function's result

	res = NULL;

	//array is full
	if (*size == N) {
		//save last element
		res = (queue[(*size) - 1]);
		//move elements in queue
		for (i = (*size)-1; i > 0; i--) {
			queue[i] = queue[i - 1];
		}
	}
	else {
		//move elements in queue
		for (i = (*size); i > 0; i--) {
			queue[i] = queue[i - 1];
		}
		//increase size
		(*size)++;
	}


	//insert elem
	queue[0] = strdup(elem);

	return res;

}//pushStringToQueue

void printShortTermHistoryQueue(char *short_term_history[N], int sthSize, int alreadyPrinted) {
	int i;

	//print array
	for (i = sthSize-1; i >= 0; i--) {
		printf("%d: ", 1+alreadyPrinted++);
		puts(short_term_history[i]);
	}
}//printShortTermHistoryQueue

void insertCommandToEndCMDLst(char *command, CMD_LIST *cmdLst) {
	CMD_NODE *newTail; // node to insert


	newTail = createNewCMDLstNode(command, NULL, NULL);

	//insert node
	insertCMDNodeToEndList(cmdLst, newTail);
}//insertToCommandList

CMD_NODE *createNewCMDLstNode(char *command, CMD_NODE *next, CMD_NODE * prev) {
	CMD_NODE* res;
	//create new node
	res = (CMD_NODE *)malloc(sizeof(CMD_NODE));
	checkMemoryAllocation(res);

	//insert given command
	res->next = next;
	res->prev = prev;
	res->data = command;

	return res;
}//createNewCMDLstNode


void initShortTermHistoryQueue(char **short_term_history,int *sthSize) {
	int i;

	for (i = 0; i < N; i++) {
		short_term_history[i] = NULL;
	}

	*sthSize = 0;
}//freeShortTermCMDArr

void freeShortTermHistoryQueue(char *queue[N], int *sthSize) {

	int i;
	for (i = 0; i < *sthSize; i++)
		free(queue[i]);
		
	*sthSize = 0;
}//freeShortTermHistoryQueue

void insertCMDNodeToEndList(CMD_LIST *lst, CMD_NODE * tail)
{
	if (isEmptyCMDList(lst) == TRUE) {
		tail->next = tail->prev = NULL;
		lst->head = lst->tail = tail;
	}
	else {
		tail->next = NULL;
		tail->prev = lst->tail;
		lst->tail->next = tail;
		lst->tail = tail;
	}

	//increase size
	lst->size++;
}//insertCMDNodeToEndList

int printCMDList(CMD_LIST *lst) {
	int res; // function's return value
	int i = 0;
	CMD_NODE *curr; // current node in traverse

	curr = lst->head;

	while (curr != NULL) {
		printf("%d: ", i+1);
		puts(curr->data);
		curr = curr->next;
		i++;
	}

	res = i;
	return res;
}//printAPTList


char *getCommandFromStart(int commandNumber, char *short_term_history[N], int sthSize, CMD_LIST *cmdLst) {
	char *res; // functions return value
	CMD_NODE * curr; // current node in traverse
	int currCommand = 1;
	int i;
	BOOL found = FALSE;
	res = NULL;

	curr = cmdLst->tail;

	//traverse command list
	while ((curr != NULL) && (found == FALSE)) {
		if (currCommand == commandNumber) {
			res = curr->data;
			found = TRUE;
		}
		currCommand++;
		curr = curr->prev;
	}

	//travese short history
	for (i = N - 1; (i >= 0) && (found == FALSE); i--) {
		if (short_term_history[i] != NULL) {
			if (currCommand == commandNumber) {
				res = short_term_history[i];
				found = TRUE;
			}
			currCommand++;
		}
	}
	return res;
}//getCommandFromStart

void freeCMDList(CMD_LIST *cmdLST) {
	CMD_NODE *curr; // current node in traverse 
	CMD_NODE *saver; // saves next node

	curr = cmdLST->head;

	while (curr != NULL) {
		saver = curr->next;
		deleteCMDNodeFormList(curr, cmdLST);
		curr = saver;
	}

	free(cmdLST);
}//freeAPTList

void deleteCMDNodeFormList(CMD_NODE *toDelete, CMD_LIST *cmdLST) {
	if (isEmptyCMDList(cmdLST) == TRUE)
		return;

	//node is head
	if (toDelete == cmdLST->head) {
		cmdLST->head = toDelete->next;
		//change head prev only if not empty
		if (isEmptyCMDList(cmdLST) == FALSE)
			cmdLST->head->prev = NULL;
	}
	//node is tail
	else if (toDelete == cmdLST->tail) {
		cmdLST->tail = toDelete->prev;
		//change rail next only if not empty
		if (isEmptyCMDList(cmdLST) == FALSE)
			cmdLST->tail->next = NULL;
	}
	//node is in middle of list
	else {
		toDelete->prev->next = toDelete->next;
		toDelete->next->prev = toDelete->prev;
	}
	
	//free data
	free(toDelete->data);

	//free node
	free(toDelete);
}//deleteCMDNodeFormList
