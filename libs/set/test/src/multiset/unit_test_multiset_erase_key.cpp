/**
 *	@file	unit_test_multiset_erase_key.cpp
 *
 *	@brief	erase のテスト
 *
 *	size_type erase(const key_type& x);
 */

#include <hamon/set/multiset.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multiset_test
{

namespace erase_key_test
{

#if !defined(HAMON_USE_STD_MULTISET)
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
MULTISET_TEST_CONSTEXPR bool test1()
{
	using Set = hamon::multiset<Key>;
	using SizeType = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().erase(hamon::declval<Key const&>())), SizeType>::value, "");
#if !defined(HAMON_USE_STD_MULTISET)
	static_assert(!noexcept(hamon::declval<Set&>().erase(hamon::declval<Key const&>())), "");
#endif

	Set v{Key{3}, Key{1}, Key{4}, Key{1}, Key{5} };
	VERIFY(v.size() == 5);

	{
		auto r = v.erase(Key{3});
		VERIFY(r == 1);
		VERIFY(v.size() == 4);
		auto it = v.begin();
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 5);
		VERIFY(it == v.end());
	}
	{
		auto r = v.erase(Key{1});
		VERIFY(r == 2);
		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 5);
		VERIFY(it == v.end());
	}
	{
		auto r = v.erase(Key{2});
		VERIFY(r == 0);
		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 5);
		VERIFY(it == v.end());
	}

	return true;
}

template <typename Key>
MULTISET_TEST_CONSTEXPR bool test2()
{
	using Set = hamon::multiset<Key>;

	Set v{
		Key{1},
		Key{2}, Key{2},
		Key{3}, Key{3}, Key{3},
		Key{4}, Key{4}, Key{4}, Key{4},
		Key{5}, Key{5}, Key{5}, Key{5}, Key{5},
	};
	VERIFY(v.size() == 15);

	{
		auto r = v.erase(Key{1});
		VERIFY(r == 1);
		VERIFY(v.size() == 14);
	}
	{
		auto r = v.erase(Key{2});
		VERIFY(r == 2);
		VERIFY(v.size() == 12);
	}
	{
		auto r = v.erase(Key{3});
		VERIFY(r == 3);
		VERIFY(v.size() == 9);
	}
	{
		auto r = v.erase(Key{4});
		VERIFY(r == 4);
		VERIFY(v.size() == 5);
	}
	{
		auto r = v.erase(Key{5});
		VERIFY(r == 5);
		VERIFY(v.size() == 0);
	}

	return true;
}

#undef VERIFY

struct S
{
	static int s_ctor_count;
	static int s_dtor_count;

	int value;

	S(int v) : value(v)
	{
		++s_ctor_count;
	}

	~S()
	{
		++s_dtor_count;
	}

	S(S&&)                 = delete;
	S(S const&)            = delete;
	S& operator=(S&&)      = delete;
	S& operator=(S const&) = delete;

	friend bool operator<(S const& lhs, S const& rhs)
	{
		return lhs.value < rhs.value;
	}
};

int S::s_ctor_count = 0;
int S::s_dtor_count = 0;

GTEST_TEST(MultisetTest, EraseKeyTest)
{
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test2<int>()));
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test2<char>()));
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test2<float>()));

	S::s_ctor_count = 0;
	S::s_dtor_count = 0;
	{
		hamon::multiset<S> v;
		v.emplace(1);
		v.emplace(2);
		v.emplace(3);
		v.emplace(3);
		v.emplace(5);
		EXPECT_EQ(5, S::s_ctor_count);
		EXPECT_EQ(0, S::s_dtor_count);

		S const k{2};
		v.erase(k);
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(6, S::s_ctor_count);
		EXPECT_EQ(1, S::s_dtor_count);

		v.erase(S{3});
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(7, S::s_ctor_count);
		EXPECT_EQ(4, S::s_dtor_count);

		v.erase(k);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(7, S::s_ctor_count);
		EXPECT_EQ(4, S::s_dtor_count);

		v.erase(S{3});
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(8, S::s_ctor_count);
		EXPECT_EQ(5, S::s_dtor_count);
	}
	EXPECT_EQ(8, S::s_ctor_count);
	EXPECT_EQ(8, S::s_dtor_count);
}

#undef MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTISET_TEST_CONSTEXPR

}	// namespace erase_key_test

}	// namespace hamon_multiset_test
