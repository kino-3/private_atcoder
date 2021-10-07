#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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
    vector<ll> sa;  // index = sa[i] は辞書順で i 番目の文字列の開始位置
    vector<ll> rank;  // i = rank[index] は開始位置 index の文字列の辞書順

    SuffixArray(vector<T> v) {
        len = v.size();
        vec.resize(len);
        sa.resize(len + 1);
        rank.resize(len + 1);
        copy(v.begin(), v.end(), vec.begin());
    }

    void exec() {
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
    }
};

template <typename T>
void print_v(const vector<T> vec) {
    cout << "size: " << vec.size() << endl;
    cout << "[";
    for (auto &&item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}

int main() {
    vector<char> str = convert_str2vec("abracadabra");
    SuffixArray<char> sa = SuffixArray<char>(str);
    sa.exec();
    print_v(sa.sa);
    print_v(sa.rank);
}