/**
 *	@file	unit_test_config_cxx23.cpp
 *
 *	@brief	
 */

#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

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

#if defined(HAMON_HAS_CXX23_DECLARATION_ORDER_LAYOUT)
namespace declaration_order_layout_test
{
struct S
{
protected:
	int a;
private:
	int b;
public:
	int c;

public:
	int* addressof_a() { return &a; }
	int* addressof_b() { return &b; }
	int* addressof_c() { return &c; }
};

GTEST_TEST(ConfigTest, Cxx23DeclarationOrderLayoutTest)
{
	S s;
	EXPECT_TRUE(s.addressof_a() < s.addressof_b());
	EXPECT_TRUE(s.addressof_b() < s.addressof_c());
}

}	// namespace declaration_order_layout_test
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

#if defined(HAMON_HAS_CXX23_EXPLICIT_THIS_PARAMETER)
namespace explicit_this_parameter_test
{
struct X
{
	int foo(this X&)       { return 1; }
	int foo(this X const&) { return 2; }
	int foo(this X&&)      { return 3; }
};

struct D : X
{
	template <typename Self>
	int bar(this Self&& self)
	{
		return std::forward<Self>(self).foo();
	}
};

GTEST_TEST(ConfigTest, Cxx23ExplicitThisParameterTest)
{
	{
		X x;
		X const& r = x;
		EXPECT_TRUE(x.foo() == 1);
		EXPECT_TRUE(r.foo() == 2);
		EXPECT_TRUE(std::move(x).foo() == 3);
	}
	{
		D d;
		D const& r = d;
		EXPECT_TRUE(d.bar() == 1);
		EXPECT_TRUE(r.bar() == 2);
		EXPECT_TRUE(std::move(d).bar() == 3);
	}
}

}	// namespace explicit_this_parameter_test
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

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_GCC("-Wreturn-local-addr")

int* five(Mutt x) {
	return x;  // OK since C++20 because P1155
}

int& six(Jeff x) {
	return x;  // Error
}

HAMON_WARNING_POP()

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

#if defined(HAMON_HAS_CXX23_CHARACTER_SETS_AND_ENCODINGS)
namespace character_sets_and_encodings_test
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4566)	// ユニバーサル文字名 '\u00F6' によって表示されている文字は、現在のコード ページ (932) で表示できません

GTEST_TEST(ConfigTest, Cxx23CharacterSetsAndEncodingsTest)
{
#define S(x) # x
	const char * s1 = S(Köppe);       // "Köppe"
	const char * s2 = S(K\u00f6ppe);  // "Köppe"
#undef S
	EXPECT_STREQ(s1, "Köppe");
	EXPECT_STREQ(s2, "Köppe");
}

HAMON_WARNING_POP()

}	// namespace character_sets_and_encodings_test
#endif

#if defined(HAMON_HAS_CXX23_CHARACTER_LITERALS_IN_PREPROCESSOR)
namespace character_literals_in_preprocessor_test
{

#if 'A' == '\x41'
#define CONSISTENT	1
#else
#define CONSISTENT	0
#endif

static_assert(CONSISTENT == 1, "");

#undef CONSISTENT

}	// namespace character_literals_in_preprocessor_test
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

#if defined(HAMON_HAS_CXX23_AUTO_CAST)
namespace auto_cast_test
{

template <typename Container>
void pop_front_alike(Container& x) {
	std::erase(x.begin(), x.end(), auto(x.front()));
	std::erase(x.begin(), x.end(), auto{x.front()});
}

}	// namespace auto_cast_test
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

#if defined(HAMON_HAS_CXX23_UNKNOWN_REFERENCE_IN_CONSTEXPR)
namespace unknown_reference_in_constexpr_test
{

template <class T, std::size_t N>
constexpr std::size_t size(const T (&)[N]) noexcept
{
	return N;
}

void check(int const (&param)[3])
{
	int local[] = {1, 2, 3};

	constexpr auto s0 = size(local); // ok
	constexpr auto s1 = size(param); // ng -> ok
	(void)s0;
	(void)s1;
}

}	// namespace unknown_reference_in_constexpr_test
#endif

#if defined(HAMON_HAS_CXX23_EQUALITY_OPERATOR)
namespace equality_operator_test
{

struct A {};
template<typename T> bool operator==(A, T) { return false; }  // #1
bool a1 = 0 == A();  // OK, calls reversed #1
template<typename T> bool operator!=(A, T) { return false; }
//bool a2 = 0 == A();  // error, #1 is not a rewrite target

struct B {
	bool operator==(const B&) { return false; }  // #2
};
struct C : B {
	C() {}
	C(B) {}
	bool operator!=(const B&) { return false; }  // #3
};
bool c1 = B() == C();  // OK, calls #2; reversed #2 is not a candidate because search for operator!= in C finds #3
//bool c2 = C() == B();  // error, ambiguous between #2 found when searching C and reversed #2 found when searching B

//struct D {};
//template <typename T>
//bool operator==(D, T) { return false; } // #4
//inline namespace N {
//template <typename T>
//bool operator!=(D, T) { return false; } // #5
//}
//bool d1 = 0 == D(); // OK, calls reversed #4; #5 does not forbid #4 as a rewrite target

}	// namespace equality_operator_test
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

