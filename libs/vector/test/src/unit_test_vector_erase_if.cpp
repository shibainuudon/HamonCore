/**
 *	@file	unit_test_vector_erase_if.cpp
 *
 *	@brief	erase_if のテスト
 *
 *	template<class T, class Allocator, class Predicate>
 *	constexpr typename vector<T, Allocator>::size_type
 *	erase_if(vector<T, Allocator>& c, Predicate pred);
 */

#include <hamon/vector.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace erase_if_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct IsEven
{
	template <typename T>
	HAMON_CXX11_CONSTEXPR bool operator()(T x) const noexcept
	{
		return x % 2 == 0;
	}
};

HAMON_CXX20_CONSTEXPR bool test()
{
	using T = int;
	using Vector = hamon::vector<T>;
	using SizeType = typename Vector::size_type;

	static_assert(hamon::is_same<
		decltype(hamon::erase_if(hamon::declval<Vector&>(), hamon::declval<IsEven>())),
		SizeType
	>::value, "");

#if !defined(HAMON_USE_STD_VECTOR)
	static_assert(!noexcept(
		hamon::erase_if(hamon::declval<Vector&>(), hamon::declval<IsEven>())), "");
#endif

	{
		Vector v = {3,1,4,5,2};
		auto r = hamon::erase_if(v, IsEven{});
		VERIFY(r == 2);
		const T v2[] = {3,1,5,};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	{
		Vector v = {3,1,4,1,5,9,2,6,5,3,5,};
		auto r = hamon::erase_if(v, [](T x) { return x >= 5; });
		VERIFY(r == 5);
		const T v2[] = {3,1,4,1,2,3,};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, EraseIfTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace erase_if_test

}	// namespace hamon_vector_test
