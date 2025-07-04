﻿/**
 *	@file	msvc.hpp
 *
 *	@brief
 */

#ifndef HAMON_CONFIG_COMPILER_MSVC_HPP
#define HAMON_CONFIG_COMPILER_MSVC_HPP

#define HAMON_MSVC _MSC_VER

#if _MSC_FULL_VER > 100000000
#  define HAMON_MSVC_FULL_VER _MSC_FULL_VER
#else
#  define HAMON_MSVC_FULL_VER (_MSC_FULL_VER * 10)
#endif

#define HAMON_COMPILER "Microsoft Visual C++"
#define HAMON_COMPILER_VERSION HAMON_MSVC_FULL_VER

#pragma warning(disable : 4503) // 修飾された名前の長さが限界を超えました。名前は切り捨てられます。

// pragma once
#define HAMON_HAS_PRAGMA_ONCE

//
// check for exception handling support:
#if !defined(_CPPUNWIND) && !defined(HAMON_NO_EXCEPTIONS)
#  define HAMON_NO_EXCEPTIONS
#endif

#if (_MSC_VER >= 1400) && !defined(_DEBUG)
#   define HAMON_HAS_NRVO
#endif

// RTTI support
#if !defined(_CPPRTTI) && !defined(HAMON_NO_RTTI)
#  define HAMON_NO_RTTI
#endif

// HAMON_CXX_STANDARD
// ※MSVCでは、`/Zc:__cplusplus`オプションを指定しない限り、
//   __cplusplus の値は 199711L で固定。
//   _MSVC_LANG マクロは、`/std:`オプションの設定が反映される。
#if !defined(HAMON_CXX_STANDARD)
#  if _MSVC_LANG > 202002L && (_MSC_VER >= 1930)
   // CMakeで CMAKE_CXX_STANDARD=20 を指定したとき、Visual Studio 2019 のオプションとして`/std:c++latest`が渡されるようだ。
   // その時、_MSVC_LANG は 202002L より大きな値になるが、C++23が使えるわけではない
#    define HAMON_CXX_STANDARD 23
#  elif _MSVC_LANG >= 202002L
#    define HAMON_CXX_STANDARD 20
#  elif _MSVC_LANG >= 201703L
#    define HAMON_CXX_STANDARD 17
#  elif _MSVC_LANG >= 201402L
#    define HAMON_CXX_STANDARD 14
#  elif  _MSVC_LANG >= 201103L
#    define HAMON_CXX_STANDARD 11
#  else
#    define HAMON_CXX_STANDARD  3
#  endif
#endif  // HAMON_CXX_STANDARD

#if (_MSC_VER >= 1600)
#  define HAMON_HAS_STDINT_H
#endif

// Visual Studio 2003 (Visual C++ 7.1)
#if (_MSC_VER >= 1400)
#  define HAMON_HAS_CXX11_EXTERN_TEMPLATE					// テンプレートのインスタンス化抑止
#  define HAMON_HAS_CXX11_LONG_LONG							// long long型
#endif

// Visual Studio 2005 (Visual C++ 8)
#if (_MSC_VER >= 1500)
#  define HAMON_HAS_CXX11_VARIADIC_MACROS					// 可変引数マクロ
#  define HAMON_HAS_CXX11_RIGHT_ANGLE_BRACKETS				// テンプレートの右山カッコ
#  define HAMON_HAS_CXX11_OVERRIDE							// override
#endif

// Visual Studio 2010 (Visual C++ 10)
#if (_MSC_VER >= 1600)
#  define HAMON_HAS_CXX11_LOCAL_TYPE_TEMPLATE_ARGS			// ローカル型と無名型をテンプレート引数として使用することを許可
#  define HAMON_HAS_CXX11_AUTO_DECLARATIONS					// 型推論
#  define HAMON_HAS_CXX11_EXTENDED_FRIEND_DECLARATIONS		// friend宣言できる対象を拡張
#  define HAMON_HAS_CXX11_STATIC_ASSERT						// コンパイル時アサート
#  define HAMON_HAS_CXX11_NULLPTR							// nullptr
#  define HAMON_HAS_CXX11_TRAILING_RETURN_TYPE				// 戻り値の型を後置する関数宣言構文
#endif

// Visual Studio 2012 (Visual C++ 11)
#if (_MSC_VER >= 1700)
#  define HAMON_HAS_CXX11_LAMBDAS							// ラムダ式
#  define HAMON_HAS_CXX11_DECLTYPE							// 式の型を取得
#  define HAMON_HAS_CXX11_FINAL								// final
#  define HAMON_HAS_CXX11_RANGE_BASED_FOR					// 範囲for文
#  define HAMON_HAS_CXX11_SCOPED_ENUMS						// スコープを持つ列挙型
#  define HAMON_HAS_CXX11_FORWARD_DECLARE_ENUMS				// enumの先行宣言
#endif

// Visual Studio 2013 (Visual C++ 12)
#if (_MSC_FULL_VER >= 180020827)
#  define HAMON_HAS_CXX11_DELETED_FUNCTIONS					// 関数のdelete宣言
#  define HAMON_HAS_CXX11_DELEGATING_CONSTRUCTORS			// 移譲コンストラクタ
#  define HAMON_HAS_CXX11_EXPLICIT_CONVERSION_OPERATORS		// 明示的な型変換演算子
#  define HAMON_HAS_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS	// 関数テンプレートに関する既定のテンプレート引数
#  define HAMON_HAS_CXX11_RAW_STRINGS						// 生文字列リテラル
#  define HAMON_HAS_CXX11_ALIAS_TEMPLATES					// エイリアステンプレート
#  define HAMON_HAS_CXX11_VARIADIC_TEMPLATES				// 可変引数テンプレート
#  define HAMON_HAS_CXX11_NSDMI								// 非静的メンバ変数の初期化
#  define HAMON_HAS_CXX11_INITIALIZER_LISTS					// 初期化子リスト
#  define HAMON_HAS_CXX11_UNIFORM_INITIALIZATION			// 一様初期化

#  define HAMON_HAS_EXPM1
#  define HAMON_HAS_LOG1P
#endif

// Visual Studio 2015 (Visual C++ 14.0)
#if (_MSC_FULL_VER >= 190023026)
#  define HAMON_HAS_CXX11_RVALUE_REFERENCES					// 右辺値参照
#  define HAMON_HAS_CXX11_DEFAULTED_FUNCTIONS				// 関数のdefault宣言
#  define HAMON_HAS_CXX11_INHERITING_CONSTRUCTORS			// 継承コンストラクタ
#  define HAMON_HAS_CXX11_NOEXCEPT							// noexcept
#  define HAMON_HAS_CXX11_REF_QUALIFIERS					// メンバ関数の左辺値／右辺値修飾
#  define HAMON_HAS_CXX11_USER_DEFINED_LITERALS				// ユーザー定義リテラル
#  define HAMON_HAS_CXX11_ALIGNAS							// アライメント指定
#  define HAMON_HAS_CXX11_ALIGNOF							// アライメント取得
#  define HAMON_HAS_CXX11_INLINE_NAMESPACES					// インライン名前空間
#  define HAMON_HAS_CXX11_CHAR16_T							// char16_t
#  define HAMON_HAS_CXX11_CHAR32_T							// char32_t
#  define HAMON_HAS_CXX11_UNICODE_LITERALS					// UTF-8文字列リテラル
#  define HAMON_HAS_CXX11_UNIVERSAL_CHARACTER_NAME			// 文字列リテラル中のユニバーサルキャラクタ名
#  define HAMON_HAS_CXX11_ATTRIBUTES						// 属性構文
#  define HAMON_HAS_CXX11_NORETURN							// [[noreturn]]属性
#  define HAMON_HAS_CXX11_CARRIES_DEPENDENCY				// [[carries_dependency]]属性
#  define HAMON_HAS_CXX11_THREAD_LOCAL						// スレッドローカルストレージ
#  define HAMON_HAS_CXX11_UNRESTRICTED_UNIONS				// 共用体の制限解除
#  define HAMON_HAS_CXX11_THREADSAFE_STATIC_INIT			// ブロックスコープを持つstatic変数初期化のスレッドセーフ化
#  define HAMON_HAS_CXX11_EXTENDED_SIZEOF					// 拡張sizeof
#  define HAMON_HAS_CXX14_BINARY_LITERALS					// 2進数リテラル
#  define HAMON_HAS_CXX14_DECLTYPE_AUTO						// 通常関数の戻り値型推論
#  define HAMON_HAS_CXX14_RETURN_TYPE_DEDUCTION				// 通常関数の戻り値型推論
#  define HAMON_HAS_CXX14_INIT_CAPTURES						// ラムダ式の初期化キャプチャ
#  define HAMON_HAS_CXX14_GENERIC_LAMBDAS					// ジェネリックラムダ
#  define HAMON_HAS_CXX14_DEPRECATED						// [[deprecated]]属性
#  define HAMON_HAS_CXX14_SIZED_DEALLOCATION				// サイズ付きデアロケーション
#  define HAMON_HAS_CXX14_DIGIT_SEPARATORS					// 数値リテラルの桁区切り文字
# if (HAMON_CXX_STANDARD >= 14)	// この 14 は間違いではない。(https://docs.microsoft.com/en-us/cpp/overview/visual-cpp-language-conformance?view=vs-2019#note_14)
#  define HAMON_HAS_CXX17_AUTO_DEDUCTION_BRACED_INIT_LIST	// 波括弧初期化の型推論の新規則
#  define HAMON_HAS_CXX17_TEMPLATE_TEMPLATE_TYPENAME		// テンプレートテンプレートパラメータにtypenameを許可
#  define HAMON_HAS_CXX17_ENUMERATOR_ATTRIBUTES				// 列挙子に属性の付加を許可
#  define HAMON_HAS_CXX17_NAMESPACE_ATTRIBUTES				// 名前空間に属性の付加を許可
#  define HAMON_HAS_CXX17_U8_CHARACTER_LITERALS				// UTF-8文字リテラル
#  define HAMON_HAS_CXX17_IGNORING_UNRECOGNIZED_ATTRIBUTES	// 不明な属性を無視する
#  define HAMON_HAS_CXX20_CONST_QUALIFIED_POINTERS_TO_MEMBERS	// P0704R1
# endif
#endif

// Visual Studio 2015 Update 1	(Visual C++ 14.0)
#if (_MSC_FULL_VER >= 190023506)
#endif

// Visual Studio 2015 Update 2	(Visual C++ 14.0)
#if (_MSC_FULL_VER >= 190023918)
//#  define HAMON_HAS_CXX14_VARIABLE_TEMPLATES				// 変数テンプレート
// VS 2015.2 で Variable templates に対応したのだが、実際にはバグっていて VS 2019 まで使い物にならない

# if (HAMON_CXX_STANDARD >= 23)
#  define HAMON_HAS_CXX23_UTF8_SOURCE_FILE_ENCODING			// P2295R6	Support for UTF-8 as a portable source file encoding
# endif
#endif

// Visual Studio 2015 Update 3	(Visual C++ 14.0)
#if (_MSC_FULL_VER >= 190024210)
#  define HAMON_HAS_CXX11_SFINAE_EXPR						// 任意の式によるSFINAE
#  define HAMON_HAS_CXX11_CONSTEXPR							// 定数式
# if (HAMON_CXX_STANDARD >= 17)
#  define HAMON_HAS_CXX17_NESTED_NAMESPACE_DEFINITIONS		// 入れ子名前空間の定義
# endif
#endif

