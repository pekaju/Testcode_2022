/**
 * @file header.h
 * @author Peeter Kaju (kajupeeter@gmail.com)
 * @brief header file for testules.c, which contains standard library inclusions, definitions and 
 * function declarations.
 * @date 2022-03-30
 */

// to avoid double inclusion check if this has been included before
#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// number of months in a year is 12 and 10 is the date when employers are paid.
#define MONTHS 12
#define DAY 10

// for clarity define 7th day of week SUNDAY and 6th day SATURDAY 
#define SUNDAY 7
#define SATURDAY 6

// function declarations
int dayOfPayment ( int, int );
int findWeekDay ( int, int, int );
int aprilDate ( int, int );
int otherDate ( int );
int findBigFriday ( int );
void fileWriter ( int[], int[], int );

#endif
