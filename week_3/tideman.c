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
	int	i;

	i = -1;
	while (++i < candidate_count)
	{
		if (strcmp(candidates[i], name) == 0)
		{
			ranks[rank] = i;
			return (true);
		}
	}
	return (false);
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
	int	col;
	int	rank;

	rank = -1;
	while (++rank < candidate_count)
	{
		col = rank + 1;
		while (col++ < candidate_count)
			preferences[ranks[rank]][ranks[col]] += 1;
	}
	return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
	int	i;
	int	j;

	i = -1;
	while (++i < candidate_count)
	{
		j = -1;
		while (++j < candidate_count)
		{
			if (preferences[i][j] > preferences [j][i])
			{
				pair new_pair = {i, j};
				pairs[pair_count] = new_pair;
				pair_count++;
			}
		}
	}
	return;
}

int	pair_weight(int i)
{
	int	pair_w;
	int	pair_l;

	pair_w = pairs[i].winner;
	pair_l = pairs[i].loser;
	return (preferences[pair_w][pair_l]);
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
	int		i;
	int		j;
	int		min_index;
	int		min_weight;
	pair	temp;

	i = pair_count - 1;
	while (i-- >= 0)
	{
		min_weight = pair_weight(i);
		min_index = i;
		j = i - 1;
		while (j-- >= 0)
		{
			if (pair_weight(j) < min_weight)
			{
				min_weight = pair_weight(j);
				min_index = j;
			}
		}
	}
	temp = pairs[min_index];
	pairs[min_index] = pairs[i];
	pairs[i] = temp;
	return;
}

bool	has_cycle(int winner, int loser)
{
	int	i;

	i = -1;
	if (locked[loser][winner] == true)
		return (true);
	while (++i < candidate_count)
	{
		if (locked[loser][i] == true && has_cycle(winner, i))
			return (true);
	}
	return (false);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
	int	i;
	int	loser;
	int	winner;

	i = -1;
	while (++i < pair_count)
	{
		loser = pairs[i].loser;
		winner = pairs[i].winner;
		if (!has_cycle(winner, loser))
		{
			locked[winner][loser] = true;
		}
	}
	return;
}

// Print the winner of the election
void print_winner(void)
{
	int		i;
	int		j;
	int		false_count;

	i = -1;
	j = -1;
	while (++i < candidate_count)
	{
		false_count = 0;
		while (++j < candidate_count)
		{
			if (locked[i][j] == false)
			{
				false_count++;
				if (false_count == candidate_count)
					printf ("%s", candidates[i]);
			}
		}
	}
	return;
}
