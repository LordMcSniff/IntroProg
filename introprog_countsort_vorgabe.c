#include <stdio.h>
#include <string.h>
#include "introprog_countsort.h"
#include "arrayio.h"

/* Ab hier Funktion count_sort_calculate_counts implementieren */

/* Ab hier Funktion count_sort_write_output_array implementieren */

/* Ab hier Funktion extract_order_direction implementieren */

/* Ab hier Funktion count_sort implementieren und entsprechende Funktionsaufrufe einfügen */

int main(int argc, char *argv[]) {
    if (argc < 3){
        printf("Aufruf: %s <Dateiname> asc|desc\n", argv[0]);
        printf("Beispiel: %s zahlen.txt asc\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];

    /*
     * Hier die Sortierrichtung einlesen und einer Variablen
     * des Datentypes SortDirection (siehe h-Datei) verwenden.
     * Beenden des Programmes mit derselben Ausgabe der Hilfe (siehe Anfang main-Funktion).
     * implementieren Sie zur Umwandlung die Funktion extract_order_direction
     */

    int input_array[MAX_LAENGE];
    int len = read_array_from_file(input_array, MAX_LAENGE, filename);

    printf("Unsortiertes Array:");
    print_array(input_array, len);

    /*
     * Hier count_sort aufrufen und alle nötigen Deklarationen einfügen!
     */

    printf("Sortiertes Array:");

    /* Folgende Zeile einkommentieren, um das Array auszugeben! */
    // print_array(output_array, len);

    return 0;
}
