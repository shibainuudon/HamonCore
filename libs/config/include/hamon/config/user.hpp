/**
 *	@file	user.hpp
 *
 *	@brief
 */

// NO INCLUDE GUARD

// define this to locate a compiler config file:
// #define HAMON_COMPILER_CONFIG <myheader>

// define this to locate a stdlib config file:
// #define HAMON_STDLIB_CONFIG   <myheader>

// define this to locate a platform config file:
// #define HAMON_PLATFORM_CONFIG <myheader>

//#define HAMON_NO_STD
// このシンボルを定義すると、できる限り標準ライブラリに依存しないようになります。
// ただし、コンパイラマジックが必要などの理由で一部のものについては標準ライブラリを使用します。
// 例)
// * initializer_list … 初期化子リスト構文を使うため
// * allocator … constexpr に動的メモリ確保するため(C++20)
//
// このシンボルを定義しない場合、標準ライブラリで定義されたクラスとHamonライブラリで定義されたクラスは
// どちらも同じように使うことができます。
// 例えば、
// * std::string と hamon::string は相互に変換可能
// * hamon::string を渡せる関数には std::string も渡すことができる
