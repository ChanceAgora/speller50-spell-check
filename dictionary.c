// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Test numbers to choose number of buckets in hash table
const unsigned int N = 131071; // Prime number for buckets

// Hash table
node *table[N] = {NULL};

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO: Implement dictionary lookup
    

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int hash = 5381;
    int c = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        hash = (hash * 33) + tolower(*word[i]);
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    int histogram[N] = {0}; // Temporary variable for viewing hash buck distribution
    // TODO: Implement loading dictionary into memory
    char c = 0;
    char word[LENGTH + 1];
    int index = 0;

    while (fread(c, sizeof(char), 1, file))
    {
        if (isalpha(c) || c == '\'')
        {
            word[index] = c; 
            index++;
        }
        else if (index > 0)
        {
            word[index] = '\0';
            unsigned int hash = hash(word);
            node *item = table[hash];
            
        }
    }

    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Identify number of words in dictionary
    unsigned int words = 0;
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            words++;
            cursor = cursor->next;
        }
    }

    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Unload dictionary
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *next = cursor->next;
            free(cursor);
            cursor = next;
        }
    }

    return true;
}
