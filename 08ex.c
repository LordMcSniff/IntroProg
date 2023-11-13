/*
Willkommen zum achten Aufgabenblatt vom Programmierkurs. Auf diesem Aufabenblatt geht es um Pointer und Arrays.

Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall 08ex_test.c -o 08ex_test.o -lm && ./08ex_test.o
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "turtlecanvas.h"

/*
Aufgabe 1a:
Lesen Sie das Headerfile `turtlecanvas.h`. Diese Funktion soll die Turtle `d` Schritte vorwärts machen lassen.
*/
void turtle_advance_by(TurtleCanvas *c, uint32_t d)
{
    for (size_t i = 0; i < d; i++)
        turtle_advance(c);

    return;
}

/*
Aufgabe 1b:
Füllen Sie die Turtlecanvas mit horizontalen, abwechselnd schwarzen und weißen Linien (die unterste Zeile soll
schwarz gefärbt werden). Die Turtle ist anfangs an Position (0, 0), ist nach rechts orientiert, und zeichnet schwarz.
*/
void turtle_stripes(TurtleCanvas *c)
{
    int w = turtle_canvas_width(c);
    int h = turtle_canvas_height(c);
    for (size_t i = 0; i <= h / 2; i++)
    {
        // draw line
        turtle_advance_by(c, w);

        // go to next line
        turtle_toggle_color(c);

        turtle_rotate_left(c);
        turtle_advance_by(c, 2);
        turtle_rotate_right(c);

        turtle_toggle_color(c);
    }

    return;
}

/*
Aufgabe 1c:
Lesen Sie die Implementierungen der Turtlecanvas-Funktionen weiter unten in der "turtlecanvas.h".
Der Quellcode sollte vollständig verständlich und unüberraschend sein.
Hinweis: Diese Aufgabe wird nicht bewertet.
*/

/*
Aufgabe 2a:
Geben Sie einen Pointer auf das erste Vorkommen der größten Zahl im Eingabearray zurück.
*/
uint16_t *find_maximal_number(uint16_t numbers[], size_t numbers_len)
{
    uint16_t *max_ptr = numbers; // set start to first num
    for (size_t i = 0; i < numbers_len; i++)
    {
        if (numbers[i] > *max_ptr)
            max_ptr = numbers + i; // i*sizeof(uint16_t) not neccessary, since pointer addition moves by num of bytes of pointer type
    }

    return max_ptr;
}

/*
Aufgabe 2b:
Geben Sie (einen Pointer auf) das Teilarray zurück, welches ab dem ersten Vorkommen der größten Zahl im Eingabearray beginnt.
*/
uint16_t *find_subarray_starting_at_maximal_number(uint16_t numbers[], size_t numbers_len)
{
    // ??? was war der sinn dieser aufgabe? man gibt ja nur den pointer zurück und keine len
    return find_maximal_number(numbers, numbers_len);
}

/*
Aufgabe 2c:
Geben Sie die größtmögliche Distanz zwischen zwei Zahlenwerten aus dem Array `numbers` zurück.
Beispiel: Im Array {1, 3, 7, 4} ist die größte Distanz die zwischen 1 und 7, und beträgt damit `6`.
*/
uint16_t find_maximum_distance(uint16_t numbers[], size_t numbers_len)
{
    uint16_t *max_ptr = numbers; // set start to first num
    uint16_t *min_ptr = numbers; // set start to first num
    for (size_t i = 0; i < numbers_len; i++)
    {
        if (numbers[i] > *max_ptr)
            max_ptr = numbers + i; // i*sizeof(uint16_t) not neccessary, since pointer addition moves by num of bytes of pointer type
        if (numbers[i] < *min_ptr)
            min_ptr = numbers + i; // i*sizeof(uint16_t) not neccessary, since pointer addition moves by num of bytes of pointer type
    }

    return *max_ptr - *min_ptr;
}

/*
Aufgabe 2d:
Geben Sie die kleinstmögliche Distanz zwischen zwei Zahlenwerten aus dem Array `numbers` zurück.
Beispiel: Im Array {1, 3, 7, 4} ist die kleinste Distanz die zwischen 3 und 4, und beträgt damit `1`.
*/
uint16_t find_minimum_distance(uint16_t numbers[], size_t numbers_len)
{
    uint16_t global_min = UINT16_MAX; // max for 16 bit
    for (size_t i = 0; i < numbers_len; i++)
    {
        uint16_t local_min = UINT16_MAX;                // max for 16 bit
        for (size_t ii = i + 1; ii < numbers_len; ii++) // loop trough from i+1 to end
        {
            uint16_t delta = UINT16_MAX; // max for 16 bit
            if (numbers[i] > numbers[ii])
                delta = numbers[i] - numbers[ii];
            else
                delta = numbers[ii] - numbers[i];

            if (delta < local_min)
                local_min = delta;
        }
        if (local_min < global_min)
            global_min = local_min;
    }
    return global_min;
}

/*
Aufgabe 2e:
Schreiben Sie die ersten `numbers_len` Quadratzahlen aufsteigend in das gegebene Array `numbers`.
Hinweis: Wir starten bei `1`. Sollte numbers_len also `5` sein, sind die ersten 5 Quadratzahlen bis
einschließlich die von 5 gemeint: 1, 4, 9, 16, 25.
*/
void square_ascending(uint16_t numbers[], size_t numbers_len)
{
    for (size_t i = 0; i < numbers_len; i++)
        numbers[i] = pow(i + 1, 2);

    return;
}

/*
Aufgabe 2f:
Füllen Sie das Array `out` mit den aufsteigend sortierten Zahlen aus dem `in` Array. Beide Arrays haben die Länge `len`.
Beispiel: Ist `in` {1, 4, 3, 7, 4}, so soll `out` am Ende {1, 3, 4, 4, 7} sein.
*/

void sort_ascending(uint16_t in[], uint16_t out[], size_t len)
{
    memcpy(out, in, sizeof(uint16_t) * len);
    // effizienz wird ja nicht bewertet

    for (int i = 0; i < len; i++)
    {
        for (int ii = i + 1; ii < len; ii++)
        {
            if (out[i] > out[ii])
            {
                // swap
                uint16_t tmp = out[i];
                out[i] = out[ii];
                out[ii] = tmp;
            }
        }
    }
}
