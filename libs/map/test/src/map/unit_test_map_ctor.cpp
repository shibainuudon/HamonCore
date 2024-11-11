/**
 *	@file	unit_test_map_ctor.cpp
 *
 *	@brief	コンストラクタのテスト
 */

#include <hamon/map/map.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include <string>
#include <sstream>

namespace hamon_map_test
{

namespace ctor_test
{

template <typename Key, typename T, typename C>
std::string ToString(const hamon::map<Key, T, C>& m)
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
		return lhs.x < rhs.x; // NB: y is intentionally ignored
	}
};

GTEST_TEST(MapTest, CtorTest)
{
	// https://en.cppreference.com/w/cpp/container/map/map

	// (1) Default constructor
	hamon::map<std::string, int> map1;
	map1["something"] = 69;
	map1["anything"] = 199;
	map1["that thing"] = 50;
	EXPECT_EQ("[anything] = 199, [something] = 69, [that thing] = 50, ", ToString(map1));

	// (4) Range constructor
	hamon::map<std::string, int> iter(map1.find("anything"), map1.end());
	EXPECT_EQ("[anything] = 199, [something] = 69, [that thing] = 50, ", ToString(iter));
	EXPECT_EQ("[anything] = 199, [something] = 69, [that thing] = 50, ", ToString(map1));

	// (6) Copy constructor
	hamon::map<std::string, int> copied(map1);
	EXPECT_EQ("[anything] = 199, [something] = 69, [that thing] = 50, ", ToString(copied));
	EXPECT_EQ("[anything] = 199, [something] = 69, [that thing] = 50, ", ToString(map1));

	// (8) Move constructor
	hamon::map<std::string, int> moved {hamon::move(map1)};
	EXPECT_EQ("[anything] = 199, [something] = 69, [that thing] = 50, ", ToString(moved));
	EXPECT_EQ("", ToString(map1));

	// (10) Initializer list constructor
	const hamon::map<std::string, int> init
	{
		{"this", 100},
		{"can", 100},
		{"be", 100},
		{"const", 100}
	};
	EXPECT_EQ("[be] = 100, [can] = 100, [const] = 100, [this] = 100, ", ToString(init));

	// Use a comparison struct
	hamon::map<Point, double, PointCmp> mag =
	{
		{{5, -12}, 13},
		{{3, 4}, 5},
		{{-8, -15}, 17}
	};
	EXPECT_EQ("[(-8, -15)] = 17, [(3, 4)] = 5, [(5, -12)] = 13, ", ToString(mag));

	// Use a comparison lambda
	// This lambda sorts points according to their magnitudes, where
	// these magnitudes are taken from the local variable mag.
	auto cmpLambda = [&mag](const Point& lhs, const Point& rhs)
	{
		return mag[lhs] < mag[rhs];
	};

	// You could also use a lambda that is not dependent on local variables, like this:
	// auto cmpLambda = [](const Point& lhs, const Point& rhs){ return lhs.y < rhs.y; };
	hamon::map<Point, double, decltype(cmpLambda)> magy(cmpLambda);

	// Various ways of inserting elements:
	magy.insert(std::pair<Point, double>({5, -12}, 13));
	magy.insert({{3, 4}, 5});
	magy.insert({Point {-8.0, -15.0}, 17});
	EXPECT_EQ("[(3, 4)] = 5, [(5, -12)] = 13, [(-8, -15)] = 17, ", ToString(magy));

	using PS = std::pair<const std::string, int>;
	const auto rg = {PS {"one", 1}, {"one", 101}, {"two", 2}, {"three", 3}};
#if !defined(HAMON_USE_STD_MAP) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))
	hamon::map<std::string, int> nums(hamon::from_range, rg); // overload (12)
#else
	hamon::map<std::string, int> nums(rg.begin(), rg.end()); // fallback to (4)
#endif
	EXPECT_EQ("[one] = 1, [three] = 3, [two] = 2, ", ToString(nums));
}

}	// namespace ctor_test

}	// namespace hamon_map_test
