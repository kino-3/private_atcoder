#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class BIT {
    ll n;             // 要素数
    vector<ll> node;  // node[0] (=0) は使用しない

   public:
    BIT(ll n) : n(n), node(n + 1, 0) {}  // 配列は 0 で初期化する

    ll sum(ll index) {
        // [1,index] の index 個の和
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
        // index 番目に value を加える
        while (index <= n) {
            node[index] += value;
            index += index & (-index);
        }
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
    // 反転数
    // 1,2,...,n を並び替えた配列 v_1,v_2,...,v_n のバブルソートに必要な回数
    // i < j & v_i > v_j の個数に同じ
    int ans = 0;
    int n = 5;
    vector<int> v = {4, 2, 1, 5, 3};

    BIT bit = BIT(5);
    for (int j = 0; j < n; j++) {
        ans += j - bit.sum(v[j]);
        bit.add(v[j], 1);
    }
    cout << ans << endl;

    // RangeBIT
    RangeBIT rangeBit = RangeBIT(7);
    rangeBit.add(3, 5, 100);
    for (int i = 1; i <= 7; i++) {
        cout << rangeBit.sum(i) << endl;
    }
}