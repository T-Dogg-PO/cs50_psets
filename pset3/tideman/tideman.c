#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
    // Cycle through the list of candidates to match the votes name, the update ranks[i] with vote
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
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
    // Cycle through the ranks array, updating the preferences array. Continue cycling through to update
    // ranked preferences for every candidate
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Cycle through the preferences to find where one is preferred over the other. Add
    // pairs to the array, and update the pair count every time this is done successfully
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; i++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[i].winner = i;
                pairs[i].loser = j;
                pair_count++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int current_highest;
    pair pairs_placeholder[MAX * (MAX - 1) / 2];

    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {

            if (preferences[pairs[i].winner][pairs[i].loser] > current_highest)
            {
                current_highest = preferences[pairs[i].winner][pairs[i].loser];
            }

            if (preferences[pairs[j].winner][pairs[j].loser] == current_highest)
            {
                pairs_placeholder[i].winner = pairs[j].winner;
                pairs_placeholder[i].loser = pairs[j].loser;
                pairs[j].winner = 0;
                break;
            }
        }
    }

    for (int k = 0; k < pair_count; k++)
    {
        pairs_placeholder[k].winner = pairs[k].winner;
        pairs_placeholder[k].loser = pairs[k].loser;
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Create the locked matrix, making sure there are no reverse pairings
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (!locked[pairs[i].winner][pairs[i].loser] && !locked[pairs[i].loser][pairs[i].winner] && i != j)
            {
                locked[pairs[i].winner][pairs[i].loser] = true;
            }
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    int current_winner = 0;
    bool found_winner = false;

    // Print out the winner of the election by making a count of true
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true)
            {
                found_winner = false;
                break;
            }
            else
            {
                found_winner = true;
            }
        }
        if (found_winner == true)
        {
            current_winner = i;
        }
    }

    printf("%s\n", candidates[current_winner]);

    return;
}

