#include <cs50.h>
#include <stdio.h>
//recovers JPEGs from a forensic image
int main(int ac, char **av)
{
    if (ac != 2)
    {
        fprintf(stderr, "Usage: ./recover image");
        return (1);
    }
    char    *infile = av[1];
    //char    *outfile = ; -later
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return (2);
    }
    //creating buffer
    char     buff[513];
    char    filename[8] = "";
    FILE    *outptr = NULL;
    int     jpg_number = 0;
    int     jpg_switch = 0; //did we found jpg's?
    //going through file
    while (fread(&buff, 512, 1, inptr))
    {
        //fread(&buff, 512, 1, inptr);
        if (buff[0] == (char)0xff && buff[1] == (char)0xd8 && buff[2] == (char)0xff && (buff[3] >= (char)0xe0 && buff[3] <= (char)0xef))
        {
            if (jpg_switch == 1)
            {
                fclose(outptr);
            }
            sprintf(filename, "%03i.jpg", jpg_number);
            // open(create) output file
            outptr = fopen(filename, "w");
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", filename);
                return (3);
            }
            jpg_switch = 1;
            jpg_number++;
        }
        if (jpg_switch == 1)
        {
            fwrite(&buff, 512, 1, outptr);
        }
    }
    fclose(inptr);
    fclose(outptr);
    return (0);
}