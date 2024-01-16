/**
 *	@file	unit_test_iterator_reverse_iterator_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	constexpr reverse_iterator();
 */

#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_implicitly_default_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test {
namespace reverse_iterator_test {
namespace ctor_default_test {

struct ThrowOnDefault
{
	using T = int;
	using iterator_category = hamon::input_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	int operator*() { return 0; }
	ThrowOnDefault() noexcept(false) {};
};

static_assert( hamon::is_default_constructible<hamon::reverse_iterator<int*>>::value, "");
static_assert( hamon::is_default_constructible<hamon::reverse_iterator<char const*>>::value, "");
static_assert( hamon::is_default_constructible<hamon::reverse_iterator<random_access_iterator_wrapper<long>>>::value, "");
static_assert( hamon::is_default_constructible<hamon::reverse_iterator<ThrowOnDefault>>::value, "");

static_assert( hamon::is_nothrow_default_constructible<hamon::reverse_iterator<int*>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::reverse_iterator<char const*>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::reverse_iterator<random_access_iterator_wrapper<long>>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::reverse_iterator<ThrowOnDefault>>::value, "");

static_assert( hamon::is_implicitly_default_constructible<hamon::reverse_iterator<int*>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::reverse_iterator<char const*>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::reverse_iterator<random_access_iterator_wrapper<long>>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::reverse_iterator<ThrowOnDefault>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	hamon::reverse_iterator<int*> it;
	VERIFY(it.base() == nullptr);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	hamon::reverse_iterator<char const*> it = {};
	VERIFY(it.base() == nullptr);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	hamon::reverse_iterator<random_access_iterator_wrapper<long>> it{};
	VERIFY(base(it.base()) == nullptr);

	return true;
}

#undef VERIFY

GTEST_TEST(ReverseIteratorTest, CtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace ctor_default_test
}	// namespace reverse_iterator_test
}	// namespace hamon_iterator_test
