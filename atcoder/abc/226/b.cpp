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

ll mod = 67280421310721;
ll base = 1000000007;
ll N, i, j, k, l;
vector<vector<ll>> A;
set<pair<ll, ll>> L;
vector<ll> hash;
using ull = unsigned long long;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    vector<vector<ll>> A(N, vector<ll>(0));
    REP(i, N) {
        cin >> l;
        ll pow = 1;
        ll h = 0;
        REP(j, l) {
            cin >> k;
            A[i].push_back(k);
            h += pow * k;
            pow *= base;
            h %= mod;
            pow %= mod;
        }
        L.insert({l, h});
    }
    cout << L.size() << endl;
}