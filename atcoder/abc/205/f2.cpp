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

struct edge {
    ll to;
    ll capacity;
    ll rev;  // graph[to][rev] が逆辺を表す
};

class Dinic {
    // graph[i] の要素 e は, i から e.to へあと e.capacity
    // だけ流せるという情報をもつ。
    // また, graph[e.to][e.rev] は e の逆辺である。
    vector<vector<edge>> graph;
    const ll INF = numeric_limits<ll>::max();
    vector<ll> level;
    vector<ll> iter;
    ll source;  // 流入口
    ll sink;    // 流出口

   public:
    Dinic(ll v) : graph(v), source(0), sink(v - 1), level(v, -1), iter(v, 0) {}

    void add_edge(ll from, ll to, ll capacity = 1LL) {
        graph[from].push_back({to, capacity, graph[to].size()});
        graph[to].push_back({from, 0, graph[from].size() - 1});  // 逆辺
    }

    void bfs() {
        // level に以下の情報を格納する
        // level[v] は source から v までに経由する(最小)ノード数
        // (ただし, 正の capacity の辺 (及び逆辺)のみ通過できる)
        // 到達不可能な場合は -1 とする
        std::fill(level.begin(), level.end(), -1);
        queue<ll> que;
        level[source] = 0;
        que.push(source);
        while (!que.empty()) {
            ll node = que.front();
            que.pop();
            for (const auto& edge : graph[node]) {
                if (edge.capacity > 0 && level[edge.to] < 0) {
                    // edge.to はまだ探索していない到達可能ノード
                    level[edge.to] = level[node] + 1;
                    que.push(edge.to);
                }
            }
        }
    }

    ll dfs(ll node, ll flow) {
        // node に flow だけ流し込もうとしたとき, 実際はどれだけ流れるか
        // 戻り値は flow 以下の値である
        if (node == sink) {
            return flow;
        }
        for (ll& i = iter[node]; i < graph[node].size(); i++) {
            // 2 回目以降に dfs が呼び出されたときは, 続きから探索する
            // iter[node] は i++ で書き換わる
            edge& edge = graph[node][i];
            if (edge.capacity > 0 && level[node] < level[edge.to]) {
                ll actual_flow = dfs(edge.to, min(flow, edge.capacity));
                if (actual_flow > 0) {
                    edge.capacity -= actual_flow;
                    graph[edge.to][edge.rev].capacity += actual_flow;
                    return actual_flow;
                }
            }
        }
        return 0;
    }

    ll exec(ll source_node, ll sink_node) {
        source = source_node;
        sink = sink_node;
        ll max_flow = 0;
        while (true) {
            bfs();
            if (level[sink] < 0) {
                return max_flow;
            }
            std::fill(iter.begin(), iter.end(), 0);
            ll flow;
            while ((flow = dfs(source, INF)) > 0) {
                max_flow += flow;
            }
        }
        return max_flow;
    }
};

class MaxFlowML {
   public:
    Dinic dinic;
    map<ll, ll> node_count;  // node_count[layer]: layer のノード数
    map<ll, ll> node_index;  // node_count[layer]: layer の最初のノードの index
    ll source_index;
    ll sink_index;

    // nodes は source 側からの各層のノード数
    MaxFlowML(vector<ll> nodes)
        : dinic(accumulate(nodes.begin(), nodes.end(), 2)),
          source_index(0),
          sink_index(accumulate(nodes.begin(), nodes.end(), 1)) {
        ll tmp = 1;
        for (ll i = 0; i < nodes.size(); i++) {
            node_count[i] = nodes[i];
            node_index[i] = tmp;
            tmp += nodes[i];
        }
    }

    void add_edge(pair<ll, ll> from, pair<ll, ll> to, ll capacity = 1LL) {
        assert(node_count.count(from.first) > 0);
        assert(from.second >= 0);
        assert(from.second < node_count[from.first]);
        assert(node_count.count(to.first) > 0);
        assert(to.second >= 0);
        assert(to.second < node_count[to.first]);
        ll from_index = node_index[from.first] + from.second;
        ll to_index = node_index[to.first] + to.second;
        dinic.add_edge(from_index, to_index, capacity);
    }

    void add_edge_from_source(pair<ll, ll> to, ll capacity = 1LL) {
        assert(node_count.count(to.first) > 0);
        assert(to.second >= 0);
        assert(to.second < node_count[to.first]);
        ll to_index = node_index[to.first] + to.second;
        dinic.add_edge(source_index, to_index, capacity);
    }

    void add_edge_to_sink(pair<ll, ll> from, ll capacity = 1LL) {
        assert(node_count.count(from.first) > 0);
        assert(from.second >= 0);
        assert(from.second < node_count[from.first]);
        ll from_index = node_index[from.first] + from.second;
        dinic.add_edge(from_index, sink_index, capacity);
    }

    ll exec() { return dinic.exec(source_index, sink_index); }
};

const ll mod = 998244353;  // 1000000007;
ll H, W, N, Q, i, j, k, l;
vector<ll> A, B, C, D;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> H >> W >> N;
    A.resize(N);
    B.resize(N);
    C.resize(N);
    D.resize(N);
    REP(i, N) {
        cin >> A[i];
        cin >> B[i];
        cin >> C[i];
        cin >> D[i];
    }
    REP(i, N) {
        A[i]--;
        B[i]--;
        C[i]--;
        D[i]--;
    }

    MaxFlowML max_flow = MaxFlowML({H, N, N, W});
    REP(i, H) max_flow.add_edge_from_source({0, i});
    REP(i, N) {
        FOR(j, A[i], C[i] + 1) { max_flow.add_edge({0, j}, {1, i}); }
    }
    REP(i, N) max_flow.add_edge({1, i}, {2, i});
    REP(i, N) {
        FOR(j, B[i], D[i] + 1) { max_flow.add_edge({2, i}, {3, j}); }
    }
    REP(i, W) max_flow.add_edge_to_sink({3, i});
    cout << max_flow.exec() << endl;
}