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
    // Iterate through the array and searh for an instance where the voted name matches a candidate
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            //printf("%i\n", candidates[i].votes);
            return true;
        }
    }

    // If the function reaches this point without finding a candidate and returning true, then return false to show invalid vote error message
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Iterate through the array and search for the largest number of votes

    // First create a variable to store the largest number of votes
    int winning_votes = 0;

    // Then loop through the array of candidates and find the largest number of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > winning_votes)
        {
            winning_votes = candidates[i].votes;
        }
    }

    // Now loop through the array again and print out the names of the candidates that match the winning number of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == winning_votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}

