/**
 *	@file	unit_test_serialization_json.cpp
 *
 *	@brief	JSONシリアライズのテスト
 */

#include <hamon/serialization/archives/json_iarchive.hpp>
#include <hamon/serialization/archives/json_oarchive.hpp>
#include <hamon/serialization/types/string.hpp>
#include <hamon/serialization/types/vector.hpp>
#include <hamon/serialization/types/array.hpp>
#include <hamon/serialization/nvp.hpp>
#include <hamon/serialization/access.hpp>
#include <hamon/string.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <sstream>
#include <limits>
#include <array>
#include <vector>
#include "get_random_value.hpp"

namespace hamon_serialization_test
{

namespace json_test
{

struct Point
{
	float x;
	float y;
};

inline bool operator==(Point const& lhs, Point const& rhs)
{
	return
		lhs.x == rhs.x &&
		lhs.y == rhs.y;
}

inline bool operator!=(Point const& lhs, Point const& rhs)
{
	return !(lhs == rhs);
}

template <typename Archive>
inline void serialize(Archive& ar, Point& o)
{
	ar & hamon::serialization::make_nvp("x", o.x);
	ar & o.y;
}

class Object
{
public:
	int           a{};
	float         b{};
	hamon::string c{};
	Point		  d{};
	std::vector<int> e{};
	std::vector<std::vector<hamon::string>> f{};

private:
	friend bool operator==(Object const& lhs, Object const& rhs)
	{
		return
			lhs.a == rhs.a &&
			lhs.b == rhs.b &&
			lhs.c == rhs.c &&
			lhs.d == rhs.d &&
			lhs.e == rhs.e &&
			lhs.f == rhs.f &&
			true;
	}

	friend bool operator!=(Object const& lhs, Object const& rhs)
	{
		return !(lhs == rhs);
	}

private:
	friend class hamon::serialization::access;

	template <typename Archive>
	void serialize(Archive& ar)
	{
		ar & a;
		ar & HAMON_SERIALIZATION_NVP(b);
		ar & c;
		ar & HAMON_SERIALIZATION_NVP(d);
		ar & HAMON_SERIALIZATION_NVP(e);
		ar & HAMON_SERIALIZATION_NVP(f);
	}
};

template <typename Stream, typename OArchive, typename IArchive>
void JsonTest()
{
	Object obj;
	obj.a = 10;
	obj.b = 12.5f;
	obj.c = "The quick brown fox";
	obj.d = { 1, 2 };
	obj.e = { 3, 1, 4, 1, 5 };
	obj.f =
	{
		{ "Foo", "Bar", },
		{ "Fizz", "Buzz", "FizzBuzz", },
	};

	Stream str;
	{
		int const a = 3;
		float const b = 1.5f;
		bool const c = true;
		float const d = std::numeric_limits<float>::infinity();
		bool const e = false;
		hamon::string const f = "hello world";
		hamon::string const g = "A\"B\\C/D\bE\fF\nG\rH\tI";
		std::array<int, 5> const h = {1, 1, 2, 3, 5};
		float const i[2][3] =
		{
			{ 0.5f, -0.5f,  1.5f},
			{-1.5f,  2.5f, -2.5f},
		};

		OArchive oa(str);
		
		oa << a;
		oa << HAMON_SERIALIZATION_NVP(b);
		oa << c;
		oa << d;
		oa << HAMON_SERIALIZATION_NVP(e);
		oa << HAMON_SERIALIZATION_NVP(f);
		oa << g;
		oa << HAMON_SERIALIZATION_NVP(h);
		oa << HAMON_SERIALIZATION_NVP(i);
		oa << HAMON_SERIALIZATION_NVP(obj);
	}
	hamon::string expected =
R"({
    "value0": 3,
    "b": 1.5,
    "value1": true,
    "value2": inf,
    "e": false,
    "f": "hello world",
    "value3": "A\"B\\C\/D\bE\fF\nG\rH\tI",
    "h": [
        1,
        1,
        2,
        3,
        5
    ],
    "i": [
        [
            0.5,
            -0.5,
            1.5
        ],
        [
            -1.5,
            2.5,
            -2.5
        ]
    ],
    "obj": {
        "version": 0,
        "value0": 10,
        "b": 12.5,
        "value1": "The quick brown fox",
        "d": {
            "version": 0,
            "x": 1,
            "value0": 2
        },
        "e": [
            3,
            1,
            4,
            1,
            5
        ],
        "f": [
            [
                "Foo",
                "Bar"
            ],
            [
                "Fizz",
                "Buzz",
                "FizzBuzz"
            ]
        ]
    }
})";
	EXPECT_EQ(expected, str.str());
	{
		int a;
		float b;
		bool c;
		float d;
		bool e;
		hamon::string f;
		hamon::string g;
		std::array<int, 5> h;
		float i[2][3];
		Object j;

		IArchive ia(str);

		ia >> a;
		ia >> b;
		ia >> c;
		ia >> d;
		ia >> e;
		ia >> f;
		ia >> g;
		ia >> h;
		ia >> i;
		ia >> j;

		EXPECT_EQ(a, 3);
		EXPECT_EQ(b, 1.5f);
		EXPECT_EQ(c, true);
		EXPECT_EQ(d, std::numeric_limits<float>::infinity());
		EXPECT_EQ(e, false);
		EXPECT_EQ(f, "hello world");
		EXPECT_EQ(g, "A\"B\\C/D\bE\fF\nG\rH\tI");
		EXPECT_EQ(h[0], 1);
		EXPECT_EQ(h[1], 1);
		EXPECT_EQ(h[2], 2);
		EXPECT_EQ(h[3], 3);
		EXPECT_EQ(h[4], 5);
		EXPECT_EQ(i[0][0],  0.5f);
		EXPECT_EQ(i[0][1], -0.5f);
		EXPECT_EQ(i[0][2],  1.5f);
		EXPECT_EQ(i[1][0], -1.5f);
		EXPECT_EQ(i[1][1],  2.5f);
		EXPECT_EQ(i[1][2], -2.5f);
		EXPECT_EQ(j, obj);
	}
}

using JsonTestTypes = ::testing::Types<
	std::tuple<std::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>
>;

template <typename T>
class SerializationJsonTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationJsonTest, JsonTestTypes);

TYPED_TEST(SerializationJsonTest, JsonTest)
{
	using Stream   = typename std::tuple_element<0, TypeParam>::type;
	using OArchive = typename std::tuple_element<1, TypeParam>::type;
	using IArchive = typename std::tuple_element<2, TypeParam>::type;

	JsonTest<Stream, OArchive, IArchive>();
}

}	// namespace json_test

}	// namespace hamon_serialization_test
