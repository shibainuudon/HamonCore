/**
 *	@file	unit_test_valarray_valarray_assign_copy.cpp
 *
 *	@brief	operator= のテスト
 *
 *	valarray& operator=(const valarray&);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_assign_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	static_assert( hamon::is_copy_assignable<hamon::valarray<T>>::value, "");
	static_assert(!hamon::is_nothrow_copy_assignable<hamon::valarray<T>>::value, "");
	static_assert(!hamon::is_trivially_copy_assignable<hamon::valarray<T>>::value, "");

	{
		T a[] = { 1, 2, 3, 4, 5 };
		const unsigned N = sizeof(a) / sizeof(a[0]);
		hamon::valarray<T> const v(a, N);
		hamon::valarray<T> v2;
		v2 = v;
		VERIFY(v2.size() == v.size());
		for (hamon::size_t i = 0; i < v2.size(); ++i)
		{
			VERIFY(v2[i] == v[i]);
		}
		// self-assignment
		v2 = static_cast<hamon::valarray<T> const&>(v2);
		VERIFY(v2.size() == v.size());
		for (hamon::size_t i = 0; i < v2.size(); ++i)
		{
			VERIFY(v2[i] == v[i]);
		}
	}
	{
		T a[] = { 1, 2, 3, 4, 5 };
		T b[] = { 6, 7, 8, 9, 10 };
		const unsigned N = sizeof(a) / sizeof(a[0]);
		hamon::valarray<T> const v(a, N);
		hamon::valarray<T> v2(b, N);
		v2 = v;
		VERIFY(v2.size() == v.size());
		for (hamon::size_t i = 0; i < v2.size(); ++i)
		{
			VERIFY(v2[i] == v[i]);
		}
	}

	return true;
}

struct S
{
	S() : x_(0) { default_ctor_called = true; }
	S(int x) : x_(x) {}
	int x_;
	static bool default_ctor_called;
};

bool S::default_ctor_called = false;

bool operator==(const S& lhs, const S& rhs)
{
	return lhs.x_ == rhs.x_;
}

inline bool test2()
{
	typedef S T;
	T a[] = { T(1), T(2), T(3), T(4), T(5) };
	const unsigned N = sizeof(a) / sizeof(a[0]);
	hamon::valarray<T> v(a, N);
	hamon::valarray<T> v2;
	v2 = v;
	VERIFY(v2.size() == v.size());
	for (hamon::size_t i = 0; i < v2.size(); ++i)
	{
		VERIFY(v2[i] == v[i]);
	}
	VERIFY(!S::default_ctor_called);

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayAssignCopyTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));

	EXPECT_TRUE((test2()));
}

}	// namespace valarray_assign_copy_test

}	// namespace hamon_valarray_test