// Visual Studio 2017 (15.0)	(Visual C++ 14.10)
#if (_MSC_FULL_VER >= 191025017)
#  define HAMON_HAS_CXX14_CONSTEXPR							// constexprの制限緩和
#  define HAMON_HAS_CXX14_AGGREGATE_NSDMI					// 宣言時のメンバ初期化を持つ型の集成体初期化
# if (HAMON_CXX_STANDARD >= 14)
#  define HAMON_HAS_CXX17_RANGE_BASED_FOR					// 範囲for文の制限を緩和
# endif
# if (HAMON_CXX_STANDARD >= 17)
#  define HAMON_HAS_CXX17_STATIC_ASSERT						// メッセージなしのstatic_assert
#  define HAMON_HAS_CXX17_FALLTHROUGH						// [[fallthrough]]属性
# endif
# if (HAMON_CXX_STANDARD >= 14)	// この 14 は間違いではない。(https://docs.microsoft.com/en-us/cpp/overview/visual-cpp-language-conformance?view=vs-2019#note_14)
#  define HAMON_HAS_CXX20_CONSTEXPR_UNION					// P1330R0
# endif
#endif

// Visual Studio 2017 Update 3 (15.3.3)	(Visual C++ 14.11)
#if (_MSC_FULL_VER >= 191125507)
# if (HAMON_CXX_STANDARD >= 14)
#  define HAMON_HAS_CXX17_HAS_INCLUDE						// プリプロセッサでの条件式__has_include
# endif
# if (HAMON_CXX_STANDARD >= 17)
#  define HAMON_HAS_CXX17_IF_CONSTEXPR						// if constexpr文
#  define HAMON_HAS_CXX17_CAPTURE_STAR_THIS					// ラムダ式での*thisのコピーキャプチャ
#  define HAMON_HAS_CXX17_USING_ATTRIBUTE_NAMESPACES		// 属性の名前空間指定に繰り返しをなくす
#  define HAMON_HAS_CXX17_INIT_ENUM_CLASS					// enum class変数の初期値として整数を指定
#  define HAMON_HAS_CXX17_CONSTEXPR_LAMBDA					// constexprラムダ
#  define HAMON_HAS_CXX17_NODISCARD							// [[nodiscard]]属性
#  define HAMON_HAS_CXX17_MAYBE_UNUSED						// [[maybe_unused]]属性
#  define HAMON_HAS_CXX17_STRUCTURED_BINDINGS				// 構造化束縛
#  define HAMON_HAS_CXX17_SELECTION_WITH_INIT				// if文とswitch文の条件式と初期化を分離
# endif
#endif

// Visual Studio 2017 Update 4 (15.4.4)	(Visual C++ 14.11)
#if (_MSC_FULL_VER >= 191125542)
#endif

// Visual Studio 2017 Update 4 (15.4.5)	(Visual C++ 14.11)
#if (_MSC_FULL_VER >= 191125547)
#endif

// Visual Studio 2017 Update 5 (v15.5)	(Visual C++ 14.12)
#if (_MSC_FULL_VER >= 191225830)
#endif

// Visual Studio 2017 Update 5 (15.5.2)	(Visual C++ 14.12)
#if (_MSC_FULL_VER >= 191225831)
#  define HAMON_HAS_CXX17_HEX_FLOAT							// 浮動小数点数の16進数リテラル
# if (HAMON_CXX_STANDARD >= 17)
#  define HAMON_HAS_CXX17_NONTYPE_TEMPLATE_ARGS				// 非型テンプレートパラメータの定数式を評価
#  define HAMON_HAS_CXX17_FOLD_EXPRESSIONS					// 畳み込み式
#  define HAMON_HAS_CXX17_EXCEPTION_SPECIFICATIONS			// 非推奨だった例外仕様を削除
#  define HAMON_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE			// 例外仕様を型システムの一部にする
#  define HAMON_HAS_CXX17_ALIGNED_NEW						// アライメント指定されたデータの動的メモリ確保
#  define HAMON_HAS_CXX17_INLINE_VARIABLES					// インライン変数
#  define HAMON_HAS_CXX17_TEMPLATE_TEMPLATE_ARGS			// テンプレートテンプレート引数のマッチングにおいて、互換性のあるテンプレートを除外
# endif
#endif

// Visual Studio 2017 Update 5 (15.5.(3-4))	(Visual C++ 14.12)
#if (_MSC_FULL_VER >= 191225834)
#endif

// Visual Studio 2017 Update 5 (15.5.(5-7))	(Visual C++ 14.12)
#if (_MSC_FULL_VER >= 191225835)
#endif

// Visual Studio 2017 Update 6 (15.6.(0-2))	(Visual C++ 14.13)
#if (_MSC_FULL_VER >= 191326128)
# if (HAMON_CXX_STANDARD >= 17)
#  define HAMON_HAS_CXX17_GUARANTEED_COPY_ELISION				// 値のコピー省略を保証
# endif
#endif

// Visual Studio 2017 Update 6 (15.6.(3-5))	(Visual C++ 14.13)
#if (_MSC_FULL_VER >= 191326129)
#endif

// Visual Studio 2017 Update 6 (15.6.6)	(Visual C++ 14.13)
#if (_MSC_FULL_VER >= 191326131)
#endif

// Visual Studio 2017 Update 6 (15.6.7)	(Visual C++ 14.13)
#if (_MSC_FULL_VER >= 191326132)
#endif

// Visual Studio 2017 Update 7 (15.7.(0-1))	(Visual C++ 14.14)
#if (_MSC_FULL_VER >= 191426428)
# if (HAMON_CXX_STANDARD >= 17)
#  define HAMON_HAS_CXX17_VARIADIC_USING						// using宣言でのパック展開
#  define HAMON_HAS_CXX17_AGGREGATE_BASES						// 集成体初期化の波カッコを省略
#  define HAMON_HAS_CXX17_DEDUCTION_GUIDES						// クラステンプレートのテンプレート引数推論
#  define HAMON_HAS_CXX17_NONTYPE_TEMPLATE_PARAMETER_AUTO		// 非型テンプレート引数のauto宣言
#  define HAMON_HAS_CXX17_INHERITING_CONSTRUCTORS				// 継承コンストラクタの新仕様
#  define HAMON_HAS_CXX17_EXPRESSION_EVALUATION_ORDER			// 厳密な式の評価順
# endif
# if (HAMON_CXX_STANDARD >= 17)	// Defect report としてC++17に適用される
#  define HAMON_HAS_CXX20_INITIALIZER_LIST_CTAD					// P0702R1
# endif
#endif

// Visual Studio 2017 Update 7 (15.7.2)	(Visual C++ 14.14)
#if (_MSC_FULL_VER >= 191426429)
#endif

// Visual Studio 2017 Update 7 (15.7.3)	(Visual C++ 14.14)
#if (_MSC_FULL_VER >= 191426430)
#endif

// Visual Studio 2017 Update 7 (15.7.4)	(Visual C++ 14.14)
#if (_MSC_FULL_VER >= 191426431)
#endif

// Visual Studio 2017 Update 7 (15.7.(5-6))	(Visual C++ 14.14)
#if (_MSC_FULL_VER >= 191426433)
#endif

// Visual Studio 2017 Update 8 (15.8.(0-3))	(Visual C++ 14.15)
#if (_MSC_FULL_VER >= 191526726)
#endif

// Visual Studio 2017 Update 8 (15.8.4)	(Visual C++ 14.15)
#if (_MSC_FULL_VER >= 191526729)
#endif

// Visual Studio 2017 Update 8 (15.8.(5-7))	(Visual C++ 14.15)
#if (_MSC_FULL_VER >= 191526730)
#endif

// Visual Studio 2017 Update 8 (15.8.(8-9))	(Visual C++ 14.15)
#if (_MSC_FULL_VER >= 191526732)
#endif

// Visual Studio 2017 Update 9 (15.9.(0-1))	(Visual C++ 14.16)
#if (_MSC_FULL_VER >= 191627023)
#endif

// Visual Studio 2017 Update 9 (15.9.(2-3))	(Visual C++ 14.16)
#if (_MSC_FULL_VER >= 191627024)
#endif

// Visual Studio 2017 Update 9 (15.9.4)	(Visual C++ 14.16)
#if (_MSC_FULL_VER >= 191627025)
#endif

// Visual Studio 2017 Update 9 (15.9.(5-6))	(Visual C++ 14.16)
#if (_MSC_FULL_VER >= 191627026)
#endif

// Visual Studio 2017 Update 9 (15.9.(7-10)) (Visual C++ 14.16)
#if (_MSC_FULL_VER >= 191627027)
#endif

// Visual Studio 2017 Update 9 (15.9.11) (Visual C++ 14.16)
#if (_MSC_FULL_VER >= 191627030)
#endif

// Visual Studio 2017 Update 9 (15.9.(12-13)) (Visual C++ 14.16)
#if (_MSC_FULL_VER >= 191627031)
#endif

// Visual Studio 2017 Update 9 (15.9.(14-15)) (Visual C++ 14.16)
#if (_MSC_FULL_VER >= 191627032)
#endif

// Visual Studio 2017 Update 9 (15.9.(16-18)) (Visual C++ 14.16)
#if (_MSC_FULL_VER >= 191627034)
#endif

// Visual Studio 2017 Update 9 (15.9.(19-20)) (Visual C++ 14.16)
#if (_MSC_FULL_VER >= 191627035)
#endif

// Visual Studio 2017 Update 9 (15.9.21) (Visual C++ 14.16)
#if (_MSC_FULL_VER >= 191627038)
#endif

// Visual Studio 2017 Update 9 (15.9.22) (Visual C++ 14.16)
#if (_MSC_FULL_VER >= 191627039)
#endif

// Visual Studio 2017 Update 9 (15.9.23) (Visual C++ 14.16)
#if (_MSC_FULL_VER >= 191627040)
#endif

// Visual Studio 2017 Update 9 (15.9.24) (Visual C++ 14.16)
#if (_MSC_FULL_VER >= 191627041)
#endif

// Visual Studio 2017 Update 9 (15.9.25) (Visual C++ 14.16)
#if (_MSC_FULL_VER >= 191627042)
#endif

// Visual Studio 2017 Update 9 (15.9.(26-27)) (Visual C++ 14.16)
#if (_MSC_FULL_VER >= 191627043)
#endif

// Visual Studio 2019 (16.0.Prev(1-4)) (Visual C++ 14.20)
#if (_MSC_FULL_VER >= 192027027)
#  define HAMON_HAS_CXX14_VARIABLE_TEMPLATES				// 変数テンプレート
# if (HAMON_CXX_STANDARD >= 20)
#  define HAMON_HAS_CXX20_THREE_WAY_COMPARISON				// P0515R3
#  define HAMON_HAS_CXX20_PROHIBIT_AGGREGATES_WITH_USER_DECLARED_CONSTRUCTORS	// P1008R1
# endif
# if (HAMON_CXX_STANDARD >= 14)	// この 14 は間違いではない。(https://docs.microsoft.com/en-us/cpp/overview/visual-cpp-language-conformance?view=vs-2019#note_14)
#  define HAMON_HAS_CXX20_FEATURE_TEST_MACROS				// P0941R2
# endif
#endif

// Visual Studio 2019 (16.0.(0-4)) (Visual C++ 14.20)
#if (_MSC_FULL_VER >= 192027508)
#endif

// Visual Studio 2019 Update 1 (16.1.(0-6)) (Visual C++ 14.21)
#if (_MSC_FULL_VER >= 192127702)
# if (HAMON_CXX_STANDARD >= 20)
#  define HAMON_HAS_CXX20_DESIGNATED_INITIALIZERS			// P0329R4
#  define HAMON_HAS_CXX20_ADL_AND_FUNCTION_TEMPLATES		// P0846R0
// partial
//#  define HAMON_HAS_CXX20_CONST_MISMATCH_WITH_DEFAULTED_COPY_CONSTRUCTOR	// P0641R2
# endif
// Defect report
# define HAMON_HAS_CXX20_RELAXING_STRUCTURED_BINDINGS				// P0961R1
# define HAMON_HAS_CXX20_STRUCTURED_BINDINGS_TO_ACCESSIBLE_MEMBERS	// P0969R0
#endif

