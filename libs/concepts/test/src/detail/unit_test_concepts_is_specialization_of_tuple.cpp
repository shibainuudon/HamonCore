/**
 *	@file	unit_test_concepts_is_specialization_of_tuple.cpp
 *
 *	@brief	is_specialization_of_tuple のテスト
 */

#include <hamon/concepts/detail/is_specialization_of_tuple.hpp>
#include <hamon/array.hpp>
#include <hamon/pair.hpp>
#include <hamon/ranges/views/subrange.hpp>
#include <hamon/tuple.hpp>
#include <hamon/config.hpp>
#include <array>
#include <tuple>
#include <utility>
#if (HAMON_CXX_STANDARD >= 20) && HAMON_HAS_INCLUDE(<ranges>)
#  include <ranges>
#endif

#define HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(B, ...)	\
	static_assert(B == hamon::detail::is_specialization_of_tuple<__VA_ARGS__>::value, "")

namespace hamon_concepts_test
{

namespace is_specialization_of_tuple_test
{

HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, std::array<int, 3>);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, std::array<float, 10>);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, std::pair<int, float>);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, std::pair<double, long>);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(true,  std::tuple<int>);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(true,  std::tuple<char, float, int>);
#if defined(__cpp_lib_ranges) && (__cpp_lib_ranges >= 201911)
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, std::ranges::subrange<int*, int*, std::ranges::subrange_kind::sized>);
#endif

HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, hamon::array<int, 3>);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, hamon::array<float, 10>);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, hamon::pair<int, float>);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, hamon::pair<double, long>);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(true,  hamon::tuple<int>);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(true,  hamon::tuple<char, float, int>);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, hamon::ranges::subrange<int*, int*, hamon::ranges::subrange_kind::sized>);

template <typename...>
struct Tuple{};

HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, Tuple<int>);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, Tuple<char, float, int>);

// signed integer types
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, signed char);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, signed short);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, signed int);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, signed long);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, signed long long);

// unsigned integer types
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, unsigned char);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, unsigned short);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, unsigned int);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, unsigned long);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, unsigned long long);

// other is_specialization_of_tuple types
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, bool);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, char);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, wchar_t);
#if defined(HAMON_HAS_CXX11_CHAR16_T)
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, char16_t);
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, char32_t);
#endif
#if 0//defined(HAMON_HAS_CXX20_CHAR8_T)
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, char8_t);
#endif

HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, void);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, float);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, int*);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, int&);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, int&&);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, const int&);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, int[]);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, int[2]);
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, int());
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, int(*)());
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, int(&)());

enum E { };
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, E);
enum class CE { };
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, CE);
struct A { };
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, A);
union B { };
HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST(false, B);

}	// namespace is_specialization_of_tuple_test

}	// namespace hamon_concepts_test

#undef HAMON_IS_SPECIALIZATION_OF_TUPLE_TEST
