typedef struct _stack stack;
typedef struct _stack_element stack_element;

struct _stack {
    stack_element* top;
};

struct _stack_element {
    stack_element* next;
    float value;
};

void stack_push(stack*, float);

float stack_pop(stack*);

void process(stack*, char*);

void print_stack(stack*);

stack* stack_erstellen();