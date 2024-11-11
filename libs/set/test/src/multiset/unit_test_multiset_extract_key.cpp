/**
 *	@file	unit_test_multiset_extract_key.cpp
 *
 *	@brief	extract のテスト
 *
 *	node_type extract(const key_type& x);
 */

#include <hamon/set/multiset.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include <string>
#include <sstream>

#if !defined(HAMON_USE_STD_MULTISET) || \
	(defined(__cpp_lib_node_extract) && (__cpp_lib_node_extract >= 201606L))

namespace hamon_multiset_test
{

namespace extract_key_test
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
MULTISET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::multiset<Key>;
	using NodeType = typename Set::node_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().extract(hamon::declval<Key const&>())), NodeType>::value, "");
#if !defined(HAMON_USE_STD_MULTISET)
	static_assert(!noexcept(hamon::declval<Set&>().extract(hamon::declval<Key const&>())), "");
#endif

	Set v{ Key{3}, Key{1}, Key{4}, Key{1}, Key{5} };
	VERIFY(v.size() == 5);

	{
		auto r = v.extract(Key{3});
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.value() == Key{3});
		VERIFY(v.size() == 4);
		auto it = v.begin();
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 5);
		VERIFY(it == v.end());
	}
	{
		auto r = v.extract(Key{1});
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.value() == Key{1});
		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 5);
		VERIFY(it == v.end());
	}
	{
		auto r = v.extract(Key{2});
		VERIFY(bool(r) == false);
		VERIFY(r.empty() == true);
		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == 1);
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
};

int S::s_ctor_count = 0;
int S::s_dtor_count = 0;

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

GTEST_TEST(MultisetTest, ExtractKeyTest)
{
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));

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
		v.extract(k);
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(6, S::s_ctor_count);
		EXPECT_EQ(1, S::s_dtor_count);

		v.extract(S{3});
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(7, S::s_ctor_count);
		EXPECT_EQ(3, S::s_dtor_count);

		v.extract(k);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(7, S::s_ctor_count);
		EXPECT_EQ(3, S::s_dtor_count);

		v.extract(S{3});
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(8, S::s_ctor_count);
		EXPECT_EQ(5, S::s_dtor_count);
	}
	EXPECT_EQ(8, S::s_ctor_count);
	EXPECT_EQ(8, S::s_dtor_count);

	// https://en.cppreference.com/w/cpp/container/multiset/extract
	{
		hamon::multiset<int> cont {1, 2, 3};
		EXPECT_EQ("{1, 2, 3}", ToString(cont));

		// Extract node handle and change key
		auto nh = cont.extract(1);
		nh.value() = 4;

		EXPECT_EQ("{2, 3}", ToString(cont));

		// Insert node handle back
		cont.insert(hamon::move(nh));
		EXPECT_EQ("{2, 3, 4}", ToString(cont));
	}
}

#undef MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTISET_TEST_CONSTEXPR

}	// namespace extract_key_test

}	// namespace hamon_multiset_test

#endif
