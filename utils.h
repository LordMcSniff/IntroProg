#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
Utility functions used throughout the codebase.
*/

/*
Try to malloc, abort when out of memory.
*/
void* mallocx(size_t size) {
    void * allocation = malloc(size);

    if (allocation) {
        return allocation;
    } else {
        printf("Out of memory");
        abort();
    }
}

uint8_t *copy_u8s(uint8_t *arr, size_t len) {
    uint8_t *r = (uint8_t *) malloc(len);
    memcpy(r, arr, len);
    return r;
}

uint16_t *copy_u16s(uint16_t *arr, size_t len) {
    uint16_t *r = (uint16_t *) malloc(sizeof(uint16_t) * len);
    memcpy(r, arr, sizeof(uint16_t) * len);
    return r;
}

/*
Return whether the given string contains characters which might make trouble in a file name.
*/
bool is_invalid_filename(char* name) {
    int len = strlen(name);

    for(int i = 0; i<len;i++){
        if(name[i] == '/' || name[i] == '\\' || name[i] == '<' || name[i] == '>' || name[i] == '|'
            || name[i] == ':' || name[i] == '*' || name[i] == '?' || name[i] == '"'){
            return true;
        }
    }

    return false;
}

#endif