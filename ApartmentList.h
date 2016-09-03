#ifndef __APARTMENT_LIST_H
#define __APARTMENT_LIST_H
#include "Date.h"

//Apartment
typedef struct apartment {
	SI code;
	char* address;
	int price;
	SI amountOfRooms;

	//dates
	struct date *entranceDate; //tenets entrance to apt
	struct date *insertionDate;// apartment insertion to structure 
}APARTMENT;

/*List to store apartments */
//node of list
typedef struct apartmentNode {
	struct apartmentNode * next;

	APARTMENT * data;
} APT_NODE;


//list
typedef struct apartmentList {
	APT_NODE *head;
	APT_NODE *tail;
	int numOfAptartments; // current apartment num

} APT_LIST; 

/*addApartment:
	Recieves an apartmentList and input string and ads apartment in input to APT_LIST.
	Assumptions: input string is legal and in the format:
	"APT_NAME" <APT_PRICE> <NUM_OF_ROOMS> <DATE_OF_ENTRANCE>
*/
void addApartment(APT_LIST * aptLst, char *input);

/*insertApartmentToEndList:
	recieves an APARTMENT pointer and an APT_LST to insert, and inserts it as tail.
	*uses insertAPTNodeToEndList
*/
void insertApartmentToEndList(APARTMENT * apt, APT_LIST * aptLST);

/*insertAPTNodeToEndList:
	recieves an APT_LIST and an APT_NODE to insert, and inserts it as tail.
*/
void insertAPTNodeToEndList(APT_LIST *lst, APT_NODE * tail);

/*makeEmptyAPTList:
	recieves an APT_LST lst and makes it an empty list.
*/
void makeEmptyAPTList(APT_LIST *lst);

/*isEmptyAPTList:
	Returns TRUE iff lst is empty list.
*/
BOOL isEmptyAPTList(APT_LIST *lst);

/*getApartmentsWithParams:
	Recieves an APARTMENT parmaeters and returns an array of pointers 
		to all apartments fitting in APT_LIST.
	Input: max/minNumRooms - max/min amount of rooms wanted.
			maxPrice - max price wanted.
			dayDiff - maximum days past since insertion.
			wantedDate - apartment inserted in date.
	Output: APARTMENT pointer array of wanted apartments and size as output param.
	Assumptions: all input paramaters are in correct format.
*/
APARTMENT **getApartmentsWithParams(APT_LIST *aptLst, int *size, SI maxNumRooms, SI minNumRooms, int maxPrice, int dayDiff, DATE *wantedDate);


/*buyApartment:
	removes apartment in input from aptLst.
	Assumptions: input contains apartment.
*/
void buyApartment(APT_LIST *aptLst, char* input);


/*createNewAptNode:
	Recieves an apartment and returns an apartmentNode pointer.
	Assumptions: apartment isnt NULL.
*/
APT_NODE *createNewAptNode(APARTMENT * apt);

/*find*/

/*findApartment:
	Recieves an apartmentList and user input string
	and prints the apartments in request of user.
	Assumptions: input string is in correct format.
*/
void findApartment(APT_LIST * aptLst, char *input);

/*getAPTNodeWithCode:
	Recieves an apartmentList and apartmentCode
	and returns an APT_NODE with the same code if exists.
	otherwise returns NULL.
*/
APT_NODE *getAPTNodeWithCode(int aptCode, APT_LIST *aptLst);


/*printAPTList:
	prints apartmentList.
*/
void printAPTList(APT_LIST *lst);

/*printApartmentArray:
	prints apartment pointer array.
*/
void printApartmentArray(APARTMENT ** arr, int size);
/*Delete*/

/*deleteApartmentsInInterval:
	Deletes all the apartments in interval contained in input string.
	Assumption: input contains a legal interval.
*/
void deleteApartmentsInInterval(APT_LIST *aptLst, char *input);

/*freeAPTList:
	Frees apartment list.
*/
void freeAPTList(APT_LIST *aptLST);

/*deleteAPTNodeFormList:
	Deletes apartment from apartment List.
*/
void deleteAPTNodeFormList(APT_NODE *toDelete, APT_LIST *aptLST);


/*Sort*/

/*mergeSort:
	Sorts apartment array arr of size using mergeSort.
	If highestFirst is TRUE function sort form highest to lowest price.
	Otherwise, function will sort from lowest to highest price.
*/
void mergeSort(APARTMENT **arr, int size, BOOL highestFirst);

/*sortedMerge:
	Combines SORTED apartment arrays A of sizeA, B of sizeB into pTemp as output paramater.
	Assumptions: A and B are sorted (pointer) apartment arrays.
*/
void sortedMerge(APARTMENT **A, int sizeA, APARTMENT **B, int sizeB,BOOL highestFirst, APARTMENT ***pTemp);


/*createNewApartment:
	Recieves apartment paramaters:
	address, price, entranceDate, code.
	Returns an APARTMENT pointer.
	Assumptions: all input is legal.
*/
APARTMENT *createNewApartment(char* address, int price, SI amountOfRooms, DATE *entranceDate, int apartmentCode);


/*Print*/
/*printApartment:
	prints apartment list.
*/
void printApartment(APARTMENT *apt);


#endif