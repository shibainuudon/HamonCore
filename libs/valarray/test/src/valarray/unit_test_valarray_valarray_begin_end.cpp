/**
 *	@file	unit_test_valarray_valarray_begin_end.cpp
 *
 *	@brief	begin, end のテスト
 *
 *	template<class T> unspecified1 begin(valarray<T>& v);
 *	template<class T> unspecified2 begin(const valarray<T>& v);
 *	template<class T> unspecified1 end(valarray<T>& v);
 *	template<class T> unspecified2 end(const valarray<T>& v);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/detail/cpp17_random_access_iterator.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/prev.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_begin_end_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	{
		T a[] = { 1, 2, 3, 4, 5 };
		hamon::valarray<T> v(a, 5);
		const hamon::valarray<T>& cv = v;

#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert(noexcept(hamon::begin(v)), "");
		static_assert(noexcept(hamon::begin(cv)), "");
		static_assert(noexcept(hamon::end(v)), "");
		static_assert(noexcept(hamon::end(cv)), "");
#endif
		using hamon::begin;
		using It = decltype(begin(v));
		using CIt = decltype(begin(cv));

		static_assert(hamon::detail::cpp17_random_access_iterator_t<It>::value, "");
		static_assert(hamon::detail::cpp17_random_access_iterator_t<CIt>::value, "");
		static_assert(hamon::contiguous_iterator_t<It>::value, "");
		static_assert(hamon::contiguous_iterator_t<CIt>::value, "");
		static_assert(hamon::is_same<hamon::iter_value_t<It>, T>::value, "");
		static_assert(hamon::is_same<hamon::iter_value_t<CIt>, T>::value, "");
		static_assert(hamon::is_same<hamon::iter_reference_t<It>, T&>::value, "");
		static_assert(hamon::is_same<hamon::iter_reference_t<CIt>, const T&>::value, "");
		VERIFY(&*begin(v) == &v[0]);
		VERIFY(&*begin(cv) == &cv[0]);
		*begin(v) = 10;
		VERIFY(v[0] == 10);

		using hamon::end;
		static_assert(hamon::is_same<decltype(end(v)), It>::value, "");
		static_assert(hamon::is_same<decltype(end(cv)), CIt>::value, "");
		VERIFY(&*hamon::prev(end(v)) == &v[4]);
		VERIFY(&*hamon::prev(end(cv)) == &cv[4]);
	}
	{
		T a[] = { 1, 2, 3, 4, 5 };
		hamon::valarray<T> v(a, 5);
		T sum = 0;
		for (T& i : v)
		{
			sum += i;
		}
		VERIFY(sum == 15);
	}
	{
		T a[] = { 1, 2, 3, 4, 5 };
		const hamon::valarray<T> cv(a, 5);
		T sum = 0;
		for (const T& i : cv)
		{
			sum += i;
		}
		VERIFY(sum == 15);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayBeginEndTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_begin_end_test

}	// namespace hamon_valarray_test
