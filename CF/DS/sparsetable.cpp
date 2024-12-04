//rmq sparse table
#include<bits/stdc++.h>
using namespace std;

#define MAX 1000
#define MAXLOG 10

int n, m;
int a[MAX];

int st[MAX][MAXLOG];

void build() {
    for (int i = 0; i < n; i++) {
        st[i][0] = a[i];
    }
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; i + (1 << j) <= n; i++) {
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query(int l, int r) {
    int j = log2(r - l + 1);
    return min(st[l][j], st[r - (1 << j) + 1][j]);
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build();
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        cout << query(l, r) << endl;
    }
    return 0;
}

// Time complexity: O(nlogn) for building, O(1) for query