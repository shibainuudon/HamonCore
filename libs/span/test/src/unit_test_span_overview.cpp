/**
 *	@file	unit_test_span_overview.cpp
 *
 *	@brief
 */

#include <hamon/span.hpp>
#include <hamon/type_traits/is_trivially_copyable.hpp>

namespace hamon_span_test
{

namespace overview_test
{

struct S1
{
};

struct S2
{
	S2(S2 const&){}
};

struct S3
{
	S3(S3&&){}
};

static_assert( hamon::is_trivially_copyable<int>::value, "");
static_assert( hamon::is_trivially_copyable<S1>::value, "");
static_assert(!hamon::is_trivially_copyable<S2>::value, "");
static_assert(!hamon::is_trivially_copyable<S3>::value, "");

// [span.overview]/3	span<ElementType, Extent> is a trivially copyable type
static_assert( hamon::is_trivially_copyable<hamon::span<int>>::value, "");
static_assert( hamon::is_trivially_copyable<hamon::span<S1>>::value, "");
static_assert( hamon::is_trivially_copyable<hamon::span<S2>>::value, "");
static_assert( hamon::is_trivially_copyable<hamon::span<S3>>::value, "");
static_assert( hamon::is_trivially_copyable<hamon::span<int, 1>>::value, "");
static_assert( hamon::is_trivially_copyable<hamon::span<S1, 2>>::value, "");
static_assert( hamon::is_trivially_copyable<hamon::span<S2, 3>>::value, "");
static_assert( hamon::is_trivially_copyable<hamon::span<S3, 4>>::value, "");

}	// namespace overview_test

}	// namespace hamon_span_test
