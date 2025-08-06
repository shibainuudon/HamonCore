/**
 *	@file	unit_test_hive_ctor_first_last_limits.cpp
 *
 *	@brief	first, last, block_limits を引数に取るコンストラクタのテスト
 *
 *	template<class InputIterator>
 *	hive(InputIterator first, InputIterator last, hive_limits block_limits, const Allocator& = Allocator());
 */

#include <hamon/hive.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/numeric/accumulate.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_hive_test
{

namespace ctor_first_last_limits_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, template <typename> class IteratorWrapper>
HAMON_CXX20_CONSTEXPR bool test_impl()
{
	using Hive = hamon::hive<T>;
	using Allocator = typename Hive::allocator_type;
	using Iterator = IteratorWrapper<T>;

	static_assert( hamon::is_constructible           <Hive, Iterator, Iterator, hamon::hive_limits>::value, "");
	static_assert(!hamon::is_nothrow_constructible   <Hive, Iterator, Iterator, hamon::hive_limits>::value, "");
	static_assert( hamon::is_implicitly_constructible<Hive, Iterator, Iterator, hamon::hive_limits>::value, "");
	static_assert(!hamon::is_trivially_constructible <Hive, Iterator, Iterator, hamon::hive_limits>::value, "");

	static_assert( hamon::is_constructible           <Hive, Iterator, Iterator, hamon::hive_limits, const Allocator&>::value, "");
	static_assert(!hamon::is_nothrow_constructible   <Hive, Iterator, Iterator, hamon::hive_limits, const Allocator&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Hive, Iterator, Iterator, hamon::hive_limits, const Allocator&>::value, "");
	static_assert(!hamon::is_trivially_constructible <Hive, Iterator, Iterator, hamon::hive_limits, const Allocator&>::value, "");

	hamon::hive_limits block_limits{1, 100};
	Allocator alloc;
	T a[] = {T{1}, T{2}, T{3}, T{4}};

	{
		Hive v(Iterator{a}, Iterator{a + 4}, block_limits);
		VERIFY(v.size() == 4u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{10});
	}
	{
		Hive v(Iterator{a}, Iterator{a + 4}, block_limits, alloc);
		VERIFY(v.size() == 4u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{10});
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

GTEST_TEST(HiveTest, CtorFirstLastLimitsTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<double>());
}

}	// namespace ctor_first_last_limits_test

}	// namespace hamon_hive_test
