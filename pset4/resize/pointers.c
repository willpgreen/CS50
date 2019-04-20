/* Pointers!
 *
 * Address of and value at...
 *
 * See this great stack overflow answer for an additional
 * discussion on the topic.
 *
 * https://stackoverflow.com/a/2094715/182778
 *
 */
#include <stdio.h>
#include <stdlib.h>

int main()
{

    int i = 42; // A plain old integer.
    int *p = &i;

    // Let's see some info about the integer's memory address & value.
    printf("--- i is an integer ---\n");
    printf("The value stored at:     i = %d\n", i);
    printf("It's memory address is: &i = %p\n", &i);

    // Now, what about p?
    printf("\n--- p is an uninitialized pointer ---\n");
    printf("At memory address:           p = %p\n", p);
    printf("The value at that location: *p = %d\n", *p);

    // We can make p point to i.
    printf("\n--- p = &i; makes p point to i's address ---\n");

    p = &i;  // p now points to the address of i.
    printf("*p = %d\n", *p);
    printf(" p = %p\n", p);
    printf("&i = %p\n", &i);
    printf("     ^^^^^^^^^^^^^^ are these the same?\n\n");

    printf("* Gives you the value at a pointer\n");
    printf("& Gives you the address of a variable.\n\n");

    return 0;
}
