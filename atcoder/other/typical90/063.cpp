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

ll H, W, i, j, k;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> H >> W;
    vector<vector<ll>> P(H, vector<ll>(0));
    REP(i, H) {
        REP(j, W) {
            cin >> k;
            P[i].push_back(k);
        }
    }

    ll N = H;
    ll ans = 1;
    REP(i, 1 << N) {
        // i = 0...2^N-1 (N 桁の辞書順)
        std::bitset<100> bs(i);
        vector<ll> value(W, -1);
        vector<bool> flg(W, true);
        // 上位桁からループ
        ll h = 0;
        REP_R(j, N) {
            if (bs[j]) {
                h++;
                if (value[0] == -1) {
                    copy(ALL(P[j]), value.begin());
                } else {
                    REP(k, W) {
                        if (value[k] != P[j][k]) {
                            flg[k] = false;
                        }
                    }
                }
            }
        }
        multiset<ll> counter;
        set<ll> index;
        REP(k, W) {
            if (flg[k]) {
                index.insert(value[k]);
                counter.insert(value[k]);
            }
        }
        ll w = 0;
        for (auto it = index.begin(), e = index.end(); it != e; ++it) {
            w = max(w, ll(counter.count(*it)));
        }
        ans = max(ans, h * w);
    }
    cout << ans << endl;
}