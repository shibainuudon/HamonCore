/**
 *	@file	unit_test_vector_iterator.cpp
 *
 *	@brief	iterator のテスト
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/iterator.hpp>
#include <hamon/compare.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace iterator_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Vector = hamon::vector<T>;
	using difference_type = typename Vector::difference_type;
	using iterator      = typename Vector::iterator;
	using const_iterator = typename Vector::const_iterator;

	static_assert(hamon::detail::cpp17_random_access_iterator_t<iterator>::value, "");
	static_assert(hamon::contiguous_iterator_t<iterator>::value, "");
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
	static_assert(hamon::is_same<iterator&, decltype(hamon::declval<iterator&>()+=(hamon::declval<difference_type>()))>::value, "");
	static_assert(hamon::is_same<iterator&, decltype(hamon::declval<iterator&>()-=(hamon::declval<difference_type>()))>::value, "");
	static_assert(hamon::is_same<iterator,  decltype(hamon::declval<iterator const&>() + (hamon::declval<difference_type>()))>::value, "");
	static_assert(hamon::is_same<iterator,  decltype(hamon::declval<difference_type>() + (hamon::declval<iterator const&>()))>::value, "");
	static_assert(hamon::is_same<iterator,  decltype(hamon::declval<iterator const&>() - (hamon::declval<difference_type>()))>::value, "");
	static_assert(hamon::is_same<difference_type, decltype(hamon::declval<iterator const&>() - (hamon::declval<iterator const&>()))>::value, "");
	static_assert(hamon::is_same<T&, decltype(hamon::declval<iterator&>()[hamon::declval<difference_type>()])>::value, "");
	static_assert(hamon::is_same<T&, decltype(hamon::declval<iterator const&>()[hamon::declval<difference_type>()])>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<iterator const&>() == (hamon::declval<iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<iterator const&>() != (hamon::declval<iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<iterator const&>() <  (hamon::declval<iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<iterator const&>() >  (hamon::declval<iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<iterator const&>() <= (hamon::declval<iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<iterator const&>() >= (hamon::declval<iterator const&>()))>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(hamon::is_same<hamon::strong_ordering, decltype(hamon::declval<iterator const&>() <=> (hamon::declval<iterator const&>()))>::value, "");
#endif

	static_assert(hamon::detail::cpp17_random_access_iterator_t<const_iterator>::value, "");
	static_assert(hamon::contiguous_iterator_t<const_iterator>::value, "");
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
	static_assert(hamon::is_same<const_iterator&, decltype(hamon::declval<const_iterator&>()+=(hamon::declval<difference_type>()))>::value, "");
	static_assert(hamon::is_same<const_iterator&, decltype(hamon::declval<const_iterator&>()-=(hamon::declval<difference_type>()))>::value, "");
	static_assert(hamon::is_same<const_iterator,  decltype(hamon::declval<const_iterator const&>() + (hamon::declval<difference_type>()))>::value, "");
	static_assert(hamon::is_same<const_iterator,  decltype(hamon::declval<difference_type>() + (hamon::declval<const_iterator const&>()))>::value, "");
	static_assert(hamon::is_same<const_iterator,  decltype(hamon::declval<const_iterator const&>() - (hamon::declval<difference_type>()))>::value, "");
	static_assert(hamon::is_same<difference_type, decltype(hamon::declval<const_iterator const&>() - (hamon::declval<const_iterator const&>()))>::value, "");
	static_assert(hamon::is_same<T const&, decltype(hamon::declval<const_iterator&>()[hamon::declval<difference_type>()])>::value, "");
	static_assert(hamon::is_same<T const&, decltype(hamon::declval<const_iterator const&>()[hamon::declval<difference_type>()])>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<const_iterator const&>() == (hamon::declval<const_iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<const_iterator const&>() != (hamon::declval<const_iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<const_iterator const&>() <  (hamon::declval<const_iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<const_iterator const&>() >  (hamon::declval<const_iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<const_iterator const&>() <= (hamon::declval<const_iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<const_iterator const&>() >= (hamon::declval<const_iterator const&>()))>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(hamon::is_same<hamon::strong_ordering, decltype(hamon::declval<const_iterator const&>() <=> (hamon::declval<const_iterator const&>()))>::value, "");
#endif

	static_assert( hamon::is_constructible<iterator,       iterator>::value, "");
	static_assert(!hamon::is_constructible<iterator,       const_iterator>::value, "");
	static_assert( hamon::is_constructible<const_iterator, iterator>::value, "");
	static_assert( hamon::is_constructible<const_iterator, const_iterator>::value, "");

	{
		iterator it1{};
		iterator it2{};
		VERIFY(it1 == it2);
	}
	{
		Vector v{1,2,3};
		iterator it = v.begin();
		auto* p = it.operator->();
		VERIFY(*p == 1);
		VERIFY(it[0] == 1);
		VERIFY(it[1] == 2);
		VERIFY(it[2] == 3);
		VERIFY(*it == 1);
		*it = 10;
		auto& r1 = ++it;
		VERIFY(&r1 == &it);
		VERIFY(*it == 2);
		auto t1 = it++;
		VERIFY(*it == 3);
		VERIFY(*t1 == 2);
		auto& r2 = --it;
		VERIFY(&r2 == &it);
		VERIFY(*it == 2);
		auto t2 = it--;
		VERIFY(*it == 10);
		VERIFY(*t2 == 2);
		auto& r3 = it += 2;
		VERIFY(&r3 == &it);
		VERIFY(*it == 3);
		auto& r4 = it -= 2;
		VERIFY(&r4 == &it);
		VERIFY(*it == 10);

		iterator it1 = v.begin();
		iterator it2 = v.begin() + 1;
		iterator it3 = 1 + v.begin();
		iterator it4 = v.begin() + 2;
		VERIFY(!(it2 == it1));
		VERIFY( (it2 == it2));
		VERIFY( (it2 == it3));
		VERIFY(!(it2 == it4));
		VERIFY( (it2 != it1));
		VERIFY(!(it2 != it2));
		VERIFY(!(it2 != it3));
		VERIFY( (it2 != it4));
		VERIFY(!(it2 <  it1));
		VERIFY(!(it2 <  it2));
		VERIFY(!(it2 <  it3));
		VERIFY( (it2 <  it4));
		VERIFY( (it2 >  it1));
		VERIFY(!(it2 >  it2));
		VERIFY(!(it2 >  it3));
		VERIFY(!(it2 >  it4));
		VERIFY(!(it2 <= it1));
		VERIFY( (it2 <= it2));
		VERIFY( (it2 <= it3));
		VERIFY( (it2 <= it4));
		VERIFY( (it2 >= it1));
		VERIFY( (it2 >= it2));
		VERIFY( (it2 >= it3));
		VERIFY(!(it2 >= it4));
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		VERIFY(!hamon::is_eq(it2 <=> it1));
		VERIFY( hamon::is_eq(it2 <=> it2));
		VERIFY( hamon::is_eq(it2 <=> it3));
		VERIFY(!hamon::is_eq(it2 <=> it4));
		VERIFY(!hamon::is_lt(it2 <=> it1));
		VERIFY(!hamon::is_lt(it2 <=> it2));
		VERIFY(!hamon::is_lt(it2 <=> it3));
		VERIFY( hamon::is_lt(it2 <=> it4));
		VERIFY( hamon::is_gt(it2 <=> it1));
		VERIFY(!hamon::is_gt(it2 <=> it2));
		VERIFY(!hamon::is_gt(it2 <=> it3));
		VERIFY(!hamon::is_gt(it2 <=> it4));
#endif

		VERIFY(it1 == (it4 - 2));
		VERIFY((it4 - it1) == 2);
		VERIFY((it1 - it2) == -1);
	}
	{
		Vector v{1,2,3};
		const_iterator it = v.begin();
		auto* p = it.operator->();
		VERIFY(*p == 1);
		VERIFY(it[0] == 1);
		VERIFY(it[1] == 2);
		VERIFY(it[2] == 3);
		VERIFY(*it == 1);
		auto& r1 = ++it;
		VERIFY(&r1 == &it);
		VERIFY(*it == 2);
		auto t1 = it++;
		VERIFY(*it == 3);
		VERIFY(*t1 == 2);
		auto& r2 = --it;
		VERIFY(&r2 == &it);
		VERIFY(*it == 2);
		auto t2 = it--;
		VERIFY(*it == 1);
		VERIFY(*t2 == 2);
		auto& r3 = it += 2;
		VERIFY(&r3 == &it);
		VERIFY(*it == 3);
		auto& r4 = it -= 2;
		VERIFY(&r4 == &it);
		VERIFY(*it == 1);

		const_iterator it1 = v.begin();
		const_iterator it2 = v.begin() + 1;
		const_iterator it3 = 1 + v.begin();
		const_iterator it4 = v.begin() + 2;
		VERIFY(!(it2 == it1));
		VERIFY( (it2 == it2));
		VERIFY( (it2 == it3));
		VERIFY(!(it2 == it4));
		VERIFY( (it2 != it1));
		VERIFY(!(it2 != it2));
		VERIFY(!(it2 != it3));
		VERIFY( (it2 != it4));
		VERIFY(!(it2 <  it1));
		VERIFY(!(it2 <  it2));
		VERIFY(!(it2 <  it3));
		VERIFY( (it2 <  it4));
		VERIFY( (it2 >  it1));
		VERIFY(!(it2 >  it2));
		VERIFY(!(it2 >  it3));
		VERIFY(!(it2 >  it4));
		VERIFY(!(it2 <= it1));
		VERIFY( (it2 <= it2));
		VERIFY( (it2 <= it3));
		VERIFY( (it2 <= it4));
		VERIFY( (it2 >= it1));
		VERIFY( (it2 >= it2));
		VERIFY( (it2 >= it3));
		VERIFY(!(it2 >= it4));
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		VERIFY(!hamon::is_eq(it2 <=> it1));
		VERIFY( hamon::is_eq(it2 <=> it2));
		VERIFY( hamon::is_eq(it2 <=> it3));
		VERIFY(!hamon::is_eq(it2 <=> it4));
		VERIFY(!hamon::is_lt(it2 <=> it1));
		VERIFY(!hamon::is_lt(it2 <=> it2));
		VERIFY(!hamon::is_lt(it2 <=> it3));
		VERIFY( hamon::is_lt(it2 <=> it4));
		VERIFY( hamon::is_gt(it2 <=> it1));
		VERIFY(!hamon::is_gt(it2 <=> it2));
		VERIFY(!hamon::is_gt(it2 <=> it3));
		VERIFY(!hamon::is_gt(it2 <=> it4));
#endif

		VERIFY(it1 == (it4 - 2));
		VERIFY((it4 - it1) == 2);
		VERIFY((it1 - it2) == -1);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, IteratorTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace iterator_test

}	// namespace hamon_vector_test
