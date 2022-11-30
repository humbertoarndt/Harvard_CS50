#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
	int	i	;
	int		j;
	double avg;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			avg = round((image[i][j].rgbtRed +
				 image[i][j].rgbtGreen +
				 image[i][j].rgbtBlue) / 3.0);

				image[i][j].rgbtRed = avg;
				image[i][j].rgbtGreen = avg;
				image[i][j].rgbtBlue = avg;
		}
	}
	return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
	int	i;
	int	j;
	int	red;
	int	green;
	int	blue;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			red = round((float)(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue));
			green = round((float)(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue));
			blue = round((float)(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue));
			image[i][j].rgbtRed = (red > 255) ? 255 : red;
			image[i][j].rgbtGreen = (green > 255) ? 255 : green;
			image[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
		}
	}
	return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
	int			i;
	int			j;
	RGBTRIPLE	temp;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width / 2)
		{
			temp = image[i][j];
			image[i][j] = image[i][width - j - 1];
			image[i][width - j - 1] = temp;
		}
	}
	return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
	int			i;
	int			j;
	int			k;
	int			l;
	int			counter;
	float		sum_r;
	float		sum_g;
	float		sum_b;
	RGBTRIPLE	img_cpy[height][width];

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
			img_cpy[i][j] = image[i][j];
	}
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			sum_r = 0;
			sum_g = 0;
			sum_b = 0;
			counter = 0;
			k = -2;
			while (++k < 2)
			{
				l = -2;
				while (++l < 2)
				{
					if (i + k < 0 || i + k >= height)
						continue;
					if (j + l < 0 || j + l >= width)
						continue;
					sum_r += img_cpy[i + k][j + l].rgbtRed;
					sum_g += img_cpy[i + k][j + l].rgbtGreen;
					sum_b += img_cpy[i + k][j + l].rgbtBlue;
					counter++;
				}
			}
			image[i][j].rgbtRed = round(sum_r / counter);
			image[i][j].rgbtGreen = round(sum_g / counter);
			image[i][j].rgbtBlue = round(sum_b / counter);
		}
	}
	return;
}
