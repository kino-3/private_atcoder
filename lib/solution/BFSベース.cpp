#include <bits/stdc++.h>
#define REP(var, n) for (decltype(n) var = 0; var < (n); var++)
#define REP_R(var, n) \
    for (auto var = (n)-1; var != static_cast<decltype(var)>(-1); var--)
#define FOR(var, a, b) for (auto var = (a); var < (b); var++)
#define FOR_R(var, a, b) for (auto var = (b - 1); var > (a - 1); var--)
#define ALL(c) std::begin(c), std::end(c)

using namespace std;
using ll = long long;
using state = pair<ll, ll>;

// REP(idx, 3) { cout << idx; }  // 012
// REP_R(idx, 3) { cout << idx; }  // 210
// FOR(idx, 4, 7) { cout << idx; }  // 456
// FOR_R(idx, 4, 7) { cout << idx; }  // 654
// sort(ALL(v));

// ll mod = 1000000007;
// ll N, i, j, k, l;
// vector<ll> A, B;

map<state, ll> cost;  // 手数

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    // cin >> N;
    // REP(i, N) {
    //     cin >> j >> k;
    //     A.push_back(j);
    //     B.push_back(k);
    // }

    state init;  // TODO: 初期化
    cost[init] = 0;

    queue<state> que;  // cost の増分が +1 ではない時は priority_queue
    que.push(init);
    while (!que.empty()) {
        state cnt = que.front();
        que.pop();

        // TODO: cnt の次の状態
        vector<state> next_states;

        for (const auto next : next_states) {
            if (cost.count(next) == 0) {
                cost[next] = cost[cnt] + 1;
                que.push(next);
            }
        }
    }
}