#include <cs50.h>
#include <stdio.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        int candidate_id_i = ranks[i];
        int next_rank = i + 1;
        for (next_rank; next_rank < candidate_count; next_rank++)
        {
            int candidate_id_y = ranks[next_rank]
            preferences[candidate_id_i][candidate_id_y]++
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        int y = i + 1;
        for (y; y < candidate_count; y++)
        {
            int a_votes = preferences[i][y];
            int b_votes = preferences[y][i];
            if (a_votes == b_votes)
            {
                continue;
            }
            if (a_votes > b_votes)
            {
                pairs[pair_count].winner = i
                pairs[pair_count].loser = y
            }
            else
            {
                pairs[pair_count].winner = y
                pairs[pair_count].loser = i
            }
            pair_count++
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count -1; i++)
    {
        int w_idx = pairs[i].winner;
        int l_idx = pairs[i].loser;
        int w_votes = preferences[w_idx][y_idx];
        for (int y = i + 1; y < pair_count; y++)
        {
            int cw_idx = pairs[y].winner;
            int cl_idx = pairs[y].loser;
            int c_votes = preferences[cw_idx][cl_idx];
            if (c_votes > w_votes)
            {
                pair temp_pair;
                temp_pair.winner = w_idx;
                temp_pair.loser = l_idx;
                pairs[i].winner = pairs[y].winner;
                pairs[i].loser = pairs[y].loser;
                pairs[y].winner = w_idx;
                pairs[y].loser = l_idx;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}

