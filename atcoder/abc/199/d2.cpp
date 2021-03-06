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
void debug_print(Head&& head, Tail&&... tail) {}
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

// ????????????????????????????????????
class Graph {
   public:
    ll V;                      // ???????????????
    vector<vector<ll>> graph;  // ???????????????
    // ???????????? 1 ???????????????????????????
    // result[0].first ???????????????????????????????????????????????????????????????????????????
    // second ???????????????????????????????????? (???????????????????????????)
    vector<pair<vector<ll>, vector<ll>>> result;

    Graph(ll v) : V(v), graph(v) {}

    void add_edge(ll n1, ll n2) {
        assert(n1 != n2);
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }

    // ??????????????????????????????????????????
    // true ??????????????????????????? result ??????????????????
    bool exec() {
        // 0: ?????????
        // 1: res.first ?????????
        // -1: res.second ?????????
        vector<ll> checked = vector<ll>(V, 0);
        ll tmp = -1;  // ?????????????????????
        while (tmp < V - 1) {
            tmp++;
            if (checked[tmp] != 0) continue;
            pair<vector<ll>, vector<ll>> res;
            queue<ll> que;  // bfs
            que.push(tmp);
            res.first.push_back(tmp);
            checked[tmp] = 1;
            while (!que.empty()) {
                ll cnt = que.front();
                que.pop();
                for (auto v : graph[cnt]) {
                    if (checked[v] != 0) {
                        // ???????????????????????????
                        if (checked[v] * checked[cnt] == 1) {
                            return false;
                        }
                    } else {
                        // ??????????????????
                        if (checked[cnt] == 1) {
                            res.second.push_back(v);
                            checked[v] = -1;
                            que.push(v);
                        } else {
                            res.first.push_back(v);
                            checked[v] = 1;
                            que.push(v);
                        }
                    }
                }
            }
            result.push_back(res);
        }
        return true;
    }
};

// input
// N
// a_1   b_1
// a_2   b_2
//  :
// a_N-1 a_N-1

ll N, M, i, j, k;
vector<pair<ll, ll>> edge;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;
    REP(i, M) {
        cin >> j >> k;
        edge.push_back({j - 1, k - 1});
    }

    ll ans = 0;
    REP(i, 1 << N) {
        std::bitset<100> bs(i); // ?????????????????????
        Graph g = Graph(N);
        bool possible = true;
        for (auto e: edge) {
            if (bs[e.first] && bs[e.second]) {
                possible = false;
                break;
            }
            if (!bs[e.first] && !bs[e.second]) {
                g.add_edge(e.first, e.second);
            }
        }
        if (!possible) continue;
        if (g.exec()) {
            ll sz = g.result.size();
            REP(j, N) {
                if (bs[j]) sz--;
            }
            ll tmp = 1;
            REP(j, sz) tmp *= 2;
            ans += tmp;
        }
    }
    cout << ans << endl;
}