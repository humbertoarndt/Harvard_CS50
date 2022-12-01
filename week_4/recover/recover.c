#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
	BYTE	buffer[512];
	int		count;
	FILE	*file;
	FILE	*img;
	char	files[8];
	char	*file_name;

	if (argc != 2)
	{
		printf("Usage: ./recover <file>\n");
		return (1);
	}
	file_name = argv[1];
	file = fopen(file_name, "r");
	if (file == NULL)
	{
		printf("Error: cannot open %s\n.", file_name);
		return (1);
	}
	count = 0;
	img = NULL;
	// Repeat until EOF
	while (fread(&buffer, 512, 1, file) == 1)
	{
		// Check the JPEG start
		if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
		{
			// Close previous image
			if (!(count == 0))
				fclose(img);
			// Initialise file
			sprintf(file_name, "%03i.jpg", count);
			img = fopen(file_name, "w");
			count++;
		}
		// Write a new JPG when its found
		if (!(count == 0))
			fwrite(&buffer, 512, 1, img);
	}
	// Close files
	fclose(file);
	fclose(img);
	return (0);
}
