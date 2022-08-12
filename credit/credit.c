#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void)
{
    // Get credit card number from user.
    long number;
    do
    {
        number = get_long("What's your card number? ");
    }
    while (false);

    // Calculate the length of the card number.
    int len_number = floor(log10(labs(number))) + 1;

    // Create an array of digits of the card number in reverse order.
    int reverse_array[len_number];
    int reverse_count = 0;
    int first_array_count = 0;
    int second_array_count = 0;
    int reverse_digit;
    while (number != 0)
    {
        reverse_digit = number % 10;
        number = number / 10;
        reverse_array[reverse_count] = reverse_digit;

        if (reverse_count % 2 != 0)
        {
            first_array_count ++;
        }

        if (reverse_count % 2 == 0)
        {
            second_array_count ++;
        }

        reverse_count += 1;
    }

    // Multiply every other digit by 2,
    // starting with the number’s second-to-last digit,
    // and then add those products’ digits together.
    int first_array[first_array_count];
    int first_sum = 0;
    int product;
    int digit;
    int i;
    for (i = 1; i < len_number; i += 2)
    {
        product = reverse_array[i] * 2;
        while (product != 0)
        {
            digit = product % 10;
            product = product / 10;
            first_sum += digit;
        }
    }

    // Calculating the sum of digits that have not been multiplied by 2.
    int second_sum = 0;
    int j;
    for (j = 0; j < len_number; j += 2)
    {
        second_sum += reverse_array[j];
    }

    // Add the sum to the sum of the digits that were not multiplied by 2.
    int sum = first_sum + second_sum;
    int first_digit = reverse_array[len_number - 1];
    int f_s_d = first_digit * 10 + reverse_array[len_number - 2];

    // Checking the equality of the last digit of the sum is 0
    // and checking the number of digits in the card number (from 13 to 16 inclusive)
    // as well as checking the conditions for compliance with AMEX, MASTERCARD, VISA.
    if (sum % 10 == 0 && len_number > 12 && len_number < 17)
    {
        if (f_s_d == 34 || f_s_d == 37)
        {
            printf("AMEX\n");
        }
        else if (f_s_d == 51 || f_s_d == 52 || f_s_d == 53 || f_s_d == 54 || f_s_d == 55)
        {
            printf("MASTERCARD\n");
        }
        else if (first_digit == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}