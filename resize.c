/**
 * Copies and resizes a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./copy factor infile outfile\n");
        return 1;
    }
    
    //remebmer factor
    int n = atoi(argv[1]);
    
    //ensure factor is in valid range
    if (n < 1 || n >100)
    {
        fprintf(stderr, "factor must be a positive integer less than or equal to 100\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    //capture padding in original file
    int opadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //capture original height and width
    int oldW = bi.biWidth;
    int oldH = bi.biHeight;
    
    //update height, width in bi
    bi.biWidth *= n;
    bi.biHeight *= n;
    
    // determine padding for scanlines of new file
    int npadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //update image size in bi
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + npadding) * abs(bi.biHeight);

    //update size in bf
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0; i < abs(oldH); i++)
    {
        //iterate write n times (vertical factor)
        for(int y = 0; y < n; y++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < oldW; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
                // write RGB triple to outfile n times (horizontal factor)
                for (int x = 0; x < n; x++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }

            }
            
            // skip over padding, if any in original file
            fseek(inptr, opadding, SEEK_CUR);
            
            //add padding based on new file size
            for (int k = 0; k < npadding; k++)
            {
                fputc(0x00, outptr);
            }
            
            //reset postion in inptr to start of line the first n -1 times to get veritcal factor lines
            if (y < n - 1)
            {
                //reset scan cursor to start of line
                fseek(inptr, -(long)((oldW * sizeof(RGBTRIPLE)) + opadding), SEEK_CUR);
            }
        }


    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
