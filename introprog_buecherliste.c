#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "introprog_buecherliste.h"
#include "introprog_structs_lists_input.h"

/* Fuege ein Element am Anfang der Liste an, sodass das neue
 * Element immer das erste Element der Liste ist.  Wenn die Liste
 * leer ist, soll das Element direkt an den Anfang platziert
 * werden.
 *
 * first    - Pointer auf das erste Element (bzw. Anfang) der
 * Liste
 * new_elem - Pointer auf das neues Element das in die Liste
 * eingefuegt werden soll
 *
 * Gib einen Pointer auf den neuen Anfang der Liste zurueck.
 */
element *insert_at_begin(element *list, element *item)
{
    item->next = list;
    return item;
}

/* Kreiere ein neues Element mit dynamischem Speicher.
 *
 * title  - Titel des Buches
 * author - Autor des Buches
 * year   - Erscheinungsjahr des Buches
 * isbn   - ISBN des Buches
 *
 * Gib einen Pointer auf das neue Element zurueck.
 */
element *construct_element(char *_title, char *_author, uint32_t _year, uint64_t _isbn)
{
    element *item = calloc(1, sizeof(element));
    _title[MAX_STR - 1] = '\0';
    _author[MAX_STR - 1] = '\0';
    strcpy(item->title, _title);
    strcpy(item->author, _author);
    item->year = _year;
    item->isbn = _isbn;
    return item;
}

/* Gib den der Liste und all ihrer Elemente zugewiesenen
 * Speicher frei.
 */
void free_list(list *list)
{
    element *item = list->first; // count may be inaccurate, when items are inserted manually
    while (item != NULL)
    {
        element *tmp = item->next;
        free(item);
        item = tmp;
    }
    free(list);
}

/* Lese die Datei ein und fuege neue Elemente in die Liste ein
 * _Soll nicht angepasst werden_
 */
void read_list(char *filename, list *alist)
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
        alist->first = insert_at_begin(alist->first, new_elem);
        alist->count++;
    }
}

/* Erstelle die Liste:
 *  - Weise ihr dynamischen Speicher zu
 *  - Initialisiere die enthaltenen Variablen
 * _Soll nicht angepasst werden_
 */
list *construct_list()
{
    list *alist = malloc(sizeof(list));
    alist->first = NULL;
    alist->count = 0;
    return alist;
}