// Helper functions for music
#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <math.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    //turs fraction into numbers
    if (strcmp(fraction, "1/8") == 0)
    {
        return (1);
    }
    else if (strcmp(fraction, "1/4") == 0)
    {
        return (2);
    }
    else if (strcmp(fraction, "3/8") == 0)
    {
        return (3);
    }
    else if (strcmp(fraction, "1/2") == 0)
    {
        return (4);
    }
    else if (strcmp(fraction, "1") == 0)
    {
        return (8);
    }
    else
    {
        printf("Something went wrong with note input");
        return (0);
    }
}

//returns 2^(x/12) value
float ft_note_numbr(char note, char accident, int octave) // c appears to be counted @ c1 - sort out
{
    float   numpow = 0.0; //pow numerator
    float   res;

    if (((octave == 0) && (note != 'A' && note != 'B'))  || (octave == 8 && note != 'C') || octave < 0 || octave > 8)
    {
        printf("Out of piano bounds.");
        return (0);
    }
    if (octave == 0) //clutch on 0 octave
    {
        if ((note == 'A') || (note == 'B') || (note == 'A' && accident == '#') || (note =='B' && accident == 'b'))
        {
            if (note == 'A')
            {
                return (1.0);
            }
            else if (note == 'B')
            {
                numpow += 2.0;
            }
            else
            {
                numpow += 1.0;
            }
            res = powf(2.0, (numpow / 12.0));
            return (res);
        }
        else
        {
            printf("Wrong note input on 0'th octave.");
            return (0);
        }
    }
    if ((octave != 0) && (note == 'A' || note == 'B'))
    {
        octave++;
    }
    for (int cnt = 1; cnt != octave; cnt++)
    {
        numpow = numpow + 12;
    }
    if (note == 'A')
    {
        numpow += 0.0;
    }
    else if (note == 'B')
    {
        numpow += 2.0;
    }
    else if (note == 'C')
    {
        numpow += 3.0;
    }
    else if (note == 'D')
    {
        numpow += 5.0;
    }
    else if (note == 'E')
    {
        numpow += 7.0;
    }
    else if (note == 'F')
    {
        numpow += 8.0;
    }
    else if (note == 'G')
    {
        numpow += 10.0;
    }
    else
    {
        printf("Wrong note input");
        return (0);
    }
    if (accident != '#' && accident != 'b' && accident != '!')
    {
        printf("Wrong accidental input");
        return (0);
    }
    if (accident == '#')
    {
        numpow += 1.0;
    }
    if (accident == 'b')
    {
        numpow -= 1.0;
    }
    res = powf(2.0, (numpow / 12.0));
    return (res);
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    char    pars_note;
    char    pars_accidental = '!';
    int     pars_octave;
    int     note_length;
    float   a0 = 440 / 16 + 0.5; // "starting" a0 note point
    float   resf;

    note_length = strlen(note);
    //parse note on n, a, oct
    if (note_length == 3)
    {
        pars_note = note[0];
        pars_accidental = note[1];
        pars_octave = note[2] - '0';
    }
    else if (note_length == 2)
    {
        pars_note = note[0];
        pars_octave = note[1] - '0';
    }
    else
    {
        printf("Wrong note input format");
        return (0);
    }
    //counting tone value with ft_note_numbr
    resf = a0 * ft_note_numbr(pars_note, pars_accidental, pars_octave) + 0.5;
    return (resf);
}
// Determines whether a string represents a rest
bool is_rest(string s)
{
    //if s represents rest - true
    if (strcmp(s, "") == 0)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}