/**
 *	@file	unit_test_unordered_multiset_insert_range.cpp
 *
 *	@brief	insert_range のテスト
 *
 *	template<container-compatible-range<value_type> R>
 *	constexpr void insert_range(R&& rg);
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "unordered_multiset_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))

namespace hamon_unordered_multiset_test
{

namespace insert_range_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, template <typename> class RangeWrapper>
UNORDERED_MULTISET_TEST_CONSTEXPR bool test_impl()
{
	using Set = hamon::unordered_multiset<Key>;
	using ValueType = typename Set::value_type;
	using Range = RangeWrapper<ValueType>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().insert_range(hamon::declval<Range>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().insert_range(hamon::declval<Range>())), "");

	Set v;
	v.max_load_factor(0.8f);

	{
		Key a[] = { Key{3}, Key{2}, Key{3}, Key{1}, Key{2}, Key{3} };
		Range r(a);
		v.insert_range(r);
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	{
		Key a[] = { Key{2}, Key{4}, Key{0}, Key{1} };
		v.insert_range(Range(a));
		VERIFY(!v.empty());
		VERIFY(v.size() == 10);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}

	return true;
}

template <typename Key>
UNORDERED_MULTISET_TEST_CONSTEXPR bool test()
{
	return
		test_impl<Key, test_input_range>() &&
		test_impl<Key, test_forward_range>() &&
		test_impl<Key, test_bidirectional_range>() &&
		test_impl<Key, test_random_access_range>() &&
		test_impl<Key, test_contiguous_range>() &&
		test_impl<Key, test_input_sized_range>() &&
		test_impl<Key, test_forward_sized_range>() &&
		test_impl<Key, test_bidirectional_sized_range>() &&
		test_impl<Key, test_random_access_sized_range>() &&
		test_impl<Key, test_contiguous_sized_range>();
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, InsertRangeTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		using Set = hamon::unordered_multiset<ThrowOnCopyIfNegative, hamon::hash<ThrowOnCopyIfNegative>>;

		Set v;
		EXPECT_EQ(0u, v.size());

		{
			ThrowOnCopyIfNegative a[] =
			{
				ThrowOnCopyIfNegative{ 10},
				ThrowOnCopyIfNegative{ 20},
				ThrowOnCopyIfNegative{-30},
				ThrowOnCopyIfNegative{ 40},
			};

			// ThrowOnCopyIfNegative{-30} をコピーするときに例外を投げる
			EXPECT_THROW(v.insert_range(a), ThrowOnCopyIfNegative::Exception);
			EXPECT_EQ(2u, v.size());
		}

		v.insert(ThrowOnCopyIfNegative{-30});
		EXPECT_EQ(3u, v.size());

		{
			ThrowOnCopyIfNegative a[] =
			{
				ThrowOnCopyIfNegative{ 20},
				ThrowOnCopyIfNegative{-30},
				ThrowOnCopyIfNegative{ 40},
				ThrowOnCopyIfNegative{ 50},
			};

			// ThrowOnCopyIfNegative{-30} をコピーするときに例外を投げる
			EXPECT_THROW(v.insert_range(a), ThrowOnCopyIfNegative::Exception);
			EXPECT_EQ(4u, v.size());
		}
	}
#endif
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace insert_range_test

}	// namespace hamon_unordered_multiset_test

#endif
