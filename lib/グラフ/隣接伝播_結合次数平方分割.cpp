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
void debug_print(const T item) {
    cout << item << endl;
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

// クエリが隣接ノードへの伝播の場合に用いるグラフ
// 「hub -> hub以外」の伝播を遅延させるのがポイント
class Graph {
   public:
    ll V;                     // 頂点の個数
    vector<vector<ll>> conn;  // 隣接リスト(vector)
    vector<vector<ll>> prev;  // 有向グラフの場合の逆辺
    vector<bool> is_hub;
    vector<ll> hub;
    vector<vector<ll>> conn_hub;  // hub への接続
    vector<vector<ll>> prev_hub;  // hub からの接続
    // hub の state は正しいことが保証されている
    vector<ll> state;
    // query[node] = {time, state} (遅延伝播情報)
    // time: ノードからの最新のクエリが発行された時間
    // state: 発行されたときの node の正しい状態
    vector<pair<ll, ll>> query;
    // 「hub->hub以外」の伝播(_lazy_propagate)を除いた直近の更新が行われた時間
    vector<ll> updated;

    Graph(ll v)
        : V(v),
          conn(v),
          prev(v),
          conn_hub(v),
          prev_hub(v),
          query(v, {-1, -1}),
          updated(v, -1) {}

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

    // 状態の初期化 + hub の追加
    void initialize(vector<ll> init_state) {
        _check_hub();
        state = init_state;
    }

    // 次数の閾値はデフォルトで √(頂点数)
    void _check_hub(ll thresh = -1) {
        if (thresh == -1) thresh = ll(sqrt(V));
        is_hub.resize(V, false);
        REP(i, V) {
            if (conn[i].size() > thresh) {
                is_hub[i] = true;
                hub.push_back(i);
            }
        }
        REP(i, V) {
            for (const auto v : conn[i]) {
                if (is_hub[v]) conn_hub[i].push_back(v);
            }
            for (const auto v : prev[i]) {
                if (is_hub[v]) prev_hub[i].push_back(v);
            }
        }
    }

    // 「hub -> hub 以外」以外の伝播
    // TODO: 伝播する内容
    void _propagate(ll from, ll to) {
        state[to] = state[from];
        updated[to] = updated[from];
    }

    // 「hub -> hub 以外」の伝播
    // TODO: 伝播する内容
    void _lazy_propagate(ll from, ll to) { state[to] = query[from].second; }

    // node は hub 以外
    // TODO: hub -> node の伝播を考慮した
    // state[node] の正しい値の取得
    // 以下は上書きの場合
    void _update(ll node) {
        ll latest_updated_time = updated[node];
        for (const auto v : prev_hub[node]) {
            if (latest_updated_time < query[v].first) {
                _lazy_propagate(v, node);
                latest_updated_time = query[v].first;
            }
        }
    }

    // node: どの頂点からの伝播か
    // query_time(>=0): 何番目のクエリか
    void propagate(ll node, ll query_time) {
        if (is_hub[node]) {
            // state[node] は正しいことが保証される
            query[node] = {query_time, state[node]};
            updated[node] = query_time;
            for (const auto v : conn_hub[node]) {
                _propagate(node, v);  // hub -> hub のみ
            }
        } else {
            _update(node);
            // この時点で state[node] は正しい
            query[node] = {query_time, state[node]};
            updated[node] = query_time;
            for (const auto v : conn[node]) {
                _propagate(node, v);  // hub以外 -> all
            }
        }
    }

    // hub 以外の情報を全て更新する
    void update() {
        ll node;
        REP(node, V) {
            if (!is_hub[node]) {
                _update(node);
            }
        }
    }
};

ll mod = 998244353;
ll N, M, Q, i, j, k, l;
vector<ll> query;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M >> Q;

    Graph graph = Graph(N);
    REP(i, M) {
        cin >> j >> k;
        graph.add_undirected_edge(j - 1, k - 1);
        // graph.add_directed_edge(j - 1, k - 1);
    }

    vector<ll> init_state;
    REP(i, N) init_state.push_back(i + 1);

    graph.initialize(init_state);

    REP(i, Q) {
        cin >> j;
        query.push_back(j - 1);
    }

    REP(i, Q) { graph.propagate(query[i], i); }

    graph.update();

    REP(i, N) { cout << graph.state[i] << " "; }
    cout << endl;
}