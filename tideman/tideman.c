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
// the function returns true if the rank was successfully recorded, and false otherwise
bool vote(int rank, string name, int ranks[])
{
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
// the function updates the global preference array to add the preferences of the current voter
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
// the function adds all pairs of candidates, where one candidate is preferred, to an array of pairs
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pair p = { .winner = i, .loser = j };
                pairs[pair_count] = p;
                pair_count++;
            }
            if (preferences[j][i] > preferences[i][j])
            {
                pair p = { .winner = j, .loser = i };
                pairs[pair_count] = p;
                pair_count++;
            }

        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
// the function sorts an array of pairs in descending order of the strength of victory,
// where the strength of victory is defined as the number of voters giving preference
// to the preferred candidate
void sort_pairs(void)
{
    int index = pair_count - 2;
    for (int j = 0; j < index; j++)
    {
        for (int i = 0; i < index; i++)
        {
            int winner_1 = pairs[i].winner;
            int loser_1 = pairs[i].loser;
            int preference_1 = preferences[winner_1][loser_1];

            int winner_2 = pairs[i + 1].winner;
            int loser_2 = pairs[i + 1].loser;
            int preference_2 = preferences[winner_2][loser_2];

            if (preference_1 < preference_2)
            {
                pair first_pair = pairs[i];
                pair second_pair = pairs[i + 1];
                pairs[i] = second_pair;
                pairs[i + 1] = first_pair;
            }
        }
        index--;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int count = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                count++;
                if (count == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
    return;
}

// Checking cycle
bool check_cycle(int los, int win)
{
    if (los == win)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[los][i])
        {
            if (check_cycle(i, win))
            {
                return true;
            }
        }
    }
    return false;
}

// The function creates a blocked graph by adding all edges in descending order
// of the winning power until the edge creates a cycle
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;
        if (!check_cycle(loser, winner))
        {
            locked[winner][loser] = true;
        }
    }
    return;
}