// Visual Studio 2019 Update 2 (16.2.(0-5)) (Visual C++ 14.22)
#if (_MSC_FULL_VER >= 192227905)
# if (HAMON_CXX_STANDARD >= 20)
#  define HAMON_HAS_CXX20_GENERIC_LAMBDAS					// P0428R2
#  define HAMON_HAS_CXX20_CHAR8_T							// P0482R6
#  define HAMON_HAS_CXX20_INIT_CAPTURES						// P0780R2
#  define HAMON_HAS_CXX20_THREE_WAY_COMPARISON_NE_EQ_OP		// P1185R2
#  define HAMON_HAS_CXX20_CONSISTENCY_IMPROVEMENTS_FOR_COMPARISONS	// P1120R0
#  define HAMON_HAS_CXX20_CAPTURE_COPY_THIS					// P0409R2
#  define HAMON_HAS_CXX20_DEFAULT_CONSTRUCTIBLE_AND_ASSIGNABLE_STATELESS_LAMBDAS	// P0624R2
#  define HAMON_HAS_CXX20_DEPRECATE_IMPLICIT_CAPTURE_COPY_THIS	// P0806R2
# endif
#endif

// Visual Studio 2019 Update 3 (16.3.(0-2)) (Visual C++ 14.23)
#if (_MSC_FULL_VER >= 192328105)
# if (HAMON_CXX_STANDARD >= 20)
#  define HAMON_HAS_CXX20_CONCEPTS							// P0734R0
# endif
#endif

// Visual Studio 2019 Update 3 (16.3.(3-8)) (Visual C++ 14.23)
#if (_MSC_FULL_VER >= 192328106)
#endif

// Visual Studio 2019 Update 3 (16.3.(9-10)) (Visual C++ 14.23)
#if (_MSC_FULL_VER >= 192328107)
#endif

// Visual Studio 2019 Update 4 (16.4.(0-2)) (Visual C++ 14.24)
#if (_MSC_FULL_VER >= 192428314)
# if (HAMON_CXX_STANDARD >= 20)
#  define HAMON_HAS_CXX20_SYNTHESIZING_THREE_WAY_COMPARISON		// P1186R3
#  define HAMON_HAS_CXX20_CONDITIONAL_EXPLICIT					// P0892R2
#  define HAMON_HAS_CXX20_USING_ENUM							// P1099R5
#  define HAMON_HAS_CXX20_STRUCTURED_BINDING_EXTENSIONS			// P1091R3,P1381R1
# endif
// Defect report
# define HAMON_HAS_CXX20_SIMPLIFYING_IMPLICIT_LAMBDA_CAPTURE	// P0588R1
# define HAMON_HAS_CXX20_NODISCARD_CTOR							// P1771R1
# define HAMON_HAS_CXX20_IMPLICIT_MOVE							// P1825R0
#endif

// Visual Studio 2019 Update 4 (16.4.3) (Visual C++ 14.24)
#if (_MSC_FULL_VER >= 192428315)
#endif

// Visual Studio 2019 Update 4 (16.4.(4-5)) (Visual C++ 14.24)
#if (_MSC_FULL_VER >= 192428316)
#endif

// Visual Studio 2019 Update 4 (16.4.6) (Visual C++ 14.24)
#if (_MSC_FULL_VER >= 192428319)
#endif

// Visual Studio 2019 Update 5 (16.5.0) (Visual C++ 14.25)
#if (_MSC_FULL_VER >= 192528610)
# if (HAMON_CXX_STANDARD >= 20)
#  define HAMON_HAS_CXX20_NODISCARD_WITH_MESSAGE				// P1301R4
#  define HAMON_HAS_CXX20_DEFAULTING_COMPARISON_BY_VALUE		// P1946R0
#  define HAMON_HAS_CXX20_REMOVE_WEAK_EQUALITY_STRONG_EQUALITY	// P1959R0
#  define HAMON_HAS_CXX20_CONSTEXPR_TRY_CATCH					// P1002R1
#  define HAMON_HAS_CXX20_BITFIELD_DEFAULT_MEMBER_INITIALIZER	// P0683R1
#  define HAMON_HAS_CXX20_RANGE_BASED_FOR_INITIALIZER			// P0614R1
#  define HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED					// P0595R2
#  define HAMON_HAS_CXX20_DEPRECATE_COMMA_IN_SUBSCRIPTING_EXPRESSIONS	// P1161R3
#  if !(defined(_MSVC_TRADITIONAL) && _MSVC_TRADITIONAL)
#   define HAMON_HAS_CXX20_VA_OPT								// P0306R4,P1042R1
#  endif
# endif
// Defect report
# define HAMON_HAS_CXX20_RELAXING_RANGE_FOR						// P0962R1
#endif

// Visual Studio 2019 Update 5 (16.5.1) (Visual C++ 14.25)
#if (_MSC_FULL_VER >= 192528611)
#endif

// Visual Studio 2019 Update 5 (16.5.(2-3)) (Visual C++ 14.25)
#if (_MSC_FULL_VER >= 192528612)
#endif

// Visual Studio 2019 Update 5 (16.5.(4-5)) (Visual C++ 14.25)
#if (_MSC_FULL_VER >= 192528614)
#endif

// Visual Studio 2019 version 16.6.0
#if (_MSC_FULL_VER >= 192628805)
# if (HAMON_CXX_STANDARD >= 20)
#  define HAMON_HAS_CXX20_LIKELY								// P0479R5
#  define HAMON_HAS_CXX20_UNLIKELY								// P0479R5
#  define HAMON_HAS_CXX20_NONTYPE_TEMPLATE_PARAMETER_FLOAT		// P1907R1
# endif
# if (HAMON_CXX_STANDARD >= 14)	// この 14 は間違いではない。(https://docs.microsoft.com/en-us/cpp/overview/visual-cpp-language-conformance?view=vs-2019#note_14)
#  define HAMON_HAS_CXX20_STRONGER_UNICODE_REQUIREMENTS			// P1041R4,P1139R2
#  define HAMON_HAS_CXX20_ACCESS_CHECKING_ON_SPECIALIZATIONS	// P0692R1
# endif
#endif

// Visual Studio 2019 version 16.6.(1-5)
#if (_MSC_FULL_VER >= 192628806)
#endif

// Visual Studio 2019 version 16.7.0
#if (_MSC_FULL_VER >= 192729110)
# if (HAMON_CXX_STANDARD >= 20)
#  define HAMON_HAS_CXX20_DESTROYING_DELETE					// P0722R3
#  define HAMON_HAS_CXX20_CONSTEXPR_TRIVIAL_DEFAULT_INIT	// P1331R2
#  define HAMON_HAS_CXX20_DEDUCTION_GUIDES					// P1814R0,P1816R0,P2082R1
#  define HAMON_HAS_CXX20_CTAD_ALIAS_TEMPLATE				// P1814R0
#  define HAMON_HAS_CXX20_CTAD_AGGREGATE					// P1816R0,P2082R1
#  define HAMON_HAS_CXX20_NESTED_INLINE_NAMESPACES			// P1094R2
#  define HAMON_HAS_CXX20_CONVERSIONS_TO_UNBOUNDED_ARRAY	// P0388R4
#  define HAMON_HAS_CXX20_DEPRECATE_VOLATILE				// P1152R4
#  define HAMON_HAS_CXX20_CONSISTENT_DEFAULTED_COMPARISONS	// P2085R0
# endif
// Defect report
# define HAMON_HAS_CXX20_ARRAY_SIZE_DEDUCTION_NEW			// P1009R2
# define HAMON_HAS_CXX20_POINTER_TO_BOOL_CONVERTING			// P1957R2
#endif

// Visual Studio 2019 version 16.7.(1-4)
#if (_MSC_FULL_VER >= 192729111)
#endif

// Visual Studio 2019 version 16.7.(5-7)
#if (_MSC_FULL_VER >= 192729112)
#endif

// Visual Studio 2019 version 16.8.0
#if (_MSC_FULL_VER >= 192800000)
# if (HAMON_CXX_STANDARD >= 20)
#  define HAMON_HAS_CXX20_COROUTINES						// P0912R5
#  define HAMON_HAS_CXX20_AGGREGATE_PAREN_INIT				// P0960R3
#  define HAMON_HAS_CXX20_MODULES							// P1103R3
#  define HAMON_HAS_CXX20_LAMBDAS_IN_UNEVALUATED_CONTEXTS	// P0315R4
#  define HAMON_HAS_CXX20_CONDITIONALLY_TRIVIAL_SPECIAL_MEMBER_FUNCTIONS	// P0848R3
#  define HAMON_HAS_CXX20_NONTYPE_TEMPLATE_PARAMETER_CLASS	// P0732R2
# endif
// Defect report
# define HAMON_HAS_CXX20_EXCEPTION_SPEC_DEFAULTED_FUNCTION	// P1286R2
#endif

// Visual Studio 2019 version 16.8.1
#if (_MSC_FULL_VER >= 192829333)
#endif

// Visual Studio 2019 version 16.8.2
#if (_MSC_FULL_VER >= 192829334)
#endif

// Visual Studio 2019 version 16.8.3
#if (_MSC_FULL_VER >= 192829335)
#endif

// Visual Studio 2019 version 16.8.4
#if (_MSC_FULL_VER >= 192829336)
#endif

// Visual Studio 2019 version 16.8.(5-6)
#if (_MSC_FULL_VER >= 192829337)
#endif

// Visual Studio 2019 version 16.9.0
#if (_MSC_FULL_VER >= 192829910)
# if (HAMON_CXX_STANDARD >= 20)
#  define HAMON_HAS_CXX20_OPTIONAL_TYPENAME					// P0634R3
#  define HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC			// P0784R7
#  define HAMON_HAS_CXX20_NO_UNIQUE_ADDRESS					// P0840R2
#  define HAMON_HAS_CXX20_CONSTEXPR_VIRTUAL_FUNCTION		// P1064R0
#  define HAMON_HAS_CXX20_ABBREVIATED_FUNCTION_TEMPLATE		// P1141R2
#  define HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_CAST			// P1327R1
#  define HAMON_HAS_CXX20_CONSTEXPR_ASM						// P1668R1
# endif
#endif

// Visual Studio 2019 version 16.9.1
#if (_MSC_FULL_VER >= 192829912)
#endif

// Visual Studio 2019 version 16.9.(2-3)
#if (_MSC_FULL_VER >= 192829913)
#endif

// Visual Studio 2019 version 16.9.4
#if (_MSC_FULL_VER >= 192829914)
#endif

// Visual Studio 2019 version 16.9.(5-6)
#if (_MSC_FULL_VER >= 192829915)
#endif

// Visual Studio 2019 version 16.10.(0-1)
#if (_MSC_FULL_VER >= 192930037)
# if (HAMON_CXX_STANDARD >= 20)
#  define HAMON_HAS_CXX20_CONSTEVAL							// P1073R3
#  define HAMON_HAS_CXX20_CONSTINIT							// P1143R2
# endif
#endif

// Visual Studio 2019 version 16.10.(2-3)
#if (_MSC_FULL_VER >= 192930038)
#endif

// Visual Studio 2019 version 16.10.4
#if (_MSC_FULL_VER >= 192930040)
#endif

// Visual Studio 2019 version 16.11.(0-3)
#if (_MSC_FULL_VER >= 192930133)
#endif

// Visual Studio 2019 version 16.11.(4-5)
#if (_MSC_FULL_VER >= 192930136)
#endif

// Visual Studio 2019 version 16.11.(6-7)
#if (_MSC_FULL_VER >= 192930137)
#endif

// Visual Studio 2019 version 16.11.8
#if (_MSC_FULL_VER >= 192930138)
#endif

// Visual Studio 2019 version 16.11.9
#if (_MSC_FULL_VER >= 192930139)
#endif

