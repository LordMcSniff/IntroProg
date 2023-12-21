/*
Zur Abgabe einen branch `iprg-b06` erstellen und pushen, in dem als einzige
Datei die `06ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den
folgenden Befehl aus: cc -std=c11 -g -Wall -Werror 06ex_test.c -o 06ex_test.o
-lm && ./06ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so
testen wir auch auf dem Server: cc -std=c11 -g -Wall -Werror 06ex_test.c -o
06ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all
--track-origins=yes ./06ex_test.o
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_visualizer.h"

/*
Aufgabe 1:
Machen Sie sich in dieser Aufgabe mit dem `Visualizer` (siehe
array_visualizer.h) vertraut. Nutzen Sie die `visualizer_append_array` Funktion
damit die Tests durchlaufen.

Tipp 1: Die erste Zeile im erzeugten Bild stellt das Eingabearray dar.
*/
void warmup(Visualizer *v, uint8_t *arr, size_t len) {
    uint8_t *sample = calloc(len * 2, sizeof(uint8_t));
    memcpy(sample, arr, len * sizeof(uint8_t));
    memcpy(sample + len, arr, len * sizeof(uint8_t));

    for (int i = 0; i < len; i++) {
        // the visualizer only prints the length of the tasks array,
        // overflow will be ignored
        visualizer_append_array(v, sample + i);
    }

    free(sample);
}

/*
Aufgabe 2:
Bringen Sie die Tests zum durchlaufen.

Tipp 1: Die erste Zeile im erzeugten Bild stellt das Eingabearray dar.
Tipp 2: Es handelt sich um eine Abwandlung von iterativem Mergesort.
Tipp 3: `len` ist immer eine Dreierpotenz, damit Sie sich nicht mit
Rundungsdetails herumschlagen brauchen.
*/

int min3(uint8_t a, uint8_t b, uint8_t c) {
    // get 0, 1, 2 depending on which argument was the lowest
    if (a > b) {
        return 1 + (b > c);
    } else {
        return (a > c) * 2;
    }
}

void mergesort3_fill(uint8_t *arr, size_t len, size_t index, size_t chunksize) {
    // fill the array at index inplace with the 3 chunks
    size_t indexA = 0, indexB = 0, indexC = 0;
    uint8_t A, B, C;

    uint8_t *tmp = calloc(chunksize * 3, sizeof(uint8_t));

    // for (size_t i = 0; i < stepsize; i++) {
    //     tmp[i] = i * UINT8_MAX / stepsize;
    // }

    A = arr[index + indexA + chunksize * 0];
    B = arr[index + indexB + chunksize * 1];
    C = arr[index + indexC + chunksize * 2];

    while (indexA + indexB + indexC < chunksize * 3) {
        // printf("\t%hhu\t%hhu\t%hhu\t%d\n", A, B, C, min3(A, B, C));

        switch (min3(A, B, C)) {
            case 0:  // A
                tmp[indexA + indexB + indexC] = A;
                indexA++;

                if (indexA >= chunksize)
                    A = UINT8_MAX;
                else
                    A = arr[index + indexA + chunksize * 0];

                break;

            case 1:  // B
                tmp[indexA + indexB + indexC] = B;
                indexB++;

                if (indexB >= chunksize)
                    B = UINT8_MAX;
                else
                    B = arr[index + indexB + chunksize * 1];

                break;

            case 2:  // C
                tmp[indexA + indexB + indexC] = C;
                indexC++;

                if (indexC >= chunksize)
                    C = UINT8_MAX;
                else
                    C = arr[index + indexC + chunksize * 2];

                break;

            default:
                printf("ERROR invalid min\n");
                return;
                break;
        }
    }

    memcpy(arr + index, tmp, chunksize * 3);
    free(tmp);
}

void sort_it(Visualizer *v, uint8_t *arr, size_t len) {
    visualizer_append_array(v, arr);

    for (size_t stepsize = 3; stepsize <= len; stepsize *= 3) {
        for (size_t i = 0; i < len; i += stepsize) {
            mergesort3_fill(arr, len, i, stepsize / 3);
            visualizer_append_array(v, arr);
        }
    }
}
