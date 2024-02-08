/**
 *	@file	unit_test_basic_const_iterator_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<sentinel_for<Iterator> S>
 *	constexpr bool operator==(const S& s) const;
 *	
 *	constexpr bool operator<(const basic_const_iterator& y) const
 *		requires random_access_iterator<Iterator>;
 *	constexpr bool operator>(const basic_const_iterator& y) const
 *		requires random_access_iterator<Iterator>;
 *	constexpr bool operator<=(const basic_const_iterator& y) const
 *		requires random_access_iterator<Iterator>;
 *	constexpr bool operator>=(const basic_const_iterator& y) const
 *		requires random_access_iterator<Iterator>;
 *	constexpr auto operator<=>(const basic_const_iterator& y) const
 *		requires random_access_iterator<Iterator> && three_way_comparable<Iterator>;
 *	
 *	template<different-from<basic_const_iterator> I>
 *	constexpr bool operator<(const I& y) const
 *		requires random_access_iterator<Iterator> && totally_ordered_with<Iterator, I>;
 *	template<different-from<basic_const_iterator> I>
 *	constexpr bool operator>(const I& y) const
 *		requires random_access_iterator<Iterator> && totally_ordered_with<Iterator, I>;
 *	template<different-from<basic_const_iterator> I>
 *	constexpr bool operator<=(const I& y) const
 *		requires random_access_iterator<Iterator> && totally_ordered_with<Iterator, I>;
 *	template<different-from<basic_const_iterator> I>
 *	constexpr bool operator>=(const I& y) const
 *		requires random_access_iterator<Iterator> && totally_ordered_with<Iterator, I>;
 *	template<different-from<basic_const_iterator> I>
 *	constexpr auto operator<=>(const I& y) const
 *		requires random_access_iterator<Iterator> && totally_ordered_with<Iterator, I> &&
 *	            three_way_comparable_with<Iterator, I>;
 *	template<not-a-const-iterator I>
 *	friend constexpr bool operator<(const I& x, const basic_const_iterator& y)
 *		requires random_access_iterator<Iterator> && totally_ordered_with<Iterator, I>;
 *	template<not-a-const-iterator I>
 *	friend constexpr bool operator>(const I& x, const basic_const_iterator& y)
 *		requires random_access_iterator<Iterator> && totally_ordered_with<Iterator, I>;
 *	template<not-a-const-iterator I>
 *	friend constexpr bool operator<=(const I& x, const basic_const_iterator& y)
 *		requires random_access_iterator<Iterator> && totally_ordered_with<Iterator, I>;
 *	template<not-a-const-iterator I>
 *	friend constexpr bool operator>=(const I& x, const basic_const_iterator& y)
 *		requires random_access_iterator<Iterator> && totally_ordered_with<Iterator, I>;
 */

#include <hamon/iterator/basic_const_iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/concepts.hpp>
#include <hamon/concepts/detail/weakly_equality_comparable_with.hpp>
#include <hamon/compare.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"
#include "ranges_test.hpp"

