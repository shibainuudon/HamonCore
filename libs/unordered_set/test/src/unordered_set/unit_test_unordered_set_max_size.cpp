/**
 *	@file	unit_test_unordered_set_max_size.cpp
 *
 *	@brief	max_size のテスト
 *
 *	constexpr size_type max_size() const noexcept;
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_set_test
{

namespace max_size_test
{

#if !defined(HAMON_USE_STD_UNORDERED_SET) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
UNORDERED_SET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::unordered_set<Key>;
	using SizeType  = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().max_size()), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().max_size()), SizeType>::value, "");
	static_assert(noexcept(hamon::declval<Set&>().max_size()), "");
	static_assert(noexcept(hamon::declval<Set const&>().max_size()), "");

	Set const v;
	VERIFY(v.max_size() > 0);

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, MaxSizeTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace max_size_test

}	// namespace hamon_unordered_set_test
