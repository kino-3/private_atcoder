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

ll N, K, i;
ll L = 100000;
vector<ll> memo(L, -1);

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> K;
    memo[N] = 0;
    ll tmp = N;
    ll c = 0;
    ll cycle;
    while (true) {
        ll v = tmp;
        ll tmptmp = tmp;
        REP(i, 5) {
            v += tmptmp % 10;
            tmptmp /= 10;
        }
        tmp = v % L;
        c++;
        if (memo[tmp] > 0) {
            cycle = c - memo[tmp];
            break;
        }
        memo[tmp] = c;
        // cout << tmp << endl;
    }
    c -= cycle;
    ll idx;
    if (K <= c) {
        idx = K;
    } else {
        idx = (K - c) % cycle + c;
    }
    REP(i, L) {
        if (memo[i] == idx) {
            cout << i << endl;
        }
    }
}