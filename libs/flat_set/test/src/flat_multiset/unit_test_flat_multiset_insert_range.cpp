/**
 *	@file	unit_test_flat_multiset_insert_range.cpp
 *
 *	@brief	insert_range のテスト
 *
 *	template<container-compatible-range<value_type> R>
 *	constexpr void insert_range(R&& rg);
 */

#include <hamon/flat_set/flat_multiset.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "flat_multiset_test_helper.hpp"

namespace hamon_flat_multiset_test
{

namespace insert_range_test
{

#if !defined(HAMON_USE_STD_FLAT_SET)
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename Compare, template <typename> class RangeWrapper>
FLAT_SET_TEST_CONSTEXPR bool test_impl()
{
	using Key = typename KeyContainer::value_type;
	using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;
	using ValueType = typename Set::value_type;
	using Range = RangeWrapper<ValueType>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().insert_range(hamon::declval<Range const&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().insert_range(hamon::declval<Range&&>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().insert_range(hamon::declval<Range const&>())), "");
	static_assert(!noexcept(hamon::declval<Set&>().insert_range(hamon::declval<Range&&>())), "");

	{
		Set v;
		VERIFY(check_invariant(v));
		{
			ValueType a[] =
			{
				Key{1},
				Key{3},
				Key{2},
				Key{1},
			};
			Range r(a);
			v.insert_range(r);
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 4);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 2);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 0);
		VERIFY(v.count(Key{5}) == 0);
		{
			ValueType a[] =
			{
				Key{5},
				Key{1},
				Key{2},
				Key{4},
				Key{4},
			};
			v.insert_range(Range(a));
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 9);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 3);
		VERIFY(v.count(Key{2}) == 2);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 2);
		VERIFY(v.count(Key{5}) == 1);
	}

	return true;
}

template <typename KeyContainer, typename Compare>
FLAT_SET_TEST_CONSTEXPR bool test()
{
	VERIFY(test_impl<KeyContainer, Compare, test_input_range>());
	VERIFY(test_impl<KeyContainer, Compare, test_forward_range>());
	VERIFY(test_impl<KeyContainer, Compare, test_bidirectional_range>());
	VERIFY(test_impl<KeyContainer, Compare, test_random_access_range>());
	VERIFY(test_impl<KeyContainer, Compare, test_contiguous_range>());
	VERIFY(test_impl<KeyContainer, Compare, test_input_sized_range>());
	VERIFY(test_impl<KeyContainer, Compare, test_forward_sized_range>());
	VERIFY(test_impl<KeyContainer, Compare, test_bidirectional_sized_range>());
	VERIFY(test_impl<KeyContainer, Compare, test_random_access_sized_range>());
	VERIFY(test_impl<KeyContainer, Compare, test_contiguous_sized_range>());

	return true;
}

#undef VERIFY

template <template <typename...> class TKeyContainer>
void test_exceptions()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	using Key = int;
	using Comp = hamon::less<Key>;
	{
		using KeyContainer = TKeyContainer<Key, ThrowAllocator<Key>>;
		using Set = hamon::flat_multiset<Key, Comp, KeyContainer>;
		using ValueType = typename Set::value_type;

		int throw_after = INT_MAX;

		KeyContainer a({Key{1}, Key{2}, Key{3}, Key{4}}, ThrowAllocator<Key>{&throw_after});
		Set v(hamon::sorted_equivalent, hamon::move(a));

		throw_after = 1;

		ValueType x[] =
		{
			Key{11},
			Key{13},
			Key{12},
			Key{15},
			Key{16},
			Key{17},
		};
		EXPECT_THROW(v.insert_range(x), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = EmplaceUnsafeContainer<Key>;
		using Set = hamon::flat_multiset<Key, Comp, KeyContainer>;
		using ValueType = typename Set::value_type;

		KeyContainer a{Key{1}, Key{2}, Key{3}, Key{4}};
		Set v(hamon::sorted_equivalent, hamon::move(a));

		ValueType x[] =
		{
			Key{11},
			Key{13},
			Key{12},
			Key{15},
			Key{16},
			Key{17},
		};
		EXPECT_THROW(v.insert_range(x), int);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatMultisetTest, InsertRangeTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::less<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::less<>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, hamon::less<int>>()));

	test_exceptions<hamon::vector>();
	test_exceptions<hamon::deque>();

	{
		hamon::flat_multiset<int> fs = {3};

		hamon::flat_multiset<int> fs2 = {5, 15};

		fs.insert_range(fs2);

		std::stringstream ss;
		for (int i : fs)
		{
			ss << i << ", ";
		}
		EXPECT_EQ("3, 5, 15, ", ss.str());
	}
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace insert_range_test

}	// namespace hamon_flat_multiset_test
