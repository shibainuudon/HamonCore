/**
 *	@file	unit_test_unordered_set_bucket_begin_end.cpp
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

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_set_test
{

namespace bucket_begin_end_test
{

#if !defined(HAMON_USE_STD_UNORDERED_SET) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
UNORDERED_SET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::unordered_set<Key>;
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

#if !defined(HAMON_USE_STD_UNORDERED_SET)
	static_assert( noexcept(hamon::declval<Set&>().begin (hamon::declval<SizeType>())), "");
	static_assert( noexcept(hamon::declval<Set&>().end   (hamon::declval<SizeType>())), "");
	static_assert( noexcept(hamon::declval<Set&>().cbegin(hamon::declval<SizeType>())), "");
	static_assert( noexcept(hamon::declval<Set&>().cend  (hamon::declval<SizeType>())), "");
	static_assert( noexcept(hamon::declval<Set const&>().begin (hamon::declval<SizeType>())), "");
	static_assert( noexcept(hamon::declval<Set const&>().end   (hamon::declval<SizeType>())), "");
	static_assert( noexcept(hamon::declval<Set const&>().cbegin(hamon::declval<SizeType>())), "");
	static_assert( noexcept(hamon::declval<Set const&>().cend  (hamon::declval<SizeType>())), "");
#endif

	{
		Set v{Key{3}, Key{1}, Key{4}, Key{1}};

		auto check = [](LocalIterator it)
		{
			return
				*it == 1 ||
				*it == 3 ||
				*it == 4;
		};

		for (SizeType i = 0; i < v.bucket_count(); ++i)
		{
			for (auto it = v.begin(i); it != v.end(i); ++it)
			{
				VERIFY(check(it));
			}
		}
	}
	{
		Set const v{Key{3}, Key{1}, Key{4}, Key{1}};

		auto check = [](ConstLocalIterator it)
		{
			return
				*it == 1 ||
				*it == 3 ||
				*it == 4;
		};

		for (SizeType i = 0; i < v.bucket_count(); ++i)
		{
			for (auto it = v.begin(i); it != v.end(i); ++it)
			{
				VERIFY(check(it));
			}
		}
	}
	{
		Set v{Key{3}, Key{1}, Key{4}, Key{1}};

		auto check = [](ConstLocalIterator it)
		{
			return
				*it == 1 ||
				*it == 3 ||
				*it == 4;
		};

		for (SizeType i = 0; i < v.bucket_count(); ++i)
		{
			for (auto it = v.cbegin(i); it != v.cend(i); ++it)
			{
				VERIFY(check(it));
			}
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, BucketBeginEndTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace bucket_begin_end_test

}	// namespace hamon_unordered_set_test
