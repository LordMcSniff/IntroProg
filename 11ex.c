/*
Zur Abgabe einen branch `iprg-b11` erstellen und pushen, in dem als einzige Datei die `11ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 11ex_test.c -o 11ex_test.o -lm && ./11ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 11ex_test.c -o 11ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./11ex_test.o
*/

#include "array_visualizer.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Aufgabe 1:
Implementieren Sie folgenden Algorithmus, um ein Array zu partitionieren:

- die `pivot_position` ist initial die letzte Stelle im Array
- der Wert an der `pivot_position` ist das `pivot` Element
- solange es links der `pivot_position` Elemente gibt, die größer oder gleich `pivot` sind:
    - sei `i` die Position des linkesten solchen Elements
    - rotiere die Werte an den Positionen `i`, `pivot_position - 1` und `pivot_position` nach links (siehe Testoutput)
    - dekrementiere die `pivot_position`

Nutzen Sie die `visualizer_append_array` Funktion (siehe `array_visualizer.h` bzw das sechste Semesteraufgabenblatt 06) um den Algorithmus zu visualisieren. Und nutzen Sie die vom Testrunner erstellten Bilder zum Debuggen, und falls Ihnen das zu erwartende Verhalten unklar ist.

Imaginäre Bonuspunkte, wenn Ihre Implementierung in linearzeit läuft.

Tipp: Die erste Zeile im erzeugten Bild stellt das Eingabearray dar.
*/
void visualize_partition(Visualizer *v, uint8_t *arr, size_t len)
{
    visualizer_append_array(v, arr);

    size_t p = len - 1;
    uint16_t pval = arr[p];

    size_t i = 0;

    while (p > i)
    {
        // skip if not bigger
        if (arr[i] < arr[p])
        {
            i++;
            continue;
        }

        arr[p] = arr[i];
        arr[i] = arr[p - 1];
        // eigentlich ist das irrelevant,
        // nur der letzte loop muss pval schreiben, aber der visualizer wills so
        arr[p - 1] = pval;

        visualizer_append_array(v, arr);
        p--;
    }

    return;
}

/*
Aufgabe 2:
Implementieren Sie Quicksort rekursiv, und visualisieren Sie den Algorithmus wie von den Tests verlangt.

Wählen Sie als Pivotelement stets das letzte Element eines Teilarrays, und partitionieren Sie mit dem in Aufgabe 1 beschriebenen Algorithmus.

Tipp 1: Die erste Zeile im erzeugten Bild stellt das Eingabearray dar.
Tipp 2: Visualisieren Sie außerdem das Array immer nachdem Sie ein Teilarray der Größe mindestens zwei partitioniert haben.
Tipp 3: Diese Funktion selbst lässt sich nicht sinnvoll rekursiv aufrufen. Schreiben Sie eine geeignete Funktion, und rufen Sie sie in `sort_quickly` auf.
*/
// returns the index of pivot the rest can be interpolated from that
size_t part(uint8_t *arr, size_t len)
{
    size_t p = len - 1;
    uint16_t pval = arr[p];

    size_t i = 0;

    while (p > i)
    {
        // skip if not bigger
        if (arr[i] < pval)
        {
            i++;
            continue;
        }

        arr[p] = arr[i];
        arr[i] = arr[p - 1];

        p--;
    }
    arr[p] = pval;

    return p;
}

void quicksort_rec(Visualizer *v, uint8_t *arr, size_t index, size_t len)
{
    size_t p = part(arr + index, len);
    visualizer_append_array(v, arr);

    if (p > 1)
        quicksort_rec(v, arr, index, p);

    if (p < len - 2)
        quicksort_rec(v, arr, index + p + 1, len - p - 1);
}

void sort_quickly(Visualizer *v, uint8_t *arr, size_t len)
{
    visualizer_append_array(v, arr);
    quicksort_rec(v, arr, 0, len);
    return;
}