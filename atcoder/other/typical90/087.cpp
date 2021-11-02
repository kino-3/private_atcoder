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

class WarshallFloyd {
   public:
    int V;                    // 頂点の個数
    vector<vector<ll>> dist;  // コスト
    const ll INF = numeric_limits<ll>::max();

    WarshallFloyd(int v) : V(v), dist(v, vector<ll>(v, INF)) {
        for (int i = 0; i < V; ++i) {
            dist[i][i] = 0;
        }
    }

    void add_edge(int from, int to, ll edge_cost) {
        dist[from][to] = edge_cost;
    }

    void exec() {
        for (int k = 0; k < V; ++k) {
            for (int i = 0; i < V; ++i) {
                for (int j = 0; j < V; ++j) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // from から to の最小コスト
    ll cost(int from, int to) { return dist[from][to]; }
};

ll N, P, K, i, j, k, l;
vector<vector<ll>> A;

ll count_way(ll X) {
    WarshallFloyd wf = WarshallFloyd(N);
    REP(i, N - 1) {
        FOR(j, i + 1, N) {
            wf.add_edge(i, j, A[i][j] < 0 ? X : A[i][j]);
            wf.add_edge(j, i, A[i][j] < 0 ? X : A[i][j]);
        }
    }
    wf.exec();
    ll way = 0;
    REP(i, N - 1) {
        FOR(j, i + 1, N) {
            if (wf.dist[i][j] <= P) way++;
        }
    }
    return way;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> P >> K;
    REP(i, N) {
        A.push_back(vector<ll>(0));
        REP(j, N) {
            cin >> k;
            A[i].push_back(k);
        }
    }
    // cout << count_way(1) << endl;
    // cout << count_way(2) << endl;
    // cout << count_way(3) << endl;
    // cout << count_way(4) << endl;
    // cout << count_way(5) << endl;

    k = count_way(1);
    ll count_1 = k;
    if (k < K) {
        cout << 0 << endl;
        return 0;
    }

    k = count_way(P + 1);
    if (k == K) {
        cout << "Infinity" << endl;
        return 0;
    } else if (k > K) {
        cout << 0 << endl;
        return 0;
    }

    // X == 1 のとき K 通り以上
    // X == inf のとき K 通り未満
    ll lb, ub;
    lb = 1;
    ub = P + 1;
    while (ub - lb > 1) {
        ll mid = (ub + lb) / 2;
        k = count_way(mid);
        if (k >= K) {
            lb = mid;
        } else {
            ub = mid;
        }
    }
    ll ans_ub = lb;  // K 通り以上となる X の最大値
    if (count_way(ans_ub) > K) {
        cout << 0 << endl;
        return 0;
    } else {
        if (count_1 == K) {
            cout << ans_ub << endl;
            return 0;
        } else {
            lb = 1;
            ub = ans_ub;
            while (ub - lb > 1) {
                ll mid = (ub + lb) / 2;
                k = count_way(mid);
                if (k == K) {
                    ub = mid;
                } else {
                    lb = mid;
                }
            }
            cout << ans_ub - ub + 1 << endl;
        }
    }
}