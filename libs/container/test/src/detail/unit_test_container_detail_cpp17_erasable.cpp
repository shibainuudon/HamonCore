/**
 *	@file	unit_test_container_detail_cpp17_erasable.cpp
 *
 *	@brief	cpp17_erasable のテスト
 */

#include <hamon/container/detail/cpp17_erasable.hpp>
#include <hamon/memory/allocator.hpp>

namespace hamon_container_test
{

namespace cpp17_erasable_test
{

static_assert( hamon::detail::cpp17_erasable_t<int, hamon::allocator<int>>::value, "");
static_assert( hamon::detail::cpp17_erasable_t<float, hamon::allocator<float>>::value, "");

static_assert( hamon::detail::cpp17_erasable_t<int*, hamon::allocator<int>>::value, "");
static_assert(!hamon::detail::cpp17_erasable_t<int&, hamon::allocator<int>>::value, "");
static_assert(!hamon::detail::cpp17_erasable_t<int&&, hamon::allocator<int>>::value, "");

struct S0
{
	S0(S0 const&) = delete;
	S0(S0 &&) = delete;
};

struct S1
{
	S1(S1 const&);
	S1(S1 &&) = delete;
};

struct S2
{
	S2(S2 const&) = delete;
	S2(S2 &&);
};

struct S3
{
	S3(S3 const&);
	S3(S3 &&);
};

static_assert( hamon::detail::cpp17_erasable_t<S0, hamon::allocator<S0>>::value, "");
static_assert( hamon::detail::cpp17_erasable_t<S1, hamon::allocator<S1>>::value, "");
static_assert( hamon::detail::cpp17_erasable_t<S2, hamon::allocator<S2>>::value, "");
static_assert( hamon::detail::cpp17_erasable_t<S3, hamon::allocator<S3>>::value, "");

}	// namespace cpp17_erasable_test

}	// namespace hamon_container_test
