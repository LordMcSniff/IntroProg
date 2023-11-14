#include <stdio.h>
#include <string.h>
#include "introprog_countsort.h"
#include "arrayio.h"

void count_sort_calculate_counts(int input_array[], int len, int count_array[])
{
    memset(count_array, 0, (MAX_VALUE + 1) * sizeof(int)); // the compiler initialises arrays to 0, but valgrind doesn't like it

    for (size_t j = 0; j < len; j++)
    {
        count_array[input_array[j]] = count_array[input_array[j]] + 1;
    }
}

void count_sort_write_output_array(int output_array[], int count_array[], SortDirection order)
{
    int k = 0;
    for (size_t j = 0; j <= MAX_VALUE; j++)
    {
        int index = j;
        if (order == ASCENDING) // redundent, but who knows what bullshit the test will pull
            index = j;
        if (order == DESCENDING)
            // len of count_array is MAX_VALUE +1, so you dont need to subtract one here
            index = MAX_VALUE - j;

        for (size_t i = 0; i < count_array[index]; i++)
        {
            output_array[k] = index;
            k = k + 1;
        }
    }
}

SortDirection extract_order_direction(char *order)
{
    if (!strcmp(order, "asc"))
        return ASCENDING;
    else if (!strcmp(order, "desc"))
        return DESCENDING;

    return NOTDEFINED;
}

void count_sort(int input_array[], int len, int output_array[], SortDirection order)
{
    int count_array[MAX_VALUE + 1]; // 0 to max including both

    count_sort_calculate_counts(input_array, len, count_array);

    count_sort_write_output_array(output_array, count_array, order);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Aufruf: %s <Dateiname> asc|desc\n", argv[0]);
        printf("Beispiel: %s zahlen.txt asc\n", argv[0]);
        return 1;
    }

    SortDirection order = extract_order_direction(argv[2]);
    char *filename = argv[1];

    int input_array[MAX_LEANGE];
    int len = read_array_from_file(input_array, MAX_LEANGE, filename);

    printf("Unsortiertes Array:");
    print_array(input_array, len);

    int output_array[MAX_LEANGE];
    count_sort(input_array, len, output_array, order);

    printf("Sortiertes Array:");
    print_array(output_array, len);

    return 0;
}
