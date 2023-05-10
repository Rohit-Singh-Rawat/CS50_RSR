#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string user_name = get_string("What's your name? "); //code line for input
    printf("hello, %s\n", user_name) ;
}