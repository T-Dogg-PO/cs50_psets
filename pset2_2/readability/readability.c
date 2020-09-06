#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text, int n);
int count_words(string text, int n);
int count_sentences(string text, int n);
int index_calculator(float characters, float words, float sentences);

int main(void)
{
    string text = get_string("Text: ");

    int n = strlen(text);

    int characters = count_letters(text, n);
    int words = count_words(text, n);
    int sentences = count_sentences(text, n);

    int index = index_calculator(characters, words, sentences);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text, int n)
{
    int characters = 0;
    for (int i = 0; i < n; i++)
    {
        if (isalpha(text[i]))
        {
            characters++;
        }
    }
    return characters;
}

int count_words(string text, int n)
{
    int words = 1;
    for (int i = 0; i < n; i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
    }
    return words;
}

int count_sentences(string text, int n)
{
    int sentences = 0;
    for (int i = 0; i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}

int index_calculator(float characters, float words, float sentences)
{
    float index = 0;

    //printf("%f, %f, %f\n", characters, words, sentences);

    float L = (characters / words) * 100;
    //printf("L is %f\n", L);
    float S = (sentences / words) * 100;
    //printf("S is %f\n", S);

    index = (0.0588 * L) - (0.296 * S) - 15.8;
    //printf("Index is %f\n", index);

    return round(index);
}