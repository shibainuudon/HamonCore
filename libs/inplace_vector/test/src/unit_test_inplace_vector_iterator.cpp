/**
 *	@file	unit_test_inplace_vector_iterator.cpp
 *
 *	@brief	inplace_vector<T>::iterator のテスト
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/compare.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace iterator_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using InplaceVector = hamon::inplace_vector<T, 10>;
	using difference_type = typename InplaceVector::difference_type;
	using iterator      = typename InplaceVector::iterator;
	using const_iterator = typename InplaceVector::const_iterator;

	static_assert(hamon::detail::cpp17_random_access_iterator_t<iterator>::value, "");
	static_assert(hamon::contiguous_iterator_t<iterator>::value, "");
	static_assert(hamon::is_same<T, hamon::iter_value_t<iterator>>::value, "");
	static_assert(hamon::is_same<T&, hamon::iter_reference_t<iterator>>::value, "");
	static_assert(hamon::is_same<difference_type, hamon::iter_difference_t<iterator>>::value, "");
	static_assert(hamon::is_default_constructible<iterator>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<iterator>::value, "");
	//static_assert(!hamon::is_constructible<iterator, T*>::value, "");
	//static_assert(!hamon::is_constructible<iterator, T const*>::value, "");
	static_assert(hamon::is_same<T&, decltype(*hamon::declval<iterator const&>())>::value, "");
	//static_assert(hamon::is_same<T*, decltype(hamon::declval<iterator const&>().operator->())>::value, "");
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
	//static_assert(!hamon::is_constructible<const_iterator, T*>::value, "");
	//static_assert(!hamon::is_constructible<const_iterator, T const*>::value, "");
	static_assert(hamon::is_same<T const&, decltype(*hamon::declval<const_iterator const&>())>::value, "");
	//static_assert(hamon::is_same<T const*, decltype(hamon::declval<const_iterator const&>().operator->())>::value, "");
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
		InplaceVector v{1,2,3};
		iterator it = v.begin();
		//auto* p = it.operator->();
		//VERIFY(*p == 1);
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
		InplaceVector v{1,2,3};
		const_iterator it = v.begin();
		//auto* p = it.operator->();
		//VERIFY(*p == 1);
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

struct Vector3
{
	int x;
	int y;
	int z;
};

HAMON_CXX20_CONSTEXPR bool test2()
{
	{
		hamon::inplace_vector<Vector3, 10> v
		{
			{1,2,3},
			{4,5,6},
		};
		auto it = v.begin();
		VERIFY(it != v.end());
		VERIFY(it->x == 1);
		VERIFY(it->y == 2);
		VERIFY(it->z == 3);
		++it;
		VERIFY(it != v.end());
		VERIFY(it->x == 4);
		VERIFY(it->y == 5);
		VERIFY(it->z == 6);
		++it;
		VERIFY(it == v.end());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, IteratorTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2());
}

}	// namespace iterator_test

}	// namespace hamon_inplace_vector_test
