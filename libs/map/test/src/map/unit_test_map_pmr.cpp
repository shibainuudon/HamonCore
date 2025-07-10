/**
 *	@file	unit_test_map_pmr.cpp
 *
 *	@brief	pmr::map のテスト
 */

#include <hamon/map.hpp>
#include <hamon/memory_resource/monotonic_buffer_resource.hpp>
#include <gtest/gtest.h>
#include <string>
#include <sstream>

namespace hamon_map_test
{

namespace pmr_test
{

template <typename Key, typename T, typename C, typename A>
std::string ToString(const hamon::map<Key, T, C, A>& m)
{
	std::stringstream out;
	for (const auto& n : m)
	{
		out << "[" << n.first << "] = " << n.second << "; ";
	}
	return out.str();
}

GTEST_TEST(MapTest, PmrTest)
{
	// https://en.cppreference.com/w/cpp/container/map

	// Create a map of three (string, int) pairs
	hamon::pmr::monotonic_buffer_resource mr;
	hamon::pmr::map<std::string, int> m ({{"CPU", 10}, {"GPU", 15}, {"RAM", 20}}, &mr);

	EXPECT_EQ("[CPU] = 10; [GPU] = 15; [RAM] = 20; ", ToString(m));

	m["CPU"] = 25; // update an existing value
	m["SSD"] = 30; // insert a new value
	EXPECT_EQ("[CPU] = 25; [GPU] = 15; [RAM] = 20; [SSD] = 30; ", ToString(m));

	// Using operator[] with non-existent key always performs an insert
	EXPECT_EQ(0, m["UPS"]);
	EXPECT_EQ("[CPU] = 25; [GPU] = 15; [RAM] = 20; [SSD] = 30; [UPS] = 0; ", ToString(m));

	m.erase("GPU");
	EXPECT_EQ("[CPU] = 25; [RAM] = 20; [SSD] = 30; [UPS] = 0; ", ToString(m));

	using Pair = typename hamon::pmr::map<std::string, int>::value_type;
	hamon::erase_if(m, [](const Pair& pair){ return pair.second > 25; });
	EXPECT_EQ("[CPU] = 25; [RAM] = 20; [UPS] = 0; ", ToString(m));
	EXPECT_EQ(3u, m.size());

	m.clear();
	EXPECT_TRUE(m.empty());
}

}	// namespace pmr_test

}	// namespace hamon_map_test
