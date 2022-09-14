/**
 *	@file	unit_test_serialization_vector.cpp
 *
 *	@brief	std::vectorのシリアライズのテスト
 */

#include <hamon/serialization.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <sstream>
#include <string>
#include <vector>
#include "serialization_test_utility.hpp"

namespace hamon_serialization_test
{

namespace vector_test
{

template <typename Stream, typename OArchive, typename IArchive>
void VectorTest()
{
	Stream str;
	{
		std::vector<int>   const v1;
		std::vector<int>   const v2{1, 2, 3};
		std::vector<float> const v3;
		std::vector<float> const v4{0.5f, -0.5f, 1.5f, -2.5f};
		std::vector<std::vector<std::string>> const v5
		{
			{ "A1", "A2" },
			{ "B1", "B2", "B3" },
			{ },
			{ "C1", "C2", "C3" },
		};
		
		OArchive oa(str);

		oa << v1;
		oa << v2;
		oa << v3;
		oa << v4;
		oa << v5;
	}
	{
		std::vector<int> a;
		std::vector<int> b;
		std::vector<float> c;
		std::vector<float> d;
		std::vector<std::vector<std::string>> e;

		IArchive ia(str);

		ia >> a;
		ia >> b;
		ia >> c;
		ia >> d;
		ia >> e;

		EXPECT_EQ(0u, a.size());
		EXPECT_EQ(3u, b.size());
		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(2, b[1]);
		EXPECT_EQ(3, b[2]);
		EXPECT_EQ(0u, c.size());
		EXPECT_EQ(4u, d.size());
		EXPECT_EQ( 0.5f, d[0]);
		EXPECT_EQ(-0.5f, d[1]);
		EXPECT_EQ( 1.5f, d[2]);
		EXPECT_EQ(-2.5f, d[3]);

		EXPECT_EQ(4u, e.size());
		EXPECT_EQ(2u, e[0].size());
		EXPECT_EQ(3u, e[1].size());
		EXPECT_EQ(0u, e[2].size());
		EXPECT_EQ(3u, e[3].size());
		EXPECT_EQ("A1", e[0][0]);
		EXPECT_EQ("A2", e[0][1]);
		EXPECT_EQ("B1", e[1][0]);
		EXPECT_EQ("B2", e[1][1]);
		EXPECT_EQ("B3", e[1][2]);
		EXPECT_EQ("C1", e[3][0]);
		EXPECT_EQ("C2", e[3][1]);
		EXPECT_EQ("C3", e[3][2]);
	}
}

using VectorTestTypes = ::testing::Types<
	std::tuple<std::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>
>;

template <typename T>
class SerializationVectorTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationVectorTest, VectorTestTypes);

TYPED_TEST(SerializationVectorTest, VectorTest)
{
	using Stream   = typename std::tuple_element<0, TypeParam>::type;
	using OArchive = typename std::tuple_element<1, TypeParam>::type;
	using IArchive = typename std::tuple_element<2, TypeParam>::type;

	VectorTest<Stream, OArchive, IArchive>();
}

}	// namespace vector_test

}	// namespace hamon_serialization_test
