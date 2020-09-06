#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
   if (argc != 2)
   {
       printf("Usage: ./caesar key\n");
       return 1;
   }
   for (int i = 0, n = strlen(argv[1]); i < n; i++)
   {
       if (!isdigit(argv[1][i]))
       {
           printf("Usage: ./caesar key\n");
           return 1;
       }
   }

   int key = atoi(argv[1]);

   string plaintext = get_string("Plaintext: ");

   for (int i = 0, n = strlen(plaintext); i < n; i++)
   {
      if (isupper(plaintext[i]))
      {
         plaintext[i] = ((plaintext[i] - 65 + key) % 26) + 65;
      }
      else if (islower(plaintext[i]))
      {
         plaintext[i] = ((plaintext[i] - 97 + key) % 26) + 97;
      }
   }

   printf("Ciphertext: %s\n", plaintext);
   return 0;
}