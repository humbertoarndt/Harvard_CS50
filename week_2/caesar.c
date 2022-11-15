#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Check is a string is formed for digits only.
 *
 * @param txt The string to be checked.
 * @return true if the string only contains digits, or false if a
 *  no digit is found.
*/
bool	only_digits(string txt)
{
	while (*txt)
	{
		if (*txt < 48 || *txt++ > 57)
		{
			printf("Usage: ./caesar key\n");
			return (false);
		}
	}
	return (true);
}

/**
 * @brief Rotates a char upwards by the given key.
 *
 * @param c Char to rotate.
 * @param key Int value to rotate.
 * @return If is a letter return the rotated char, else return the char.
*/
char	rotate(char c, int key)
{
	int	n_key;

	if	(key > 26)
		n_key = key % 26;
	else
		n_key = key;
	if (isupper(c))
	{
		if (c + n_key > 90)
		{
			return (((c + n_key) - 90) + 64);
		}
		return (c + n_key);
	}
	else if (islower(c))
	{
		if (c + n_key > 122)
		{
			return (((c + n_key) - 122) + 96);
		}
		return (c + n_key);
	}
	else
		return (c);
}

int main(int argc, string argv[])
{
	int		i;
	int		key;
	char	*txt;

	if (argc != 2)
	{
		printf("Usage: ./caesar key\n");
		return (1);
	}
	else if (only_digits(argv[1]))
	{

		key = atoi(argv[1]);
		txt = get_string("plaintext: ");
		printf("ciphertext: ");
		i = -1;
		while (txt[++i])
		{
			printf("%c", rotate(txt[i], key));
		}
		printf("\n");
	}
	else
		return (1);
	return (0);
}
