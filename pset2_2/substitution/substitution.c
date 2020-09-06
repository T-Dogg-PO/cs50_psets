#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Validate that only one command-line argument was provided
    if (argc != 2)
    {
        printf("Please provide exactly one key (no spaces)\n");
        return 1;
    }

    // Validate that the provided key is exactly 26 characters long
    if (strlen(argv[1]) != 26)
    {
        printf("Please provide a key that is 26 characters long\n");
        return 1;
    }

    // Validate that each character in the key is a letter, and if it is make sure it's upper now
    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Please provide a key that only contains letters\n");
            return 1;
        }
        else
        {
            argv[1][i] = toupper(argv[1][i]);
        }
    }

    // In the same loop check that each letter only appears once
    for (int i = 0; i < 26; i++)
    {
        for (int n = i + 1; n < 26; n++)
        {
            if (argv[1][i] == argv[1][n])
            {
                printf("Do not repeate characters in your key\n");
                return 1;
            }
        }
    }

    // Get the Plaintext from the user
    string plaintext = get_string("Plaintext: ");

    // Loop through the Plaintext and encipher along the way
    string ciphertext = plaintext;
    int placeholder = 0;

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isupper(plaintext[i]))
        {
            placeholder = ciphertext[i] - 65;
            ciphertext[i] = argv[1][placeholder];
        }
        else if (islower(plaintext[i]))
        {
            placeholder = ciphertext[i] - 97;
            ciphertext[i] = tolower(argv[1][placeholder]);
        }
    }

    // Print out ciphertext
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}