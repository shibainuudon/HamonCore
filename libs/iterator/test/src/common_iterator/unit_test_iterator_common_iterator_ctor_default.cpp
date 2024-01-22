/**
 *	@file	unit_test_iterator_common_iterator_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	constexpr common_iterator() requires default_initializable<I> = default;
 */

#include <hamon/iterator/common_iterator.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_iterator_test {
namespace common_iterator_test {
namespace ctor_default_test {

template <typename T>
struct NoDefault
{
	T*	m_ptr;
	using difference_type = hamon::ptrdiff_t;
	NoDefault& operator++();
	void       operator++(int);
	T          operator*();
	NoDefault() = delete;
};

template <typename T>
struct ThrowOnDefault
{
	T*	m_ptr;
	using difference_type = hamon::ptrdiff_t;
	ThrowOnDefault& operator++();
	void            operator++(int);
	T               operator*();
	ThrowOnDefault() noexcept(false);
};

static_assert( hamon::is_default_constructible<
	hamon::common_iterator<int*, int const*>>::value, "");
static_assert( hamon::is_default_constructible<
	hamon::common_iterator<input_iterator_wrapper<int>, hamon::unreachable_sentinel_t>>::value, "");
static_assert(!hamon::is_default_constructible<
	hamon::common_iterator<NoDefault<int>, hamon::unreachable_sentinel_t>>::value, "");
static_assert( hamon::is_default_constructible<
	hamon::common_iterator<ThrowOnDefault<int>, hamon::unreachable_sentinel_t>>::value, "");

static_assert( hamon::is_nothrow_default_constructible<
	hamon::common_iterator<int*, int const*>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<
	hamon::common_iterator<input_iterator_wrapper<int>, hamon::unreachable_sentinel_t>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<
	hamon::common_iterator<ThrowOnDefault<int>, hamon::unreachable_sentinel_t>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	hamon::common_iterator<int*, int const*> it;
	VERIFY(it.operator->() == nullptr);
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	hamon::common_iterator<input_iterator_wrapper<int>, hamon::unreachable_sentinel_t> it1;
	hamon::common_iterator<input_iterator_wrapper<int>, hamon::unreachable_sentinel_t> it2;
	VERIFY(it1 == it2);
	return true;
}

#undef VERIFY

GTEST_TEST(CommonIteratorTest, CtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace ctor_default_test
}	// namespace common_iterator_test
}	// namespace hamon_iterator_test
