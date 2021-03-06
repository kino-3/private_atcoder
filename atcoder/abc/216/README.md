# ABC 216

## 重要メモ

## A

- `"abcdefg".substr(2, 4)` は "cdef"

## D

- 貪欲的にとって良い。DAG 判定で解いた。
- 解答例: (取り出した筒の状態しか変わらないので, 状態の変更を O(1) で処理する)
  - 用意
    - `vector<int> cnt[i]`: 1 番上が色 i である筒の個数
    - `vector<vector<int>> list[i]`: 1 番上が色 i である筒の番号のリスト
    - `queue<int> que`: cnt[i] >= 2 となる i の集合
  - 以下(O(1))を N 回繰り返す
    - que から i を 1 つ取り出す
    - cnt[i] -= 2
    - list[i] から要素を2つ (j, k) 削除する
    - 筒 j, 筒 k の次の球の色を調べて, cnt と vector と queue を更新する

## E

- 閾値で二分探索

## F

- 集合の数はソートしても変わらない
- i 番目の dp で i を使うと, A_i == max(A) と固定されるので, sum(B) == B_i + sum(B') の形で考えられる。

## G

- 別解の方法(右端が左にあるものから順に考えて, 足りなければ区間の最も右の0を1にする)で解いた。
- 牛ゲーでも解けるらしい
