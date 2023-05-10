#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int count_letters(string s);

int count_words(string s);

int count_sentences(string s);
int main(void)
{
    string text = get_string("Text: ");
    float L = (count_letters(text) * 100.00) / count_words(text); // Number of letters in 100 words
    float S = (count_sentences(text) * 100.00) / count_words(text); // Number of sentences in 100 words
    float index = (0.0588 * L) - (0.296 * S) - 15.8 ;// Coleman-Liau index.
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        index = round(index); // Rounding off to nearest integer
        printf("Grade %i\n", (int) index);
    }
}


int count_letters(string s) // Function to return letters in a text
{
    int total_letters = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (isalpha(s[i]))
        {
            total_letters++;
        }
    }
    return total_letters;
}

int count_words(string s) // Function to return words in a text
{
    int total_words = 1;
    for (int i = 0; i < strlen(s); i++)
    {
        if (isspace(s[i]) && ! isspace(s[i - 1])  && ! isspace(s[i + 1]))
        {
            total_words++;
        }
    }
    return total_words;
}

int count_sentences(string s) // Funtion to return se ntences in a text
{
    int total_sentences = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            total_sentences++;
        }
    }
    return total_sentences;
}
