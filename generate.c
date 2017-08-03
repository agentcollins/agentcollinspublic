/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    // verifies proper number of arguments are passed into the command-line
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    //converts first (after program name) argument into an int
    int n = atoi(argv[1]);

    //If optional seed argument is provided, converts it long and passes it to srand48.  Otherwise, use current time (in seconds) to seed srand48. srand48 is needed to initialize drand48 which is called in the next function.
    if (argc == 3)
    {
        srand48((long) atoi(argv[2]));
    }
    else
    {
        srand48((long) time(NULL));
    }

    //generates and prints pseudo-random numbers, in quantity provided by command-line, whose upper limit is defined above in LIMIT.
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
