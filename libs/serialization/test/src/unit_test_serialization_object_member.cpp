/**
 *	@file	unit_test_serialization_object_member.cpp
 *
 *	@brief	メンバー関数serializeのテスト
 */

#include <hamon/serialization.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include "serialization_test_utility.hpp"

namespace hamon_serialization_test
{

namespace object_member_test
{

class Object
{
public:
	bool   a = get_random_value<bool>();
	double b = get_random_value<double>();
	int    c[2][3] =
	{
		{
			get_random_value<int>(),
			get_random_value<int>(),
			get_random_value<int>(),
		},
		{
			get_random_value<int>(),
			get_random_value<int>(),
			get_random_value<int>(),
		},
	};

private:
	friend bool operator==(Object const& lhs, Object const& rhs)
	{
		return
			lhs.a == rhs.a &&
			lhs.b == rhs.b &&
			lhs.c[0][0] == rhs.c[0][0] &&
			lhs.c[0][1] == rhs.c[0][1] &&
			lhs.c[0][2] == rhs.c[0][2] &&
			lhs.c[1][0] == rhs.c[1][0] &&
			lhs.c[1][1] == rhs.c[1][1] &&
			lhs.c[1][2] == rhs.c[1][2] &&
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
		ar & b;
		ar & c;
	}
};

template <typename Stream, typename OArchive, typename IArchive>
void ObjectMemberTest()
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

using ObjectMemberTestTypes = ::testing::Types<
	std::tuple<std::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>
>;

template <typename T>
class SerializationObjectMemberTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationObjectMemberTest, ObjectMemberTestTypes);

TYPED_TEST(SerializationObjectMemberTest, ObjectMemberTest)
{
	using Stream   = typename std::tuple_element<0, TypeParam>::type;
	using OArchive = typename std::tuple_element<1, TypeParam>::type;
	using IArchive = typename std::tuple_element<2, TypeParam>::type;

	ObjectMemberTest<Stream, OArchive, IArchive>();
}

}	// namespace object_member_test

}	// namespace hamon_serialization_test
