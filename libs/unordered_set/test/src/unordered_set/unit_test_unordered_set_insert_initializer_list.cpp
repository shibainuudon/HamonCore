/**
 *	@file	unit_test_unordered_set_insert_initializer_list.cpp
 *
 *	@brief	insert のテスト
 *
 *	constexpr void insert(initializer_list<value_type>);
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include <initializer_list>
#include "constexpr_test.hpp"
#include "unordered_set_test_helper.hpp"

namespace hamon_unordered_set_test
{

namespace insert_initializer_list_test
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

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().insert(hamon::declval<std::initializer_list<ValueType>>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().insert(hamon::declval<std::initializer_list<ValueType>>())), "");

	Set v;

	v.insert({ Key{3}, Key{2}, Key{3}, Key{1}, Key{2}, Key{3} });
	VERIFY(!v.empty());
	VERIFY(v.size() == 3);
	VERIFY(v.load_factor() <= v.max_load_factor());

	v.insert({ Key{2}, Key{4}, Key{0}, Key{1} });
	VERIFY(!v.empty());
	VERIFY(v.size() == 5);
	VERIFY(v.load_factor() <= v.max_load_factor());

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, InsertInitializerListTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		using Set = hamon::unordered_set<ThrowOnCopyIfNegative, hamon::hash<ThrowOnCopyIfNegative>>;

		Set v;
		EXPECT_EQ(0u, v.size());

		// ThrowOnCopyIfNegative{-30} をコピーするときに例外を投げる
		EXPECT_THROW(v.insert({
			ThrowOnCopyIfNegative{ 10},
			ThrowOnCopyIfNegative{ 20},
			ThrowOnCopyIfNegative{-30},
			ThrowOnCopyIfNegative{ 40},
		}), ThrowOnCopyIfNegative::Exception);
		EXPECT_EQ(2u, v.size());

		v.insert(ThrowOnCopyIfNegative{-30});
		EXPECT_EQ(3u, v.size());

		// ThrowOnCopyIfNegative{-30} は挿入されないので例外を投げない
		EXPECT_NO_THROW(v.insert({
			ThrowOnCopyIfNegative{ 20},
			ThrowOnCopyIfNegative{-30},
			ThrowOnCopyIfNegative{ 40},
			ThrowOnCopyIfNegative{ 50},
		}));
		EXPECT_EQ(5u, v.size());
	}
#endif
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace insert_initializer_list_test

}	// namespace hamon_unordered_set_test
