// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 676;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word_1)
{
    node *tmp;
    tmp = table[hash(word_1)];
    while (tmp != NULL)
    {
        if (strcasecmp(tmp->word, word_1) == 0)
        {
            return true;
        }

        tmp = tmp->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int n ;
    if (strlen(word) == 1)
    {
        n = 0;
    }
    else
    {

        n = toupper(word[1]) - 'A';
    }
    int m = 26 * (toupper(word[0]) - 'A') + n;
    return m;
}

int words_in_dic = 0;
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char word_1[LENGTH + 1];
    FILE *file_d = fopen(dictionary, "r");
    if (file_d == NULL)
    {
        return false;
    }
    while (fscanf(file_d, "%s", word_1) != EOF)
    {
        node *word_node = malloc(sizeof(node));
        strcpy(word_node->word, word_1);
        word_node->next = table[hash(word_1)];
        table[hash(word_1)] = word_node;
        words_in_dic++;
        //printf("%i", words_in_dic);

    }
    fclose(file_d);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

    return words_in_dic;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *tmp;
    node *cursor;

    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {

            tmp = cursor->next;
            free(cursor);
            cursor  = tmp;
        }

    }
    return true;
}
