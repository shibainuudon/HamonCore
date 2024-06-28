/**
 *	@file	unit_test_deque_shrink_to_fit.cpp
 *
 *	@brief	shrink_to_fit のテスト
 *
 *	void shrink_to_fit();
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace shrink_to_fit_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Deque = hamon::deque<T>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().shrink_to_fit()),
		void
	>::value, "");

	static_assert(!noexcept(
		hamon::declval<Deque&>().shrink_to_fit()), "");

	{
		Deque v{1,2,3,4,5};
		VERIFY(v.size() == 5);
		v.shrink_to_fit();
		VERIFY(v.size() == 5);
		v.pop_back();
		VERIFY(v.size() == 4);
		v.shrink_to_fit();
		VERIFY(v.size() == 4);
		v.clear();
		VERIFY(v.size() == 0);
		v.shrink_to_fit();
		VERIFY(v.size() == 0);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, ShrinkToFitTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace shrink_to_fit_test

}	// namespace hamon_deque_test
