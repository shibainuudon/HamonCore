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

static_assert( hamon::detail::cpp17_emplace_constructible_t<int, hamon::allocator<int>>::value, "");
static_assert( hamon::detail::cpp17_emplace_constructible_t<int, hamon::allocator<int>, int>::value, "");
#if !defined(HAMON_USE_STD_ALLOCATOR_TRAITS)
static_assert(!hamon::detail::cpp17_emplace_constructible_t<int, hamon::allocator<int>, int, int>::value, "");
#endif

struct S1
{
	S1(int);
};

static_assert( hamon::detail::cpp17_emplace_constructible_t<S1, hamon::allocator<S1>, int>::value, "");
#if !defined(HAMON_USE_STD_ALLOCATOR_TRAITS)
static_assert(!hamon::detail::cpp17_emplace_constructible_t<S1, hamon::allocator<S1>>::value, "");
static_assert(!hamon::detail::cpp17_emplace_constructible_t<S1, hamon::allocator<S1>, int, int>::value, "");
#endif

struct S2
{
	S2(int, int);
};

static_assert( hamon::detail::cpp17_emplace_constructible_t<S2, hamon::allocator<S2>, int, int>::value, "");
#if !defined(HAMON_USE_STD_ALLOCATOR_TRAITS)
static_assert(!hamon::detail::cpp17_emplace_constructible_t<S2, hamon::allocator<S2>>::value, "");
static_assert(!hamon::detail::cpp17_emplace_constructible_t<S2, hamon::allocator<S2>, int>::value, "");
#endif

using P = hamon::pair<int, S2>;

static_assert( hamon::detail::cpp17_emplace_constructible_t<P, hamon::allocator<P>,
	hamon::piecewise_construct_t,
	hamon::tuple<int&&>,
	hamon::tuple<int&&, int&&>
>::value, "");

struct S3
{
	S3(S3 const&);
	S3(S3 &&) = delete;
};

static_assert( hamon::detail::cpp17_emplace_constructible_t<S3, hamon::allocator<S3>, S3 const&>::value, "");
#if !defined(HAMON_USE_STD_ALLOCATOR_TRAITS)
static_assert(!hamon::detail::cpp17_emplace_constructible_t<S3, hamon::allocator<S3>, S3 &&>::value, "");
#endif

struct S4
{
	S4(S4 const&) = delete;
	S4(S4 &&);
};

#if !defined(HAMON_USE_STD_ALLOCATOR_TRAITS)
static_assert(!hamon::detail::cpp17_emplace_constructible_t<S4, hamon::allocator<S4>, S4 const&>::value, "");
#endif
static_assert( hamon::detail::cpp17_emplace_constructible_t<S4, hamon::allocator<S4>, S4 &&>::value, "");

}	// namespace cpp17_emplace_constructible_test

}	// namespace hamon_container_test