namespace hamon_iterator_test
{

namespace basic_const_iterator_test
{

namespace compare_test
{

static_assert( hamon::equality_comparable_t<hamon::basic_const_iterator<input_iterator_wrapper<int>>>::value, "");
static_assert( hamon::equality_comparable_t<hamon::basic_const_iterator<forward_iterator_wrapper<int>>>::value, "");
static_assert( hamon::equality_comparable_t<hamon::basic_const_iterator<bidirectional_iterator_wrapper<int>>>::value, "");
static_assert( hamon::equality_comparable_t<hamon::basic_const_iterator<random_access_iterator_wrapper<int>>>::value, "");
static_assert( hamon::equality_comparable_t<hamon::basic_const_iterator<contiguous_iterator_wrapper<int>>>::value, "");

static_assert(!hamon::totally_ordered_t<hamon::basic_const_iterator<input_iterator_wrapper<int>>>::value, "");
static_assert(!hamon::totally_ordered_t<hamon::basic_const_iterator<forward_iterator_wrapper<int>>>::value, "");
static_assert(!hamon::totally_ordered_t<hamon::basic_const_iterator<bidirectional_iterator_wrapper<int>>>::value, "");
static_assert( hamon::totally_ordered_t<hamon::basic_const_iterator<random_access_iterator_wrapper<int>>>::value, "");
static_assert( hamon::totally_ordered_t<hamon::basic_const_iterator<contiguous_iterator_wrapper<int>>>::value, "");

static_assert(!hamon::equality_comparable_with_t<hamon::basic_const_iterator<input_iterator_wrapper<int>>, forward_iterator_wrapper<int>>::value, "");
static_assert( hamon::equality_comparable_with_t<hamon::basic_const_iterator<input_iterator_wrapper<int>>, input_iterator_wrapper<int>>::value, "");
static_assert( hamon::equality_comparable_with_t<hamon::basic_const_iterator<forward_iterator_wrapper<int>>, forward_iterator_wrapper<int>>::value, "");
static_assert( hamon::equality_comparable_with_t<hamon::basic_const_iterator<bidirectional_iterator_wrapper<int>>, bidirectional_iterator_wrapper<int>>::value, "");
static_assert( hamon::equality_comparable_with_t<hamon::basic_const_iterator<random_access_iterator_wrapper<int>>, random_access_iterator_wrapper<int>>::value, "");
static_assert( hamon::equality_comparable_with_t<hamon::basic_const_iterator<contiguous_iterator_wrapper<int>>, contiguous_iterator_wrapper<int>>::value, "");

static_assert(!hamon::totally_ordered_with_t<hamon::basic_const_iterator<input_iterator_wrapper<int>>, input_iterator_wrapper<int>>::value, "");
static_assert(!hamon::totally_ordered_with_t<hamon::basic_const_iterator<forward_iterator_wrapper<int>>, forward_iterator_wrapper<int>>::value, "");
static_assert(!hamon::totally_ordered_with_t<hamon::basic_const_iterator<bidirectional_iterator_wrapper<int>>, bidirectional_iterator_wrapper<int>>::value, "");
static_assert( hamon::totally_ordered_with_t<hamon::basic_const_iterator<random_access_iterator_wrapper<int>>, random_access_iterator_wrapper<int>>::value, "");
static_assert( hamon::totally_ordered_with_t<hamon::basic_const_iterator<contiguous_iterator_wrapper<int>>, contiguous_iterator_wrapper<int>>::value, "");

static_assert(!hamon::equality_comparable_with_t<forward_iterator_wrapper<int>, hamon::basic_const_iterator<input_iterator_wrapper<int>>>::value, "");
static_assert( hamon::equality_comparable_with_t<input_iterator_wrapper<int>, hamon::basic_const_iterator<input_iterator_wrapper<int>>>::value, "");
static_assert( hamon::equality_comparable_with_t<forward_iterator_wrapper<int>, hamon::basic_const_iterator<forward_iterator_wrapper<int>>>::value, "");
static_assert( hamon::equality_comparable_with_t<bidirectional_iterator_wrapper<int>, hamon::basic_const_iterator<bidirectional_iterator_wrapper<int>>>::value, "");
static_assert( hamon::equality_comparable_with_t<random_access_iterator_wrapper<int>, hamon::basic_const_iterator<random_access_iterator_wrapper<int>>>::value, "");
static_assert( hamon::equality_comparable_with_t<contiguous_iterator_wrapper<int>, hamon::basic_const_iterator<contiguous_iterator_wrapper<int>>>::value, "");

static_assert(!hamon::totally_ordered_with_t<input_iterator_wrapper<int>, hamon::basic_const_iterator<input_iterator_wrapper<int>>>::value, "");
static_assert(!hamon::totally_ordered_with_t<forward_iterator_wrapper<int>, hamon::basic_const_iterator<forward_iterator_wrapper<int>>>::value, "");
static_assert(!hamon::totally_ordered_with_t<bidirectional_iterator_wrapper<int>, hamon::basic_const_iterator<bidirectional_iterator_wrapper<int>>>::value, "");
static_assert( hamon::totally_ordered_with_t<random_access_iterator_wrapper<int>, hamon::basic_const_iterator<random_access_iterator_wrapper<int>>>::value, "");
static_assert( hamon::totally_ordered_with_t<contiguous_iterator_wrapper<int>, hamon::basic_const_iterator<contiguous_iterator_wrapper<int>>>::value, "");

static_assert( hamon::detail::weakly_equality_comparable_with_t<hamon::basic_const_iterator<input_iterator_wrapper<int>>, test_sentinel<input_iterator_wrapper<int>>>::value, "");
static_assert( hamon::detail::weakly_equality_comparable_with_t<hamon::basic_const_iterator<forward_iterator_wrapper<int>>, test_sentinel<forward_iterator_wrapper<int>>>::value, "");
static_assert( hamon::detail::weakly_equality_comparable_with_t<hamon::basic_const_iterator<bidirectional_iterator_wrapper<int>>, test_sentinel<bidirectional_iterator_wrapper<int>>>::value, "");
static_assert( hamon::detail::weakly_equality_comparable_with_t<hamon::basic_const_iterator<random_access_iterator_wrapper<int>>, test_sentinel<random_access_iterator_wrapper<int>>>::value, "");
static_assert( hamon::detail::weakly_equality_comparable_with_t<hamon::basic_const_iterator<contiguous_iterator_wrapper<int>>, test_sentinel<contiguous_iterator_wrapper<int>>>::value, "");
static_assert(!hamon::detail::weakly_equality_comparable_with_t<hamon::basic_const_iterator<input_iterator_wrapper<int>>, test_sentinel<forward_iterator_wrapper<int>>>::value, "");
static_assert(!hamon::detail::weakly_equality_comparable_with_t<hamon::basic_const_iterator<input_iterator_wrapper<int>>, test_sentinel<input_iterator_wrapper<int const>>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test01()
{
	using Iter = input_iterator_wrapper<int>;
	int a[3] = {3, 1, 4};
	Iter it1{&a[0]};
	Iter it2{&a[1]};
	hamon::basic_const_iterator<Iter> ci1{it1};
	hamon::basic_const_iterator<Iter> ci2{it1};
	hamon::basic_const_iterator<Iter> ci3{it2};

	VERIFY( (ci1 == ci1));
	VERIFY( (ci1 == ci2));
	VERIFY(!(ci1 == ci3));

	VERIFY(!(ci1 != ci1));
	VERIFY(!(ci1 != ci2));
	VERIFY( (ci1 != ci3));

	VERIFY( (ci1 == it1));
	VERIFY(!(ci1 == it2));
	VERIFY(!(ci3 == it1));
	VERIFY( (ci3 == it2));

	VERIFY( (it1 == ci1));
	VERIFY(!(it1 == ci3));
	VERIFY(!(it2 == ci1));
	VERIFY( (it2 == ci3));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using Iter = random_access_iterator_wrapper<int>;
	int a[3] = {3, 1, 4};
	Iter it1{&a[0]};
	Iter it2{&a[1]};
	hamon::basic_const_iterator<Iter> ci1{it1};
	hamon::basic_const_iterator<Iter> ci2{it2};

	VERIFY( (ci1 == ci1));
	VERIFY(!(ci1 == ci2));
	VERIFY(!(ci1 != ci1));
	VERIFY( (ci1 != ci2));
	VERIFY(!(ci1 <  ci1));
	VERIFY( (ci1 <  ci2));
	VERIFY( (ci1 <= ci1));
	VERIFY( (ci1 <= ci2));
	VERIFY(!(ci1 >  ci1));
	VERIFY(!(ci1 >  ci2));
	VERIFY( (ci1 >= ci1));
	VERIFY(!(ci1 >= ci2));

	VERIFY(!(ci2 == ci1));
	VERIFY( (ci2 == ci2));
	VERIFY( (ci2 != ci1));
	VERIFY(!(ci2 != ci2));
	VERIFY(!(ci2 <  ci1));
	VERIFY(!(ci2 <  ci2));
	VERIFY(!(ci2 <= ci1));
	VERIFY( (ci2 <= ci2));
	VERIFY( (ci2 >  ci1));
	VERIFY(!(ci2 >  ci2));
	VERIFY( (ci2 >= ci1));
	VERIFY( (ci2 >= ci2));

	VERIFY( (ci1 == it1));
	VERIFY(!(ci1 == it2));
	VERIFY(!(ci1 != it1));
	VERIFY( (ci1 != it2));
	VERIFY(!(ci1 <  it1));
	VERIFY( (ci1 <  it2));
	VERIFY( (ci1 <= it1));
	VERIFY( (ci1 <= it2));
	VERIFY(!(ci1 >  it1));
	VERIFY(!(ci1 >  it2));
	VERIFY( (ci1 >= it1));
	VERIFY(!(ci1 >= it2));

	VERIFY( (it1 == ci1));
	VERIFY(!(it1 == ci2));
	VERIFY(!(it1 != ci1));
	VERIFY( (it1 != ci2));
	VERIFY(!(it1 <  ci1));
	VERIFY( (it1 <  ci2));
	VERIFY( (it1 <= ci1));
	VERIFY( (it1 <= ci2));
	VERIFY(!(it1 >  ci1));
	VERIFY(!(it1 >  ci2));
	VERIFY( (it1 >= ci1));
	VERIFY(!(it1 >= ci2));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	using Iter = int*;
	int a[3] = {3, 1, 4};
	Iter it1{&a[0]};
	Iter it2{&a[1]};
	hamon::basic_const_iterator<Iter> ci1{it1};
	hamon::basic_const_iterator<Iter> ci2{it2};

	VERIFY( (ci1 == ci1));
	VERIFY(!(ci1 == ci2));
	VERIFY(!(ci1 != ci1));
	VERIFY( (ci1 != ci2));
	VERIFY(!(ci1 <  ci1));
	VERIFY( (ci1 <  ci2));
	VERIFY( (ci1 <= ci1));
	VERIFY( (ci1 <= ci2));
	VERIFY(!(ci1 >  ci1));
	VERIFY(!(ci1 >  ci2));
	VERIFY( (ci1 >= ci1));
	VERIFY(!(ci1 >= ci2));

	VERIFY(!(ci2 == ci1));
	VERIFY( (ci2 == ci2));
	VERIFY( (ci2 != ci1));
	VERIFY(!(ci2 != ci2));
	VERIFY(!(ci2 <  ci1));
	VERIFY(!(ci2 <  ci2));
	VERIFY(!(ci2 <= ci1));
	VERIFY( (ci2 <= ci2));
	VERIFY( (ci2 >  ci1));
	VERIFY(!(ci2 >  ci2));
	VERIFY( (ci2 >= ci1));
	VERIFY( (ci2 >= ci2));

	VERIFY( (ci1 == it1));
	VERIFY(!(ci1 == it2));
	VERIFY(!(ci1 != it1));
	VERIFY( (ci1 != it2));
	VERIFY(!(ci1 <  it1));
	VERIFY( (ci1 <  it2));
	VERIFY( (ci1 <= it1));
	VERIFY( (ci1 <= it2));
	VERIFY(!(ci1 >  it1));
	VERIFY(!(ci1 >  it2));
	VERIFY( (ci1 >= it1));
	VERIFY(!(ci1 >= it2));

	VERIFY( (it1 == ci1));
	VERIFY(!(it1 == ci2));
	VERIFY(!(it1 != ci1));
	VERIFY( (it1 != ci2));
	VERIFY(!(it1 <  ci1));
	VERIFY( (it1 <  ci2));
	VERIFY( (it1 <= ci1));
	VERIFY( (it1 <= ci2));
	VERIFY(!(it1 >  ci1));
	VERIFY(!(it1 >  ci2));
	VERIFY( (it1 >= ci1));
	VERIFY(!(it1 >= ci2));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY(hamon::is_eq(ci1 <=> ci1));
	VERIFY(hamon::is_lt(ci1 <=> ci2));
	VERIFY(hamon::is_eq(ci1 <=> it1));
	VERIFY(hamon::is_lt(ci1 <=> it2));
	VERIFY(hamon::is_eq(it1 <=> ci1));
	VERIFY(hamon::is_lt(it1 <=> ci2));
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(BasicConstIteratorTest, compareTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace compare_test

}	// namespace basic_const_iterator_test

}	// namespace hamon_iterator_test