// Visual Studio 2019 version 16.11.10
#if (_MSC_FULL_VER >= 192930140)
#endif

// Visual Studio 2019 version 16.11.11
#if (_MSC_FULL_VER >= 192930141)
#endif

// Visual Studio 2019 version 16.11.12
#if (_MSC_FULL_VER >= 192930142)
#endif

// Visual Studio 2019 version 16.11.13
#if (_MSC_FULL_VER >= 192930143)
#endif

// Visual Studio 2019 version 16.11.(14-16)
#if (_MSC_FULL_VER >= 192930145)
#endif

// Visual Studio 2019 version 16.11.(17-20)
#if (_MSC_FULL_VER >= 192930146)
#endif

// Visual Studio 2019 Version 16.11.(21-23)
#if (_MSC_FULL_VER >= 192930147)
#endif

// Visual Studio 2019 Version 16.11.(24-26)
#if (_MSC_FULL_VER >= 192930148)
#endif

// Visual Studio 2019 Version 16.11.(27-29)
#if (_MSC_FULL_VER >= 192930151)
#endif

// Visual Studio 2019 Version 16.11.(30-31)
#if (_MSC_FULL_VER >= 192930152)
#endif

// Visual Studio 2019 Version 16.11.(32-33)
#if (_MSC_FULL_VER >= 192930153)
#endif

// Visual Studio 2019 Version 16.11.(34-40)
#if (_MSC_FULL_VER >= 192930154)
#endif

// Visual Studio 2019 Version 16.11.41
#if (_MSC_FULL_VER >= 192930156)
#endif

// Visual Studio 2019 Version 16.11.42
#if (_MSC_FULL_VER >= 192930157)
#endif

// Visual Studio 2019 Version 16.11.(43-44)
#if (_MSC_FULL_VER >= 192930158)
#endif

// Visual Studio 2019 Version 16.11.(45-48)
#if (_MSC_FULL_VER >= 192930159)
#endif

// Visual Studio 2022 Preview version 17.0.0 Preview 1.(0-1)
#if (_MSC_FULL_VER >= 192930130)
#endif

// Visual Studio 2022 Preview version 17.0.0 Preview 2.0
#if (_MSC_FULL_VER >= 193030401)
#endif

// Visual Studio 2022 Preview version 17.0.0 Preview 3.(0-1)
#if (_MSC_FULL_VER >= 193030423)
#endif

// Visual Studio 2022 Preview version 17.0.0 Preview 4.(0-1)
#if (_MSC_FULL_VER >= 193030528)
#endif

// Visual Studio 2022 Preview version 17.0.0 Preview (5.0-6.0)
#if (_MSC_FULL_VER >= 193030704)
#endif

// Visual Studio 2022 Preview version 17.0.0 Preview 7.0
#if (_MSC_FULL_VER >= 193030705)
#endif

// Visual Studio 2022 Preview version 17.1.0 Preview 1.(0-1)
#if (_MSC_FULL_VER >= 193130818)
#endif

// Visual Studio 2022 Preview version 17.1.0 Preview 2.0
#if (_MSC_FULL_VER >= 193130919)
#endif

// Visual Studio 2022 Preview version 17.1.0 Preview (3.0-4.0)
#if (_MSC_FULL_VER >= 193131103)
#endif

// Visual Studio 2022 Preview version 17.1.0 Preview (5.0-6.0)
#if (_MSC_FULL_VER >= 193131104)
#endif

// Visual Studio 2022 Preview version 17.2.0 Preview 1.0
#if (_MSC_FULL_VER >= 193231114)
#endif

// Visual Studio 2022 Preview version 17.2.0 Preview 2.(0-1)
#if (_MSC_FULL_VER >= 193231302)
#endif

// Visual Studio 2022 Preview version 17.2.0 Preview (3.0-4.0)
#if (_MSC_FULL_VER >= 193231326)
#endif

// Visual Studio 2022 Preview version 17.2.0 Preview 5.0
#if (_MSC_FULL_VER >= 193231328)
#endif

// Visual Studio 2022 Preview version 17.3.0 Preview 1.(0-1)
#if (_MSC_FULL_VER >= 193331424)
#endif

// Visual Studio 2022 Preview version 17.3.0 Preview 2.0
#if (_MSC_FULL_VER >= 193331517)
#endif

// Visual Studio 2022 Preview version 17.3.0 Preview 6.0
#if (_MSC_FULL_VER >= 193331629)
#endif

// Visual Studio 2022 Preview version 17.4.0 Preview 1.0
#if (_MSC_FULL_VER >= 193431721)
#endif

// Visual Studio 2022 Preview version 17.4.0 Preview 2.(0-1)
#if (_MSC_FULL_VER >= 193431823)
#endif

// Visual Studio 2022 Preview version 17.4.0 Preview 3.0
#if (_MSC_FULL_VER >= 193431921)
#endif

// Visual Studio 2022 Preview version 17.4.0 Preview 4.0
#if (_MSC_FULL_VER >= 193431931)
#endif

// Visual Studio 2022 Preview version 17.4.0 Preview 5.0
#if (_MSC_FULL_VER >= 193431932)
#endif

// Visual Studio 2022 Preview version 17.4.0 Preview 6.0
#if (_MSC_FULL_VER >= 193431933)
#endif

// Visual Studio 2022 Preview Version 17.5.0 Preview 1.0
#if (_MSC_FULL_VER >= 193532019)
#endif

// Visual Studio 2022 Preview Version 17.5.0 Preview 2.0
#if (_MSC_FULL_VER >= 193532124)
#endif

// Visual Studio 2022 Preview Version 17.5.0 Preview (3.0-6.0)
#if (_MSC_FULL_VER >= 193532213)
#endif

// Visual Studio 2022 Preview Version 17.6.0 Preview 1.0
#if (_MSC_FULL_VER >= 193632323)
#endif

// Visual Studio 2022 Preview Version 17.6.0 Preview 2.0
#if (_MSC_FULL_VER >= 193632502)
#endif

// Visual Studio 2022 Preview Version 17.6.0 Preview (3.0-4.0)
#if (_MSC_FULL_VER >= 193632522)
#endif

// Visual Studio 2022 Preview Version 17.6.0 Preview (5.0-7.0)
#if (_MSC_FULL_VER >= 193632530)
#endif

// Visual Studio 2022 Preview Version 17.7.0 Preview (1.0-2.0)
#if (_MSC_FULL_VER >= 193732705)
#endif

// Visual Studio 2022 Preview Version 17.7.0 Preview (3.0-6.0)
#if (_MSC_FULL_VER >= 193732820)
#endif

// Visual Studio 2022 Preview Version 17.8.0 Preview 1.0
#if (_MSC_FULL_VER >= 193832919)
#endif

// Visual Studio 2022 Preview Version 17.8.0 Preview 2.0
#if (_MSC_FULL_VER >= 193833030)
#endif

// Visual Studio 2022 Preview Version 17.8.0 Preview (3.0-4.0)
#if (_MSC_FULL_VER >= 193833126)
#endif

// Visual Studio 2022 Preview Version 17.8.0 Preview 5.0
#if (_MSC_FULL_VER >= 193833128)
#endif

// Visual Studio 2022 Preview Version 17.8.0 Preview (6.0-7.0)
#if (_MSC_FULL_VER >= 193833129)
#endif

// Visual Studio 2022 Preview Version 17.9.0 Preview 1.(0-1)
#if (_MSC_FULL_VER >= 193933218)
#endif

// Visual Studio 2022 Preview Version 17.9.0 Preview 2.(0-1)
#if (_MSC_FULL_VER >= 193933321)
#endif

// Visual Studio 2022 Preview Version 17.9.0 Preview (3.0-4.0)
#if (_MSC_FULL_VER >= 193933428)
#endif

// Visual Studio 2022 Preview Version 17.9.0 Preview 5.0
#if (_MSC_FULL_VER >= 193933519)
#endif

// Visual Studio 2022 Preview Version 17.10.0 Preview 1.0
#if (_MSC_FULL_VER >= 194033521)
#endif

// Visual Studio 2022 Preview Version 17.10.0 Preview 2.0
#if (_MSC_FULL_VER >= 194033617)
#endif

// Visual Studio 2022 Preview Version 17.10.0 Preview 3.0
#if (_MSC_FULL_VER >= 194033721)
#endif

// Visual Studio 2022 Preview Version 17.10.0 Preview 4.0
#if (_MSC_FULL_VER >= 194033807)
#endif

// Visual Studio 2022 Preview Version 17.10.0 Preview (5.0-7.0)
#if (_MSC_FULL_VER >= 194033808)
#endif

// Visual Studio 2022 Preview Version 17.11.0 Preview 1.(0-1)
#if (_MSC_FULL_VER >= 194133901)
#endif

// Visual Studio 2022 Preview Version 17.11.0 Preview 2.1
#if (_MSC_FULL_VER >= 194133923)
#endif

// Visual Studio 2022 Preview Version 17.11.0 Preview (3.0-4.0)
#if (_MSC_FULL_VER >= 194134021)
#endif

// Visual Studio 2022 Preview Version 17.11.0 Preview (5.0-6.0)
#if (_MSC_FULL_VER >= 194134117)
#endif

// Visual Studio 2022 Preview Version 17.11.0 Preview 7.0
#if (_MSC_FULL_VER >= 194134119)
#endif

// Visual Studio 2022 Preview Version 17.12.0 Preview 1.0
#if (_MSC_FULL_VER >= 194234226)
#endif

// Visual Studio 2022 Preview Version 17.12.0 Preview 2.(0-1)
#if (_MSC_FULL_VER >= 194234321)
#endif

// Visual Studio 2022 Preview Version 17.12.0 Preview 3.0
#if (_MSC_FULL_VER >= 194234430)
#endif

// Visual Studio 2022 Preview Version 17.12.0 Preview 4.0
#if (_MSC_FULL_VER >= 194234431)
#endif

// Visual Studio 2022 Preview Version 17.12.0 Preview 5.0
#if (_MSC_FULL_VER >= 194234432)
#endif

// Visual Studio 2022 Preview Version 17.13.0 Preview 1.0
#if (_MSC_FULL_VER >= 194334604)
#endif

// Visual Studio 2022 Preview Version 17.13.0 Preview 2.(0-1)
#if (_MSC_FULL_VER >= 194334618)
#endif

// Visual Studio 2022 Preview Version 17.13.0 Preview 3.0
#if (_MSC_FULL_VER >= 194334618)
#endif

// Visual Studio 2022 Preview Version 17.13.0 Preview (4.0-5.0)
#if (_MSC_FULL_VER >= 194334808)
#endif

// Visual Studio 2022 Preview Version 17.14.0 Preview 1.(0-1)
#if (_MSC_FULL_VER >= 194434823)
#endif

// Visual Studio 2022 Preview Version 17.14.0 Preview 2.0
#if (_MSC_FULL_VER >= 194434918)
#endif

// Visual Studio 2022 Preview Version 17.14.0 Preview 3.0
#if (_MSC_FULL_VER >= 194435109)
#endif

// Visual Studio 2022 Preview Version 17.14.0 Preview (4.0-5.0)
#if (_MSC_FULL_VER >= 194435112)
#endif

// Visual Studio 2022 Preview Version 17.14.0 Preview 6.0
#if (_MSC_FULL_VER >= 194435128)
#endif

// Visual Studio 2022 Preview Version 17.14.0 Preview 7.0
#if (_MSC_FULL_VER >= 194435207)
#endif

// Visual Studio 2022 Preview Version 17.14.1 Preview 1.0
#if (_MSC_FULL_VER >= 194435207)
#endif

// Visual Studio 2022 Preview Version 17.14.2 Preview 1.0
#if (_MSC_FULL_VER >= 194435207)
#endif

// Visual Studio 2022 Preview Version 17.14.3 Preview 1.0
#if (_MSC_FULL_VER >= 194435208)
#endif

