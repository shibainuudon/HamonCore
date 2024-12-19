/**
 *	@file	unit_test_multiset_op_assign_initializer_list.cpp
 *
 *	@brief	initializer_listを引数に取る代入演算子のテスト
 *
 *	multiset& operator=(initializer_list<value_type>);
 */

#include <hamon/set/multiset.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multiset_test
{

namespace op_assign_initializer_list_test
{

#if !defined(HAMON_USE_STD_MULTISET)
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
MULTISET_TEST_CONSTEXPR bool test1()
{
	using Set = hamon::multiset<Key>;
	using ValueType = typename Set::value_type;
	using IL = std::initializer_list<ValueType>;

	static_assert( hamon::is_assignable<Set, IL>::value, "");
	static_assert(!hamon::is_nothrow_assignable<Set, IL>::value, "");
	static_assert(!hamon::is_trivially_assignable<Set, IL>::value, "");

	Set v1;
	VERIFY(v1.empty());

	{
		auto& r = (v1 = {Key{3}, Key{1}, Key{4}});
		VERIFY(&r == &v1);
		VERIFY(v1.size() == 3);
		{
			auto it = v1.begin();
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{4});
			VERIFY(it == v1.end());
		}
	}
	{
		auto& r = (v1 = {Key{3}, Key{1}, Key{4}, Key{5}, Key{2}, Key{3}, Key{4}, Key{5}, Key{4}});
		VERIFY(&r == &v1);
		VERIFY(v1.size() == 9);
		{
			auto it = v1.begin();
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{2});
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{4});
			VERIFY(*it++ == Key{4});
			VERIFY(*it++ == Key{4});
			VERIFY(*it++ == Key{5});
			VERIFY(*it++ == Key{5});
			VERIFY(it == v1.end());
		}
	}
	{
		auto& r = (v1 = {});
		VERIFY(&r == &v1);
		VERIFY(v1.empty());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MultisetTest, OpAssignInitializerListTest)
{
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());
}

#undef MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTISET_TEST_CONSTEXPR

}	// namespace op_assign_initializer_list_test

}	// namespace hamon_multiset_test
