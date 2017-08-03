/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <math.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    //return false is value is non-positive
    if(value <=0)
    {
        return false;
    }
    
    int end = n - 1;
    int start = 0;
    while(end >= start)
    {
        int mid = (int)floor((start + end)/2);
        if(values[mid] == value)
        {
            return true;
        }
        else if(values[mid] > value)
        {
            end = mid - 1;
        }
        else if(values[mid] < value)
        {
            start = mid + 1;
        }
        
    }
    

    //if the value was not found above, return false
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{

    int swap = 0;//setup termination variable
    
    //loop through array.  Outer loop makes end index smaller each time since final value of each loop is in correct place
    for(int i = n-1; i > 0; i--)
    {
        swap = 0;//reset termination variable
        //start at beginning of array and check current value versus next value
        for(int j = 0; j < i; j++)
        {
            //swap if left value is larger
            if(values[j] > values[j+1])
            {
                int temp = values[j+1];
                values[j+1] = values[j];
                values[j] = temp;
                swap++;
            }
        }
        
        if(swap == 0)//if no swaps occured, end bubble sort
        {
            return;
        }
    }
      
    return;
}
