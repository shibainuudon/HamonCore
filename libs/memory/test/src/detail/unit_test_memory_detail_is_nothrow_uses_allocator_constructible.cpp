/**
 *	@file	unit_test_memory_detail_is_nothrow_uses_allocator_constructible.cpp
 *
 *	@brief	is_nothrow_uses_allocator_constructible のテスト
 */

#include <hamon/memory/detail/is_nothrow_uses_allocator_constructible.hpp>
#include <hamon/memory/allocator_arg_t.hpp>

namespace hamon_memory_test
{

namespace is_nothrow_uses_allocator_constructible_test
{

struct MyAlloc {};

struct FirstAlloc
{
	using allocator_type = MyAlloc;
	FirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int) noexcept;
	FirstAlloc(hamon::allocator_arg_t, MyAlloc const&, char, float);
};

struct LastAlloc
{
	using allocator_type = MyAlloc;
	LastAlloc(MyAlloc const&) noexcept;
	LastAlloc(int, MyAlloc const&);
};

struct NoAlloc
{
	NoAlloc(int);
	NoAlloc(char, float) noexcept;
};


static_assert( hamon::detail::is_nothrow_uses_allocator_constructible<int,        MyAlloc>::value, "");
static_assert(!hamon::detail::is_nothrow_uses_allocator_constructible<FirstAlloc, MyAlloc>::value, "");
static_assert( hamon::detail::is_nothrow_uses_allocator_constructible<LastAlloc,  MyAlloc>::value, "");
static_assert(!hamon::detail::is_nothrow_uses_allocator_constructible<NoAlloc,    MyAlloc>::value, "");

static_assert( hamon::detail::is_nothrow_uses_allocator_constructible<int,        MyAlloc, int>::value, "");
static_assert( hamon::detail::is_nothrow_uses_allocator_constructible<FirstAlloc, MyAlloc, int>::value, "");
static_assert(!hamon::detail::is_nothrow_uses_allocator_constructible<LastAlloc,  MyAlloc, int>::value, "");
static_assert(!hamon::detail::is_nothrow_uses_allocator_constructible<NoAlloc,    MyAlloc, int>::value, "");

static_assert(!hamon::detail::is_nothrow_uses_allocator_constructible<int,        MyAlloc, char, float>::value, "");
static_assert(!hamon::detail::is_nothrow_uses_allocator_constructible<FirstAlloc, MyAlloc, char, float>::value, "");
static_assert(!hamon::detail::is_nothrow_uses_allocator_constructible<LastAlloc,  MyAlloc, char, float>::value, "");
static_assert( hamon::detail::is_nothrow_uses_allocator_constructible<NoAlloc,    MyAlloc, char, float>::value, "");

}	// namespace is_nothrow_uses_allocator_constructible_test

}	// namespace hamon_memory_test
