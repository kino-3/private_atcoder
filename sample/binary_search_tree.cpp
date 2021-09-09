#include <bits/stdc++.h>
using namespace std;

int main() {
    {
        // set
        std::set<int> s;
        s.insert(10);  //
        s.insert(30);
        s.insert(30);
        cout << "set empty?:" << s.empty() << endl;  //
        cout << s.size() << endl;                    //
        for (auto it = s.begin(), e = s.end(); it != e; ++it) {
            // begin, end は vector と同じ
            std::cout << *it << std::endl;
        }
        s.erase(30);                                 //
        cout << s.count(30) << s.count(10) << endl;  // 見つかれば 1 なければ 0
        cout << *s.find(10) << endl;  // find は見つけた要素への iter
    }

    {
        // multiset
        std::multiset<int> s;
        s.insert(10);  //
        s.insert(30);
        s.insert(30);
        s.insert(30);
        cout << "multiset empty?:" << s.empty() << endl;  //
        cout << s.size() << endl;                         //
        for (auto it = s.begin(), e = s.end(); it != e; ++it) {
            // begin, end は vector と同じ
            std::cout << *it << std::endl;
        }
        cout << s.count(30) << endl;  // 見つけた個数
        if (s.count(30) > 0) {        // 1個だけ消したい場合
            s.erase(s.find(30));      // erase は iter もとれる
        }
        cout << s.count(30) << endl;
        s.erase(30);                  // 全部消したい場合
        cout << s.count(30) << endl;  // 見つけた個数
    }

    {
        // map
        std::map<int, string> m;
        m[1] = "v1";  // 存在しない場合は生成
        m[2] = "v2";
        m.insert({3, "v3"});
        cout << "map empty?:" << m.empty() << endl;  //
        cout << m.size() << endl;                    //
        for (auto it = m.begin(), e = m.end(); it != e; ++it) {
            std::cout << it->first << it->second
                      << std::endl;  // pair のようなアクセス
        }
        m.erase(2);
        cout << m.count(2) << endl;
        cout << m.at(1) << endl;  // 存在しない場合は error
    }
}