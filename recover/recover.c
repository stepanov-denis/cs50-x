#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>
#include <cs50.h>

const int BUFFER_SIZE = 4096;
const int BLOCK_SIZE = 512;


int main(int argc, char *argv[])
{
    // Checking the number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    // Creating a file pointer
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    // Creating buffer and some values
    uint8_t buffer[BUFFER_SIZE];
    char filename[8];
    int count_image = 0;
    int count_block = 0;
    FILE *image;
    size_t write_image;

    // Image recovery
    while (fread(&buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // Checking for the jpg file header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Checking the number of blocks in the current file
            if (count_block > 0)
            {
                // Close current file
                fclose(image);

                // Open new file in write mode
                sprintf(filename, "%03i.jpg", count_image);
                image = fopen(filename, "w");
                if (image == NULL)
                {
                    printf("Could not open file\n");
                    return 1;
                }

                write_image = fwrite(&buffer, 1, BLOCK_SIZE, image);
                if (write_image != BLOCK_SIZE)
                {
                    printf("error of writing block in file");
                    return 1;
                }
                count_image++;
                count_block++;
            }

            // Checking the number of blocks in the current file
            if (count_block == 0)
            {
                // Open new file in write mode
                sprintf(filename, "%03i.jpg", count_image);
                image = fopen(filename, "w");
                if (image == NULL)
                {
                    printf("Could not open file\n");
                    return 1;
                }

                // Write into file
                write_image = fwrite(&buffer, 1, BLOCK_SIZE, image);
                if (write_image != BLOCK_SIZE)
                {
                    printf("error of writing block in file");
                    return 1;
                }
                count_image++;
                count_block++;
            }
        }
        else
        {
            if (count_block > 0)
            {
                write_image = fwrite(&buffer, 1, BLOCK_SIZE, image);
            }
        }
    }
    fclose(image);
    fclose(file);
}