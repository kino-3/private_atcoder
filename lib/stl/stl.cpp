#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <class T>
void assert_same(T actual, T expected) {
    assert(abs(actual - expected) < 1e-5);
}

// ref. https://qiita.com/e869120/items/518297c6816adb67f9a5
int main() {
    { assert(abs(-123) == 123); }
    {
        assert_same(M_PI, 3.141592);
        assert_same(sin(M_PI / 6), 0.5);
        assert_same(atan2(sqrt(3), 1.0), M_PI / 3);  // (y, x) -> [-pi, pi]
    }
    {
        string str = "ABC";
        str += "abc";
        str += 'd';
        assert(str == "ABCabcd");
        assert(str.size() == 7);
        assert(str[2] == 'C');
        assert(str.substr(2) == "Cabcd");
        assert(str.substr(2, 3) == "Cab");
    }
    {
        assert(min(10, 2) == 2);
        assert(min({10, 20, 3, 40}) == 3);
        vector<ll> v = {10, 20, 30, 40, 10, 20, 3, 40};
        auto iter = min_element(v.begin(), v.end());
        assert(*iter == 3);
        assert(iter - v.begin() == 6);
    }
    {
        ll a = 1, b = 2;
        swap(a, b);
        assert(a == 2 && b == 1);
    }
    { assert(__gcd(24, 16) == 8); }
    {
        int time = clock();
        ll j = 0;
        for (ll i = 0; i < 1e7; i++) j += i;
        cout << j << endl;
        cout << double(clock() - time) / CLOCKS_PER_SEC << " sec" << endl;
    }
    {
        string str = "japan";
        reverse(str.begin(), str.end());
        assert(str == "napaj");
        sort(str.begin(), str.end());
        assert(str == "aajnp");
        str = "qwertyqwerty";
        assert(distance(str.begin(), find(str.begin(), str.end(), 'w')) == 1);
        assert(distance(str.begin(), find(str.begin() + 4, str.end(), 'w')) ==
               7);
    }
    {
        vector<int> v = {2, 3, 1};
        do {
            // 231, 312, 321 と辞書順で最後まで
            cout << v[0] << v[1] << v[2] << endl;
        } while (next_permutation(v.begin(), v.end()));
    }
    {
        // 2 進数表記で 1 の個数
        assert(__builtin_popcount(10) == 2);
        // long long に対応
        assert(__builtin_popcountll((1LL << 59) - 1) == 59);
    }
    {
        bitset<77> bs1(10);  // 77 桁の [0,0,...,0,0,1,0,1,0] のようなもの
        bitset<77> bs2("1100");  // [0,0,...,0,0,1,1,0,0]
        assert(bs1[3] == 1 && bs1[2] == 0 && bs1[1] == 1 && bs1[0] == 0);
        assert(bs1.count() == __builtin_popcount(10));
        bs1.set(12);  // 1 に書き換え
        assert(bs1[12] == 1);
        bs1.reset(12);  // 0 に書き換え
        assert(bs1[12] == 0);
        cout << "and:" << (bs1 & bs2) << endl;
        cout << " or:" << (bs1 | bs2) << endl;
        cout << "xor:" << (bs1 ^ bs2) << endl;
    }
}