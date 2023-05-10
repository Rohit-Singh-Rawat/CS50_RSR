#include <cs50.h>
#include <stdio.h>

int get_size() ;//Funtion to input value from user that is size of pyramid

void print_piramid(int n) ;//Funtion to print the desired output or pattern

int main(void)//main function to call the funtion for input and output
{
    int n = get_size();
    print_piramid(n);
}

int get_size()
{
    int n;
    do
    {
        n = get_int("Enter the size of Piramid: ") ;
    }
    while (n < 1 || n > 8);//loop for entering only right input

    return n;

}

void print_piramid(int n)
{
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < n + 1; j++)//loop for marking space and hash tag
        {
            if (j >= n + 1 - i)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("  ");
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }


}