#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    // 入力
    vector<int> vec(n);
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
}