// Implements a dictionary's functionality

#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

typedef struct
{
    node **array;
    unsigned int array_size;
    unsigned int num_elements;
} hash_table;

hash_table *table;

// ----------------------------------------------------------------------------------

int count_lines(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        // printf("Failed to open file: %s\n", filename);
        return -1;
    }

    int num_lines = 0;
    char chunk[LENGTH + 2];
    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {
        num_lines++;
    }
    fclose(file);

    return num_lines;
}

bool initialize_hash_table(unsigned int size)
{
    table = malloc(sizeof(hash_table));
    if (table == NULL)
    {
        // printf("Error: Memory allocation failed for table.\n");
        return false;
    }
    table->array_size = size;
    table->num_elements = 0;

    table->array = calloc(size, sizeof(node *));
    if (table->array == NULL)
    {
        // printf("Error: Memory allocation failed for table's array.\n");
        free(table);
        return false;
    }
    return true;
}

bool populate_hashtable(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        // printf("Failed to open file: %s\n", dictionary);
        return false;
    }
    char chunk[LENGTH + 2];
    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {

        chunk[strcspn(chunk, "\n")] = 0;
        int length = strlen(chunk);

        unsigned int index = hash(chunk);

        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            // unload
            fclose(file);
            return false;
        }

        strcpy(n->word, chunk);
        n->next = table->array[index];
        table->array[index] = n;
        table->num_elements++;
    };
    fclose(file);
    return true;
}

// ----------------------------------------------------------------------------------

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int index = hash(word);

    if (table->array[index] == NULL)
    {
        return false;
    }

    int word_match = strcasecmp(table->array[index]->word, word);
    if (word_match == 0)
    {
        return true;
    }
    node *ptr = table->array[index]->next;
    while (ptr != NULL)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

// Hashes word to a number

unsigned int hash(const char *word)
{
    char word_lower[LENGTH + 1];
    int i;
    for (i = 0; word[i] != '\0'; i++)
    {
        word_lower[i] = tolower(word[i]);
    }
    word_lower[i] = '\0';

    unsigned long hash = 5381;
    int c;

    i = 0; // Reset i to 0

    while ((c = word_lower[i++]))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    unsigned int index = hash % table->array_size;
    return index;
}

bool load(const char *dictionary)
{
    int num_lines = count_lines(dictionary);
    if (num_lines == -1)
    {
        return false;
    }
    int array_size = num_lines * 2;

    bool is_initialized = initialize_hash_table(array_size);
    if (!is_initialized)
    {
        return false;
    }

    bool is_populated = populate_hashtable(dictionary);

    /* printf("Hash Table Contents:\n");
    for (unsigned int i = 0; i < table->array_size; i++)
    {
        node *current = table->array[i];
        printf("Bucket %u: ", i);
        while (current != NULL)
        {
            printf("%s -> ", current->word);
            current = current->next;
        }
        printf("NULL\n");
    } */

    return is_populated;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return table->num_elements;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (unsigned int i = 0; i < table->array_size; i++)
    {
        node *ptr = table->array[i];
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }
    free(table->array);
    free(table);
    return true;
}
