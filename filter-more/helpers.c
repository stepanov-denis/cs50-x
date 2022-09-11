#include "helpers.h"
#include "math.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int blue;
    int green;
    int red;
    float average;
    int round_average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blue = image[i][j].rgbtBlue;
            green = image[i][j].rgbtGreen;
            red = image[i][j].rgbtRed;
            average = (blue + green + red) / 3.00;
            round_average = roundf(average);
            image[i][j].rgbtBlue = round_average;
            image[i][j].rgbtGreen = round_average;
            image[i][j].rgbtRed = round_average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int len;
    RGBTRIPLE first_buff;
    RGBTRIPLE second_buff;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            len = width - j - 1;
            first_buff = image[i][j];
            second_buff = image[i][len];
            image[i][j] = second_buff;
            image[i][len] = first_buff;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create copy of image array
    RGBTRIPLE copy_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy_image[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red;
            float blue;
            float green;
            int counter;
            red = blue = green = counter = 0;

            // For each pixel, loop vertical and horizontal
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Check if pixel is outside rows
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    // Check if pixel is outside columns
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }
                    // Otherwise add to sums
                    red += copy_image[i + k][j + l].rgbtRed;
                    blue += copy_image[i + k][j + l].rgbtBlue;
                    green += copy_image[i + k][j + l].rgbtGreen;
                    counter++;
                }
            }
            // Get average and blur image
            image[i][j].rgbtRed = round(red / counter);
            image[i][j].rgbtGreen = round(green / counter);
            image[i][j].rgbtBlue = round(blue / counter);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create copy of image array
    RGBTRIPLE copy_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy_image[i][j] = image[i][j];
        }
    }

    // Initialise Sobel arrays
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Loop through rows
    for (int i = 0; i < height; i++)
    {
        // Loop through columns
        for (int j = 0; j < width; j++)
        {
            // Initialise ints
            float gx_red;
            float gx_blue;
            float gx_green;
            float gy_red;
            float gy_blue;
            float gy_green;
            gx_red = gx_blue = gx_green = gy_red = gy_blue = gy_green = 0;

            // For each pixel, loop vertical and horizontal
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Check if pixel is outside rows
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }

                    // Check if pixel is outside columns
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }

                    // Otherwise add to sums
                    gx_red += copy_image[i + k][j + l].rgbtRed * gx[k + 1][l + 1];
                    gx_green += copy_image[i + k][j + l].rgbtGreen * gx[k + 1][l + 1];
                    gx_blue += copy_image[i + k][j + l].rgbtBlue * gx[k + 1][l + 1];
                    gy_red += copy_image[i + k][j + l].rgbtRed * gy[k + 1][l + 1];
                    gy_green += copy_image[i + k][j + l].rgbtGreen * gy[k + 1][l + 1];
                    gy_blue += copy_image[i + k][j + l].rgbtBlue * gy[k + 1][l + 1];
                }
            }

            // Calculate Sobel operator
            int red = round(sqrt(gx_red * gx_red + gy_red * gy_red));
            int green = round(sqrt(gx_green * gx_green + gy_green * gy_green));
            int blue = round(sqrt(gx_blue * gx_blue + gy_blue * gy_blue));

            // Cap at 255
            if (red > 255)
            {
                red = 255;
            }

            if (green > 255)
            {
                green = 255;
            }

            if (blue > 255)
            {
                blue = 255;
            }

            // Assign new values to pixels
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}
