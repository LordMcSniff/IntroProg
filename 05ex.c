/*
Willkommen zum fünften Aufgabenblatt vom Programmierkurs. Auf diesem Aufabenblatt geht es um Rekursion.

Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall 05ex_test.c -o 05ex_test.o -lm && ./05ex_test.o
*/

#include "05_canvas.h"
#include <stdio.h>
#include <math.h>
asdad
    /*
    Aufgabe 1a:
    Zeichnen Sie eine horizontale Linie der Länge `width`, deren am weitesten links liegender Pixel bei `(x, y)` ist.

    _Benutzen Sie keine Schleifen - Die Aufgabe soll über Rekursion gelöst werden!_

    */
    Canvas
    recursive_line(Canvas c, int x, int y, int width)
{
    if (width <= 0)
        return c;
    if (x >= 0 && x < canvas_width(c)) // das steht nirgens wo in der aufgabe
        c = canvas_set_black(c, x, y);
    return recursive_line(c, x + 1, y, width - 1);
}

/*
Aufgabe 1b:
Zeichnen Sie ein Rechteck mit der Breite `width` und der Höhe `height`. Der Pixel der linken unteren Ecke liegt bei `(x, y)`.

_Benutzen Sie keine Schleifen, die Aufgabe soll über Rekursion gelöst werden!_
*/
Canvas recursive_rectangle(Canvas c, int x, int y, int width, int height)
{
    // Es zeigt ziehmlich schlechtes management, dass keiner irgendwo angesagt hat, das die Aufgabe unmöglich war und das es ne neue zum runterladen gibt.
    // Das in den Foren irgendwo zu verstecken ist echt gemein. Ihr hättet da wenigstens in die Ankündigungen zetzen.
    // ich hab mehrere Tage an dieser Aufgabe gesessen, weil ich einfach nicht glauben wollte, das ihr nen fehler in den tests gemacht habt.
    if (height <= 0)
        return c;
    if (y >= 0 && y < canvas_height(c)) // das steht nirgens wo in der aufgabe
        c = recursive_line(c, x, y, width);
    return recursive_rectangle(c, x, y + 1, width, height - 1);
}

/*
Aufgabe 2:
Der *Sierpinski Carpet der Ordnung 0* ist ein einzelnes schwarzes Pixel.
Der *Sierpinski Carpet der Ordnung n+1* besteht aus acht Sierpinski Carpets der Ordnung n, angeordnet als drei-mal-drei
Quadrat dessen Mittelstück fehlt.

Beispiele (`X` stellt schwarze Pixel dar)
=========================================

Ordnung 0:

X

Ordnung 1:

XXX
X X
XXX

Ordnung 2:

XXXXXXXXX
X XX XX X
XXXXXXXXX
XXX   XXX
X X   X X
XXX   XXX
XXXXXXXXX
X XX XX X
XXXXXXXXX

Siehe auch die Datei `05sierpinski.jpg`

Aufgabe 2a:
Um in der nächsten Aufgabe den Sierpinski-Carpet auf die Canvas zeichnen zu können müssen Potenzen berechnet werden.
Implementieren Sie die Berechnung der Potenz einer nicht-negativen, ganzzahligen Basis `b` mit einem
nicht-negativen, ganzzahligen Exponenten `exp`.

_Benutzen Sie keine Schleifen, die Aufgabe soll über Rekursion gelöst werden!_
*/
int power(int b, int exp)
{
    if (exp <= 0)
        return 1;

    return power(b, exp - 1) * b;
}

/*
Aufgabe 2b:
Diese Funktion soll den Sierpinski Carpet der Ordnung `n` auf die Canvas zeichnen, mit unterer linker Ecke an Koordinate `(x, y)`.

_Benutzen Sie keine Schleifen, die Aufgabe soll über Rekursion gelöst werden!_
*/
Canvas sierpinski_carpet(Canvas c, int n, int x, int y)
{
    // Canvas sierpinski_carpet(Canvas c, int n, int px, int py) {
    // ist doch behindert, das nach den literall strings geprüft wird
    int px = x;
    int py = y;

    if (n <= 0)
        return canvas_set_black(c, px, py);

    int w = power(3, n - 1);
    //! literally retarded decision to not allow loops entirely
    //? https://isis.tu-berlin.de/mod/forum/discuss.php?d=554130
    // for (size_t y = 0; y < 3; y++)
    // {
    //     for (size_t x = 0; x < 3; x++)
    //     {
    //         if (x == 1 && y == 1)
    //             continue;
    //
    //         c = sierpinski_carpet(c, n - 1, px + w * x, py + w * y);
    //     }
    // }

    c = sierpinski_carpet(c, n - 1, px + w * 0, py + w * 0);
    c = sierpinski_carpet(c, n - 1, px + w * 1, py + w * 0);
    c = sierpinski_carpet(c, n - 1, px + w * 2, py + w * 0);

    c = sierpinski_carpet(c, n - 1, px + w * 0, py + w * 1);
    // c = sierpinski_carpet(c, n - 1, px + w * 1, py + w * 1);
    c = sierpinski_carpet(c, n - 1, px + w * 2, py + w * 1);

    c = sierpinski_carpet(c, n - 1, px + w * 0, py + w * 2);
    c = sierpinski_carpet(c, n - 1, px + w * 1, py + w * 2);
    c = sierpinski_carpet(c, n - 1, px + w * 2, py + w * 2);
    return c;
}

/*
Aufgabe 3:
Implementieren Sie einen Fülleimer. Gegeben eine Koordinate `(x, y)` auf einer (bereits bemalten) Canvas, soll die komplette
zusammenhängende Fläche aller Pixel der selben Farbe (schwarz oder weiß) schwarz gefärbt werden.
Zwei Pixel sind Teil der selben Fläche wenn sie die selbe Farbe haben und direkt benachbart sind. Jeder Pixel hat bis
zu vier direkte Nachbarn - die Diagonalen zählen nicht.

Funktionen, um die Farbe eines Pixels auf der Canvas zu bestimmen, sind im Headerfile der Canvas dokumentiert.
*/
Canvas bucket_fill(Canvas c, int x, int y)
{
    if (x < 0 || x > canvas_width(c) - 1 || y < 0 || y > canvas_height(c) - 1)
        return c;

    if (pixel_is_black(c, x, y))
        return c;

    c = canvas_set_black(c, x, y);

    if (x > 0)
        c = bucket_fill(c, x - 1, y);

    if (x < canvas_width(c) - 1)
        c = bucket_fill(c, x + 1, y);

    if (y > 0)
        c = bucket_fill(c, x, y - 1);

    if (y < canvas_height(c) - 1)
        c = bucket_fill(c, x, y + 1);

    return c;
}