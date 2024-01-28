#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
    int ch;

    while ((ch = getchar()) != EOF) {
        if (isupper(ch)) {
            putchar(tolower(ch));
        }
        else if (islower(ch)) {
            putchar(toupper(ch));
        }
        else {
            putchar(ch);
        }
    }
    exit(0);
}
