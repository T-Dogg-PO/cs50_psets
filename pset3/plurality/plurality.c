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
    // Check to see if the name matches one of the candidates. If yes, add a vote
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }

    // Else return false
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Create a variable to store the current highest number of votes while we search for the highest
    int current_highest = 0;

    // Loop through the candidates.votes array to find the highest number
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > current_highest)
        {
            current_highest = candidates[i].votes;
        }
    }

    // Create a second loop to print out all of the candidates that match the current_highest
    for (int i = 0; i < candidate_count; i++)
    {
        if (current_highest == candidates[i].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}

