// A program that applies Caesar's cypher to user input

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// A function that checks whether a string contains only alphabetical characters
bool check_alpha(string s)
{
    // Initialize variables
    bool b;
    int n = strlen(s);

    // Check that s is not empty
    if (n > 0)
    {
        b = true;
        // Iterate through each char in s and check if alpha
        for (int i = 0; i < n; i++)
        {
            if (isalpha(s[i]))
            {
                b = b && true;
            }
            else
            {
                b = b && false;
            }
        }
    }
    else
    {
        b = false;
    }
    return b;
}

// A function that encrpyts a char p based off value of char k
char encrypt(char p, char k)
{
    char c = p;
    int shift = 0;
    if (isalpha(p)) // Check if aplha character
    {
        // Check case to assign shift variable
        if (isupper(p))
        {
            k = toupper(k);
            shift = 65;
        }
        else
        {
            k = tolower(k);
            shift = 97;
        }
        // Convert from ascii to alpha index
        k = k - shift;
        c = c - shift;
        // Apply formula
        c = (c + k) % 26;
        // Convert back to ascii
        c += shift;
    }
    return c;
}

int main(int argc, string argv[])
{
    if (argc == 2 && check_alpha(argv[1]))
    {
        string key = argv[1]; // Store key provided by user
        string s = get_string("plaintext: "); // Get string from user

        printf("ciphertext: ");
        // Iterate through each character of string s
        for (int i = 0, j = 0, n = strlen(s), o = strlen(key); i < n; i++)
        {
            // Check if char is alpha, if so encrypt and increment j
            if (isalpha(s[i]))
            {
                printf("%c", encrypt(s[i], key[j])); // Encrypt character
                j = (j + 1) % o;
            }
            else
            {
                printf("%c", s[i]);
            }
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