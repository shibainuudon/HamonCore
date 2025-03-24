/**
 *	@file	unit_test_unordered_multiset_op_assign_initializer_list.cpp
 *
 *	@brief	initializer_listを引数に取る代入演算子のテスト
 *
 *	constexpr unordered_multiset& operator=(initializer_list<value_type>);
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multiset_test
{

namespace op_assign_initializer_list_test
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
	using ValueType = typename Set::value_type;

	static_assert( hamon::is_assignable<Set, std::initializer_list<ValueType>>::value, "");
	static_assert(!hamon::is_nothrow_assignable<Set, std::initializer_list<ValueType>>::value, "");
	static_assert(!hamon::is_trivially_assignable<Set, std::initializer_list<ValueType>>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, OpAssignInitializerListTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace op_assign_initializer_list_test

}	// namespace hamon_unordered_multiset_test
