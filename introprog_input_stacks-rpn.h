#ifndef MAX_STR
#define MAX_STR 255
#endif

int taschenrechner_input(char *zeile);
void intro();
int is_mult(char *token);
int is_sub(char *token);
int is_add(char *token);
int is_number(char *token);
