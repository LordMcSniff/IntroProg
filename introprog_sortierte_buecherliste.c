#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "introprog_sortierte_buecherliste.h"
#include "introprog_structs_lists_input.h"

/* HIER struct _element implementieren. */

/* Fuege ein Element in die Liste ein, sodass die Liste aufsteigend
 * nach ISBN sortiert ist.  Dafür muss das erste Element ermittelt
 * werden, das in der bisher sortierten Liste eine ISBN besitzt,
 * die größer ist als die des neuen Elements.  Wenn die Liste leer
 * ist, soll das Element direkt an den Anfang platziert werden.
 *
 * first    - Pointer auf das erste Element (bzw. Anfang) der Liste
 * new_elem - Pointer auf das neues Element das in die Liste
 * eingefuegt werden soll
 *
 * Gib einen Pointer auf den neuen oder alten Anfang der Liste
 * zurueck.
 */
element *insert_sorted(element *list, element *new_item)
{
    element *start = calloc(1, sizeof(element));
    element *prev = start;

    prev->next = list;
    while (prev->next != NULL)
    {
        if (prev->next->isbn < new_item->isbn) // angenommen die liste ist aufsteigend sortiert
        {
            prev = prev->next;
            continue;
        }

        // if spot was found before end of list, insert and break
        new_item->next = prev->next;
        break;
    }
    prev->next = new_item;

    list = start->next;
    free(start);
    return list;
}

/* Lese die Datei ein und fuege neue Elemente in die Liste ein
 * _Soll nicht angepasst werden_
 */
void read_list_sorted(char *filename, list *alist)
{
    element *new_elem;
    char *new_title;
    char *new_author;
    uint32_t new_year;
    uint64_t new_isbn;
    read_line_context ctx;
    open_file(&ctx, filename);
    while (read_line(&ctx, &new_title, &new_author, &new_year, &new_isbn) == 0)
    {
        new_elem = construct_element(new_title, new_author, new_year, new_isbn);
        alist->first = insert_sorted(alist->first, new_elem);
        alist->count++;
    }
}