// Visual Studio 2022 Preview Version 17.14.4 Preview 1.0
#if (_MSC_FULL_VER >= 194435209)
#endif

// Visual Studio 2022 Preview Version 17.14.5 Preview 1.0
#if (_MSC_FULL_VER >= 194435209)
#endif

// Visual Studio 2022 Preview Version 17.14.6 Preview 1.0
#if (_MSC_FULL_VER >= 194435211)
#endif

// Visual Studio 2022 Preview Version 17.14.7 Preview 1.0
#if (_MSC_FULL_VER >= 194435211)
#endif

// Visual Studio 2022 Version 17.0.(0-1)
#if (_MSC_FULL_VER >= 193030705)
# define HAMON_HAS_CXX23_CHARACTER_LITERALS_IN_PREPROCESSOR		// P2316R2	Consistent character literal encoding
#endif

// Visual Studio 2022 Version 17.0.(2-4)
#if (_MSC_FULL_VER >= 193030706)
#endif

// Visual Studio 2022 Version 17.0.(5-6)
#if (_MSC_FULL_VER >= 193030709)
#endif

// Visual Studio 2022 Version 17.1.(0-1)
#if (_MSC_FULL_VER >= 193131104)
// Defect report
//#define HAMON_HAS_CXX20_CONSTEXPR_IN_DECLTYPE				// P0859R0	(partial)
#endif

// Visual Studio 2022 Version 17.1.(2-3)
#if (_MSC_FULL_VER >= 193131105)
#endif

// Visual Studio 2022 Version 17.1.4
#if (_MSC_FULL_VER >= 193131106)
#endif

// Visual Studio 2022 Version 17.1.(5-6)
#if (_MSC_FULL_VER >= 193131107)
#endif

// Visual Studio 2022 Version 17.2.0
#if (_MSC_FULL_VER >= 193231328)
# if (HAMON_CXX_STANDARD >= 23)
#  define HAMON_HAS_CXX23_EXPLICIT_THIS_PARAMETER			// P0847R7, P2797R0, CWG2586	Deducing this										__cpp_explicit_this_parameter >= 202110L
# endif
#endif

// Visual Studio 2022 Version 17.2.2
#if (_MSC_FULL_VER >= 193231329)
#endif

// Visual Studio 2022 Version 17.2.3
#if (_MSC_FULL_VER >= 193231330)
#endif

// Visual Studio 2022 Version 17.2.4
#if (_MSC_FULL_VER >= 193231331)
#endif

// Visual Studio 2022 Version 17.2.(5-6)
#if (_MSC_FULL_VER >= 193231332)
#endif

// Visual Studio 2022 Version 17.3.(0-3)
#if (_MSC_FULL_VER >= 193331629)
#endif

// Visual Studio 2022 Version 17.3.(4-6)
#if (_MSC_FULL_VER >= 193331630)
#endif

// Visual Studio 2022 Version 17.4.(0-1)
#if (_MSC_FULL_VER >= 193431933)
// DR20:
# if (HAMON_CXX_STANDARD >= 20)
#  define HAMON_HAS_CXX23_CHAR8_T_COMPATIBILITY			// P2513R4	DR20: char8_t Compatibility and Portability Fix							__cpp_char8_t >= 202207L
# endif
#endif

// Visual Studio 2022 Version 17.4.2
#if (_MSC_FULL_VER >= 193431935)
#endif

// Visual Studio 2022 Version 17.4.(3-4)
#if (_MSC_FULL_VER >= 193431937)
#endif

// Visual Studio 2022 Version 17.4.5
#if (_MSC_FULL_VER >= 193431942)
#endif

// Visual Studio 2022 Version 17.5.(0-2)
#if (_MSC_FULL_VER >= 193532215)
#endif

// Visual Studio 2022 Version 17.5.3
#if (_MSC_FULL_VER >= 193532216)
#endif

// Visual Studio 2022 Version 17.5.(4-5)
#if (_MSC_FULL_VER >= 193532217)
#endif

// Visual Studio 2022 Version 17.6.(0-2)
#if (_MSC_FULL_VER >= 193632532)
#endif

// Visual Studio 2022 Version 17.6.3
#if (_MSC_FULL_VER >= 193632534)
#endif

// Visual Studio 2022 Version 17.6.4
#if (_MSC_FULL_VER >= 193632535)
#endif

// Visual Studio 2022 Version 17.6.5
#if (_MSC_FULL_VER >= 193632537)
#endif

// Visual Studio 2022 Version 17.7.(0-3)
#if (_MSC_FULL_VER >= 193732822)
#endif

// Visual Studio 2022 Version 17.7.4
#if (_MSC_FULL_VER >= 193732824)
#endif

// Visual Studio 2022 Version 17.7.(5-6)
#if (_MSC_FULL_VER >= 193732825)
#endif

// Visual Studio 2022 Version 17.8.(0-2)
#if (_MSC_FULL_VER >= 193833130)
#endif

// Visual Studio 2022 Version 17.8.3
#if (_MSC_FULL_VER >= 193833133)
#endif

// Visual Studio 2022 Version 17.8.(4-5)
#if (_MSC_FULL_VER >= 193833134)
#endif

// Visual Studio 2022 Version 17.8.6
#if (_MSC_FULL_VER >= 193833135)
#endif

// Visual Studio 2022 Version 17.9.0
#if (_MSC_FULL_VER >= 193933519)
#endif

// Visual Studio 2022 Version 17.9.1
#if (_MSC_FULL_VER >= 193933520)
#endif

// Visual Studio 2022 Version 17.9.2
#if (_MSC_FULL_VER >= 193933521)
#endif

// Visual Studio 2022 Version 17.9.3
#if (_MSC_FULL_VER >= 193933522)
#endif

// Visual Studio 2022 Version 17.9.(4-7)
#if (_MSC_FULL_VER >= 193933523)
#endif

// Visual Studio 2022 Version 17.10.0
#if (_MSC_FULL_VER >= 194033808)
# if (HAMON_CXX_STANDARD >= 20)
#  define HAMON_HAS_CXX23_ELIFDEF				// P2334R1	Add support for preprocessing directives elifdef and elifndef
# endif
// DR98/11:
#define HAMON_HAS_CXX23_ALLOW_STATIC_ASSERT_FALSE	// CWG2518	DR98/11: Clarify reporting of diagnostic directives and allow static_assert of non-value-dependent expressions in a template context
#endif

// Visual Studio 2022 Version 17.10.(1-3)
#if (_MSC_FULL_VER >= 194033811)
#endif

// Visual Studio 2022 Version 17.10.4
#if (_MSC_FULL_VER >= 194033812)
#endif

// Visual Studio 2022 Version 17.10.5
#if (_MSC_FULL_VER >= 194033813)
#endif

// Visual Studio 2022 Version 17.11.(0-4)
#if (_MSC_FULL_VER >= 194134120)
#endif

// Visual Studio 2022 Version 17.11.5
#if (_MSC_FULL_VER >= 194134123)
#endif

// Visual Studio 2022 Version 17.12.(0-1)
#if (_MSC_FULL_VER >= 194234433)
#  if (HAMON_CXX_STANDARD >= 23)
#    define HAMON_HAS_CXX23_MULTIDIMENSIONAL_SUBSCRIPT					// P2128R6, CWG2507	Multidimensional subscript operator								__cpp_multidimensional_subscript >= 202110L
#  endif
#endif

// Visual Studio 2022 Version 17.12.(2-3)
#if (_MSC_FULL_VER >= 194234435)
#endif

// Visual Studio 2022 Version 17.12.4
#if (_MSC_FULL_VER >= 194234436)
#endif

// Visual Studio 2022 Version 17.13.(0-2)
#if (_MSC_FULL_VER >= 194334808)
#  if (HAMON_CXX_STANDARD >= 23)
#    define HAMON_HAS_CXX23_SIZE_T_SUFFIX	// P0330R8	Literal Suffix for (signed) size_t		__cpp_size_t_suffix >= 202011L
#    define HAMON_HAS_CXX23_CONSTEXPR_NON_LITERAL_VARIABLES				// P2242R3	Non-literal variables (and labels and gotos) in constexpr functions		__cpp_constexpr >= 202110L
#  endif
#endif

// Visual Studio 2022 Version 17.13.(3-5)
#if (_MSC_FULL_VER >= 194334809)
#endif

// Visual Studio 2022 Version 17.13.6
#if (_MSC_FULL_VER >= 194334810)
#endif

// Visual Studio 2022 Version 17.14.(0-2)
#if (_MSC_FULL_VER >= 194435207)
#  if (HAMON_CXX_STANDARD >= 23)
#    define HAMON_HAS_CXX23_LAMBDA_WITHOUT_PAREN		// P1102R2	Down with ()!
// MSVC 19.44 で "if consteval" 自体は実装されたが、その中でconsteval関数を呼び出すことができない
//#    define HAMON_HAS_CXX23_IF_CONSTEVAL				// P1938R3	if consteval				__cpp_if_consteval >= 202106L
#    define HAMON_HAS_CXX23_NARROWING_CONVERSIONS_TO_BOOL				// P1401R5	Narrowing contextual conversions to bool
#    define HAMON_HAS_CXX23_ATTRIBUTES_ON_LAMBDAS						// P2173R1	Attributes on lambda-expressions
#    define HAMON_HAS_CXX23_STATIC_CALL_OPERATOR						// P1169R4	static operator()														__cpp_static_call_operator >= 202207L
#    define HAMON_HAS_CXX23_STATIC_SUBSCRIPT_OPERATOR					// P2589R1	static operator[]														__cpp_multidimensional_subscript >= 202211L
#  endif
#endif

// Visual Studio 2022 Version 17.14.3
#if (_MSC_FULL_VER >= 194435208)
#endif

// Visual Studio 2022 Version 17.14.(4-5)
#if (_MSC_FULL_VER >= 194435209)
#endif

// Visual Studio 2022 Version 17.14.(6-7)
#if (_MSC_FULL_VER >= 194435211)
#endif

#if (HAMON_CXX_STANDARD >= 17)
#  if defined(__cpp_constexpr) && (__cpp_constexpr >= 201603)
#    define HAMON_HAS_CXX17_CONSTEXPR
#  endif
#endif

#if (HAMON_CXX_STANDARD >= 20)
#  if defined(__cpp_constexpr) && (__cpp_constexpr >= 201907)
#    define HAMON_HAS_CXX20_CONSTEXPR
#  endif
#endif

#if (HAMON_CXX_STANDARD >= 23)
#endif

#define HAMON_NO_COMPLETE_VALUE_INITIALIZATION
#define HAMON_NO_TWO_PHASE_NAME_LOOKUP					// Two-phase name lookup
//#define HAMON_HAS_CXX11_PRAGMA_OPERATOR				// Pragma演算子
#define HAMON_HAS_CXX20_TWOS_COMPLEMENT_SIGNED_INTEGERS		// P1236R1
#define HAMON_HAS_CXX20_PSEUDO_DESTRUCTOR					// P0593R6
#define HAMON_HAS_CXX23_DECLARATION_ORDER_LAYOUT			// P1847R4	Make declaration order layout mandated
#define HAMON_HAS_CXX23_MIXED_STRING_LITERAL_CONCATENATION	// P2201R1	Mixed string literal concatenation

#if 0

