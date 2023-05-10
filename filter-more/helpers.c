#include "helpers.h"

#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //taking average of RGB values for each pixel
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / (float)3);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }

    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width / 2; j++)
        {
            // Swaping elements to make reflection
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
    // Create temp array
    RGBTRIPLE temp_i[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp_i[i][j] = image[i][j];
        }
    }
    //Going through each element
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avgr = 0, avgg = 0, avgb = 0, temp = 0 ;
            for (int m = i - 1; m < i + 2; m++)
            {
                for (int n = j - 1; n < j + 2; n++)
                {
                    if (m > -1 && n > -1 && m < height && n < width)
                    {
                        avgr += image[m][n].rgbtRed;
                        avgg += image[m][n].rgbtGreen;
                        avgb += image[m][n].rgbtBlue;
                        temp++;
                    }
                }
            }
            //Takes average of each neighbouring unit
            avgr = round(avgr / (float)temp);
            avgg = round(avgg / (float)temp);
            avgb = round(avgb / (float)temp);

            temp_i[i][j].rgbtBlue = avgb;
            temp_i[i][j].rgbtGreen = avgg;
            temp_i[i][j].rgbtRed = avgr;
        }
    }
    //putting value to back to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp_i[i][j] ;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create temp array
    RGBTRIPLE temp_i[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp_i[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avgrx = 0, avggx = 0, avgbx = 0, temp = 0 ;
            int avgry = 0, avggy = 0, avgby = 0;
            int gx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
            int gy[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1}; //intitalising each vlaue to zero
            for (int m = i - 1; m < i + 2; m++)
            {
                for (int n = j - 1; n < j + 2; n++)
                {
                    if (m > -1 && n > -1 && m < height && n < width)
                    {
                        avgrx += image[m][n].rgbtRed * gx[temp];
                        avggx += image[m][n].rgbtGreen * gx[temp];
                        avgbx += image[m][n].rgbtBlue * gx[temp]; // making values using sobel operator
                        avgry += image[m][n].rgbtRed * gy[temp];
                        avggy += image[m][n].rgbtGreen * gy[temp];
                        avgby += image[m][n].rgbtBlue * gy[temp];


                    }
                    temp++;
                }
            }


            float avgr = round(sqrt(pow(avgrx, 2) + pow(avgry, 2))); // finding each of unit using sborl operator
            float avgb = round(sqrt(pow(avgbx, 2) + pow(avgby, 2)));
            float avgg = round(sqrt(pow(avggx, 2) + pow(avggy, 2)));
            if (avgr > 255)// setting cap for RGB vaue exceding 255
            {
                avgr = 255;
            }
            if (avgb > 255)
            {
                avgb = 255;
            }
            if (avgg > 255)
            {
                avgg = 255;
            }

            temp_i[i][j].rgbtBlue = (int)avgb;
            temp_i[i][j].rgbtGreen = (int)avgg;
            temp_i[i][j].rgbtRed = (int)avgr;

        }
    }
    // puuting back into images
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp_i[i][j] ;
        }
    }
    return;
}