#if defined(HAMON_HAS_CXX23_WARNING)
namespace warning_test
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-W#warnings")
HAMON_WARNING_DISABLE_GCC("-Wcpp")

#warning This library currently has no thread support.

HAMON_WARNING_POP()

}	// namespace warning_test
#endif

#if 0//!defined(HAMON_HAS_CXX23_NON_ENCODABLE_WIDE_CHARACTER_LITERALS)
namespace non_encodable_wide_character_literals_test
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4066)	// ワイド文字定数の文字列は無視されます。

wchar_t a = L'🤦';  // \U0001f926
wchar_t b = L'ab';  // multi character literal
wchar_t c = L'é́';   // \u0065\u0301

HAMON_WARNING_POP()

}	// namespace non_encodable_wide_character_literals_test
#endif

#if defined(HAMON_HAS_CXX23_DELIMITED_ESCAPE_SEQUENCES)
namespace delimited_escape_sequences_test
{

auto a = "\o{17}";
auto b = "\x{ab}c";
auto c = "\u{1F1F8}";

}	// namespace delimited_escape_sequences_test
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

#if defined(HAMON_HAS_CXX23_RELAXING_CONSTEXPR)
namespace relaxing_constexpr_test
{

void f(int& i) {
	i = 0;
}

constexpr void g(int& i) {
	f(i);
}

}	// namespace relaxing_constexpr_test
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

#if defined(HAMON_HAS_CXX23_INHERITED_CONSTRUCTOR_CTAD)
namespace inherited_constructor_ctad_test
{

template <typename T>
struct B
{
	B(T) {}
};

B(short) -> B<char>;

template <typename T>
struct C : public B<T>
{
	using B<T>::B;
};

template <typename T, typename U, typename V>
struct F
{
	F(T, U, V) {}
};

template <typename T, typename U>
struct G : F<U, T, int>
{
	using F<U, T, int>::F;
};

GTEST_TEST(ConfigTest, Cxx23InheritedConstructorCtadTest)
{
	{
		C c(42);
		static_assert(std::is_same<decltype(c), C<int>>::value, "");
	}
	{
		C c(short(1));
		static_assert(std::is_same<decltype(c), C<char>>::value, "");
	}
	{
		G g(true, 'a', 1);
		static_assert(std::is_same<decltype(g), G<char, bool>>::value, "");
	}
}

}	// namespace inherited_constructor_ctad_test
#endif

#if defined(HAMON_HAS_CXX23_ASSUME)
namespace assume_test
{

int divide_by_32(int x) {
	[[assume(x >= 0)]];
	return x/32;
}

}	// namespace assume_test
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

#if defined(HAMON_HAS_CXX23_STATIC_VARIABLE_IN_CONSTEXPR_FUNCTION)
namespace static_variable_in_constexpr_function_test
{

constexpr char xdigit(int n) {
	static constexpr char digits[] = "0123456789abcdef";
	return digits[n];
}

}	// namespace static_variable_in_constexpr_function_test
#endif

#if defined(HAMON_HAS_CXX23_CONSTEVAL_PROPAGATE_UP)
namespace consteval_propagate_up_test
{

consteval int id(int i) { return i; }
constexpr char id(char c) { return c; }

template <typename T>
constexpr int f(T t) {
    return t + id(t);
}

auto a = &f<char>; // ok, f<char> is not an immediate function
//auto b = &f<int>;  // error: f<int> is an immediate function

static_assert(f(3) == 6); // ok

template <typename T>
constexpr int g(T t) {    // g<int> is not an immediate function
    return t + id(42);    // because id(42) is already a constant
}

template <typename T, typename F>
constexpr bool is_not(T t, F f) {
    return not f(t);
}

consteval bool is_even(int i) { return i % 2 == 0; }

static_assert(is_not(5, is_even)); // ok

int x = 0;

template <typename T>
constexpr T h(T t = id(x)) { // h<int> is not an immediate function
    return t;
}

template <typename T>
constexpr T hh() {           // hh<int> is an immediate function
    return h<T>();
}

//int i = hh<int>(); // ill-formed: hh<int>() is an immediate-escalating expression
//                   // outside of an immediate-escalating function

struct A {
  int x;
  int y = id(x);
};

template <typename T>
constexpr int k(int) {  // k<int> is not an immediate function
  return A(42).y;       // because A(42) is a constant expression and thus not
}                       // immediate-escalating

}	// namespace consteval_propagate_up_test
#endif

#if defined(HAMON_HAS_CXX23_CHAR8_T_COMPATIBILITY)
namespace char8_t_compatibility_test
{
const char str[] = u8"UTF-8 string";
}	// namespace char8_t_compatibility_test
#endif

#if defined(HAMON_HAS_CXX23_ALLOW_STATIC_ASSERT_FALSE) && defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
namespace allow_static_assert_false_test
{

template <typename T>
int f()
{
	if constexpr (sizeof(T) == sizeof(int))
	{
		return 0;
	}
	else
	{
		static_assert(false, "must be int-sized");
	}
}

auto i = f<int>();

}	// namespace allow_static_assert_false_test
#endif

}	// namespace hamon_config_cxx23_test
