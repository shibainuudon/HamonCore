/**
 *	@file	unit_test_config_cxx23.cpp
 *
 *	@brief	
 */

#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <type_traits>

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
