#include <stdio.h>
#include <stdlib.h>
#include "arrayio.h"

int MAX_LENGTH = 1024;

void insertion_sort(int array[], int len)
{
}

// gcc -std=c11 -g -Wall introprog_insertionsort.c arrayio.c -o main.o && ./main.o zahlen_insertionsort.txt

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("Aufruf: %s <Dateiname>\n", argv[0]);
        printf("Beispiel: %s zahlen.txt\n", argv[0]);
        exit(1);
    }

    char *filename = argv[1];

    int array[MAX_LENGTH];
    int len = read_array_from_file(array, MAX_LENGTH, filename);

    printf("Unsortiertes Array:");
    print_array(array, len);

    insertion_sort(array, MAX_LENGTH);

    printf("Sortiertes Array:");
    print_array(array, len);

    return 0;
}
