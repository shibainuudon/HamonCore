[![base64](https://github.com/shibainuudon/HamonCore/actions/workflows/base64.yml/badge.svg)](https://github.com/shibainuudon/HamonCore/actions/workflows/base64.yml)

# Hamon.Base64

このライブラリはBASE64エンコード・デコード機能を提供します。

## 使い方

エンコード：

```cpp
#include <hamon/base64/base64.hpp>

// 元データ
std::vector<float> src = {1, 2, 3};
// エンコード後のバイト数を取得
auto length = hamon::base64::get_encoded_size(src.size() * sizeof(float));
// 出力用バッファ
std::string dst(length, '\0');
// エンコード
hamon::base64::encode(src.begin(), src.end(), dst.begin());
//hamon::base64::encode(src, dst.begin());	と書くこともできる

// dst == "AACAPwAAAEAAAEBA"
```

デコード：

```cpp
#include <hamon/base64/base64.hpp>

// 元データ
std::string src = "AACAPwAAAEAAAEBA";
// デコード後のバイト数を取得
auto length = hamon::base64::get_decoded_size(src.size() * sizeof(char));
// 出力用バッファ
std::vector<float> dst(length / sizeof(float));
// デコード
hamon::base64::decode(src.begin(), src.end(), dst.begin());
//hamon::base64::decode(src, dst.begin());	と書くこともできる

// dst == {1, 2, 3}
```

## 種類

目的別に、変換テーブルの一部やパディングの文字が違うバージョンも用意しています。

|名前|説明|
|----|----|
|base64|標準|
|base64_xml_name|XML識別子向け修正Base64|
|base64_xml_nmtoken|XML名前トークン向け修正Base64|
|base64url|URLアプリケーションのための変形 Base64|


## ビルドステータス

| main | develop |
| ---- | ------- |
|[![base64](https://github.com/shibainuudon/HamonCore/actions/workflows/base64.yml/badge.svg?branch=main)](https://github.com/shibainuudon/HamonCore/actions/workflows/base64.yml)|[![base64](https://github.com/shibainuudon/HamonCore/actions/workflows/base64.yml/badge.svg?branch=develop)](https://github.com/shibainuudon/HamonCore/actions/workflows/base64.yml)|

## 依存ライブラリ

* Hamon.Concepts
* Hamon.Config
* Hamon.CStdDef
* Hamon.CStdInt
* Hamon.Detail
* Hamon.Iterator
* Hamon.Memory
* Hamon.Ranges
* Hamon.TypeTraits
* Hamon.Utility
