[![cctype](https://github.com/shibainuudon/HamonCore/actions/workflows/cctype.yml/badge.svg)](https://github.com/shibainuudon/HamonCore/actions/workflows/cctype.yml)

# Hamon.CCType

このライブラリはC++標準ライブラリの`<cctype>`を拡張・改良する機能を提供します。

## `<cctype>`からの変更点

* `constexpr`をつけた
* 引数と戻り値の型を変更
* 現在のロケールに影響を受けない(常に"C"ロケールと同じ結果になる)

ロケールに応じた処理がしたい場合は、`<locale>`の関数を使用してください。

## ビルドステータス

| main | develop |
| ---- | ------- |
|[![cctype](https://github.com/shibainuudon/HamonCore/actions/workflows/cctype.yml/badge.svg?branch=main)](https://github.com/shibainuudon/HamonCore/actions/workflows/cctype.yml)|[![cctype](https://github.com/shibainuudon/HamonCore/actions/workflows/cctype.yml/badge.svg?branch=develop)](https://github.com/shibainuudon/HamonCore/actions/workflows/cctype.yml)|

## 依存ライブラリ

* Hamon.Config
