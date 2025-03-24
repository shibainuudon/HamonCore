/**
 *	@file	unit_test_unordered_set_emplace_hint.cpp
 *
 *	@brief	emplace_hint のテスト
 *
 *	template<class... Args>
 *	constexpr iterator emplace_hint(const_iterator position, Args&&... args);
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/pair/pair.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_set_test_helper.hpp"

namespace hamon_unordered_set_test
{

namespace emplace_hint_test
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
UNORDERED_SET_TEST_CONSTEXPR bool test1()
{
	using Set = hamon::unordered_set<Key>;
	using ValueType = typename Set::value_type;
	using Iterator = typename Set::iterator;
	using ConstIterator = typename Set::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<ValueType&&>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<ValueType const&>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<ValueType&&>())), "");
	static_assert(!noexcept(hamon::declval<Set&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<ValueType const&>())), "");

	Set v;

	{
		auto r = v.emplace_hint(v.cbegin(), Key{10});
		VERIFY(*r == 10);

		VERIFY(v.size() == 1);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	{
		auto r = v.emplace_hint(v.cend(), Key{10});
		VERIFY(*r == 10);

		VERIFY(v.size() == 1);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	{
		Key const k{20};
		auto r = v.emplace_hint(v.end(), k);
		VERIFY(*r == 20);

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	{
		Key const k{20};
		auto r = v.emplace_hint(v.begin(), k);
		VERIFY(*r == 20);

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}

	return true;
}

struct S1
{
	int x;
	int y;

	constexpr S1(int i, int j) : x(i), y(j) {}

	S1(S1&&)                 = delete;
	S1(S1 const&)            = delete;
	S1& operator=(S1&&)      = delete;
	S1& operator=(S1 const&) = delete;

	constexpr hamon::size_t hash() const noexcept
	{
		return hamon::ranges::hash_combine(0, x, y);
	}

	friend constexpr bool operator==(S1 const& lhs, S1 const& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}
};

UNORDERED_SET_TEST_CONSTEXPR bool test2()
{
	using Set = hamon::unordered_set<S1, TransparentHash>;
	using Iterator = typename Set::iterator;
	using ConstIterator = typename Set::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<int>(), hamon::declval<int>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<int>(), hamon::declval<int>())), "");

	Set v;

	{
		auto r = v.emplace_hint(v.begin(), 10, 20);
		VERIFY(r->x == 10);
		VERIFY(r->y == 20);

		VERIFY(v.size() == 1);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	{
		auto r = v.emplace_hint(v.begin(), 10, 30);
		VERIFY(r->x == 10);
		VERIFY(r->y == 30);

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	{
		auto r = v.emplace_hint(v.end(), 40, 20);
		VERIFY(r->x == 40);
		VERIFY(r->y == 20);

		VERIFY(v.size() == 3);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	{
		auto r = v.emplace_hint(v.end(), 10, 20);
		VERIFY(r->x == 10);
		VERIFY(r->y == 20);

		VERIFY(v.size() == 3);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	{
		auto r = v.emplace_hint(v.end(), 10, 30);
		VERIFY(r->x == 10);
		VERIFY(r->y == 30);

		VERIFY(v.size() == 3);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, EmplaceHintTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE(test2());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::unordered_set<ThrowIfNegative, hamon::hash<ThrowIfNegative>> v;
		EXPECT_TRUE(v.empty());

		v.emplace_hint(v.begin(), 2);
		v.emplace_hint(v.begin(), 1);
		v.emplace_hint(v.begin(), 2);
		EXPECT_EQ(2u, v.size());

		EXPECT_THROW(v.emplace_hint(v.begin(), -1), ThrowIfNegative::Exception);
		EXPECT_EQ(2u, v.size());

		ThrowIfNegative x{0};
		x.value = -1;
		EXPECT_NO_THROW(v.emplace_hint(v.begin(), x));
		EXPECT_EQ(3u, v.size());

		EXPECT_THROW(v.emplace_hint(v.begin(), -1), ThrowIfNegative::Exception);
		EXPECT_EQ(3u, v.size());
	}
#endif
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace emplace_hint_test

}	// namespace hamon_unordered_set_test
