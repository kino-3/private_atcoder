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

class UnionFind2D {
   public:
    ll R;
    ll C;
    UnionFind uf;

    UnionFind2D(ll row, ll column) : R(row), C(column), uf(R * C) {}

    ll convert_2d_to_1d(pair<ll, ll> x) { return x.first * C + x.second; }

    pair<ll, ll> convert_1d_to_2d(ll x) { return {x / C, x % C}; }

    // 集合を併合する
    // 併合できたかを返す(すでに同じ木に属するなら併合不要なのでfalse)
    bool unite(pair<ll, ll> x, pair<ll, ll> y) {
        return uf.unite(convert_2d_to_1d(x), convert_2d_to_1d(y));
    }

    // 同じ木に属するか
    bool find(pair<ll, ll> x, pair<ll, ll> y) {
        return uf.find(convert_2d_to_1d(x), convert_2d_to_1d(y));
    }

    // 属する木の根を返す
    // (その過程で根まで辿ったノードを根に付ける)
    pair<ll, ll> root(pair<ll, ll> x) {
        return convert_1d_to_2d(uf.root(convert_2d_to_1d(x)));
    }

    // 集合の要素数を返す
    ll size(pair<ll, ll> x) { return uf.size(convert_2d_to_1d(x)); }
};

const ll mod = 998244353;
ll N, M, i, j, k, l;
string S;
vector<vector<bool>> A;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;

    A.resize(N);
    REP(i, N) {
        cin >> S;
        REP(j, M) { A[i].push_back(S[j] == '.'); }
    }

    ll ans = 0;
    vector<vector<ll>> cost(N, vector<ll>(M, -1));
    cost[0][0] = 0;

    while (true) {
        queue<state> que;
        REP(i, N) {
            REP(j, M) {
                if (cost[i][j] == ans) {
                    que.push({i, j});
                }
            }
        }
        // 道路を移動
        while (!que.empty()) {
            state cnt = que.front();
            que.pop();
            // TODO: cnt の次の状態
            vector<state> next_states;
            vector<state> move = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
            for (auto v : move) {
                ll x = cnt.first + v.first;
                ll y = cnt.second + v.second;
                if (x >= 0 && x < N && y >= 0 && y < M) {
                    if (A[x][y] && cost[x][y] == -1) {
                        next_states.push_back({x, y});
                    }
                }
            }
            for (const auto next : next_states) {
                cost[next.first][next.second] = ans;
                que.push(next);
            }
        }
        if (cost[N - 1][M - 1] >= 0) break;
        // 壁破壊
        ans++;
        REP(i, N) {
            REP(j, M) {
                if (cost[i][j] == ans - 1) {
                    REP(k, 5) {
                        REP(l, 5) {
                            if (k % 4 == 0 && l % 4 == 0) continue;
                            ll x = i + k - 2;
                            ll y = j + l - 2;
                            if (x >= 0 && x < N && y >= 0 && y < M) {
                                if (cost[x][y] == -1) {
                                    cost[x][y] = ans;
                                }
                            }
                        }
                    }
                }
            }
        }

        // print_vv(cost); break;
    }
    cout << cost[N - 1][M - 1] << endl;
}