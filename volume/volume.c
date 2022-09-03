// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Read header from input file
    uint8_t header[HEADER_SIZE];
    size_t read_header = fread(&header, 1, HEADER_SIZE, input);
    printf("read header %zu bytes\n", read_header);

    // Write header into output file
    size_t write_header = fwrite(&header, 1, HEADER_SIZE, output);
    printf("write header %zu bytes\n", write_header);

    // Get file lenght
    struct stat st;
    stat(argv[1], &st);
    int len = st.st_size;
    printf("file size %d bytes\n", len);

    // Read bytes from input file
    int buffer_len = len - HEADER_SIZE;
    int16_t buffer[buffer_len];
    size_t read_wav = fread(&buffer, 1, buffer_len, input);
    printf("read wav %zu bytes\n", read_wav);

    // Multiplication by a coefficient
    int16_t wav[buffer_len];
    for (int i = 0; i < buffer_len; i++)
    {
        wav[i] = buffer[i] * factor;
    }

    // Write bytes into output file
    size_t write_wav = fwrite(&wav, 1, buffer_len, output);
    printf("write wav %zu bytes\n", write_wav);

    // Close files
    fclose(input);
    fclose(output);
}