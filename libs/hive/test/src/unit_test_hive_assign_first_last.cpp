/**
 *	@file	unit_test_hive_assign_first_last.cpp
 *
 *	@brief	assign のテスト
 *
 *	template<class InputIterator>
 *	void assign(InputIterator first, InputIterator last);
 */

#include <hamon/hive.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/numeric/accumulate.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_hive_test
{

namespace assign_first_last_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, template <typename> class IteratorWrapper>
HAMON_CXX20_CONSTEXPR bool test_impl()
{
	using Hive = hamon::hive<T>;
	using Iterator = IteratorWrapper<T>;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().assign(hamon::declval<Iterator>(), hamon::declval<Iterator>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Hive>().assign(hamon::declval<Iterator>(), hamon::declval<Iterator>())), "");

	Hive v;

	{
		T a[] = {10,20,30};
		v.assign(Iterator{a}, Iterator{a + 3});
		VERIFY(v.size() == 3u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{60});
	}
	{
		T a[] = {5,4,3,2,1};
		v.assign(Iterator{a}, Iterator{a + 5});
		VERIFY(v.size() == 5u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{15});
	}
	{
		T a[] = {5,4,3,2,1};
		v.assign(Iterator{a}, Iterator{a});
		VERIFY(v.size() == 0u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{0});
	}

	return true;
}

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	return
		test_impl<T, cpp17_input_iterator_wrapper>() &&
		//test_impl<T, input_iterator_wrapper>() &&
		test_impl<T, forward_iterator_wrapper>() &&
		test_impl<T, bidirectional_iterator_wrapper>() &&
		test_impl<T, random_access_iterator_wrapper>() &&
		test_impl<T, contiguous_iterator_wrapper>();
}

#undef VERIFY

GTEST_TEST(HiveTest, AssignFirstLastTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace assign_first_last_test

}	// namespace hamon_hive_test
