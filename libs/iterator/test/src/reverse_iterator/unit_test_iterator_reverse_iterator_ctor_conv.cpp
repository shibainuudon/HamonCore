/**
 *	@file	unit_test_iterator_reverse_iterator_ctor_conv.cpp
 *
 *	@brief	変換コンストラクタのテスト
 *
 *	template<class U> constexpr reverse_iterator(const reverse_iterator<U>& u);
 */

#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test {
namespace reverse_iterator_test {
namespace ctor_conv_test {

struct Base{};
struct Derived : public Base{};

template <typename T>
struct ThrowOnCopy
{
	using iterator_category = hamon::input_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	int operator*() { return 0; }
	template <typename U>
	ThrowOnCopy(ThrowOnCopy<U> &&) noexcept(true) {}
	template <typename U>
	ThrowOnCopy(ThrowOnCopy<U> const&) noexcept(false) {}
};

static_assert( hamon::is_constructible<hamon::reverse_iterator<Base*>, hamon::reverse_iterator<Base*> const&>::value, "");
static_assert( hamon::is_constructible<hamon::reverse_iterator<Base*>, hamon::reverse_iterator<Derived*> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::reverse_iterator<Base*>, hamon::reverse_iterator<int*> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::reverse_iterator<Derived*>, hamon::reverse_iterator<Base*> const&>::value, "");
static_assert( hamon::is_constructible<hamon::reverse_iterator<Derived*>, hamon::reverse_iterator<Derived*> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::reverse_iterator<Derived*>, hamon::reverse_iterator<int*> const&>::value, "");
static_assert( hamon::is_constructible<hamon::reverse_iterator<int*>, hamon::reverse_iterator<int*> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::reverse_iterator<int*>, hamon::reverse_iterator<int const*> const&>::value, "");
static_assert( hamon::is_constructible<hamon::reverse_iterator<int const*>, hamon::reverse_iterator<int*> const&>::value, "");
static_assert( hamon::is_constructible<hamon::reverse_iterator<int const*>, hamon::reverse_iterator<int const*> const&>::value, "");
static_assert( hamon::is_constructible<hamon::reverse_iterator<ThrowOnCopy<int>>, hamon::reverse_iterator<ThrowOnCopy<int>> const&>::value, "");
static_assert( hamon::is_constructible<hamon::reverse_iterator<ThrowOnCopy<int>>, hamon::reverse_iterator<ThrowOnCopy<float>> const&>::value, "");
static_assert( hamon::is_constructible<hamon::reverse_iterator<ThrowOnCopy<int>>, hamon::reverse_iterator<ThrowOnCopy<int*>> const&>::value, "");

static_assert( hamon::is_nothrow_constructible<hamon::reverse_iterator<Base*>, hamon::reverse_iterator<Base*> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::reverse_iterator<Base*>, hamon::reverse_iterator<Derived*> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::reverse_iterator<Base*>, hamon::reverse_iterator<int*> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::reverse_iterator<Derived*>, hamon::reverse_iterator<Base*> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::reverse_iterator<Derived*>, hamon::reverse_iterator<Derived*> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::reverse_iterator<Derived*>, hamon::reverse_iterator<int*> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::reverse_iterator<int*>, hamon::reverse_iterator<int*> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::reverse_iterator<int*>, hamon::reverse_iterator<int const*> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::reverse_iterator<int const*>, hamon::reverse_iterator<int*> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::reverse_iterator<int const*>, hamon::reverse_iterator<int const*> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::reverse_iterator<ThrowOnCopy<int>>, hamon::reverse_iterator<ThrowOnCopy<int>> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::reverse_iterator<ThrowOnCopy<int>>, hamon::reverse_iterator<ThrowOnCopy<float>> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::reverse_iterator<ThrowOnCopy<int>>, hamon::reverse_iterator<ThrowOnCopy<int*>> const&>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::reverse_iterator<Base*>, hamon::reverse_iterator<Base*> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::reverse_iterator<Base*>, hamon::reverse_iterator<Derived*> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::reverse_iterator<Base*>, hamon::reverse_iterator<int*> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::reverse_iterator<Derived*>, hamon::reverse_iterator<Base*> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::reverse_iterator<Derived*>, hamon::reverse_iterator<Derived*> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::reverse_iterator<Derived*>, hamon::reverse_iterator<int*> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::reverse_iterator<int*>, hamon::reverse_iterator<int*> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::reverse_iterator<int*>, hamon::reverse_iterator<int const*> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::reverse_iterator<int const*>, hamon::reverse_iterator<int*> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::reverse_iterator<int const*>, hamon::reverse_iterator<int const*> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::reverse_iterator<ThrowOnCopy<int>>, hamon::reverse_iterator<ThrowOnCopy<int>> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::reverse_iterator<ThrowOnCopy<int>>, hamon::reverse_iterator<ThrowOnCopy<float>> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::reverse_iterator<ThrowOnCopy<int>>, hamon::reverse_iterator<ThrowOnCopy<int*>> const&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	int n = 0;
	hamon::reverse_iterator<int*> const it1(&n);
	hamon::reverse_iterator<int const*> it2(it1);
	VERIFY(it2.base() == &n);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	Derived d;
	hamon::reverse_iterator<Derived*> it1(&d);
	hamon::reverse_iterator<Base*> it2(it1);
	VERIFY(it2.base() == &d);

	return true;
}

#undef VERIFY

GTEST_TEST(ReverseIteratorTest, CtorConvTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace ctor_conv_test
}	// namespace reverse_iterator_test
}	// namespace hamon_iterator_test
