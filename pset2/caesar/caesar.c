// A program that applies Caesar's cypher to user input

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char encrypt(char p, int k)
{
    char c = p;
    int shift = 0;
    if (isalpha(p)) // Check if aplha character
    {
        // Check case to assign shift variable
        if (isupper(p))
        {
            shift = 65;
        }
        else
        {
            shift = 97;
        }

        c = c - shift; // Concert ascii index to aphabet index
        c = (c + k) % (26); // Apply cypher formula
        c += shift; // Convert back to ascii
    }

    return c;

}

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        int k = atoi(argv[1]); // Store initial input, convert to int
        string s = get_string("plaintext: "); // Get string from user
        printf("ciphertext: ");
        // Iterate through each character of string s
        for (int i = 0, n = strlen(s); i < n; i++)
        {
            printf("%c", encrypt(s[i], k)); // Encrypt character
        }

        printf("\n");

        return 0;
    }
    else
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
}