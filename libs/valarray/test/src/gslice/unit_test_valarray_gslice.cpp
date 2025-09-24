/**
 *	@file	unit_test_valarray_gslice.cpp
 *
 *	@brief	gslice のテスト
 *
 *	class gslice {
 *	public:
 *		gslice();
 *		gslice(size_t s, const valarray<size_t>& l, const valarray<size_t>& d);
 *
 *		size_t           start() const;
 *		valarray<size_t> size() const;
 *		valarray<size_t> stride() const;
 *	};
 */

#include <hamon/valarray/gslice.hpp>
#include <hamon/valarray/valarray.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace gslice_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX20_CONSTEXPR bool test()
{
	static_assert( hamon::is_default_constructible<hamon::gslice>::value, "");
#if !defined(HAMON_USE_STD_VALARRAY)
	static_assert(!hamon::is_nothrow_default_constructible<hamon::gslice>::value, "");
#endif
	static_assert(!hamon::is_trivially_default_constructible<hamon::gslice>::value, "");
	static_assert( hamon::is_implicitly_default_constructible<hamon::gslice>::value, "");

	static_assert( hamon::is_constructible<hamon::gslice, hamon::size_t, hamon::valarray<hamon::size_t> const&, hamon::valarray<hamon::size_t> const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<hamon::gslice, hamon::size_t, hamon::valarray<hamon::size_t> const&, hamon::valarray<hamon::size_t> const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<hamon::gslice, hamon::size_t, hamon::valarray<hamon::size_t> const&, hamon::valarray<hamon::size_t> const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<hamon::gslice, hamon::size_t, hamon::valarray<hamon::size_t> const&, hamon::valarray<hamon::size_t> const&>::value, "");

	// [gslice.cons]
	// [gslice.access]
	{
		hamon::gslice gs;

		static_assert(hamon::is_same<decltype(gs.start()), hamon::size_t>::value, "");
		static_assert(hamon::is_same<decltype(gs.size()), hamon::valarray<hamon::size_t>>::value, "");
		static_assert(hamon::is_same<decltype(gs.stride()), hamon::valarray<hamon::size_t>>::value, "");

#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert( noexcept(gs.start()), "");
		static_assert(!noexcept(gs.size()), "");
		static_assert(!noexcept(gs.stride()), "");
#endif

		VERIFY(gs.start() == 0);
		VERIFY(gs.size().size() == 0);
		VERIFY(gs.stride().size() == 0);
	}
	{
		hamon::size_t a1[] = { 1, 2, 3 };
		hamon::size_t a2[] = { 4, 5, 6 };
		hamon::valarray<hamon::size_t> size(a1, sizeof(a1) / sizeof(a1[0]));
		hamon::valarray<hamon::size_t> stride(a2, sizeof(a2) / sizeof(a2[0]));
		hamon::gslice gs(7, size, stride);
		VERIFY(gs.start() == 7);
		hamon::valarray<hamon::size_t> r = gs.size();
		VERIFY(r.size() == 3);
		VERIFY(r[0] == 1);
		VERIFY(r[1] == 2);
		VERIFY(r[2] == 3);
		r = gs.stride();
		VERIFY(r.size() == 3);
		VERIFY(r[0] == 4);
		VERIFY(r[1] == 5);
		VERIFY(r[2] == 6);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, GsliceTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace gslice_test

}	// namespace hamon_valarray_test
