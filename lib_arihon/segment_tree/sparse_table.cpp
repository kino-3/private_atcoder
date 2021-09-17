#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
void print_v(const vector<T> vec) {
    cout << "size: " << vec.size() << endl;
    cout << "[";
    for (auto&& item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}

class SparseTable {
    ll n;     // 要素数
    ll N;     // n 以上の最小の 2 の累乗
    int exp;  // 2^exp = N
    const ll INF = numeric_limits<ll>::max();
    vector<ll> explist;  // [1,2,4,...,2^(exp)]
    vector<vector<ll>> table;

   public:
    SparseTable(ll n) : n(n) {
        N = 1;
        explist.push_back(1);
        exp = 0;
        while (N < n) {
            N *= 2;
            explist.push_back(N);
            exp += 1;
        }
        // 最大値で初期化する
        ll blank = 0;
        for (int i = 0; i < exp; i++) {
            table.push_back(vector<ll>(n - blank, INF));
            blank = blank * 2 + 1;
        }
    }

    void init(vector<ll> values) {
        // 0 行目
        for (ll i = 0; i < values.size(); i++) {
            table[0][i] = values[i];
        }
        // i 行目
        ll diff = 1;
        for (int i = 1; i < exp; i++) {
            for (ll j = 0; j < table[i].size(); j++) {
                table[i][j] = min(table[i-1][j], table[i-1][j + diff]);
            }
            diff *= 2;
        }
    }

    ll query(ll left, ll right) {
        // [left, right)
        auto itr = lower_bound(explist.begin(), explist.end(), right - left);
        int low = distance(explist.begin(), itr) - 1;
        return min(table[low][left], table[low][right - (*itr) / 2]);
    }

    vector<vector<ll>> get_table() { return table; }
};

int main() {
    SparseTable table = SparseTable(8);
    table.init({5, 3, 7, 9 ,6, 4, 1, 2});
    for (const auto& low : table.get_table()) {
        print_v(low);
    }
    cout << table.query(0, 8) << endl;
    cout << table.query(2, 5) << endl;
    cout << table.query(2, 6) << endl;
    cout << table.query(2, 7) << endl;
}