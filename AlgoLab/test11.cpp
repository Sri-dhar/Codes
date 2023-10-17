#include <iostream>
#include <cmath>
using namespace std;

pair<int, int> splitHalves(int x) {
   int Base = 10;
   int divisor = pow(Base, to_string(x).length() / 2);
   int a = x / divisor;
   int b = x % divisor;
   return make_pair(a, b);
}


int karatsuba(int x, int y, int n) {
   if (n == 1) {
       return x * y; 
   } else {
       int a, b, c, d;
       pair<int, int> halves_x = splitHalves(x);
       pair<int, int> halves_y = splitHalves(y);
       a = halves_x.first;
       b = halves_x.second; 
       c = halves_y.first; 
       d = halves_y.second; 

       int p = a + b; 
       int q = c + d; 

       int ac = karatsuba(a, c, n / 2); 
       int bd = karatsuba(b, d, n / 2); 
       int pq = karatsuba(p, q, n / 2); 

       int acbd = pq - bd - ac; 

       return pow(10, n) * ac + pow(10, n / 2) * acbd + bd;
   }
}

int main() {
   int x = 1234;
   int y = 4321;
   int xy = karatsuba(x, y, 4);
   cout << xy << endl;
   return 0;
}