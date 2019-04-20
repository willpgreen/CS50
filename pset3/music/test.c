#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int get_index(string s, char c)
{
    for (int i = 0;i <= strlen(s); i++)
    {
        if (s[i] == c)
        {

            return i;
        }
    }
    return -1;
}

int main(void)
{
    string scale = "CDEFGAB";
    char note[4] = "A5\0";

    int A3 = 440;

    int n; // Represents number of notes from A4
    int freq; // Represents frequency of note

    // First find distance between A and note
    // Use string of notes and find difference between indices
    n = get_index(scale, note[0]) - get_index(scale, 'A');
    printf("%i\n", n);

    // Adjust for sharp or flat
    if (note[1] == 'b')
    {
        n -= 1;
    }
    else if (note[1] == '#')
    {
        n += 1;
    }
    printf("%i\n", n);

    // Adjust based off the octave
    n = n + 12 * (note[strlen(note) - 1] - '4');
    //char x = note(index);
    printf("%i\n", n);

    freq = (int) round(pow(2.0, n / 12.0) * 440);
    printf("%i\n", freq);
    /*
    //if (strlen(test) == 3)
    //{
        printf("%lu\n", strlen(test));
    //}
    printf("%i\n", A4);
    int out = (int) round(pow(2.0, test[1] - 49) * 55);
    printf("%i\n", out);
    //if (strcmp(test[1], 'b') == 0)
    printf("%i\n", get_index(notes, test[0]));
    */

}