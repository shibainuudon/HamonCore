/**
 *	@file	unit_test_tuple_concepts_pair_like.cpp
 *
 *	@brief	pair_like のテスト
 */

#include <hamon/tuple/concepts/pair_like.hpp>
#include <hamon/tuple/tuple.hpp>
#include <hamon/pair/pair.hpp>
#include <hamon/array/array.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>
#include <utility>
#include <tuple>
#include <array>
#include <string>
#if (HAMON_CXX_STANDARD >= 20) && HAMON_HAS_INCLUDE(<ranges>)
#  include <ranges>
#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_PAIR_LIKE_TEST_IMPL(B, ...)	\
	static_assert(B == hamon::pair_like<__VA_ARGS__>, "");	\
	static_assert(B == hamon::pair_like_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_PAIR_LIKE_TEST_IMPL(B, ...)	\
	static_assert(B == hamon::pair_like<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::pair_like_t<__VA_ARGS__>::value, "")
#endif

#define HAMON_PAIR_LIKE_TEST(B, ...)	\
	HAMON_PAIR_LIKE_TEST_IMPL(B, __VA_ARGS__);	\
	HAMON_PAIR_LIKE_TEST_IMPL(B, __VA_ARGS__ &);	\
	HAMON_PAIR_LIKE_TEST_IMPL(B, __VA_ARGS__ &&);	\
	HAMON_PAIR_LIKE_TEST_IMPL(B, __VA_ARGS__ const);	\
	HAMON_PAIR_LIKE_TEST_IMPL(B, __VA_ARGS__ const&);	\
	HAMON_PAIR_LIKE_TEST_IMPL(B, __VA_ARGS__ const&&)

HAMON_PAIR_LIKE_TEST(true,  std::pair<int, int>);
HAMON_PAIR_LIKE_TEST(true,  std::pair<float, char>);
HAMON_PAIR_LIKE_TEST(false, std::tuple<>);
HAMON_PAIR_LIKE_TEST(false, std::tuple<int>);
HAMON_PAIR_LIKE_TEST(true,  std::tuple<int, int>);
HAMON_PAIR_LIKE_TEST(true,  std::tuple<float, long>);
HAMON_PAIR_LIKE_TEST(false, std::tuple<float, long, double>);
HAMON_PAIR_LIKE_TEST(false, std::array<float, 0>);
HAMON_PAIR_LIKE_TEST(false, std::array<int, 1>);
HAMON_PAIR_LIKE_TEST(true,  std::array<int, 2>);
HAMON_PAIR_LIKE_TEST(false, std::array<int, 3>);
HAMON_PAIR_LIKE_TEST(false, std::array<int, 10>);
#if defined(__cpp_lib_ranges) && (__cpp_lib_ranges >= 201911)
HAMON_PAIR_LIKE_TEST(true, std::ranges::subrange<int*, int*, std::ranges::subrange_kind::sized>);
#endif

HAMON_PAIR_LIKE_TEST(true,  hamon::pair<int, int>);
HAMON_PAIR_LIKE_TEST(true,  hamon::pair<float, char>);
HAMON_PAIR_LIKE_TEST(false, hamon::tuple<>);
HAMON_PAIR_LIKE_TEST(false, hamon::tuple<int>);
HAMON_PAIR_LIKE_TEST(true,  hamon::tuple<int, int>);
HAMON_PAIR_LIKE_TEST(true,  hamon::tuple<float, long>);
HAMON_PAIR_LIKE_TEST(false, hamon::tuple<float, long, double>);
HAMON_PAIR_LIKE_TEST(false, hamon::array<float, 0>);
HAMON_PAIR_LIKE_TEST(false, hamon::array<int, 1>);
HAMON_PAIR_LIKE_TEST(true,  hamon::array<int, 2>);
HAMON_PAIR_LIKE_TEST(false, hamon::array<int, 3>);
HAMON_PAIR_LIKE_TEST(false, hamon::array<int, 10>);
HAMON_PAIR_LIKE_TEST(true,  hamon::ranges::subrange<int*, int*, hamon::ranges::subrange_kind::sized>);

HAMON_PAIR_LIKE_TEST(false, int);
HAMON_PAIR_LIKE_TEST(false, float);

HAMON_PAIR_LIKE_TEST(false, hamon::vector<int>);
HAMON_PAIR_LIKE_TEST(false, std::string);

#undef HAMON_PAIR_LIKE_TEST_IMPL
#undef HAMON_PAIR_LIKE_TEST
