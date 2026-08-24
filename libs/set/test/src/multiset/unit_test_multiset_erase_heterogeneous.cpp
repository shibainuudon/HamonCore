/**
 *	@file	unit_test_multiset_erase_heterogeneous.cpp
 *
 *	@brief	erase のテスト
 *
 *	template<class K> size_type erase(K&& x);
 */

#include <hamon/set/multiset.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multiset_test
{

namespace erase_heterogeneous_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::multiset<Key, hamon::less<>>;
	using SizeType = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().erase(hamon::declval<int>())), SizeType>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().erase(hamon::declval<int>())), "");

	Set v{Key{3}, Key{1}, Key{4}, Key{1}, Key{5} };
	VERIFY(v.size() == 5);

	{
		auto r = v.erase(3);
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
		auto r = v.erase(1);
		VERIFY(r == 2);
		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 5);
		VERIFY(it == v.end());
	}
	{
		auto r = v.erase(2);
		VERIFY(r == 0);
		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 5);
		VERIFY(it == v.end());
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

	friend bool operator<(S const& lhs, int rhs)
	{
		return lhs.value < rhs;
	}

	friend bool operator<(int lhs, S const& rhs)
	{
		return lhs < rhs.value;
	}
};

int S::s_ctor_count = 0;
int S::s_dtor_count = 0;

GTEST_TEST(MultisetTest, EraseHeterogeneousTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));

	S::s_ctor_count = 0;
	S::s_dtor_count = 0;
	{
		hamon::multiset<S, hamon::less<>> v;
		v.emplace(1);
		v.emplace(2);
		v.emplace(3);
		v.emplace(3);
		v.emplace(5);
		EXPECT_EQ(5, S::s_ctor_count);
		EXPECT_EQ(0, S::s_dtor_count);

		v.erase(2);
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(5, S::s_ctor_count);
		EXPECT_EQ(1, S::s_dtor_count);

		v.erase(3);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(5, S::s_ctor_count);
		EXPECT_EQ(3, S::s_dtor_count);

		v.erase(4);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(5, S::s_ctor_count);
		EXPECT_EQ(3, S::s_dtor_count);

		v.erase(3);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(5, S::s_ctor_count);
		EXPECT_EQ(3, S::s_dtor_count);
	}
	EXPECT_EQ(5, S::s_ctor_count);
	EXPECT_EQ(5, S::s_dtor_count);
}

}	// namespace erase_heterogeneous_test

}	// namespace hamon_multiset_test
