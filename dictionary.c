// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Test numbers to choose number of buckets in hash table
const unsigned int N = 131071; // Prime number for buckets
unsigned int wordCount = 0;

// Hash table
node *table[N] = {NULL};

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Check for the word in the dictionary
    node *cursor = table[hash(word)];
    
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
            return true;
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int h = 5381;
    int c = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        h = (h * 33) + tolower(word[i]);
    }

    return h % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // load dictionary into memory
    FILE *file = fopen(dictionary, "r");
    if (!file)
        return false;
    char c = 0;
    char word[LENGTH + 1];
    int index = 0;

    // Read chars from the dictionary and assemble words
    while (!feof(file))
    {
        // Read from dictionary
        c = fgetc(file);

        if (index >= LENGTH)
        {
            while ((c = fgetc(file)) != '\n' && c != EOF);
            index = 0;
        }
        else if (isalpha(c) || c == '\'')
        {
            word[index] = c; 
            index++;
        }
        else if (index > 0)
        {
            word[index] = '\0';
            index = 0;
            unsigned int h = hash(word);

            // Allocate Memory for New Word
            node *newNode = malloc(sizeof(node));
            if (!newNode)
            {
                unload();
                fclose(file);
                return false;
            }

            // Add word to Dictionary
            newNode->next = table[h];
            table[h] = newNode;

            // Set the node's word value to the dictionary word
            strcpy(newNode->word, word);
            wordCount++;
        }
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordCount;
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
