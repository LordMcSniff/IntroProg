#include <stdint.h>
#ifndef MAX_STR
#define MAX_STR 255
#endif
/* Bewirkt, dass statt 'struct _element' auch 'element' verwendet
 * werden kann.
 */
#ifndef ELEMENT
#define ELEMENT
typedef struct _element element;
#endif
/* Bewirkt, dass statt 'struct _list' auch 'list' verwendet werden
 * kann.  Hier in einem geschrieben, so dass man auch 'list'
 * innerhalb der struct-Definition selbst verwenden kann.
 */
#ifndef LIST
#define LIST
typedef struct _list
{                   /* Separater Wurzelknoten */
    element *first; /* Anfang/Kopf der Liste */
    int count;      /* Anzahl der Elemente */
} list;
#endif

#ifndef ELEMENTDEF
#define ELEMENTDEF
/* HIER struct _element implementieren. */
struct _element
{
    char title[MAX_STR]; // Dumm aber ok, wenn ihr dass so wollt
    char author[MAX_STR];
    uint32_t year;
    uint64_t isbn;

    element *next;
};
/* ab hier nichts mehr implementieren. */
#endif
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
element *insert_at_begin(element *list, element *item);

/* Kreiere ein neues Element mit dynamischem Speicher.
 *
 * title  - Titel des Buches
 * author - Autor des Buches
 * year   - Erscheinungsjahr des Buches
 * isbn   - ISBN des Buches
 *
 * Gib einen Pointer auf das neue Element zurueck.
 */
element *construct_element(char *, char *, uint32_t, uint64_t);

/* Gib den der Liste und all ihrer Elemente zugewiesenen
 * Speicher frei.
 */
void free_list(list *);

/* Lese die Datei ein und fuege neue Elemente in die Liste ein
 * _Soll nicht angepasst werden_
 */
void read_list(char *, list *);

/* Erstelle die Liste:
 *  - Weise ihr dynamischen Speicher zu
 *  - Initialisiere die enthaltenen Variablen
 * _Soll nicht angepasst werden_
 */
list *construct_list();