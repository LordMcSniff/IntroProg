#include <stdio.h>
#include <string.h>
#include "introprog_countsort.h"
#include "arrayio.h"

/* Ab hier Funktion count_sort_calculate_counts implementieren */
void count_sort_calculate_counts(int input_array[], int len, int count_array[])
{
}

/* Ab hier Funktion count_sort_write_output_array implementieren */
void count_sort_write_output_array(int output_array[], int count_array[], SortDirection order)
{
}

/* Ab hier Funktion extract_order_direction implementieren */
SortDirection extract_order_direction(char *order)
{
    if (!strcmp(order, "asc"))
        return ASCENDING;
    else if (!strcmp(order, "desc"))
        return DESCENDING;

    return NOTDEFINED;
}

/* Ab hier Funktion count_sort implementieren und entsprechende Funktionsaufrufe einfügen */
void count_sort(int A[], int len, int B[], SortDirection order)
{
    // es ist doch behindert, dass wir die ganze zeit mit malloc arbeiten beigebracht kriegen und es dann nicht beutzen dürfen
    int C[MAX_LENGTH];

    for (size_t j = 0; j < len; j++)
    {
        C[A[j]] = C[A[j]] + 1;
    }

    int k = 0;
    for (size_t j = 0; j < MAX_LENGTH; j++)
    {
        for (size_t i = 0; i < C[j]; i++)
        {
            B[k] = j;
            k = k + 1;
        }
    }
}

int exit_help(char *filename)
{
    printf("Aufruf: %s <Dateiname> asc|desc\n", filename);
    printf("Beispiel: %s zahlen.txt asc\n", filename);
    return 1;
}

int main(int argc, char *argv[])
{
    if (MAX_VALUE >= MAX_LENGTH) // normally i'd use an assert, but we're not allowed to include other libs
        return 1;

    if (argc < 3)
        return exit_help(argv[0]);

    SortDirection order = extract_order_direction(argv[2]);
    if (!order) // NOTDEFINED is set to 0, while the others are 1 and 2
        return exit_help(argv[0]);

    char *filename = argv[1];

    int input_array[MAX_LENGTH];
    int len = read_array_from_file(input_array, MAX_LENGTH, filename);

    printf("Unsortiertes Array:");
    print_array(input_array, len);

    int output_array[MAX_LENGTH];
    count_sort(input_array, len, output_array, order);

    printf("Sortiertes Array:");
    print_array(output_array, len);

    return 0;
}
