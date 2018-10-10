#include <cs50.h>
#include <stdio.h>
//builds one-sided piramide from mario in bash
void b(int dashes)
{
    while (dashes != 0)
    {
        printf("%c", '#');
        dashes--;
    }
}
void c(int spaces)
{
    while (spaces != 0)
    {
        printf("%c", ' ');
        spaces--;
    }
}

int main(void)
{
    int height = get_int("Height: ");
    int dashes = 2;
    int spaces;
    int length = height + 1;

    if (height > 0 && height <= 23)
    {
        while (height != 0)
        {
            spaces = length - dashes;
            c(spaces);
            b(dashes);
            printf("%s", "\n");
            height--;
            dashes++;
        }
    }
    else if (height == 0)
    {
        return (0);
    }
    else
    {
        main();
    }
    return (0);
}