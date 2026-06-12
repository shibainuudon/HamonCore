/**
 *	@file	unit_test_config_cxx26.cpp
 *
 *	@brief	
 */

#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <tuple>
#include <type_traits>

#if HAMON_HAS_INCLUDE(<string_view>) && (HAMON_CXX_STANDARD >= 17)
#include <string_view>
#endif

namespace hamon_config_cxx26_test
{

#if defined(HAMON_HAS_CXX26_REMOVE_UNDEFINED_BEHAVIOR_FROM_LEXING)
namespace remove_undefined_behavior_from_lexing_test
{

// UB : universal character name accross spliced lines
int \u\
0\
3\
9\
1 = 0;

#define CONCAT(x, y) x ## y
int CONCAT(\, u0393) = 0; // UB: universal character name formed by macro expansion
#undef CONCAT

}	// namespace remove_undefined_behavior_from_lexing_test
#endif

#if defined(HAMON_HAS_CXX26_CONSTEXPR_CAST_FROM_VOID_POINTER)
namespace constexpr_cast_from_void_pointer_test
{

struct Sheep
{
	constexpr std::string_view speak() const noexcept { return "Baaaaaa"; }
};

struct Cow
{
	constexpr std::string_view speak() const noexcept { return "Mooo"; }
};

class Animal_View
{
private:
	const void* animal;
	std::string_view (*speak_function)(const void*);
public:
	template <typename Animal>
	constexpr Animal_View(const Animal& a)
		: animal{ &a }, speak_function{ [](const void* object) {
			return static_cast<const Animal*>(object)->speak();
		} }
	{
	}

	constexpr std::string_view speak() const noexcept
	{
		return speak_function(animal);
	}
};

// This is the key bit here. This is a single concrete function
// that can take anything that happens to have the "Animal_View"
// interface
constexpr std::string_view do_speak(Animal_View av) { return av.speak(); }

GTEST_TEST(ConfigTest, Cxx26ConstexprCastFromVoidPointerTest)
{
	// A Cow is a cow. The only think that makes it special
	// is that it has a "std::string_view speak() const" member
	constexpr Cow cow;
	constexpr auto result = do_speak(cow);
	static_assert(result.size() == 4, "");
}

}	// namespace constexpr_cast_from_void_pointer_test
#endif

#if defined(HAMON_HAS_CXX26_STATIC_ASSERT)
namespace static_assert_test
{

enum E
{
	One,
	Two,
	Three
};

constexpr std::string_view ToString(E e)
{
	switch (e)
	{
	case One: return "One";
	case Two: return "Two";
	case Three: return "Three";
	default: return "Unknown";
	}
}

static_assert(true, ToString(One));

}	// namespace static_assert_test
#endif

#if defined(HAMON_HAS_CXX26_PLACEHOLDER_VARIABLES)
namespace placeholder_variables_test
{

inline int f() { return 42; }

auto _ = f(); // Ok, declare a variable "_"
//auto _ = f(); // error: "_" is already defined in this namespace scope

GTEST_TEST(ConfigTest, Cxx26PlaceholderVariablesTest)
{
	auto _ = 42; // Ok, declare a variable "_"
	auto _ = 0; // Ok, re-declare a variable "_"
	{
		auto _ = 1; // Ok, shaddowing
		EXPECT_TRUE(_ == 1); // Ok
	}
//	EXPECT_TRUE(_ == 42); // ill-formed: Use of a redeclared placeholder variables
}

}	// namespace placeholder_variables_test
#endif

#if defined(HAMON_HAS_CXX26_PACK_INDEXING)
namespace pack_indexing_test
{

template <typename... T>
constexpr auto first_plus_last(T... values)
#if !defined(HAMON_GCC_VERSION)
	-> T...[0]
	// TODO: gccだと
	// sorry, unimplemented: mangling type pack index
	// というエラーになる
#endif
{
	return T...[0](values...[0] + values...[sizeof...(values) - 1]);
}

//first_plus_last(); // ill formed
static_assert(first_plus_last(1, 2, 10) == 11);

}	// namespace pack_indexing_test
#endif

#if !defined(HAMON_HAS_CXX26_REMOVE_ARITHMETIC_CONVERSION_ON_ENUMERATIONS)
namespace remove_arithmetic_conversion_on_enumerations_test
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(5054)	// 演算子 '-': 異なる型の列挙間では非推奨です
HAMON_WARNING_DISABLE_MSVC(5055)	// 演算子 '<=': 列挙型と浮動小数点型の間では非推奨です
HAMON_WARNING_DISABLE_CLANG("-Wenum-float-conversion")
HAMON_WARNING_DISABLE_CLANG("-Wenum-enum-conversion")
HAMON_WARNING_DISABLE_CLANG("-Wenum-compare-conditional")
HAMON_WARNING_DISABLE_CLANG("-Wdeprecated-enum-float-conversion")
HAMON_WARNING_DISABLE_CLANG("-Wdeprecated-enum-enum-conversion")
HAMON_WARNING_DISABLE_CLANG("-Wdeprecated-enum-compare-conditional")
HAMON_WARNING_DISABLE_GCC("-Wdeprecated-enum-float-conversion")
HAMON_WARNING_DISABLE_GCC("-Wdeprecated-enum-enum-conversion")
HAMON_WARNING_DISABLE_GCC("-Wenum-compare")

enum E1 { e };
enum E2 { f };
bool b = e <= 3.7;     // ill-formed; previously well-formed
int  k = f - e;        // ill-formed; previously well-formed
auto x = true ? e : f; // ill-formed; previously well-formed

HAMON_WARNING_POP()

}	// namespace remove_arithmetic_conversion_on_enumerations_test
#endif

