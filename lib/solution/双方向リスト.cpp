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

struct Node {
    Node *prev;
    Node *next;
    ll value;
};

class LinkedList {
   public:
    // 番兵(始点と終点を兼ねる)
    // nil -> next が先頭
    // nil -> prev が末尾
    Node *nil;
    ll size;

    LinkedList() : size(0) {
        nil = (Node *)malloc(sizeof(Node));
        nil->next = nil;
        nil->prev = nil;
    }

    void set_vector(vector<ll> vec) {
        for (auto v : vec) push_back(v);
    }

    void push_back(ll val) {
        size++;
        Node *new_node = (Node *)malloc(sizeof(Node));
        new_node->value = val;
        nil->prev->next = new_node;
        new_node->prev = nil->prev;
        new_node->next = nil;
        nil->prev = new_node;
    }

    void push_front(ll val) {
        size++;
        Node *new_node = (Node *)malloc(sizeof(Node));
        new_node->value = val;
        nil->next->prev = new_node;
        new_node->next = nil->next;
        new_node->prev = nil;
        nil->next = new_node;
    }

    ll pop_back() {
        assert(size > 0);
        size--;
        ll res = nil->prev->value;
        nil->prev->prev->next = nil;
        nil->prev = nil->prev->prev;
        return res;
    }

    ll pop_front() {
        assert(size > 0);
        size--;
        ll res = nil->next->value;
        nil->next->next->prev = nil;
        nil->next = nil->next->next;
        return res;
    }

    vector<ll> to_vector() {
        vector<ll> res;
        Node *tmp = nil;
        while (tmp->next != nil) {
            tmp = tmp->next;
            res.push_back(tmp->value);
        }
        return res;
    }

    void concat_back(LinkedList link_list) {
        // {1,2,3}concat_front({4,5,6}) -> {1,2,3,4,5,6}
        Node *link_nil = link_list.nil;
        size += link_list.size;
        nil->prev->next = link_nil->next;
        link_nil->next->prev = nil->prev;
        link_nil->prev->next = nil;
        nil->prev = link_nil->prev;
        // link_list は空にする;
        link_list.size = 0;
        link_nil->next = link_nil;
        link_nil->prev = link_nil;
    }

    void concat_front(LinkedList link_list) {
        // {1,2,3}concat_front({4,5,6}) -> {4,5,6,1,2,3}
        Node *link_nil = link_list.nil;
        size += link_list.size;
        nil->next->prev = link_nil->prev;
        link_nil->prev->next = nil->next;
        link_nil->next->prev = nil;
        nil->next = link_nil->next;
        // link_list は空にする;
        link_list.size = 0;
        link_nil->next = link_nil;
        link_nil->prev = link_nil;
    }
};

const ll mod = 998244353;  // 1000000007;
ll N, M, Q, i, j, k, l;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    LinkedList la = LinkedList();
    la.push_back(1);
    la.push_back(2);
    la.push_back(3);
    la.push_back(4);
    la.push_back(5);
    la.push_front(6);
    la.push_front(7);
    la.push_front(8);
    for (auto v : la.to_vector()) cout << v;
    cout << endl;
    cout << la.pop_back();
    cout << la.pop_back();
    cout << la.pop_front();
    cout << la.pop_front();
    cout << endl;
    for (auto v : la.to_vector()) cout << v;
    cout << endl;
    {
        LinkedList lb = LinkedList();
        LinkedList lc = LinkedList();
        lb.set_vector({1, 2, 3});
        lc.set_vector({4, 5, 6, 7});
        lb.concat_back(lc);
        for (auto v : lb.to_vector()) cout << v;
        cout << endl;
    }
    {
        LinkedList lb = LinkedList();
        LinkedList lc = LinkedList();
        lb.set_vector({1, 2, 3});
        lc.set_vector({4, 5, 6, 7});
        lb.concat_front(lc);
        for (auto v : lb.to_vector()) cout << v;
        cout << endl;
    }
}