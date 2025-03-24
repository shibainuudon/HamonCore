/**
 *	@file	unit_test_unordered_set_hash_function.cpp
 *
 *	@brief	hash_function のテスト
 *
 *	constexpr hasher hash_function() const;
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_set_test_helper.hpp"

namespace hamon_unordered_set_test
{

namespace hash_function_test
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
	using Set = hamon::unordered_set<Key, TestHash<Key>>;
	using Hasher = typename Set::hasher;

	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().hash_function()), Hasher>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_SET)
	static_assert( noexcept(hamon::declval<Set const&>().hash_function()), "");
#endif

	Hasher h1{42};
	Hasher h2{43};
	{
		Set v{17, h1};
		VERIFY(v.hash_function() == h1);
		VERIFY(v.hash_function() != h2);
	}
	{
		Set v{17, h2};
		VERIFY(v.hash_function() != h1);
		VERIFY(v.hash_function() == h2);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, HashFunctionTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace hash_function_test

}	// namespace hamon_unordered_set_test