#if defined(HAMON_HAS_CXX26_ATTRIBUTES_FOR_STRUCTURED_BINDINGS)
namespace attributes_for_structured_bindings_test
{

std::tuple<int, float, int> f()
{
	return { 3, 0.5f, 42 };
}

auto g()
{
	auto [a, b [[maybe_unused]], c] = f();
	return a + c;
}

}	// namespace attributes_for_structured_bindings_test
#endif

#if defined(HAMON_HAS_CXX26_ERRONEOUS_BEHAVIOUR_FOR_UNINITIALIZED_READS)
namespace erroneous_behaviour_for_uninitialized_reads_test
{

void f(int) {}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4700)	// 初期化されていないローカル変数 ' ' が使用されます
HAMON_WARNING_DISABLE_CLANG("-Wuninitialized")
HAMON_WARNING_DISABLE_GCC("-Wuninitialized")

void g()
{
	int x;
	int y [[indeterminate]];

	f(x);
	f(y);
}

HAMON_WARNING_POP()

}	// namespace erroneous_behaviour_for_uninitialized_reads_test
#endif

#if defined(HAMON_HAS_CXX26_DELETED_FUNCTION)
namespace deleted_function_test
{

void newapi();
void oldapi() = delete("This old API is outdated and already been removed. Please use newapi() instead.");

template<typename T>
struct A {/* ... */};
template<typename T>
A<T> factory(const T&) {/* process lvalue */}
template<typename T>
A<T> factory(const T&&) = delete("Using rvalue to construct A may result in dangling reference");

struct MoveOnly
{
	// ... (with move members defaulted or defined)
	MoveOnly(const MoveOnly&) = delete("Copy-construction is expensive; please use move construction instead.");
	MoveOnly& operator=(const MoveOnly&) = delete("Copy-assignment is expensive; please use move assignment instead.");
};

}	// namespace deleted_function_test
#endif

#if defined(HAMON_HAS_CXX26_VARIADIC_FRIEND)
namespace variadic_friend_test
{

template<class... Ts>
class Foo
{
	friend Ts...;
};

}	// namespace variadic_friend_test
#endif

#if defined(HAMON_HAS_CXX26_BRACE_ELISION_IN_AGGREGATE_INITIALIZATION)
namespace brace_elision_in_aggregate_initialization_test
{

struct X { int i, j, k; };

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wmissing-braces")

GTEST_TEST(ConfigTest, Cxx26BraceElisionInAggregateInitializationTest)
{
	X a[] = { 1, 2, 3, 4, 5, 6 };
	X b[2] = { { 1, 2, 3 }, { 4, 5, 6 } };

	EXPECT_EQ(a[0].i, b[0].i);
	EXPECT_EQ(a[0].j, b[0].j);
	EXPECT_EQ(a[0].k, b[0].k);
	EXPECT_EQ(a[1].i, b[1].i);
	EXPECT_EQ(a[1].j, b[1].j);
	EXPECT_EQ(a[1].k, b[1].k);
}

HAMON_WARNING_POP()

}	// namespace brace_elision_in_aggregate_initialization_test
#endif

