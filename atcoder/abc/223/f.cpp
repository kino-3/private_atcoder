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

class BIT {
    ll n;             // 要素数
    vector<ll> node;  // node[0] (=0) は使用しない

   public:
    BIT(ll n) : n(n), node(n + 1, 0) {}  // 配列は 0 で初期化する

    ll sum(ll index) {
        // [1,index] の index 個の和
        index++;
        ll res = 0;
        while (index > 0) {
            res += node[index];
            // i  = ****1000 のとき
            // -i = ####1000 なので (####は****のビット反転)
            // (これは,-iが####0111に1を加えたものであるため)
            // i&-i = 00001000 となる(iの一番下の1だけとりだしたもの)
            index -= index & (-index);  // 一番下の1を0に変える
        }
        return res;
    }

    ll sum(ll left, ll right) {
        // [left, right] の 和
        return sum(right) - sum(left - 1);
    }

    void add(ll index, ll value) {
        index++;
        // index 番目に value を加える
        while (index <= n) {
            node[index] += value;
            index += index & (-index);
        }
    }
};

// 再帰型遅延評価セグメント木(区間加算・区間最小)
class LazySegmentTree {
    ll n;  // 要素数
    ll N;  // n 以上の最小の 2 の累乗
    const ll INF = numeric_limits<ll>::max();
    // node[idx] + lazy[idx]: idx の示す区間の最小値
    vector<ll> node;
    // lazy[idx]: idx の示す区間に一様に加算された値
    vector<ll> lazy;

   public:
    LazySegmentTree(vector<ll> values) {
        n = ll(values.size());
        N = 1;
        while (N < n) {
            N *= 2;
        }
        node = vector<ll>(2 * N - 1, INF);
        lazy = vector<ll>(2 * N - 1, 0);
        // 葉ノードの初期化
        for (ll i = 0; i < values.size(); i++) {
            node[i + N - 1] = values[i];
        }
        // 葉ノード以外の初期化
        for (ll i = N - 2; i >= 0; i--) {
            node[i] = min(node[2 * i + 1], node[2 * i + 2]);
        }
    }

    // lazy[idx] を node に移した後, 子ノードに lazy を伝播させる
    // これ自体は伝播処理をまとめただけなので,
    // 前処理・後処理は適切に行われる必要がある
    // なお, lazy[idx] が 区間[l,r) を示すように l, r が与えられなければならない
    void propagate(ll idx, ll l, ll r) {
        if (lazy[idx] != 0) {
            node[idx] += lazy[idx];
            if (r - l > 1) {
                // 伝播させるのは idx が葉ノードではないときのみ
                lazy[idx * 2 + 1] += lazy[idx];
                lazy[idx * 2 + 2] += lazy[idx];
            }
            lazy[idx] = 0;
        }
    }

    // [left, right) の区間に value を加算する
    // 外部から idx, l, r を指定することはない
    // 内部的には node[idx] を value 加算後の区間最小値に更新する
    void add(ll left, ll right, ll value, ll idx = 0, ll l = 0, ll r = -1) {
        // トップダウンに見ていく (外部から呼び出されたときは, [0,N) から始まる)
        if (r < 0) r = N;  // 外部から呼び出されたとき
        if (right <= l || r <= left) {
            // idx の区間が加算区間外
            propagate(idx, l, r);  // ※の処理ために node を更新
        } else if (left <= l && r <= right) {
            // idx の区間が加算区間に完全に含まれている場合
            lazy[idx] += value;
            propagate(idx, l, r);  // ※の処理ために node を更新
        } else {
            // idx の区間が加算区間に一部だけ含まれている場合
            propagate(idx, l, r);  // 子ノードに伝播するため
            add(left, right, value, 2 * idx + 1, l, (l + r) / 2);
            add(left, right, value, 2 * idx + 2, (l + r) / 2, r);
            // ここまでで, 子ノードの node は更新された
            node[idx] = min(node[2 * idx + 1], node[2 * idx + 2]);  // ※
        }
    }

    // [left, right) の最小値を返す
    // 外からは query(left, right) と呼び出す
    // 他の引数は add と同じ
    // 内部的には [left,right) かつ [l,r) を満たす区間の最小値を返す
    ll query(ll left, ll right, ll idx = 0, ll l = 0, ll r = -1) {
        if (r < 0) r = N;  // 外部から呼び出されたとき
        // lazy != 0 なら node を更新
        // これは ※※ のためである
        propagate(idx, l, r);
        if (right <= l || r <= left) {
            // idx の区間が検査対象区間外
            return INF;
        } else if (left <= l && r <= right) {
            // idx の区間が検査対象区間に完全に含まれている場合
            return node[idx];  // ※※
        } else {
            // idx の区間が検査対象区間に一部だけ含まれている場合
            ll value_l = query(left, right, 2 * idx + 1, l, (l + r) / 2);
            ll value_r = query(left, right, 2 * idx + 2, (l + r) / 2, r);
            return min(value_l, value_r);
        }
    }

    vector<ll> get_node() { return node; }
};

ll mod = 1000000007;
ll N, Q, i, j, k, l;
vector<ll> query, L, R;
string S;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> Q;
    cin >> S;
    REP(i, Q) {
        cin >> j >> k >> l;
        query.push_back(j);
        L.push_back(k - 1);
        R.push_back(l - 1);
    }

    BIT bit = BIT(N);
    LazySegmentTree seg = LazySegmentTree(vector<ll>(N, 0));
    REP(i, S.size()) {
        if (S[i] == '(') {
            bit.add(i, 1);
            seg.add(i, N, 1);
        } else {
            bit.add(i, -1);
            seg.add(i, N, -1);
        }
    }
    // REP(i, N) debug_print(bit.sum(i, i));
    // REP(i, N) debug_print(seg.query(i, i + 1));

    REP(i, Q) {
        if (query[i] == 1) {
            if (bit.sum(L[i], L[i]) * bit.sum(R[i], R[i]) < 0) {
                seg.add(L[i], R[i], -bit.sum(L[i], L[i]) * 2);
                bit.add(L[i], -bit.sum(L[i], L[i]) * 2);
                bit.add(R[i], -bit.sum(R[i], R[i]) * 2);
            }
            // REP(i, N) debug_print(bit.sum(i, i));
            // REP(i, N) debug_print(seg.query(i, i + 1));
        } else {
            bool flg = bit.sum(L[i], R[i]) == 0;
            if (bit.sum(L[i], L[i]) < 0) flg = false;
            if (seg.query(L[i], R[i] + 1) < seg.query(L[i], L[i] + 1) - 1)
                flg = false;
            if (flg) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
    }
}