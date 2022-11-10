[![serialization](https://github.com/shibainuudon/HamonCore/actions/workflows/serialization.yml/badge.svg)](https://github.com/shibainuudon/HamonCore/actions/workflows/serialization.yml)

# Hamon.Serialization

このライブラリはヘッダオンリーのシリアライゼーションライブラリです。
任意のデータ型を、決められたフォーマットのデータに変換することができます。

## ビルドステータス

| main | develop |
| ---- | ------- |
|[![serialization](https://github.com/shibainuudon/HamonCore/actions/workflows/serialization.yml/badge.svg?branch=main)](https://github.com/shibainuudon/HamonCore/actions/workflows/serialization.yml)|[![serialization](https://github.com/shibainuudon/HamonCore/actions/workflows/serialization.yml/badge.svg?branch=develop)](https://github.com/shibainuudon/HamonCore/actions/workflows/serialization.yml)|

## 依存ライブラリ

* Hamon.Base64
* Hamon.Concepts
* Hamon.Config
* Hamon.Detail
* Hamon.TypeTraits

## 対応フォーマット

* Binary
* Text
* JSON
* XML
* PortableBinary(WIP)

## 使い方

```cpp
#include <hamon/serialization/access.hpp>
#include <hamon/serialization/string.hpp>

class Student
{
private:
    std::string     name;
    int             age;

    friend class hamon::serialization::access;

    template <typename Archive>
    void serialize(Archive& ar)
    {
        ar & name;
        ar & age;
    }
};

#include <fstream>
#include <hamon/serialization/text_oarchive.hpp>
#include <hamon/serialization/text_iarchive.hpp>

int main()
{
    Student student;

    {
        // 出力アーカイブの作成
        std::ofstream ofs("output.txt");
        hamon::serialization::text_oarchive oa(ofs);

        // ファイルに書き出し
        oa << student;
    }
    {
        Student student2;

        // 入力アーカイブの作成
        std::ifstream ifs("output.txt");
        hamon::serialization::text_iarchive ia(ifs);

        // ファイルから読込
        ia >> student2;

        // student == student2
    }

    return 0;
}
```

## 生ポインタと参照のシリアライズについて

Hamon.Serializationは生ポインタと参照型変数のシリアライズをサポート**しません**。

参照変数は、初期化時にしか参照先を設定できないため、ロード処理をすることができません。

生ポインタは、指しているデータの所有権をもっているかどうかがわかりません。
そのため、これを正しくシリアライズするには、プログラム中のデータを全てトラッキングする必要があります。
これは実装を複雑にし、実行時のオーバーヘッドの原因となります。
また、トラッキングの設定をする必要があるため、ユーザーコードも不必要に複雑にします。

`std::unique_ptr`や`std::shared_ptr`のようなスマートポインタにはこのような問題がないため、
シリアライズをサポートすることができます。