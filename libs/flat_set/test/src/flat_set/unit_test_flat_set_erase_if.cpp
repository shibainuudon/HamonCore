/**
 *	@file	unit_test_flat_set_erase_if.cpp
 *
 *	@brief	erase_if のテスト
 *
 *	template<class Key, class Compare, class KeyContainer, class Predicate>
 *	constexpr typename flat_set<Key, Compare, KeyContainer>::size_type
 *	erase_if(flat_set<Key, Compare, KeyContainer>& c, Predicate pred);
 */

#include <hamon/flat_set/flat_set.hpp>
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
#include "flat_set_test_helper.hpp"

namespace hamon_flat_set_test
{

namespace erase_if_test
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
	using ConstReference = typename Set::const_reference;
	using ValueType = typename Set::value_type;
	using SizeType = typename Set::size_type;

	struct F1
	{
		constexpr bool operator()(ConstReference x) const noexcept
		{
			return x < 3;
		}
	};

	struct F2
	{
		constexpr bool operator()(ValueType x) const
		{
			return x == 3;
		}
	};

	static_assert(hamon::is_same<decltype(hamon::erase_if(hamon::declval<Set&>(), F1{})), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::erase_if(hamon::declval<Set&>(), F2{})), SizeType>::value, "");
	static_assert(!noexcept(hamon::erase_if(hamon::declval<Set&>(), F1{})), "");
	static_assert(!noexcept(hamon::erase_if(hamon::declval<Set&>(), F2{})), "");

	{
		Set v
		{
			Key{3},
			Key{1},
			Key{4},
			Key{5},
			Key{2},
		};

		auto r = hamon::erase_if(v, F1{});
		VERIFY(r == 2);
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 3);
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 1);
		VERIFY(v.count(Key{5}) == 1);
	}
	{
		Set v
		{
			Key{3},
			Key{1},
			Key{4},
			Key{5},
			Key{2},
		};

		auto r = hamon::erase_if(v, F2{});
		VERIFY(r == 1);
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 4);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 0);
		VERIFY(v.count(Key{4}) == 1);
		VERIFY(v.count(Key{5}) == 1);
	}
	{
		Set v;
		auto r = hamon::erase_if(v, F1{});
		VERIFY(r == 0);
		VERIFY(v.size() == 0);
	}
	{
		Set v
		{
			Key{3},
			Key{1},
			Key{4},
		};

		auto r = hamon::erase_if(v, [](ValueType){return true;});
		VERIFY(r == 3);
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 0);
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 0);
		VERIFY(v.count(Key{4}) == 0);
		VERIFY(v.count(Key{5}) == 0);
	}

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
		using KeyContainer = ThrowOnEraseContainer<Key>;
		using Set = hamon::flat_set<Key, Comp, KeyContainer>;
		using ConstReference = typename Set::const_reference;

		KeyContainer a{Key{1}, Key{2}, Key{3}, Key{4}};
		Set v(hamon::sorted_unique, hamon::move(a));

		EXPECT_THROW(hamon::erase_if(v, [](ConstReference x){return x % 2 == 0;}), int);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatSetTest, EraseIfTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::less<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::greater<double>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, hamon::less<>>()));

	test_exceptions<hamon::vector>();
	test_exceptions<hamon::deque>();

	{
		hamon::flat_set<int> fs = {3, 1, 4};

		// コンテナfsから、キー1をもつ要素をすべて削除する
		hamon::erase_if(fs, [](const int& x) { return x == 1; });

		std::stringstream ss;
		for (int i : fs)
		{
			ss << i << ", ";
		}
		EXPECT_EQ("3, 4, ", ss.str());
	}
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace erase_if_test

}	// namespace hamon_flat_set_test
