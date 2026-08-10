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

static_assert( hamon::detail::cpp17_move_insertable<int, hamon::allocator<int>>, "");
static_assert( hamon::detail::cpp17_move_insertable<float, hamon::allocator<float>>, "");

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

static_assert(!hamon::detail::cpp17_move_insertable<S0, hamon::allocator<S0>>, "");
static_assert(!hamon::detail::cpp17_move_insertable<S1, hamon::allocator<S1>>, "");
static_assert( hamon::detail::cpp17_move_insertable<S2, hamon::allocator<S2>>, "");
static_assert( hamon::detail::cpp17_move_insertable<S3, hamon::allocator<S3>>, "");

}	// namespace cpp17_move_insertable_test

}	// namespace hamon_container_test
