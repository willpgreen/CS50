// Prints out a double half-pyramid of specified height

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get user input and check it is in range
    int x = 0;
    do
    {
        x = get_int("Enter height: ");
    }
    while (x < 0 || x > 23);

    // Loop through each row of tower
    for (int i = 0; i < x; i++)
    {
        // Print out spaces
        for (int j = i + 1; j < x; j++)
        {
            printf(" ");
        }

        // Print out blocks in left column
        for (int k = x - i; k <= x; k++)
        {
            printf("#");
        }
        /*
        // Print out gap between column
        printf("  ");

        // Print out blocks in right column
        for (int k = x - i; k <= x; k++)
        {
            printf("#");
        }
        */

        // Move to new line
        printf("#\n");
    }

}