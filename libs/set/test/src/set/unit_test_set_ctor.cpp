/**
 *	@file	unit_test_set_ctor.cpp
 *
 *	@brief	コンストラクタのテスト
 */

#include <hamon/set/set.hpp>
#include <hamon/cmath/hypot.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include <string>
#include <sstream>

namespace hamon_set_test
{

namespace ctor_test
{

template <typename T, typename C>
std::string ToString(const hamon::set<T, C>& set)
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

// https://en.cppreference.com/w/cpp/container/set/set

struct Point { double x, y; };
 
struct PointCmp
{
    bool operator()(const Point& lhs, const Point& rhs) const
    {
        return hamon::hypot(lhs.x, lhs.y) < hamon::hypot(rhs.x, rhs.y);
    }
};

std::ostream& operator<<(std::ostream& os, Point pt)
{
    return os << '(' << pt.x << ',' << pt.x << ')';
}

GTEST_TEST(SetTest, CtorTest)
{
	// (1) Default constructor
	hamon::set<std::string> a;
	EXPECT_EQ("{}", ToString(a));

	a.insert("horse");
	a.insert("cat");
	a.insert("dog");
	EXPECT_EQ("{cat, dog, horse}", ToString(a));

	// (4) Range constructor
	hamon::set<std::string> b(a.find("dog"), a.end());
	EXPECT_EQ("{dog, horse}", ToString(b));

	// (6) Copy constructor
	hamon::set<std::string> c(a);
	c.insert("another horse");
	EXPECT_EQ("{another horse, cat, dog, horse}", ToString(c));

	// (8) Move constructor
	hamon::set<std::string> d(hamon::move(a));
	EXPECT_EQ("{cat, dog, horse}", ToString(d));
	EXPECT_EQ("{}", ToString(a));

	// (10) Initializer list constructor
	hamon::set<std::string> e {"one", "two", "three", "five", "eight"};
	EXPECT_EQ("{eight, five, one, three, two}", ToString(e));

	// Custom comparison
	hamon::set<Point, PointCmp> f = {{2, 5}, {3, 4}, {1, 1}};
	f.insert({1, -1}); // This fails because the magnitude of (1,-1) equals (1,1)
	EXPECT_EQ("{(1,1), (3,3), (2,2)}", ToString(f));

	// (12) Range constructor
	const auto w = {"Eurybia", "Theia", "Rhea", "Aura", "Mnemosyne", "Mnemosyne"};
#if !defined(HAMON_USE_STD_SET) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))
	hamon::set<std::string> g(hamon::from_range, w); // overload (12)
#else
	hamon::set<std::string> g(w.begin(), w.end()); // fallback to (4)
#endif
	EXPECT_EQ("{Aura, Eurybia, Mnemosyne, Rhea, Theia}", ToString(g));
}

}	// namespace ctor_test

}	// namespace hamon_set_test
