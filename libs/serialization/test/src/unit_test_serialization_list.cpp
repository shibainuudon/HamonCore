/**
 *	@file	unit_test_serialization_list.cpp
 *
 *	@brief	hamon::listのシリアライズのテスト
 */

#include <hamon/serialization/types/list.hpp>
#include <hamon/serialization/types/vector.hpp>
#include <hamon/serialization/types/string.hpp>
#include <hamon/list.hpp>
#include <hamon/string.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <sstream>
#include "serialization_test_archives.hpp"
#include "get_random_value.hpp"

namespace hamon_serialization_test
{

namespace list_test
{

struct Point
{
	int x;
	int y;

	friend bool operator==(Point const& lhs, Point const& rhs)
	{
		return
			lhs.x == rhs.x &&
			lhs.y == rhs.y &&
			true;
	}

	friend bool operator!=(Point const& lhs, Point const& rhs)
	{
		return !(lhs == rhs);
	}

	template <typename Archive>
	void serialize(Archive& ar)
	{
		ar & HAMON_SERIALIZATION_NVP(x);
		ar & HAMON_SERIALIZATION_NVP(y);
	}
};

template <typename Stream, typename OArchive, typename IArchive>
void ListTest()
{
	hamon::list<int> const v1;
	hamon::list<int> const v2{ 1, 2, 3 };
	hamon::list<hamon::string> const v3 { "The", "quick brown", "fox" };
	hamon::list<hamon::vector<float>> const v4
	{
		{ 10, 11, 12, 13 },
		{ 20, 21, 22 },
	};
	hamon::list<Point> const v5
	{
		{ 1, 2 },
		{ 3, 4 },
		{ 5, 6 },
	};

	Stream str;
	{
		OArchive oa(str);

		oa << v1;
		oa << v2;
		oa << v3;
		oa << v4;
		oa << v5;
	}

#if 0
	hamon::string expected =
R"({
    "value0": [

    ],
    "value1": [
        1,
        2,
        3
    ],
    "value2": [
        "The",
        "quick brown",
        "fox"
    ],
    "value3": [
        [
            10,
            11,
            12,
            13
        ],
        [
            20,
            21,
            22
        ]
    ],
    "value4": [
        {
            "version": 0,
            "x": 1,
            "y": 2
        },
        {
            "version": 0,
            "x": 3,
            "y": 4
        },
        {
            "version": 0,
            "x": 5,
            "y": 6
        }
    ]
})";
	EXPECT_EQ(expected, str.str());
#endif

	{
		hamon::list<int> a{ 10, 11, 12 };
		hamon::list<int> b{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
		hamon::list<hamon::string> c;
		hamon::list<hamon::vector<float>> d;
		hamon::list<Point> e;

		IArchive ia(str);

		ia >> a;
		ia >> b;
		ia >> c;
		ia >> d;
		ia >> e;

		EXPECT_EQ(v1, a);
		EXPECT_EQ(v2, b);
		EXPECT_EQ(v3, c);
		EXPECT_EQ(v4, d);
		EXPECT_EQ(v5, e);
	}
}

using ListTestTypes = ::testing::Types<
	std::tuple<std::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>
>;

template <typename T>
class SerializationListTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationListTest, ListTestTypes);

TYPED_TEST(SerializationListTest, ListTest)
{
	using Stream   = typename std::tuple_element<0, TypeParam>::type;
	using OArchive = typename std::tuple_element<1, TypeParam>::type;
	using IArchive = typename std::tuple_element<2, TypeParam>::type;

	ListTest<Stream, OArchive, IArchive>();
}

}	// namespace list_test

}	// namespace hamon_serialization_test
