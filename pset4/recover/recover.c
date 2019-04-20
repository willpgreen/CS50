#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check user input
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // Open input file
    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // Create an outfile for the picture
    FILE *img = NULL;

    // create arrays, counter for storage
    unsigned char buffer[512];
    char outfile[8];
    int count = 0;

    // Loop until end of the memory card
    while (fread(buffer, 1, 512, inptr) == 512)
    {
        // check if first four bytes signify jpeg
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // found a jpeg

            // if not first, close prior jpeg
            if (count != 0)
            {
                fclose(img);
            }

            // open new file
            sprintf(outfile, "%03i.jpg", count);
            img = fopen(outfile, "w");
            count++;

            fwrite(&buffer, 1, 512, img);

        }
        else // didn't find a jpeg
        {
            // if already found a jpeg, write out the pixels
            if (count != 0)
            {
                fwrite(&buffer, 1, 512, img);
            }
        }
    }
    // close files
    fclose(inptr);
    fclose(img);

    return 0;
}