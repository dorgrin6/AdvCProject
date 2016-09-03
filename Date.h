#ifndef __Date_H
#define __Date_H
#include <time.h>
#include "GeneralDefs.h"

//Date
typedef struct date
{
	SI day;
	SI month;
	SI year;
} DATE;

/*createNewDate:
	Recieves date paramaters:
	day, month and year.
	returns a DATE with given paramaters.
	Assumptions: given paramaters are legal:
	day[0..31],month[1..12]
*/
DATE* createNewDate(SI day, SI month, SI year);

/*setCurrentDate:
	Recieves and changes date into current time.
*/
void setCurrentDate(DATE* date);

/*isEqualDate:
	Returns true iff dates are equal.
*/
BOOL isEqualDate(DATE* date1, DATE* date2);

/*getDateFromDigits:
	recieves a date in format ddmmyyyy and converts it to DATE.
	Assumptions: given paramaters are legal:
	day[0..31],month[1..12]
*/
void getDateFromDigits(int dateInDigits, DATE* date);

/*isInDateInterval:
	recieves a date interval (positive) and returns TRUE iff diffrence between date and
	local time is in interval.
	Assumptions: interval is positive int.
*/
BOOL isInDateInterval(unsigned int interval, DATE* date);

/*getDaysDifference:
	returns the difference in days between 2 dates.
*/
double getDaysDifference(DATE* d1, DATE* d2);

/*converts date to date struct*/
struct tm* convertDateStruct(DATE* date);
#endif

