/**
 *	@file	unit_test_unordered_set_key_eq.cpp
 *
 *	@brief	key_eq のテスト
 *
 *	constexpr key_equal key_eq() const;
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_set_test_helper.hpp"

namespace hamon_unordered_set_test
{

namespace key_eq_test
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
	using Set = hamon::unordered_set<Key, hamon::hash<Key>, TestEqualTo<Key>>;
	using Hasher = typename Set::hasher;
	using KeyEqual = typename Set::key_equal;

	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().key_eq()), KeyEqual>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_SET)
	static_assert( noexcept(hamon::declval<Set const&>().key_eq()), "");
#endif

	KeyEqual pred1{42};
	KeyEqual pred2{43};
	{
		Set v{17, Hasher{}, pred1};
		VERIFY(v.key_eq() == pred1);
		VERIFY(v.key_eq() != pred2);
	}
	{
		Set v{17, Hasher{}, pred2};
		VERIFY(v.key_eq() != pred1);
		VERIFY(v.key_eq() == pred2);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, KeyEqTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace key_eq_test

}	// namespace hamon_unordered_set_test
