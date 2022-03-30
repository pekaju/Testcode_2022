/**
 * @file testules.c
 * @author Peeter Kaju (kajupeeter@gmail.com)
 * @brief This program will save 12 dates, which can only be non-holidays and non-weekends, in a file. 
 * The dates represent dates on which employers are paid. 12 additional dates are saved in the file
 * which will be 3 days before each payment day as a reminder.
 * @date 2022-03-29
 */

#include "header.h"

int main ( int argc, char *argv[] )
{
    if ( argc > 2 ) // in case too many integers are entered
    {
        perror ( "Liiga palju argumente\n" );
        exit ( 1 );
    } 
    else if ( argc <= 1 ) // in case no integers are entered
    {
        perror ( "Argumendid puuduvad, väljun\n" );
        exit ( 1 );
    }
    int y = atoi ( argv[1] ); // year passed into main function as an argument converted from a string into an integer
    if ( y < 1 )
    {
        perror ( "Aasta on liiga väike, palun valige aasta vahemikus 1 - 9999\n" );
        exit ( 1 );
    }
    else if ( y > 9999 )
    {
        perror ( "Aasta on liiga suur, palun valige aasta vahemikus 1 - 9999\n" );
        exit ( 1 );
    }
	
    int dates[MONTHS]; 
    int reminder[MONTHS];

    for ( int m = 0; m < ( MONTHS ); m++ ) // loop until 12 months is hit
    {
        dates[m] = dayOfPayment ( m, y ); // day of payment will be saved into an array
        reminder[m] = ( dates[m] - 3 ); // day of reminder will be in a separate array, 3 days before payment date
    }
    fileWriter ( dates, reminder, y ); // call the function to write data into a file
    return 0;
}
/**
 * @brief the function will call other functions, based on the month ( april has to be separate because of Easter )
 * @param m, integer, represents the month counter from main function ( 1 - 12 )
 * @param y, integer, represents the year inserted from cmd
 * @return int, returns from one of two functions, one for April, one for other months.
 */
int dayOfPayment ( int m, int y )
{                              
    int d = 10; 

    // will check which day of the week ( 1 - 7 ) is the 10th of current month, 
    // of the inserted year, returned as an integer      
    int weekDay = findWeekDay ( d, m, y );  
    
    // if the current month is April, it will run the function aprilDate and return an integer 
    // that represents a date
    if ( m == 4 )
    {  
        return aprilDate ( y, weekDay );
    }  
    
    // if the current month is not April, call the function otherDate and return an integer
    // that represents a date
    else 
    {
        return otherDate ( weekDay );
    }
}
/**
 * @brief this function will find the day on which employers will be paid if the month is April.
 * @param Y, int, represents year in used date ( 1 - 9999 )
 * @param weekDay, int, represents the day of week that currently used 10th date is.
 * @return int, 4 different return cases, depends on the date of big friday
 */
int aprilDate ( int Y, int weekDay )
{
    // finds the date of big friday on the year inserted by user. Saved as an integer.
    int bigFri = findBigFriday ( Y );
    
    // if big friday is 9th of April, employers can't be paid then
    if ( bigFri == 9 )
    {
	// returns the day ( 10 - 2 = 8th of April ) on which employers will be paid, 
        return DAY - 2;
    }
    
    // employers can't be paid on 8th
    else if ( bigFri == 8 )
    {
	// so they will be paid on 7th
        return DAY - 3;
    }
    
    // employers can't be paid on 10th
    else if ( bigFri == 10 )
    {
	// so they will be paid on 9th
        return DAY - 1;
    }
    
    // if big friday doesn't interfere with payment day, proceed with normal action
    else
    {
	// return a date on which employers will be paid
        return otherDate ( weekDay );
    } 
}
/**
 * @brief this function will convert a date into a weekday ( monday, tuesday, wednesday etc. ) 
 * @param d, integer, represents a day ( 1 - 31 )
 * @param m, integer, represents a month ( 1 - 12 )
 * @param y, integer, represents a year ( 1 - 9999 )
 * @return int, day of the week ( 1 - 7 )
 */
int findWeekDay ( int d, int m, int y )
{
    // this algorithm will convert a date, where day, month and year are separate integers, 
    // into a day of week
    int weekDay = ( ( d += m < 3 ? y-- : y - 2, 23 * m / 9 + d + 4 + y / 4 - y / 100 + y / 400 ) % 7 );  
    return weekDay;
}
/**
 * @brief this function will return a day on which employers will be paid, avoids returning
 * dates that fall on weekends
 * @param weekDay, int, day of week that searched date is.
 * @return int, day on which employers will be paid
 */
int otherDate ( int weekDay )
{
    // checks if weekday of given date is on saturday
    if ( weekDay == SATURDAY )
    {
	// if true, return day minus one, so friday
        return ( DAY - 1 );
    } 
    
    // checks if weekday of given date us sunday
    else if ( weekDay == SUNDAY )
    {
	// if true, return day minus two, so friday
        return ( DAY - 2 );
    }
    
    // if the date doesn't fall on weekends, return the date itself
    else 
    {
        return DAY;
    }
}
/**
 * @brief this function will find the date of big friday if it is in April
 * @param Y, int, the given year
 * @return int, day of big friday 
 */
int findBigFriday ( int Y )
{
    int A, B, C, P, Q,
		M, N, D, E;
    
    // this algorithm will calculate the day on which big friday is in given year,
    // years used can vary from 1 - 9999
    A = Y % 19;
	B = Y % 4;
	C = Y % 7;
	P = floor ( Y / 100 );
	Q = floor ( ( 13 + 8 * P ) / 25 );
	M = ( 15 - Q + P - P / 4 ) % 30;
	N = ( 4 + P - P / 4 ) % 7;
	D = ( 19 * A + M ) % 30;
	E = ( 2 * B + 4 * C + 6 * D + N ) % 7;

    // now we know when easter is
    int easter = ( 22 + D + E - 31 );
    // we can calculate when big friday will be
    int bigFriday = easter - 2;
    
    // returns day of big friday as an integer
    return bigFriday;
}
/**
 * @brief this function will write the dates returned to main function into a csv file.
 * @param dates, integer array, this array of 12 integers includes all 12 returned dates on which
 * employers will be paid
 * @param reminder, integer array, this array of 12 integers includes all 12 dates 3 days before payment day
 */
void fileWriter ( int dates[12], int reminder[12], int y )
{
    // creating a file pointer called fPtr and opening or creating a csv file called 2022.
    FILE * fPtr = fopen ( "2022.csv", "w" );
    
    // if file pointer didn't get a file to point to, exit with an error message
    if ( fPtr == NULL )
    {
        perror ( "Fail ei avane, valjun" );
        exit ( 1 );
    }
   
    // print 2 column headers into the csv file 
    fprintf ( fPtr, "%s, %s\n", "meeldetuletus", "palgamaksmine" );
	
    // create a loop for 12 cycles, counter m.
    for ( int m = 0; m < MONTHS; m++ )
    {
	 // print the 12 dates into two columns, one for reminder date and one for payment date
         fprintf ( fPtr, "%d.%d.%d, %d.%d.%d\n", reminder[m], ( m + 1 ), y, dates[m], ( m + 1 ), y );
    }
    // close the file pointed to by fPtr.
    fclose ( fPtr );
}
