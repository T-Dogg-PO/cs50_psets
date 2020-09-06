// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table. Change this to 26 to represent the number of letters in the alphabet
const unsigned int N = 26;

// Hash table
node *table[N];

// Create a variable to store the number of entries in the dictionary, so we can count at the same time we are iterating over the dictionary
int dictionary_count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Convert the word in question to all lower case, so that the comparison can run correctly
    int length = strlen(word);
    char lower_word[length];
    for (int i = 0; i < length; i++)
    {
        lower_word[i] = tolower(word[i]);
    }
    // Run the hash function on the word to find out where in our hash table we need to be looking at
    int index = hash(lower_word);
    //printf("Index of word '%s' is %i\n", lower_word, index);

    // Now loop through that part of our hash table, checking each entry in the linked list. If found, return true. Else, if
    // reaching the end of the linked list, return false
    node *head = table[index];
    //node *cursor = malloc(sizeof(node));
    if (head == NULL)
    {
        printf("Could not allocate memory to check\n");
        return 1;
    }
    //cursor = table[index];
    //printf("Cursor at beginning is %s\n", cursor->word);
    for (; head != NULL; head = head->next)
    //while (cursor != NULL)
    {
        //printf("Cursor here is %s\n", cursor->word);
        if (strcasecmp(lower_word, head->word) == 0)
        {
            free(head);
            return true;
        }
    }
    free(head);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // First iteration, just look at first letter of the given word to return the value of the hash
    // Convert the word in question to all lower case, so that the comparison can run correctly
    int length = strlen(word);
    char lower_word[length];
    for (int i = 0; i < length; i++)
    {
        lower_word[i] = tolower(word[i]);
    }
    unsigned int index = (lower_word[0] - 'a');
    return index;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open up dictionary file
    FILE *dictionary_file = fopen(dictionary, "r");

    // Exit from program if file could not be opened
    if (!dictionary_file)
    {
        return false;
    }

    // Create an array of characters to store the words from the dictionary (size of array is based on maximum defined length of a word)
    char dictionary_word[LENGTH + 1];

    // Read each line of the dictionary file. For each line, create a new node in the hash table, and store the value there
    while (fscanf(dictionary_file, "%s", dictionary_word) != EOF)
    {
        // Create a new node, allocating memory using malloc, for each word
        node *n = malloc(sizeof(node));
        // Check if malloc returns NULL or not
        if (n == NULL)
        {
            printf("Could not allocate memory using malloc\n");
            fclose(dictionary_file);
            return false;
        }

        // For this word, copy the contents of the word into the newly created node
        strcpy(n->word, dictionary_word);

        // Call our hash function to find out where in our hash table we need to store this word from the dictionary
        int x = hash(n->word);

        // Check to see if we already have words stored at this index in our hash table. If no, then add word to that index. If yes,
        // Point new word to the front of the hash table
        if(table[x] == NULL)
        {
            table[x] = n;
            n->next = NULL;
        }
        else
        {
            n->next = table[x];
            table[x] = n;
        }
        // Finally, add this entry to the dictionary count
        dictionary_count++;
    }
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // Since we have counted the dictionary entries in the load function, return dictionary_count
    return dictionary_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Loop through each bucket in our hash table, to free memory from each linked list in order
    for (int i = 0; i < N; i++)
    {
        node *cursor = malloc(sizeof(node));
        cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = malloc(sizeof(node));
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
