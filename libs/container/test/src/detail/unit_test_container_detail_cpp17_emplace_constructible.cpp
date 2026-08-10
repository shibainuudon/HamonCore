/**
 *	@file	unit_test_container_detail_cpp17_emplace_constructible.cpp
 *
 *	@brief	cpp17_emplace_constructible のテスト
 */

#include <hamon/container/detail/cpp17_emplace_constructible.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/pair.hpp>
#include <hamon/tuple.hpp>

namespace hamon_container_test
{

namespace cpp17_emplace_constructible_test
{

static_assert( hamon::detail::cpp17_emplace_constructible<int, hamon::allocator<int>>, "");
static_assert( hamon::detail::cpp17_emplace_constructible<int, hamon::allocator<int>, int>, "");
static_assert(!hamon::detail::cpp17_emplace_constructible<int, hamon::allocator<int>, int, int>, "");

struct S1
{
	S1(int);
};

static_assert( hamon::detail::cpp17_emplace_constructible<S1, hamon::allocator<S1>, int>, "");
static_assert(!hamon::detail::cpp17_emplace_constructible<S1, hamon::allocator<S1>>, "");
static_assert(!hamon::detail::cpp17_emplace_constructible<S1, hamon::allocator<S1>, int, int>, "");

struct S2
{
	S2(int, int);
};

static_assert( hamon::detail::cpp17_emplace_constructible<S2, hamon::allocator<S2>, int, int>, "");
static_assert(!hamon::detail::cpp17_emplace_constructible<S2, hamon::allocator<S2>>, "");
static_assert(!hamon::detail::cpp17_emplace_constructible<S2, hamon::allocator<S2>, int>, "");

using P = hamon::pair<int, S2>;

static_assert( hamon::detail::cpp17_emplace_constructible<P, hamon::allocator<P>,
	hamon::piecewise_construct_t,
	hamon::tuple<int&&>,
	hamon::tuple<int&&, int&&>
>, "");

struct S3
{
	S3(S3 const&);
	S3(S3 &&) = delete;
};

static_assert( hamon::detail::cpp17_emplace_constructible<S3, hamon::allocator<S3>, S3 const&>, "");
static_assert(!hamon::detail::cpp17_emplace_constructible<S3, hamon::allocator<S3>, S3 &&>, "");

struct S4
{
	S4(S4 const&) = delete;
	S4(S4 &&);
};

static_assert(!hamon::detail::cpp17_emplace_constructible<S4, hamon::allocator<S4>, S4 const&>, "");
static_assert( hamon::detail::cpp17_emplace_constructible<S4, hamon::allocator<S4>, S4 &&>, "");

}	// namespace cpp17_emplace_constructible_test

}	// namespace hamon_container_test
