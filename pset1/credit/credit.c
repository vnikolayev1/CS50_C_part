#include <cs50.h>
#include <stdio.h>
#include <limits.h>
//checks if credit card is valid
int main(void)
{
    long long cardno;
    long long digit;
    long long digsum;
    int first = 0;
    int scnd = 0;
    int cnt = 1;
    int bul = 10;
    int bultwo = 1;

    do
    {
        cardno = get_long_long("Number: ");
    }
    while (!(cardno >= LLONG_MIN && cardno <= LLONG_MAX));

    digsum = cardno;
    while (digsum > 10)
    {
        cnt++;                      //counter to find  amount of digits
        digsum = digsum / 10;
    }
    digit = cardno;
    digit = digit / bul;             //second digit alignment

    while (digit != 0)
    {
        scnd = scnd + ((((digit % 10) * 2) % 10) + (((digit % 10) * 2) / 10)); // Luhn's 2nd digit sum
        digit = digit / 100;
    }
    digit = cardno;
    digit = digit / bultwo;
    while (digit != 0)
    {
        first = first + (digit % 10) ; // Luhn's 1st digit sum
        digit = digit / 100;
    }
    if (((first + scnd) % 10) == 0)
    {
        if ((cnt == 13 && cardno / 1000000000000 == 4) || (cnt == 16 && cardno / 1000000000000000 == 4))
        {
            printf("%s\n", "VISA");
        }
        else if (cnt == 15 && (cardno / 10000000000000 == 34 || cardno / 10000000000000 == 37))
        {
            printf("%s\n", "AMEX");
        }
        else if (cnt == 16 && (cardno / 100000000000000 >= 51 && cardno / 100000000000000 <= 55))
        {
            printf("%s\n", "MASTERCARD");
        }
        else
        {
            printf("%s\n", "INVALID");
        }
    }
    else
    {
        printf("%s\n", "INVALID");
    }
    return (0);
}