// Implements a dictionary's functionality

#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define BUCKET_LENGTH 143091
#define MAXWORDLENGTH 46
typedef struct node
{
    char            word[MAXWORDLENGTH];
    struct  node     *next;
} node;
int         WORDS_LOADED = 0;
node        *BUCKET[BUCKET_LENGTH];

//hashes words (djb2 by Dan Bernstein at http://www.cse.yorku.ca/~oz/hash.html with modifyed incoming parameter)
unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}
// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int     hashword_num;
    char    low_word[MAXWORDLENGTH];
    int i = 0;
    for (; word[i] != '\0'; i++)
    {
        low_word[i] = tolower(word[i]);
    }
    low_word[i] = '\0';
    hashword_num = hash(low_word) % BUCKET_LENGTH;
    //strcmp incoming word with bucket's word @ hasword_num location
    for (node *cursor = BUCKET[hashword_num]; cursor != NULL;)
    {
        if (strcmp(cursor -> word, low_word) == 0)
        {
            return (true);
        }
        cursor = cursor -> next;
    }
    return (false);
}
// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)//name of dict
{
    int     hashword_num;
    for (int i = 0; i <= BUCKET_LENGTH - 1; i++)
    {
        BUCKET[i] = NULL;
    }
    FILE *file_in_dict = fopen(dictionary, "r");
    if (file_in_dict == NULL)
    {
        fclose(file_in_dict);
        fprintf(stderr, "Could not load %s.\n", dictionary);
        return (false);
    }
    node *new_node = malloc(sizeof(node));
    while (fscanf(file_in_dict, "%s", new_node -> word) != EOF)
    {
        hashword_num = hash(new_node -> word) % BUCKET_LENGTH;
        new_node -> next = BUCKET[hashword_num];
        BUCKET[hashword_num] = new_node;
        new_node = malloc(sizeof(node));
        WORDS_LOADED++;
    }

    //extracting eof extra cycle
    if (fscanf(file_in_dict, "%s", new_node -> word) == EOF)
    {
        fclose(file_in_dict);
        free(new_node);
        return (true);
    }
    else
    {
        fclose(file_in_dict);
        free(new_node);
        return (false);
    }
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return WORDS_LOADED;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //while we go over array
    for (int i = 0; i < BUCKET_LENGTH; i++)
    {
        node *cursor = BUCKET[i];
        while (cursor != NULL)
        {
            node    *free_node;
            free_node = cursor;
            cursor = cursor -> next;
            free(free_node);
        }
    }
    return true;
}