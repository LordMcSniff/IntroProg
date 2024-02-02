/*
Zur Abgabe einen branch `iprg-b10` erstellen und pushen, in dem als einzige Datei die `10ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 10ex_test.c -o 10ex_test.o -lm && ./10ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 10ex_test.c -o 10ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./10ex_test.o
*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "array.h"
#include "tree.h"

/*
Aufgabe 1:

Implementieren Sie min-heapify auf Bäumen: gegeben ein nichtleerer, linksvollständiger Baum `t`, dessen
Kinder der Wurzel die min-heap Eigenschaft erfüllen, lassen Sie den Wert in der Wurzel so lange
"hinuntersinken", bis `t` die min-heap Eigenschaft erfüllt.

Da "hinuntersinken" nicht gerade präzise formuliert ist, müssen Sie unter Umständen Ihre Implementierung
an die Testfälle anpassen. Aber wenn Sie der Intuition der Vorlesungsfolien folgen, sollte das keine Probleme bereiten.

Werte kommen in `t` niemals mehrfach vor.
*/

void heapify_tree(TreeNode *t)
{
    //! check if reached the end of the tree
    if (t->left == NULL)
        return;

    //! check if min heap

    // check parent against lc
    TreeNode *T = (t->item < t->left->item) ? t : t->left;

    // if the rc exists check against it as well
    if (t->right)
        T = (T->item < t->right->item) ? T : t->right;

    // break if min heap satisfied
    if (T == t)
        return;

    //! swap
    uint16_t tmp = T->item;
    T->item = t->item;
    t->item = tmp;

    // continue with swaped child
    heapify_tree(T);
}

/*
Aufgabe 2:

Implementieren Sie min-heapify auf Arrays: gegeben ein nichtleeres Array und eine Position `i` innerhalb des Arrays,
sodass die Kinder vom Knoten der zum Element an Position `i` gehört min-heaps sind, lassen Sie den Wert an Position `i`
solange hinuntersinken, wie nötig, um die min-heap Eigenschaft für den Teilbaum ab Position `i` wiederherzustellen.

Oder knapper: Implementieren Sie den heapify Algorithmus aus der Vorlesung, aber für min-heaps.

Werte kommen im Array niemals mehrfach vor.
*/
void heapify_array(Array arr, size_t i)
{
    //! check if reached the end of the tree
    if (i * 2 + 1 >= arr.len)
        return;

    //! check if min heap

    // check parent against lc
    size_t I = (arr.arr[i] < arr.arr[i * 2 + 1]) ? i : i * 2 + 1;

    // if the rc exists check against it as well
    if (i * 2 + 2 < arr.len)
        I = (arr.arr[I] < arr.arr[i * 2 + 2]) ? I : i * 2 + 2;

    // break if min heap satisfied
    if (I == i)
        return;

    //! swap
    uint16_t tmp = arr.arr[I];
    arr.arr[I] = arr.arr[i];
    arr.arr[i] = tmp;

    // continue with swaped child
    heapify_array(arr, I);
}
