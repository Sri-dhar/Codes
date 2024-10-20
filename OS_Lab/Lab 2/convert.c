#include <stdio.h>
#include <ctype.h>

int main() {
    int ch;

    while ((ch = getchar()) != EOF) {
        if (islower(ch)) {
            putchar(toupper(ch));
        } else if (isupper(ch)) {
            putchar(tolower(ch));
        } else {
            putchar(ch);
        }
    }

    exit(0);
}
