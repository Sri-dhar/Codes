#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve() {
    int N, K;
    cin >> N >> K;
    vector<int> bids(N);
    for (int i = 0; i < N; i++) {
        cin >> bids[i];
    }
    sort(bids.begin(), bids.end());

    long long minRevenue = 0;
    for (int i = 0; i < 2 * K; i += 2) {
        minRevenue += bids[i];
    }

    long long maxRevenue = 0;
    for (int i = N - 1; i >= N - K; i--) {
        maxRevenue += bids[i];
    }
    for (int i = N - K - 1; i >= K; i--) {
        maxRevenue += bids[i];
    }

    cout << minRevenue << " " << maxRevenue << "\n";
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}