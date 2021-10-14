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

ll H, W;
vector<vector<ll>> a;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> H >> W;
    ll i;
    ll j;
    REP(i, H) {
        a.push_back(vector<ll>(0));
        REP(j, W) {
            ll k;
            cin >> k;
            a[i].push_back(k);
        }
    }

    vector<ll> row;
    vector<ll> col;
    REP(i, H) {
        ll s = 0;
        REP(j, W) { s += a[i][j]; }
        row.push_back(s);
    }
    REP(j, W) {
        ll s = 0;
        REP(i, H) { s += a[i][j]; }
        col.push_back(s);
    }
    REP(i, H) {
        REP(j, W) {
            cout << row[i] + col[j] - a[i][j];
            if (j < W - 1) cout << " ";
        }
        cout << endl;
    }
}