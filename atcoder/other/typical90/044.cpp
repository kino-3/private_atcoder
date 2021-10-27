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

ll N, Q, i, j, k, l;
vector<ll> A, T, X, Y;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> Q;
    REP(i, N) {
        cin >> j;
        A.push_back(j);
    }
    REP(i, Q) {
        cin >> j >> k >> l;
        T.push_back(j - 1);
        X.push_back(k - 1);
        Y.push_back(l - 1);
    }
    ll index = 0;
    REP(i, Q) {
        if (T[i] == 0) {
            ll x = X[i] - index;
            ll y = Y[i] - index;
            x = x < 0 ? x + N : x;
            y = y < 0 ? y + N : y;
            ll tmp = A[x];
            A[x] = A[y];
            A[y] = tmp;
        } else if (T[i] == 1) {
            index += 1;
            index %= N;
        } else {
            ll x = X[i] - index;
            x = x < 0 ? x + N : x;
            cout << A[x] << endl;
        }
    }
}