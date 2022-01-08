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
void debug_print() {
    cout << endl;
}
template <class Head, class... Tail>
void debug_print(Head&& head, Tail&&... tail) {
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
    for (const auto v: dict) {
        cout << v.first << ":" << v.second << ", ";
    }
    cout << endl;
}
template <typename T>
void print_set(const set<T> data) {
    for (const auto v: data) {
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

const ll mod = 998244353;  // 1000000007;
ll N, M, i, j, k, l;
string S, T;

bool cond(ll num) {
    if (num < 10) return true;
    ll a = num % 10;
    ll b = (num / 10)  % 10;
    ll d = b - a;
    num /= 100;
    while(num > 0) {
        b += d;
        if (num % 10 != b) {
            return false;
        }
        num /= 10;
    }
    return true;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    // debug_print(cond(5), cond(1357), cond(49), cond(963), cond(88888888));
    // debug_print(cond(842), cond(990));
    cin >> N;

    if (N < 100000) {
        while(!cond(N)) {
            N ++;
        }
        cout << N << endl;
    } else {
        vector<ll> keta;
        ll ans = -1;
        ll tmp = N;
        while(tmp > 0) {
            keta.push_back(tmp % 10);
            tmp /= 10;
        }
        ll sz = keta.size();
        
        //
        ll zoro = 0;
        REP(i, sz) {
            zoro *= 10;
            zoro += 1;
        }
        if (N <= zoro * keta[sz - 1]) {
            ans = zoro * keta[sz - 1];
        } else {
            ans = zoro * (keta[sz - 1] + 1);
        }
        // debug_print(ans);

        // up
        ll u_tmp = 0;
        ll u_end = keta[sz - 1];
        REP(i, sz) {
            u_tmp *= 10;
            u_tmp += u_end;
            u_end ++;
        }
        u_end --;
        // debug_print(u_end, u_tmp);
        if (u_end <= 9) {
            if (N <= u_tmp) {
                ans = min(ans, u_tmp);
            }
        }
        // debug_print(ans);

        // down
        ll d_tmp = 0;
        ll d_end = keta[sz - 1];
        REP(i, sz) {
            d_tmp *= 10;
            d_tmp += d_end;
            d_end --;
        }
        d_end ++;
        // debug_print(d_end, d_tmp);
        if (d_end >= 0) {
            if (N <= d_tmp) {
                ans = min(ans, d_tmp);
            } else {
                ans = min(ans, d_tmp + zoro);
            }
        } else if (d_end == -1) {
            ll d_tmp = 0;
            ll d_end = keta[sz - 1] + 1;
            REP(i, sz) {
                d_tmp *= 10;
                d_tmp += d_end;
                d_end --;
            }
            // debug_print(d_end, d_tmp);
            if (N <= d_tmp) {
                ans = min(ans, d_tmp);
            }
        }
        // debug_print(ans);

        cout << ans << endl;
    }
}