/**
 *	@file	unit_test_flat_multiset_erase_position.cpp
 *
 *	@brief	erase のテスト
 *
 *	constexpr iterator erase(iterator position);
 *	constexpr iterator erase(const_iterator position);
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
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"
#include "flat_multiset_test_helper.hpp"

namespace hamon_flat_multiset_test
{

namespace erase_position_test
{

#if !defined(HAMON_USE_STD_FLAT_SET)
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer>
FLAT_SET_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;

	{
		using Set = hamon::flat_multiset<Key, hamon::less<Key>, KeyContainer>;
		using Iterator = typename Set::iterator;
		using ConstIterator = typename Set::const_iterator;

		static_assert(hamon::is_same<decltype(hamon::declval<Set&>().erase(hamon::declval<Iterator>())), Iterator>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Set&>().erase(hamon::declval<ConstIterator>())), Iterator>::value, "");
		static_assert(!noexcept(hamon::declval<Set&>().erase(hamon::declval<Iterator>())), "");
		static_assert(!noexcept(hamon::declval<Set&>().erase(hamon::declval<ConstIterator>())), "");

		Set v
		{
			Key{3},
			Key{1},
			Key{3},
			Key{2},
			Key{2},
			Key{3},
		};
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 6);
		VERIFY(!v.empty());
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 2);
		VERIFY(v.count(Key{3}) == 3);
		{
			auto it = v.erase(v.begin());
			VERIFY(it == v.begin());
			VERIFY(*it == Key{2});
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 5);
		VERIFY(!v.empty());
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 2);
		VERIFY(v.count(Key{3}) == 3);
		{
			auto it = v.erase(v.begin() + 1);
			VERIFY(it == v.begin() + 1);
			VERIFY(*it == Key{3});
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 4);
		VERIFY(!v.empty());
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 3);
		{
			auto it = v.erase(v.begin() + 1);
			VERIFY(it == v.begin() + 1);
			VERIFY(*it == Key{3});
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 3);
		VERIFY(!v.empty());
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 2);
		{
			auto it = v.erase(v.begin() + 2);
			VERIFY(it == v.end());
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 2);
		VERIFY(!v.empty());
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 1);
	}
	{
		using Set = hamon::flat_multiset<Key, hamon::greater<Key>, KeyContainer>;
		using Iterator = typename Set::iterator;
		using ConstIterator = typename Set::const_iterator;

		static_assert(hamon::is_same<decltype(hamon::declval<Set&>().erase(hamon::declval<Iterator>())), Iterator>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Set&>().erase(hamon::declval<ConstIterator>())), Iterator>::value, "");
		static_assert(!noexcept(hamon::declval<Set&>().erase(hamon::declval<Iterator>())), "");
		static_assert(!noexcept(hamon::declval<Set&>().erase(hamon::declval<ConstIterator>())), "");

		Set v
		{
			Key{3},
			Key{1},
			Key{3},
			Key{2},
			Key{2},
			Key{3},
		};
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 6);
		VERIFY(!v.empty());
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 2);
		VERIFY(v.count(Key{3}) == 3);
		{
			auto it = v.erase(v.cbegin());
			VERIFY(it == v.begin());
			VERIFY(*it == Key{3});
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 5);
		VERIFY(!v.empty());
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 2);
		VERIFY(v.count(Key{3}) == 2);
		{
			auto it = v.erase(v.cbegin() + 2);
			VERIFY(it == v.begin() + 2);
			VERIFY(*it == Key{2});
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 4);
		VERIFY(!v.empty());
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 2);
		{
			auto it = v.erase(v.cbegin() + 3);
			VERIFY(it == v.end());
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 3);
		VERIFY(!v.empty());
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 2);
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
		using Set = hamon::flat_multiset<Key, Comp, KeyContainer>;

		KeyContainer a{Key{1}, Key{2}, Key{3}, Key{4}};
		Set v(hamon::sorted_equivalent, hamon::move(a));

		EXPECT_THROW(v.erase(v.begin() + 1), int);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatMultisetTest, ErasePositionTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<float>>()));

	test_exceptions<hamon::vector>();
	test_exceptions<hamon::deque>();
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace erase_position_test

}	// namespace hamon_flat_multiset_test
