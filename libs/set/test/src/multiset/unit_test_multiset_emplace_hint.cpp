/**
 *	@file	unit_test_multiset_emplace_hint.cpp
 *
 *	@brief	emplace_hint のテスト
 *
 *	template<class... Args> iterator emplace_hint(const_iterator position, Args&&... args);
 */

#include <hamon/set/multiset.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multiset_test
{

namespace emplace_hint_test
{

#if !defined(HAMON_USE_STD_MULTISET)
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR              /**/
#endif

struct S1
{
	int x;
	int y;

	constexpr S1(int i) : x(i), y(0) {}
	constexpr S1(int i, int j) : x(i), y(j) {}

	S1(S1&&)                 = delete;
	S1(S1 const&)            = delete;
	S1& operator=(S1&&)      = delete;
	S1& operator=(S1 const&) = delete;

	friend constexpr bool operator<(S1 const& lhs, S1 const& rhs)
	{
		return lhs.x < rhs.x;
	}
};

struct S2
{
	static int s_ctor_count;
	static int s_dtor_count;

	int value;

	S2(int v) : value(v)
	{
		++s_ctor_count;
	}

	~S2()
	{
		++s_dtor_count;
	}

	S2(S2&&)                 = delete;
	S2(S2 const&)            = delete;
	S2& operator=(S2&&)      = delete;
	S2& operator=(S2 const&) = delete;

	friend bool operator<(S2 const& lhs, S2 const& rhs)
	{
		return lhs.value < rhs.value;
	}
};

int S2::s_ctor_count = 0;
int S2::s_dtor_count = 0;

#if !defined(HAMON_NO_EXCEPTIONS)
struct MayThrow
{
	struct Exception{};

	int value;

	MayThrow(int v) : value(v)
	{
		if (v < 0)
		{
			throw Exception{};
		}
	}

	friend bool operator<(MayThrow const& lhs, MayThrow const& rhs)
	{
		return lhs.value < rhs.value;
	}
};
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
MULTISET_TEST_CONSTEXPR bool test1()
{
	using Set = hamon::multiset<Key>;
	using Iterator = typename Set::iterator;
	using ConstIterator = typename Set::const_iterator;

	Set v;

	static_assert(hamon::is_same<decltype(v.emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<Key>())), Iterator>::value, "");
	static_assert(!noexcept(v.emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<Key>())), "");

	{
		auto r = v.emplace_hint(v.end(), Key{10});
		VERIFY(r == hamon::next(v.begin(), 0));

		VERIFY(v.size() == 1);
		auto it = v.begin();
		VERIFY(*it++ == 10);
		VERIFY(it == v.end());
	}
	{
		auto r = v.emplace_hint(v.begin(), Key{10});
		VERIFY(r == hamon::next(v.begin(), 0));

		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == 10);
		VERIFY(*it++ == 10);
		VERIFY(it == v.end());
	}
	{
		auto r = v.emplace_hint(v.end(), Key{20});
		VERIFY(r == hamon::next(v.begin(), 2));

		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == 10);
		VERIFY(*it++ == 10);
		VERIFY(*it++ == 20);
		VERIFY(it == v.end());
	}
	{
		auto r = v.emplace_hint(hamon::next(v.begin(), 2), Key{20});
		VERIFY(r == hamon::next(v.begin(), 2));

		VERIFY(v.size() == 4);
		auto it = v.begin();
		VERIFY(*it++ == 10);
		VERIFY(*it++ == 10);
		VERIFY(*it++ == 20);
		VERIFY(*it++ == 20);
		VERIFY(it == v.end());
	}
	{
		auto r = v.emplace_hint(hamon::next(v.begin(), 2), Key{15});
		VERIFY(r == hamon::next(v.begin(), 2));

		VERIFY(v.size() == 5);
		auto it = v.begin();
		VERIFY(*it++ == 10);
		VERIFY(*it++ == 10);
		VERIFY(*it++ == 15);
		VERIFY(*it++ == 20);
		VERIFY(*it++ == 20);
		VERIFY(it == v.end());
	}

	return true;
}

