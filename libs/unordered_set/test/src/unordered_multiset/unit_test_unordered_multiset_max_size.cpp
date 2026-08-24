/**
 *	@file	unit_test_unordered_multiset_max_size.cpp
 *
 *	@brief	max_size のテスト
 *
 *	constexpr size_type max_size() const noexcept;
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multiset_test
{

namespace max_size_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::unordered_multiset<Key>;
	using SizeType  = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().max_size()), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().max_size()), SizeType>::value, "");
	static_assert(noexcept(hamon::declval<Set&>().max_size()), "");
	static_assert(noexcept(hamon::declval<Set const&>().max_size()), "");

	Set const v;
	VERIFY(v.max_size() > 0);

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, MaxSizeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace max_size_test

}	// namespace hamon_unordered_multiset_test
