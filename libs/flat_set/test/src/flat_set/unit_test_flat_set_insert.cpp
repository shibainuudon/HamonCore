/**
 *	@file	unit_test_flat_set_insert.cpp
 *
 *	@brief	insert のテスト
 *
 *	constexpr pair<iterator, bool> insert(const value_type& x);
 *	constexpr pair<iterator, bool> insert(value_type&& x);
 */

#include <hamon/flat_set/flat_set.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"
#include "flat_set_test_helper.hpp"

namespace hamon_flat_set_test
{

namespace insert_test
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
	using Set = hamon::flat_set<Key, Compare, KeyContainer>;
	using ValueType = typename Set::value_type;
	using Iterator = typename Set::iterator;
#if defined(HAMON_USE_STD_FLAT_SET)
	using Result = std::pair<Iterator, bool>;
#else
	using Result = hamon::pair<Iterator, bool>;
#endif

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().insert(hamon::declval<ValueType const&>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().insert(hamon::declval<ValueType&&>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().insert(hamon::declval<ValueType const&>())), "");
	static_assert(!noexcept(hamon::declval<Set&>().insert(hamon::declval<ValueType&&>())), "");

	Set v;
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 0);
	VERIFY(v.count(Key{0}) == 0);
	VERIFY(v.count(Key{1}) == 0);
	VERIFY(v.count(Key{2}) == 0);
	VERIFY(v.count(Key{3}) == 0);
	VERIFY(v.count(Key{4}) == 0);
	{
		ValueType const x{Key{1}};
		auto r = v.insert(x);
		VERIFY(*(r.first) == Key{1});
		VERIFY(r.second == true);
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 1);
	VERIFY(v.count(Key{0}) == 0);
	VERIFY(v.count(Key{1}) == 1);
	VERIFY(v.count(Key{2}) == 0);
	VERIFY(v.count(Key{3}) == 0);
	VERIFY(v.count(Key{4}) == 0);
	{
		ValueType x{Key{2}};
		auto r = v.insert(hamon::move(x));
		VERIFY(*(r.first) == Key{2});
		VERIFY(r.second == true);
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 2);
	VERIFY(v.count(Key{0}) == 0);
	VERIFY(v.count(Key{1}) == 1);
	VERIFY(v.count(Key{2}) == 1);
	VERIFY(v.count(Key{3}) == 0);
	VERIFY(v.count(Key{4}) == 0);
	{
		ValueType x{Key{1}};
		auto r = v.insert(hamon::move(x));
		VERIFY(*(r.first) == Key{1});
		VERIFY(r.second == false);
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 2);
	VERIFY(v.count(Key{0}) == 0);
	VERIFY(v.count(Key{1}) == 1);
	VERIFY(v.count(Key{2}) == 1);
	VERIFY(v.count(Key{3}) == 0);
	VERIFY(v.count(Key{4}) == 0);
	{
		ValueType const x{Key{2}};
		auto r = v.insert(x);
		VERIFY(*(r.first) == Key{2});
		VERIFY(r.second == false);
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 2);
	VERIFY(v.count(Key{0}) == 0);
	VERIFY(v.count(Key{1}) == 1);
	VERIFY(v.count(Key{2}) == 1);
	VERIFY(v.count(Key{3}) == 0);
	VERIFY(v.count(Key{4}) == 0);

	return true;
}

#undef VERIFY

template <template <typename...> class TKeyContainer>
void test_exceptions()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	using Key = int;
	using Comp = hamon::less<Key>;
	{
		using KeyContainer = TKeyContainer<Key, ThrowAllocator<Key>>;
		using Set = hamon::flat_set<Key, Comp, KeyContainer>;
		using ValueType = typename Set::value_type;

		int throw_after = INT_MAX;

		KeyContainer a({Key{1}, Key{2}, Key{3}, Key{4}}, ThrowAllocator<Key>{&throw_after});
		Set v(hamon::sorted_unique, hamon::move(a));

		throw_after = 1;

		EXPECT_THROW(v.insert(ValueType(0)), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = EmplaceUnsafeContainer<Key>;
		using Set = hamon::flat_set<Key, Comp, KeyContainer>;
		using ValueType = typename Set::value_type;

		KeyContainer a{Key{1}, Key{2}, Key{3}, Key{4}};
		Set v(hamon::sorted_unique, hamon::move(a));

		ValueType const x{0};
		EXPECT_THROW(v.insert(x), int);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatSetTest, InsertTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::less<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::greater<char>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, hamon::less<int>>()));

	test_exceptions<hamon::vector>();
	test_exceptions<hamon::deque>();

	{
		hamon::flat_set<int> fs;

		// 単一要素を挿入する
		fs.insert(1);

		// シーケンスを挿入する
		hamon::vector<int> v = {2, 3, 4};
		fs.insert(v.begin(), v.end());

		// 挿入するシーケンスがソート済みかつ重複要素がないことがわかっている場合、
		// 以下のように指定した方が高速になる
		fs.insert(hamon::sorted_unique, {5, 6, 7});

		std::stringstream ss;
		for (int i : fs)
		{
			ss << i << ", ";
		}
		EXPECT_EQ("1, 2, 3, 4, 5, 6, 7, ", ss.str());
	}
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace insert_test

}	// namespace hamon_flat_set_test
