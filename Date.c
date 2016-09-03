#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#include "Date.h"
#include "GeneralDefs.h"
#include "Files.h"

void setCurrentDate(DATE * date) {
	//create time
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	//set date
	date->day = (SI)tm.tm_mday;
	date->month = (SI)(tm.tm_mon + 1);
	date->year = (SI)(tm.tm_year + 1900);
}//setCurrentDate

DATE *createNewDate(SI day, SI month, SI year) {
	DATE *res; // result of function

	res = (DATE*)malloc(sizeof(DATE));
	checkMemoryAllocation(res);

	res->day = day;
	res->month = month;
	res->year = year;

	return res;
}//createNewDATE

void getDateFromDigits(int dateInDigits,DATE *date) {

	date->year = (SI)((dateInDigits % 10000));
	dateInDigits /= 10000;
	date->month = (SI)(dateInDigits % 100);
	dateInDigits /= 100;
	date->day  = (SI)(dateInDigits);

}//getDateFromDigits

BOOL isInDateInterval(unsigned int interval, DATE *date) {
	BOOL res;//result of function
	time_t now; // local time
	struct tm prev; // date given
	double daysPast; // difference between now and prev
					 //get current time
	time(&now);
	prev = *localtime(&now);

	//init previous day to given date
	prev.tm_mday = date->day;
	prev.tm_mon = date->month;
	prev.tm_year = date->year;

	//divide by number of seconds in day
	daysPast = (difftime(now, mktime(&prev)) / SECONDS_IN_DAY);

	if (daysPast <= interval)
		res = TRUE;
	else
		res = FALSE;

	return res;
}//isInDateInterval

double getDaysDifference(DATE * d1, DATE *d2) {
	double res; // functions result
	struct tm *startDate; // start date
	struct tm *endDate; // end date
	time_t startTime; // get start time
	time_t endTime; // get end time

	//reset dates
	startDate = convertDateStruct(d1);
	endDate = convertDateStruct(d2);

	//set time of start and end
	startTime = mktime(startDate);
	endTime = mktime(endDate);

	res = difftime(endTime, startTime) / (SECONDS_IN_DAY);

	free(startDate);
	free(endDate);

	return res;
}//getDaysDifference


struct tm *convertDateStruct(DATE * date) {
	struct tm *newDate = (struct tm *) malloc(sizeof(struct tm));
	newDate->tm_hour = 0;  newDate->tm_min = 0;  newDate->tm_sec = 0;
	newDate->tm_mon = date->month; newDate->tm_mday = date->month; newDate->tm_year = date->year + 100 - MILLENNIUM;
	return newDate;
}//

BOOL isEqualDate(DATE *date1, DATE *date2) {
	BOOL res;
	if (date1 == NULL || date2 == NULL)
		res = FALSE;
	else if ((date1->day == date2->day) && (date1->month == date2->month)
		&& (date1->year == date2->year))
		res = TRUE;
	else
		res = FALSE;
	return res;
}//isEqualDate


