#include <stdio.h>
#include <cs50.h>
#include <math.h>


int main(void)
{
    printf("O hai! How much change is owed?\n");
    
    float input;
    int count = 0;
    
    do
    {
        input = get_float();
        if(input < 0)
        {
            printf("How much change is owed?\n");
        }
    }
    while(input < 0);
    
    int cd = round(input * 100);
    
    if(cd > 0)
    {
        while(cd >= 25)
        {
            count++;
            cd = cd - 25;
        }
        
        while(cd >= 10)
        {
            count++;
            cd = cd - 10;
        }
        
        while(cd >= 5)
        {
            count++;
            cd = cd - 5;
        }
        
        while(cd >= 1)
        {
            count++;
            cd = cd - 1;
        }
    }
    
    printf("%i\n", count);
}