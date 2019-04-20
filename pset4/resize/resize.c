// Copies a BMP file
 #include <stdio.h>
#include <stdlib.h>
 #include "bmp.h"
 int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }
     // remember filenames and factor
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];
     // check user input
    if (n < 1 || n > 100)
    {
        fprintf(stderr, "Usage: Please provide an int between 1 and 100\n");
        return 1;
    }
     // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
     // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
     // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
     // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
     // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
     // determine padding of original file
    int old_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int old_biWidth = bi.biWidth;
    int old_biHeight = bi.biHeight;
     // recalculate width and height for header
    bi.biWidth *= n;
    bi.biHeight *= n;
     // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
     // recalculate biSizeImage and bfSize
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
     // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
     // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
     // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(old_biHeight); i < biHeight; i++)
    {
        for (int z = 0; z < n; z++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < old_biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
                 // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                 // write RGB triple to outfile n times
                for (int k = 0; k < n; k++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    printf("pix");
                 }
            }
             // skip over padding in original file, if any
            fseek(inptr, old_padding, SEEK_CUR);
             // then add it back (adjusted for new size)
            for (int p = 0; p < padding; p++)
            {
                 fputc(0x00, outptr);
                 printf("pad");
            }
            printf("\n");
             // set pointer back
            if (z < n - 1)
            {
                fseek(inptr, (old_biWidth * -3) - old_padding, SEEK_CUR);
            }
        }
    }
     // close infile
    fclose(inptr);
     // close outfile
    fclose(outptr);
     // success
    return 0;
}