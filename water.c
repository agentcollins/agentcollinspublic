#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("How many minutes do you shower? ");
    int minutes = get_int();
    
    int bottles = 12 * minutes;
    
    
    printf("Minutes: %i\n", minutes);
    printf("Bottles: %i\n", bottles);
}