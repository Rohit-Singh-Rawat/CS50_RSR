#include <cs50.h>
#include <stdio.h>

bool check_sum(long n) ;//just an illusion for compiler
void check_card(long n, bool k) ;// Just another illusion for compiler
int main(void)
{
    long n = get_long("Plz, Enter your credit card number: ") ;// Input for credit card number
    bool k = check_sum(n) ;// Calling function
    check_card(n, k) ; // Calling function
}
bool check_sum(long n) // Function to check sum for Luhn's algorithm
{
    int sum = 0 ;
    int i = 1 ;
    while (n != 0) // Loop for getting all character or integer in the number
    {
        int m = n % 10 ;
        if (i % 2 == 0)
        {
            m *= 2 ;
            while (m != 0) // Loop for geeting all unteger from numbers
            {
                sum += m % 10 ;
                m /= 10 ;
            }
        }
        sum += m ;
        n /= 10 ;
        i++;
    }
    printf("%i", sum);
    if (sum % 10 == 0)
    {
        return true ;
    }
    else if (i < 12)
    {
        return false ;
    }
    else
    {
        return false ;
    }

}
void check_card(long n, bool k)// Function to check which card it is
{
    if (k == true)

    {
        int l[20] = {} ;
        int i = 0 ;
        while (n != 0)
        {
            int m = n % 10 ;
            l[i] = m ;
            n /= 10 ;
            i++;
        }
        if (l[i - 1] == 4 && (i == 13 || i == 16))
        {
            printf("VISA\n") ;
        }
        else if (i == 15 && l[i - 1] == 3 && (l[i - 2] == 4 || l[i - 2] == 7))
        {
            printf("AMEX\n");;
        }
        else if ((i == 16) && l[i - 1] == 5 && (l[i - 2] == 1 || l[i - 2] == 2 || l[i - 2] == 3 || l[i - 2] == 4 || l[i - 2] == 5))
        {
            printf("MASTERCARD\n") ;
        }
        else
        {
            printf("INVALID\n") ;
        }
    }
    else
    {
        printf("INVALID\n") ;
    }

}
