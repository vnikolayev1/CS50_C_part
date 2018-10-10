#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

//encrypts word on given number example  ./caesar 1 hello - ifmmp
int     main(int argc, char **argv)
{
    int     shift;
    int     cnt;

    cnt = 0;
    if (argc == 2)
    {
        char    *text = get_string("plaintext: ");
        shift = atoi(argv[1]);
        printf("%s", "ciphertext: ");
        while (text[cnt] != '\0')
        {
            if (text[cnt] >= 65 && text[cnt] <= 90)
            {
                text[cnt] = (text[cnt] - 64 + shift) % 26 + 64;
            }
            else if (text[cnt] >= 97 && text[cnt] <= 122)
            {
                text[cnt] = (text[cnt] - 96 + shift) % 26 + 96;
            }
            printf("%c", text[cnt]);
            cnt++;

        }
    }
    else
    {
        printf("%s", "Usage: ./caesar k");
        return (1);
    }
    printf("%c", '\n');
    return (0);
}