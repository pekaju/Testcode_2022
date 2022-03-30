/**
 * @file testules.c
 * @author Peeter Kaju (kajupeeter@gmail.com)
 * @brief This program will save 12 dates, which can only be non-holidays and non-weekends, in a file. 
 * The dates represent dates on which employers are paid. 12 additional dates are saved in the file
 * which will be 3 days before each payment day as a reminder.
 * @date 2022-03-29
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// number of months in a year is 12 and 10 is the date when employers are paid.
#define MONTHS 12
#define DAY 10

#define SUNDAY 7
#define SATURDAY 6

int dayOfPayment ( int, int );
int findWeekDay ( int, int, int );
int aprilDate ( int, int );
int otherDate ( int );
int findBigFriday ( int );
void fileWriter ( int[], int[], int );

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
 * @brief 
 * 
 * @param m 
 * @param y 
 * @return int 
 */
int dayOfPayment ( int m, int y )
{                              
    int d = 10; 

    // leian, mis päev on kümnes kuupäev antud kuul       
    int weekDay = findWeekDay ( d, m, y );  
    
    if ( m == 4 )
    {  
        return aprilDate ( y, weekDay );
    }  
    else 
    {
        return otherDate ( weekDay );
    }
}
int aprilDate ( int Y, int weekDay )
{
    int bigFri = findBigFriday ( Y );
    
    if ( bigFri == 9 )
    {
        return DAY - 2;
    }
    else if ( bigFri == 8 )
    {
        return DAY - 3;
    }
    else if ( bigFri == 10 )
    {
        return DAY - 1;
    }
    else
    {
        return otherDate ( weekDay );
    } 
}
int findWeekDay ( int d, int m, int y )
{
    int weekDay = ( ( d += m < 3 ? y-- : y - 2, 23 * m / 9 + d + 4 + y / 4 - y / 100 + y / 400 ) % 7 );  
    return weekDay;
}
int otherDate ( int weekDay )
{
    if ( weekDay == SATURDAY )
    {
        return ( DAY - 1 );
    } 
    else if ( weekDay == SUNDAY )
    {
        return ( DAY - 2 );
    }
    else 
    {
        return DAY;
    }
}
int findBigFriday ( int Y )
{
    int A, B, C, P, Q,
		M, N, D, E;
	
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
    
    return bigFriday;
}
void fileWriter ( int dates[12], int reminder[12], int y )
{
    FILE * fPtr = fopen ( "2022.csv", "w" );
    if ( fPtr == NULL )
    {
        perror ( "Fail ei avane, valjun" );
        exit ( 1 );
    }
    fprintf ( fPtr, "%s, %s\n", "meeldetuletus", "palgamaksmine" );
    for ( int m = 0; m < MONTHS; m++ )
    {
         fprintf ( fPtr, "%d.%d.%d, %d.%d.%d\n", reminder[m], ( m + 1 ), y, dates[m], ( m + 1 ), y );
    }
    fclose ( fPtr );
}