#include <cs50.h>
#include <math.h>
#include <stdio.h>

/**
 * @brief Count the number of letter at a given string.
 *
 * @param txt String to travel.
 * @return The number of letter.
*/
int	count_letter(string txt)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (txt[++i] != '\0')
	{
		if ((txt[i] >= 65 && txt[i] <= 90) || (txt[i] >= 97 && txt[i] <= 122))
			count++;
	}
	return (count);
}

/**
 * @brief Count the number of words at a given string.
 *
 * @param txt String to travel.
 * @return The number of words.
*/
int	count_word(string txt)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (txt[++i] != '\0')
	{
		if (txt[i] == ' ' || txt[i+1] == '\0')
			count++;
	}
	return (count);
}

/**
 * @brief Count the number of sentences at a given string.
 *
 * @param txt String to travel.
 * @return The number of senteces.
*/
int	count_sentences(string txt)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (txt[++i] != '\0')
	{
		if (txt[i] == 33 || txt[i] == 46 || txt[i] == 63)
			count++;
	}
	return (count);
}

/**
 * @brief Calculates Coleman-Liau index o a text given by user input.
*/
int main(void)
{
	char	*txt;
	int		grade;
	float	avg_l;
	float	avg_s;

	txt = get_string("Text: ");
	avg_l = ((float)count_letter(txt) / (float)count_word(txt)) * 100;
	avg_s = ((float)count_sentences(txt) / (float)count_word(txt)) * 100;
	grade = round(0.0588 * avg_l - 0.296 * avg_s - 15.8);

	if (grade < 1)
		printf("Before Grade 1\n");
	else if (grade >= 16)
		printf("Grade 16+\n");
	else
		printf("Grade %i\n", grade);
	return (0);
}