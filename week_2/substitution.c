#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/**
 * @brief Checks if a string key contains 26 characters, only letters
 * and no duplicated chars.
 * 
 * @param txt The key to be checked.
 * @return true if the key is valid.
 * @return false if the key is invalid.
 */
bool	check_key(char *txt)
{
	int		i;
	int		j;
	char	*buffer;

	buffer = txt;
	if (strlen(txt) != 26)
	{
		printf("Key must contain 26 characters\n");
		return (false);
	}
	while (*txt)
	{
		if ((*txt < 65 || *txt > 90) && (*txt < 97 || *txt > 122))
		{
			printf("Key must contain only letters\n");
			return (false);
		}
		txt++;
	}
	i = -1;
	while (buffer[++i] != '\0')
	{
		j = i;
		while (buffer[++j] != '\0')
		{
			if (toupper(buffer[i]) == toupper(buffer[j]))
			{
				printf("Key must not contain duplicated letters\n");
				return (false);
			}
		}
	}
	return (true);
}

/**
 * @brief Creates and array with the uppercase alphabet.
 * 
 * @return char* Array with the uppercase alphabet.
 */
char	*set_abc(void)
{
	int	i;
	char	abc[27];

	i = -1;
	while (++i < 26)
		abc[i] = 'A' + i;
	abc[i] = '\0';
	return(abc);
 }

/**
 * @brief Replaces the given char accordingly by the the given key.
 * 
 * @param c The char to be replaced.
 * @param key The encrypt key.
 * @return char The new encrypted char.
 */
char	rotate(char c, char *key)
{
	int		i;
	char	*abc;
	char	*buffer_key;

	buffer_key = key;
	while (*buffer_key)
	{
		*buffer_key = toupper(*buffer_key);
		buffer_key++;
	}
	abc = set_abc();
	i = -1;
	while (abc[++i])
	{
		if (c == abc[i])
			return(key[i]);
	}
	return (c);
}

/**
 * @brief The program to encrypt a given message by a given key
 * by command line.
 * 
 * @param argc ./substitution
 * @param argv <26-characters key>
 * @return int 0 if the program executes, or 1 when the program do not execute.
 */
int main(int argc, string argv[])
{
	int		i;
	char	*txt;

	if (argc != 2)
	{
		printf("Usage: ./substitution key\n");
		return (1);
	}
	else if (check_key(argv[1]))
	{
		txt = get_string("plaintext: ");
		printf("ciphertext: ");
		i = -1;
		while (txt[++i])
		{
			if (isupper(txt[i]))
				printf("%c", rotate(txt[i], argv[1]));
			else if (islower(txt[i]))
				printf("%c", tolower(rotate(toupper(txt[i]), argv[1])));
			else
				printf("%c", txt[i]);
		}
		printf("\n");
		return (0);
	}
	else
		return (1);
}
