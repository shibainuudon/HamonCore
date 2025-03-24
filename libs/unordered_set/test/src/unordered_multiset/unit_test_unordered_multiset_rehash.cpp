/**
 *	@file	unit_test_unordered_multiset_rehash.cpp
 *
 *	@brief	rehash のテスト
 *
 *	constexpr void rehash(size_type n);
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multiset_test
{

namespace rehash_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
UNORDERED_MULTISET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::unordered_multiset<Key>;
	using SizeType = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().rehash(hamon::declval<SizeType>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().rehash(hamon::declval<SizeType>())), "");

	Set v;

	v.rehash(10);
	VERIFY(static_cast<float>(v.bucket_count()) >= static_cast<float>(v.size()) / v.max_load_factor());
	VERIFY(v.bucket_count() >= 10);

	for (int i = 0; i < 100; ++i)
	{
		v.emplace(static_cast<Key>(i));
	}

	v.rehash(1000);
	VERIFY(static_cast<float>(v.bucket_count()) >= static_cast<float>(v.size()) / v.max_load_factor());
	VERIFY(v.bucket_count() >= 1000);

	v.clear();
	v.rehash(1);
	VERIFY(static_cast<float>(v.bucket_count()) >= static_cast<float>(v.size()) / v.max_load_factor());
	VERIFY(v.bucket_count() >= 1);

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, RehashTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace rehash_test

}	// namespace hamon_unordered_multiset_test
