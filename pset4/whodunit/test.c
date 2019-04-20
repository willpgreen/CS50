#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(void)
{
    int padding = (4 - (3 * sizeof(RGBTRIPLE)) % 4) % 4;
    printf("%i\n", padding);
}
