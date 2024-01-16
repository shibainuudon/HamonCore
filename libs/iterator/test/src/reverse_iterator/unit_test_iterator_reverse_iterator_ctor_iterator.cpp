/**
 *	@file	unit_test_iterator_reverse_iterator_ctor_iterator.cpp
 *
 *	@brief	Iteratorからのコンストラクタのテスト
 *
 *	constexpr explicit reverse_iterator(Iterator x);
 */

#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test {
namespace reverse_iterator_test {
namespace ctor_iterator_test {

struct Base{};
struct Derived : public Base{};

struct ThrowOnMove
{
	using T = int;
	using iterator_category = hamon::input_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	int operator*() { return 0; }
	ThrowOnMove(ThrowOnMove&&) noexcept(false) {}
	ThrowOnMove(ThrowOnMove const&) noexcept(true) {}
};

struct ThrowOnCopy
{
	using T = int;
	using iterator_category = hamon::input_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	int operator*() { return 0; }
	ThrowOnCopy(ThrowOnCopy &&) noexcept(true) {}
	ThrowOnCopy(ThrowOnCopy const&) noexcept(false) {}
};

static_assert( hamon::is_constructible<hamon::reverse_iterator<Base*>, Base*>::value, "");
static_assert( hamon::is_constructible<hamon::reverse_iterator<Base*>, Derived*>::value, "");
static_assert(!hamon::is_constructible<hamon::reverse_iterator<Base*>, int*>::value, "");
static_assert(!hamon::is_constructible<hamon::reverse_iterator<Derived*>, Base*>::value, "");
static_assert( hamon::is_constructible<hamon::reverse_iterator<Derived*>, Derived*>::value, "");
static_assert(!hamon::is_constructible<hamon::reverse_iterator<Derived*>, int*>::value, "");
static_assert( hamon::is_constructible<hamon::reverse_iterator<int*>, int*>::value, "");
static_assert(!hamon::is_constructible<hamon::reverse_iterator<int*>, int const*>::value, "");
static_assert( hamon::is_constructible<hamon::reverse_iterator<int const*>, int*>::value, "");
static_assert( hamon::is_constructible<hamon::reverse_iterator<int const*>, int const*>::value, "");
static_assert( hamon::is_constructible<hamon::reverse_iterator<ThrowOnMove>, ThrowOnMove>::value, "");
static_assert( hamon::is_constructible<hamon::reverse_iterator<ThrowOnCopy>, ThrowOnCopy>::value, "");

static_assert( hamon::is_nothrow_constructible<hamon::reverse_iterator<Base*>, Base*>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::reverse_iterator<Base*>, Derived*>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::reverse_iterator<Base*>, int*>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::reverse_iterator<Derived*>, Base*>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::reverse_iterator<Derived*>, Derived*>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::reverse_iterator<Derived*>, int*>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::reverse_iterator<int*>, int*>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::reverse_iterator<int*>, int const*>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::reverse_iterator<int const*>, int*>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::reverse_iterator<int const*>, int const*>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::reverse_iterator<ThrowOnMove>, ThrowOnMove>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::reverse_iterator<ThrowOnCopy>, ThrowOnCopy>::value, "");

static_assert(!hamon::is_implicitly_constructible<hamon::reverse_iterator<Base*>, Base*>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::reverse_iterator<Base*>, Derived*>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::reverse_iterator<Base*>, int*>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::reverse_iterator<Derived*>, Base*>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::reverse_iterator<Derived*>, Derived*>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::reverse_iterator<Derived*>, int*>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::reverse_iterator<int*>, int*>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::reverse_iterator<int*>, int const*>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::reverse_iterator<int const*>, int*>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::reverse_iterator<int const*>, int const*>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::reverse_iterator<ThrowOnMove>, ThrowOnMove>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::reverse_iterator<ThrowOnCopy>, ThrowOnCopy>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	int n = 0;
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::reverse_iterator it(&n);
	static_assert(hamon::is_same<decltype(it), hamon::reverse_iterator<int*>>::value, "");
#else
	hamon::reverse_iterator<int*> it(&n);
#endif
	VERIFY(it.base() == &n);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	char const* str = "Hello World";
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::reverse_iterator it(str);
	static_assert(hamon::is_same<decltype(it), hamon::reverse_iterator<char const*>>::value, "");
#else
	hamon::reverse_iterator<char const*> it(str);
#endif
	VERIFY(it.base() == str);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	long const n = 42;
	using I = random_access_iterator_wrapper<long const>;
	I i{&n};
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::reverse_iterator it{i};
	static_assert(hamon::is_same<decltype(it), hamon::reverse_iterator<I>>::value, "");
#else
	hamon::reverse_iterator<I> it{i};
#endif
	VERIFY(base(it.base()) == &n);

	return true;
}

#undef VERIFY

GTEST_TEST(ReverseIteratorTest, CtorIteratorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace ctor_iterator_test
}	// namespace reverse_iterator_test
}	// namespace hamon_iterator_test
