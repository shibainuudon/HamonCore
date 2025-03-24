/**
 *	@file	unit_test_unordered_set_insert_move.cpp
 *
 *	@brief	insert のテスト
 *
 *	constexpr pair<iterator, bool> insert(value_type&& obj);
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/pair/pair.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_set_test_helper.hpp"

namespace hamon_unordered_set_test
{

namespace insert_move_test
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
#if defined(HAMON_USE_STD_UNORDERED_SET)
	using Result = std::pair<Iterator, bool>;
#else
	using Result = hamon::pair<Iterator, bool>;
#endif

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().insert(hamon::declval<ValueType&&>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().insert(hamon::declval<ValueType&&>())), "");

	Set v;

	{
		ValueType x{10};
		auto r = v.insert(hamon::move(x));
		VERIFY(*r.first == 10);
		VERIFY(r.second);

		VERIFY(v.size() == 1);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	{
		ValueType x{10};
		auto r = v.insert(hamon::move(x));
		VERIFY(*r.first == 10);
		VERIFY(!r.second);

		VERIFY(v.size() == 1);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	{
		ValueType x{20};
		auto r = v.insert(hamon::move(x));
		VERIFY(*r.first == 20);
		VERIFY(r.second);

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

	S1(S1&&)                 = default;
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
	using ValueType = typename Set::value_type;
	using Iterator = typename Set::iterator;
#if defined(HAMON_USE_STD_UNORDERED_SET)
	using Result = std::pair<Iterator, bool>;
#else
	using Result = hamon::pair<Iterator, bool>;
#endif

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().insert(hamon::declval<ValueType&&>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().insert(hamon::declval<ValueType&&>())), "");

	Set v;

	{
		S1 x(10, 20);
		auto r = v.insert(hamon::move(x));
		VERIFY(r.first->x == 10);
		VERIFY(r.first->y == 20);
		VERIFY(r.second);

		VERIFY(v.size() == 1);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	{
		S1 x(10, 20);
		auto r = v.insert(hamon::move(x));
		VERIFY(r.first->x == 10);
		VERIFY(r.first->y == 20);
		VERIFY(!r.second);

		VERIFY(v.size() == 1);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	{
		S1 x(20, 10);
		auto r = v.insert(hamon::move(x));
		VERIFY(r.first->x == 20);
		VERIFY(r.first->y == 10);
		VERIFY(r.second);

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, InsertMoveTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE(test2());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		using Set = hamon::unordered_set<ThrowOnMove, hamon::hash<ThrowOnMove>>;

		Set v;

		{
			ThrowOnMove x{10};
			EXPECT_THROW(v.insert(hamon::move(x)), ThrowOnMove::Exception);
			EXPECT_EQ(0u, v.size());
		}
		{
			ThrowOnMove const x{10};
			v.insert(x);
			EXPECT_EQ(1u, v.size());
		}
#if 1//!defined(HAMON_USE_STD_UNORDERED_SET)	// 要素が挿入されないときに一時オブジェクトが作成されるかどうかは実装依存
		{
			ThrowOnMove x{10};
			EXPECT_NO_THROW(v.insert(hamon::move(x)));
			EXPECT_EQ(1u, v.size());
		}
#endif
	}
#endif
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace insert_move_test

}	// namespace hamon_unordered_set_test
