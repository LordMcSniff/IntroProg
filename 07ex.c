/*
Zur Abgabe einen branch `iprg-b07` erstellen und pushen, in dem als einzige Datei die `07ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 07ex_test.c -o 07ex_test.o -lm && ./07ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 07ex_test.c -o 07ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./07ex_test.o
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "sphinx.h"

/*
Aufgabe 1:

Da spaziert man entspannt durch Theben, und plötzlich kommt eine Sphinx angeflogen
und spricht: "Ich habe mir ein Array mit n absteigend sortierten Zahlen überlegt (Zahlen
können mehrfach vorkommen). Du darfst mich nach dem Wert an 1 + log2(n) (aufgerundet) vielen
Positionen fragen. Und wenn du mir danach nicht sagen kannst, ob das Array die Zahl 12345
enthält, dann fresse ich dich.".

Geben Sie zurück, ob das Array der Sphinx die Zahl 12345 enthält. Um den Wert an Position `i`
zu erfragen, rufen Sie `sphinx_ask(s, i)` auf. Aber Achtung: Wenn Sie diese Funktion mehr als
1 + log2(n) (aufgerundet) mal aufrufen, stürzt das Programm fehlerhaft ab.
*/
#define VALUE 12345

bool descending_sphinx(Sphinx *s, size_t n) {
    printf(" > \n");
    size_t left = 0;
    size_t right = n - 1;
    size_t index = 0;

    if (n < 1)
        return false;

    while (left <= right && right != UINT64_MAX && left != n) {
        index = (left + right) / 2;
        uint16_t value = sphinx_ask(s, index);
        // printf("  %lu,  %lu,  %lu  - %hu \n", left, right, index, value);

        if (value == VALUE)
            return true;

        if (left == right)
            break;

        if (value > VALUE)
            left = index + 1;
        else if (value < VALUE)
            right = index - 1;
    }

    return false;
}
