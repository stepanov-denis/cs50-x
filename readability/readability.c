#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int count_letters(string text, int text_len);
int count_words(string text, int text_len);
int count_sentences(string text, int text_len);
int calc_index(string text, int text_len);
void print_result(string text, int text_len);


int main(void)
{
    // Getting User input
    string text = get_string("Text: ");

    // Calculating the length of the text
    int text_len = strlen(text);

    // Printing the result
    print_result(text, text_len);
}


// Сounting the number of letters in the text
int count_letters(string text, int text_len)
{
    int count = 0;
    for (int i = 0; i < text_len; i++)
    {
        if (text[i] >= 65 && text[i] <= 90)
        {
            count++;
        }
        else if (text[i] >= 97 && text[i] <= 122)
        {
            count++;
        }
    }
    return count;
}


// Counting the number of words in the text
// we will consider any sequence of characters separated by a space as a word
int count_words(string text, int text_len)
{
    int count = 0;
    for (int i = 0; i < text_len; i++)
    {
        if (text[i] == 32)
        {
            count++;
        }
    }
    if (text_len != 0 && count == 0)
    {
        count++;
    }
    if (text_len != 0 && count != 0)
    {
        count++;
    }
    return count;
}


// Counting the number of sentences in the text
// we will consider any sequence of characters that ends with a "."
// or a "!" or a, "?" as a suggestion
int count_sentences(string text, int text_len)
{
    int count = 0;
    for (int i = 0; i < text_len; i++)
    {
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            count++;
        }
    }
    return count;
}


// Сalculation of the Coleman-Liau index
// index = 0.0588 * L - 0.296 * S - 15.8
// where L is the average number of letters per 100 words in the text,
// and S is the average number of sentences per 100 words in the text
int calc_index(string text, int text_len)
{
    int letters = count_letters(text, text_len);
    int words = count_words(text, text_len);
    int sentences = count_sentences(text, text_len);

    float l = 100.00 * letters / words;
    float s = 100.00 * sentences / words;
    float index = 0.0588 * l - 0.296 * s - 15.8;

    int result = round(index);
    return result;
}


// Printing the result
// if the resulting index number is 16 or higher - "Grade 16+"
// if the index number is less than 1 - "Before Grade 1"
// or outputs the grade level as defined by the Coleman-Liau index
// (e.g. "Grade 2" or "Grade 8" or the like)
void print_result(string text, int text_len)
{
    int index = calc_index(text, text_len);

    if (index > 0 && index < 16)
    {
        printf("Grade %i\n", index);
    }
    else if (index > 15)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
}