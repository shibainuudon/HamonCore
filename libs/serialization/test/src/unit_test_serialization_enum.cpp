/**
 *	@file	unit_test_serialization_enum.cpp
 *
 *	@brief	enum型のシリアライズのテスト
 */

#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <sstream>
#include "serialization_test_archives.hpp"
#include "get_random_value.hpp"

namespace hamon_serialization_test
{

namespace enum_test
{

enum Enum1
{
	Value1,
	Value2,
	Value3,
};

enum Enum2 : std::uint8_t
{
	Red   = 1 << 0,
	Green = 1 << 1,
	Blue  = 1 << 2,
	All   = Red | Green | Blue
};

enum class Enum3 : std::int64_t
{
	Value1,
	Value2,
	Value3,
};

template <typename Stream, typename OArchive, typename IArchive>
void EnumTest()
{
	Stream str;
	{
		Enum1 const e1 = Value1;
		Enum1 const e2 = Value3;
		Enum2 const e3 = Green;
		Enum2 const e4 = All;
		Enum3 const e5 = Enum3::Value1;
		Enum3 const e6 = Enum3::Value2;

		OArchive oa(str);
		
		oa << e1;
		oa << e2;
		oa << e3;
		oa << e4;
		oa << e5;
		oa << e6;
	}
	{
		Enum1 a;
		Enum1 b;
		Enum2 c;
		Enum2 d;
		Enum3 e;
		Enum3 f;

		IArchive ia(str);

		ia >> a;
		ia >> b;
		ia >> c;
		ia >> d;
		ia >> e;
		ia >> f;

		EXPECT_EQ(Value1, a);
		EXPECT_EQ(Value3, b);
		EXPECT_EQ(Green,  c);
		EXPECT_EQ(All,    d);
		EXPECT_EQ(Enum3::Value1, e);
		EXPECT_EQ(Enum3::Value2, f);
	}
}

using EnumTestTypes = ::testing::Types<
	std::tuple<std::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>
>;

template <typename T>
class SerializationEnumTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationEnumTest, EnumTestTypes);

TYPED_TEST(SerializationEnumTest, EnumTest)
{
	using Stream   = typename std::tuple_element<0, TypeParam>::type;
	using OArchive = typename std::tuple_element<1, TypeParam>::type;
	using IArchive = typename std::tuple_element<2, TypeParam>::type;

	EnumTest<Stream, OArchive, IArchive>();
}

}	// namespace enum_test

}	// namespace hamon_serialization_test
