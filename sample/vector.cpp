#include <bits/stdc++.h>
using namespace std;

template <typename T>
void print_v(const vector<T> vec) {
    cout << "size: " << vec.size() << endl;
    cout << "[";
    for (auto &&item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}

template <typename T>
void print_vv(const vector<vector<T>> vv) {
    cout << "size: (" << vv.size() << ", " << vv.at(0).size() << ")" << endl;
    cout << "[" << endl;
    for (auto &&v : vv) {
        cout << "  [";
        for (auto &&item : v) {
            cout << item << ",";
        }
        cout << "]," << endl;
    }
    cout << "]" << endl;
}

int main() {
    int n;
    cin >> n;

    // 入力
    vector<int> vec(n, -1);  // 全要素を -1 で初期化
    for (auto &&i : vec) {
        cin >> i;
    }
    // 入力2
    // vector<int> vec;
    // vec.reserve(n);  // あったほうが良い
    // for (int i = 0; i < n; i++) {
    //     int e;
    //     cin >> e;
    //     vec.push_back(e);
    // }

    // loop
    for (auto &&item : vec) {
        cout << item << endl;
    }
    // loop const
    for (const auto &item : vec) {
        cout << item << endl;
    }
    print_v(vec);  // 内容確認

    // 2次元ベクトル
    // 入力
    int n1;
    cin >> n1;
    int n2;
    cin >> n2;
    vector<vector<int>> vv(n1, vector<int>(n2, -1));
    for (auto &&v : vv) {
        for (auto &&i : v) {
            cin >> i;
        }
    }
    print_vv(vv);  // 内容確認
}