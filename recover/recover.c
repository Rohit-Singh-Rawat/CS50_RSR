#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t BYTE;
int BLOCK_SIZE = (sizeof(BYTE)) * 512;
BYTE buffer[512];

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        printf("Could not open file");
        return 2;
    }
    int img = 000 ;
    char *int_o =  malloc(8 * sizeof(char));
    FILE *new_img = NULL;
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, raw_file))
    {
        //checking for jpeg header to create image
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (new_img != NULL)
            {
                fclose(new_img);
            }

            sprintf(int_o, "%03d.jpg", img);// saving or printing number to convert into string

            new_img = fopen(int_o, "w");
            img++;
        }
        if (new_img != NULL)// checking whether image file is created to write in
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, new_img);
        }

    }

    fclose(raw_file); // Close Raw file
    fclose(new_img);// Close last image file created
    free(int_o); // free the alloted space
    return 0;
}

