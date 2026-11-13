/**
 *	@file	unit_test_serialization_std_array.cpp
 *
 *	@brief	hamon::arrayのシリアライズのテスト
 */

#include <hamon/serialization/types/array.hpp>
#include <hamon/serialization/types/string.hpp>
#include <hamon/array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/sstream/stringstream.hpp>
#include <hamon/sstream/wstringstream.hpp>
#include <hamon/string.hpp>
#include <hamon/tuple.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "serialization_test_archives.hpp"
#include "get_random_value.hpp"

#if !defined(HAMON_NO_STD)
#include <array>
#endif

namespace hamon_serialization_test
{

namespace std_array_test
{

enum class Enum
{
	Value1,
	Value2,
	Value3,
};

template <typename Stream, typename OArchive, typename IArchive,
	template <typename, hamon::size_t> class Array
>
void StdArrayTest()
{
	Stream str;
	{
		Array<int, 5> const a1 = {1, 2, 3, 4, 5};
		Array<Array<int, 3>, 2> const a2 =
		{{
			{ 11, 12, 13 },
			{ 21, 22, 23 },
		}};
		Array<Enum, 3> const a3 =
		{
			Enum::Value2,
			Enum::Value1,
			Enum::Value3,
		};
		Array<hamon::string, 3> const a4 =
		{
			"quick brown fox",
			",",
			"Hello World!",
		};

		OArchive oa(str);
		
		oa << a1;
		oa << a2;
		oa << a3;
		oa << a4;
	}
	{
		Array<int, 5> a;
		Array<Array<int, 3>, 2> b;
		Array<Enum, 3> c;
		Array<hamon::string, 3> d;

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
		EXPECT_EQ(",", d[1]);
		EXPECT_EQ("Hello World!", d[2]);
	}
}

using StdArrayTestTypes = ::testing::Types<
	hamon::tuple<hamon::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	hamon::tuple<hamon::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	hamon::tuple<hamon::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	hamon::tuple<hamon::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	hamon::tuple<hamon::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	hamon::tuple<hamon::stringstream,  hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>,
	hamon::tuple<hamon::wstringstream, hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>
>;

template <typename T>
class SerializationStdArrayTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationStdArrayTest, StdArrayTestTypes);

TYPED_TEST(SerializationStdArrayTest, StdArrayTest)
{
	using Stream   = typename hamon::tuple_element<0, TypeParam>::type;
	using OArchive = typename hamon::tuple_element<1, TypeParam>::type;
	using IArchive = typename hamon::tuple_element<2, TypeParam>::type;

	StdArrayTest<Stream, OArchive, IArchive, hamon::array>();
#if !defined(HAMON_NO_STD)
	StdArrayTest<Stream, OArchive, IArchive, std::array>();
#endif
}

}	// namespace std_array_test

}	// namespace hamon_serialization_test
