﻿/**
 *	@file	unit_test_serialization_xml.cpp
 *
 *	@brief	XMLシリアライズのテスト
 */

#include <hamon/serialization/xml_iarchive.hpp>
#include <hamon/serialization/xml_oarchive.hpp>
#include <hamon/serialization/array.hpp>
#include <hamon/serialization/string.hpp>
#include <hamon/serialization/vector.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "serialization_test_utility.hpp"

namespace hamon_serialization_test
{

namespace xml_test
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
	ar & hamon::serialization::make_nvp("y", o.y);
}

class Object
{
public:
	int         a{};
	float       b{};
	std::string c{};
	Point		d{};
	std::vector<int> e{};
	std::vector<std::vector<std::string>> f{};

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
		ar & hamon::serialization::make_nvp("b", b);
		ar & c;
		ar & hamon::serialization::make_nvp("d", d);
		ar & hamon::serialization::make_nvp("e", e);
		ar & hamon::serialization::make_nvp("f", f);
	}
};

template <typename Stream, typename OArchive, typename IArchive>
void XmlTest()
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
		std::string const f = "hello world";
		std::string const g = "A\"B\'C<DE>F&G";
		std::array<int, 5> const h = {1, 1, 2, 3, 5};
		float const i[2][3] =
		{
			{ 0.5f, -0.5f,  1.5f},
			{-1.5f,  2.5f, -2.5f},
		};

		OArchive oa(str);
		
		oa << a;
		oa << hamon::serialization::make_nvp("b", b);
		oa << c;
		oa << d;
		oa << hamon::serialization::make_nvp("e", e);
		oa << hamon::serialization::make_nvp("f", f);
		oa << g;
		oa << hamon::serialization::make_nvp("h", h);
		oa << hamon::serialization::make_nvp("i", i);
		oa << hamon::serialization::make_nvp("obj", obj);
	}

	std::string expected =
R"(<?xml version="1.0"?>
<serialization>
    <value0>3</value0>
    <b>1.5</b>
    <value1>true</value1>
    <value2>inf</value2>
    <e>false</e>
    <f>hello world</f>
    <value3>A&quot;B&apos;C&lt;DE&gt;F&amp;G</value3>
    <h>
        <value0>1</value0>
        <value1>1</value1>
        <value2>2</value2>
        <value3>3</value3>
        <value4>5</value4>
    </h>
    <i>
        <value0>
            <value0>0.5</value0>
            <value1>-0.5</value1>
            <value2>1.5</value2>
        </value0>
        <value1>
            <value0>-1.5</value0>
            <value1>2.5</value1>
            <value2>-2.5</value2>
        </value1>
    </i>
    <obj>
        <version>0</version>
        <value0>10</value0>
        <b>12.5</b>
        <value1>The quick brown fox</value1>
        <d>
            <version>0</version>
            <x>1</x>
            <y>2</y>
        </d>
        <e>
            <value0>3</value0>
            <value1>1</value1>
            <value2>4</value2>
            <value3>1</value3>
            <value4>5</value4>
        </e>
        <f>
            <value0>
                <value0>Foo</value0>
                <value1>Bar</value1>
            </value0>
            <value1>
                <value0>Fizz</value0>
                <value1>Buzz</value1>
                <value2>FizzBuzz</value2>
            </value1>
        </f>
    </obj>
</serialization>)";
	EXPECT_EQ(expected, str.str());

	{
		int a;
		float b;
		bool c;
		float d;
		bool e;
		std::string f;
		std::string g;
		std::array<int, 5> h;
		float i[2][3];
		Object j;

		IArchive ia(str);

		ia >> a;
		ia >> hamon::serialization::make_nvp("b", b);
		ia >> c;
		ia >> d;
		ia >> e;
		ia >> f;
		ia >> g;
		ia >> hamon::serialization::make_nvp("h", h);
		ia >> i;
		ia >> j;

		EXPECT_EQ(a, 3);
		EXPECT_EQ(b, 1.5f);
		EXPECT_EQ(c, true);
		EXPECT_EQ(d, std::numeric_limits<float>::infinity());
		EXPECT_EQ(e, false);
		EXPECT_EQ(f, "hello world");
		EXPECT_EQ(g, "A\"B\'C<DE>F&G");
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

using XmlTestTypes = ::testing::Types<
	std::tuple<std::stringstream, hamon::serialization::xml_oarchive, hamon::serialization::xml_iarchive>
>;

template <typename T>
class SerializationXmlTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationXmlTest, XmlTestTypes);

TYPED_TEST(SerializationXmlTest, XmlTest)
{
	using Stream   = typename std::tuple_element<0, TypeParam>::type;
	using OArchive = typename std::tuple_element<1, TypeParam>::type;
	using IArchive = typename std::tuple_element<2, TypeParam>::type;

	XmlTest<Stream, OArchive, IArchive>();
}

}	// namespace xml_test

}	// namespace hamon_serialization_test
