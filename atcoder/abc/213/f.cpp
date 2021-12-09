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

vector<char> convert_str2vec(string s) {
    ll len = s.size();
    vector<char> vec(len);
    copy(s.begin(), s.end(), vec.begin());
    return vec;
}

template <class T>
class SuffixArray {
    vector<T> vec;
    ll len;

    class Comp {
        ll len;
        ll clen;
        const vector<ll> &rank;

       public:
        Comp(ll len, ll clen, const vector<ll> &rank)
            : len(len), clen(clen), rank(rank) {}

        bool operator()(ll i, ll j) {
            if (rank[i] != rank[j]) {
                return rank[i] < rank[j];
            } else {
                ll rank_i = (i + clen <= len ? rank[i + clen] : -1);
                ll rank_j = (j + clen <= len ? rank[j + clen] : -1);
                return rank_i < rank_j;
            }
        }
    };

   public:
    vector<ll> sa;  // index = sa[i] は辞書順で i 番目の接尾辞文字列の開始位置
    vector<ll> rank;  // i = rank[index] は開始位置 index の接尾辞文字列の辞書順
    // lcp[i] は辞書順で i 番目と i+1 番目の接尾辞文字列の先頭一致文字数
    vector<ll> lcp;

    SuffixArray(vector<T> v) {
        len = v.size();
        vec.resize(len);
        sa.resize(len + 1);
        rank.resize(len + 1);
        lcp.resize(len);
        copy(v.begin(), v.end(), vec.begin());
    }

    // O(n (log n)^2)
    vector<ll> exec() {
        vector<ll> tmp_rank(len + 1);
        for (ll i = 0; i < len; i++) {
            sa[i] = i;
            rank[i] = vec[i];  // 1 文字ならこれでソートされている
        }
        sa[len] = len;
        rank[len] = -1;  // 空文字列は一番最初に来るので
        for (ll clen = 1; clen <= len; clen *= 2) {
            // 前提として, clen 文字について rank は適切に並んでいる
            // この状態から 2*clen 文字を sort する
            Comp comp = Comp(len, clen, rank);
            sort(sa.begin(), sa.end(), comp);
            // 2*clen 文字での rank を求める
            tmp_rank[sa[0]] = 0;
            for (ll i = 1; i <= len; i++) {
                // 辞書順 i 番目の文字列と辞書順 i-1 番目の文字列が 2*clen
                // 文字で 同じなら rank も同じ, 違うなら rank は 1 増える
                tmp_rank[sa[i]] = tmp_rank[sa[i - 1]];
                if (comp(sa[i - 1], sa[i])) {
                    tmp_rank[sa[i]]++;
                }
            }
            copy(tmp_rank.begin(), tmp_rank.end(), rank.begin());
        }
        return sa;
    }

    // O(n)
    vector<ll> exec_lcp() {
        ll height = 0;
        lcp[0] = 0;  // 空文字列と文字列は先頭一致しない
        for (ll idx = 0; idx < len; idx++) {
            // 辞書順で「位置 idx から始まる文字列」の 1 個前の文字列の開始位置
            // rank[len] = 0 かつ idx != len より, rank[idx] > 0
            ll pre_idx = sa[rank[idx] - 1];
            if (height > 0) height--;
            while (idx + height < len && pre_idx + height < len) {
                if (vec[idx + height] != vec[pre_idx + height]) break;
                height++;
            }
            lcp[rank[idx] - 1] = height;
        }
        return lcp;
    }
};

const ll mod = 998244353;
ll N, M, i, j, k, l;
string S, T;

// 単調増加数列総和最大
vector<ll> accum(vector<ll> &vec) {
    stack<pair<ll, ll>> stk;
    vector<ll> res;
    res.push_back(vec[0]);
    stk.push({vec[0], 0});
    FOR(i, 1, vec.size()) {
        auto v = stk.top();
        if (v.first < vec[i]) {
            ll tmp = vec[i];
            tmp += v.first * (i - v.second - 1);
            res.push_back(tmp + res[v.second]);
            stk.push({vec[i], i});
        } else {
            while (!stk.empty()) {
                if (stk.top().first > vec[i]) {
                    stk.pop();
                } else {
                    break;
                }
            }
            if (stk.empty()) {
                res.push_back(vec[i] * (i + 1));
            } else {
                res.push_back(res[stk.top().second] +
                              vec[i] * (i - stk.top().second));
            }
            stk.push({vec[i], i});
        }
    }
    return res;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    cin >> S;

    vector<char> str = convert_str2vec(S);
    SuffixArray<char> sa = SuffixArray<char>(str);
    sa.exec();
    auto lcp = sa.exec_lcp();
    // test
    // print_v(sa.sa);
    // print_v(sa.rank);
    // print_v(lcp);
    // REP(i, N + 1) {
    //     cout << S.substr(sa.sa[i]) << " " << (i != N ? lcp[i] : -1) << endl;
    // }

    auto accum_lcp = accum(lcp);
    reverse(ALL(lcp));
    auto accum_lcp_r = accum(lcp);
    reverse(ALL(accum_lcp_r));
    reverse(ALL(lcp));
    // print_v(lcp);
    // print_v(accum_lcp);
    // print_v(accum_lcp_r);
    accum_lcp_r.push_back(0);

    REP(i, N) {
        ll rank = sa.rank[i];
        ll ans = N - i + accum_lcp_r[rank] + accum_lcp[rank-1];
        cout << ans << endl;
    }

    // REP(i, N) {
    //     ll rank = sa.rank[i];
    //     ll ans = N - i;
    //     k = 100000000;
    //     FOR(j, rank, N) {
    //         k = min(k, lcp[j]);
    //         ans += k;
    //         if (lcp[j] == 0) break;
    //     }
    //     k = 100000000;
    //     REP_R(j, rank) {
    //         k = min(k, lcp[j]);
    //         ans += k;
    //         if (lcp[j] == 0) break;
    //     }
    //     cout << ans << endl;
    // }
}