/**
 *	@file	unit_test_multimap_ctor.cpp
 *
 *	@brief	コンストラクタのテスト
 */

#include <hamon/map/multimap.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <gtest/gtest.h>
#include <string>
#include <sstream>

namespace hamon_multimap_test
{

namespace ctor_test
{

template <typename Key, typename T, typename C>
std::string ToString(const hamon::multimap<Key, T, C>& m)
{
	std::stringstream out;
	for (const auto& n : m)
	{
		out << "[" << n.first << "] = " << n.second << ", ";
	}
	return out.str();
}

struct Point
{
	double x, y;

	friend std::ostream& operator<<(std::ostream& os, Point pt)
	{
		return os << '(' << pt.x << ", " << pt.y << ')';
	}
};

struct PointCmp
{
	bool operator()(const Point& lhs, const Point& rhs) const
	{
		return lhs.x < rhs.x; // NB. ignores y on purpose
	}
};

GTEST_TEST(MultimapTest, CtorTest)
{
	// https://en.cppreference.com/w/cpp/container/multimap/multimap

	hamon::multimap<int, int> m1 =
	{
		{1, 1}, {2, 2}, {3, 3}, {4, 4}, {4, 4}, {3, 3}, {2, 2}, {1, 1}
	};
	EXPECT_EQ("[1] = 1, [1] = 1, [2] = 2, [2] = 2, [3] = 3, [3] = 3, [4] = 4, [4] = 4, ", ToString(m1));

	// Custom comparison
	hamon::multimap<Point, double, PointCmp> mag
	{
		{{5, 12}, 13},
		{{3, 4}, 5},
		{{8, 15}, 17},
		{{3, -3}, -1}
	};
	EXPECT_EQ("[(3, 4)] = 5, [(3, -3)] = -1, [(5, 12)] = 13, [(8, 15)] = 17, ", ToString(mag));

	// Construction from a range
	using PS = std::pair<int, std::string>;
	const auto rg = {PS {3, "Earth"}, {2, "Venus"}, {1, "Mercury"}, {3, "Moon"}};
#if !defined(HAMON_USE_STD_MULTIMAP) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))
	hamon::multimap<int, std::string> m2(hamon::from_range, rg); // overload (12)
#else
	hamon::multimap<int, std::string> m2(rg.begin(), rg.end()); // fallback to (4)
#endif
	EXPECT_EQ("[1] = Mercury, [2] = Venus, [3] = Earth, [3] = Moon, ", ToString(m2));
}

}	// namespace ctor_test

}	// namespace hamon_multimap_test
