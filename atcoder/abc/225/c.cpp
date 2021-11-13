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

ll mod = 1000000007;
ll N, M, i, j, k, l;
vector<vector<ll>> A;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;
    REP(i, N) {
        A.push_back(vector<ll>(0));
        REP(j, M) {
            cin >> k;
            A[i].push_back(k);
        }
    }
    ll test = (A[0][0] - 1) % 7 + 1;
    bool yes = true;
    REP(i, M) {
        if (((A[0][i] - 1) % 7 + 1) == test) {
            test++;
        } else {
            yes = false;
        }
    }
    REP(i, N) {
        REP(j, M - 1) {
            if (A[i][j + 1] != A[i][j] + 1) yes = false;
        }
    }
    REP(i, N - 1) {
        if (A[i + 1][0] != A[i][0] + 7) yes = false;
    }
    if (yes) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}