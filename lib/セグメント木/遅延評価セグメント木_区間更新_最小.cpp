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

// 再帰型遅延評価セグメント木(区間更新・区間最小)
// ref. https://tsutaj.hatenablog.com/entry/2017/03/30/224339
// ref. https://smijake3.hatenablog.com/entry/2018/11/03/100133
class LazySegmentTree {
    ll n;  // 要素数
    ll N;  // n 以上の最小の 2 の累乗
    const ll INF = numeric_limits<ll>::max();
    // node[idx]: (flag[idx] == false の場合) idx の示す区間
    // (値が一様かは不問) の最小値を持つ
    // flag[idx] == true の場合, この値は保証されない
    vector<ll> node;
    // lazy[idx]: (flag[idx] == true の場合) idx の示す区間の値は一様である
    // ことを保証し, その一様な値を持つ (一様なので当然区間の最小値でもある)
    // flag[idx] == false の場合, この値は保証されない
    vector<ll> lazy;
    vector<bool> flag;  // lazy に必要な情報が入っているか

   public:
    LazySegmentTree(vector<ll> values) {
        n = ll(values.size());
        N = 1;
        while (N < n) {
            N *= 2;
        }
        node = vector<ll>(2 * N - 1, INF);
        lazy = vector<ll>(2 * N - 1);
        flag = vector<bool>(2 * N - 1, false);
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
    // flag[idx] を false にする
    // これ自体は伝播処理をまとめただけなので,
    // 前処理・後処理は適切に行われる必要がある
    // なお, lazy[idx] が 区間[l,r) を示すように l, r が与えられなければならない
    void propagate(ll idx, ll l, ll r) {
        if (flag[idx]) {
            node[idx] = lazy[idx];
            if (r - l > 1) {
                // 伝播させるのは idx が葉ノードではないときのみ
                lazy[idx * 2 + 1] = lazy[idx * 2 + 2] = lazy[idx];
                flag[idx * 2 + 1] = flag[idx * 2 + 2] = true;
            }
            flag[idx] = false;
        }
    }

    // [left, right) の区間を value に更新する
    // 外部から idx, l, r を指定することはない
    // 内部的には node[idx] を value 更新後の区間最小値に更新する
    // (flag[idx] はfalseになる)
    void update(ll left, ll right, ll value, ll idx = 0, ll l = 0, ll r = -1) {
        // トップダウンに見ていく (外部から呼び出されたときは, [0,N) から始まる)
        if (r < 0) r = N;  // 外部から呼び出されたとき
        if (right <= l || r <= left) {
            // idx の区間が更新区間外
            propagate(idx, l, r);  // ※の処理ために node を更新
        } else if (left <= l && r <= right) {
            // idx の区間が更新区間に完全に含まれている場合
            lazy[idx] = value;
            flag[idx] = true;
            propagate(idx, l, r);  // ※の処理ために node を更新
        } else {
            // idx の区間が更新区間に一部だけ含まれている場合
            propagate(idx, l, r);  // 子ノードに伝播するため
            update(left, right, value, 2 * idx + 1, l, (l + r) / 2);
            update(left, right, value, 2 * idx + 2, (l + r) / 2, r);
            // ここまでで, 子ノードの node は更新された
            node[idx] = min(node[2 * idx + 1], node[2 * idx + 2]);  // ※
        }
    }

    // [left, right) の最小値を返す
    // 外からは query(left, right) と呼び出す
    // 他の引数は update と同じ
    // 内部的には [left,right) かつ [l,r) を満たす区間の最小値を返す
    ll query(ll left, ll right, ll idx = 0, ll l = 0, ll r = -1) {
        if (r < 0) r = N;  // 外部から呼び出されたとき
        // flg[idx] == true なら (i.e. lazy が有効なら) node を更新
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

ll N, Q, i, j, s, t, x;
vector<ll> A, S, T, X;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    {  // test:
       // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_F
       // https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=6029963#1
        cin >> N >> Q;
        REP(i, Q) {
            cin >> j;
            if (j == 0) {
                cin >> s >> t >> x;
                A.push_back(0);
                S.push_back(s);
                T.push_back(t + 1);
                X.push_back(x);
            } else {
                cin >> s >> t;
                A.push_back(1);
                S.push_back(s);
                T.push_back(t + 1);
                X.push_back(0);
            }
        }
        LazySegmentTree seg = LazySegmentTree(vector<ll>(N, (1LL << 31) - 1));
        REP(i, Q) {
            if (A[i] == 0) {
                seg.update(S[i], T[i], X[i]);
            } else {
                cout << seg.query(S[i], T[i]) << endl;
            }
        }
    }
}