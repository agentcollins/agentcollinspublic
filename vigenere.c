#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char alphaShift(char c, int i);

int main(int argc, string argv[])
{
    //check if proper number or command line arguments were passed to main.  If not, display error message and return 1 to main.
    if (argc != 2)
    {
        printf("Usage: ./vingenere k\n");
        return 1;
    }

    //convert argument into ciper key
    string s = argv[1];    
    
    int len = strlen(s);
    int y = 0;
    //check that argv is all alphabetical chars
    while(y < len)
    {
        if (!isalpha(s[y]))
        {
            printf("Invalid ciper key\n");
            return 1;
        }
        y++;
    }
    
    //get plaintext from user
    printf("plaintext: ");
    string p = get_string();
    
    //intialize key to lower case alhpa index of first char
    int start = tolower(s[0]) - 97; 
    int k = start;
    int counter = 0;

    
    
    //iterate over each char in plaintext and encrypt it with alphaShift function written below
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        
        //check to see if char is a-z or A-Z.  If not, do change it.
        if(isalpha(p[i]))
        {
            
            p[i] = alphaShift(p[i], k);
            //increment key
            counter++;
            k = tolower(s[counter]) -97;

            //check for end of key.  If at end, reset to start
            if (counter >= len)
            {
                k = start;
                counter = 0;
            }
        }

    }
    

    //display encrypted text
    printf("ciphertext: %s", p);
    printf("\n");
    return 0;
}

char alphaShift(char c, int i)
{
    //initialize shift for lower case
    int x = 97;
    //switch shift for uppper case if needed
    if(isupper(c))
    {
        x = 65;
    }

    //shift char in the alphabet n number of spaces, where n equals int passed in
    c = x + ((c - x + i) % 26);
    return c;
}