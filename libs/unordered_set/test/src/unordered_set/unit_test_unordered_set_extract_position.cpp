/**
 *	@file	unit_test_unordered_set_extract_position.cpp
 *
 *	@brief	extract のテスト
 *
 *	constexpr node_type extract(const_iterator position);
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_set_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_SET) || \
	(defined(__cpp_lib_node_extract) && (__cpp_lib_node_extract >= 201606L))

namespace hamon_unordered_set_test
{

namespace extract_position_test
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
	using NodeType = typename Set::node_type;
	using ConstIterator = typename Set::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().extract(hamon::declval<ConstIterator>())), NodeType>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_SET)
	static_assert( noexcept(hamon::declval<Set&>().extract(hamon::declval<ConstIterator>())), "");
#endif

	Set v
	{
		Key{3}, Key{1}, Key{4}, Key{1}, Key{5}, Key{4}, Key{4},
	};
	VERIFY(v.size() == 4);

	{
		auto i = v.begin();
		auto& x = *i;
		auto r = v.extract(i);
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.value() == x);
		VERIFY(v.size() == 3);
	}
	{
		auto i = hamon::next(v.begin(), 2);
		auto& x = *i;
		auto r = v.extract(i);
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.value() == x);
		VERIFY(v.size() == 2);
	}
	{
		auto i = hamon::next(v.begin(), 1);
		auto& x = *i;
		auto r = v.extract(i);
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.value() == x);
		VERIFY(v.size() == 1);
	}
	{
		auto i = v.begin();
		auto& x = *i;
		auto r = v.extract(i);
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.value() == x);
		VERIFY(v.size() == 0);
	}

	return true;
}

template <typename Key>
UNORDERED_SET_TEST_CONSTEXPR bool test_noexcept()
{
#if !defined(HAMON_USE_STD_UNORDERED_SET)
	{
		using Set = hamon::unordered_set<Key, NoThrowHash<Key>, NoThrowEqualTo<Key>>;
		using ConstIterator = typename Set::const_iterator;
		static_assert( noexcept(hamon::declval<Set&>().extract(hamon::declval<ConstIterator>())), "");
	}
	{
		using Set = hamon::unordered_set<Key, NoThrowHash<Key>, ThrowEqualTo<Key>>;
		using ConstIterator = typename Set::const_iterator;
		static_assert( noexcept(hamon::declval<Set&>().extract(hamon::declval<ConstIterator>())), "");
	}
	{
		using Set = hamon::unordered_set<Key, ThrowHash<Key>, NoThrowEqualTo<Key>>;
		using ConstIterator = typename Set::const_iterator;
		static_assert( noexcept(hamon::declval<Set&>().extract(hamon::declval<ConstIterator>())), "");
	}
	{
		using Set = hamon::unordered_set<Key, ThrowHash<Key>, ThrowEqualTo<Key>>;
		using ConstIterator = typename Set::const_iterator;
		static_assert( noexcept(hamon::declval<Set&>().extract(hamon::declval<ConstIterator>())), "");
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, ExtractPositionTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));

	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<float>()));
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace extract_position_test

}	// namespace hamon_unordered_set_test

#endif
