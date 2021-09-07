#include <bits/stdc++.h>
using namespace std;

int main() {
    {  // stack
        std::stack<int> a;
        cout << a.empty() << endl;  // 空か?
        a.push(10);                 //
        a.push(100);
        cout << a.size() << endl;  //
        a.top() += 1;  // 最後の要素への参照なので左辺における
        cout << a.top() << endl;
        a.pop();  //
        cout << a.top() << endl;
    }

    {  // queue
        std::queue<int> b;
        cout << b.empty() << endl;  // 空か?
        b.push(11);                 //
        b.push(22);
        b.push(33);
        cout << b.size() << endl;  //
        b.front() += 1000;         // 先頭要素への参照
        b.back() += 2000;          // 末尾要素への参照
        cout << b.front() << " " << b.back() << endl;
        b.pop();  //
        cout << b.front() << endl;
    }

    {  // pair
        std::pair<int, string> p;
        p = std::make_pair(1, "pair");  // 初期化 1
        cout << p.first << p.second << endl;
        p = {2, "a"};  // 初期化 2
        cout << p.first << p.second << endl;
    }

    {  // tuple
        std::tuple<int, int, string> t;
        t = std::make_tuple(1, 2, "tuple");  // 初期化 1
        cout << std::get<0>(t) << std::get<1>(t) << std::get<2>(t) << endl;
        t = {2, 4, "a"};  // 初期化 2
        cout << std::get<0>(t) << std::get<1>(t) << std::get<2>(t) << endl;
    }

    {  // deque
        cout << "deque" << endl;
        std::deque<int> d;
        d.push_back(1);
        d.push_front(2);
        cout << d.size() << endl;
        cout << d[0] << d.at(1) << endl;        // index アクセス
        cout << d.front() << d.back() << endl;  // これは参照
        for (auto it = d.begin(), e = d.end(); it != e; ++it) {
            // begin, end は vector と同じ
            std::cout << *it << std::endl;
        }
        d.pop_back();
        d.pop_front();
        cout << d.empty() << endl;
    }

    { // priority_queue

    }

    {  // string
    
    }
}