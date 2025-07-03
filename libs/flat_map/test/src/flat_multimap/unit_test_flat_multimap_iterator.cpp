/**
 *	@file	unit_test_flat_multimap_iterator.cpp
 *
 *	@brief	iterator のテスト
 */

#include <hamon/flat_map/flat_multimap.hpp>
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
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

namespace iterator_test
{

#if !defined(HAMON_USE_STD_FLAT_MAP)
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer>
FLAT_MAP_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map = hamon::flat_multimap<Key, T, hamon::less<Key>, KeyContainer, MappedContainer>;
	using value_type      = typename Map::value_type;
	using reference       = typename Map::reference;
	using const_reference = typename Map::const_reference;
	using difference_type = typename Map::difference_type;
	using iterator        = typename Map::iterator;
	using const_iterator  = typename Map::const_iterator;

	static_assert( hamon::detail::cpp17_input_iterator_t<iterator>::value, "");
	static_assert(!hamon::detail::cpp17_forward_iterator_t<iterator>::value, "");
	static_assert(!hamon::detail::cpp17_bidirectional_iterator_t<iterator>::value, "");
	static_assert(!hamon::detail::cpp17_random_access_iterator_t<iterator>::value, "");
	static_assert( hamon::input_iterator_t<iterator>::value, "");
	static_assert( hamon::forward_iterator_t<iterator>::value, "");
	static_assert( hamon::bidirectional_iterator_t<iterator>::value, "");
	static_assert( hamon::random_access_iterator_t<iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<iterator>::value, "");
	static_assert(hamon::is_same<value_type, hamon::iter_value_t<iterator>>::value, "");
	static_assert(!hamon::is_same<value_type&, hamon::iter_reference_t<iterator>>::value, "");
	static_assert(hamon::is_same<reference, hamon::iter_reference_t<iterator>>::value, "");
	static_assert(hamon::is_same<difference_type, hamon::iter_difference_t<iterator>>::value, "");
	static_assert(hamon::is_default_constructible<iterator>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<iterator>::value, "");
	static_assert(!hamon::is_constructible<iterator, value_type*>::value, "");
	static_assert(!hamon::is_constructible<iterator, value_type const*>::value, "");
	static_assert(!hamon::is_same<value_type&, decltype(*hamon::declval<iterator const&>())>::value, "");
	static_assert(hamon::is_same<reference, decltype(*hamon::declval<iterator const&>())>::value, "");
	static_assert(!hamon::is_same<value_type*, decltype(hamon::declval<iterator const&>().operator->())>::value, "");
	static_assert(hamon::is_same<iterator&, decltype(++hamon::declval<iterator&>())>::value, "");
	static_assert(hamon::is_same<iterator,  decltype(hamon::declval<iterator&>()++)>::value, "");
	static_assert(hamon::is_same<iterator&, decltype(--hamon::declval<iterator&>())>::value, "");
	static_assert(hamon::is_same<iterator,  decltype(hamon::declval<iterator&>()--)>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<iterator const&>() == (hamon::declval<iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<iterator const&>() != (hamon::declval<iterator const&>()))>::value, "");

	static_assert( hamon::detail::cpp17_input_iterator_t<const_iterator>::value, "");
	static_assert(!hamon::detail::cpp17_forward_iterator_t<const_iterator>::value, "");
	static_assert(!hamon::detail::cpp17_bidirectional_iterator_t<const_iterator>::value, "");
	static_assert(!hamon::detail::cpp17_random_access_iterator_t<const_iterator>::value, "");
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
	static_assert(!hamon::is_same<value_type&, decltype(*hamon::declval<const_iterator const&>())>::value, "");
	static_assert(hamon::is_same<const_reference, decltype(*hamon::declval<const_iterator const&>())>::value, "");
	static_assert(!hamon::is_same<value_type*, decltype(hamon::declval<const_iterator const&>().operator->())>::value, "");
	static_assert(hamon::is_same<const_iterator&, decltype(++hamon::declval<const_iterator&>())>::value, "");
	static_assert(hamon::is_same<const_iterator,  decltype(hamon::declval<const_iterator&>()++)>::value, "");
	static_assert(hamon::is_same<const_iterator&, decltype(--hamon::declval<const_iterator&>())>::value, "");
	static_assert(hamon::is_same<const_iterator,  decltype(hamon::declval<const_iterator&>()--)>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<const_iterator const&>() == (hamon::declval<const_iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<const_iterator const&>() != (hamon::declval<const_iterator const&>()))>::value, "");

	static_assert( hamon::is_constructible<iterator,       iterator>::value, "");
	static_assert(!hamon::is_constructible<iterator,       const_iterator>::value, "");
	static_assert( hamon::is_constructible<const_iterator, iterator>::value, "");
	static_assert( hamon::is_constructible<const_iterator, const_iterator>::value, "");

	{
		Map v
		{
			{Key{3}, T{10}},
			{Key{6}, T{20}},
			{Key{1}, T{30}},
			{Key{4}, T{40}},
		};

		iterator i;
		i = v.begin();
		const_iterator ci = i;
		VERIFY(i == ci);
		VERIFY(i->first == Key{1});
		VERIFY(i->second == T{30});
		VERIFY((*i).first == Key{1});
		VERIFY((*i).second == T{30});
		VERIFY(i[0].first == Key{1});
		VERIFY(i[1].first == Key{3});
		VERIFY(i[2].first == Key{4});
		VERIFY(i[3].first == Key{6});
		VERIFY(i[0].second == T{30});
		VERIFY(i[1].second == T{10});
		VERIFY(i[2].second == T{40});
		VERIFY(i[3].second == T{20});
		{
			auto t = ++i;
			VERIFY(t->first == Key{3});
			VERIFY(t->second == T{10});
		}
		VERIFY(i->first == Key{3});
		VERIFY(i->second == T{10});
		{
			auto t = i++;
			VERIFY(t->first == Key{3});
			VERIFY(t->second == T{10});
		}
		VERIFY(i->first == Key{4});
		VERIFY(i->second == T{40});
		VERIFY(i[1].first == Key{6});
		VERIFY(i[1].second == T{20});
		{
			auto t = i--;
			VERIFY(t->first == Key{4});
			VERIFY(t->second == T{40});
		}
		VERIFY(i->first == Key{3});
		VERIFY(i->second == T{10});
		{
			auto t = --i;
			VERIFY(t->first == Key{1});
			VERIFY(t->second == T{30});
		}
		VERIFY(i->first == Key{1});
		VERIFY(i->second == T{30});
		i += 3;
		VERIFY(i->first == Key{6});
		VERIFY(i->second == T{20});
		i -= 2;
		VERIFY(i->first == Key{3});
		VERIFY(i->second == T{10});
		auto j = i + 2;
		VERIFY(j->first == Key{6});
		VERIFY(j->second == T{20});
		auto k = 1 + i;
		VERIFY(k->first == Key{4});
		VERIFY(k->second == T{40});
		auto l = j - 1;
		VERIFY(l->first == Key{4});
		VERIFY(l->second == T{40});
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

GTEST_TEST(FlatMultimapTest, IteratorTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>>()));
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace iterator_test

}	// namespace hamon_flat_multimap_test
