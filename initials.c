#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include<ctype.h>

int main(void)
{
    //get user name and store it in 's'
    string s = get_string();

    //check that 's' is a valid string
    if (s != NULL)
    {
        //iterate over chars in string 's'
        for (int i = 0, n = strlen(s); i < n; i++)
        {
            //check for first letter of word and print the first char of it
            if (!isblank(s[i]) && (isblank(s[i-1]) || i == 0))
            {
                printf("%c", toupper(s[i]));
            }
        }
        printf("\n");
    }

}