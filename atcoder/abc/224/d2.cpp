#include <bits/stdc++.h>
#define REP(var, n) for (decltype(n) var = 0; var < (n); var++)
#define REP_R(var, n) \
    for (auto var = (n)-1; var != static_cast<decltype(var)>(-1); var--)
#define FOR(var, a, b) for (auto var = (a); var < (b); var++)
#define FOR_R(var, a, b) for (auto var = (b - 1); var > (a - 1); var--)
#define ALL(c) std::begin(c), std::end(c)

using namespace std;
using ll = long long;
using state = string;

// REP(idx, 3) { cout << idx; }  // 012
// REP_R(idx, 3) { cout << idx; }  // 210
// FOR(idx, 4, 7) { cout << idx; }  // 456
// FOR_R(idx, 4, 7) { cout << idx; }  // 654
// sort(ALL(v));

template <typename T>
void debug_print(const T item) {
    cout << item << endl;
}
ll DEBUG_PRINT_COUNT = 0;
void debug_print_count() {
    cout << "debug: " << DEBUG_PRINT_COUNT << endl;
    DEBUG_PRINT_COUNT++;
    assert(DEBUG_PRINT_COUNT < 5);
}

ll N, i, j, k;
vector<vector<ll>> G(9, vector<ll>(0));

map<state, ll> cost;  // 手数

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    REP(i, N) {
        cin >> j >> k;
        G[j - 1].push_back(k - 1);
        G[k - 1].push_back(j - 1);
    }

    state init = "888888888";
    REP(i, 8) {
        cin >> j;
        init[j - 1] = i + '0';
    }
    // debug_print(init);
    cost[init] = 0;

    queue<state> que;  // cost の増分が +1 ではない時は priority_queue
    que.push(init);
    while (!que.empty()) {
        // debug_print_count();
        state cnt = que.front();
        que.pop();
        if (cnt == "012345678") {
            cout << cost[cnt] << endl;
            return 0;
        }
        // TODO: cnt の次の状態
        vector<state> next_states;
        REP(i, 9) {
            if (cnt[i] == '8') {
                for (const auto v : G[i]) {
                    state next = "";
                    next += cnt;
                    swap(next[i], next[v]);
                    next_states.push_back(next);
                }
            }
        }
        for (const auto next : next_states) {
            if (cost.count(next) == 0) {
                cost[next] = cost[cnt] + 1;
                que.push(next);
            }
        }
    }
    cout << -1 << endl;
}