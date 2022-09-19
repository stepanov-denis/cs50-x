// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <cs50.h>
#include <strings.h>

#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table
const unsigned int N = 262144;

// Hash table
node *table[N];

// Counter of the number of words in the hash table
unsigned int count_word = 0;

// Pointer to the counter of the number of words in the hash table
unsigned int *count_ptr = &count_word;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Calculate hash for word
    unsigned int index = hash(word);

    // Checking that the node is not empty
    if (table[index] == NULL)
    {
        return false;
    }

    // Сhecking for the presence of a word in this node
    if (table[index] != NULL && strcasecmp(table[index]->word, word) == 0)
    {
        return true;
    }

    // If the word is not in this node, search for the word in the linked list of nodes
    if (table[index] != NULL && strcasecmp(table[index]->word, word) != 0)
    {
        node *cursor = malloc(sizeof(node));
        cursor = table[index];
        while (true)
        {
            if (cursor->next != NULL)
            {
                cursor = cursor->next;
            }

            if (strcasecmp(cursor->word, word) == 0)
            {
                return true;
            }

            if (cursor->next == NULL)
            {
                break;
            }
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Improve this hash function
    unsigned int hash = 0;
    unsigned int deduct = 2;

    // Calculate hash for word
    for (int i = 0; i < LENGTH + 1; i++)
    {
        if (word[i] == '\0')
        {
            break;
        }

        hash += tolower(word[i]);
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    hash = hash % N;
    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary in read mode
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    // Buffer for word
    char current_word[LENGTH + 1];

    // Read each word in dictionary
    while (fscanf(f, "%s", current_word) != EOF)
    {
        // Allocate memory for node
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return 1;
        }

        // Copy word to node
        strcpy(n->word, current_word);
        n->next = NULL;

        // Calculate hash for word
        unsigned int current_hash = hash(current_word);

        // If there is no such node in the table yet, insert it
        if (table[current_hash] == NULL)
        {
            table[current_hash] = n;
            unsigned int tmp = *count_ptr + 1;
            *count_ptr = tmp;
        }

        // if there is already a node for this hash, insert the node into the linked list
        if (table[current_hash] != NULL && strcasecmp(table[current_hash]->word, current_word) != 0)
        {
            n->next = table[current_hash];
            table[current_hash] = n;
            unsigned int tmp = *count_ptr + 1;
            *count_ptr = tmp;
        }
    }

    // Close dictionary
    fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return *count_ptr;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            free(table[i]);
        }
    }
    return true;
}