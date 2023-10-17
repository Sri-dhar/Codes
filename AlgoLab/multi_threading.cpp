#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
using namespace std;

bool is_prime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void task(int id) {
    cout << "Thread " << id << " started" << endl;
    auto start_time = chrono::steady_clock::now();
    int count = 0;
    while (chrono::steady_clock::now() - start_time < chrono::seconds(60)) {
        for (int i = 2; i < 100000; i++) {
            if (is_prime(i)) {
                count++;
            }
        }
    }
    cout << "Thread " << id << " finished, calculated " << count << " primes" << endl;
}

int main() {
    const int num_threads = 3;
    thread threads[num_threads];
    for (int i = 0; i < num_threads; i++) {
        threads[i] = thread(task, i);
    }
    for (int i = 0; i < num_threads; i++) {
        threads[i].join();
    }
    cout << "All threads finished" << endl;
    return 0;
}
