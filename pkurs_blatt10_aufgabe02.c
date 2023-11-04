#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *prepare_repeated_message(char *message, int repeat)
{
    // len including \0 or \n
    int len = strlen(message) + 1;
    char *out = calloc(repeat * len + 1, sizeof(char)); // add terminator

    for (int i = 0; i < repeat; i++)
    {
        // include new line in len
        memcpy(out + len * i, message, len);
        // add line feed \n
        out[len * (i + 1) - 1] = '\n';
    }
    // and since calloc initializes all to 0 you dont even need to set the terminator :D
    return out;
}

int main()
{
    char *out = prepare_repeated_message("Hallo Osiris!", 0);
    printf("%s", out);
    free(out);
    return 0;
}