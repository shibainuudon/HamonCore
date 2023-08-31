/**
 *	@file	unit_test_config_cxx23.cpp
 *
 *	@brief	
 */

#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include <iostream>

namespace hamon_config_cxx23_test
{

#if defined(HAMON_HAS_CXX23_SIZE_T_SUFFIX)

static_assert(std::is_same<std::ptrdiff_t, decltype(0z)>::value, "");
static_assert(std::is_same<std::ptrdiff_t, decltype(0Z)>::value, "");
static_assert(std::is_same<std::size_t, decltype(0uz)>::value, "");
static_assert(std::is_same<std::size_t, decltype(0uZ)>::value, "");
static_assert(std::is_same<std::size_t, decltype(0Uz)>::value, "");
static_assert(std::is_same<std::size_t, decltype(0UZ)>::value, "");
static_assert(std::is_same<std::size_t, decltype(0zu)>::value, "");
static_assert(std::is_same<std::size_t, decltype(0zU)>::value, "");
static_assert(std::is_same<std::size_t, decltype(0Zu)>::value, "");
static_assert(std::is_same<std::size_t, decltype(0ZU)>::value, "");

#endif

#if defined(HAMON_HAS_CXX23_LAMBDA_WITHOUT_PAREN)
namespace lambda_without_paren_test
{

GTEST_TEST(ConfigTest, Cxx23LambdaWithoutParenTest)
{
	{
		std::string s1 = "abc";
		auto withParen = [s1 = std::move(s1)] () {
			std::cout << s1 << '\n';
		};

		std::string s2 = "abc";
		auto noSean = [s2 = std::move(s2)] { // Note no syntax error.
			std::cout << s2 << '\n';
		};
	}
	{
		std::string s1 = "abc";
		auto withParen = [s1 = std::move(s1)] () mutable {
			s1 += "d";
			std::cout << s1 << '\n';
		};

		std::string s2 = "abc";
		auto noSean = [s2 = std::move(s2)] mutable { // Currently a syntax error.
			s2 += "d";
			std::cout << s2 << '\n';
		};
	}
}

}	// namespace lambda_without_paren_test
#endif

#if defined(HAMON_HAS_CXX23_IF_CONSTEVAL)
namespace if_consteval_test
{

consteval int f(int i) { return i; }

constexpr int g(int i) {
	if consteval {
		return f(i) + 1; // ok: immediate function context
	} else {
		return 42;
	}
}

consteval int h(int i) {
	return f(i) + 1; // ok: immediate function context
}

}	// namespace if_consteval_test
#endif

#if !defined(HAMON_HAS_CXX23_IDENTIFIER_SYNTAX_UAX31)
namespace identifier_syntax_uax31_test
{

// gccだと #if 0 で囲んでもコンパイルエラーになるのでテストできない

////bool 👷 = true; //  Construction Worker
////bool 👷‍♀ = false; // Woman Construction Worker ({Construction Worker}{ZWJ}{Female Sign})
//
////int ⏰ = 0; //not valid
//int 🕐 = 0;
//
////int ☠ = 0; //not valid
//int 💀 = 0;
//
////int ✋ = 0; //not valid
//int 👊 = 0;
//
////int ✈ = 0; //not valid
//int 🚀 = 0;
//
////int ☹ = 0; //not valid
//int 😀 = 0;

}	// namespace identifier_syntax_uax31_test
#endif

#if defined(HAMON_HAS_CXX23_DUPLICATE_ATTRIBUTES)
namespace duplicate_attributes_test
{

#if defined(HAMON_HAS_CXX11_NORETURN)
[[noreturn, noreturn]] void func1();
#endif
#if defined(HAMON_HAS_CXX14_DEPRECATED)
[[deprecated, deprecated]] void func2();
#endif

}	// namespace duplicate_attributes_test
#endif

#if defined(HAMON_HAS_CXX23_NARROWING_CONVERSIONS_TO_BOOL)
namespace narrowing_conversions_to_bool_test
{

enum Flags { Write = 1, Read = 2, Exec = 4 };

template <Flags flags>
int f() {
	if constexpr (flags & Flags::Exec) // fails to compile due to narrowing
		return 0;
	else
		return 1;
}

int test() {
	return f<Flags::Exec>(); // when instantiated like this
}

template <std::size_t N>
class Array
{
	static_assert(N, "no 0-size Arrays");
	// ...
};

Array<16> a; // fails to compile in pure C++

}	// namespace narrowing_conversions_to_bool_test
#endif

#if defined(HAMON_HAS_CXX23_TRIMMING_WHITESPACES_BEFORE_LINE_SPLICING)
namespace trimming_whitespaces_before_line_splicing_test
{

// gcc12までだと、multi-line comment があると警告(エラー)になってしまう
// * pragma で抑制できない
// * #if 0 で囲ってもダメ
// なのでテストできない。
// また、テストの内容をコメントで残すこともできない。
// どんなテストをしようとしていたかは以下を参照
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2021/p2223r2.pdf

}	// namespace trimming_whitespaces_before_line_splicing_test
#endif

#if !defined(HAMON_HAS_CXX23_MIXED_STRING_LITERAL_CONCATENATION)
namespace mixed_string_literal_concatenation_test
{

GTEST_TEST(ConfigTest, Cxx23MixedStringLiteralConcatenationTest)
{
	{ auto a = L"" u""; }
	{ auto a = L"" u8""; }
	{ auto a = L"" U""; }

	{ auto a = u8"" L""; }
	{ auto a = u8"" u""; }
	{ auto a = u8"" U""; }

	{ auto a = u"" L""; }
	{ auto a = u"" u8""; }
	{ auto a = u"" U""; }

	{ auto a = U"" L""; }
	{ auto a = U"" u""; }
	{ auto a = U"" u8""; }
}

}	// namespace mixed_string_literal_concatenation_test
#endif

#if defined(HAMON_HAS_CXX23_LAMBDA_TRAILING_RETURN_TYPE_SCOPE)
namespace lambda_trailing_return_type_scope_test
{

GTEST_TEST(ConfigTest, Cxx23LambdaTrailingReturnTypeScopeTest)
{
	auto counter = [i=0]() mutable -> decltype(i) {  // ok: returns int
		return i++;
	};
	auto n = counter();
	static_assert(std::is_same<decltype(n), int>::value, "");
}

}	// namespace lambda_trailing_return_type_scope_test
#endif

#if defined(HAMON_HAS_CXX23_IMPLICIT_MOVE)
namespace implicit_move_test
{

struct Widget {
	Widget(Widget&&){}
};

struct RRefTaker {
	RRefTaker(Widget&&){}
};

Widget one(Widget w) {
	return w;  // OK since C++11
}

RRefTaker two(Widget w) {
	return w;  // OK since C++11 + CWG1579
}

RRefTaker three(Widget&& w) {
	return w;  // OK since C++20 because P0527
}

Widget&& four(Widget&& w) {
	return w;  // Error
}

struct Mutt {
	int i;
	operator int*() && { return &i; }
};

struct Jeff {
	int i;
	operator int&() && { return i; }
};

int* five(Mutt x) {
	return x;  // OK since C++20 because P1155
}

int& six(Jeff x) {
	return x;  // Error
}

template<class T>
T&& seven(T&& x) { return x; }

void test_seven(Widget w) {
	Widget& r = seven(w);               // OK
	Widget&& rr = seven(std::move(w));  // Error
	(void)r;
	(void)rr;
}

}	// namespace implicit_move_test
#endif

#if defined(HAMON_HAS_CXX23_MULTIDIMENSIONAL_SUBSCRIPT)
namespace multidimensional_subscript_test
{

struct MDArray
{
	int& operator[](std::size_t);
	int& operator[](std::size_t, std::size_t);
	int& operator[](std::size_t, std::size_t, std::size_t);
};

}	// namespace multidimensional_subscript_test
#endif

#if defined(HAMON_HAS_CXX23_CONSTEXPR_NON_LITERAL_VARIABLES)
namespace constexpr_non_literal_variables_test
{

template<typename T> constexpr bool f() {
	if (std::is_constant_evaluated()) {
		// ...
		return true;
	} else {
		T t;
		// ...
		return true;
	}
}
struct nonliteral { nonliteral(); };
static_assert(f<nonliteral>());

}	// namespace constexpr_non_literal_variables_test
#endif

#if defined(HAMON_HAS_CXX23_ELIFDEF)

//#ifdef M1
//#elifdef M2
//#elifndef M3
//#endif

#endif

#if defined(HAMON_HAS_CXX23_ALIAS_DECLARATION_IN_INIT_STATEMENT)
namespace alias_declaration_in_init_statement_test
{

GTEST_TEST(ConfigTest, Cxx23AliasDeclarationInInitStatementTest)
{
	std::vector<int> v;
	for (using T = int; T e : v) { (void)e; }
}

}	// namespace alias_declaration_in_init_statement_test
#endif

#if defined(HAMON_HAS_CXX23_DECAY_COPY)
namespace decay_copy_test
{

template <typename Container>
void pop_front_alike(Container& x) {
	std::erase(x.begin(), x.end(), auto(x.front()));
	std::erase(x.begin(), x.end(), auto{x.front()});
}

}	// namespace decay_copy_test
#endif

#if defined(HAMON_HAS_CXX23_LABEL_AT_END_OF_COMPOUND_STATEMENT)
namespace label_at_end_of_compound_statement_test
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wunused-label")
HAMON_WARNING_DISABLE_CLANG("-Wunused-but-set-variable")
HAMON_WARNING_DISABLE_GCC("-Wunused-label")
HAMON_WARNING_DISABLE_GCC("-Wunused-but-set-variable")

void foo(void)
{
first: // allowed in C++, now also allowed in C
	int x;
second: // allowed in both C++ and C
	x = 1;
last: // not allowed in C++, but now allowed in C
}

HAMON_WARNING_POP()

}	// namespace label_at_end_of_compound_statement_test
#endif

