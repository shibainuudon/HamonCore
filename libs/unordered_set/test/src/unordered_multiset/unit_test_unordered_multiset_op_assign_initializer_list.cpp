/**
 *	@file	unit_test_unordered_multiset_op_assign_initializer_list.cpp
 *
 *	@brief	initializer_listを引数に取る代入演算子のテスト
 *
 *	constexpr unordered_multiset& operator=(initializer_list<value_type>);
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/type_traits/is_nothrow_assignable.hpp>
#include <hamon/type_traits/is_trivially_assignable.hpp>
#include <gtest/gtest.h>
#include <initializer_list>
#include "constexpr_test.hpp"

namespace hamon_unordered_multiset_test
{

namespace op_assign_initializer_list_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::unordered_multiset<Key>;
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
	VERIFY(v.size() == 7);
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

GTEST_TEST(UnorderedMultisetTest, OpAssignInitializerListTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace op_assign_initializer_list_test

}	// namespace hamon_unordered_multiset_test
