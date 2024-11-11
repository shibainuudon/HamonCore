/**
 *	@file	unit_test_set_max_size.cpp
 *
 *	@brief	max_size のテスト
 *
 *	size_type max_size() const noexcept;
 */

#include <hamon/set/set.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_set_test
{

namespace max_size_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
SET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::set<Key>;
	using SizeType = typename Set::size_type;

	{
		Set v;
		static_assert(hamon::is_same<decltype(v.max_size()), SizeType>::value, "");
		static_assert(noexcept(v.max_size()), "");
		VERIFY(v.max_size() > 0);
	}
	{
		Set const v;
		static_assert(hamon::is_same<decltype(v.max_size()), SizeType>::value, "");
		static_assert(noexcept(v.max_size()), "");
		VERIFY(v.max_size() > 0);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(SetTest, MaxSizeTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace max_size_test

}	// namespace hamon_set_test
