#include "helpers.h"
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
	int			i;
	int			j;
	int			k;
	int			l;
	int			red;
	int			green;
	int			blue;
	// Sobel Array
	int			gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
	int 		gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
	float		gx_r;
	float		gx_g;
	float		gx_b;
	float		gy_r;
	float		gy_g;
	float		gy_b;
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
			gx_r = 0;
			gx_g = 0;
			gx_b = 0;
			gy_r = 0;
			gy_g = 0;
			gy_b = 0;
			k = -2;
			while (++k < 2)
			{
				l = -2;
				while (++l < 2)
				{
					// Check if pixel is outside rows
					if (i + k < 0 || i + k >= height)
						continue;
					// Check if pixel is outside columns
					if (j + l < 0 || j + l >= width)
						continue;
					gx_r += img_cpy[i + k][j + l].rgbtRed * gx[k + 1][l + 1];
					gx_g += img_cpy[i + k][j + l].rgbtGreen * gx[k + 1][l + 1];
					gx_b += img_cpy[i + k][j + l].rgbtBlue * gx[k + 1][l + 1];
					gy_r += img_cpy[i + k][j + l].rgbtRed * gy[k + 1][l + 1];
					gy_g += img_cpy[i + k][j + l].rgbtGreen * gy[k + 1][l + 1];
					gy_b += img_cpy[i + k][j + l].rgbtBlue * gy[k + 1][l + 1];
				}
			}
			// Calculate Sobel operator
			red = round(sqrt(gx_r * gx_r + gy_r * gy_r));
			green = round(sqrt(gx_g * gx_g + gy_g * gy_g));
			blue = round(sqrt(gx_b * gx_b + gy_b * gy_b));
			image[i][j].rgbtRed = (red > 255) ? 255 : red;
			image[i][j].rgbtGreen = (green > 255) ? 255 : green;
			image[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
		}
	}
	return;
}
