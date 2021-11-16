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

template <typename T>
void debug_print(const T item) {
    cout << item << endl;
}
void debug_printp(const pair<ll, ll> item) {
    cout << item.first << "," << item.second << endl;
}
ll DEBUG_PRINT_COUNT = 0;
void debug_print_count() {
    cout << "debug: " << DEBUG_PRINT_COUNT << endl;
    DEBUG_PRINT_COUNT++;
    assert(DEBUG_PRINT_COUNT < 5);
}

// REP(idx, 3) { cout << idx; }  // 012
// REP_R(idx, 3) { cout << idx; }  // 210
// FOR(idx, 4, 7) { cout << idx; }  // 456
// FOR_R(idx, 4, 7) { cout << idx; }  // 654
// sort(ALL(v));

ll mod = 1000000007;
ll H, W, N, i, j, k, l;
vector<ll> R, C, A;

map<state, ll> cost;   // 手数
map<state, ll> value;  // - 書かれた数字

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> H >> W >> N;
    REP(i, N) {
        cin >> j >> k >> l;
        R.push_back(j - 1);
        C.push_back(k - 1);
        A.push_back(-l);
        value[{j - 1, k - 1}] = -l;
    }

    map<ll, vector<pair<ll, ll>>> row;
    map<ll, vector<pair<ll, ll>>> col;

    REP(i, N) {
        ll r = R[i];
        ll c = C[i];
        ll a = A[i];
        if (row.count(r) == 0) row[r] = vector<pair<ll, ll>>();
        row[r].push_back({a, c});
        if (col.count(c) == 0) col[c] = vector<pair<ll, ll>>();
        col[c].push_back({a, r});
    }
    for (auto it = row.begin(), e = row.end(); it != e; ++it) {
        sort(ALL(it->second));
    }
    for (auto it = col.begin(), e = col.end(); it != e; ++it) {
        sort(ALL(it->second));
    }

    queue<state> que;
    REP(i, N) {
        ll r = R[i];
        ll c = C[i];
        if (value[{r, c}] > row[r][0].first) continue;
        if (value[{r, c}] > col[c][0].first) continue;
        que.push({r, c});
        cost[{r, c}] = 0;
    }

    while (!que.empty()) {
        state cnt = que.front();
        que.pop();

        // TODO: cnt の次の状態
        vector<state> next_states;
        ll r = cnt.first;
        ll c = cnt.second;
        ll a = value[{r, c}];
        ll idx, tmp_idx;
        idx =
            distance(row[r].begin(), lower_bound(row[r].begin(), row[r].end(),
                                                 make_pair<ll, ll>(a + 1, -1)));
        tmp_idx = idx;
        while (tmp_idx < row[r].size()) {
            next_states.push_back({r, row[r][tmp_idx].second});
            if (row[r][idx].first != row[r][tmp_idx].first) break;
            tmp_idx++;
        }
        idx =
            distance(col[c].begin(), lower_bound(col[c].begin(), col[c].end(),
                                                 make_pair<ll, ll>(a + 1, -1)));
        tmp_idx = idx;
        while (tmp_idx < col[c].size()) {
            next_states.push_back({col[c][tmp_idx].second, c});
            if (col[c][idx].first != col[c][tmp_idx].first) break;
            tmp_idx++;
        }
        // debug_print_count();
        // for (const auto v : next_states) debug_printp(v);

        for (const auto next : next_states) {
            if (cost.count(next) == 0 || cost[next] < cost[cnt] + 1) {
                cost[next] = cost[cnt] + 1;
                que.push(next);
            }
        }
    }

    REP(i, N) {
        ll r = R[i];
        ll c = C[i];
        cout << cost[{r, c}] << endl;
    }
}