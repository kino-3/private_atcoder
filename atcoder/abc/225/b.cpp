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
ll N, i, n_1, n_2, n_3, n_4, j, k;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    cin >> n_1 >> n_2;
    cin >> n_3 >> n_4;
    ll center = 0;
    bool star = true;
    if (n_1 == n_3 || n_1 == n_4) {
        center = n_1;
    } else if (n_2 == n_3 || n_2 == n_4) {
        center = n_2;
    } else {
        star = false;
    }
    REP(i, N - 3) {
        cin >> j >> k;
        if (j != center && k != center) {
            star = false;
        }
    }
    if (star) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}