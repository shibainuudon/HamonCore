/**
 *	@file	unit_test_concepts_cpp17_hash.cpp
 *
 *	@brief	cpp17_hash のテスト
 */

#include <hamon/concepts/detail/cpp17_hash.hpp>
#include <hamon/config.hpp>
#include <functional>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_CPP17_HASH_TEST(B, ...)	\
	static_assert(B == hamon::detail::cpp17_hash<__VA_ARGS__>, "");	\
	static_assert(B == hamon::detail::cpp17_hash_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_CPP17_HASH_TEST(B, ...)	\
	static_assert(B == hamon::detail::cpp17_hash<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::detail::cpp17_hash_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_concepts_test
{

namespace cpp17_hash_test
{

HAMON_CPP17_HASH_TEST(false, void, int);
HAMON_CPP17_HASH_TEST(false, int, int);

struct H1
{
	std::size_t operator()(int);
};
HAMON_CPP17_HASH_TEST(true,  H1, int);
HAMON_CPP17_HASH_TEST(false, H1, int*);

struct H2
{
	std::size_t operator()(int*);
};
HAMON_CPP17_HASH_TEST(false, H2, int);
HAMON_CPP17_HASH_TEST(true,  H2, int*);

struct H3
{
	void operator()(int);
};
HAMON_CPP17_HASH_TEST(false, H3, int);
HAMON_CPP17_HASH_TEST(false, H3, int*);

HAMON_CPP17_HASH_TEST(true, std::hash<bool>,  bool);
HAMON_CPP17_HASH_TEST(true, std::hash<char>,  char);
HAMON_CPP17_HASH_TEST(true, std::hash<int>,   int);
HAMON_CPP17_HASH_TEST(true, std::hash<float>, float);

}	// namespace cpp17_hash_test

}	// namespace hamon_concepts_test

#undef HAMON_CPP17_HASH_TEST
