/**
 *	@file	unit_test_iterator_unreachable_sentinel.cpp
 *
 *	@brief	unreachable_sentinel のテスト
 */

#include <hamon/iterator/unreachable_sentinel.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/semiregular.hpp>
#include <hamon/concepts/detail/weakly_eq_cmp_with.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_empty.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "noexcept_test.hpp"
#include "constexpr_test.hpp"

namespace hamon_iterator_test
{

namespace unreachable_sentinel_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename U>
using weakly_equality_comparable_with_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::detail::weakly_eq_cmp_with<T, U>>;
#else
	hamon::detail::weakly_eq_cmp_with<T, U>;
#endif

HAMON_CXX14_CONSTEXPR bool test01()
{
	static_assert(hamon::is_empty<hamon::unreachable_sentinel_t>::value, "");
	static_assert(hamon::semiregular_t<hamon::unreachable_sentinel_t>::value, "");

	static_assert(hamon::same_as_t<
		decltype(hamon::unreachable_sentinel),
		const hamon::unreachable_sentinel_t
	>::value, "");

	auto sentinel = hamon::unreachable_sentinel;
	int i = 42;
	VERIFY(i != sentinel);
	VERIFY(sentinel != i);
	VERIFY(!(i == sentinel));
	VERIFY(!(sentinel == i));

	VERIFY(&i != sentinel);
	VERIFY(sentinel != &i);
	VERIFY(!(&i == sentinel));
	VERIFY(!(sentinel == &i));

	int *p = nullptr;
	VERIFY(p != sentinel);
	VERIFY(sentinel != p);
	VERIFY(!(p == sentinel));
	VERIFY(!(sentinel == p));

	static_assert( weakly_equality_comparable_with_t<hamon::unreachable_sentinel_t, int>::value, "");
	static_assert( weakly_equality_comparable_with_t<hamon::unreachable_sentinel_t, int*>::value, "");
	static_assert(!weakly_equality_comparable_with_t<hamon::unreachable_sentinel_t, void*>::value, "");
	HAMON_ASSERT_NOEXCEPT_TRUE(sentinel == p);
	HAMON_ASSERT_NOEXCEPT_TRUE(sentinel != p);

	return true;
}

#undef VERIFY

GTEST_TEST(IteratorTest, UnreachableSentinelTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace unreachable_sentinel_test

}	// namespace hamon_iterator_test
