/**
 * Recovers jpegs
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    //checks for correct number of arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    
    //remember file name
    char *infile = argv[1];
    
    //open input file
    FILE *inptr = fopen(infile, "r");
    
    //check that image can be opened
    if (inptr == NULL)
    {
        fprintf(stderr, "Cannot open %s.\n", infile);
        return 2;
    }
    
    //set up buffer
    BYTE buffer[512];
    
    //allocate space for filename
    char filename[8];
    
    //variable to count number of jpegs
    int count = 0;
    
    //flag for whether writing to jpeg already
    bool jexist = false;

    //set variable for output file
    FILE *img = NULL; 
    
    //read through card file until eof reached, which is a chunk less than 512
    while(fread(&buffer, 1, 512, inptr) == 512){

        // check for beginning of jpeg
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            //close old file if there is one
            if(jexist == true)
            {
                //close output file
                fclose(img);
                jexist = false;
            }

            //make new file for jpeg
            sprintf(filename, "%03i.jpg", count);
            
            //increment file count
            count++; 
            
            // //open output file
            img = fopen(filename, "w");
            if (img == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", filename);
                return 3;
            }
            
            //write to output file
            fwrite(buffer, 1, 512, img); 
            
            //set flag for currently writing jpeg
            jexist = true;
        }
        else if (jexist == true)//if existing jpeg file is being written to, add to it
        {
            //write to output file
            fwrite(buffer, 1, 512, img);
        }
        
    }
    
    //close img file
    fclose(img);
    
    // close infile
    fclose(inptr);
    
    // success
    return 0;
}