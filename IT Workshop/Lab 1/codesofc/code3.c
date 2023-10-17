#include <stdio.h>

int sumOfDigits(int num) {
    if (num == 0) {
        return 0;
    } else {
        return (num % 10) + sumOfDigits(num / 10);
    }
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    int sum = sumOfDigits(num);
    printf("Sum of digits of %d is %d\n", num, sum);

    return 0;
}
