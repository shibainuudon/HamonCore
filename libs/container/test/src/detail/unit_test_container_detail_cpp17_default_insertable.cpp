/**
 *	@file	unit_test_container_detail_cpp17_default_insertable.cpp
 *
 *	@brief	cpp17_default_insertable のテスト
 */

#include <hamon/container/detail/cpp17_default_insertable.hpp>
#include <hamon/memory/allocator.hpp>

namespace hamon_container_test
{

namespace cpp17_default_insertable_test
{

static_assert( hamon::detail::cpp17_default_insertable<int, hamon::allocator<int>>, "");
static_assert( hamon::detail::cpp17_default_insertable<float, hamon::allocator<float>>, "");

struct S0
{
	S0() = delete;
	S0(S0 const&) = delete;
	S0(S0 &&) = delete;
};

struct S1
{
	S1();
	S1(S1 const&) = delete;
	S1(S1 &&) = delete;
};

#if !defined(HAMON_USE_STD_ALLOCATOR_TRAITS)
static_assert(!hamon::detail::cpp17_default_insertable<S0, hamon::allocator<S0>>, "");
#endif
static_assert( hamon::detail::cpp17_default_insertable<S1, hamon::allocator<S1>>, "");

}	// namespace cpp17_default_insertable_test

}	// namespace hamon_container_test
