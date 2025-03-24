/**
 *	@file	unit_test_unordered_multiset_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	constexpr unordered_multiset(const unordered_multiset&);
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multiset_test
{

namespace ctor_copy_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
UNORDERED_MULTISET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::unordered_multiset<Key>;

	static_assert( hamon::is_copy_constructible<Set>::value, "");
	static_assert(!hamon::is_nothrow_copy_constructible<Set>::value, "");
	static_assert( hamon::is_implicitly_copy_constructible<Set>::value, "");
	static_assert(!hamon::is_trivially_copy_constructible<Set>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, CtorCopyTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace ctor_copy_test

}	// namespace hamon_unordered_multiset_test
