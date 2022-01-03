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

class Tree {
   public:
    ll V;                         // 頂点の個数
    vector<vector<ll>> graph;     // 隣接リスト
    vector<ll> parent;            // 親ノード
    vector<vector<ll>> children;  // 子ノード
    vector<ll> size;  // 自身を root とする部分木の大きさ
    vector<vector<ll>> ancestor;  // ancestor[i][j]: j の 2^i 階層上の祖先
    vector<ll> depth;             // 深さ
    vector<vector<ll>> depth_node;  // その深さの node

    Tree(ll v)
        : V(v),
          graph(v),
          parent(v),
          children(v),
          size(v),
          depth(v),
          depth_node(v) {}

    void add_edge(ll n1, ll n2) {
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }

    // 頂点 v で吊ったときの木探索
    ll exec(ll v, ll parent_of_v = -1) {
        if (parent_of_v == -1) {
            depth[v] = 0;
        }
        parent[v] = parent_of_v;
        ll s = 1;
        for (const auto &child : graph[v]) {
            if (child == parent_of_v) continue;
            depth[child] = depth[v] + 1;
            s += exec(child, v);
            children[v].push_back(child);
        }
        size[v] = s;
        depth_node[depth[v]].push_back(v);
        return s;
    }

    void calc_ancestor() {
        ancestor.push_back(parent);
        REP(i, 19) {
            ancestor.push_back(vector<ll>(V, -1));
            REP(j, V) {
                if (ancestor[i][j] == -1) {
                    ancestor[i + 1][j] = -1;
                } else {
                    ancestor[i + 1][j] = ancestor[i][ancestor[i][j]];
                }
            }
        }
    }

    ll get_ancestor(ll node, ll distance) {
        ll cnt = node;
        ll step = 0;
        while (distance > 0) {
            if (distance % 2 == 1) {
                cnt = ancestor[step][cnt];
            }
            distance /= 2;
            step++;
        }
        return cnt;
    }

    // LCA (O(n))
    ll lca(ll n1, ll n2) {
        while (depth[n1] > depth[n2]) n1 = parent[n1];
        while (depth[n1] < depth[n2]) n2 = parent[n2];
        while (n1 != n2) {
            n1 = parent[n1];
            n2 = parent[n2];
        }
        return n1;
    }

    // (始点と終点を含む)経路
    vector<ll> path(ll from_node, ll to_node) {
        vector<ll> res;
        ll path_lca = lca(from_node, to_node);
        while (from_node != path_lca) {
            res.push_back(from_node);
            from_node = parent[from_node];
        }
        vector<ll> rev_path;
        while (to_node != path_lca) {
            rev_path.push_back(to_node);
            to_node = parent[to_node];
        }
        reverse(rev_path.begin(), rev_path.end());
        res.push_back(path_lca);
        for (auto v : rev_path) {
            res.push_back(v);
        }
        return res;
    }
};

// input
// N
// a_1   b_1
// a_2   b_2
//  :
// a_N-1 a_N-1

ll N, Q, i, j, k;
vector<ll> U, D;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    Tree tree = Tree(N);
    REP(i, N - 1) {
        cin >> j;
        j--;
        tree.add_edge(i + 1, j);
    }
    cin >> Q;
    U.resize(N);
    D.resize(N);
    REP(i, Q) {
        cin >> U[i];
        cin >> D[i];
        U[i]--;
    }
    tree.exec(0);
    tree.calc_ancestor();
    // print_v(tree.parent);
    // print_v(tree.depth);
    // print_vv(tree.ancestor);
    print_vv(tree.depth_node);
    vector<map<ll, ll>> depth_node_index;
    for (auto v : tree.depth_node) {
        map<ll, ll> tmp;
        REP(i, v.size()) { tmp[v[i]] = i; }
        depth_node_index.push_back(tmp);
    }

    REP(i, Q) {
        auto &nodes = tree.depth_node[D[i]];
        ll u_dist = tree.depth[U[i]];
        ll dist = D[i] - u_dist;
        if (dist < 0) {
            cout << 0 << '\n';
            continue;
        }
        ll ans = 0;
        {
            // 条件を満たす最小値を求める
            ll lb = -1;  // これは条件を満たさない必要がある
            ll ub = nodes.size() - 1;  // これは条件を満たす必要がある
            auto &lmap = depth_node_index[u_dist];
            while (ub - lb > 1) {
                ll mid = (ub + lb) / 2;  // mid は lb の初期値にはならない
                ll anc = tree.get_ancestor(nodes[mid], dist);
                if (lmap[anc] >= lmap[D[i]]) {
                    ub = mid;
                } else {
                    lb = mid;
                }
            }
            ans -= ub;
        }
        {
            // 条件を満たす最大値を求める
            ll lb = 0;  // これは条件を満たす必要がある
            ll ub = nodes.size();  // これは条件を満たさない必要がある
            auto &lmap = depth_node_index[u_dist];
            while (ub - lb > 1) {
                ll mid = (ub + lb) / 2;  // mid は ub の初期値にはならない
                ll anc = tree.get_ancestor(nodes[mid], dist);
                if (lmap[anc] <= lmap[D[i]]) {
                    lb = mid;
                } else {
                    ub = mid;
                }
            }
            ans += lb;
        }
        cout << ans << '\n';
    }
    cout << endl;
}