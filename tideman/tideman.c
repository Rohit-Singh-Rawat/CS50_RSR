#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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


int lo = 0;
pair locker[MAX * (MAX - 1) / 2] = {};
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
    for (int i = 0;  i < candidate_count; i++)
    {
        for (int j = i + 1;  j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int n = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[n].winner = i;
                pairs[n].loser = j;
                n++;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[n].winner = j;
                pairs[n].loser = i;
                n++;
                pair_count++;
            }

        }

    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{

    pair swap;

    int swap_p = 0;

    for (int j = 0; j < pair_count; j++)
    {
        int strength = 0;
        for (int i = j; i < pair_count; i++)
        {
            if (abs(preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner]) > strength)
            {
                strength = abs(preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner]);
                swap_p = i;
            }
            if (abs(preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner]) == strength)
            {
                if (pairs[i].winner < pairs[j].winner)
                {
                    swap_p = i;
                }
            }

        }

        swap = pairs[j];
        pairs[j] = pairs[swap_p];
        pairs[swap_p] = swap;


    }

    return;
}
// Function to check for cycle in a continous chain
bool is_cycle(int index, bool searched[])
{
    if (searched[index])
    {
        return true;
    }
    searched[index] = true;
    for (int i = 0; i < candidate_count; i++)
    {
        // Here, we check for each term connected to to a certain index thus forming internal chain until it showes false
        if (locked[index][i] && is_cycle(i, searched))
        {
            return true;
        }
    }
    return false;
}
// Function to initial make  list for position we have searched as false
bool has_cycle(int initial)
{
    bool searched[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        searched[i] = false;

    }
    return is_cycle(initial, searched);
}

// Lock pairs into the candidate graph in order, without creating cycles


void lock_pairs(void)
{
    int i;
    for (i = 0; i < pair_count; i++)
    {

        locked[pairs[i].winner][pairs[i].loser] = true;
        if (has_cycle(pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }

    }
}

// Print the winner of the election
void print_winner(void)
{
// Going through each element inside a 2d array of locked
    for (int i = 0; i < candidate_count; i++)
    {
        int q = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                q++;
            }
        }
        // Judging the final candidate who have no winner upper to them
        if (q == candidate_count)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}