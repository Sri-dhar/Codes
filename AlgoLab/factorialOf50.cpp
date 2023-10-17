#include <iostream>
#include <gmpxx.h>

int main() {
    mpz_class factorial = 1;

    for (int i = 2; i <= 100000; ++i) {
        factorial *= i;
    }

    std::cout << "Factorial of 100000 is a very large number: " << factorial << std::endl;

    return 0;
}

//g++ -o factorial_gmp factorial_gmp.cpp -lgmpxx -lgmp
//compilation command