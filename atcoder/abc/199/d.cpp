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

#ifdef _DEBUG
void debug_print() { cout << endl; }
template <class Head, class... Tail>
void debug_print(Head &&head, Tail &&...tail) {
    std::cout << head << ", ";
    debug_print(std::forward<Tail>(tail)...);
}
ll DEBUG_PRINT_COUNT = 0;
void debug_print_count() {
    cout << "debug: " << DEBUG_PRINT_COUNT << endl;
    DEBUG_PRINT_COUNT++;
    assert(DEBUG_PRINT_COUNT < 10);
}
template <typename T>
void print_v(const vector<T> vec) {
    cout << "[";
    for (auto &&item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}
template <typename T>
void print_vv(const vector<T> vec) {
    for (auto &&item : vec) {
        print_v(item);
    }
}
template <typename K, typename V>
void print_map(const map<K, V> dict) {
    for (const auto v : dict) {
        cout << v.first << ":" << v.second << ", ";
    }
    cout << endl;
}
template <typename T>
void print_set(const set<T> data) {
    for (const auto v : data) {
        cout << v << ", ";
    }
    cout << endl;
}
template <typename T1, typename T2>
void print_pair(const pair<T1, T2> data) {
    cout << "(" << data.first << "," << data.second << ")";
    // cout << endl;
}
template <typename T1, typename T2, typename T3>
void print_tuple(const tuple<T1, T2, T3> data) {
    cout << "(";
    cout << get<0>(data) << "," << get<1>(data) << "," << get<2>(data);
    cout << ")";
    // cout << endl;
}
template <typename T1, typename T2>
void print_vp(const vector<pair<T1, T2>> vec) {
    for (auto &&item : vec) {
        print_pair(item);
    }
}
#else
void debug_print() {}
template <class Head, class... Tail>
void debug_print(Head &&head, Tail &&...tail) {}
void debug_print_count() {}
template <typename T>
void print_v(const vector<T> vec) {}
template <typename T>
void print_vv(const vector<T> vec) {}
template <typename K, typename V>
void print_map(const map<K, V> dict) {}
template <typename T>
void print_set(const set<T> data) {}
template <typename T1, typename T2>
void print_pair(const pair<T1, T2> data) {}
template <typename T1, typename T2, typename T3>
void print_tuple(const tuple<T1, T2, T3> data) {}
template <typename T1, typename T2>
void print_vp(const vector<pair<T1, T2>> vec) {}
#endif

// コスト無しグラフ
class Graph {
   public:
    ll V;                     // 頂点の個数
    vector<vector<ll>> conn;  // 隣接リスト(vector)
    vector<vector<ll>> prev;  // 有向グラフの場合の逆辺

    Graph(ll v) : V(v), conn(v), prev(v) {}

    // 有向グラフ
    void add_directed_edge(ll from, ll to) {
        conn[from].push_back(to);
        prev[to].push_back(from);
    }

    // 無向グラフ
    void add_undirected_edge(ll v1, ll v2) {
        add_directed_edge(v1, v2);
        add_directed_edge(v2, v1);
    }
};

ll mod = 998244353;
ll N, M, i, j, k, l;
ll ans = 1;
vector<vector<ll>> path;
vector<vector<ll>> root;

ll dfs(vector<ll> &tmp, vector<ll> &rt) {
    ll sz = tmp.size();
    ll cnt = rt[sz];
    vector<bool> tmp_ans = {true, true, true};
    for (auto v : path[cnt]) {
        ll di;
        REP(di, sz) {
            if (rt[di] == v) {
                tmp_ans[tmp[di]] = false;
            }
        }
    }
    ll i;
    ll t_ans = 0;
    if (tmp.size() == rt.size() - 1) {
        REP(i, 3) {
            if (tmp_ans[i]) t_ans++;
        }
    } else {
        REP(i, 3) {
            if (tmp_ans[i]) {
                auto new_tmp = tmp;
                new_tmp.push_back(i);
                t_ans += dfs(new_tmp, rt);
            }
        }
    }
    // print_v(tmp);
    // debug_print(t_ans);
    return t_ans;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;
    Graph graph = Graph(N);
    REP(i, M) {
        cin >> j >> k;
        graph.add_undirected_edge(j - 1, k - 1);
    }
    path = graph.conn;
    vector<bool> visited(N, false);
    while (true) {
        REP(i, N) {
            if (visited[i]) continue;
            queue<ll> que;
            que.push(i);
            vector<ll> t_root;
            t_root.push_back(i);
            visited[i] = true;
            while (!que.empty()) {
                auto cnt = que.front();
                que.pop();
                for (auto v : path[cnt]) {
                    if (!visited[v]) {
                        que.push(v);
                        visited[v] = true;
                        t_root.push_back(v);
                    }
                }
            }
            root.push_back(t_root);
        }
        REP(i, N) if (visited[i]) continue;
        break;
    }
    print_vv(root);
    ll ans = 1;
    REP(i, root.size()) {
        vector<ll> vo;
        ans *= dfs(vo, root[i]);
    }
    cout << ans << endl;
}