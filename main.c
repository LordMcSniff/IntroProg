#include <stdio.h>
#include <stdlib.h>

int hailstone(int n)
{
    int c = 0;
    while (n != 1)
    {
        c++;
        if (n % 2 == 0)
            n /= 2;
        else
            n = n * 3 + 1;
    }
    return c;
}
//
int values[] = {0, 1, 7, 2, 5, 8, 16, 3, 19, 6, 14, 9, 9, 17, 17, 4, 12, 20, 20, 7,
                7, 15, 15, 10, 23, 10, 111, 18, 18, 18, 106, 5, 26, 13, 13, 21,
                21, 21, 34, 8, 109, 8, 29, 16, 16, 16, 104, 11, 24, 24, 24, 11,
                11, 112, 112, 19, 32, 19, 32, 19, 19, 107, 107, 6, 27, 27, 27,
                14, 14, 14, 102, 22};

int main(int argc, char const *argv[])
{
    long limit = (argc == 2) ? strtol(argv[1], NULL, 10) : sizeof(values) / sizeof(int);

    for (int n = 1; n < limit; n++)
    {
        int out = 0;
        out = hailstone(n);
        if (out != values[n - 1])
            printf("error: %i \t %i \t : %i\n", n, values[n], out);
    }
    return 0;
}

// cd ${workspaceRoot}
// gcc -fdiagnostics-color=always -g -std=c11 -Wall -lm main.c -o main
// gdb main
// or just use vscode like a normal person