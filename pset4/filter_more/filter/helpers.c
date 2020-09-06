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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temporary array (copy of the image) to store values while doing the calculations
    RGBTRIPLE temp[height][width];

    // Create gx and gy arrays for calculations
    int gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    // Create variables that will be used in the calculations
    int gxRed;
    int gxGreen;
    int gxBlue;

    int gyRed;
    int gyGreen;
    int gyBlue;

    float totalRed;
    float totalGreen;
    float totalBlue;

    // Loop through height
    for (int i = 0; i < height; i++)
    {
        // Loop through width
        for (int j = 0; j < width; j++)
        {
            // For each pixel, set the calculation variables to 0
            gxRed = 0;
            gxGreen = 0;
            gxBlue = 0;

            gyRed = 0;
            gyGreen = 0;
            gyBlue = 0;

            totalRed = 0.0;
            totalGreen = 0.0;
            totalBlue = 0.0;

            for (int k = 0; k < 3; k++)
            {
                for (int m = 0; m < 3; m++)
                {
                    if (i + k - 1 < 0 || i + k - 1 > height - 1 || j + m - 1 < 0 || j + m - 1 > width - 1)
                    {
                        continue;
                    }

                    // X Calculations
                    gxRed += image[i + k - 1][j + m - 1].rgbtRed * gx[k][m];
                    gxGreen += image[i + k - 1][j + m - 1].rgbtGreen * gx[k][m];
                    gxBlue += image[i + k - 1][j + m - 1].rgbtBlue * gx[k][m];

                    // Y Calculations
                    gyRed += image[i + k - 1][j + m - 1].rgbtRed * gy[k][m];
                    gyGreen += image[i + k - 1][j + m - 1].rgbtGreen * gy[k][m];
                    gyBlue += image[i + k - 1][j + m - 1].rgbtBlue * gy[k][m];
                }
            }

            // Final calculations for the pixel
            totalRed = round(sqrt(pow(gxRed, 2) + pow(gyRed, 2)));
            totalGreen = round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2)));
            totalBlue = round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2)));

            // Make sure none of the values are over 255
            if (totalRed > 255)
            {
                totalRed = 255;
            }

            if (totalGreen > 255)
            {
                totalGreen = 255;
            }

            if (totalBlue > 255)
            {
                totalBlue = 255;
            }

            // Add to the tempoary array
            temp[i][j].rgbtRed = totalRed;
            temp[i][j].rgbtGreen = totalGreen;
            temp[i][j].rgbtBlue = totalBlue;
        }
    }

    // Finally replace all values in the origianl image with those in temp
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }

    return;
}