// C++11
#define HAMON_HAS_CXX11_RVALUE_REFERENCES				// N2118	__cpp_rvalue_references					右辺値参照
#define HAMON_HAS_CXX11_REF_QUALIFIERS					// N2439	__cpp_ref_qualifiers					メンバ関数の左辺値／右辺値修飾
#define HAMON_HAS_CXX11_NSDMI							// N2756	__cpp_nsdmi								非静的メンバ変数の初期化
#define HAMON_HAS_CXX11_VARIADIC_TEMPLATES				// N2242	__cpp_variadic_templates				可変引数テンプレート
#define HAMON_HAS_CXX11_INITIALIZER_LISTS				// N2672	__cpp_initializer_lists					初期化子リスト
#define HAMON_HAS_CXX11_STATIC_ASSERT					// N1720	__cpp_static_assert						コンパイル時アサート
#define HAMON_HAS_CXX11_AUTO_DECLARATIONS				// N2546	none									型推論
#define HAMON_HAS_CXX11_TRAILING_RETURN_TYPE			// N2541	none									戻り値の型を後置する関数宣言構文
#define HAMON_HAS_CXX11_LAMBDAS							// N2927	__cpp_lambdas							ラムダ式
#define HAMON_HAS_CXX11_DECLTYPE						// N2343	__cpp_decltype							式の型を取得
#define HAMON_HAS_CXX11_RIGHT_ANGLE_BRACKETS			// N1757	none									テンプレートの右山カッコ
#define HAMON_HAS_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS	// 			none									関数テンプレートに関する既定のテンプレート引数
#define HAMON_HAS_CXX11_SFINAE_EXPR						// N2634	none									任意の式によるSFINAE
#define HAMON_HAS_CXX11_ALIAS_TEMPLATES					// N2258	__cpp_alias_templates					エイリアステンプレート
#define HAMON_HAS_CXX11_EXTERN_TEMPLATE					// N1987	none									テンプレートのインスタンス化抑止
#define HAMON_HAS_CXX11_NULLPTR							// N2431	none									nullptr
#define HAMON_HAS_CXX11_SCOPED_ENUMS					// N2347	none									スコープを持つ列挙型
#define HAMON_HAS_CXX11_FORWARD_DECLARE_ENUMS			// N2764	none									enumの先行宣言
#define HAMON_HAS_CXX11_ATTRIBUTES						// N2761	__cpp_attributes						属性構文
#define HAMON_HAS_CXX11_NORETURN						// N2761	__has_cpp_attribute(noreturn)			[[noreturn]]属性
#define HAMON_HAS_CXX11_CARRIES_DEPENDENCY				// N2761	__has_cpp_attribute(carries_dependency)	[[carries_dependency]]属性
#define HAMON_HAS_CXX11_CONSTEXPR						// N2235	__cpp_constexpr							定数式
#define HAMON_HAS_CXX11_ALIGNAS							// N2341	none									アライメント指定
#define HAMON_HAS_CXX11_ALIGNOF							// N2341	none									アライメント取得
#define HAMON_HAS_CXX11_DELEGATING_CONSTRUCTORS			// N1986	__cpp_delegating_constructors			移譲コンストラクタ
#define HAMON_HAS_CXX11_INHERITING_CONSTRUCTORS			// N2540	__cpp_inheriting_constructors			継承コンストラクタ
#define HAMON_HAS_CXX11_EXPLICIT_CONVERSION_OPERATORS	// N2437	none									明示的な型変換演算子
#define HAMON_HAS_CXX11_CHAR16_T						// N2249	__cpp_unicode_characters				char16_t
#define HAMON_HAS_CXX11_CHAR32_T						// N2249	__cpp_unicode_characters				char32_t
#define HAMON_HAS_CXX11_UNICODE_LITERALS				// N2442	__cpp_unicode_literals					UTF-8文字列リテラル
#define HAMON_HAS_CXX11_RAW_STRINGS						// N2442	__cpp_raw_strings						生文字列リテラル
#define HAMON_HAS_CXX11_UNIVERSAL_CHARACTER_NAME		// N2170 	none									文字列リテラル中のユニバーサルキャラクタ名
#define HAMON_HAS_CXX11_USER_DEFINED_LITERALS			// N2765	__cpp_user_defined_literals				ユーザー定義リテラル
// TODO													// N2342											Standard-layout and trivial types
#define HAMON_HAS_CXX11_DELETED_FUNCTIONS				// N2346	none									関数のdelete宣言
#define HAMON_HAS_CXX11_DEFAULTED_FUNCTIONS				// N2346	none									関数のdefault宣言
#define HAMON_HAS_CXX11_EXTENDED_FRIEND_DECLARATIONS	// N1791	none									friend宣言できる対象を拡張
#define HAMON_HAS_CXX11_EXTENDED_SIZEOF					// N2253	none									拡張sizeof
#define HAMON_HAS_CXX11_INLINE_NAMESPACES				// N2535	none									インライン名前空間
#define HAMON_HAS_CXX11_UNRESTRICTED_UNIONS				// N2544	none									共用体の制限解除
#define HAMON_HAS_CXX11_LOCAL_TYPE_TEMPLATE_ARGS		// N2657	none									ローカル型と無名型をテンプレート引数として使用することを許可
#define HAMON_HAS_CXX11_RANGE_BASED_FOR					// N2930	__cpp_range_based_for					範囲for文
#define HAMON_HAS_CXX11_OVERRIDE						// N3272	none									override
#define HAMON_HAS_CXX11_FINAL							// N3272	none									final
#define HAMON_HAS_CXX11_NOEXCEPT						// N3050	none									noexcept
#define HAMON_HAS_CXX11_THREAD_LOCAL					// N2659	none									スレッドローカルストレージ
#define HAMON_HAS_CXX11_THREADSAFE_STATIC_INIT			// N2660	__cpp_threadsafe_static_init			ブロックスコープを持つstatic変数初期化のスレッドセーフ化
#define HAMON_HAS_CXX11_LONG_LONG						// N1811	none									long long型
#define HAMON_HAS_CXX11_VARIADIC_MACROS					// N1653	none									可変引数マクロ
#define HAMON_HAS_CXX11_PRAGMA_OPERATOR					// N1653	none									Pragma演算子
#define HAMON_HAS_CXX11_UNIFORM_INITIALIZATION			// N2640	none									一様初期化

// C++14
#define HAMON_HAS_CXX14_BINARY_LITERALS					// N3472	__cpp_binary_literals					2進数リテラル
#define HAMON_HAS_CXX14_DECLTYPE_AUTO					// N3638	__cpp_decltype_auto						通常関数の戻り値型推論
#define HAMON_HAS_CXX14_RETURN_TYPE_DEDUCTION			// N3638	__cpp_return_type_deduction				通常関数の戻り値型推論
#define HAMON_HAS_CXX14_INIT_CAPTURES					// N3610	__cpp_init_captures						ラムダ式の初期化キャプチャ
#define HAMON_HAS_CXX14_GENERIC_LAMBDAS					// N3649	__cpp_generic_lambdas					ジェネリックラムダ
#define HAMON_HAS_CXX14_DEPRECATED						// N3760	__has_cpp_attribute(deprecated)			[[deprecated]]属性
#define HAMON_HAS_CXX14_SIZED_DEALLOCATION				// N3778	__cpp_sized_deallocation				サイズ付きデアロケーション
#define HAMON_HAS_CXX14_DIGIT_SEPARATORS				// N3781	none									数値リテラルの桁区切り文字
#define HAMON_HAS_CXX14_VARIABLE_TEMPLATES				// N3651	__cpp_variable_templates				変数テンプレート
#define HAMON_HAS_CXX14_CONSTEXPR						// N3652	__cpp_constexpr							constexprの制限緩和
#define HAMON_HAS_CXX14_AGGREGATE_NSDMI					// N3653	__cpp_aggregate_nsdmi					宣言時のメンバ初期化を持つ型の集成体初期化

// C++17
#define HAMON_HAS_CXX17_HEX_FLOAT						// P0245R1	__cpp_hex_float							浮動小数点数の16進数リテラル
#define HAMON_HAS_CXX17_U8_CHARACTER_LITERALS			// N4267	none									UTF-8文字リテラル
#define HAMON_HAS_CXX17_INLINE_VARIABLES				// P0386R2	__cpp_inline_variables					インライン変数
#define HAMON_HAS_CXX17_ALIGNED_NEW						// P0035R4	__cpp_aligned_new						アライメント指定new
#define HAMON_HAS_CXX17_GUARANTEED_COPY_ELISION			// P0135R1	__cpp_guaranteed_copy_elision			値のコピー省略を保証
#define HAMON_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE			// P0012R1	__cpp_noexcept_function_type			例外仕様を型システムの一部にする
#define HAMON_HAS_CXX17_EXPRESSION_EVALUATION_ORDER		// P0145R3	none									厳密な式の評価順
#define HAMON_HAS_CXX17_FOLD_EXPRESSIONS				// N4295	__cpp_fold_expressions					畳み込み式
#define HAMON_HAS_CXX17_CAPTURE_STAR_THIS				// P0018R3	__cpp_capture_star_this					ラムダ式での*thisのコピーキャプチャ
#define HAMON_HAS_CXX17_CONSTEXPR_LAMBDA				// P0170R1	__cpp_constexpr							constexprラムダ
#define HAMON_HAS_CXX17_IF_CONSTEXPR					// P0292R2	__cpp_if_constexpr						if constexpr文
#define HAMON_HAS_CXX17_SELECTION_WITH_INIT				// P0305R1	none									if文とswitch文の条件式と初期化を分離
#define HAMON_HAS_CXX17_RANGE_BASED_FOR					// P0184R0	__cpp_range_based_for					範囲for文の制限を緩和
#define HAMON_HAS_CXX17_STATIC_ASSERT					// N3928	__cpp_static_assert						メッセージなしのstatic_assert
#define HAMON_HAS_CXX17_AUTO_DEDUCTION_BRACED_INIT_LIST	// N3922	none									波括弧初期化の型推論の新規則
#define HAMON_HAS_CXX17_DEDUCTION_GUIDES				// P0091R3	__cpp_deduction_guides					クラステンプレートのテンプレート引数推論
#define HAMON_HAS_CXX17_NONTYPE_TEMPLATE_PARAMETER_AUTO	// P0127R2	__cpp_nontype_template_parameter_auto	非型テンプレート引数のauto宣言
#define HAMON_HAS_CXX17_NAMESPACE_ATTRIBUTES			// N4266	__cpp_namespace_attributes				名前空間に属性の付加を許可
#define HAMON_HAS_CXX17_ENUMERATOR_ATTRIBUTES			// N4266	__cpp_enumerator_attributes				列挙子に属性の付加を許可
#define HAMON_HAS_CXX17_NESTED_NAMESPACE_DEFINITIONS	// N4230	none									入れ子名前空間の定義
#define HAMON_HAS_CXX17_INHERITING_CONSTRUCTORS			// P0136R1	__cpp_inheriting_constructors			継承コンストラクタの新仕様
#define HAMON_HAS_CXX17_VARIADIC_USING					// P0195R2	__cpp_variadic_using					using宣言でのパック展開
#define HAMON_HAS_CXX17_FALLTHROUGH						// P0188R1	__has_cpp_attribute(fallthrough)		[[fallthrough]]属性
#define HAMON_HAS_CXX17_NODISCARD						// P0189R1	__has_cpp_attribute(nodiscard)			[[nodiscard]]属性
#define HAMON_HAS_CXX17_MAYBE_UNUSED					// P0212R1	__has_cpp_attribute(maybe_unused)		[[maybe_unused]]属性
#define HAMON_HAS_CXX17_USING_ATTRIBUTE_NAMESPACES		// P0028R4	none									属性の名前空間指定に繰り返しをなくす
#define HAMON_HAS_CXX17_IGNORING_UNRECOGNIZED_ATTRIBUTES// P0283R2	none									不明な属性を無視する
#define HAMON_HAS_CXX17_STRUCTURED_BINDINGS				// P0217R3	__cpp_structured_bindings				構造化束縛
#define HAMON_HAS_CXX17_AGGREGATE_BASES					// P0017R1	__cpp_aggregate_bases					集成体初期化の波カッコを省略
#define HAMON_HAS_CXX17_INIT_ENUM_CLASS					// P0138R2	none									enum class変数の初期値として整数を指定する際の規則を調整
#define HAMON_HAS_CXX17_TEMPLATE_TEMPLATE_TYPENAME		// N4051	none									テンプレートテンプレートパラメータにtypenameを許可
#define HAMON_HAS_CXX17_NONTYPE_TEMPLATE_ARGS			// N4268	__cpp_nontype_template_args				非型テンプレートパラメータの定数式を評価する
#define HAMON_HAS_CXX17_TEMPLATE_TEMPLATE_ARGS			// P0522R0	__cpp_template_template_args			テンプレートテンプレート引数のマッチングにおいて、互換性のあるテンプレートを除外
#define HAMON_HAS_CXX17_EXCEPTION_SPECIFICATIONS		// P0003R5	none									非推奨だった例外仕様を削除
#define HAMON_HAS_CXX17_HAS_INCLUDE						// P0061R1	__has_include							プリプロセッサでの条件式__has_include
// P0398R0	Explicit default constructors and copy-list-initialization						none
// P0134R0	Introducing a name for brace-or-equal-initializers for non-static data members	none

