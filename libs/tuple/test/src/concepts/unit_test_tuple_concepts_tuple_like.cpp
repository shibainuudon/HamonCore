/**
 *	@file	unit_test_tuple_concepts_tuple_like.cpp
 *
 *	@brief	tuple_like のテスト
 */

#include <hamon/tuple/concepts/tuple_like.hpp>
#include <hamon/config.hpp>
#include <utility>
#include <tuple>
#include <array>
#include <vector>
#include <string>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_TUPLE_LIKE_TEST(B, ...)	\
	static_assert(B == hamon::tuple_like<__VA_ARGS__>, "");	\
	static_assert(B == hamon::tuple_like_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_TUPLE_LIKE_TEST(B, ...)	\
	static_assert(B == hamon::tuple_like<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::tuple_like_t<__VA_ARGS__>::value, "")
#endif


HAMON_TUPLE_LIKE_TEST(false, int);
HAMON_TUPLE_LIKE_TEST(false, float);

HAMON_TUPLE_LIKE_TEST(true, std::pair<int, int>);
HAMON_TUPLE_LIKE_TEST(true, std::pair<float, char>);
HAMON_TUPLE_LIKE_TEST(true, std::tuple<>);
HAMON_TUPLE_LIKE_TEST(true, std::tuple<int>);
HAMON_TUPLE_LIKE_TEST(true, std::tuple<int, int>);
HAMON_TUPLE_LIKE_TEST(true, std::tuple<float, long, double>);
HAMON_TUPLE_LIKE_TEST(true, std::array<float, 0>);
HAMON_TUPLE_LIKE_TEST(true, std::array<int, 1>);
HAMON_TUPLE_LIKE_TEST(true, std::array<int, 10>);

HAMON_TUPLE_LIKE_TEST(false, std::vector<int>);
HAMON_TUPLE_LIKE_TEST(false, std::string);

#undef HAMON_TUPLE_LIKE_TEST
