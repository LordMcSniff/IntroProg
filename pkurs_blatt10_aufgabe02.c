#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *prepare_repeated_message(char *message, int repeat)
{
    if (repeat <= 0)
        return calloc(1, 1);

    // len including \0 or \n
    int len = strlen(message) + 1;
    char *out = calloc(repeat * len, sizeof(char));
    char line_feed = '\n';

    strcpy(out, message);
    for (int i = 0; i < repeat - 1; i++)
    {
        strncat(out, &line_feed, 1);
        strcat(out, message);
    }

    return out;
}

int main()
{
    char *out = prepare_repeated_message("Hallo Osiris!", 0);
    printf("%s\n", out);
    free(out);
    return 0;
}