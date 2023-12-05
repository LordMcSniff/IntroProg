#include <stdlib.h>
#include <string.h>
#include <math.h> // definiert den speziellen Wert NaN für floats
#include "introprog_stacks-rpn.h"
#include "introprog_input_stacks-rpn.h"

/*
 * Füge Element am Anfang des Stacks ein
 *
 * char* - Ein Pointer auf den Stack.
 * float - Zahl, die als neues Element auf den Stack gelegt
 *         werden soll.
 */
void stack_push(stack *stack, float input)
{
    stack_element *layer = calloc(1, sizeof(stack_element));
    layer->value = input;
    layer->next = stack->top;
    stack->top = layer;
}

/*
 * Nehme das letzte eingefügte Element vom Anfang des Stacks
 * Gebe NaN zurück, wenn keine Element vorhanden ist.
 *
 * stack* - Ein Pointer auf den Stack
 *
 * Gebe die im Element enthaltenen Zahl zurück
 */
float stack_pop(stack *stack)
{
    if (stack->top == NULL)
        return NAN;

    stack_element *layer = stack->top;
    float v = layer->value;
    stack->top = layer->next;
    free(layer);
    return v;
}

/*
 * Führt abhängig von dem Token eine entsprechende Operation auf
 * dem Stack aus.  Wenn es sich bei dem Token um
 *  -> eine Zahl handelt, dann konvertiere die Zahl mithilfe von
 *     atof() zu einem float und lege sie auf den Stack.
 *  -> einen Operator handelt, dann nehme zwei Zahlen vom Stack,
 *     führe die Operation aus und lege das Resultat auf den Stack.
 *  -> eine nichterkennbare Zeichenkette handelt, dann tue nichts.
 *
 * stack*  - Ein Pointer auf den Stack
 * char*  - Eine Zeichenkette
 */
void process(stack *stack, char *token)
{
    if (is_number(token))
    {
        stack_push(stack, atof(token));
    }
    else if (is_add(token))
    {
        float b = stack_pop(stack), a = stack_pop(stack);
        stack_push(stack, a + b);
    }
    else if (is_sub(token))
    {
        // double initialisation calls the function once for each var,
        // but the stack last value on top, so the order is b, a.
        // This only matters for subtracktion.
        float b = stack_pop(stack), a = stack_pop(stack);
        stack_push(stack, a - b);
    }
    else if (is_mult(token))
    {
        float b = stack_pop(stack), a = stack_pop(stack);
        stack_push(stack, a * b);
    }

    return;
}

/*
 * Erstelle einen Stack mit dynamischem Speicher.
 * Initialisiere die enthaltenen Variablen.
 *
 * Gebe einen Pointer auf den Stack zurück.
 */
stack *stack_erstellen()
{
    return calloc(1, sizeof(stack));
}