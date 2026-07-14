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

static_assert( hamon::detail::cpp17_erasable<int, hamon::allocator<int>>, "");
static_assert( hamon::detail::cpp17_erasable<float, hamon::allocator<float>>, "");

static_assert( hamon::detail::cpp17_erasable<int*, hamon::allocator<int>>, "");
static_assert(!hamon::detail::cpp17_erasable<int&, hamon::allocator<int>>, "");
static_assert(!hamon::detail::cpp17_erasable<int&&, hamon::allocator<int>>, "");

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

static_assert( hamon::detail::cpp17_erasable<S0, hamon::allocator<S0>>, "");
static_assert( hamon::detail::cpp17_erasable<S1, hamon::allocator<S1>>, "");
static_assert( hamon::detail::cpp17_erasable<S2, hamon::allocator<S2>>, "");
static_assert( hamon::detail::cpp17_erasable<S3, hamon::allocator<S3>>, "");

}	// namespace cpp17_erasable_test

}	// namespace hamon_container_test