#if defined(HAMON_HAS_CXX23_ATTRIBUTES_ON_LAMBDAS)
namespace attributes_on_lambdas_test
{

GTEST_TEST(ConfigTest, Cxx23AttributesOnLambdasTest)
{
	auto lm = [][[nodiscard]]()->int { return 42; };
	EXPECT_EQ(42, lm());
}

}	// namespace attributes_on_lambdas_test
#endif

#if defined(HAMON_HAS_CXX23_DE_DEPRECATE_VOLATILE)
namespace de_deprecate_volatile
{

struct ADC {
	volatile uint8_t CTRL;
	volatile uint8_t VALUE;
};

#define ADC_CTRL_ENABLE ( 1 << 3 )

void test(ADC* ADC1)
{
	ADC1->CTRL |= ADC_CTRL_ENABLE;
	ADC1->CTRL &= ~ADC_CTRL_ENABLE;
}

}	// namespace de_deprecate_volatile
#endif

#if defined(HAMON_HAS_CXX23_NAMED_CHARACTER_ESCAPES)
namespace named_character_escapes_test
{

GTEST_TEST(ConfigTest, Cxx23NamedCharacterEscapesTest)
{
	EXPECT_EQ(U'\u0100', U'\N{LATIN CAPITAL LETTER A WITH MACRON}');
	EXPECT_EQ(U'\u0300', U'\N{COMBINING GRAVE ACCENT}');
	EXPECT_EQ(U'\u200B', U'\N{ZERO WIDTH SPACE}');
}

}	// namespace named_character_escapes_test
#endif

#if defined(HAMON_HAS_CXX23_STATIC_CALL_OPERATOR)
namespace static_call_operator_test
{

struct less {
	static constexpr auto operator()(int i, int j) -> bool {
		return i < j;
	}
};

}	// namespace static_call_operator_test
#endif

#if defined(HAMON_HAS_CXX23_STATIC_SUBSCRIPT_OPERATOR)
namespace static_subscript_operator_test
{

struct MDArray
{
	static constexpr int& operator[](std::size_t);
	static constexpr int& operator[](std::size_t, std::size_t);
	static constexpr int& operator[](std::size_t, std::size_t, std::size_t);
};

}	// namespace static_subscript_operator_test
#endif

}	// namespace hamon_config_cxx23_test
