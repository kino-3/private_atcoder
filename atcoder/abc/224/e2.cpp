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

template <typename T>
void print_v(const vector<T> vec) {
    cout << "size: " << vec.size() << endl;
    cout << "[";
    for (auto &&item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}

template <typename T>
void debug_print(const T item) {
    cout << item << endl;
}
ll DEBUG_PRINT_COUNT = 0;
void debug_print_count() {
    cout << "debug: " << DEBUG_PRINT_COUNT << endl;
    DEBUG_PRINT_COUNT++;
    assert(DEBUG_PRINT_COUNT < 10);
}

ll mod = 1000000007;
ll H, W, N, i, j, k, l;
map<ll, pair<ll, ll>> pos;     // idx -> (x, y)
map<ll, vector<ll>> cost_idx;  // cost -> idx

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> H >> W >> N;
    vector<ll> ans(N);
    vector<ll> maxH(H, 0);
    vector<ll> maxW(W, 0);
    REP(i, N) {
        cin >> j >> k >> l;
        pos[i] = {j - 1, k - 1};
        cost_idx[-l].push_back(i);
    }
    for (auto it = cost_idx.begin(); it != cost_idx.end(); it++) {
        for (const auto v : it->second) {
            ans[v] = max(maxH[pos[v].first], maxW[pos[v].second]);
        }
        for (const auto v : it->second) {
            maxH[pos[v].first] = max(maxH[pos[v].first], ans[v] + 1);
            maxW[pos[v].second] = max(maxW[pos[v].second], ans[v] + 1);
        }
    }
    REP(i, N) cout << ans[i] << endl;
}