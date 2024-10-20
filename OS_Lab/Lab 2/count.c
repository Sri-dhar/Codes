#include <stdio.h>
#include <ctype.h>

int main() {
    int ch;
    int count = 0;

    while ((ch = getchar()) != EOF) {
        putchar(ch);
        if (!isalpha(ch)) {
            count++;
        }
    }

    fprintf(stderr, "final count = %d\n", count);
    exit(0);
}
