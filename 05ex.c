/*
Zur Abgabe einen branch `iprg-b05` erstellen und pushen, in dem als einzige Datei die `05ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 05ex_test.c -o 05ex_test.o -lm && ./05ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 05ex_test.c -o 05ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./05ex_test.o
*/

#include "search_tree.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Aufgabe 1:

Fügen Sie den Wert `x` als Blatt so in den nicht-leeren Suchbaum `t` ein, dass `t` hinterher
wieder ein Suchbaum ist. Falls `x` bereits in `t` vorkam, soll `t` stattdessen
unverändert bleiben.
Geben Sie zurück, ob der Baum modifiziert wurde.

Nutzen Sie `malloc`, um das neue Blatt zu erstellen. Der Testrunner wird das Blatt wieder `free`n,
darum brauchen Sie sich nicht zu kümmern.
*/
bool search_tree_insert(TreeNode *t, uint16_t x)
{
    while (true)
    {
        if (t->item < x)
        {
            if (t->right == NULL)
            {
                t->right = calloc(1, sizeof(TreeNode));
                t->right->item = x;
                return true;
            }
            else
            {
                t = t->right;
                continue;
            }
        }
        else if (t->item > x)
        {
            if (t->left == NULL)
            {
                t->left = calloc(1, sizeof(TreeNode));
                t->left->item = x;
                return true;
            }
            else
            {
                t = t->left;
                continue;
            }
        }
        else
        {
            return false;
        }
    }
}

/*
Aufgabe 2:
Geben Sie die kleinste Zahl im Suchbaum `t` zurück, welche echt größer als `x` ist.
Falls keine solche Zahl existiert, geben Sie stattdessen `x` zurück. Die Laufzeit Ihrer Lösung soll
proportional zur Höhe des Baumes sein, aber unabhängig von der Gesamtzahl an Knoten.
*/
uint16_t search_tree_get_greater_than(TreeNode *t, uint16_t x)
{
    uint16_t last = x; // save x in last, if there is no value found bigger than x, then last will never be overwritten
    while (t != NULL)  // loop infinitely
    {

        if (t->item > x) // go right until you find an item is bigger than x
        {
            last = t->item; // save last item bigger than x and go smaller (left)
            t = t->left;
            continue; // skip to the next loop
        }
        else // since item is not bigger than x go bigger (right)
        {
            t = t->right;
            continue; // skip to the next loop
        }
    }
    return last; // if you entered a dead end, return the last value bigger than x
}
