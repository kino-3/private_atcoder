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
    for (auto&& item : vec) {
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

class Tree {
   public:
    ll V;                         // 頂点の個数
    vector<vector<ll>> graph;     // 隣接リスト
    vector<ll> parent;            // 親ノード
    vector<vector<ll>> children;  // 子ノード
    vector<ll> size;  // 自身を root とする部分木の大きさ
    vector<ll> depth;

    Tree(ll v) : V(v), graph(v), parent(v), children(v), size(v), depth(v) {}

    void add_edge(ll n1, ll n2) {
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }

    // 頂点 v で吊ったときの木探索
    ll exec(ll v, ll parent_of_v = -1) {
        // if (parent_of_v == -1) {}
        parent[v] = parent_of_v;
        ll s = 1;
        for (const auto& child : graph[v]) {
            if (child == parent_of_v) continue;
            depth[child] = depth[v] + 1;
            s += exec(child, v);
            children[v].push_back(child);
        }
        size[v] = s;
        return s;
    }
};

ll mod = 998244353;
ll N, M, K, i, j, k, l;
vector<ll> A;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M >> K;
    REP(i, M) {
        cin >> j;
        A.push_back(j - 1);
    }
    Tree tree = Tree(N);
    REP(i, N - 1) {
        cin >> j >> k;
        tree.add_edge(j - 1, k - 1);
    }
    tree.exec(N - 1);

    vector<ll> count(N - 1, 0);
    REP(i, M - 1) {
        ll left = A[i];
        ll right = A[i + 1];
        vector<ll> edges;
        while (tree.depth[left] != tree.depth[right]) {
            if (tree.depth[left] > tree.depth[right]) {
                edges.push_back(left);
                left = tree.parent[left];
            } else {
                edges.push_back(right);
                right = tree.parent[right];
            }
        }
        while (left != right) {
            edges.push_back(left);
            edges.push_back(right);
            left = tree.parent[left];
            right = tree.parent[right];
        }
        for (const auto v : edges) {
            count[v]++;
        }
        // print_v(edges);
    }
    // print_v(count);
    ll total = 0;
    for (const auto v : count) {
        total += v;
    }
    if (total < abs(K)) {
        cout << 0 << endl;
        return 0;
    }
    if (abs(total - K) % 2 > 0) {
        cout << 0 << endl;
        return 0;
    }
    ll red = (K + total) / 2;  // 赤い辺を通る回数

    vector<ll> dp(red + 1, 0);
    dp[0] = 1;
    REP(i, N - 1) {
        ll c = count[i];
        REP_R(j, red + 1) {
            if (j + c <= red) {
                dp[j + c] += dp[j];
                dp[j + c] %= mod;
            }
        }
    }
    cout << dp[red] << endl;
}