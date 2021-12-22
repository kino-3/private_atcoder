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

void debug_print() { cout << endl; }
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
    for (auto&& item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}
template <typename T>
void print_vv(const vector<T> vec) {
    for (auto&& item : vec) {
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
    for (auto&& item : vec) {
        print_pair(item);
    }
}

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

    void add_edge(ll from, ll to, ll capacity) {
        graph[from].push_back({to, capacity, graph[to].size()});
        graph[to].push_back({from, 0, graph[from].size() - 1});  // 逆辺
        debug_print(from, to, capacity);
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
    }
};

const ll RANGE = 200;          // 2000000;
vector<ll> spf(RANGE + 1, 0);  // spf[i]: i の最小の素因数
vector<ll> primes;             // RANGE 以下の素数のリスト

// RANGE 以下の n の素因数分解
// spf を用いる
map<ll, ll> get_prime_factor(ll n) {
    map<ll, ll> prime_factor;
    while (n > 1) {
        ll prime = spf[n];
        if (prime_factor.count(prime) > 0) {
            prime_factor[prime] += 1;
        } else {
            prime_factor[prime] = 1;
        }
        n /= prime;
    }
    return prime_factor;
}

const ll mod = 998244353;
ll N, M, Q, i, j, k, l;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    B.resize(N);
    REP(i, N) { cin >> A[i] >> B[i]; }

    // 線形篩 O(N)
    FOR(i, 2, RANGE + 1) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (const auto p : primes) {
            if (p > spf[i] || p * i > RANGE) break;
            spf[p * i] = p;
        }
    }
    // print_v(primes);

    ll node = 2 + N * 3 + primes.size();
    // debug_print(node);
    Dinic max_flow = Dinic(node);
    map<ll, ll> prime_node;

    REP(i, primes.size()) {
        prime_node[primes[i]] = 2 + N * 3 + i;
        max_flow.add_edge(2 + N * 3 + i, 3 * N + 1, 1);
    }
    REP(i, N) {
        max_flow.add_edge(3 * N, i, 1);
        max_flow.add_edge(i, i + N, 1);
        max_flow.add_edge(i, i + 2 * N, 1);
        for (auto v : get_prime_factor(A[i])) {
            max_flow.add_edge(i + N, prime_node[v.first], 1);
        }
        for (auto v : get_prime_factor(B[i])) {
            max_flow.add_edge(i + 2 * N, prime_node[v.first], 1);
        }
    }

    ll flow = max_flow.exec(3 * N, 3 * N + 1);

    //

    if (flow == N) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}