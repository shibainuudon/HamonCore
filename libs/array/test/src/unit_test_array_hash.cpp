/**
 *	@file	unit_test_array_hash.cpp
 *
 *	@brief	hash<array> のテスト
 */

#include <hamon/array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/type_traits/is_detected.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_array_test {
namespace hash_test {

template <typename T>
using invoke_hash = decltype(hamon::hash<T>{}(hamon::declval<T const&>()));

struct S1 {};
struct S2 {};

}	// namespace hash_test
}	// namespace hamon_array_test

template <>
struct hamon::hash<hamon_array_test::hash_test::S1>
{
	hamon::size_t operator()(hamon_array_test::hash_test::S1 const&) const
	{
		return 42;
	}
};

namespace hamon_array_test {
namespace hash_test {

static_assert( hamon::is_detected<invoke_hash, int>::value, "");
static_assert( hamon::is_detected<invoke_hash, float>::value, "");
static_assert( hamon::is_detected<invoke_hash, S1>::value, "");
static_assert(!hamon::is_detected<invoke_hash, S2>::value, "");

static_assert( hamon::is_detected<invoke_hash, hamon::array<int, 3>>::value, "");
static_assert( hamon::is_detected<invoke_hash, hamon::array<float, 3>>::value, "");
static_assert( hamon::is_detected<invoke_hash, hamon::array<S1, 3>>::value, "");
static_assert(!hamon::is_detected<invoke_hash, hamon::array<S2, 3>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	using Array1 = hamon::array<int, 1>;
	using Array2 = hamon::array<int, 2>;
	using Array3 = hamon::array<int, 3>;
	using Array4 = hamon::array<float, 3>;

	Array1 a1{0};
	Array1 a2{0};
	Array1 a3{1};
	Array2 a4{0, 0};
	Array3 a5{0, 0, 0};
	Array3 a6{0, 1, 2};
	Array3 a7{0, 1, 3};
	Array3 a8{1, 1, 2};
	Array4 a9{0, 1, 2};

	using Hash1 = hamon::hash<Array1>;
	using Hash2 = hamon::hash<Array2>;
	using Hash3 = hamon::hash<Array3>;
	using Hash4 = hamon::hash<Array4>;

	VERIFY(Hash1{}(a1) == Hash1{}(a1));
	VERIFY(Hash1{}(a1) == Hash1{}(a2));
	VERIFY(Hash1{}(a1) != Hash1{}(a3));
	VERIFY(Hash1{}(a1) != Hash2{}(a4));
	VERIFY(Hash1{}(a1) != Hash3{}(a5));

	VERIFY(Hash3{}(a6) == Hash3{}(a6));
	VERIFY(Hash3{}(a6) != Hash3{}(a7));
	VERIFY(Hash3{}(a6) != Hash3{}(a8));
	VERIFY(Hash3{}(a6) != Hash4{}(a9));

	return true;
}

#undef VERIFY

GTEST_TEST(ArrayTest, HashTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace hash_test
}	// namespace hamon_array_test
