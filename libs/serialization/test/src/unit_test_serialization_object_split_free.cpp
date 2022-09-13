/**
 *	@file	unit_test_serialization_object_split_free.cpp
 *
 *	@brief	フリー関数save/loadのテスト
 */

#include <hamon/serialization.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <sstream>
#include "serialization_test_utility.hpp"

namespace hamon_serialization_test
{

namespace object_split_free_test
{

class Object
{
public:
	int   a = get_random_value<int>();
	char  b = get_random_value<char>();
	float c[3] =
	{
		get_random_value<float>(),
		get_random_value<float>(),
		get_random_value<float>(),
	};

private:
	friend bool operator==(Object const& lhs, Object const& rhs)
	{
		return
			lhs.a == rhs.a &&
			lhs.b == rhs.b &&
			lhs.c[0] == rhs.c[0] &&
			lhs.c[1] == rhs.c[1] &&
			lhs.c[2] == rhs.c[2] &&
			true;
	}

	friend bool operator!=(Object const& lhs, Object const& rhs)
	{
		return !(lhs == rhs);
	}
};

template <typename Archive>
void save(Archive& ar, Object const& o)
{
	ar << o.a;
	ar << o.b;
	ar << o.c;
}

template <typename Archive>
void load(Archive& ar, Object& o)
{
	ar >> o.a;
	ar >> o.b;
	ar >> o.c;
}

template <typename Stream, typename OArchive, typename IArchive>
void ObjectSplitFreeTest()
{
	Object t;
	Stream str;
	{
		OArchive oa(str);
		oa << t;
	}
	{
		Object tmp;
		EXPECT_NE(t, tmp);

		IArchive ia(str);
		ia >> tmp;

		EXPECT_EQ(t, tmp);
	}
}

using ObjectSplitFreeTestTypes = ::testing::Types<
	std::tuple<std::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>
>;

template <typename T>
class SerializationObjectSplitFreeTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationObjectSplitFreeTest, ObjectSplitFreeTestTypes);

TYPED_TEST(SerializationObjectSplitFreeTest, ObjectSplitFreeTest)
{
	using Stream   = typename std::tuple_element<0, TypeParam>::type;
	using OArchive = typename std::tuple_element<1, TypeParam>::type;
	using IArchive = typename std::tuple_element<2, TypeParam>::type;

	ObjectSplitFreeTest<Stream, OArchive, IArchive>();
}

}	// namespace object_split_free_test

}	// namespace hamon_serialization_test
