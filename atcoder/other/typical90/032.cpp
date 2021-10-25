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

ll N, M, i, j, k;
vector<vector<ll>> A;
vector<vector<bool>> forbidden(10, vector<bool>(10, false));

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    vector<ll> runner;
    REP(i, N) {
        A.push_back(vector<ll>(0));
        REP(j, N) {
            cin >> k;
            A[i].push_back(k);
        }
        runner.push_back(i);
    }
    cin >> M;
    REP(i, M) {
        cin >> j >> k;
        forbidden[j - 1][k - 1] = true;
        forbidden[k - 1][j - 1] = true;
    }
    ll INF = 10000000;
    ll ans = INF;
    do {
        bool flg = false;
        for (int i = 0; i < N - 1; i++) {
            if (forbidden[runner[i]][runner[i + 1]]) flg = true;
        }
        if (flg) continue;
        ll time = 0;
        for (int i = 0; i < N; i++) {
            time += A[runner[i]][i];
        }
        ans = min(ans, time);
    } while (std::next_permutation(runner.begin(), runner.end()));
    if (ans == INF) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
}