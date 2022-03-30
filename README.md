# Payday
This is a program intended for a company who needs to check which dates the employers will be paid on.
## How to use
The file needs a year as a command line argument, any year from 1 - 9999 can be used. 
When running the program add the year after the executable. 
## How it works
It takes a year as an input from CLI, calculates which dates the employers can be payed on every month and for 
each payment date a notification date 3 days prior. First it checks if employer can be payed on 10th of said month, 
if it falls on a weekend day or public holiday then it uses the last day which was neither a weekend or holiday. All of this data
(24 dates in total) will be saved into a file called 2022.csv. 
## Additional info
For simplicity's sake it comes in one single .c file without header files, so as to make compiling and running from command line easier. 

