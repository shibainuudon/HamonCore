/**
 *	@file	unit_test_serialization_pair.cpp
 *
 *	@brief	std::pair のシリアライズのテスト
 */

#include <hamon/serialization/pair.hpp>
#include <hamon/serialization/string.hpp>
#include <hamon/serialization/vector.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "serialization_test_archives.hpp"
#include "serialization_test_utility.hpp"

namespace hamon_serialization_test
{

namespace pair_test
{

struct Object
{
	int n;
	float f;
	std::vector<int> v;
	
	template <typename Archive>
	void serialize(Archive& ar)
	{
		ar & HAMON_SERIALIZATION_NVP(n);
		ar & HAMON_SERIALIZATION_NVP(f);
		ar & HAMON_SERIALIZATION_NVP(v);
	}
};

template <typename Stream, typename OArchive, typename IArchive>
void PairTest()
{
	Stream str;
	{
		std::pair<int, float> const p1{2, 3.5f};
		std::pair<std::string, Object> const p2
		{
			"Hello World!",
			{ 10, -2.5f, {1, 2, 3} },
		};
		std::vector<std::pair<float, int>> const p3
		{
			{0.5f, 1},
			{1.5f, 2},
			{2.5f, 3},
		};

		OArchive oa(str);
		
		oa << p1;
		oa << p2;
		oa << p3;
	}

#if 0
	std::string expected =
R"({
    "value0": {
        "first": 2,
        "second": 3.5
    },
    "value1": {
        "first": "Hello World!",
        "second": {
            "version": 0,
            "n": 10,
            "f": -2.5,
            "v": [
                1,
                2,
                3
            ]
        }
    },
    "value2": [
        {
            "first": 0.5,
            "second": 1
        },
        {
            "first": 1.5,
            "second": 2
        },
        {
            "first": 2.5,
            "second": 3
        }
    ]
})";
	EXPECT_EQ(expected, str.str());
#endif

	{
		std::pair<int, float> a;
		std::pair<std::string, Object> b;
		std::vector<std::pair<float, int>> c;

		IArchive ia(str);

		ia >> a;
		ia >> b;
		ia >> c;

		EXPECT_EQ(2, a.first);
		EXPECT_EQ(3.5f, a.second);

		EXPECT_EQ("Hello World!", b.first);
		EXPECT_EQ(10, b.second.n);
		EXPECT_EQ(-2.5f, b.second.f);
		EXPECT_EQ((std::vector<int>{1, 2, 3}), b.second.v);

		EXPECT_EQ(0.5f, c[0].first);
		EXPECT_EQ(1,    c[0].second);
		EXPECT_EQ(1.5f, c[1].first);
		EXPECT_EQ(2,    c[1].second);
		EXPECT_EQ(2.5f, c[2].first);
		EXPECT_EQ(3,    c[2].second);
	}
}

using PairTestTypes = ::testing::Types<
	std::tuple<std::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>
>;

template <typename T>
class SerializationPairTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationPairTest, PairTestTypes);

TYPED_TEST(SerializationPairTest, PairTest)
{
	using Stream   = typename std::tuple_element<0, TypeParam>::type;
	using OArchive = typename std::tuple_element<1, TypeParam>::type;
	using IArchive = typename std::tuple_element<2, TypeParam>::type;

	PairTest<Stream, OArchive, IArchive>();
}

}	// namespace pair_test

}	// namespace hamon_serialization_test
