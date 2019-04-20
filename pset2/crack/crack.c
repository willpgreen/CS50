// A program that cracks passwords

#define _XOPEN_SOURCE
#include <unistd.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[])
{
    // Check user input
    if (argc == 2)
    {
        // Declare variables
        char key[6]; // Key is a char array to store the output
        key[0] = 'A';
        key[5] = '\0';

        // Store users input, the hashed password
        string hash = argv[1];

        // The first two characters of the hashed password are the salt
        char salt[2];
        salt[0] = argv[1][0];
        salt[1] = argv[1][1];

        // Run outer while loop until crypted key matches hash
        while (strcmp(crypt(key, salt), hash) != 0)
        {
            // Go to next letter for first character
            key[0]++;

            // Loop through each char in key, increment ith char
            // if previous is char has reached z
            for (int i = 1; i < 5; i++)
            {
                // Check previous character
                if (key[i - 1 ] == 'z' + 1)
                {
                    // Reset previous character to A
                    key[i - 1] = 'A';

                    // Check ith character, increment if already set and not after z
                    if (key[i] >= 'A' && key[i] < 'z' + 1)
                    {
                        key[i]++;

                        // Jump over punctuation characters
                        if (key[i] == '[')
                        {
                            key[i] = 'a';
                        }
                    }
                    // Set ith character A if not previously set, or after z
                    else
                    {
                        key[i] = 'A';
                    }
                }
            }
            // Jump over punctuation characters (1st char)
            if (key[0] == '[')
            {
                key[0] = 'a';
            }
        }

        // Print password
        printf("%s\n", key);

        return 0;
    }
    else
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
}