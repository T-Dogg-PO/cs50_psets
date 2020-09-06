#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

float count_letters(string text);

float count_words(string text);

float count_sentences(string text);

int main(void)
{
    // Ask the user for their text input
    string text = get_string("Text: ");

    // Declare variables and call functions
    float letters = count_letters(text);
    float words = count_words(text);
    float sentences = count_sentences(text);

    printf("%f letter(s)\n", letters);

    printf("%f word(s)\n", words);

    printf("%f sentence(s)\n", sentences);

    // Calculate number of letters per 100 words
    float l = letters / words * 100;

    // Calculate number of sentences per 100 words
    float s = sentences / words * 100;

    printf("l = %f\n", l);
    printf("s = %f\n", s);

    // Calculate and display reading level
    float index = ((0.0588 * l) - (0.296 * s) - 15.8);
    printf("Raw index = %f\n", index);
    int rounded_index = round (index);
    if (rounded_index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (rounded_index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", rounded_index);
    }
}

// Calculate the number of characters in the string
float count_letters(string text)
{
    float letters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if isalpha(text[i])
        {
            letters++;
        }
    }
    return letters;
}

// Calculate the number of words in the string
float count_words(string text)
{
    float words = 1; // Assumes that the string will start with at least one word and not a space or anything else weird
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] != 32 && text[i - 1] == 32)
        {
            words++;
        }
    }
    return words;
}

// Calculate the number of sentences in the string
float count_sentences(string text)
{
    float sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}