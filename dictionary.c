/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>

#include "dictionary.h"

// //delcare function to change chars and apostrophy to alpha index
// int atoindx(char c);

//define constant for char set to be used in trie node children array
#define ALPHA_SIZE (27)

//define nodes for Trie
typedef struct node
{
    bool is_word;
    struct node *children[ALPHA_SIZE];
}
node;

//setup root of trie and pointer to move through it
node *root;
node *nodeptr;

// //declare fucnction to insert into trie
// void insert(node *root, const char *str);

// //declare function for creating new nodes of trie
// node *newnode(void);

//initialize dictionary word size counter
int dsize = 0;

int indx;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    //set traversal pointer to root
    nodeptr = root;
    
    //int lttr;
    
    //for each letter in word
    for (int j = 0, leng = strlen(word); j < leng; j++)
    {
        // //convert char to alpha index and store in lttr
        // lttr = atoindx(word[j]);
        //check for apostrophy and return last index of alpha array
        if(word[j] == '\'')
        {
            indx = 26;
        }
        else //otherwise, convert char into int 0-25
        {
            indx = tolower(word[j]) - 'a';//substract to difference of ASCII value to get 0-25
        }
        
        //go to corresponding element in children
        if(nodeptr->children[indx] == NULL)
        {
            return false;//if NULL, word is misspelled
        }
        else//if not NULL, move to the next letter
        {
            nodeptr = nodeptr->children[indx];
            //check is_word at the end of word
            if (j == leng -1)
            {
    
                //check if is_word it true
                if(nodeptr->is_word)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
            
    }
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // try to open dictionary to read
    FILE *d = fopen(dictionary, "r");
    if (d == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        fclose(d);
        return false;
    }
    
    
    /***********
     *****/ 
    //prepare to capture words
    /*int*/ indx = 0;
    
    //setting root and nodeptr
    root = calloc(1, sizeof(node));
    nodeptr = root;
    
    //iterate over each char until \n to create words
    for (int c = fgetc(d); c != EOF; c = fgetc(d))
    {
        if(c != '\n')
        {
            // //convert char to aplha index and store in mark
            // indx = atoindx(c);
            //check for apostrophy and return last index of alpha array
            if(c == '\'')
            {
                indx = 26;
            }
            else //otherwise, convert char into int 0-25
            {
                indx = tolower(c) - 'a';//substract to difference of ASCII value to get 0-25
            }
            
            //check for null before creating a new node
            if(!nodeptr->children[indx])
            {
                nodeptr->children[indx] = (node*)malloc(sizeof(node));
            }
        
            //move pointer to next node
            nodeptr = nodeptr->children[indx];
        }


        if(c == '\n')//check for last char in word
        {
            nodeptr->is_word = true;
            nodeptr = root;
            dsize++;//increment dictionary word count
        }
    }
     /*
     * ************/
    
    
    
    
    
    
    // //prepare to capture words
    // int indx = 0;
    // char w[LENGTH+1];
    // memset(w, 0, sizeof(w));
    
    // //setting root and nodeptr
    // root = calloc(1, sizeof(node));
    // nodeptr = root;
    
    // //iterate over each char until \n to create words
    // for (int c = fgetc(d); c != EOF; c = fgetc(d))
    // {
    //     // check for end of word
    //     if (c != '\n')
    //     {
    //         // append character to word
    //         w[indx] = c;
            
    //         //increment indx for next char
    //         indx++;

    //     }
    //     else//end of word
    //     {
    //         w[indx] = '\0';
    //         insert(root, w);//add word to trie
    //         indx = 0;//reset word index for next word
    //         dsize++;//increment dictionary word count
    //     }
    // }
    
    fclose(d);

    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    //return global counter that is incremented upon loading of dictionary
    return dsize;
}

//recurions to free nodes bottom up
bool freenode(node *path)
{
    for(int x = 0; x < 27; x++)
    {
        //check for end of path
        if(path->children[x] != NULL)
        {
            freenode(path->children[x]);//if not end of path, move to the next node
        }
    }
    free(path);
    return true; 
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    //free trie from memory
    return freenode(root);
}


// //function to create new nodes
// node *newnode(void)
// {
//     //initialize a block of memory that is node sized to a node pointer 
//     node *nnode = (node*)malloc(sizeof(node));
    
//     //check the node was allocated memory
//     if(nnode)
//     {
//         //initialize word check to false
//         nnode->is_word = false;
//         //initialize children array to NULL
//         memset(nnode->children, 0, sizeof(nnode->children));
//     }
//     else//if malloc failed, report error, unload dictionary from memory, and return 1
//     {
//         printf("Could not create new node.\n");
//         unload();
//         return NULL;
//     }
    
//     return nnode;
// }

// //add word to trie
// void insert(node *root, const char *str)
// {
//     //set traversal pointer to root
//     nodeptr = root;
    
//     //create variable to store alpha index value for char
//     int mark;
    
//     //iterate over each char in str
//     for (int i = 0, len = strlen(str); i < len; i++)
//     {
//         //convert char to aplha index and store in mark
//         mark = atoindx(str[i]);
        
//         //check for null before creating a new node
//         if(!nodeptr->children[mark])
//         {
//             nodeptr->children[mark] = newnode();
//         }
        
//         //move pointer to next node
//         nodeptr = nodeptr->children[mark];

//         if(i == len - 1)//check for last char in word
//         {
//             nodeptr->is_word = true;
//         }
//     }
// }

// //implement alpha index converter
// int atoindx(char ci)
// {
//     //setup variable to store return value
//     int ai;
//     //check for apostrophy and return last index of alpha array
//     if(ci == '\'')
//     {
//         ai = 26;
//         return ai;
//     }
//     else //otherwise, convert char into int 0-25
//     {
//         ai = tolower(ci) - 'a';//substract to difference of ASCII value to get 0-25
//         return ai;
//         // char converttoindex = tolower(ci); //make sure we are looking at lower case versions of each char only
//         // ai = (int)converttoindex - (int)'a';//substract to difference of ASCII value to get 0-25
//         // return ai;
//     }
// } 