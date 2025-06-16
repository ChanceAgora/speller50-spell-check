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
    unsigned int hash = 5381;
    int c = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        hash = (hash * 33) + tolower(word[i]);
    }

    return hash % N;
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
        c = fgetc(file)

        if (isalpha(c) || c == '\'')
        {
            word[index] = c; 
            index++;
        }
        else if (index > 0)
        {
            word[index] = '\0';
            index = 0;
            unsigned int hash = hash(word);
            node *cursor = table[hash];

            // Add new word to hash table
            if (cursor == NULL)
            {
                table[hash] = malloc(sizeof(node));
                cursor = table[hash];
                if (cursor == NULL)
                {
                    unload();
                    fclose(file);
                    return false;
                }
                cursor->next = NULL;
            }
            else
            {
                node *temp = malloc(sizeof(node));
                if (temp == NULL)
                {
                    unload();
                    fclose(file);
                    return false;
                }
                temp->next = cursor;
                table[hash] = temp;
                cursor = temp;
            }
            // Set the node's word value to the dictionary word
            strcpy(cursor->word, word);
        }
    }

    fclose(file);
    return true;
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
