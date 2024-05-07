/**
 *	@file	unit_test_vector_pop_back.cpp
 *
 *	@brief	pop_back のテスト
 *
 *	constexpr void pop_back();
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace pop_back_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Vector = hamon::vector<T>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().pop_back()),
		void
	>::value, "");

#if 0
	static_assert(!noexcept(
		hamon::declval<Vector&>().pop_back()), "");
#endif

	{
		Vector v {1,2,3};
		VERIFY(v.size() == 3);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
		v.pop_back();
		VERIFY(v.size() == 2);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		v.pop_back();
		VERIFY(v.size() == 1);
		VERIFY(v[0] == 1);
		v.pop_back();
		VERIFY(v.size() == 0);
	}
	{
		Vector v {1,2,3};
		// 削除位置より前のイテレータは無効にならない
		auto const it1 = v.begin();
		auto const it2 = v.begin() + 1;
		auto const old_capacity = v.capacity();
		v.pop_back();
		VERIFY(v.capacity() == old_capacity);	// capacityは変化しない
		VERIFY(it1 == v.begin());
		VERIFY(it2 == v.begin() + 1);
		v.pop_back();
		VERIFY(it1 == v.begin());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, PopBackTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace pop_back_test

}	// namespace hamon_vector_test
