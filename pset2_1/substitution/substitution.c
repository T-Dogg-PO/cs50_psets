#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Validate that only a single command line argument is given
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Validate that the key given is exactly 26 characters long
    if (strlen(argv[1]) != 26)
    {
        printf("Key must be 26 characters long.\n");
        return 1;
    }

    // Validate that the key given only contains alphabetic characters
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }

    // Validate that each letter in the key is only used once
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (argv[1][i] == argv[1][j] || argv[1][i] == argv[1][j] + 32 || argv[1][i] == argv[1][j] - 32) //make into Elseif
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }

    // Get the plaintext from the user
    string plaintext = get_string("Plaintext: ");

    // Encipher the text
    // Loop over each character in the plaintext
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // Check for upper case characters only
        if (isupper(plaintext[i]))
        {
            // Create a variable for which location in the key we are looking for
            int subtracted = plaintext[i] - 65;
            // Substitute the plaintext character with the relevant character provided by the key
            plaintext[i] = argv[1][subtracted];
            // Ensure it is set back to an upper case character (regardless of what was provided in the key)
            plaintext[i] = toupper(plaintext[i]);
        }
        else if (islower(plaintext[i]))
        {
            int subtracted = plaintext[i] - 97;
            plaintext[i] = argv[1][subtracted];
            plaintext[i] = tolower(plaintext[i]);
        }
    }

    // Print out the enciphered text
    printf("Ciphertext: %s\n", plaintext);
    return 0;
}