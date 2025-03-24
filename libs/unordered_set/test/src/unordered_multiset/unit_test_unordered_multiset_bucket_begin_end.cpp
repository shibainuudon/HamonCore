/**
 *	@file	unit_test_unordered_multiset_bucket_begin_end.cpp
 *
 *	@brief	begin, end のテスト
 *
 *	constexpr local_iterator begin(size_type n);
 *	constexpr const_local_iterator begin(size_type n) const;
 *	constexpr local_iterator end(size_type n);
 *	constexpr const_local_iterator end(size_type n) const;
 *	constexpr const_local_iterator cbegin(size_type n) const;
 *	constexpr const_local_iterator cend(size_type n) const;
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multiset_test
{

namespace bucket_begin_end_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
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
	using LocalIterator = typename Set::local_iterator;
	using ConstLocalIterator = typename Set::const_local_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().begin (hamon::declval<SizeType>())), LocalIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().end   (hamon::declval<SizeType>())), LocalIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().cbegin(hamon::declval<SizeType>())), ConstLocalIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().cend  (hamon::declval<SizeType>())), ConstLocalIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().begin (hamon::declval<SizeType>())), ConstLocalIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().end   (hamon::declval<SizeType>())), ConstLocalIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().cbegin(hamon::declval<SizeType>())), ConstLocalIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().cend  (hamon::declval<SizeType>())), ConstLocalIterator>::value, "");

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
	static_assert(!noexcept(hamon::declval<Set&>().begin (hamon::declval<SizeType>())), "");
	static_assert(!noexcept(hamon::declval<Set&>().end   (hamon::declval<SizeType>())), "");
	static_assert(!noexcept(hamon::declval<Set&>().cbegin(hamon::declval<SizeType>())), "");
	static_assert(!noexcept(hamon::declval<Set&>().cend  (hamon::declval<SizeType>())), "");
	static_assert(!noexcept(hamon::declval<Set const&>().begin (hamon::declval<SizeType>())), "");
	static_assert(!noexcept(hamon::declval<Set const&>().end   (hamon::declval<SizeType>())), "");
	static_assert(!noexcept(hamon::declval<Set const&>().cbegin(hamon::declval<SizeType>())), "");
	static_assert(!noexcept(hamon::declval<Set const&>().cend  (hamon::declval<SizeType>())), "");
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, BucketBeginEndTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace bucket_begin_end_test

}	// namespace hamon_unordered_multiset_test
