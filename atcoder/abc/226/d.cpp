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
ll N, i, j, k, l;
vector<ll> X, Y;
set<pair<ll, ll>> ans;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    REP(i, N) {
        cin >> j >> k;
        X.push_back(j);
        Y.push_back(k);
    }
    REP(i, N) {
        REP(j, N) {
            if (i == j) continue;
            if (X[i] == X[j]) {
                ans.insert({1, 0});
                ans.insert({-1, 0});
            } else if (Y[i] == Y[j]) {
                ans.insert({0, 1});
                ans.insert({0, -1});
            } else {
                ll g = __gcd(abs(X[i] - X[j]), abs(Y[i] - Y[j]));
                ll x = (X[i] - X[j]) / g;
                ll y = (Y[i] - Y[j]) / g;
                ans.insert({x, y});
            }
        }
    }
    cout << ans.size() << endl;
}