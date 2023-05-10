#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>


string incrpyt(string t, string key) // Function to incrpyt text using given key
{
    int z = strlen(t);
    for (int i = 0; i < z; i++)
    {
        if (isupper(t[i]))
        {
            int j =  t[i] - 65;

            t[i] = toupper(key[j]);
        }
        else if (islower(t[i]))
        {
            int j = t[i] - 97;
            t[i] = tolower(key[j]);
        }
    }
    return t;


}
int main(int argc, string argv[])
{
    if (argc != 2) // If arguments will be more than 1
    {
        printf("Usage: ./substitution key\n");
        return 1;

    }
    if (strlen(argv[1]) != 26) // If key have less or more character than 26
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int la = 0; la < strlen(argv[1]); la++)
    {
        if (! isalpha(argv[1][la])) // if key is not given correctly
        {
            printf("Key must contain 26 alphabhetic characters.\n");
            return 1;
        }
        for (int lu = 0; lu < strlen(argv[1]); lu++)// Nested loop to check duplicate
        {
            if (argv[1][la] == argv[1][lu] && la != lu)
            {
                printf("key must contain 26 different alphabetic cahracters\n");
                return 1;
            }

        }
    }
    string plaintext = get_string("Plaintext: ");
    printf("ciphertext: %s\n", incrpyt(plaintext, argv[1])); //Printing ciphertext
}
