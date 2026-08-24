/**
 *	@file	unit_test_valarray_slice.cpp
 *
 *	@brief	slice のテスト
 *
 *	class slice {
 *	public:
 *		slice();
 *		slice(size_t, size_t, size_t);
 *		slice(const slice&);
 *
 *		size_t start() const;
 *		size_t size() const;
 *		size_t stride() const;
 *
 *		friend bool operator==(const slice& x, const slice& y);
 *	};
 */

#include <hamon/valarray/slice.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace slice_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	static_assert( hamon::is_default_constructible<hamon::slice>::value, "");
	static_assert( hamon::is_nothrow_default_constructible<hamon::slice>::value, "");
	static_assert(!hamon::is_trivially_default_constructible<hamon::slice>::value, "");
	static_assert( hamon::is_implicitly_default_constructible<hamon::slice>::value, "");

	static_assert( hamon::is_constructible<hamon::slice, hamon::size_t, hamon::size_t, hamon::size_t>::value, "");
	static_assert( hamon::is_nothrow_constructible<hamon::slice, hamon::size_t, hamon::size_t, hamon::size_t>::value, "");
	static_assert(!hamon::is_trivially_constructible<hamon::slice, hamon::size_t, hamon::size_t, hamon::size_t>::value, "");
	static_assert( hamon::is_implicitly_constructible<hamon::slice, hamon::size_t, hamon::size_t, hamon::size_t>::value, "");

	// [cons.slice]
	// [slice.access]
	{
		hamon::slice s;

		static_assert(hamon::is_same<decltype(s.start()), hamon::size_t>::value, "");
		static_assert(hamon::is_same<decltype(s.size()), hamon::size_t>::value, "");
		static_assert(hamon::is_same<decltype(s.stride()), hamon::size_t>::value, "");

		static_assert(noexcept(s.start()), "");
		static_assert(noexcept(s.size()), "");
		static_assert(noexcept(s.stride()), "");

		VERIFY(s.start() == 0);
		VERIFY(s.size() == 0);
		VERIFY(s.stride() == 0);
	}
	{
		hamon::slice s(1, 3, 2);
		VERIFY(s.start() == 1);
		VERIFY(s.size() == 3);
		VERIFY(s.stride() == 2);
	}

	// [slice.ops]
	{
		hamon::slice s1;
		hamon::slice s2;

		static_assert(hamon::is_same<decltype(s1 == s1), bool>::value, "");
		static_assert(hamon::is_same<decltype(s1 != s1), bool>::value, "");

		static_assert(noexcept(s1 == s1), "");
		static_assert(noexcept(s1 != s1), "");

		VERIFY( (s1 == s2));
		VERIFY(!(s1 != s2));
	}
	{
		hamon::slice s1{ 1, 2, 3 };
		hamon::slice s2{ 1, 2, 3 };

		VERIFY( (s1 == s2));
		VERIFY(!(s1 != s2));
	}
	{
		hamon::slice s1;
		hamon::slice s2{ 1, 2, 3 };

		VERIFY(!(s1 == s2));
		VERIFY( (s1 != s2));
	}
	{
		hamon::slice s1{ 0, 2, 3 };
		hamon::slice s2{ 1, 2, 3 };

		VERIFY(!(s1 == s2));
		VERIFY( (s1 != s2));
	}
	{
		hamon::slice s1{ 1, 0, 3 };
		hamon::slice s2{ 1, 2, 3 };

		VERIFY(!(s1 == s2));
		VERIFY( (s1 != s2));
	}
	{
		hamon::slice s1{ 1, 2, 0 };
		hamon::slice s2{ 1, 2, 3 };

		VERIFY(!(s1 == s2));
		VERIFY( (s1 != s2));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, SliceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace slice_test

}	// namespace hamon_valarray_test
