#include <stdio.h>
#include <ctype.h>

int main() {
    int c;
    int count = 0;

    while ((c = getchar()) != EOF) {
        if (!isalpha(c)) {
            count++;
        }
    }
    fprintf(stderr, "The count of Non-Alphabetic Nos. is : %d\n", count);
    return 0;
}