[![concepts](https://github.com/shibainuudon/HamonCore/actions/workflows/concepts.yml/badge.svg)](https://github.com/shibainuudon/HamonCore/actions/workflows/concepts.yml)

# Hamon.Concepts

このライブラリはC++標準ライブラリの`<concepts>`を使えない環境でも、できるだけ`<concepts>`を再現することを目標としています。

## 実装方針

* C++20で`<concepts>`ヘッダーを使えるときは使う
* そうでなく、C++20の Concept 言語機能が使えるときは Concept を自分で定義
* そうでないときは TypeTraits で Conceptを再現

## 使い方

コンセプト`XXX`があるとき、
```cpp
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::XXX<T>
#else
	hamon::XXX<T>::value
#endif
```
という風に使います。
また、全てのコンセプトに対して`XXX_t`という形でTypeTraits風のクラスを定義しているので、
```cpp
hamon::XXX_t<T>::value
```
とすれば、Conceptが使えるときも使えないときも共通の書き方ができます。

## ビルドステータス

| main | develop |
| ---- | ------- |
|[![concepts](https://github.com/shibainuudon/HamonCore/actions/workflows/concepts.yml/badge.svg?branch=main)](https://github.com/shibainuudon/HamonCore/actions/workflows/concepts.yml)|[![concepts](https://github.com/shibainuudon/HamonCore/actions/workflows/concepts.yml/badge.svg?branch=develop)](https://github.com/shibainuudon/HamonCore/actions/workflows/concepts.yml)|

## 依存ライブラリ

* Hamon.Config
* Hamon.CStdDef
* Hamon.Detail
* Hamon.Preprocessor
* Hamon.TypeTraits
* Hamon.Utility