#if defined(HAMON_HAS_CXX26_CONSTEXPR_PLACEMENT_NEW)
namespace constexpr_placement_new_test
{

struct X
{
	int a = 1;
	int b = 2;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

constexpr bool f()
{
	{
		X* p = std::allocator<X>{}.allocate(1);
		// value initialization
		new (p) X(3, 4);
		VERIFY(p->a == 3);
		VERIFY(p->b == 4);
		std::allocator<X>{}.deallocate(p, 1);
	}
	{
		X* p = std::allocator<X>{}.allocate(1);
		// default initialization
		new (p) X;
		VERIFY(p->a == 1);
		VERIFY(p->b == 2);
		std::allocator<X>{}.deallocate(p, 1);
	}
	// TODO: clang だとエラーになる
	//{
	//	int* p = std::allocator<int>{}.allocate(3);
	//	// list initialization
	//	new (p) int[]{1,2,3};
	//	VERIFY(p[0] == 1);
	//	VERIFY(p[1] == 2);
	//	VERIFY(p[2] == 3);
	//	std::allocator<int>{}.deallocate(p, 3);
	//}
	{
		X* p = std::allocator<X>{}.allocate(1);
		// designated initialization
		new (p) X{.a = 17, .b = 42};
		VERIFY(p->a == 17);
		VERIFY(p->b == 42);
		std::allocator<X>{}.deallocate(p, 1);
	}
	return true;
}

#undef VERIFY

static_assert(f(), "");

}	// namespace constexpr_placement_new_test
#endif

#if defined(HAMON_HAS_CXX26_STRUCTURED_BINDING_DECLARATION_AS_A_CONDITION)
namespace structured_binding_declaration_as_a_condition_test
{

struct result
{
	int val;
	int ec;

	explicit operator bool() const
	{
		return ec == 0;
	}
};

result f()
{
	return {42, 0};
}

void g()
{
	if (auto [val, ec] = f())
	{
		(void)val;
	}
}

}	// namespace structured_binding_declaration_as_a_condition_test
#endif

#if defined(HAMON_HAS_CXX26_FOLD_EXPRESSIONS)
namespace fold_expressions_test
{

template <class T> concept A = std::is_move_constructible_v<T>;
template <class T> concept B = std::is_copy_constructible_v<T>;
template <class T> concept C = A<T> && B<T>;

template <class... T>
requires (A<T> && ...)
int g(T...){return 1;}

template <class... T>
requires (C<T> && ...)
int g(T...){return 2;}

GTEST_TEST(ConfigTest, Cxx26FoldExpressionsTest)
{
	EXPECT_EQ(2, g(0));
}

}	// namespace fold_expressions_test
#endif

#if defined(HAMON_HAS_CXX26_STRUCTURED_BINDINGS_CAN_INTRODUCE_A_PACK)
namespace structured_bindings_can_introduce_a_pack_test
{

struct C { int x, y, z; };

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wunused-variable")

template <class T>
void now_i_know_my()
{
	auto [a, b, c] = C(); // OK, SB0 is a, SB1 is b, and SB2 is c
	auto [d, ...e] = C(); // OK, SB0 is d, the pack e (v1) contains two structured bindings: SB1 and SB2
	auto [...f, g] = C(); // OK, the pack f (v0) contains two structured bindings: SB0 and SB1, and SB2 is g
	auto [h, i, j, ...k] = C(); // OK, the pack k is empty
//	auto [l, m, n, o, ...p] = C(); // error: structured binding size is too small
}

HAMON_WARNING_POP()

}	// namespace structured_bindings_can_introduce_a_pack_test
#endif

#if !defined(HAMON_HAS_CXX26_REMOVE_ARRAY_COMPARISONS)
namespace remove_array_comparisons_test
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(5056)	// 演算子 '==': 配列型に対しては非推奨です
HAMON_WARNING_DISABLE_CLANG("-Wtautological-compare")
HAMON_WARNING_DISABLE_CLANG("-Wdeprecated-array-compare")
#if defined(HAMON_CLANG_VERSION) && (HAMON_CLANG_VERSION >= 200000)
HAMON_WARNING_DISABLE_CLANG("-Warray-compare")
#endif
#if defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION >= 120000)
HAMON_WARNING_DISABLE_GCC("-Warray-compare")
#endif

void f()
{
	int arr1[5];
	int arr2[5];
	bool same = arr1 == arr2; // ill-formed; previously well-formed
	(void)same;
}

HAMON_WARNING_POP()

}	// namespace remove_array_comparisons_test
#endif

#if defined(HAMON_HAS_CXX26_PP_EMBED)
namespace pp_embed_test
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wc23-extensions")

GTEST_TEST(ConfigTest, Cxx26PPEmbedTest)
{
	constexpr char text[] = {
		#embed "test.txt"
	};

	EXPECT_EQ('h', text[0]);
	EXPECT_EQ('e', text[1]);
	EXPECT_EQ('l', text[2]);
	EXPECT_EQ('l', text[3]);
	EXPECT_EQ('o', text[4]);
}

HAMON_WARNING_POP()

}	// namespace pp_embed_test
#endif

}	// namespace hamon_config_cxx26_test
