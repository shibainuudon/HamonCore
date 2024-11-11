/**
 *	@file	unit_test_multiset_ctor.cpp
 *
 *	@brief	コンストラクタのテスト
 */

#include <hamon/set/multiset.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include <string>
#include <sstream>

namespace hamon_multiset_test
{

namespace ctor_test
{

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

GTEST_TEST(MultisetTest, CtorTest)
{
	// https://en.cppreference.com/w/cpp/container/multiset/multiset

	// (1) Default constructor
	hamon::multiset<int> a;
	EXPECT_EQ("{}", ToString(a));

	a.insert(4);
	a.insert(3);
	a.insert(2);
	a.insert(1);
	EXPECT_EQ("{1, 2, 3, 4}", ToString(a));

	// (4) Range constructor
	hamon::multiset<int> b(a.begin(), a.find(3));
	EXPECT_EQ("{1, 2}", ToString(b));

	// (6) Copy constructor
	hamon::multiset<int> c(a);
	EXPECT_EQ("{1, 2, 3, 4}", ToString(c));

	// (8) Move constructor
	hamon::multiset<int> d(hamon::move(a));
	EXPECT_EQ("{1, 2, 3, 4}", ToString(d));

	// (10) Initializer list constructor
	hamon::multiset<int> e {3, 2, 1, 2, 4, 7, 3};
	EXPECT_EQ("{1, 2, 2, 3, 3, 4, 7}", ToString(e));

	// (12) Range constructor
	const auto w = {"a", "b", "c", "d", "d", "c", "b", "a"};
#if !defined(HAMON_USE_STD_MULTISET) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))
	hamon::multiset<std::string> f(hamon::from_range, w); // overload (12)
#else
	hamon::multiset<std::string> f(w.begin(), w.end()); // fallback to (4)
#endif
	EXPECT_EQ("{a, a, b, b, c, c, d, d}", ToString(f));
}

}	// namespace ctor_test

}	// namespace hamon_multiset_test
