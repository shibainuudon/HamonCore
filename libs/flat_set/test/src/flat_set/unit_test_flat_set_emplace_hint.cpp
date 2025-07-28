/**
 *	@file	unit_test_flat_set_emplace_hint.cpp
 *
 *	@brief	emplace_hint のテスト
 *
 *	template<class... Args>
 *	constexpr iterator emplace_hint(const_iterator position, Args&&... args);
 */

#include <hamon/flat_set/flat_set.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/iterator.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"
#include "flat_set_test_helper.hpp"

namespace hamon_flat_set_test
{

namespace emplace_hint_test
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
	using ConstIterator = typename Set::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().emplace_hint(hamon::declval<ConstIterator>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<ValueType const&>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<ValueType&&>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<Key>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().emplace_hint(hamon::declval<ConstIterator>())), "");
	static_assert(!noexcept(hamon::declval<Set&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<ValueType const&>())), "");
	static_assert(!noexcept(hamon::declval<Set&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<ValueType&&>())), "");
	static_assert(!noexcept(hamon::declval<Set&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<Key>())), "");

	Set v;
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 0);
	VERIFY(v.count(Key{0}) == 0);
	VERIFY(v.count(Key{1}) == 0);
	VERIFY(v.count(Key{2}) == 0);
	VERIFY(v.count(Key{3}) == 0);
	VERIFY(v.count(Key{4}) == 0);
	{
		auto r = v.emplace_hint(v.cbegin(), Key{1});
		VERIFY(*r == Key{1});
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 1);
	VERIFY(v.count(Key{0}) == 0);
	VERIFY(v.count(Key{1}) == 1);
	VERIFY(v.count(Key{2}) == 0);
	VERIFY(v.count(Key{3}) == 0);
	VERIFY(v.count(Key{4}) == 0);
	{
		auto r = v.emplace_hint(v.end(), Key{1});
		VERIFY(*r == Key{1});
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 1);
	VERIFY(v.count(Key{0}) == 0);
	VERIFY(v.count(Key{1}) == 1);
	VERIFY(v.count(Key{2}) == 0);
	VERIFY(v.count(Key{3}) == 0);
	VERIFY(v.count(Key{4}) == 0);
	{
		ValueType const t{Key{2}};
		auto r = v.emplace_hint(v.begin(), t);
		VERIFY(*r == Key{2});
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 2);
	VERIFY(v.count(Key{0}) == 0);
	VERIFY(v.count(Key{1}) == 1);
	VERIFY(v.count(Key{2}) == 1);
	VERIFY(v.count(Key{3}) == 0);
	VERIFY(v.count(Key{4}) == 0);
	{
		ValueType const t{Key{2}};
		auto r = v.emplace_hint(v.cend(), t);
		VERIFY(*r == Key{2});
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 2);
	VERIFY(v.count(Key{0}) == 0);
	VERIFY(v.count(Key{1}) == 1);
	VERIFY(v.count(Key{2}) == 1);
	VERIFY(v.count(Key{3}) == 0);
	VERIFY(v.count(Key{4}) == 0);
	{
		ValueType t{Key{2}};
		auto r = v.emplace_hint(v.end(), hamon::move(t));
		VERIFY(*r == Key{2});
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 2);
	VERIFY(v.count(Key{0}) == 0);
	VERIFY(v.count(Key{1}) == 1);
	VERIFY(v.count(Key{2}) == 1);
	VERIFY(v.count(Key{3}) == 0);
	VERIFY(v.count(Key{4}) == 0);
	{
		ValueType t{Key{0}};
		auto r = v.emplace_hint(v.begin(), hamon::move(t));
		VERIFY(*r == Key{0});
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 3);
	VERIFY(v.count(Key{0}) == 1);
	VERIFY(v.count(Key{1}) == 1);
	VERIFY(v.count(Key{2}) == 1);
	VERIFY(v.count(Key{3}) == 0);
	VERIFY(v.count(Key{4}) == 0);

	return true;
}

template <typename Void, typename T, typename... Args>
struct is_emplace_hint_invocable_impl
	: hamon::false_type {};

template <typename T, typename... Args>
struct is_emplace_hint_invocable_impl<
	hamon::void_t<decltype(hamon::declval<T>().emplace_hint(hamon::declval<Args>()...))>, T, Args...>
	: hamon::true_type {};

template <typename T, typename... Args>
using is_emplace_hint_invocable = is_emplace_hint_invocable_impl<void, T, Args...>;

struct S1
{
	int x;
	int y;

	constexpr S1(int i, int j) : x(i), y(j) {}

	friend constexpr bool operator<(S1 const& lhs, S1 const& rhs)
	{
		return lhs.x < rhs.x;
	}
};

FLAT_SET_TEST_CONSTEXPR bool test2()
{
	using Set = hamon::flat_set<S1>;
	using ConstIterator = typename Set::const_iterator;

	static_assert( is_emplace_hint_invocable<Set&, ConstIterator, S1>::value, "");
	static_assert(!is_emplace_hint_invocable<Set&, ConstIterator, int>::value, "");
	static_assert( is_emplace_hint_invocable<Set&, ConstIterator, int, int>::value, "");
	static_assert(!is_emplace_hint_invocable<Set&, ConstIterator, int, int, int>::value, "");
	static_assert(!is_emplace_hint_invocable<Set const&, ConstIterator, S1>::value, "");
	static_assert(!is_emplace_hint_invocable<Set const&, ConstIterator, int>::value, "");
	static_assert(!is_emplace_hint_invocable<Set const&, ConstIterator, int, int>::value, "");
	static_assert(!is_emplace_hint_invocable<Set const&, ConstIterator, int, int, int>::value, "");

	Set v;

	{
		auto r = v.emplace_hint(v.begin(), 10, 20);
		VERIFY(r->x == 10);
		VERIFY(r->y == 20);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 1);
	}
	{
		auto r = v.emplace_hint(v.begin(), 10, 30);
		VERIFY(r->x == 10);
		VERIFY(r->y == 20);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 1);
	}
	{
		auto r = v.emplace_hint(v.begin(), 20, 30);
		VERIFY(r->x == 20);
		VERIFY(r->y == 30);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 2);
	}

	return true;
}

