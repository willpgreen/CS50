#define _XOPEN_SOURCE
#include <unistd.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    // Declare variables
    char key[6];
    key[0] = 'A';
    key[5] = '\0';
    int count = 0;


    string test = "hahah";

    // Run outer while loop until key matches word
    while (strcmp(key, test) != 0)
    {



        // print to test current state of key
        ///printf("%s\n", key);

        // Go to next letter for first character
        key[0]++;

        // Loop through each character in key
        // Increment next characters
        // if previous one is past z
        for (int i = 1; i < 5; i++)
        {
            // Check previous character
            if (key[i-1] == 'z'+1)
            {
                // Check
                // printf("reset %i should happen here\n", i);

                // Reset previous character to A
                key[i-1] = 'A';

                // Check ith character, increment if already set and not past z
                if (key[i] >= 'A' && key[i] < 'z'+1)
                {
                    key[i]++;

                    // Jump over punctuation characters
                    if (key[i] == '[')
                    {
                        key[i] = 'a';
                    }
                }
                // Set ith character A if not previously set, or if past z
                else
                {
                    key[i] = 'A';
                }

                // place \0 at end of string
            }
        }
        // Jump over punctiation characters
        if (key[0] == '[')
        {
            key[0] = 'a';
        }

        //printf("While loop pass %i\n", count);
        count++;
        //if (count > 1432)
        //{
        //    break;
        //}
        //if (count == 1430)
        //{
          //  printf("key: %s\n", key);
            //printf("%d\n", strcmp(key, test));
        //}
        if (strcmp(key, "zzzzz") == 0)
        {
           break;
        }

    }
    printf("The key is %s\n", key);

    ///char test_key[6];
    ///test_key[0] = 'a';
    ///test_key[1] = 'a';
    ///test_key[2] = '\0';

    ///printf("test: %s\n", test);
    ///printf("test key: %s\n", test_key);
    ///printf("%d\n", strcmp(test, test_key));


}