MULTISET_TEST_CONSTEXPR bool test2()
{
	hamon::multiset<S1> v;

	{
		auto r = v.emplace_hint(v.end(), 1, 10);
		VERIFY(r == hamon::next(v.begin(), 0));

		VERIFY(v.size() == 1);
		auto it = v.begin();
		VERIFY(it->x == 1);
		VERIFY(it->y == 10);
		++it;
		VERIFY(it == v.end());
	}
	{
		auto r = v.emplace_hint(v.end(), 1, 20);
		VERIFY(r == hamon::next(v.begin(), 1));

		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(it->x == 1);
		VERIFY(it->y == 10);
		++it;
		VERIFY(it->x == 1);
		VERIFY(it->y == 20);
		++it;
		VERIFY(it == v.end());
	}
	{
		auto r = v.emplace_hint(v.begin(), 1, 30);
		VERIFY(r == hamon::next(v.begin(), 0));

		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(it->x == 1);
		VERIFY(it->y == 30);
		++it;
		VERIFY(it->x == 1);
		VERIFY(it->y == 10);
		++it;
		VERIFY(it->x == 1);
		VERIFY(it->y == 20);
		++it;
		VERIFY(it == v.end());
	}
	{
		auto r = v.emplace_hint(hamon::next(v.begin(), 2), 1, 40);
		VERIFY(r == hamon::next(v.begin(), 2));

		VERIFY(v.size() == 4);
		auto it = v.begin();
		VERIFY(it->x == 1);
		VERIFY(it->y == 30);
		++it;
		VERIFY(it->x == 1);
		VERIFY(it->y == 10);
		++it;
		VERIFY(it->x == 1);
		VERIFY(it->y == 40);
		++it;
		VERIFY(it->x == 1);
		VERIFY(it->y == 20);
		++it;
		VERIFY(it == v.end());
	}
	{
		auto r = v.emplace_hint(hamon::next(v.begin(), 3), 3, 50);
		VERIFY(r == hamon::next(v.begin(), 4));

		VERIFY(v.size() == 5);
		auto it = v.begin();
		VERIFY(it->x == 1);
		VERIFY(it->y == 30);
		++it;
		VERIFY(it->x == 1);
		VERIFY(it->y == 10);
		++it;
		VERIFY(it->x == 1);
		VERIFY(it->y == 40);
		++it;
		VERIFY(it->x == 1);
		VERIFY(it->y == 20);
		++it;
		VERIFY(it->x == 3);
		VERIFY(it->y == 50);
		++it;
		VERIFY(it == v.end());
	}
	{
		auto r = v.emplace_hint(hamon::next(v.begin(), 4), 3, 60);
		VERIFY(r == hamon::next(v.begin(), 4));

		VERIFY(v.size() == 6);
		auto it = v.begin();
		VERIFY(it->x == 1);
		VERIFY(it->y == 30);
		++it;
		VERIFY(it->x == 1);
		VERIFY(it->y == 10);
		++it;
		VERIFY(it->x == 1);
		VERIFY(it->y == 40);
		++it;
		VERIFY(it->x == 1);
		VERIFY(it->y == 20);
		++it;
		VERIFY(it->x == 3);
		VERIFY(it->y == 60);
		++it;
		VERIFY(it->x == 3);
		VERIFY(it->y == 50);
		++it;
		VERIFY(it == v.end());
	}
	{
		auto r = v.emplace_hint(hamon::next(v.begin(), 5), 3, 70);
		VERIFY(r == hamon::next(v.begin(), 5));

		VERIFY(v.size() == 7);
		auto it = v.begin();
		VERIFY(it->x == 1);
		VERIFY(it->y == 30);
		++it;
		VERIFY(it->x == 1);
		VERIFY(it->y == 10);
		++it;
		VERIFY(it->x == 1);
		VERIFY(it->y == 40);
		++it;
		VERIFY(it->x == 1);
		VERIFY(it->y == 20);
		++it;
		VERIFY(it->x == 3);
		VERIFY(it->y == 60);
		++it;
		VERIFY(it->x == 3);
		VERIFY(it->y == 70);
		++it;
		VERIFY(it->x == 3);
		VERIFY(it->y == 50);
		++it;
		VERIFY(it == v.end());
	}
	{
		auto r = v.emplace_hint(hamon::next(v.begin(), 3), 2, 80);
		VERIFY(r == hamon::next(v.begin(), 4));

		VERIFY(v.size() == 8);
		auto it = v.begin();
		VERIFY(it->x == 1);
		VERIFY(it->y == 30);
		++it;
		VERIFY(it->x == 1);
		VERIFY(it->y == 10);
		++it;
		VERIFY(it->x == 1);
		VERIFY(it->y == 40);
		++it;
		VERIFY(it->x == 1);
		VERIFY(it->y == 20);
		++it;
		VERIFY(it->x == 2);
		VERIFY(it->y == 80);
		++it;
		VERIFY(it->x == 3);
		VERIFY(it->y == 60);
		++it;
		VERIFY(it->x == 3);
		VERIFY(it->y == 70);
		++it;
		VERIFY(it->x == 3);
		VERIFY(it->y == 50);
		++it;
		VERIFY(it == v.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MultisetTest, EmplaceHintTest)
{
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test2());

	S2::s_ctor_count = 0;
	S2::s_dtor_count = 0;
	{
		hamon::multiset<S2> v;
		EXPECT_EQ(0u, v.size());
		EXPECT_EQ(0, S2::s_ctor_count);
		EXPECT_EQ(0, S2::s_dtor_count);

		v.emplace_hint(v.begin(), 10);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(1, S2::s_ctor_count);
		EXPECT_EQ(0, S2::s_dtor_count);

		v.emplace_hint(v.end(), 10);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(2, S2::s_ctor_count);
		EXPECT_EQ(0, S2::s_dtor_count);

		v.emplace_hint(v.begin(), 20);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(3, S2::s_ctor_count);
		EXPECT_EQ(0, S2::s_dtor_count);

		v.emplace_hint(v.end(), 20);
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(4, S2::s_ctor_count);
		EXPECT_EQ(0, S2::s_dtor_count);
	}
	EXPECT_EQ(4, S2::s_ctor_count);
	EXPECT_EQ(4, S2::s_dtor_count);

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::multiset<MayThrow> v;
		EXPECT_TRUE(v.empty());

		v.emplace_hint(v.end(), 2);
		EXPECT_EQ(1u, v.size());

		v.emplace_hint(v.end(), 1);
		EXPECT_EQ(2u, v.size());

		EXPECT_THROW(v.emplace_hint(v.end(), -1), MayThrow::Exception);
		EXPECT_EQ(2u, v.size());
		{
			auto it = v.begin();
			EXPECT_EQ(1, (it++)->value);
			EXPECT_EQ(2, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		MayThrow x{0};
		x.value = -1;
		v.emplace_hint(v.end(), x);
		EXPECT_EQ(3u, v.size());
		{
			auto it = v.begin();
			EXPECT_EQ(-1, (it++)->value);
			EXPECT_EQ(1, (it++)->value);
			EXPECT_EQ(2, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		EXPECT_THROW(v.emplace_hint(v.end(), -1), MayThrow::Exception);
		EXPECT_EQ(3u, v.size());
	}
#endif
}

#undef MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTISET_TEST_CONSTEXPR

}	// namespace emplace_hint_test

}	// namespace hamon_multiset_test
