#include <stdio.h>
#include <cs50.h>

void printH(int d)
{
        for(int j = 0; j < d; j++)
        {
            printf("#");
        }
}

int main(void)
{
    printf("Height: ");
    
    int h;
    
    do
    {
        h = get_int();
        
        if(h < 0 || h >23)
        {
            printf("Height: ");
        }
    }
    while (h < 0 || h >23);
    
    int temp = h;
    int dif;

    for(int i = 0; i < h; i++)
     {
        int counter = 0;
        for(int s = 0; s < temp - 1; s++)
        {
            printf(" ");
            counter++;
        }
        
        dif = h - counter;
        
        printH(dif);
    
        printf("  ");
        
        printH(dif);
        
        printf("\n");
        temp--;
    }
    
}