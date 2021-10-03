#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

// 2^61 - 1 を法とする rolling hash
// ref. https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
class RollingHash {
    const ull MASK30 = (1ULL << 30) - 1;
    const ull MASK31 = (1ULL << 31) - 1;
    const ull MOD = (1ULL << 61) - 1;
    const ull MASK61 = MOD;
    const ull BASE = 100000007;

   public:
    RollingHash() {}

    // a*b mod MOD (a < MOD, b < MOD, MOD=2^61 とする)
    // 2^61-1 以上の値を返すことがあるが, 2^63 未満である
    ull mul(ull a, ull b) {
        // a = au * 2^31 + ad
        // a*b = (au*bu)*2^62 + (ad*bu+au*bd)*2^31 + ad*bd
        // ad*bu+au*bd = mid = midu*2^30 + midd とすると
        // a*b = (au*bu)*2^62 + midu*2^61 + midd*2^31 + ad*bd
        // 2^61 ≡ 1, 2^62 ≡ 2 より
        // a*b ≡ (au*bu)*2 + midu + midd*(2^31) + ad*bd
        // ここで,
        // au < 2^30, ad < 2^31 より,
        // (au*bu)*2 <= (2^30-1)*(2^30-1)*2
        //           <= 2^61 - 2^32 + 2
        // mid <= (2^30-1)*(2^31-1)*2 < (2^61-1)*2 = 2^62 -2
        // midu < 2^32, midd < 2^30
        // midd*2^31 < 2^61
        // (au*bu)*2 + midu + midd*(2^31) + ad*bd
        // < (2^61 - 2^32 + 2) + 2^32 + 2^61 + 2^62 -2
        // = 2^63
        ull au = a >> 31;
        ull ad = a & MASK31;
        ull bu = b >> 31;
        ull bd = b & MASK31;
        ull mid = ad * bu + au * bd;
        ull midu = mid >> 30;
        ull midd = mid & MASK30;
        return au * bu * 2 + midu + (midd << 31) + ad * bd;
    }

    // mod 2^61-1
    ull mod(ull x) {
        // x = xu * 2^61 + xd
        //   ≡ xu + xd
        ull xu = x >> 61;
        ull xd = x & MASK61;
        ull res = xu + xd;
        if (res >= MOD) res -= MOD;
        return res;
    }

    // data の中で最初に見つけた target の位置を返す
    // 無ければ -1 を返す
    ll find(string target, string data) {
        ll target_length = target.length();
        if (target_length > data.length()) return -1;
        ull target_hash = 0;
        ull data_hash = 0;
        ull pow = 1;  // BASE の target_length 乗
        for (ll i = 0; i < target_length; i++) {
            target_hash = mod(mul(target_hash, BASE) + target[i]);
            data_hash = mod(mul(data_hash, BASE) + data[i]);
            pow = mod(mul(pow, BASE));
        }
        if (target_hash == data_hash) return 0;
        ll max_idx = data.length() - target_length;
        for (ll idx = 1; idx <= max_idx; idx++) {
            // data の [idx,idx+target_length) が target に一致しているか
            data_hash =
                mod(mul(data_hash, BASE) + data[target_length + idx - 1] +
                    (MOD * 4 - mul(data[idx - 1], pow)));
            if (target_hash == data_hash) return idx;
        }
        return -1;
    }
};

int main() {
    RollingHash rolling_hash = RollingHash();
    assert(rolling_hash.mod((1ULL << 63) + 100) == 104);
    ull x = rolling_hash.mul(123456789123456789, 987654321987654321);
    assert(x % ((1ULL << 61) - 1) == 587437849037674763);
    cout << rolling_hash.find("RollingHash", "RollingHash") << endl;
    cout << rolling_hash.find("lin", "RollingHash") << endl;
    cout << rolling_hash.find("o", "RollingHash") << endl;
    cout << rolling_hash.find("h", "RollingHash") << endl;
    cout << rolling_hash.find("l", "RollingHash") << endl;
}