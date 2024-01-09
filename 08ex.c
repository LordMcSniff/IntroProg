/*
Zur Abgabe einen branch `iprg-b08` erstellen und pushen, in dem als einzige Datei die `08ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 08ex_test.c -o 08ex_test.o -lm && ./08ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 08ex_test.c -o 08ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./08ex_test.o
*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Ein Array zusammen mit seiner Länge. */
typedef struct ArrayWithLength_ {
    uint16_t *arr;
    size_t len;
} ArrayWithLength;

/*
Bei merge sort werden häufiger mal *zwei* vorsortierte Arrays kombiniert. Auf diesem Blatt
kombinieren wir effizient *beliebig viele* vorsortierte Arrays mit einem divide-and-conquer Algorithmus.
*/

/*
Aufgabe 1a:

Gegeben ein absteigend sortiertes Array, geben Sie ein absteigend sortiertes Array
mit den gleichen Elementen zurück.
Der Speicher für die Arrayelemente im Rückgabewert soll eigens mit malloc allokiert werden.

Tipp: Ja, es ist wirklich so banal wie es klingt. Das haben base-cases bei divide-and-conquer
Algorithmen häufig so an sich.
*/
ArrayWithLength base_case(ArrayWithLength arr) {
    uint16_t *tmp = calloc(arr.len, sizeof(uint16_t));

    // once again a genius move from you guys to ban memcpy
    // memcpy(ret.arr, arr.arr, sizeof(uint16_t) * arr.len);

    for (size_t i = 0; i < arr.len; i++) {
        tmp[i] = arr.arr[i];
    }

    arr.arr = tmp;

    return arr;
}

/*
Aufgabe 1b:

Gegeben zwei absteigend sortierte Arrays der Längen len1 und len2,
geben Sie ein absteigend sortiertes Array zurück,
welches die Elemente beider Eingabearrays enthält. Die Funktion soll in O(len1 + len2) laufen.
Der Speicher für die Arrayelemente im Rückgabewert soll eigens mit malloc allokiert werden.
*/
size_t min(size_t a, size_t b) {
    return a < b ? a : b;
}
size_t minb(size_t a, size_t b) {
    return a > b;
}

ArrayWithLength combine(ArrayWithLength arr1, ArrayWithLength arr2) {
    if (arr1.len == 0)
        return base_case(arr2);
    if (arr2.len == 0)
        return base_case(arr1);

    ArrayWithLength ret = {.arr = NULL, .len = 0};
    size_t total_len = arr1.len + arr2.len;

    ret.arr = calloc(total_len, sizeof(uint16_t));

    size_t Index_A = 0, Index_B = 0;
    uint16_t value_A = arr1.arr[0], value_B = arr2.arr[0];

    while (Index_A + Index_B < total_len) {
        if (value_A > value_B) {
            ret.arr[ret.len] = value_A;
            Index_A++;

            if (Index_A >= arr1.len)
                value_A = 0;
            else
                value_A = arr1.arr[Index_A];

        } else {
            ret.arr[ret.len] = value_B;
            Index_B++;

            if (Index_B >= arr2.len)
                value_B = 0;
            else
                value_B = arr2.arr[Index_B];
        }
        ret.len++;
    }

    return ret;
}

/*
Aufgabe 1c:

Gegeben ein nichtleeres Array `arrs` aus `count` vielen absteigend sortierten Arrays, geben Sie ein absteigend sortiertes Array
zurück, welches die Elemente aller Eingabearrays enthält. Ihre Lösung soll in O(n * log(count)) laufen, wobei `n` die
Gesamtzahl an Elementen in allen Arrays ist. Dazu müssen sie clever dive-and-conquern.

Der Speicher für die Arrayelemente im Rückgabewert soll eigens mit malloc allokiert werden.
*/

/*
returns the index of the maximum value in the array.

returns UINT16_MAX (-1) if not found, eg. array is empty.
*/
size_t max_index(uint16_t *arr, size_t len) {
    if (len == 0)
        return UINT16_MAX;

    size_t index = 0;
    for (size_t i = 0; i < len; i++) {
        if (arr[i] > arr[index])
            index = i;
    }
    return index;
}

ArrayWithLength merge_k(ArrayWithLength *arrs, size_t count) {
    size_t total_len = 0;

    //! 1. Step filter out the empty arrays and sum up length
    for (size_t i = 0; i <= count - 1; i++) {
        // while in the loop might as well keep a running total of the length instead of haveing a second one later
        total_len += arrs[i].len;

        if (arrs[i].len == 0) {
            // swap, note order of the inputed array will not be preserved,
            ArrayWithLength tmp = arrs[i];
            arrs[i] = arrs[count - 1];
            arrs[count - 1] = tmp;

            count--;
            i--;
        }
    }

    //! 2. Step Handle edge cases
    if (count == 0)
        return (ArrayWithLength){.arr = NULL, .len = 0};
    if (count == 1)
        return base_case(arrs[0]);

    //! 3. Step setup/ alloc the necessary arrays
    ArrayWithLength ret = {.arr = NULL, .len = 0};
    ret.arr = calloc(total_len, sizeof(uint16_t));

    size_t *Indices = calloc(count, sizeof(size_t));
    uint16_t *values = calloc(count, sizeof(uint16_t));
    // fill the values with the first values
    for (size_t i = 0; i < count; i++)
        values[i] = arrs[i].arr[0];

    //! 4. Step merge the arrays
    // // TODO: loop condition
    while (ret.len < total_len) {
        size_t I = max_index(values, count);

        ret.arr[ret.len] = values[I];
        Indices[I]++;

        if (Indices[I] >= arrs[I].len)
            values[I] = 0;
        else
            values[I] = arrs[I].arr[Indices[I]];

        ret.len++;
    }

    free(values);
    free(Indices);
    return ret;
}
