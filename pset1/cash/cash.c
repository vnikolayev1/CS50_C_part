#include <cs50.h>
#include <stdio.h>
#include <float.h>

//counts amount of coins we give in change
int main(void)
{
    float chowed;
    int coins;

    coins = 0;
    do
    {
        chowed = get_float("Change owed: ");
    }
    while (chowed > FLT_MAX || chowed < 0);
    chowed = (chowed * 1000 + 5) / 10;
    while (chowed >= 25)
    {
        chowed = chowed - 25;
        coins++;
    }
    while (chowed >= 10)
    {
        chowed = chowed - 10;
        coins++;
    }
    while (chowed >= 5)
    {
        chowed = chowed - 5;
        coins++;
    }
    while (chowed >= 1)
    {
        chowed = chowed - 1;
        coins++;
    }
    printf("%i\n", coins);
}