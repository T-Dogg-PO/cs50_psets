#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check that only one command line argument is provided
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }


    // Attempt to open the provided file
    FILE *file = fopen(argv[1], "r");

    // Exit program if the file could not be opened
    if (!file)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    // Create output file placeholder for recovered images, making sure to initalize it to NULL
    FILE *img = NULL;

    // Create arrays for the 512 bytes of every block we are checking and for the file name
    unsigned char buffer[512];
    char filename[8];

    // Create a counter for the filename
    int counter = 0;

    // Read the file (store data in buffer, read 512 bytes at a time, read them once,
    // read from file). Because our number argument is 1 (we are reading 1 element of
    // 512 bytes at a time), fread should return 1 each time. If we are unable to read
    // 512 bytes, then it should return 0 (as it will read 0 elements of size 512)
    while (fread(buffer, 512, 1, file) == 1)
    {
        // Check the first 4 bytes of the buffer array to see if we are at the start of a jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If img is anything other than NULL, we are not on our first JPG, which means we
            // then close the previous img
            if (img != NULL)
            {
                fclose(img);
            }

            // Print (to a string) the filename of the file we are creating for this JPEG
            sprintf(filename, "%03i.jpg", counter);
            // Open a new img file with that filename
            img = fopen(filename, "w");
            // Add one to our filename counter
            counter++;
        }

        // If img has been created (i.e. we have found our fist JPG), then write to the img
        // using the data from current section of the file
        if (img != NULL)
        {
            fwrite(&buffer, 512, 1, img);
        }
    }

    // End of program, so close any open files we have
    fclose(img);
    fclose(file);
}