// C++20
// __cpp_impl_coroutine >= 201902
#define HAMON_HAS_CXX20_COROUTINES							// P0912R5	Coroutines(for the use of standard library implementors)

// __cpp_concepts >= 201907
#define HAMON_HAS_CXX20_CONCEPTS							// P0734R0	Concepts
// P1084R2	Today's return-type-requirement s Are Insufcient
// P1452R2	On the non-uniform semantics of return-type-requirements
// P0857R0	Wording for "functionality gaps in constraints"
// P1616R1	Using unconstrained template template parameters with constrained templates

// __cpp_constexpr_in_decltype >= 201711
#define HAMON_HAS_CXX20_CONSTEXPR_IN_DECLTYPE				// P0859R0	Less eager instantiation of constexpr functions

// __cpp_generic_lambdas >= 201707
#define HAMON_HAS_CXX20_GENERIC_LAMBDAS						// P0428R2	ジェネリックラムダのテンプレート構文

// __cpp_init_captures >= 201803
#define HAMON_HAS_CXX20_INIT_CAPTURES						// P0780R2	Allow pack expansion in lambda init-capture

// __cpp_impl_destroying_delete >= 201806
#define HAMON_HAS_CXX20_DESTROYING_DELETE					// P0722R3	std::destroying_delete

// __cpp_char8_t >= 201811
#define HAMON_HAS_CXX20_CHAR8_T								// P0482R6	char8_t

// __cpp_constexpr_dynamic_alloc >= 201907
#define HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC				// P0784R7	constexpr container operations

// __cpp_impl_three_way_comparison >= 201907
#define HAMON_HAS_CXX20_THREE_WAY_COMPARISON				// P0515R3	三方比較演算子 (operator<=>)
#define HAMON_HAS_CXX20_THREE_WAY_COMPARISON_NE_EQ_OP		// P1185R2 <=> != ==
#define HAMON_HAS_CXX20_SYNTHESIZING_THREE_WAY_COMPARISON	// P1186R3 Synthesizing three-way comparison for specified comparison category
// P1630R1 Spaceship needs a tune-up
// P0905R1 Symmetry for spaceship
#define HAMON_HAS_CXX20_DEFAULTING_COMPARISON_BY_VALUE		// P1946R0 Allow defaulting comparisons by value
#define HAMON_HAS_CXX20_REMOVE_WEAK_EQUALITY_STRONG_EQUALITY	// P1959R0 Remove std::weak_equality and std::strong_equality
#define HAMON_HAS_CXX20_CONSISTENCY_IMPROVEMENTS_FOR_COMPARISONS	// P1120R0 Consistency improvements for comparisons

// __cpp_consteval >= 201811
#define HAMON_HAS_CXX20_CONSTEVAL							// P1073R3	Immediate functions (consteval)

// __cpp_constexpr >= 201907
#define HAMON_HAS_CXX20_CONSTEXPR_VIRTUAL_FUNCTION			// P1064R0	constexpr virtual function
#define HAMON_HAS_CXX20_CONSTEXPR_TRY_CATCH					// P1002R1	constexpr関数内でtry-catchブロックを書けるようにする
#define HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_CAST				// P1327R1	constexpr dynamic_cast and polymorphic typeid
#define HAMON_HAS_CXX20_CONSTEXPR_UNION						// P1330R0	Changing the active member of a union inside constexpr
#define HAMON_HAS_CXX20_CONSTEXPR_TRIVIAL_DEFAULT_INIT		// P1331R2	Trivial default initialization in constexpr functions
// __cpp_constexpr >= 201907
#define HAMON_HAS_CXX20_CONSTEXPR_ASM						// P1668R1	Unevaluated asm-declaration in constexpr functions

// __cpp_deduction_guides >= 201907
#define HAMON_HAS_CXX20_DEDUCTION_GUIDES					// P1814R0,P1816R0,P2082R1,P1021R4
#define HAMON_HAS_CXX20_CTAD_ALIAS_TEMPLATE					// P1814R0	Class template argument deduction for alias templates
#define HAMON_HAS_CXX20_CTAD_AGGREGATE						// P1816R0, P2082R1	Class template argument deduction for aggregates

// __cpp_conditional_explicit >= 201806
#define HAMON_HAS_CXX20_CONDITIONAL_EXPLICIT				// P0892R2	explicit(bool)

// __cpp_constinit >= 201907
#define HAMON_HAS_CXX20_CONSTINIT							// P1143R2	constinit

// __cpp_using_enum >= 201907
#define HAMON_HAS_CXX20_USING_ENUM							// P1099R5	using enum

// __cpp_designated_initializers >= 201707
#define HAMON_HAS_CXX20_DESIGNATED_INITIALIZERS				// P0329R4	指示付き初期化子

// __cpp_aggregate_paren_init >= 201902
#define HAMON_HAS_CXX20_AGGREGATE_PAREN_INIT				// P0960R3	Aggregate initialization from a parenthesized list

// __has_cpp_attribute(likely) >= 201803
#define HAMON_HAS_CXX20_LIKELY								// P0479R5	Attributes [[likely]]
// __has_cpp_attribute(unlikely) >= 201803
#define HAMON_HAS_CXX20_UNLIKELY							// P0479R5	Attributes [[unlikely]]

// __has_cpp_attribute(nodiscard) >= 201907
#define HAMON_HAS_CXX20_NODISCARD_WITH_MESSAGE				// P1301R4	[[nodiscard("with reason")]]
#define HAMON_HAS_CXX20_NODISCARD_CTOR						// P1771R1	[[nodiscard]] for constructors

// __has_cpp_attribute(no_unique_address) >= 201803
#define HAMON_HAS_CXX20_NO_UNIQUE_ADDRESS					// P0840R2	Language support for empty objects ([[no_unique_address]])

// __cpp_modules >= 201907
#define HAMON_HAS_CXX20_MODULES								// P1103R3	Modules
// P1811R0	Relaxing redefinition restrictions for re-exportation robustness
// P1766R1	Mitigating minor modules maladies 
// P1874R1	Dynamic Initialization Order of Non-Local Variables in Modules
// P1703R1	Recognizing Header Unit Imports Requires Full Preprocessing

// __cpp_nontype_template_args >= 201911
#define HAMON_HAS_CXX20_NONTYPE_TEMPLATE_PARAMETER_FLOAT	// P1907R1	Class types and floating-point types in non-type template parameters

#define HAMON_HAS_CXX20_CAPTURE_COPY_THIS					// P0409R2	ラムダ式のキャプチャとして[=, this]を許可する
#define HAMON_HAS_CXX20_VA_OPT								// P0306R4,P1042R1	__VA_OPT__
#define HAMON_HAS_CXX20_BITFIELD_DEFAULT_MEMBER_INITIALIZER	// P0683R1	ビットフィールドのメンバ変数初期化
#define HAMON_HAS_CXX20_INITIALIZER_LIST_CTAD				// P0702R1	Initializer list constructors in class template argument deduction
#define HAMON_HAS_CXX20_CONST_QUALIFIED_POINTERS_TO_MEMBERS	// P0704R1	const修飾されたメンバポインタの制限を修正
#define HAMON_HAS_CXX20_LAMBDAS_IN_UNEVALUATED_CONTEXTS		// P0315R4	Lambdas in unevaluated contexts
#define HAMON_HAS_CXX20_SIMPLIFYING_IMPLICIT_LAMBDA_CAPTURE	// P0588R1	Simplifying implicit lambda capture
#define HAMON_HAS_CXX20_RANGE_BASED_FOR_INITIALIZER			// P0614R1	初期化式をともなう範囲for文
#define HAMON_HAS_CXX20_DEFAULT_CONSTRUCTIBLE_AND_ASSIGNABLE_STATELESS_LAMBDAS	// P0624R2	Default constructible and assignable stateless lambdas
#define HAMON_HAS_CXX20_CONST_MISMATCH_WITH_DEFAULTED_COPY_CONSTRUCTOR	// P0641R2	const mismatch with defaulted copy constructor
#define HAMON_HAS_CXX20_ACCESS_CHECKING_ON_SPECIALIZATIONS		// P0692R1	Access checking on specializations
#define HAMON_HAS_CXX20_ADL_AND_FUNCTION_TEMPLATES			// P0846R0	ADL and function templates that are not visible
#define HAMON_HAS_CXX20_OPTIONAL_TYPENAME					// P0634R3	Make typename more optional
#define HAMON_HAS_CXX20_CONDITIONALLY_TRIVIAL_SPECIAL_MEMBER_FUNCTIONS	// P0848R3	Conditionally trivial special member functions 
#define HAMON_HAS_CXX20_RELAXING_STRUCTURED_BINDINGS		// P0961R1	Relaxing the structured bindings customization point finding rules
#define HAMON_HAS_CXX20_RELAXING_RANGE_FOR					// P0962R1	Relaxing the range-for loop customization point finding rules
#define HAMON_HAS_CXX20_STRUCTURED_BINDINGS_TO_ACCESSIBLE_MEMBERS	// P0969R0	Allow structured bindings to accessible members
#define HAMON_HAS_CXX20_NONTYPE_TEMPLATE_PARAMETER_CLASS	// P0732R2	Class Types in Non-Type Template Parameters
#define HAMON_HAS_CXX20_DEPRECATE_IMPLICIT_CAPTURE_COPY_THIS	// P0806R2	[=]によるthisの暗黙のキャプチャを非推奨化
#define HAMON_HAS_CXX20_FEATURE_TEST_MACROS					// P0941R2	Feature test macros
#define HAMON_HAS_CXX20_PROHIBIT_AGGREGATES_WITH_USER_DECLARED_CONSTRUCTORS	// P1008R1	Prohibit aggregates with user-declared constructors
#define HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED				// P0595R2	std::is_constant_evaluated
#define HAMON_HAS_CXX20_NESTED_INLINE_NAMESPACES			// P1094R2	Nested inline namespaces
#define HAMON_HAS_CXX20_ABBREVIATED_FUNCTION_TEMPLATE		// P1141R2	制約付きの宣言のためのもうひとつの方法
#define HAMON_HAS_CXX20_TWOS_COMPLEMENT_SIGNED_INTEGERS		// P1236R1	Signed integers are two's complement
#define HAMON_HAS_CXX20_ARRAY_SIZE_DEDUCTION_NEW			// P1009R2	Array size deduction in new-expressions
#define HAMON_HAS_CXX20_STRONGER_UNICODE_REQUIREMENTS		// P1041R4,P1139R2	Stronger Unicode requirements
#define HAMON_HAS_CXX20_EXCEPTION_SPEC_DEFAULTED_FUNCTION	// P1286R2	Explicitly defaulted functions with different exception specifications
#define HAMON_HAS_CXX20_STRUCTURED_BINDING_EXTENSIONS		// P1091R3,P1381R1	Structured binding extensions
#define HAMON_HAS_CXX20_CONVERSIONS_TO_UNBOUNDED_ARRAY		// P0388R4	Permit conversions to arrays of unknown bound
#define HAMON_HAS_CXX20_DEPRECATE_VOLATILE					// P1152R4	Deprecating some uses of volatile
#define HAMON_HAS_CXX20_DEPRECATE_COMMA_IN_SUBSCRIPTING_EXPRESSIONS	// P1161R3		Deprecate a[b,c]
#define HAMON_HAS_CXX20_IMPLICIT_MOVE						// P1825R0	Implicit move for more local objects and rvalue references
#define HAMON_HAS_CXX20_PSEUDO_DESTRUCTOR					// P0593R6 Pseudo-destructors end object lifetimes
#define HAMON_HAS_CXX20_POINTER_TO_BOOL_CONVERTING			// P1957R2 Converting from T* to bool should be considered narrowing
#define HAMON_HAS_CXX20_CONSISTENT_DEFAULTED_COMPARISONS	// P2085R0 Consistent defaulted comparisons

