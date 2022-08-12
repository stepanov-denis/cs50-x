#include <cs50.h>
#include <stdio.h>

void print_block(int i);
void print_whitespace(int i);
void print_pyramid(int height);

int main(void)
{
    // get hieght value from user
    int height;
    do
    {
        height = get_int("how height? ");
    }
    while (height < 1 || height > 8);

    // print pyramid
    print_pyramid(height);
}

// print block's in current row
void print_block(int i)
{
    int j;
    for (j = 0; j < i; j++)
    {
        printf("#");
    }
}

// print whitespace's in current row
void print_whitespace(int i)
{
    int j;
    for (j = 0; j < i; j++)
    {
        printf(" ");
    }
}

// print pyramid
void print_pyramid(int height)
{
    int i;
    for (i = 0; i < height; i++)
    {
        print_whitespace(height - (i + 1));

        print_block(i + 1);

        printf("  ");

        print_block(i + 1);

        printf("\n");
    }
}