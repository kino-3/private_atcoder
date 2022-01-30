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

#ifdef _DEBUG
void debug_print() { cout << endl; }
template <class Head, class... Tail>
void debug_print(Head &&head, Tail &&...tail) {
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
    for (auto &&item : vec) {
        print_pair(item);
    }
}
#else
void debug_print() {}
template <class Head, class... Tail>
void debug_print(Head&& head, Tail&&... tail) {}
void debug_print_count() {}
template <typename T>
void print_v(const vector<T> vec) {}
template <typename T>
void print_vv(const vector<T> vec) {}
template <typename K, typename V>
void print_map(const map<K, V> dict) {}
template <typename T>
void print_set(const set<T> data) {}
template <typename T1, typename T2>
void print_pair(const pair<T1, T2> data) {}
template <typename T1, typename T2, typename T3>
void print_tuple(const tuple<T1, T2, T3> data) {}
template <typename T1, typename T2>
void print_vp(const vector<pair<T1, T2>> vec) {}
#endif

// 再帰型遅延評価セグメント木(区間更新・区間総和)
class LazySegmentTree {
    ll n;  // 要素数
    ll N;  // n 以上の最小の 2 の累乗
    // node[idx]: (flag[idx] == false の場合) idx の示す区間和
    // flag[idx] == true の場合, この値は保証されない
    vector<ll> node;
    // lazy[idx]: (flag[idx] == true の場合) idx の示す区間の値は一様である
    // ことを保証し, (その一様な値)*(ノード数)を持つ (これは区間和である)
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
        node = vector<ll>(2 * N - 1, 0);
        lazy = vector<ll>(2 * N - 1);
        flag = vector<bool>(2 * N - 1, false);
        // 葉ノードの初期化
        for (ll i = 0; i < values.size(); i++) {
            node[i + N - 1] = values[i];
        }
        // 葉ノード以外の初期化
        for (ll i = N - 2; i >= 0; i--) {
            node[i] = node[2 * i + 1] + node[2 * i + 2];
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
                lazy[idx * 2 + 1] = lazy[idx * 2 + 2] = lazy[idx] / 2;
                flag[idx * 2 + 1] = flag[idx * 2 + 2] = true;
            }
            flag[idx] = false;
        }
    }

    // [left, right) の区間を value に更新する
    // 外部から idx, l, r を指定することはない
    // 内部的には node[idx] を value 更新後の区間和に更新する
    // (flag[idx] はfalseになる)
    void update(ll left, ll right, ll value, ll idx = 0, ll l = 0, ll r = -1) {
        // トップダウンに見ていく (外部から呼び出されたときは, [0,N) から始まる)
        if (r < 0) r = N;  // 外部から呼び出されたとき
        if (right <= l || r <= left) {
            // idx の区間が更新区間外
            propagate(idx, l, r);  // ※の処理ために node を更新
        } else if (left <= l && r <= right) {
            // idx の区間が更新区間に完全に含まれている場合
            lazy[idx] = value * (r - l);
            flag[idx] = true;
            propagate(idx, l, r);  // ※の処理ために node を更新
        } else {
            // idx の区間が更新区間に一部だけ含まれている場合
            propagate(idx, l, r);  // 子ノードに伝播するため
            update(left, right, value, 2 * idx + 1, l, (l + r) / 2);
            update(left, right, value, 2 * idx + 2, (l + r) / 2, r);
            // ここまでで, 子ノードの node は更新された
            node[idx] = node[2 * idx + 1] + node[2 * idx + 2];  // ※
        }
    }

    // [left, right) の総和を返す
    // 外からは query(left, right) と呼び出す
    // 他の引数は update と同じ
    // 内部的には [left,right) かつ [l,r) を満たす区間の総和を返す
    ll query(ll left, ll right, ll idx = 0, ll l = 0, ll r = -1) {
        if (r < 0) r = N;  // 外部から呼び出されたとき
        // flg[idx] == true なら (i.e. lazy が有効なら) node を更新
        // これは ※※ のためである
        propagate(idx, l, r);
        if (right <= l || r <= left) {
            // idx の区間が検査対象区間外
            return 0;
        } else if (left <= l && r <= right) {
            // idx の区間が検査対象区間に完全に含まれている場合
            return node[idx];  // ※※
        } else {
            // idx の区間が検査対象区間に一部だけ含まれている場合
            ll value_l = query(left, right, 2 * idx + 1, l, (l + r) / 2);
            ll value_r = query(left, right, 2 * idx + 2, (l + r) / 2, r);
            return value_l + value_r;
        }
    }

    vector<ll> get_node() { return node; }
};

const ll mod = 998244353;  // 1000000007;
ll N, X, Q, i, j, k, l;
vector<ll> P, C, L, R;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> Q >> X;
    P.resize(N);
    REP(i, N) { cin >> P[i]; }
    C.resize(Q);
    L.resize(Q);
    R.resize(Q);
    REP(i, Q) { 
        cin >> C[i] >> L[i] >> R[i];
        L[i] --;
        R[i] --;
    }
    // init
    vector<ll> que;
    ll pos = -1;
    REP(i, N) {
        if (P[i] > X) {
            que.push_back(1);
        } else if (P[i] == X) {
            que.push_back(1);
            pos = i;
        } else {
            que.push_back(0);
        }
    }
    // print_v(que);
    // X 以上な場所
    LazySegmentTree seg = LazySegmentTree(que);
    REP(i, Q) {
        ll count = seg.query(L[i], R[i] + 1); // X 以上
        if (C[i] == 1) {
            ll c_0 = (R[i] - L[i] + 1 - count); // X 未満
            seg.update(L[i], L[i] + c_0, 0);
            seg.update(L[i] + c_0, R[i] + 1, 1);
            if (L[i] <= pos && pos <= R[i]) {
                pos = L[i] + c_0;
            }
        } else {
            seg.update(L[i], L[i] + count, 1);
            seg.update(L[i] + count, R[i] + 1, 0);
            if (L[i] <= pos && pos <= R[i]) {
                pos = L[i] + count - 1;
            }
        }
        // REP(i, N) {
        //     cout << seg.query(i, i+1);
        // }
        // cout << endl;
        // debug_print(pos);
    }
    cout << pos + 1 << endl;
}