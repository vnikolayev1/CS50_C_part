#include <stdio.h>
#include <cs50.h>
/*Encrypts messages using Vigenère’s cipher, per the below.

$ ./vigenere ABC
plaintext:  HELLO
ciphertext: HFNLP
*/
int main(int argc, char **argv)
{
    int     cnt = 0;
    int     cntv = 0;
    int     shift;

    if (argc == 2)
    {
        while (argv[1][cntv] != '\0')
        {
            if (!(argv[1][cntv] >= 97 && argv[1][cntv] <= 122) && !(argv[1][cntv] >= 65 && argv[1][cntv] <= 90))
            {
                printf("invalid keyword\n");
                return (1);
            }
            cntv++;
        }
        cntv = 0;
        char    *text = get_string("plaintext: ");
        while (text[cnt] != '\0')
        {

            if (argv[1][cntv] == '\0')
            {
                cntv = 0;
            }
            if (argv[1][cntv] >= 97 && argv[1][cntv] <= 122)
            {
                shift = argv[1][cntv] - 97;
            }
            else if (argv[1][cntv] >= 65 && argv[1][cntv] <= 90)
            {
                shift = argv[1][cntv] - 65;
            }
            if (text[cnt] >= 65 && text[cnt] <= 90)
            {
                text[cnt] = (text[cnt] - 64 + shift) % 26 + 64;
                cntv++;
            }
            else if (text[cnt] >= 97 && text[cnt] <= 122)
            {
                text[cnt] = (text[cnt] - 97 + shift) % 26 + 97;
                cntv++;
            }
            cnt++;
        }
        printf("ciphertext: %s", text);
    }
    else if (argc != 2)
    {
        printf("%s", "Usage: ./vigenere k");
        return (1);
    }
    printf("%c", '\n');
}