/*
Zur Abgabe einen branch `iprg-b12` erstellen und pushen, in dem als einzige Datei die `12ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 12ex_test.c -o 12ex_test.o -lm && ./12ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 12ex_test.c -o 12ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./12ex_test.o
*/

#include "height_tree.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

size_t height_or_zero(HeightTreeNode *t)
{
    if (t == NULL)
    {
        return 0;
    }
    else
    {
        return t->height;
    }
}

/*
Aufgabe 1a:

Führen Sie eine Rechtsrotation auf dem gegebenen Baum durch, und geben Sie einen Pointer auf
die Wurzel des neuen Baumes zurück.
Der Baum ist nichtleer, und die Wurzel hat einen nichtleeren linken Teilbaum.

Denken Sie daran, auch die Höhen und die Elternpointer anzupassen.

Die Baumausgabe im Terminal enthält in jedem Knoten erst das Item, dann die Höhe, und zuletzt
das Item des Elternkotens (oder NULL für die Wurzel).

Die Baumausgabe nimmt den zurückgegebenen Knoten als Wurzel. Sollte die Baumausgabe komplett
überraschend aussehen, könnte das gut an einer falsch zurückgegebenen Wurzel liegen.
*/
HeightTreeNode *rotate_right(HeightTreeNode *t)
{
    HeightTreeNode *Root = t;
    HeightTreeNode *LeftChild = t->left;

    Root->height = height_or_zero(Root->right) + 1;

    Root->left = LeftChild->right;
    if (Root->left)
    {
        Root->left->parent = Root;
        Root->height = fmax(Root->left->height, Root->height - 1) + 1;
    }

    Root->parent = LeftChild;
    LeftChild->right = t;
    LeftChild->parent = NULL;

    LeftChild->height = Root->height + 1;

    LeftChild->height = fmax(LeftChild->height - 1, height_or_zero(LeftChild->left)) + 1;

    return LeftChild;
}

/*
Die vier möglichen Sequenzen von Rotationen, um einen Beinahe-AVL-Baum in einen AVL-Baum zu überführen.
*/
typedef enum Rotations_
{
    Left,                    /* eine Linksrotation */
    Right,                   /* eine Rechtsrotation */
    DoubleRotationLeftRight, /* Doppelrotation: erst Linksrotation, dann Rechtsrotation */
    DoubleRotationRightLeft, /* Doppelrotation: erst Rechtsrotation, dann Linksrotation */
} Rotations;

/*
Aufgabe 2:

Gegeben ein Beinahe-AVL-Baum mit korrekten Höhenwerten, geben Sie zurück, welche Rotationen ihn zu einem AVL-Baum machen.
*/
Rotations determine_rotations(HeightTreeNode *t)
{
    int8_t balance = height_or_zero(t->left) - height_or_zero(t->right);
    // printf(" > %hhi", balance);

    if (balance > 1)
    {
        if (height_or_zero(t->left->left) >= height_or_zero(t->left->right))
        {
            return Right;
        }
        return DoubleRotationLeftRight;
    }

    if (balance < -1)
    {
        if (height_or_zero(t->right->left) <= height_or_zero(t->right->right))
        {
            return Left;
        }
        return DoubleRotationRightLeft;
    }

    return Left;
}