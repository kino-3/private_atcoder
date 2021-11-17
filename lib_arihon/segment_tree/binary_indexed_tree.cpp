#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 呼び出しは 0-indexed (範囲の取り方に注意)
// 動作確認: https://atcoder.jp/contests/typical90/tasks/typical90_bp
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

    // この関数は未検証
    void update(ll index, ll value) {
        ll cnt = sum(index, index);
        add(index, value - cnt);
    }
};

class RangeBIT {
    // 範囲に一様に値を加算できるようにした bit
    // 計算量のオーダーは BIT に同じ
    ll n;  // 要素数
    BIT coef_bit;
    BIT bias_bit;

   public:
    RangeBIT(ll n) : n(n), coef_bit(n), bias_bit(n) {}  // 配列は 0 で初期化する

    ll sum(ll index) {
        // [1,index] の index 個の和
        return coef_bit.sum(index) * index + bias_bit.sum(index);
    }

    ll sum(ll left, ll right) {
        // [left, right] の 和
        return sum(right) - sum(left - 1);
    }

    void add(ll left, ll right, ll value) {
        // [left, right] に value を加える
        bias_bit.add(left, -value * (left - 1));
        bias_bit.add(right + 1, value * right);
        coef_bit.add(left, value);
        coef_bit.add(right + 1, -value);
    }
};

int main() {
    // テスト
    BIT test_bit = BIT(10);
    test_bit.add(0, 10);
    test_bit.add(1, 20);
    test_bit.add(2, 3);
    assert(test_bit.sum(1, 1) == 20);
    assert(test_bit.sum(0, 2) == 33);
    assert(test_bit.sum(1) == 30);

    // 反転数
    // 0,1,...,n-1 を並び替えた配列 v_0,v_1,...,v_n-1 のバブルソートに必要な回数
    // i < j & v_i > v_j の個数に同じ
    int ans = 0;
    int n = 5;
    vector<int> v = {3, 1, 0, 4, 2};

    BIT bit = BIT(5);
    for (int j = 0; j < n; j++) {
        ans += j - bit.sum(v[j]);
        bit.add(v[j], 1);
    }
    cout << ans << endl;

    // RangeBIT
    RangeBIT rangeBit = RangeBIT(7);
    rangeBit.add(3, 5, 100);
    for (int i = 0; i <= 6; i++) {
        cout << rangeBit.sum(i) << endl;
    }
}