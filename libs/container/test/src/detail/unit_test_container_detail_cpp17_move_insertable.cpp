/**
 *	@file	unit_test_container_detail_cpp17_move_insertable.cpp
 *
 *	@brief	cpp17_move_insertable のテスト
 */

#include <hamon/container/detail/cpp17_move_insertable.hpp>
#include <hamon/memory/allocator.hpp>

namespace hamon_container_test
{

namespace cpp17_move_insertable_test
{

static_assert( hamon::detail::cpp17_move_insertable_t<int, hamon::allocator<int>>::value, "");
static_assert( hamon::detail::cpp17_move_insertable_t<float, hamon::allocator<float>>::value, "");

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

#if !defined(HAMON_USE_STD_ALLOCATOR_TRAITS)
static_assert(!hamon::detail::cpp17_move_insertable_t<S0, hamon::allocator<S0>>::value, "");
static_assert(!hamon::detail::cpp17_move_insertable_t<S1, hamon::allocator<S1>>::value, "");
#endif
static_assert( hamon::detail::cpp17_move_insertable_t<S2, hamon::allocator<S2>>::value, "");
static_assert( hamon::detail::cpp17_move_insertable_t<S3, hamon::allocator<S3>>::value, "");

}	// namespace cpp17_move_insertable_test

}	// namespace hamon_container_test
