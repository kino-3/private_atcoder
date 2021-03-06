# ABC 208

## 重要メモ

## B

- 貪欲法で価値の大きなほうから決めていったが, 価値の小さい方から決めることもできる

## C

- K 番目に小さい値を O(N lon N) で出した
- これは Median of Median で最悪計算量 O(n) で出せる。
  - 計算量を f(n) とする
  - f(n) <= O(n) + f(n/5) + f(7n/10) より, f(n) <= 10 × O(n)
    - O(n)
      - 配列を 5個ずつの m セットに分ける (m = n/5)
      - 各セットの中央値を出す
    - f(n/5)
      - 各セットの中央値(計 m 個) に対して, それらの中央値を計算
      - 再帰的に行うと, f(m) の計算量
    - O(n)
      - 上で求めた中央値の中央値を pivot として全体を二分する
      - この pivot は昇順で 3n/10 ~ 7n/10 番目の位置にある
      - 二分したうち, k 番目に小さい値を含む方を選ぶ
        - これのサイズは 7n/10 以下
    - f(7n/10)
      - 上で得た k 番目に小さい値を含む方に対して, 再帰的に行う f(7n/10)

## D

- ワーシャルフロイドそのもの(背景を忘れていて解けなかった)

## E

- 桁DP
- WA は上位桁の積が K を超えても下位桁に 0 があったときを考慮していなかったため
- 積のパターンが少ないと思われることから, map を使った
  - 模範解答では, 桁の積の素因数は 2,3,5,7 のみ含まれることを利用している
- 桁DP ではない解法
  - https://atcoder.jp/contests/abc208/editorial/2225
