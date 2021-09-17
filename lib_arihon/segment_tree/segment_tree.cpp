#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
void print_v(const vector<T> vec) {
    cout << "size: " << vec.size() << endl;
    cout << "[";
    for (auto &&item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}

// 最小値を考えるセグメント木
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

int main() {
    SegmentTree seg = SegmentTree(6);
    seg.init({10, 20, 30, 40, 50, 60});
    print_v(seg.get_node());
    cout << seg.query(1, 4) << endl;
    seg.update(3, 8);
    print_v(seg.get_node());
    cout << seg.query(1, 4) << endl;
}