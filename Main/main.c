#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *str = "Hello, World!";
    char *copy = malloc(strlen(str) + 1); // +1 for the null terminator
    if (copy == NULL) {
        fprintf(stderr, "Memory allcoation failed\n");
        return 1;
    }
}