/**
 *	@file	unit_test_unordered_map_pmr.cpp
 *
 *	@brief	pmr::unordered_map のテスト
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/memory_resource/monotonic_buffer_resource.hpp>
#include <hamon/string.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace hamon_unordered_map_test
{

namespace pmr_test
{

GTEST_TEST(UnorderedMapTest, PmrTest)
{
	// https://en.cppreference.com/w/cpp/container/unordered_map

	// Create an unordered_map of three strings (that map to strings)
	hamon::pmr::monotonic_buffer_resource mr;
	hamon::pmr::unordered_map<hamon::string, hamon::string> u(
		{
			{"RED", "#FF0000"},
			{"GREEN", "#00FF00"},
			{"BLUE", "#0000FF"}
		}, &mr);

	std::stringstream ss;

	// Helper lambda function to print key-value pairs
	auto print_key_value = [&](const hamon::string& key, const hamon::string& value)
	{
		ss << "Key:[" << key << "] Value:[" << value << "]\n";
	};

	//std::cout << "Iterate and print key-value pairs of unordered_map, being\n"
	//	"explicit with their types:\n";
	for (auto& n : u)
	{
		print_key_value(n.first, n.second);
	}

#if defined(HAMON_HAS_CXX17_STRUCTURED_BINDINGS)
	//std::cout << "\nIterate and print key-value pairs using C++17 structured binding:\n";
	for (const auto& [key, value] : u)
	{
		print_key_value(key, value);
	}
#endif

	// Add two new entries to the unordered_map
	u["BLACK"] = "#000000";
	u["WHITE"] = "#FFFFFF";

	//std::cout << "\nOutput values by key:\n"
	//	"The HEX of color RED is:[" << u["RED"] << "]\n"
	//	"The HEX of color BLACK is:[" << u["BLACK"] << "]\n\n";

	//std::cout << "Use operator[] with non-existent key to insert a new key-value pair:\n";
	print_key_value("new_key", u["new_key"]);

	//std::cout << "\nIterate and print key-value pairs, using `auto`;\n"
	//	"new_key is now one of the keys in the map:\n";
	for (const auto& n : u)
	{
		print_key_value(n.first, n.second);
	}
}

}	// namespace pmr_test

}	// namespace hamon_unordered_map_test
