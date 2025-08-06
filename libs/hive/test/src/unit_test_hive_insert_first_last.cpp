/**
 *	@file	unit_test_hive_insert_first_last.cpp
 *
 *	@brief	insert のテスト
 *
 *	template<class InputIterator>
 *	void insert(InputIterator first, InputIterator last);
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

namespace insert_first_last_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, template <typename> class IteratorWrapper>
HAMON_CXX20_CONSTEXPR bool test_impl()
{
	using Hive = hamon::hive<T>;
	using Iterator = IteratorWrapper<T>;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().insert(hamon::declval<Iterator>(), hamon::declval<Iterator>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Hive>().insert(hamon::declval<Iterator>(), hamon::declval<Iterator>())), "");

	Hive v;
	VERIFY(v.empty());
	VERIFY(v.size() == 0u);
	{
		T a[] = {T{1}, T{2}, T{3}};
		v.insert(Iterator{a}, Iterator{a + 3});
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{6});
	}
	VERIFY(v.size() == 3u);
	{
		T a[] = {T{4}, T{5}, T{6}, T{7}};
		v.insert(Iterator{a}, Iterator{a + 4});
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{28});
	}
	VERIFY(v.size() == 7u);

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

GTEST_TEST(HiveTest, InsertFirstLastTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace insert_first_last_test

}	// namespace hamon_hive_test
