// enhances a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "bmp.h"
// makes your bmp image bigger ./resize 2(or any number to 100) incoming_image.bmp new_image_name.bmp
int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: enhanse(number) infile outfile\n");
        return 1;
    }

    // remember filenames
    int     enhance = atoi(argv[1]);
    char    *infile = argv[2];
    char    *outfile = argv[3];

    if (enhance <= 0 || enhance > 100)
    {
        printf("Enhance has to be number, more than 0 and less than 100.\nUsage: enhanse(number) infile outfile\n");
        return (1);
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
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);//data, size, number, inptr

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
    //adding biWidth, biHeight of enhanced file
    int in_width = bi.biWidth;
    int in_height = bi.biHeight;
    int in_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //int rowlength = in_padding + in_width;
    //RGBTRIPLE *triple_rollback; //adding structure to rollback pointer when needed;
    bi.biWidth = bi.biWidth * enhance;
    bi.biHeight = bi.biHeight * enhance;
    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //determine enhanced biSizeImage
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight); //abs returns positive value
    //increasiing bf.bfSize by adding increased bi.biSizeImage
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(in_height); i < biHeight; i++)
    {
        for (int cntr = 0; cntr < enhance; cntr++)
        {
            // temporary storage
            RGBTRIPLE triple;
            // iterate over pixels in scanline
            for (int j = 0; j < (in_width); j++)
            {
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                //enhancing horizontal pixels
                for (int cntp = 0; cntp < enhance; cntp++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            //jumping onto first byte of the line
            fseek(inptr, - (in_width * sizeof(RGBTRIPLE)), SEEK_CUR);
            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
        }
        // skip over padding, if any
        fseek(inptr, (in_padding + in_width * sizeof(RGBTRIPLE)), SEEK_CUR);
    }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
