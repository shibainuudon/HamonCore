/**
 *	@file	unit_test_deque_pop_front.cpp
 *
 *	@brief	pop_front のテスト
 *
 *	void pop_front();
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if 0
namespace hamon_deque_test
{

namespace pop_front_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Deque = hamon::deque<T>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().pop_front()),
		void
	>::value, "");

#if 0
	static_assert(!noexcept(
		hamon::declval<Deque&>().pop_front()), "");
#endif

	{
		Deque v {1,2,3};
		VERIFY(v.size() == 3);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
		v.pop_front();
		VERIFY(v.size() == 2);
		VERIFY(v[0] == 2);
		VERIFY(v[1] == 3);
		v.pop_front();
		VERIFY(v.size() == 1);
		VERIFY(v[0] == 3);
		v.pop_front();
		VERIFY(v.size() == 0);
	}
	//{
	//	Deque v {1,2,3};
	//	// 削除位置より前のイテレータは無効にならない
	//	auto const it1 = v.begin();
	//	auto const it2 = v.begin() + 1;
	//	//auto const old_capacity = v.capacity();
	//	v.pop_front();
	//	//VERIFY(v.capacity() == old_capacity);	// capacityは変化しない
	//	VERIFY(it1 == v.begin());
	//	VERIFY(it2 == v.begin() + 1);
	//	v.pop_front();
	//	VERIFY(it1 == v.begin());
	//}

	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, PopFrontTest)
{
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<unsigned int>());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<char>());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<float>());
}

}	// namespace pop_front_test

}	// namespace hamon_deque_test
#endif
