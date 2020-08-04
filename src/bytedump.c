// it's like xxd, but dumber and worse
// by @simboyd

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printBinary(FILE* fl, unsigned long filesize);
void printDecimal(FILE* fl, unsigned long filesize);
void printHex(FILE* fl, unsigned long filesize);

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Usage: bytedump [filename] [--option]\n\tOptions:\n\t\t--bin = print bytes in binary\n\t\t--dec = print bytes in decimal\n\t\t--hex = print bytes in hexadecimal\n");
        exit(-1);
    }

    FILE* fl; 
    fopen_s(&fl, argv[1], "rb");
    if (!fl)
    {
        printf("Error opening the file. Does it exist?\n");
        exit(-50);
    }

    unsigned long filesize = 0;
    fseek(fl, 0, SEEK_END);
    filesize = ftell(fl);
    fseek(fl, 0, SEEK_SET);

   if (strcmp(argv[2], "--bin") == 0)
        printBinary(fl, filesize);
    else if (strcmp(argv[2], "--dec") == 0)
        printDecimal(fl, filesize);
    else if (strcmp(argv[2], "--hex") == 0)
        printHex(fl, filesize);
    else
    {
        printf("Incorrect usage. Third argument should either be --bin, --hex or --dec.\n");
        exit(-51);
    }
    printf("\nTotal filesize: %d byte(s)", filesize);
    return 0;
}

void printBinary(FILE* fl, unsigned long filesize)
{
    unsigned char byte = 0;
    char buffer[9];
    printf("1+:\t");
    for (unsigned long i = 1; i <= filesize; i++)
    {
        fread(&byte, 1, 1, fl);
        _itoa_s(byte, buffer, 2);
        for (unsigned int k = 0; k < 8 - strlen(buffer); k++)
            printf("0");
        printf("%s   ", (unsigned char)buffer);
        if (i % 10 == 0)
            printf("\n%d+:\t", i + 1);
    }
}

void printDecimal(FILE* fl, unsigned long filesize)
{
    unsigned char byte = 0;
    printf("1+:\t\t");
    for (unsigned long i = 1; i <= filesize; i++)
    {
        fread(&byte, 1, 1, fl);
        printf("%d\t", (unsigned char)byte);
        if (i % 10 == 0)
        {
            printf("\n%d+:\t\t", i + 1);
        }
    }
}

void printHex(FILE* fl, unsigned long filesize)
{
    unsigned char byte = 0;
    printf("1+:\t\t");
    for (unsigned long i = 1; i <= filesize; i++)
    {
        fread(&byte, 1, 1, fl);
        printf("%02X\t", (unsigned char)byte);
        if (i % 10 == 0)
        {
            printf("\n%d+:\t\t", i + 1);
        }
    }
}
