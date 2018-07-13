/***************************************************************************
 ***                                                                     ***
 ***   Exercise #1 from MAC-0115 discipline, 1998                        ***
 ***   Originally proposed by professor Dr. Routo Terada                 ***
 ***                                                                     ***
 ***************************************************************************/

/*Goal is to receive current date and another date in the past, and to return:
  a. what day of the week was the past date given
  b. how many days have passed from that past date until today
  Using time.h is forbidden.*/

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// ATTENTION: changing BASELINE_YEAR will invalidate order of DAY_NAMES
int BASELINE_YEAR = 2000;
// ATTENTION: changing BASELINE_YEAR will invalidate order of DAY_NAMES
char DAY_NAMES[7][10] = {"Saturday","Sunday","Monday","Tuesday",
                        "Wednesday","Thursday","Friday"};

// check that the dashes in a date string are in the correct position
// and only in the correct position
bool check_dashes(char date[]);

// receives a date in proper format and returns difference in days from
// Jan 1st of BASELINE_YEAR to given date. Result is positive if date is after
// that baseline, negative if before
int difference_to_baseline(char date[], char dow[]);

// next three functions extract parts of a valid date
int extract_day(char date[]);
int extract_month(char date[]);
int extract_year(char date[]);

// Gets date_type[] date from user, as a string, and stores it into date[]
void get_date(char date_type[], char date[]);

// Checks if a year is a leap year
bool is_leap_year(int year);

// checks if date is valid
bool valid_date(char date[]);

// Verifies if a string is in the correct date format yyyy-mm-dd
bool verify_date(char date[]);

int main(void)
{
    int dcurrent, dtarget;
    char current_date[] = "0000-00-00";
    char target_date[] = "0000-00-00";
    char dow_current[10], dow_target[10];

    printf("\n");
    get_date("current",current_date);
    get_date("target",target_date);

    dcurrent = difference_to_y2k(current_date,dow_current);
    dtarget = difference_to_y2k(target_date,dow_target);

    printf("\nToday, %s, is a %s. Target date given was %s "
        "which was a %s, %d days ago.\n",
        current_date, dow_current, target_date, dow_target,
        (dcurrent - dtarget));

    return 0;
}

bool check_dashes(char date[])
{
    int i = 0, l = strlen(date);
    bool check = true;
    while(check && i < l)
    {
        switch(i)
        {
            case 4:
            case 7:
                if(date[i] != '-'){check = false;}
                break;
            default:
                if(date[i] < '0' || date[i] > '9'){check = false;}
        }
        i++;
    }
    return check;
} // end of check_dashes

int difference_to_baseline(char date[], char dow[])
{
    long diff = 0;
    int year = extract_year(date);
    int month = extract_month(date);
    int day = extract_day(date);
    int days_before_month[] = {0,31,59,90,130,151,181,212,243,273,304,334};

    // should -1 from the day, but should +1 for 2000 being leap year
    diff += (year - BASELINE_YEAR) * 365.25
        +days_before_month[month-1]
        +day;

    if(year < BASELINE_YEAR)
    {
        // Account for the baseline date...
        diff--;
        // ... and count back the leap day of target year
        if(is_leap_year(year) && month > 2){diff++;}
    }

    if(diff >=0) {strcpy(dow,DAY_NAMES[diff % 7]);}
    else {strcpy(dow,DAY_NAMES[7 - (abs(diff) % 7)]);}

    return diff;
}

int extract_day(char date[])
{
    int day = ((int) (date[8] - '0'))*10 + (int) (date[9] - '0');
    return day;
} // end of extract_day

int extract_month(char date[])
{
    int month = ((int) (date[5] - '0'))*10 + (int) (date[6] - '0');
    return month;
} // end of extract_month

int extract_year(char date[])
{
    int year = ((int) (date[0] - '0'))*1000
        + ((int) (date[1] - '0'))*100
        + ((int) (date[2] - '0'))*10
        + (int) (date[3] - '0');
    return year;
} // end of extract_year

void get_date(char date_type[], char date[])
{
    bool missing_date = true;
    while(missing_date)
    {
        printf("Please give the %s date (yyyy-mm-dd): ",date_type);
        scanf("%s",date);
        if(verify_date(date))
        {
            missing_date = false;
        }
        else
        {
            printf("\nInvalid date, please mind the input format "
                "and try again.\n\n");
        }
    }
} /*end of get_date */

bool is_leap_year(int year)
{
    bool check = false;
    if(year % 4 == 0)
    {
        if(year % 100 != 0 || year % 400 == 0)
        {check = true;}
    }
    return check;
} // end of is_leap_year

bool valid_date(char date[])
{
    bool check = false;
    int year = extract_year(date);
    int month = extract_month(date);
    int day = extract_day(date);
    if(month >= 1 && month <= 12)
    {
        if(day > 0)
        {
            switch(month)
            {
                case 2:
                    if(day <= 28 || (day == 29 && is_leap_year(year)) )
                    {check = true;}
                    break;
                case 4:
                case 6:
                case 9:
                case 11:
                    if(day <= 30){check = true;}
                    break;
                default:
                    if(day <= 31){check = true;}
            }
        }
    }
    return check;
} // end of valid_date

bool verify_date(char date[])
{
    bool check = false;
    if(strlen(date) == 10 && check_dashes(date) && valid_date(date))
    {
        check = true;
    }
    return check;
} /*end of verify_date */