template <typename KeyContainer>
FLAT_SET_TEST_CONSTEXPR bool test3()
{
	using Key = typename KeyContainer::value_type;
	using Set = hamon::flat_set<Key, hamon::less<Key>, KeyContainer>;
	using ValueType = typename Set::value_type;

	{
		// was empty
		Set m;
		auto r = m.emplace_hint(m.end(), ValueType(2));
		VERIFY(r == m.begin());
		VERIFY(m.size() == 1);
		VERIFY(*r == 2);
	}
	{
		// hints correct at the begin
		Set m = {3, 4};
		auto hint = m.begin();
		auto r = m.emplace_hint(hint, ValueType(2));
		VERIFY(r == m.begin());
		VERIFY(m.size() == 3);
		VERIFY(*r == 2);
	}
	{
		// hints correct in the middle
		Set m = {0, 1, 3, 4};
		auto hint = m.begin() + 2;
		auto r = m.emplace_hint(hint, ValueType(2));
		VERIFY(r == m.begin() + 2);
		VERIFY(m.size() == 5);
		VERIFY(*r == 2);
	}
	{
		// hints correct at the end
		Set m = {0, 1};
		auto hint = m.end();
		auto r = m.emplace_hint(hint, ValueType(2));
		VERIFY(r == m.begin() + 2);
		VERIFY(m.size() == 3);
		VERIFY(*r == 2);
	}
	{
		// hints correct but key already exists
		Set m = {0, 1, 2, 3, 4};
		auto hint = m.begin() + 2;
		auto r = m.emplace_hint(hint, ValueType(2));
		VERIFY(r == m.begin() + 2);
		VERIFY(m.size() == 5);
		VERIFY(*r == 2);
	}
	{
		// hints incorrectly at the begin
		Set m = {1, 4};
		auto hint = m.begin();
		auto r = m.emplace_hint(hint, ValueType(2));
		VERIFY(r == m.begin() + 1);
		VERIFY(m.size() == 3);
		VERIFY(*r == 2);
	}
	{
		// hints incorrectly in the middle
		Set m = {0, 1, 3, 4};
		auto hint = m.begin() + 1;
		auto r = m.emplace_hint(hint, ValueType(2));
		VERIFY(r == m.begin() + 2);
		VERIFY(m.size() == 5);
		VERIFY(*r == 2);
	}
	{
		// hints incorrectly at the end
		Set m = {0, 3};
		auto hint = m.end();
		auto r = m.emplace_hint(hint, ValueType(2));
		VERIFY(r == m.begin() + 1);
		VERIFY(m.size() == 3);
		VERIFY(*r == 2);
	}
	{
		// hints incorrect and key already exists
		Set m = {0, 1, 2, 3, 4};
		auto hint = m.begin();
		auto r = m.emplace_hint(hint, ValueType(2));
		VERIFY(r == m.begin() + 2);
		VERIFY(m.size() == 5);
		VERIFY(*r == 2);
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
		using KeyContainer = TKeyContainer<Key, ThrowAllocator<Key>>;
		using Set = hamon::flat_set<Key, Comp, KeyContainer>;
		using ValueType = typename Set::value_type;

		int throw_after = INT_MAX;

		KeyContainer a({Key{1}, Key{2}, Key{3}, Key{4}}, ThrowAllocator<Key>{&throw_after});
		Set v(hamon::sorted_unique, hamon::move(a));

		throw_after = 1;

		EXPECT_THROW(v.emplace_hint(v.end(), ValueType{0}), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = EmplaceUnsafeContainer<Key>;
		using Set = hamon::flat_set<Key, Comp, KeyContainer>;
		using ValueType = typename Set::value_type;

		KeyContainer a{Key{1}, Key{2}, Key{3}, Key{4}};
		Set v(hamon::sorted_unique, hamon::move(a));

		EXPECT_THROW(v.emplace_hint(v.end(), ValueType{0}), int);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatSetTest, EmplaceHintTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::less<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::less<>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, hamon::less<int>>()));

	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE(test2());

	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test3<hamon::vector<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test3<hamon::deque<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test3<MinSequenceContainer<int>>()));

	test_exceptions<hamon::vector>();
	test_exceptions<hamon::deque>();

	{
		hamon::flat_set<int> fs = {3, 1, 4};

		// キー5の要素が最後尾に追加されることが事前にわかっているので、fs.end()をヒントとして与える
		fs.emplace_hint(fs.end(), 5);

		std::stringstream ss;
		for (int i : fs)
		{
			ss << i << ", ";
		}
		EXPECT_EQ("1, 3, 4, 5, ", ss.str());
	}
	{
		hamon::flat_set<hamon::string> fs;
		const char aaa[3] = {'A', 'A', 'A'};

		fs.emplace_hint(fs.begin(), 5u, 'C');
		fs.emplace_hint(fs.end(), "BBBB");
		fs.emplace_hint(fs.begin(), hamon::begin(aaa), hamon::end(aaa));

		std::stringstream ss;
		for (auto const& i : fs)
		{
			ss << i << ", ";
		}
		EXPECT_EQ("AAA, BBBB, CCCCC, ", ss.str());
	}
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace emplace_hint_test

}	// namespace hamon_flat_set_test
