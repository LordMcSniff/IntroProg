/*
Zur Abgabe einen branch `iprg-b09` erstellen und pushen, in dem als einzige Datei die `09ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 09ex_test.c -o 09ex_test.o -lm && ./09ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 09ex_test.c -o 09ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./09ex_test.o
*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "array.h"
#include "tree.h"

/*
Aufgabe 1:

Gegeben ein Array `arr`, geben Sie zurück, ob der zugehörige linksvollständige Binärbaum
die max-heap Eigenschaft erfüllt.
*/

bool is_max_heap_rec(Array arr, size_t index, uint16_t last) {
    if (index >= arr.len)
        return true;

    if (last < arr.arr[index])
        return false;

    return is_max_heap_rec(arr, index * 2 + 1, arr.arr[index]) && is_max_heap_rec(arr, index * 2 + 2, arr.arr[index]);
}

bool is_max_heap(Array arr) {
    if (arr.len < 1)
        return true;

    return is_max_heap_rec(arr, 1, arr.arr[0]) && is_max_heap_rec(arr, 2, arr.arr[0]);
}

/*
Aufgabe 2:

Gegeben ein linksvollständiger Binärbaum, tragen Sie im Array `arr` dessen Arrayrepräsentation ein.

Tipp 1: Wie so häufig bei Bäumen, bietet sich hier eine rekursive Lösung an.
Tipp 2: Diese Funktion selbst ist allerdings nur so mäßig gut für rekursive Aufrufe geeignet, eventuell sollten Sie sich eine (rekursive) Hilfsfunktion schreiben.
Tipp 3: Die Position eines Knotens im Array lässt sich relativ leicht bestimmen, wenn man die Position vom Elternknoten weiß, und, ob es sich um ein linkes oder ein rechtes Kind handelt.
Tipp 4: Ja, das sind also sinnvolle Argumente für die Hilfsfunktion.
Tipp 5: Regelmäßig zähneputzen und genug bewegen.
*/
void tree_to_array_rec(TreeNode *t, Array arr, size_t index) {
    if (t == NULL)
        return;

    arr.arr[index] = t->item;

    tree_to_array_rec(t->left, arr, index * 2 + 1);
    tree_to_array_rec(t->right, arr, index * 2 + 2);
}

void tree_to_array(TreeNode *t, Array arr) {
    tree_to_array_rec(t, arr, 0);
}
