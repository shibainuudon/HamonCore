/**
 *	@file	unit_test_config_cxx26.cpp
 *
 *	@brief	
 */

#include <hamon/config.hpp>
#include <gtest/gtest.h>

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

}	// namespace hamon_config_cxx26_test
