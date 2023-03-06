/**
 *	@file	unit_test_iterator_default_sentinel.cpp
 *
 *	@brief	default_sentinel のテスト
 */

#include <hamon/iterator/default_sentinel.hpp>
#include <hamon/concepts/semiregular.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/type_traits/is_empty.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(IteratorTest, DefaultSentinelTest)
{
	static_assert(hamon::is_empty<hamon::default_sentinel_t>::value, "");
	static_assert(hamon::semiregular_t<hamon::default_sentinel_t>::value, "");

	static_assert(hamon::same_as_t<
		decltype(hamon::default_sentinel),
		const hamon::default_sentinel_t
	>::value, "");

	hamon::default_sentinel_t s1;
	auto s2 = hamon::default_sentinel_t{};
	s2 = s1;
}
