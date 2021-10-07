#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<char> convert_str2vec(string s) {
    ll len = s.size();
    vector<char> vec(len);
    copy(s.begin(), s.end(), vec.begin());
    return vec;
}

template <typename T>
void print_v(const vector<T> vec) {
    cout << "size: " << vec.size() << endl;
    cout << "[";
    for (auto &&item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}

template <class T>
class SuffixArray {
    vector<T> vec;
    ll len;

   public:
    SuffixArray(vector<T> v) {
        len = v.size();
        vec.resize(len);
        copy(v.begin(), v.end(), vec.begin());
    }

    void print() {
        cout << len << endl;
        print_v(vec);
    }
};

int main() {
    vector<char> str = convert_str2vec("abracadabra");
    SuffixArray<char> sa = SuffixArray<char>(str);
    sa.print();
}