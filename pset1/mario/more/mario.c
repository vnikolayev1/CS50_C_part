#include <cs50.h>
#include <stdio.h>

//builds two-sided piramide in bash
void ft_add_hash(int hashes)
{
    while (hashes != 0)
    {
        printf("%c", '#');
        hashes--;
    }
}
void ft_add_space(int spaces)
{
    while (spaces != 0)
    {
        printf("%c", ' ');
        spaces--;
    }
}

int main(void)
{

    int spaces;
    int hashes = 1;
    int length;
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (!(height <= 23 && height >= 0));
    length = height;
    while (height != 0)
    {
        spaces = length - hashes;
        ft_add_space(spaces);
        ft_add_hash(hashes);
        printf("%s", "  ");
        ft_add_hash(hashes);
        printf("%s", "\n");
        height--;
        hashes++;
    }
    return (0);
}