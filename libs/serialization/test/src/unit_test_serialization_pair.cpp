/**
 *	@file	unit_test_serialization_pair.cpp
 *
 *	@brief	hamon::pair のシリアライズのテスト
 */

#include <hamon/serialization/types/pair.hpp>
#include <hamon/serialization/types/string.hpp>
#include <hamon/serialization/types/vector.hpp>
#include <hamon/sstream/stringstream.hpp>
#include <hamon/sstream/wstringstream.hpp>
#include <hamon/pair.hpp>
#include <hamon/string.hpp>
#include <hamon/tuple.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "serialization_test_archives.hpp"
#include "get_random_value.hpp"

#if !defined(HAMON_NO_STD)
#include <utility>
#endif

namespace hamon_serialization_test
{

namespace pair_test
{

struct Object
{
	int n;
	float f;
	hamon::vector<int> v;
	
	template <typename Archive>
	void serialize(Archive& ar)
	{
		ar & HAMON_SERIALIZATION_NVP(n);
		ar & HAMON_SERIALIZATION_NVP(f);
		ar & HAMON_SERIALIZATION_NVP(v);
	}
};

template <typename Stream, typename OArchive, typename IArchive,
	template <typename, typename> class Pair
>
void PairTest()
{
	Stream str;
	{
		Pair<int, float> const p1{2, 3.5f};
		Pair<hamon::string, Object> const p2
		{
			"Hello World!",
			{ 10, -2.5f, {1, 2, 3} },
		};
		hamon::vector<Pair<float, int>> const p3
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
	hamon::string expected =
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
		Pair<int, float> a;
		Pair<hamon::string, Object> b;
		hamon::vector<Pair<float, int>> c;

		IArchive ia(str);

		ia >> a;
		ia >> b;
		ia >> c;

		EXPECT_EQ(2, a.first);
		EXPECT_EQ(3.5f, a.second);

		EXPECT_EQ("Hello World!", b.first);
		EXPECT_EQ(10, b.second.n);
		EXPECT_EQ(-2.5f, b.second.f);
		EXPECT_EQ((hamon::vector<int>{1, 2, 3}), b.second.v);

		EXPECT_EQ(0.5f, c[0].first);
		EXPECT_EQ(1,    c[0].second);
		EXPECT_EQ(1.5f, c[1].first);
		EXPECT_EQ(2,    c[1].second);
		EXPECT_EQ(2.5f, c[2].first);
		EXPECT_EQ(3,    c[2].second);
	}
}

using PairTestTypes = ::testing::Types<
	hamon::tuple<hamon::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	hamon::tuple<hamon::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	hamon::tuple<hamon::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	hamon::tuple<hamon::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	hamon::tuple<hamon::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	hamon::tuple<hamon::stringstream,  hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>,
	hamon::tuple<hamon::wstringstream, hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>
>;

template <typename T>
class SerializationPairTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationPairTest, PairTestTypes);

TYPED_TEST(SerializationPairTest, PairTest)
{
	using Stream   = typename hamon::tuple_element<0, TypeParam>::type;
	using OArchive = typename hamon::tuple_element<1, TypeParam>::type;
	using IArchive = typename hamon::tuple_element<2, TypeParam>::type;

	PairTest<Stream, OArchive, IArchive, hamon::pair>();
#if !defined(HAMON_NO_STD)
	PairTest<Stream, OArchive, IArchive, std::pair>();
#endif
}

}	// namespace pair_test

}	// namespace hamon_serialization_test
