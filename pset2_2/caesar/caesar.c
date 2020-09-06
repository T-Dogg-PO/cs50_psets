#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // Check for correct number of command line arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Iterate over argument to ensure it's only digits
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Convert argument to an int (from a string)
    int key = atoi(argv[1]);

    // Prompt for Plaintext
    string plaintext = get_string("plaintext: ");

    // Calculate Ciphertext. Iterate over characters (if upper, if lower, if neither)
    string ciphertext = plaintext;

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isupper(plaintext[i]))
        {
            ciphertext[i] = (((plaintext[i] - 65) + key) % 26) + 65;
        }
        else if (islower(plaintext[i]))
        {
            ciphertext[i] = (((plaintext[i] - 97) + key) % 26) + 97;
        }
    }

    // Print Ciphertext
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}