/**
 *	@file	unit_test_flat_multiset_iterator.cpp
 *
 *	@brief	iterator のテスト
 */

#include <hamon/flat_set/flat_multiset.hpp>
#include <hamon/compare.hpp>
#include <hamon/concepts.hpp>
#include <hamon/functional.hpp>
#include <hamon/iterator.hpp>
#include <hamon/utility.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_multiset_test_helper.hpp"

namespace hamon_flat_multiset_test
{

namespace iterator_test
{

#if !defined(HAMON_USE_STD_FLAT_SET)
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer>
FLAT_SET_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Set = hamon::flat_multiset<Key, hamon::less<Key>, KeyContainer>;
	using value_type      = typename Set::value_type;
	using const_reference = typename Set::const_reference;
	using difference_type = typename Set::difference_type;
	using iterator        = typename Set::iterator;
	using const_iterator  = typename Set::const_iterator;

	static_assert( hamon::detail::cpp17_input_iterator_t<iterator>::value, "");
	static_assert( hamon::detail::cpp17_forward_iterator_t<iterator>::value, "");
	static_assert( hamon::detail::cpp17_bidirectional_iterator_t<iterator>::value, "");
	static_assert( hamon::detail::cpp17_random_access_iterator_t<iterator>::value, "");
	static_assert( hamon::input_iterator_t<iterator>::value, "");
	static_assert( hamon::forward_iterator_t<iterator>::value, "");
	static_assert( hamon::bidirectional_iterator_t<iterator>::value, "");
	static_assert( hamon::random_access_iterator_t<iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<iterator>::value, "");
	static_assert(hamon::is_same<value_type, hamon::iter_value_t<iterator>>::value, "");
	static_assert(!hamon::is_same<value_type&, hamon::iter_reference_t<iterator>>::value, "");
	static_assert(hamon::is_same<const_reference, hamon::iter_reference_t<iterator>>::value, "");
	static_assert(hamon::is_same<difference_type, hamon::iter_difference_t<iterator>>::value, "");
	static_assert(hamon::is_default_constructible<iterator>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<iterator>::value, "");
	static_assert(!hamon::is_constructible<iterator, value_type*>::value, "");
	static_assert(!hamon::is_constructible<iterator, value_type const*>::value, "");
	static_assert(hamon::is_same<value_type const&, decltype(*hamon::declval<iterator const&>())>::value, "");
	static_assert(hamon::is_same<value_type const*, decltype(hamon::declval<iterator const&>().operator->())>::value, "");
	static_assert(hamon::is_same<iterator&, decltype(++hamon::declval<iterator&>())>::value, "");
	static_assert(hamon::is_same<iterator,  decltype(hamon::declval<iterator&>()++)>::value, "");
	static_assert(hamon::is_same<iterator&, decltype(--hamon::declval<iterator&>())>::value, "");
	static_assert(hamon::is_same<iterator,  decltype(hamon::declval<iterator&>()--)>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<iterator const&>() == (hamon::declval<iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<iterator const&>() != (hamon::declval<iterator const&>()))>::value, "");

	static_assert( hamon::detail::cpp17_input_iterator_t<const_iterator>::value, "");
	static_assert( hamon::detail::cpp17_forward_iterator_t<const_iterator>::value, "");
	static_assert( hamon::detail::cpp17_bidirectional_iterator_t<const_iterator>::value, "");
	static_assert( hamon::detail::cpp17_random_access_iterator_t<const_iterator>::value, "");
	static_assert( hamon::input_iterator_t<const_iterator>::value, "");
	static_assert( hamon::forward_iterator_t<const_iterator>::value, "");
	static_assert( hamon::bidirectional_iterator_t<const_iterator>::value, "");
	static_assert( hamon::random_access_iterator_t<const_iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<const_iterator>::value, "");
	static_assert(hamon::is_same<value_type, hamon::iter_value_t<const_iterator>>::value, "");
	static_assert(!hamon::is_same<value_type&, hamon::iter_reference_t<const_iterator>>::value, "");
	static_assert(hamon::is_same<const_reference, hamon::iter_reference_t<const_iterator>>::value, "");
	static_assert(hamon::is_same<difference_type, hamon::iter_difference_t<const_iterator>>::value, "");
	static_assert(hamon::is_default_constructible<const_iterator>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<const_iterator>::value, "");
	static_assert(!hamon::is_constructible<const_iterator, value_type*>::value, "");
	static_assert(!hamon::is_constructible<const_iterator, value_type const*>::value, "");
	static_assert(hamon::is_same<value_type const&, decltype(*hamon::declval<const_iterator const&>())>::value, "");
	static_assert(hamon::is_same<value_type const*, decltype(hamon::declval<const_iterator const&>().operator->())>::value, "");
	static_assert(hamon::is_same<const_iterator&, decltype(++hamon::declval<const_iterator&>())>::value, "");
	static_assert(hamon::is_same<const_iterator,  decltype(hamon::declval<const_iterator&>()++)>::value, "");
	static_assert(hamon::is_same<const_iterator&, decltype(--hamon::declval<const_iterator&>())>::value, "");
	static_assert(hamon::is_same<const_iterator,  decltype(hamon::declval<const_iterator&>()--)>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<const_iterator const&>() == (hamon::declval<const_iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<const_iterator const&>() != (hamon::declval<const_iterator const&>()))>::value, "");

