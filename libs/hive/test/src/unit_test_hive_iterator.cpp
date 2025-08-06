/**
 *	@file	unit_test_hive_iterator.cpp
 *
 *	@brief	iterator, const_iterator のテスト
 */

#include <hamon/hive.hpp>
#include <hamon/compare.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace iterator_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;
	using difference_type = typename Hive::difference_type;
	using iterator = typename Hive::iterator;
	using const_iterator = typename Hive::const_iterator;

	static_assert( hamon::detail::cpp17_input_iterator_t<iterator>::value, "");
	static_assert( hamon::detail::cpp17_forward_iterator_t<iterator>::value, "");
	static_assert( hamon::detail::cpp17_bidirectional_iterator_t<iterator>::value, "");
	static_assert(!hamon::detail::cpp17_random_access_iterator_t<iterator>::value, "");
	static_assert( hamon::input_iterator_t<iterator>::value, "");
	static_assert( hamon::forward_iterator_t<iterator>::value, "");
	static_assert( hamon::bidirectional_iterator_t<iterator>::value, "");
	static_assert(!hamon::random_access_iterator_t<iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<iterator>::value, "");
	static_assert(hamon::is_same<T, hamon::iter_value_t<iterator>>::value, "");
	static_assert(hamon::is_same<T&, hamon::iter_reference_t<iterator>>::value, "");
	static_assert(hamon::is_same<difference_type, hamon::iter_difference_t<iterator>>::value, "");
	static_assert(hamon::is_default_constructible<iterator>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<iterator>::value, "");
	static_assert(!hamon::is_constructible<iterator, T*>::value, "");
	static_assert(!hamon::is_constructible<iterator, T const*>::value, "");
	static_assert(hamon::is_same<T&, decltype(*hamon::declval<iterator const&>())>::value, "");
	static_assert(hamon::is_same<T*, decltype(hamon::declval<iterator const&>().operator->())>::value, "");
	static_assert(hamon::is_same<iterator&, decltype(++hamon::declval<iterator&>())>::value, "");
	static_assert(hamon::is_same<iterator,  decltype(hamon::declval<iterator&>()++)>::value, "");
	static_assert(hamon::is_same<iterator&, decltype(--hamon::declval<iterator&>())>::value, "");
	static_assert(hamon::is_same<iterator,  decltype(hamon::declval<iterator&>()--)>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<iterator const&>() == (hamon::declval<iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<iterator const&>() != (hamon::declval<iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<iterator const&>() <  (hamon::declval<iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<iterator const&>() >  (hamon::declval<iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<iterator const&>() <= (hamon::declval<iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<iterator const&>() >= (hamon::declval<iterator const&>()))>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(hamon::is_same<hamon::strong_ordering, decltype(hamon::declval<iterator const&>() <=> (hamon::declval<iterator const&>()))>::value, "");
	static_assert(hamon::three_way_comparable<iterator>, "");
#endif

	static_assert( hamon::detail::cpp17_input_iterator_t<const_iterator>::value, "");
	static_assert( hamon::detail::cpp17_forward_iterator_t<const_iterator>::value, "");
	static_assert( hamon::detail::cpp17_bidirectional_iterator_t<const_iterator>::value, "");
	static_assert(!hamon::detail::cpp17_random_access_iterator_t<const_iterator>::value, "");
	static_assert( hamon::input_iterator_t<const_iterator>::value, "");
	static_assert( hamon::forward_iterator_t<const_iterator>::value, "");
	static_assert( hamon::bidirectional_iterator_t<const_iterator>::value, "");
	static_assert(!hamon::random_access_iterator_t<const_iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<const_iterator>::value, "");
	static_assert(hamon::is_same<T, hamon::iter_value_t<const_iterator>>::value, "");
	static_assert(hamon::is_same<T const&, hamon::iter_reference_t<const_iterator>>::value, "");
	static_assert(hamon::is_same<difference_type, hamon::iter_difference_t<const_iterator>>::value, "");
	static_assert(hamon::is_default_constructible<const_iterator>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<const_iterator>::value, "");
	static_assert(!hamon::is_constructible<const_iterator, T*>::value, "");
	static_assert(!hamon::is_constructible<const_iterator, T const*>::value, "");
	static_assert(hamon::is_same<T const&, decltype(*hamon::declval<const_iterator const&>())>::value, "");
	static_assert(hamon::is_same<T const*, decltype(hamon::declval<const_iterator const&>().operator->())>::value, "");
	static_assert(hamon::is_same<const_iterator&, decltype(++hamon::declval<const_iterator&>())>::value, "");
	static_assert(hamon::is_same<const_iterator,  decltype(hamon::declval<const_iterator&>()++)>::value, "");
	static_assert(hamon::is_same<const_iterator&, decltype(--hamon::declval<const_iterator&>())>::value, "");
	static_assert(hamon::is_same<const_iterator,  decltype(hamon::declval<const_iterator&>()--)>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<const_iterator const&>() == (hamon::declval<const_iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<const_iterator const&>() != (hamon::declval<const_iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<const_iterator const&>() <  (hamon::declval<const_iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<const_iterator const&>() >  (hamon::declval<const_iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<const_iterator const&>() <= (hamon::declval<const_iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<const_iterator const&>() >= (hamon::declval<const_iterator const&>()))>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(hamon::is_same<hamon::strong_ordering, decltype(hamon::declval<const_iterator const&>() <=> (hamon::declval<const_iterator const&>()))>::value, "");
	static_assert(hamon::three_way_comparable<const_iterator>, "");
#endif

	static_assert( hamon::is_constructible<iterator,       iterator>::value, "");
	static_assert(!hamon::is_constructible<iterator,       const_iterator>::value, "");
	static_assert( hamon::is_constructible<const_iterator, iterator>::value, "");
	static_assert( hamon::is_constructible<const_iterator, const_iterator>::value, "");

	{
		iterator it1{};
		iterator it2{};
		VERIFY( (it1 == it2));
		VERIFY(!(it1 != it2));
		VERIFY(!(it1 <  it2));
		VERIFY(!(it1 >  it2));
		VERIFY( (it1 <= it2));
		VERIFY( (it1 >= it2));
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		VERIFY( hamon::is_eq(it1 <=> it2));
		VERIFY(!hamon::is_lt(it1 <=> it2));
		VERIFY(!hamon::is_gt(it1 <=> it2));
#endif
	}
	{
		const_iterator it1{};
		const_iterator it2{};
		VERIFY( (it1 == it2));
		VERIFY(!(it1 != it2));
		VERIFY(!(it1 <  it2));
		VERIFY(!(it1 >  it2));
		VERIFY( (it1 <= it2));
		VERIFY( (it1 >= it2));
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		VERIFY( hamon::is_eq(it1 <=> it2));
		VERIFY(!hamon::is_lt(it1 <=> it2));
		VERIFY(!hamon::is_gt(it1 <=> it2));
#endif
	}
	{
		Hive v(100, T{42});
		for (auto it = v.begin(); it != v.end(); ++it)
		{
			VERIFY(*it == T{42});

			auto next = hamon::next(it);
			VERIFY(!(it == next));
			VERIFY( (it != next));
			VERIFY( (it <  next));
			VERIFY(!(it >  next));
			VERIFY( (it <= next));
			VERIFY(!(it >= next));
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
			VERIFY(!hamon::is_eq(it <=> next));
			VERIFY( hamon::is_lt(it <=> next));
			VERIFY(!hamon::is_gt(it <=> next));
#endif

			if (it != v.begin())
			{
				auto prev = hamon::prev(it);
				VERIFY(!(it == prev));
				VERIFY( (it != prev));
				VERIFY(!(it <  prev));
				VERIFY( (it >  prev));
				VERIFY(!(it <= prev));
				VERIFY( (it >= prev));
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
				VERIFY(!hamon::is_eq(it <=> prev));
				VERIFY(!hamon::is_lt(it <=> prev));
				VERIFY( hamon::is_gt(it <=> prev));
#endif
			}
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, IteratorTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace iterator_test

}	// namespace hamon_hive_test
