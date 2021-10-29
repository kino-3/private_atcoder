#include <bits/stdc++.h>
#define REP(var, n) for (decltype(n) var = 0; var < (n); var++)
#define REP_R(var, n) \
    for (auto var = (n)-1; var != static_cast<decltype(var)>(-1); var--)
#define FOR(var, a, b) for (auto var = (a); var < (b); var++)
#define FOR_R(var, a, b) for (auto var = (b - 1); var > (a - 1); var--)
#define ALL(c) std::begin(c), std::end(c)

using namespace std;
using ll = long long;

// REP(idx, 3) { cout << idx; }  // 012
// REP_R(idx, 3) { cout << idx; }  // 210
// FOR(idx, 4, 7) { cout << idx; }  // 456
// FOR_R(idx, 4, 7) { cout << idx; }  // 654
// sort(ALL(v));

ll Q, i, j, k;
vector<ll> T, X;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> Q;
    REP(i, Q) {
        cin >> j >> k;
        T.push_back(j);
        X.push_back(k);
    }
    deque<ll> que;
    REP(i, Q) {
        switch (T[i]) {
            case 1:
                que.push_front(X[i]);
                break;
            case 2:
                que.push_back(X[i]);
                break;
            case 3:
                cout << que[X[i] - 1] << endl;
                break;
        }
    }
}