#include <stdio.h>
#include <cs50.h>


int main(void)
{
    // username request
    string name = get_string("What's your name? ");
    // print "hello, username"
    printf("hello, %s\n", name);
}