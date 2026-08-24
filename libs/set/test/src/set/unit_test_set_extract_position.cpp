/**
 *	@file	unit_test_set_extract_position.cpp
 *
 *	@brief	extract のテスト
 *
 *	node_type extract(const_iterator position);
 */

#include <hamon/set/set.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_set_test
{

namespace extract_position_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::set<Key>;
	using NodeType = typename Set::node_type;
	using ConstIterator = typename Set::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().extract(hamon::declval<ConstIterator>())), NodeType>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().extract(hamon::declval<ConstIterator>())), "");

	Set v{Key{3}, Key{1}, Key{4}, Key{1}, Key{5} };
	VERIFY(v.size() == 4);

	{
		auto r = v.extract(v.begin());
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.value() == Key{1});
		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == 3);
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 5);
		VERIFY(it == v.end());
	}
	{
		auto r = v.extract(hamon::next(v.cbegin(), 1));
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.value() == Key{4});
		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == 3);
		VERIFY(*it++ == 5);
		VERIFY(it == v.end());
	}
	{
		auto r = v.extract(hamon::next(v.begin(), 1));
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.value() == Key{5});
		VERIFY(v.size() == 1);
		auto it = v.begin();
		VERIFY(*it++ == 3);
		VERIFY(it == v.end());
	}
	{
		auto r = v.extract(v.cbegin());
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.value() == Key{3});
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

GTEST_TEST(SetTest, ExtractPositionTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));

	S::s_ctor_count = 0;
	S::s_dtor_count = 0;
	{
		hamon::set<S> v;
		v.emplace(1);
		v.emplace(2);
		v.emplace(3);
		v.emplace(4);
		v.emplace(5);
		EXPECT_EQ(5, S::s_ctor_count);
		EXPECT_EQ(0, S::s_dtor_count);

		v.extract(v.begin());
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(5, S::s_ctor_count);
		EXPECT_EQ(1, S::s_dtor_count);

		v.extract(hamon::next(v.begin(), 1));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(5, S::s_ctor_count);
		EXPECT_EQ(2, S::s_dtor_count);
	}
	EXPECT_EQ(5, S::s_ctor_count);
	EXPECT_EQ(5, S::s_dtor_count);
}

}	// namespace extract_position_test

}	// namespace hamon_set_test
