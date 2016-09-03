#ifndef __COMMAND_LIST_H
#define __COMMAND_LIST_H
#include "GeneralDefs.h"
typedef struct commandListNode {
	struct commandListNode *next;
	struct commandListNode *prev;
	char *data; // command of Node

}CMD_NODE;

typedef struct commandList {
	CMD_NODE *head;
	CMD_NODE *tail;
	int size;

} CMD_LIST;


/*makeEmptyCMDList:
	Recieves and initiates a commandList.

*/
void makeEmptyCMDList(CMD_LIST *lst);


/*createNewCMDLstNode:
	Recieves a command and return a node updated with the nodes in command.

*/
CMD_NODE *createNewCMDLstNode(char *command, CMD_NODE *next, CMD_NODE * prev);

/*pushStringToQueue: 
	recieves an element and pushes it into queue of size. (max size N)
*/
char *pushStringToQueue(char *elem, char *queue[N], int *size);


/*insertCommandToHistory: 
	Recieves a command and insert it into history (CMD_LIST or short_term_history).
*/
void insertCommandToHistory(char *command, char *short_term_history[N], int *sthSize, CMD_LIST *cmdLst);

/*insertCommandToEndCMDLst: 
	recieves an element and pushes it into queue of size. (max size N)
*/
void insertCommandToEndCMDLst(char *command, CMD_LIST *cmdLst);

/*pushStringToQueue: 
	recieves an element and pushes it into queue of size. (max size N)
*/
void insertCMDNodeToEndList(CMD_LIST *lst, CMD_NODE * tail);

/*printShortTermHistoryQueue:
	recieves a short_term_history queue, its size and how many elements 
		were already printed and prints the short_term_history.

*/
void printShortTermHistoryQueue(char *short_term_history[N], int sthSize, int alreadyPrinted);


/*printCMDList:
	Prints CMD_LIST.

*/
int printCMDList(CMD_LIST *lst);

/*getCommandFromStart:
	recieves the wanted command number, array of short_term_history, and the CMD_LIST.
	Returns the command of requested number.

*/
char *getCommandFromStart(int commandNumber, char *short_term_history[N], int sthSize, CMD_LIST *cmdLst);

/*freeCMDList:
	recieves CMD_LIST and frees it.
*/
void freeCMDList(CMD_LIST *cmdLST);
/*freeCMDList:
	recieves a CMD_NODE and frees it.
*/
void deleteCMDNodeFormList(CMD_NODE *toDelete, CMD_LIST *cmdLST);

/*initShortTermHistoryList:
Intializes short term history array of size N.
*/
void initShortTermHistoryQueue(char **short_term_history, int *sthSize);


/*freeShortTermHistoryQueue:
	recieves a short_term_history queue and frees it.
*/
void freeShortTermHistoryQueue(char *queue[N], int *sthSize);
#endif