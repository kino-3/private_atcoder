# ABC 220

## 重要メモ

- 点と直線の距離は正規化した方向ベクトルと内積, 外積を考えると速い

## G

- 平行四辺形, 正方形の場合分けがかなり面倒な気がする。解けはするはずだが, 明らかに時間内に実装が間に合わない。PASS。
- 線分の中点に着目すれば簡単に判定可能。
  - 傾き一致
  - and 中点が同一法線上 i.e. 方向ベクトルと (原点->中点) の外積が一致
  - and 中点が不一致
