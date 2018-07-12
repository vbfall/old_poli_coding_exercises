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

char* get_date(char date_type[]);

bool verify_date(char date[]);

int main(void)
{
    char* current_date = "0000-00-00";
    char* target_date = "0000-00-00";

    // both are storing the same value (the one supplied later).
    // Something to do with the definition inside the function, but how to get around it?
    printf("\n");
    current_date = get_date("current");
    target_date = get_date("target");

//dcheck = calculate difference in days between given date and reference
//dcurrent = calculate difference in days between today and reference

//calculate difference in days between check date and current date using dcheck and dcurrent

//calculate weekday for each date using dcheck and dcurrent

    printf("\nToday, %s, is a ____. Target date given was %s which was a _____, ___ days ago.\n",
        current_date, target_date);
}

char* get_date(char date_type[])
{
    bool missing_date = true;
    static char full_date[] = "0000-00-00";
    while(missing_date)
    {
        printf("Please give %s date (yyyy-mm-dd): ",date_type);
        scanf("%s",full_date);
        if(verify_date(full_date))
        {
            missing_date = false;
        }
        else
        {
            printf("\nInvalid date, please mind the input format and try again.\n\n");
        }
    }
    return full_date;
} /*end of get_date */

bool verify_date(char date[])
{
    bool check = false;
    int l = strlen(date);
    if(l == 10 /*and dashes in the right positions*/ /*and all others are digits*/)
    {
        check = true;
    }
    return check;
} /*end of verify_date */
