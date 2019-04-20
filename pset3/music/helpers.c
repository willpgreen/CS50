// Helper functions for music

#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#include "helpers.h"

// A function that returns the position of a char in a string
int get_index(string s, char c)
{
    for (int i = 0; i <= strlen(s); i++)
    {
        if (s[i] == c)
        {
            return i;
        }
    }
    return -1;
}

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int den = fraction[2] - 48;
    int num = fraction[0] - 48;
    int out = 8 * num / den;
    return out;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    string scale = "C D EF G A B"; // Used to compare notes
    int n; // Represents number of notes from A4
    int freq; // Represents frequency of note

    // Find distance between 'A' and note using scale
    n = get_index(scale, note[0]) - get_index(scale, 'A');

    //Adjust for sharp or flat
    if (note[1] == 'b')
    {
        n -= 1;
    }
    else if (note[1] == '#')
    {
        n += 1;
    }

    // Adjust based off the octave
    n = n + 12 * (note[strlen(note) - 1] - '4');

    // Calculate frequency
    freq = (int) round(pow(2.0, n / 12.0) * 440);

    return freq;

}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    return strcmp(s, "") == 0;
}

