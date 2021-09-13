#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 約数関連

ll gcd(ll a, ll b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

ll extgcd(ll a, ll b, ll& x, ll& y) {
    // ax + by = gcd(a,b) を満たす解を x, y に代入し,
    // gcd(a, b) を返す
    int d = a;
    if (b != 0) {
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    } else {
        x = 1;
        y = 0;
    }
    return d;
}

int main() {
    cout << gcd(30, 48) << endl;
    ll x, y;
    cout << extgcd(30, 48, x, y) << endl;
    cout << x << " " << y << endl;
}