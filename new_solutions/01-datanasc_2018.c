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
#include<string.h>

// check that the dashes in a date string are in the correct position
// and only in the correct position
bool check_dashes(char date[]);

// Gets date_type[] date from user, as a string, and stores it into date[]
void get_date(char date_type[], char date[]);

// checks if date is valid
bool valid_date(char date[]);

// Verifies if a string is in the correct date format yyyy-mm-dd
bool verify_date(char date[]);

int main(void)
{
    char current_date[] = "0000-00-00";
    char target_date[] = "0000-00-00";

    printf("\n");
    get_date("current",current_date);
    get_date("target",target_date);

//dtarget = calculate difference in days between given date and reference
//dcurrent = calculate difference in days between today and reference

//calculate difference in days between check date and current date using dtarget and dcurrent

//calculate weekday for each date using dtarget and dcurrent

    printf("\nToday, %s, is a ____. Target date given was %s "
        "which was a _____, ___ days ago.\n",
        current_date, target_date);
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

bool valid_date(char date[])
{
    bool check = false;
    int year = ((int) (date[0] - '0'))*1000 + ((int) (date[1] - '0'))*100 + ((int) (date[2] - '0'))*10 + (int) (date[3] - '0');
    int month = ((int) (date[5] - '0'))*10 + (int) (date[6] - '0');
    int day = ((int) (date[8] - '0'))*10 + (int) (date[9] - '0');
    if(month >= 1 && month <= 12)
    {
        if(day > 0)
        {
            switch(month)
            {
                case 2:
                    if(day <= 28 || (day == 29 && year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)))
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
    if(strlen(date) == 10 && check_dashes(date)
        && valid_date(date))
    {
        check = true;
    }
    return check;
} /*end of verify_date */
