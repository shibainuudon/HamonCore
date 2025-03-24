/**
 *	@file	unit_test_unordered_set_op_assign_initializer_list.cpp
 *
 *	@brief	initializer_listを引数に取る代入演算子のテスト
 *
 *	constexpr unordered_set& operator=(initializer_list<value_type>);
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/type_traits/is_nothrow_assignable.hpp>
#include <hamon/type_traits/is_trivially_assignable.hpp>
#include <gtest/gtest.h>
#include <initializer_list>
#include "constexpr_test.hpp"

namespace hamon_unordered_set_test
{

namespace op_assign_initializer_list_test
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
	using ValueType = typename Set::value_type;

	static_assert( hamon::is_assignable<Set, std::initializer_list<ValueType>>::value, "");
	static_assert(!hamon::is_nothrow_assignable<Set, std::initializer_list<ValueType>>::value, "");
	static_assert(!hamon::is_trivially_assignable<Set, std::initializer_list<ValueType>>::value, "");

	Set v;
	VERIFY(v.empty());

	{
		auto& r = (v = { Key{1}, Key{2}, Key{3}, });
		VERIFY(&r == &v);
	}
	VERIFY(v.size() == 3);
	VERIFY(v.load_factor() <= v.max_load_factor());

	{
		auto& r = (v = { Key{1}, Key{3}, Key{5}, Key{1}, Key{5}, Key{7}, Key{3}, });
		VERIFY(&r == &v);
	}
	VERIFY(v.size() == 4);
	VERIFY(v.load_factor() <= v.max_load_factor());

	{
		auto& r = (v = { Key{42}, });
		VERIFY(&r == &v);
	}
	VERIFY(v.size() == 1);
	VERIFY(v.load_factor() <= v.max_load_factor());

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, OpAssignInitializerListTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace op_assign_initializer_list_test

}	// namespace hamon_unordered_set_test
