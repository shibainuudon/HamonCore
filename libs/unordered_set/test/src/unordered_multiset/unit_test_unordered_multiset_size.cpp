/**
 *	@file	unit_test_unordered_multiset_size.cpp
 *
 *	@brief	size のテスト
 *
 *	constexpr size_type size() const noexcept;
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multiset_test
{

namespace size_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::unordered_multiset<Key>;
	using SizeType  = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().size()), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().size()), SizeType>::value, "");
	static_assert(noexcept(hamon::declval<Set&>().size()), "");
	static_assert(noexcept(hamon::declval<Set const&>().size()), "");

	Set v;
	VERIFY(v.size() == 0);

	v.insert(Key{1});
	VERIFY(v.size() == 1);

	v.insert({Key{3}, Key{1}, Key{4}});
	VERIFY(v.size() == 4);

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, SizeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace size_test

}	// namespace hamon_unordered_multiset_test
