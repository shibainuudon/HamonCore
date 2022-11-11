[![units](https://github.com/shibainuudon/HamonCore/actions/workflows/units.yml/badge.svg)](https://github.com/shibainuudon/HamonCore/actions/workflows/units.yml)

# Hamon.Units

このライブラリは単位付きの演算を提供します。

## 基本的な使い方

```cpp
using hamon::units;

// 単位付きの値型を作成する
metres m {10};
// m.value() == 10

// スケールが自動的に変換される
m = kilometres{20};
// m.value() == 20000

kilometres km = metres{30};
// km.value() == 0.03

// 長さ+長さ -> 長さ
auto x = metres{3} + metres{4};
// decltype(x) == metres
// a.value() == 7

// 長さ×長さ -> 面積
auto a = metres{3} * metres{4};
// decltype(a) == square_metres
// a.value() == 12
```


## ビルドステータス

| main | develop |
| ---- | ------- |
|[![units](https://github.com/shibainuudon/HamonCore/actions/workflows/units.yml/badge.svg?branch=main)](https://github.com/shibainuudon/HamonCore/actions/workflows/units.yml)|[![units](https://github.com/shibainuudon/HamonCore/actions/workflows/units.yml/badge.svg?branch=develop)](https://github.com/shibainuudon/HamonCore/actions/workflows/units.yml)|

## 依存ライブラリ

* Hamon.Config
* Hamon.Ratio
* Hamon.Tuple
* Hamon.TypeTraits
