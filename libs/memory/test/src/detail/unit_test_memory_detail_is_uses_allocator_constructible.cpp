/**
 *	@file	unit_test_memory_detail_is_uses_allocator_constructible.cpp
 *
 *	@brief	is_uses_allocator_constructible のテスト
 */

#include <hamon/memory/detail/is_uses_allocator_constructible.hpp>
#include <hamon/memory/allocator_arg_t.hpp>

namespace hamon_memory_test
{

namespace is_uses_allocator_constructible_test
{

struct MyAlloc {};

struct FirstAlloc
{
	using allocator_type = MyAlloc;
	FirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int);
	FirstAlloc(hamon::allocator_arg_t, MyAlloc const&, char, float);
};

struct LastAlloc
{
	using allocator_type = MyAlloc;
	LastAlloc(MyAlloc const&);
	LastAlloc(int, MyAlloc const&);
};

struct NoAlloc
{
	NoAlloc(int);
};

struct NoAlloc2
{
	NoAlloc2(char, float);
};

struct Invalid
{
	using allocator_type = MyAlloc;
	Invalid(int);
};

struct Invalid2
{
	using allocator_type = MyAlloc;
	Invalid2(char, float);
};

static_assert( hamon::detail::is_uses_allocator_constructible<int,        MyAlloc>::value, "");
static_assert(!hamon::detail::is_uses_allocator_constructible<FirstAlloc, MyAlloc>::value, "");
static_assert( hamon::detail::is_uses_allocator_constructible<LastAlloc,  MyAlloc>::value, "");
static_assert(!hamon::detail::is_uses_allocator_constructible<NoAlloc,    MyAlloc>::value, "");
static_assert(!hamon::detail::is_uses_allocator_constructible<NoAlloc2,   MyAlloc>::value, "");
static_assert(!hamon::detail::is_uses_allocator_constructible<Invalid,    MyAlloc>::value, "");
static_assert(!hamon::detail::is_uses_allocator_constructible<Invalid2,   MyAlloc>::value, "");

static_assert( hamon::detail::is_uses_allocator_constructible<int,        MyAlloc, int>::value, "");
static_assert( hamon::detail::is_uses_allocator_constructible<FirstAlloc, MyAlloc, int>::value, "");
static_assert( hamon::detail::is_uses_allocator_constructible<LastAlloc,  MyAlloc, int>::value, "");
static_assert( hamon::detail::is_uses_allocator_constructible<NoAlloc,    MyAlloc, int>::value, "");
static_assert(!hamon::detail::is_uses_allocator_constructible<NoAlloc2,   MyAlloc, int>::value, "");
static_assert(!hamon::detail::is_uses_allocator_constructible<Invalid,    MyAlloc, int>::value, "");
static_assert(!hamon::detail::is_uses_allocator_constructible<Invalid2,   MyAlloc, int>::value, "");

static_assert(!hamon::detail::is_uses_allocator_constructible<int,        MyAlloc, char, float>::value, "");
static_assert( hamon::detail::is_uses_allocator_constructible<FirstAlloc, MyAlloc, char, float>::value, "");
static_assert(!hamon::detail::is_uses_allocator_constructible<LastAlloc,  MyAlloc, char, float>::value, "");
static_assert(!hamon::detail::is_uses_allocator_constructible<NoAlloc,    MyAlloc, char, float>::value, "");
static_assert( hamon::detail::is_uses_allocator_constructible<NoAlloc2,   MyAlloc, char, float>::value, "");
static_assert(!hamon::detail::is_uses_allocator_constructible<Invalid,    MyAlloc, char, float>::value, "");
static_assert(!hamon::detail::is_uses_allocator_constructible<Invalid2,   MyAlloc, char, float>::value, "");

}	// namespace is_uses_allocator_constructible_test

}	// namespace hamon_memory_test