	static_assert( hamon::is_constructible<iterator,       iterator>::value, "");
	static_assert( hamon::is_constructible<iterator,       const_iterator>::value, "");
	static_assert( hamon::is_constructible<const_iterator, iterator>::value, "");
	static_assert( hamon::is_constructible<const_iterator, const_iterator>::value, "");

	{
		Set v
		{
			Key{3},
			Key{6},
			Key{1},
			Key{4},
		};

		iterator i;
		i = v.begin();
		const_iterator ci = i;
		VERIFY(i == ci);
		VERIFY(*i == Key{1});
		VERIFY(i[0] == Key{1});
		VERIFY(i[1] == Key{3});
		VERIFY(i[2] == Key{4});
		VERIFY(i[3] == Key{6});
		{
			auto t = ++i;
			VERIFY(*t == Key{3});
		}
		VERIFY(*i == Key{3});
		{
			auto t = i++;
			VERIFY(*t == Key{3});
		}
		VERIFY(*i == Key{4});
		VERIFY(i[1] == Key{6});
		{
			auto t = i--;
			VERIFY(*t == Key{4});
		}
		VERIFY(*i == Key{3});
		{
			auto t = --i;
			VERIFY(*t == Key{1});
		}
		VERIFY(*i == Key{1});
		i += 3;
		VERIFY(*i == Key{6});
		i -= 2;
		VERIFY(*i == Key{3});
		auto j = i + 2;
		VERIFY(*j == Key{6});
		auto k = 1 + i;
		VERIFY(*k == Key{4});
		auto l = j - 1;
		VERIFY(*l == Key{4});
		auto d = j - l;
		VERIFY(d == 1);

		VERIFY(!(l == i));
		VERIFY(!(l == j));
		VERIFY( (l == k));

		VERIFY( (l != i));
		VERIFY( (l != j));
		VERIFY(!(l != k));

		VERIFY(!(l <  i));
		VERIFY( (l <  j));
		VERIFY(!(l <  k));

		VERIFY( (l >  i));
		VERIFY(!(l >  j));
		VERIFY(!(l >  k));

		VERIFY(!(l <= i));
		VERIFY( (l <= j));
		VERIFY( (l <= k));

		VERIFY( (l >= i));
		VERIFY(!(l >= j));
		VERIFY( (l >= k));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		VERIFY(!hamon::is_eq(l <=> i));
		VERIFY(!hamon::is_eq(l <=> j));
		VERIFY( hamon::is_eq(l <=> k));

		VERIFY(!hamon::is_lt(l <=> i));
		VERIFY( hamon::is_lt(l <=> j));
		VERIFY(!hamon::is_lt(l <=> k));

		VERIFY( hamon::is_gt(l <=> i));
		VERIFY(!hamon::is_gt(l <=> j));
		VERIFY(!hamon::is_gt(l <=> k));
#endif
	}
	{
		iterator ii1 {};
		iterator ii2 {};
		iterator ii4 = ii1;
		const_iterator cii {};
		VERIFY(ii1 == ii2);
		VERIFY(ii1 == ii4);
		VERIFY(!(ii1 != ii2));

		VERIFY((ii1 == cii));
		VERIFY((cii == ii1));
		VERIFY(!(ii1 != cii));
		VERIFY(!(cii != ii1));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultisetTest, IteratorTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<char>>()));
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace iterator_test

}	// namespace hamon_flat_multiset_test
