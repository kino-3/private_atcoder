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

void debug_print() {
    cout << endl;
}
template <class Head, class... Tail>
void debug_print(Head&& head, Tail&&... tail) {
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
    for (const auto v: dict) {
        cout << v.first << ":" << v.second << ", ";
    }
    cout << endl;
}
template <typename T>
void print_set(const set<T> data) {
    for (const auto v: data) {
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

class UnionFind {
   public:
    // 根ノードなら -(データ数)
    // それ以外なら親ノード
    // が格納される
    std::vector<ll> data;

    UnionFind(ll size) : data(size, -1) {}

    // 集合を併合する
    // 併合できたかを返す(すでに同じ木に属するなら併合不要なのでfalse)
    bool unite(ll x, ll y) {
        x = root(x);
        y = root(y);
        if (x != y) {
            if (data[y] < data[x]) std::swap(x, y);
            // 要素数の大きな方(x)へyを合併する
            data[x] += data[y];
            data[y] = x;
        }
        return x != y;
    }

    // 同じ木に属するか
    bool find(ll x, ll y) { return root(x) == root(y); }

    // 属する木の根を返す
    // (その過程で根まで辿ったノードを根に付ける)
    ll root(ll x) { return (data[x] < 0) ? x : data[x] = root(data[x]); }

    // 集合の要素数を返す
    ll size(ll x) { return -data[root(x)]; }
};

class Tree {
   public:
    ll V;                         // 頂点の個数
    vector<vector<ll>> graph;     // 隣接リスト
    vector<ll> parent;            // 親ノード
    vector<vector<ll>> children;  // 子ノード
    vector<ll> size;   // 自身を root とする部分木の大きさ
    vector<ll> depth;  // 深さ
    vector<ll> memo;

    Tree(ll v) : V(v), graph(v), parent(v), children(v), size(v), depth(v) {}

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
        memo.push_back(v);
        return s;
    }

    ll lca(ll n1, ll n2) {
        while (depth[n1] > depth[n2]) n1 = parent[n1];
        while (depth[n1] < depth[n2]) n2 = parent[n2];
        while (n1 != n2) {
            n1 = parent[n1];
            n2 = parent[n2];
        }
        return n1;
    }

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

const ll mod = 998244353;
ll N, M, Q, i, j, k, l;
vector<ll> P, A, B, ans;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    P.resize(N);
    REP(i, N) {
        cin >> P[i];
        P[i] --;
    }
    cin >> M;
    A.resize(M);
    B.resize(M);
    REP(i, M) {
        cin >> A[i] >> B[i];
        A[i] --;
        B[i] --;
    }

    UnionFind uf = UnionFind(N);
    REP(i, M) {
        uf.unite(A[i], B[i]);
    }

    map<ll, vector<ll>> roots;
    REP(i, N) {
        roots[uf.root(i)].push_back(i);
    }
    map<pair<ll, ll>, ll> sousa;
    REP(i, M) {
        sousa[{A[i], B[i]}] = i + 1;
    }
    // debug_print(sousa[{0,1}]);

    for (auto v: roots) {
        // debug_print(v.first);
        // print_v(v.second);
        vector<ll> cnt;
        for (auto vv: v.second) {
            cnt.push_back(P[vv]);
        }
        vector<ll> tmp = cnt;
        sort(ALL(tmp));
        if (tmp != v.second) {
            cout << -1 << endl;
            return 0;
        }
        if (v.second.size() == 1) continue;
        // 木を作る
        map<ll, ll> node;
        REP(i, v.second.size()) {
            node[v.second[i]] = i;
        }
        UnionFind tmp_uf = UnionFind(v.second.size());
        Tree tree = Tree(v.second.size());
        map<pair<ll, ll>, ll> tree_sousa;
        REP(i, M) {
            if (node.count(A[i]) > 0 && node.count(B[i]) > 0) {
                if (!tmp_uf.find(node[A[i]], node[B[i]])) {
                    tmp_uf.unite(node[A[i]], node[B[i]]);
                    tree.add_edge(node[A[i]], node[B[i]]);
                    ll min_n = min(node[A[i]], node[B[i]]);
                    ll max_n = max(node[A[i]], node[B[i]]);
                    tree_sousa[{min_n, max_n}] = sousa[{A[i], B[i]}];
                }
            }
        }
        tree.exec(node[v.first]);
        // print_v(tree.memo);
        // print_v(v.second);
        // print_v(cnt);
        // for (auto vv: tree_sousa) {
        //     print_pair(vv.first);
        //     debug_print(vv.second);
        // }

        // print_v(tree.path(1, 4));
        map<ll, ll> tmp_node;
        REP(i, v.second.size()) {
            tmp_node[cnt[i]] = i;
        }
        // print_map(tmp_node);

        for (auto vv: tree.memo) {
            ll to_node = vv;
            ll from_node = tmp_node[v.second[vv]];
            // debug_print(from_node, to_node);

            ll tmp_from = from_node;
            ll tmp_to = to_node;
            vector<ll> path = tree.path(tmp_from, tmp_to);
            REP(i, path.size() - 1) {
                ll n1 = path[i];
                ll n2 = path[i + 1];
                ll c1 = cnt[n1];
                ll c2 = cnt[n2];
                swap(cnt[n1], cnt[n2]);
                tmp_node[c1] = n2;
                tmp_node[c2] = n1;
                // debug_print(n1, n2);
                ans.push_back(tree_sousa[{min(n1, n2), max(n1, n2)}]);
            }
        }
        // vector<ll> a_res;
        // vector<ll> a_cnt;
        // print_v(tree.memo);

        // for (auto vv: tree.memo) {
        //     a_res.push_back(v.second[vv]);
        //     a_cnt.push_back(cnt[vv]);
        // }
        // map<ll, ll> cnt2res;
        // REP(i, v.second.size()) {
        //     cnt2res[a_cnt[i]] = a_res[i];
        // }
        // REP(i, v.second.size()) {
        //     debug_print(node[cnt2res[a_res[i]]], node[a_res[i]]);
        // }
        // print_map(cnt2res);
        // print_v(a_res);
        // print_v(a_cnt);
    }
    cout << ans.size() << endl;
    for (auto v: ans) {
        cout << v << " ";
    }
    cout << endl;
}