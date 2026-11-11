/**
 *	@file	unit_test_serialization_empty.cpp
 *
 *	@brief	空のクラスのシリアライズのテスト
 */

#include <hamon/config.hpp>
#include <hamon/sstream/stringstream.hpp>
#include <hamon/sstream/wstringstream.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "serialization_test_archives.hpp"

namespace hamon_serialization_test
{

namespace empty_test
{

static int s_serialize_invoke_count = 0;

// 空のクラスは何もしなくてもシリアライズできる
struct Empty1{};

// serialize関数を定義しているとそれが呼ばれる
struct Empty2
{
private:
	friend class hamon::serialization::access;

	template <typename Archive>
	void serialize(Archive&)
	{
		++s_serialize_invoke_count;
	}
};

template <typename Stream, typename OArchive, typename IArchive>
void EmptyTest()
{
	s_serialize_invoke_count = 0;
	Stream str;
	{
		Empty1 e1;
		Empty2 e2;

		OArchive oa(str);
		
		EXPECT_EQ(0, s_serialize_invoke_count);
		oa << e1;
		EXPECT_EQ(0, s_serialize_invoke_count);
		oa << e2;
		EXPECT_EQ(1, s_serialize_invoke_count);
	}
	s_serialize_invoke_count = 0;
	{
		Empty1 e1;
		Empty2 e2;

		IArchive ia(str);

		EXPECT_EQ(0, s_serialize_invoke_count);
		ia >> e1;
		EXPECT_EQ(0, s_serialize_invoke_count);
		ia >> e2;
		EXPECT_EQ(1, s_serialize_invoke_count);
	}
}

using EmptyTestTypes = ::testing::Types<
	hamon::tuple<hamon::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	hamon::tuple<hamon::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	hamon::tuple<hamon::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	hamon::tuple<hamon::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	hamon::tuple<hamon::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	hamon::tuple<hamon::stringstream,  hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>,
	hamon::tuple<hamon::wstringstream, hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>
>;

template <typename T>
class SerializationEmptyTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationEmptyTest, EmptyTestTypes);

TYPED_TEST(SerializationEmptyTest, EmptyTest)
{
	using Stream   = typename hamon::tuple_element<0, TypeParam>::type;
	using OArchive = typename hamon::tuple_element<1, TypeParam>::type;
	using IArchive = typename hamon::tuple_element<2, TypeParam>::type;

	EmptyTest<Stream, OArchive, IArchive>();
}

}	// namespace empty_test

}	// namespace hamon_serialization_test
