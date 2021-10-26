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

class SegmentTree {
    ll n;  // 要素数
    ll N;  // n 以上の最小の 2 の累乗
    const ll INF = numeric_limits<ll>::max();
    vector<ll> node;

   public:
    SegmentTree(ll n) : n(n) {
        N = 1;
        while (N < n) {
            N *= 2;
        }
        // 最大値で初期化する
        node = vector<ll>(2 * N - 1, INF);
    }

    void init(vector<ll> values) {
        // 葉ノードの初期化
        for (ll i = 0; i < values.size(); i++) {
            node[i + N - 1] = values[i];
        }
        // 葉ノード以外の初期化
        for (ll i = N - 2; i >= 0; i--) {
            node[i] = min(node[2 * i + 1], node[2 * i + 2]);
        }
    }

    void update(ll idx, ll value) {
        // 葉ノードの更新
        idx += N - 1;
        node[idx] = value;
        // 葉ノードの以外の更新
        while (idx > 0) {
            idx = (idx - 1) / 2;
            node[idx] = min(node[2 * idx + 1], node[2 * idx + 2]);
        }
    }

    ll query(ll left, ll right, ll idx = 0, ll n_left = 0, ll n_right = -1) {
        // [left, right) の最小値を返す
        // 外からは query(left, right) と呼び出す
        // idx は考えているノード番号で, [n_left, n_right) はその区間
        if (idx == 0) {
            n_right = N;
        }
        if (n_right <= left || right <= n_left) {
            return INF;  // 区間がかぶっていない
        } else if (left <= n_left && n_right <= right) {
            return node[idx];  // 区間がおおわれている
        } else {
            // 区間が部分的にかぶっている
            ll n_middle = (n_left + n_right) / 2;
            ll value_left = query(left, right, idx * 2 + 1, n_left, n_middle);
            ll value_right = query(left, right, idx * 2 + 2, n_middle, n_right);
            return min(value_left, value_right);
        }
    }

    vector<ll> get_node() { return node; }
};

ll W, N, i, j, k, l, r, v, w;
ll INF = 10000000000000000;
vector<ll> L, R, V;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> W >> N;
    REP(i, N) {
        cin >> j >> k >> l;
        L.push_back(j);
        R.push_back(k);
        V.push_back(l);
    }
    vector<ll> value(W + 1, INF);
    value[0] = 0;
    REP(i, N) {
        l = L[i];
        r = R[i];
        v = V[i];
        SegmentTree seg = SegmentTree(W + 1);
        seg.init(value);
        REP_R(w, W + 1) {
            // この時点で, (i-1) 番目までで w の重さの最大価値が -value[w]
            // (w - r ~ w - l の最小値) - v で更新
            ll left = max(w - r, 0LL);
            ll right = max(w - l + 1, 0LL);
            ll new_value = seg.query(left, right);
            new_value -= v;
            value[w] = min(new_value, value[w]);
        }
    }
    cout << (value[W] > 0 ? -1 : -value[W]) << endl;
}