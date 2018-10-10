// resizes (i.e., enlarges or shrinks) 24-bit uncompressed BMPs by a factor of incoming value.

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"
//able to make your image bigger on decimal scale(e.g 1.1 to 100), or smaller (0.9 to 0.1) ./resize 1.5 small.bmp new.bmp
int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    float   change = atof(argv[1]);
    char    *infile = argv[2];
    char    *outfile = argv[3];
    if (change <= 0 || change > 100)
    {
        printf("Resize value has to be number, more than 0 and less than 100.\n");
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }
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
    //saving input size and padding, changing output size and padding
    int in_width = bi.biWidth;
    int in_height = bi.biHeight;
    int in_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biWidth = (bi.biWidth * change) /*+ 0.5*/;
    if (bi.biHeight < 0)
    {
        bi.biHeight = (bi.biHeight * change)/* - 0.5*/;
    }
    else
    {
        bi.biHeight = (bi.biHeight * change) + 0.5;
    }
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //determine bi.SizeImage and bf.bfSize for new headers
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    //decimal part of resize
    int dec = (change * 100);
    int integ = dec / 100;          //integer value
    dec = dec % 100;                //decimal read value
    int decw = 0;                   //write counter
    int decrow = dec;               //row input counter
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(in_height); i < biHeight; i++)
    {
        //copying each row
        for (int cntr = 0; cntr < integ; cntr++)
        {
            // temporary storage
            RGBTRIPLE triple;
            // iterate over pixels in scanline
            for (int l = 0; l < (in_width); l++)
            {
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                //enhancing horizontal pixels
                for (int cntp = 0; cntp < integ; cntp++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
                decw = decw + dec;
                if (decw >= 100)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    decw = decw - 100;
                }
            }
            //jumping onto first byte of the line
            fseek(inptr, - (in_width * sizeof(RGBTRIPLE)), SEEK_CUR);
            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
            decw = 0;
        }
        //reading over rows (adding counter here)
        if (decrow >= 100)
        {
            // temporary storage
            RGBTRIPLE triple;
            // iterate over pixels in scanline
            for (int j = 0; j < (in_width); j++)
            {
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                //enhancing horizontal pixels
                for (int cntp = 0; cntp < integ; cntp++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
                decw = decw + dec;
                if (decw >= 100)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    decw = decw - 100;
                }

            }
            //jumping onto first byte of the line
            fseek(inptr, - (in_width * sizeof(RGBTRIPLE)), SEEK_CUR);
            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
            decrow = decrow - 100;
            decw = 0;
        }
        // skip over padding, if any
        fseek(inptr, (in_padding + (in_width * sizeof(RGBTRIPLE))), SEEK_CUR);
        decrow = decrow + dec;
    }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}