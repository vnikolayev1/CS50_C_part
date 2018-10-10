#define _XOPEN_SOURCE //char *crypt(const char *key, const char *salt);
#include <unistd.h>
#include <cs50.h>
#include <string.h>
#include <stdio.h>

char ft_inc_char(char ch);
/*brut forces encrypted password of chars, first two incoming chars are salt. examples to brute:
usage: ./crack 50fkUxYHbnXGw - rofl
50xcIMJ0y.RXo
50mjprEcqC/ts
50GApilQSG3E2
50n0AAUD.pL8g
50CcfIk1QrPr6
509nVI8B9VfuA
50JIIyhDORqMU
50JGnXUgaafgc
51u8F0dkeDSbY
50cI2vYkF0YU2
*/
int main(int ac, char **av)
{
    int     cnt = 0;
    int     iter;
    char    salt[3];
    char    *result;
    char    arr[6];

    if (ac != 2)
    {
        printf("Too many or not enough arguments.\n");
        return (1);
    }
    salt[0] = av[1][0];
    salt[1] = av[1][1];
    salt[2] = '\0';

    while (cnt != 6)
    {
        arr[cnt] = '\0';
        cnt++;
    }
    cnt = 0;
    while (cnt != 5)
    {

        while (arr[cnt] != '!')
        {
            if (arr[cnt] != '!')
            {
                result = crypt(arr, salt);
                //printf("result: %s\n", arr);    //for debug
                if (strcmp(av[1], result) == 0)
                {
                    printf("Password is: %s\n", arr);
                    return (0);
                }
            }
            arr[cnt] = ft_inc_char(arr[cnt]);
        }
        if (arr[0] == '!')
        {
            arr[cnt] = ft_inc_char(arr[cnt]);
            cnt++;
            arr[cnt] = ft_inc_char(arr[cnt]);
        }
        else if (arr[cnt] == '!' && cnt != 0)
        {
            iter = cnt;
            while (iter >= 0)                                    //getting rid of !'s
            {
                if (arr[0] == '!')
                {
                    arr[iter] = ft_inc_char(arr[iter]);
                    cnt++;
                    arr[cnt] = ft_inc_char(arr[cnt]);
                }
                if (arr[iter] == '!')
                {
                    arr[iter - 1] = ft_inc_char(arr[iter - 1]);     //increasing prev char on 1
                    arr[iter] = ft_inc_char(arr[iter]);          //increasing this char on 1
                }
                iter--;
            }
        }
    }
    if (cnt == 5)
    {
        printf("End of the line. Password is different, than 5 letters.");
        return (0);
    }
    return (0);
}

char ft_inc_char(char ch)
{
    if (ch == '\0' || ch == '!')
    {
        ch = 65;
    }
    else if ((ch >= 65 && ch < 90) || (ch >= 97 && ch < 122))
    {
        ch++;
    }
    else if (ch == 90)
    {
        ch = 97;
    }
    else if (ch == 122)
    {
        ch = '!';
    }
    return (ch);
}
/* char alph[] = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ" - for consideration
/*char ft_inc_char(char ch)    //for debug, just A and Z
{
    if (ch == '\0' || ch == '!')
    {
        ch = 65;
    }
    else if (ch == 65)
    {
        ch = 90;
    }
    else if(ch == 90)
    {
        ch = '!';
    }
    return (ch);
}*/