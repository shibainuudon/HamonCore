/**
 *	@file	unit_test_deque_pop_back.cpp
 *
 *	@brief	pop_back のテスト
 *
 *	void pop_back();
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace pop_back_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Deque = hamon::deque<T>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().pop_back()),
		void
	>::value, "");

#if 0
	static_assert(!noexcept(
		hamon::declval<Deque&>().pop_back()), "");
#endif

	{
		Deque v {1,2,3};
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
		Deque v {1,2,3};
		// 削除された要素へのイテレータと参照は無効化される。それ以外のイテレータと参照は無効化されない
		auto const it1 = v.begin();
		auto const it2 = v.begin() + 1;
		auto& r0 = v[0];
		auto& r1 = v[1];
		v.pop_back();
		VERIFY(it1 == v.begin());
		VERIFY(it2 == v.begin() + 1);
		VERIFY(&r0 == &v[0]);
		VERIFY(&r1 == &v[1]);
		v.pop_back();
		VERIFY(it1 == v.begin());
		VERIFY(&r0 == &v[0]);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, PopBackTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace pop_back_test

}	// namespace hamon_deque_test
