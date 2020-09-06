#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int temp_red = round((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue));
            int temp_green = round((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue));
            int temp_blue = round((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue));

            if (temp_red > 255)
            {
                temp_red = 255;
            }

            if (temp_green > 255)
            {
                temp_green = 255;
            }

            if (temp_blue > 255)
            {
                temp_blue = 255;
            }

            image[i][j].rgbtRed = temp_red;
            image[i][j].rgbtGreen = temp_green;
            image[i][j].rgbtBlue = temp_blue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int halfWidth = round((float)width / 2);
        for (int j = 0; j < halfWidth; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create temp array to store values temporarily
    RGBTRIPLE temp[height][width];

    // Create variables used in the calculations of the blurred number
    int sumBlue, sumGreen, sumRed;
    float counter;

    // Loop through height
    for (int i = 0; i < height; i++)
    {
        // Loop through width
        for (int j = 0; j < width; j++)
        {
            // For each pixel, set the calculation variables to 0
            sumBlue = 0;
            sumGreen = 0;
            sumRed = 0;
            counter = 0.0;

            // Check if current pixel is on the top or bottom line of image, and continue through / skip if it is
            for (int k = -1; k < 2; k++)
            {
                if (i + k < 0 || i + k > height - 1)
                {
                    continue;
                }

                // Check if current pixel is on left or right line of image, and continue through / skip if it is
                for (int l = -1; l < 2; l++)
                {
                    if (j + l < 0 || j + l > width - 1)
                    {
                        continue;
                    }

                    // Update calculation variables through each loop
                    sumBlue += image[i + k][j + l].rgbtBlue;
                    sumGreen += image[i + k][j + l].rgbtGreen;
                    sumRed += image[i + k][j + l].rgbtRed;
                    counter++;
                }
            }

            // Calculate the average for this pixel, then store it in temp
            temp[i][j].rgbtBlue = round(sumBlue / counter);
            temp[i][j].rgbtGreen = round(sumGreen / counter);
            temp[i][j].rgbtRed = round(sumRed / counter);
        }
    }

    // Copy values from the temp into the real image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }

    return;
}
