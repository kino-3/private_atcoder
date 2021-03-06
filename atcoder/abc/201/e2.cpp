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

// ????????? root ???????????????????????????????????????????????????????????????
struct subtree_info {
    ll sz_s;  // root ??????????????????
    ll sz_d;  // root ?????????????????????
};
// ???????????????????????????????????????
// ?????? -> ??? -> ?????? ?????????????????????????????????????????????????????????
struct parent_info {
    ll sz_s;  // ????????????????????????
    ll sz_d;  // ???????????????????????????
};

// ????????????DP (???????????????????????????)
// ????????????: https://atcoder.jp/contests/abc222/tasks/abc222_f
class Tree {
   public:
    ll V;                         // ???????????????
    vector<map<ll, ll>> graph;    // ???????????????{node,cost}
    vector<ll> parent;            // ????????????
    vector<vector<ll>> children;  // ????????????
    vector<subtree_info> subtree_i;
    vector<parent_info> parent_i;

    Tree(ll v) : V(v), graph(v) {}

    void add_edge(ll n1, ll n2, ll cost = 1) {
        graph[n1][n2] = cost;
        graph[n2][n1] = cost;
    }

    void reset_data() {
        parent.clear();
        children.clear();
        subtree_i.clear();
        parent_i.clear();
        parent.resize(V);
        children.resize(V);
        subtree_i.resize(V);
        parent_i.resize(V);
    }

    ll exec() {
        // ???????????? 2 ???????????????
        if (V == 1) {
            return 0;
        } else if (V == 2) {
            return graph[0][1];
        }
        reset_data();
        // ???????????? 3 ???????????????, ???????????? 2 ????????????????????????
        ll root = -1;
        REP(i, V) {
            if (graph[i].size() >= 2) {
                root = i;
                break;
            }
        }
        // ???????????????????????????
        compute_subtree(root);
        // ???????????????
        return compute_ans(root);
    }

    // ?????? v ????????????????????????????????????
    void compute_subtree(ll v, ll parent_of_v = -1) {
        parent[v] = parent_of_v;
        for (const auto &child : graph[v]) {
            ll node = child.first;
            if (node == parent_of_v) continue;
            children[v].push_back(node);
            compute_subtree(node, v);
        }
        // ?????????????????????????????? subtree_i ????????????
        if (children[v].size() == 0) {
            // TODO: ????????????
            subtree_i[v].sz_s = 1;  // ???
            subtree_i[v].sz_d = 0;
        } else {
            // TODO: ??????????????????
            subtree_i[v].sz_s = 1;  // ???
            subtree_i[v].sz_d = 0;
            for (const auto &cv : children[v]) {
                if (graph[v][cv] == 0) {
                    subtree_i[v].sz_s += subtree_i[cv].sz_s;
                    subtree_i[v].sz_d += subtree_i[cv].sz_d;
                } else {
                    subtree_i[v].sz_s += subtree_i[cv].sz_d;
                    subtree_i[v].sz_d += subtree_i[cv].sz_s;
                }
            }
        }
    }

    ll compute_ans(ll v) {
        // debug_print(v, subtree_i[v].sz_s, subtree_i[v].sz_d);
        // ????????????
        // ?????????
        if (parent[v] == -1) {
            parent_i[v].sz_s = subtree_i[v].sz_s;
            parent_i[v].sz_d = subtree_i[v].sz_d;
        } else {
            if (graph[v][parent[v]] == 0) {
                parent_i[v].sz_s = parent_i[parent[v]].sz_s;
                parent_i[v].sz_d = parent_i[parent[v]].sz_d;
            } else {
                parent_i[v].sz_s = parent_i[parent[v]].sz_d;
                parent_i[v].sz_d = parent_i[parent[v]].sz_s;
            }
        }
        ll ans = 0;
        for (const auto &child : graph[v]) {
            if (child.first == parent[v]) continue;
            ans += compute_ans(child.first);
        }
        // debug_print(v, parent_i[v].sz_s, parent_i[v].sz_d);
        // v - parent[v] ??????????????????
        if (parent[v] != -1 && graph[v][parent[v]] > 0) {
            auto pv = parent_i[parent[v]];
            auto st = subtree_i[v];
            ll ans1 = st.sz_s * (pv.sz_s - st.sz_d);
            ll ans2 = st.sz_d * (pv.sz_d - st.sz_s);
            ans += ans1 + ans2;
        }
        // debug_print(v, ans);
        return ans;
    }
};

// input
// N
// a_1   b_1
// a_2   b_2
//  :
// a_N-1 a_N-1

ll N, i, j, k, l;
vector<ll> A, B;
vector<std::bitset<100>> C;
const ll mod = 1000000007;  // ;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    REP(i, N - 1) {
        cin >> j >> k >> l;
        A.push_back(j - 1);
        B.push_back(k - 1);
        std::bitset<100> bs(l);
        C.push_back(bs);
    }

    ll ans = 0;
    ll pow = 1;
    REP(i, 60) {
        Tree tree = Tree(N);
        REP(j, N - 1) {
            // debug_print(A[j], B[j], int(C[j][i]));
            tree.add_edge(A[j], B[j], int(C[j][i]));
        }
        ll res = tree.exec();
        debug_print(res);
        res %= mod;
        ans += res * pow;
        ans %= mod;
        pow *= 2;
        pow %= mod;
    }
    cout << ans << endl;
}