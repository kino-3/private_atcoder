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

const ll mod = 998244353;
ll H, W, i, j, k, l;
string S;
vector<vector<bool>> A;
const ll LARGE = numeric_limits<long long>::max();

bool is_field(pair<ll, ll> pos) {
    if (pos.first < 0) return false;
    if (pos.first >= H) return false;
    if (pos.second < 0) return false;
    if (pos.second >= W) return false;
    return true;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> H >> W;

    A.resize(H);
    REP(i, H) {
        cin >> S;
        REP(j, W) {
            // . が移動可能とする
            A[i].push_back(S[j] == '.');
        }
    }

    pair<ll, ll> init = {0, 0};                        // TODO: 初期化
    vector<vector<ll>> cost(H, vector<ll>(W, LARGE));  // 手数
    cost[init.first][init.second] = 0;

    queue<pair<ll, ll>> que;  // cost の増分が +1 ではない時は priority_queue
    que.push(init);
    while (!que.empty()) {
        pair<ll, ll> cnt = que.front();
        que.pop();

        // TODO: cnt の次の状態
        vector<pair<ll, ll>> next_states;
        vector<pair<ll, ll>> direction = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for (auto d : direction) {
            ll row = cnt.first + d.first;
            ll col = cnt.second + d.second;
            if (is_field({row, col}) && A[row][col])
                next_states.push_back({row, col});
        }

        for (const auto next : next_states) {
            if (cost[next.first][next.second] == LARGE) {
                cost[next.first][next.second] = cost[cnt.first][cnt.second] + 1;
                que.push(next);
            }
        }
    }
}