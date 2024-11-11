/**
 *	@file	unit_test_multiset_clear.cpp
 *
 *	@brief	clear のテスト
 *
 *	void clear() noexcept;
 */

#include <hamon/set/multiset.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include <string>
#include <sstream>

namespace hamon_multiset_test
{

namespace clear_test
{

#if !defined(HAMON_USE_STD_MULTISET)
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR              /**/
#endif

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

	friend constexpr bool operator<(S const& lhs, S const& rhs)
	{
		return lhs.value < rhs.value;
	}
};

int S::s_ctor_count = 0;
int S::s_dtor_count = 0;

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
MULTISET_TEST_CONSTEXPR bool test()
{
	using Map = hamon::multiset<Key>;

	Map v;

	static_assert(hamon::is_same<decltype(v.clear()), void>::value, "");
	static_assert(noexcept(v.clear()), "");

	VERIFY(v.empty() == true);
	v.clear();
	VERIFY(v.empty() == true);
	v.emplace(Key{1});
	VERIFY(v.empty() == false);
	v.clear();
	VERIFY(v.empty() == true);

	return true;
}

#undef VERIFY

template <typename T, typename C>
std::string ToString(const hamon::multiset<T, C>& set)
{
	std::stringstream out;
	auto n = set.size();
	out << "{";
	for (auto const& elm : set)
	{
		out << elm << (--n ? ", " : "");
	}
	out << "}";
	return out.str();
}

GTEST_TEST(MultisetTest, ClearTest)
{
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));

	S::s_ctor_count = 0;
	S::s_dtor_count = 0;
	{
		hamon::multiset<S> v;
		EXPECT_EQ(0u, v.size());
		EXPECT_EQ(0, S::s_ctor_count);
		EXPECT_EQ(0, S::s_dtor_count);

		v.emplace(10);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(1, S::s_ctor_count);
		EXPECT_EQ(0, S::s_dtor_count);

		v.emplace(20);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(2, S::s_ctor_count);
		EXPECT_EQ(0, S::s_dtor_count);

		v.emplace(20);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(3, S::s_ctor_count);
		EXPECT_EQ(0, S::s_dtor_count);

		v.clear();
		EXPECT_EQ(0u, v.size());
		EXPECT_EQ(3, S::s_ctor_count);
		EXPECT_EQ(3, S::s_dtor_count);
	}
	EXPECT_EQ(3, S::s_ctor_count);
	EXPECT_EQ(3, S::s_dtor_count);

	// https://en.cppreference.com/w/cpp/container/multiset/clear
	{
		hamon::multiset<int> container {1, 2, 3};
		EXPECT_EQ("{1, 2, 3}", ToString(container));
		container.clear();
		EXPECT_EQ("{}", ToString(container));
	}
}

#undef MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTISET_TEST_CONSTEXPR

}	// namespace clear_test

}	// namespace hamon_multiset_test
