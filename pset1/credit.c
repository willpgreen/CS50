// Prompts the user for a credit card number and then reports whether it is
// an Amex, MasterCard, Visa or Invalid

#include <cs50.h>
#include <stdio.h>

// Returns 10 raised to the power of y
long long power(int y)
{
    long long x = 1;
    for (int i = 0; i < y; i++)
    {
        x *= 10;
    }

    return x;
}

int main(void)
{
    // Get card number from user
    long long card_num = get_long_long("Enter card number: ");

    // Declare placeholder variables
    long long x = card_num;
    int digits = 0;
    long long sum = 0;

    // Count number of digits in card number
    while (x)
    {
        digits += 1;
        x /= 10;
    }

    // Store first two digits to check card type
    int first_digits = card_num / power(digits - 2);

    // Iterate through each digit in card number, based off number
    for (int i = 0; i < digits; i++)
    {
        // Isolate individual digit
        long long z = card_num / power(i);
        z = z % 10;

        // If even, multiply by two and add digits
        if (i % 2 != 0)
        {
            z *= 2;
            // If greater than 10, add 1 + remainder
            if (z > 9)
            {
                sum += 1;
                sum += z % 10;
            }
            // Else add digit
            else
            {
                sum += z;
            }
        }

        // If odd then add digit
        if (i % 2 == 0)
        {
            sum += z;
        }
    }

    // Sum must be divisible by 1o
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    // Check starting numbers to determine card type
    else if ((first_digits == 34 || first_digits == 37) && digits == 15)
    {
        printf("AMEX\n");
    }
    else if ((first_digits > 50 && first_digits < 56) && digits == 16)
    {
        printf("MASTERCARD\n");
    }
    else if ((first_digits > 39 && first_digits < 50) &&
             (digits == 13 || digits == 16))
    {
        printf("VISA\n");
    }
    // If starting numbers don't match any brand, card must be invalid
    else
    {
        printf("INVALID\n");
    }

    return 0;
}