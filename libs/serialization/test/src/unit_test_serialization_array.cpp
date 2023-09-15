/**
 *	@file	unit_test_serialization_array.cpp
 *
 *	@brief	配列のシリアライズのテスト
 */

#include <hamon/serialization/types/string.hpp>
#include <hamon/string.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <sstream>
#include "serialization_test_archives.hpp"
#include "get_random_value.hpp"

namespace hamon_serialization_test
{

namespace array_test
{

enum class Enum
{
	Value1,
	Value2,
	Value3,
};

template <typename Stream, typename OArchive, typename IArchive>
void ArrayTest()
{
	Stream str;
	{
		int const a1[] = {1, 2, 3, 4, 5};
		float const a2[2][3] =
		{
			{ 11, 12, 13 },
			{ 21, 22, 23 },
		};
		Enum const a3[3] =
		{
			Enum::Value2,
			Enum::Value1,
			Enum::Value3,
		};
		hamon::string const a4[] =
		{
			"quick brown fox",
			"",
			"Hello World!",
		};

		OArchive oa(str);
		
		oa << a1;
		oa << a2;
		oa << a3;
		oa << a4;
	}
	{
		int a[5];
		float b[2][3];
		Enum c[3];
		hamon::string d[3];

		IArchive ia(str);

		ia >> a;
		ia >> b;
		ia >> c;
		ia >> d;

		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(4, a[3]);
		EXPECT_EQ(5, a[4]);
		EXPECT_EQ(11, b[0][0]);
		EXPECT_EQ(12, b[0][1]);
		EXPECT_EQ(13, b[0][2]);
		EXPECT_EQ(21, b[1][0]);
		EXPECT_EQ(22, b[1][1]);
		EXPECT_EQ(23, b[1][2]);
		EXPECT_EQ(Enum::Value2, c[0]);
		EXPECT_EQ(Enum::Value1, c[1]);
		EXPECT_EQ(Enum::Value3, c[2]);
		EXPECT_EQ("quick brown fox", d[0]);
		EXPECT_EQ("", d[1]);
		EXPECT_EQ("Hello World!", d[2]);
	}
}

using ArrayTestTypes = ::testing::Types<
	std::tuple<std::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>
>;

template <typename T>
class SerializationArrayTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationArrayTest, ArrayTestTypes);

TYPED_TEST(SerializationArrayTest, ArrayTest)
{
	using Stream   = typename std::tuple_element<0, TypeParam>::type;
	using OArchive = typename std::tuple_element<1, TypeParam>::type;
	using IArchive = typename std::tuple_element<2, TypeParam>::type;

	ArrayTest<Stream, OArchive, IArchive>();
}

}	// namespace array_test

}	// namespace hamon_serialization_test