// C++20 libary features
// P0528R3	Atomic Compare-and-Exchange with Padding Bits
// P0466R5	Layout-Compatibility and Pointer-Interconvertibility Traits

// C++23

#define HAMON_HAS_CXX23_											// P1787R6	DR: Declarations and where to find them
#define HAMON_HAS_CXX23_											// P2246R1	Character encoding of diagnostic text
#define HAMON_HAS_CXX23_											// CWG2397	auto specifier for pointers and references to arrays
#define HAMON_HAS_CXX23_											// CWG2481	Cv-qualification of temporary to which a reference is bound
#define HAMON_HAS_CXX23_DE_DEPRECATE_VOLATILE						// P2327R1	De-deprecating volatile compound operations
#define HAMON_HAS_CXX23_											// P2736R2	Referencing The Unicode Standard

#define HAMON_HAS_CXX23_SIZE_T_SUFFIX								// P0330R8	Literal Suffix for (signed) size_t										__cpp_size_t_suffix >= 202011L
#define HAMON_HAS_CXX23_LAMBDA_WITHOUT_PAREN						// P1102R2	Down with ()!
#define HAMON_HAS_CXX23_IF_CONSTEVAL								// P1938R3	if consteval															__cpp_if_consteval >= 202106L
#define HAMON_HAS_CXX23_NARROWING_CONVERSIONS_TO_BOOL				// P1401R5	Narrowing contextual conversions to bool
#define HAMON_HAS_CXX23_TRIMMING_WHITESPACES_BEFORE_LINE_SPLICING	// P2223R2	Trimming whitespaces before line splicing
#define HAMON_HAS_CXX23_DECLARATION_ORDER_LAYOUT					// P1847R4	Make declaration order layout mandated
#define HAMON_HAS_CXX23_MIXED_STRING_LITERAL_CONCATENATION			// P2201R1	Mixed string literal concatenation
#define HAMON_HAS_CXX23_EXPLICIT_THIS_PARAMETER						// P0847R7, P2797R0, CWG2586	Deducing this										__cpp_explicit_this_parameter >= 202110L
#define HAMON_HAS_CXX23_AUTO_CAST									// P0849R8	auto(x): decay-copy in the language										__cpp_auto_cast >= 202110L
#define HAMON_HAS_CXX23_LAMBDA_TRAILING_RETURN_TYPE_SCOPE			// P2036R3, P2579R0	Change scope of lambda trailing-return-type
#define HAMON_HAS_CXX23_ELIFDEF										// P2334R1	Add support for preprocessing directives elifdef and elifndef
#define HAMON_HAS_CXX23_CONSTEXPR_NON_LITERAL_VARIABLES				// P2242R3	Non-literal variables (and labels and gotos) in constexpr functions		__cpp_constexpr >= 202110L
#define HAMON_HAS_CXX23_CHARACTER_LITERALS_IN_PREPROCESSOR			// P2316R2	Consistent character literal encoding
#define HAMON_HAS_CXX23_CHARACTER_SETS_AND_ENCODINGS				// P2314R4	Character sets and encodings
#define HAMON_HAS_CXX23_ALIAS_DECLARATION_IN_INIT_STATEMENT			// P2360R0	Extend init-statement to allow alias-declaration
#define HAMON_HAS_CXX23_MULTIDIMENSIONAL_SUBSCRIPT					// P2128R6, CWG2507	Multidimensional subscript operator								__cpp_multidimensional_subscript >= 202110L
#define HAMON_HAS_CXX23_ATTRIBUTES_ON_LAMBDAS						// P2173R1	Attributes on lambda-expressions
#define HAMON_HAS_CXX23_WARNING										// P2437R1	Support for #warning
#define HAMON_HAS_CXX23_NON_ENCODABLE_WIDE_CHARACTER_LITERALS		// P2362R3	Remove non-encodable wide character literals and multicharacter wide character literals
#define HAMON_HAS_CXX23_LABEL_AT_END_OF_COMPOUND_STATEMENT			// P2324R2	Labels at the end of compound statements
#define HAMON_HAS_CXX23_DELIMITED_ESCAPE_SEQUENCES					// P2290R3	Delimited escape sequences
#define HAMON_HAS_CXX23_NAMED_CHARACTER_ESCAPES						// P2071R2	Named universal character escapes										__cpp_named_character_escapes >= 202207L
#define HAMON_HAS_CXX23_RELAXING_CONSTEXPR							// P2448R2	Relaxing some constexpr restrictions									__cpp_constexpr >= 202207L
#define HAMON_HAS_CXX23_IMPLICIT_MOVE								// P2266R3	Simpler implicit move													__cpp_implicit_move >= 202207L
#define HAMON_HAS_CXX23_STATIC_CALL_OPERATOR						// P1169R4	static operator()														__cpp_static_call_operator >= 202207L
#define HAMON_HAS_CXX23_INHERITED_CONSTRUCTOR_CTAD					// P2582R1	Wording for class template argument deduction from inherited constructors
#define HAMON_HAS_CXX23_ASSUME										// P1774R8	Portable assumptions
#define HAMON_HAS_CXX23_UTF8_SOURCE_FILE_ENCODING					// P2295R6	Support for UTF-8 as a portable source file encoding
#define HAMON_HAS_CXX23_STATIC_SUBSCRIPT_OPERATOR					// P2589R1	static operator[]														__cpp_multidimensional_subscript >= 202211L
#define HAMON_HAS_CXX23_STATIC_VARIABLE_IN_CONSTEXPR_FUNCTION		// P2647R1	Permitting static constexpr variables in constexpr functions			__cpp_constexpr >= 202211L
#define HAMON_HAS_CXX23_RANGE_BASED_FOR								// P2718R0	Wording for P2644R1 Fix for Range-based for Loop						__cpp_range_based_for >= 202211L
#define HAMON_HAS_CXX23_											// P2615R1	DR20: Meaningful exports
#define HAMON_HAS_CXX23_CONSTEVAL_PROPAGATE_UP						// P2564R3	DR20: consteval needs to propagate up									__cpp_consteval >= 202211L
#define HAMON_HAS_CXX23_IDENTIFIER_SYNTAX_UAX31						// P1949R7	DR98: C++ Identifier Syntax using Unicode Standard Annex 31
#define HAMON_HAS_CXX23_DUPLICATE_ATTRIBUTES						// P2156R1	DR11: Allow Duplicate Attributes
#define HAMON_HAS_CXX23_											// P2493R0	DR20: Missing feature test macros for C++20 core papers					__cpp_concepts >= 202002L
#define HAMON_HAS_CXX23_											// P2460R2	DR98: Relax requirements on wchar_t to match existing practices
#define HAMON_HAS_CXX23_UNKNOWN_REFERENCE_IN_CONSTEXPR				// P2280R4	DR11: Using unknown references in constant expressions
#define HAMON_HAS_CXX23_EQUALITY_OPERATOR							// P2468R2	DR20: The Equality Operator You Are Looking For
#define HAMON_HAS_CXX23_CHAR8_T_COMPATIBILITY						// P2513R4	DR20: char8_t Compatibility and Portability Fix							__cpp_char8_t >= 202207L
#define HAMON_HAS_CXX23_ALLOW_STATIC_ASSERT_FALSE					// CWG2518	DR98/11: Clarify reporting of diagnostic directives and allow static_assert of non-value-dependent expressions in a template context

// C++23 libary features
#define HAMON_HAS_CXX23_											// P2186R2	Removing Garbage Collection Support
#define HAMON_HAS_CXX23_											// P2255R2	A type trait to detect reference binding to temporary
#define HAMON_HAS_CXX23_LIB_EXTENDED_FLOATING_POINT_TYPES			// P1467R9	Extended floating-point types and standard names
#define HAMON_HAS_CXX23_											// P2590R2	Explicit lifetime management

// C++26
#define HAMON_HAS_CXX26_											// P2621R3	DR98: UB? In my Lexer?
#define HAMON_HAS_CXX26_											// P1854R4	DR98: Making non-encodable string literals ill-formed
#define HAMON_HAS_CXX26_											// P2361R6	Unevaluated strings
#define HAMON_HAS_CXX26_											// P2558R2	Add @, $, and ` to the basic character set
#define HAMON_HAS_CXX26_											// P2738R1	constexpr cast from void*: towards constexpr type-erasure				__cpp_constexpr >= 202306L
#define HAMON_HAS_CXX26_											// P2552R3	DR20: On the ignorability of standard attributes
#define HAMON_HAS_CXX26_											// P2752R3	DR11: Static storage for braced initializers
#define HAMON_HAS_CXX26_											// P2741R3	user-generated static_assert messages									__cpp_static_assert >= 202306L
#define HAMON_HAS_CXX26_PLACEHOLDER_VARIABLES						// P2169R4	A nice placeholder with no name											__cpp_placeholder_variables >= 202306L
#define HAMON_HAS_CXX26_PACK_INDEXING								// P2662R3	Pack Indexing															__cpp_pack_indexing >= 202311L
#define HAMON_HAS_CXX26_											// P2864R2	Remove Deprecated Arithmetic Conversion on Enumerations From C++26
#define HAMON_HAS_CXX26_											// P2308R1	DR11/20: Template parameter initialization
#define HAMON_HAS_CXX26_											// P2748R5	Disallow Binding a Returned Glvalue to a Temporary
#define HAMON_HAS_CXX26_											// P0609R3	Attributes for Structured Bindings										__cpp_structured_bindings >= 202403L
#define HAMON_HAS_CXX26_											// P2795R5	Erroneous behaviour for uninitialized reads
#define HAMON_HAS_CXX26_DELETED_FUNCTION							// P2573R2	= delete("should have a reason");										__cpp_deleted_function >= 202403L
#define HAMON_HAS_CXX26_VARIADIC_FRIEND								// P2893R3	Variadic friends														__cpp_variadic_friend >= 202403L
#define HAMON_HAS_CXX26_											// P3106R1	DR98: Clarifying rules for brace elision in aggregate initialization
#define HAMON_HAS_CXX26_											// P3034R1	DR20: Module Declarations Shouldn’t be Macros
#define HAMON_HAS_CXX26_											// P2809R3	DR11: Trivial infinite loops are not Undefined Behavior
#define HAMON_HAS_CXX26_											// P2747R2	constexpr placement new													__cpp_constexpr >= 202406L
#define HAMON_HAS_CXX26_											// P0963R3	Structured binding declaration as a condition							__cpp_structured_bindings >= 202406L
#define HAMON_HAS_CXX26_											// P2963R3	Ordering of constraints involving fold expressions						__cpp_fold_expressions >= 202406L
#define HAMON_HAS_CXX26_											// P3144R2	Deleting a Pointer to an Incomplete Type Should be Ill-formed

#endif

#endif // HAMON_CONFIG_COMPILER_MSVC_HPP
