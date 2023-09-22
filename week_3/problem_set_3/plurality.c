#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++) 
    {
        int y = i;

        candidate temp;
        temp.name = candidates[i].name;
        temp.votes = candidates[i].votes;
        int temp_index = -1;

        for (y; y < candidate_count; y++) 
        {
            if (temp.votes < candidates[y].votes)
            {
                temp.name = candidates[y].name;
                temp.votes = candidates[y].votes;
                temp_index = y;
            }
        }
        if (temp_index >= 0)
        {
            candidates[temp_index].name = candidates[i].name;
            candidates[temp_index].votes = candidates[i].votes;

            candidates[i].name = temp.name;
            candidates[i].votes = temp.votes;
        }
    }
    int winner_votes = candidates[0].votes;
    if (winner_votes == 0)
    {
        return;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes != winner_votes)
        {
            continue;
        }
        printf("%s\n", candidates[i].name);
    }
    return;
}

// gcc -o plurality plurality.c -lcs50
