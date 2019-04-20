#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float in = -1;
    int coins;

    while (in < 0)
    {
        in = get_float("Change owed: ");
    }

    // Convert to penny
    int input = (int) round((in * 100));
    //printf("Pennies only: %i\n", input);

    // Count quarters
    coins = (int) round(input) / 25;
    //int quarters = (int) round(input) / 25;
    //printf("quarters: %i\n", quarters);

    // Count dimes
    coins += (int) round((input % 25) / 10);
    //int dimes = (int) round((input % 25) / 10);
    //printf("dimes: %i\n", dimes);

    // Count nickels
    coins += (int) round(((input % 25) % 10) / 5);
    //int nickels = (int) round(((input % 25) % 10) / 5);
    //printf("nickels: %i\n", nickels);

    // Count pennies
    coins += ((int) input) % 5;
    //int pennies = ((int) input) % 5;
    //printf("pennies: %i\n", pennies);

    printf("%i\n", coins);

}