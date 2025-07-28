/**
 *	@file	unit_test_flat_multiset_op_assign_init_list.cpp
 *
 *	@brief	operator= のテスト
 *
 *	constexpr flat_multiset& operator=(initializer_list<value_type>);
 */

#include <hamon/flat_set/flat_multiset.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"
#include "flat_multiset_test_helper.hpp"

namespace hamon_flat_multiset_test
{

namespace op_assign_init_list_test
{

#if !defined(HAMON_USE_STD_FLAT_SET)
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename Compare>
FLAT_SET_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;
	using ValueType = typename Set::value_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().operator=(hamon::declval<std::initializer_list<ValueType>>())), Set&>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().operator=(hamon::declval<std::initializer_list<ValueType>>())), "");

	Set v
	{
		Key{1},
		Key{3},
	};

	VERIFY(check_invariant(v));
	VERIFY(v.size() == 2);
	VERIFY(v.count(Key{0}) == 0);
	VERIFY(v.count(Key{1}) == 1);
	VERIFY(v.count(Key{2}) == 0);
	VERIFY(v.count(Key{3}) == 1);
	VERIFY(v.count(Key{4}) == 0);

	{
		auto& r = (v = {
			Key{2},
			Key{1},
			Key{4},
		});
		VERIFY(&r == &v);
	}

	VERIFY(check_invariant(v));
	VERIFY(v.size() == 3);
	VERIFY(v.count(Key{0}) == 0);
	VERIFY(v.count(Key{1}) == 1);
	VERIFY(v.count(Key{2}) == 1);
	VERIFY(v.count(Key{3}) == 0);
	VERIFY(v.count(Key{4}) == 1);

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultisetTest, OpAssignInitListTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::less<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::less<char>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, hamon::less<int>>()));

	{
		std::initializer_list<hamon::string> elems = {"Alice", "Bob", "Carol", "Alice"};

		hamon::flat_multiset<hamon::string> fs;
		fs = elems;

		std::stringstream ss;
		for (const hamon::string& i : fs)
		{
			ss << i << ", ";
		}
		EXPECT_EQ("Alice, Alice, Bob, Carol, ", ss.str());
	}
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace op_assign_init_list_test

}	// namespace hamon_flat_multiset_test
