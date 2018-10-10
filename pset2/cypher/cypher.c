#define _XOPEN_SOURCE //char *crypt(const char *key, const char *salt);
#include <unistd.h>
#include <cs50.h>
#include <string.h>
#include <stdio.h>

//cyphers any word given into arr
int main(void)
{
    char arr[6] = "zzzzz";
    char salt[3] = "50";
    char *result;

    result = crypt(arr, salt);
    printf("%s\n", result);
}