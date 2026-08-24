/**
 *	@file	unit_test_unordered_set_bucket.cpp
 *
 *	@brief	bucket のテスト
 *
 *	constexpr size_type bucket(const key_type& k) const;
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_set_test_helper.hpp"

namespace hamon_unordered_set_test
{

namespace bucket_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::unordered_set<Key>;
	using SizeType = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().bucket(hamon::declval<Key const&>())), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().bucket(hamon::declval<Key const&>())), SizeType>::value, "");
	//static_assert( noexcept(hamon::declval<Set&>().bucket(hamon::declval<Key const&>())), "");
	//static_assert( noexcept(hamon::declval<Set const&>().bucket(hamon::declval<Key const&>())), "");

	Set const v{Key{3}, Key{1}, Key{4}, Key{1}, Key{5}};
	VERIFY(v.bucket(Key{0}) < v.bucket_count());
	VERIFY(v.bucket(Key{1}) < v.bucket_count());
	VERIFY(v.bucket(Key{2}) < v.bucket_count());
	VERIFY(v.bucket(Key{3}) < v.bucket_count());
	VERIFY(v.bucket(Key{4}) < v.bucket_count());
	VERIFY(v.bucket(Key{5}) < v.bucket_count());
	VERIFY(v.bucket(Key{100}) < v.bucket_count());

	return true;
}

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test_noexcept()
{
	{
		using Set = hamon::unordered_set<Key, NoThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert( noexcept(hamon::declval<Set&>().bucket(hamon::declval<Key const&>())), "");
		static_assert( noexcept(hamon::declval<Set const&>().bucket(hamon::declval<Key const&>())), "");
	}
	{
		using Set = hamon::unordered_set<Key, NoThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert( noexcept(hamon::declval<Set&>().bucket(hamon::declval<Key const&>())), "");
		static_assert( noexcept(hamon::declval<Set const&>().bucket(hamon::declval<Key const&>())), "");
	}
	{
		using Set = hamon::unordered_set<Key, ThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Set&>().bucket(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().bucket(hamon::declval<Key const&>())), "");
	}
	{
		using Set = hamon::unordered_set<Key, ThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Set&>().bucket(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().bucket(hamon::declval<Key const&>())), "");
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, BucketTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<float>()));
}

}	// namespace bucket_test

}	// namespace hamon_unordered_set_test
