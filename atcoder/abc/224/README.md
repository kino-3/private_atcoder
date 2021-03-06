# ABC 224

## 重要メモ

- `string S = "abc";` は `S[0] = 'z'` で書き換え可能。
  - 文字列周りの動作確認を ./test.cpp で行った。
- D:「 0 ~ 8 の番号のマスに 0 ~ 8 の番号のコマがいる」状態は, 文字列で管理するとよい。
  - `string state = "201456783"` で, 場所 `i` にコマ `state[i]` がいることを表す。
  - `map<string, int>` などで, その状態に対応する手数などを管理するとよい。
- E: 数字が同じものは同じタイミングで処理したいので, `vector<pair<数字, idx>>` のソートではなく, `map<数字, idx>` で管理するとよい。
- F: 具体例で考える。
- pair の lower_bound, upper_bound

```cpp
// make_pair<ll, ll>(2, -10000) で型の指定が必要?
vector<pair<ll, ll>> vec = {{1, 1}, {1, 2}, {1, 3}, {2, 1}, {2, 2}, {2, 3}};
auto iter = lower_bound(vec.begin(), vec.end(), make_pair<ll, ll>(2, -10000));
ll idx = distance(vec.begin(), iter);
```

## D

- 状態量が 9! なので, BFS で間に合うことに気付くのに時間がかかった。
- 気付いた後の方針は正しかったが, 状態の管理にかなり苦戦した。
  - 文字列で管理するという発想がなかった。
  - コマに対応する場所を管理しているのか, 場所に対応しているコマを管理しているのかで混乱した。
    - 今回は, 場所同士が edge で繋がれているので, 場所に対応するコマを管理したほうが良かった。

## E

- 問題は見た。BFS のような要領で埋めていけば良いが, 計算量的に間に合う方針がすぐに思いつかなかったので後回しにした。
- 間に合うと思った方針(70min)で TLE した。PASS
- 書かれた数字の大きい順に見ていき, それぞれの処理を O(1) で行えばよい。(DAGに似ている?)
  - それぞれの処理は, 各行各列の現在の手数の最大値をメモしておけばよい(O(N))
  - 数字が同じものは同じタイミングで処理したいので, `vector<pair<数字, idx>>` のソートではなく, `map<数字, idx>` で管理するとよい。

## F

- 同解法(5分間に合わなかった)
- 方針はすぐに思いついたが, 等比数列の項の伝え方(コード中の base, base_pow)を考えるのに時間がかかった。
- 具体例で "1000" の場合を考えていれば, もう少し速く解けた。

## G

## H
