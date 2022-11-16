#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int		compute_score(string word);

int		main(void)
{
	// Get input words from both players
	string word1 = get_string("Player 1: ");
	string word2 = get_string("Player 2: ");

	// Score both words
	int score1 = compute_score(word1);
	int score2 = compute_score(word2);

	// TODO: Print the winner
	if (score1 > score2)
		printf("Player 1 wins!\n");
	else if (score1 == score2)
		printf("Tie!\n");
	else
		printf("Player 2 wins!\n");
	return (0);
}

int		compute_score(string word)
{
	// TODO: Compute and return score for string
	int		i;
	int		j;
	int		score;
	char	abc[27];

	i = -1;
	while (++i < 26)
		abc[i] = 'A' + i;
	abc[i] = '\0';
	i = -1;
	score = 0;
	while (abc[++i])
	{
		j = -1;
		while (word[++j])
		{
			if (abc[i] == toupper(word[j]))
			{
				score += POINTS[i];
			}
			else
				score += 0;
		}
	}
	return (score);
}
