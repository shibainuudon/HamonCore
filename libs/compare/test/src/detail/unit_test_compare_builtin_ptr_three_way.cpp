/**
 *	@file	unit_test_compare_builtin_ptr_three_way.cpp
 *
 *	@brief	builtin_ptr_three_way のテスト
 */

#include <hamon/compare/detail/builtin_ptr_three_way.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

namespace hamon_compare_test
{

namespace builtin_ptr_three_way_test
{

static_assert(!hamon::detail::builtin_ptr_three_way<int, int>, "");
static_assert( hamon::detail::builtin_ptr_three_way<int*, int*>, "");
static_assert( hamon::detail::builtin_ptr_three_way<int const*, int const*>, "");
static_assert( hamon::detail::builtin_ptr_three_way<int volatile*, int volatile*>, "");
static_assert( hamon::detail::builtin_ptr_three_way<int const volatile*, int const volatile*>, "");
static_assert( hamon::detail::builtin_ptr_three_way<void*, void*>, "");
static_assert( hamon::detail::builtin_ptr_three_way<int*, void*>, "");
static_assert( hamon::detail::builtin_ptr_three_way<void*, void*>, "");
#if !defined(HAMON_GCC)
static_assert(!hamon::detail::builtin_ptr_three_way<int*, char*>, "");	// gcc で internal compiler error
#endif

struct S1
{
	operator void*()const;
};
void operator<=>(S1 const&, S1 const&);

static_assert(!hamon::detail::builtin_ptr_three_way<S1, S1>, "");

struct S2
{
	operator void*()const;
	void operator<=>(S2 const&) const;
};

static_assert(!hamon::detail::builtin_ptr_three_way<S2, S2>, "");

}	// namespace builtin_ptr_three_way_test

}	// namespace hamon_compare_test

#endif
