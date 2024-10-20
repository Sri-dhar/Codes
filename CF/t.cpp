#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Car {
    ll pos, vel;
    int idx;
    Car(ll p, ll v, int i) : pos(p), vel(v), idx(i) {}
};

pair<bool, double> willCollide(const Car& car1, const Car& car2) {
    if (car1.pos == car2.pos) return {true, 0};
    ll relativeVel = car1.vel - car2.vel;
    if (relativeVel == 0) return {false, -1};
    double time = (double)(car2.pos - car1.pos) / relativeVel;
    return {time >= 0, time};
}

bool canAchieveTime(vector<Car>& cars, int M, double targetTime) {
    int n = cars.size();
    vector<vector<bool>> willCollideMatrix(n, vector<bool>(n, false));
    vector<int> collisionCount(n, 0);
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            auto [collides, time] = willCollide(cars[i], cars[j]);
            if (collides && time <= targetTime) {
                willCollideMatrix[i][j] = true;
                collisionCount[i]++;
                collisionCount[j]++;
            }
        }
    }
    
    for (int removed = 0; removed < M; removed++) {
        int maxCollisions = 0;
        int carToRemove = -1;
        
        for (int i = 0; i < n; i++) {
            if (collisionCount[i] > maxCollisions) {
                maxCollisions = collisionCount[i];
                carToRemove = i;
            }
        }
        
        if (maxCollisions == 0) return true;
        
        for (int j = 0; j < n; j++) {
            if (willCollideMatrix[carToRemove][j]) {
                collisionCount[j]--;
            }
            if (willCollideMatrix[j][carToRemove]) {
                collisionCount[j]--;
            }
        }
        collisionCount[carToRemove] = 0;
    }
    
    return *max_element(collisionCount.begin(), collisionCount.end()) == 0;
}

double solve(int N, int M, vector<ll>& positions, vector<ll>& velocities) {
    vector<Car> cars;
    for (int i = 0; i < N; i++) {
        cars.emplace_back(positions[i], velocities[i], i);
    }
    
    bool allMovingAway = true;
    for (int i = 0; i < N && allMovingAway; i++) {
        for (int j = i + 1; j < N; j++) {
            if ((cars[i].vel == cars[j].vel && cars[i].pos != cars[j].pos) ||
                (cars[i].pos < cars[j].pos && cars[i].vel > cars[j].vel) ||
                (cars[i].pos > cars[j].pos && cars[i].vel < cars[j].vel)) {
                allMovingAway = false;
                break;
            }
        }
    }
    if (allMovingAway) return -1;
    
    double left = 0, right = 1e18;
    for (int iter = 0; iter < 100; iter++) {
        double mid = (left + right) / 2;
        if (canAchieveTime(cars, M, mid)) {
            left = mid;
        } else {
            right = mid;
        }
    }
    
    return left;
}

void runTestCase() {
    int N, M;
    cin >> N >> M;
    
    vector<ll> positions(N), velocities(N);
    for (int i = 0; i < N; i++) {
        cin >> positions[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> velocities[i];
    }
    
    double result = solve(N, M, positions, velocities);
    
    if (result == -1) {
        cout << -1 << endl;
    } else {
        ll rounded = (ll)(result * 1000000 + 0.5);
        cout << rounded << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T = 1;
    while (T--) {
    runTestCase();          
    }
    
    return 0;
}