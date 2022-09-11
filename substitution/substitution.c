#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Check the number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Check key length
    string key = argv[1];
    int key_len = strlen(key);
    if (key_len != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Check key for contains alphabetical characters
    for (int i = 0; i < key_len; i++)
    {
        if (isalpha(key[i]) == 0)
        {
            printf("Key must contain only alphabetical characters\n");
            return 1;
        }
    }

    // Copy key into lowercase
    char copy_key[key_len];
    for (int i = 0; i < key_len; i++)
    {
        copy_key[i] = tolower(key[i]);
    }

    // Check for non repeat key characters
    for (int i = 0; i < key_len; i++)
    {
        for (int j = i + 1; j < key_len; j++)
        {
            if (tolower(key[i]) == copy_key[j])
            {
                printf("Characters should not be repeated\n");
                return 1;
            }
        }
    }

    // Create cipher
    char cipher[122];
    int count = 0;
    for (int i = 97; i < 123; i++)
    {
        cipher[i] = copy_key[count];
        count++;
    }

    // Get plaintetx
    string plaintext = get_string("plaintext: ");

    // Convert plaintetx to ciphertext
    int plaintext_len = strlen(plaintext);
    for (int i = 0; i < plaintext_len; i++)
    {
        if (islower(plaintext[i]) != 0)
        {
            int number_char = tolower(plaintext[i]);
            plaintext[i] = cipher[number_char];
        }

        if (isupper(plaintext[i]) != 0)
        {
            int number_char = tolower(plaintext[i]);
            plaintext[i] = toupper(cipher[number_char]);
        }
    }

    // Print ciphertext
    printf("ciphertext: %s\n", plaintext);



}