[![config](https://github.com/shibainuudon/HamonCore/actions/workflows/config.yml/badge.svg)](https://github.com/shibainuudon/HamonCore/actions/workflows/config.yml)

# Hamon.Config

このライブラリはプラットフォーム、コンパイラ、C++バージョンなどの差を吸収するための機能を提供します。

Hamon.Coreのその他のライブラリの基礎となるライブラリです。

## ビルドステータス
| main | develop |
| ---- | ------- |
|[![config](https://github.com/shibainuudon/HamonCore/actions/workflows/config.yml/badge.svg?branch=main)](https://github.com/shibainuudon/HamonCore/actions/workflows/config.yml)|[![config](https://github.com/shibainuudon/HamonCore/actions/workflows/config.yml/badge.svg?branch=develop)](https://github.com/shibainuudon/HamonCore/actions/workflows/config.yml)|

### 定義されるマクロの例

| マクロ             | 説明               | 値の例                 |
| ------------------ | ------------------ | ---------------------- |
| HAMON_PLATFORM     | プラットフォーム名 | "Win32",               |
| HAMON_ARCHITECTURE | アーキテクチャ名   | "x86_64"               |
| HAMON_COMPILER     | コンパイラー名     | "Microsoft Visual C++" |
| HAMON_CXX_STANDARD | C++バージョン      | 20                     |

## 依存ライブラリ
なし