[![pair](https://github.com/shibainuudon/HamonCore/actions/workflows/pair.yml/badge.svg)](https://github.com/shibainuudon/HamonCore/actions/workflows/pair.yml)

# Hamon.Pair

このライブラリはC++標準ライブラリの`std::pair`を拡張・改良する機能を提供します。

## `std::pair`からの変更点

* `<utility>`ヘッダではなく、独立したライブラリにした
* 可能な限り`constexpr`をつけた
* 可能な限り`nodiscard`をつけた
* C++のバージョンごとの差異をなくした

## ビルドステータス

| main | develop |
| ---- | ------- |
|[![pair](https://github.com/shibainuudon/HamonCore/actions/workflows/pair.yml/badge.svg?branch=main)](https://github.com/shibainuudon/HamonCore/actions/workflows/pair.yml)|[![pair](https://github.com/shibainuudon/HamonCore/actions/workflows/pair.yml/badge.svg?branch=develop)](https://github.com/shibainuudon/HamonCore/actions/workflows/pair.yml)|

## 依存ライブラリ

* Hamon.Compare
* Hamon.Concepts
* Hamon.Config
* Hamon.CStdDef
* Hamon.Ranges
* Hamon.Tuple
* Hamon.TypeTraits
* Hamon.Utility
