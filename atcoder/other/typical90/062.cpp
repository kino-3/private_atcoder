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
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    REP(i, N) {
        cin >> j >> k;
        A.push_back(j - 1);
        B.push_back(k - 1);
    }
    vector<vector<ll>> next(N, vector<ll>(0));
    queue<ll> que;
    vector<ll> ans;
    set<ll> ans_set;
    REP(i, N) {
        if (A[i] == i || B[i] == i) {
            que.push(i);
        } else {
            next[A[i]].push_back(i);
            next[B[i]].push_back(i);
        }
    }
    while (!que.empty()) {
        ll target = que.front();
        // cout << target << endl;
        que.pop();
        ans.push_back(target);
        for (const auto v : next[target]) {
            if (ans_set.count(v) == 0) {
                // cout << 100 + v << endl;
                que.push(v);
                ans_set.insert(v);
            }
        }
    }
    if (ans.size() == N) {
        reverse(ALL(ans));
        for (const auto v : ans) {
            cout << v + 1 << endl;
        }
    } else {
        cout << -1 << endl;
    }
}