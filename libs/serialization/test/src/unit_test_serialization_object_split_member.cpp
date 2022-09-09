/**
 *	@file	unit_test_serialization_object_split_member.cpp
 *
 *	@brief	メンバー関数save/loadのテスト
 */

#include <hamon/serialization.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include "serialization_test_utility.hpp"

namespace hamon_serialization_test
{

namespace object_split_member_test
{

class Object
{
private:
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

private:
	friend class hamon::serialization::access;

	template <typename Archive>
	void save(Archive& ar) const
	{
		ar << a;
		ar << b;
		ar << c;
	}

	template <typename Archive>
	void load(Archive& ar)
	{
		ar >> a;
		ar >> b;
		ar >> c;
	}
};

template <typename Stream, typename OArchive, typename IArchive>
void ObjectSplitMemberTest()
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

using ObjectSplitMemberTestTypes = ::testing::Types<
	std::tuple<std::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>
>;

template <typename T>
class SerializationObjectSplitMemberTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationObjectSplitMemberTest, ObjectSplitMemberTestTypes);

TYPED_TEST(SerializationObjectSplitMemberTest, ObjectSplitMemberTest)
{
	using Stream   = typename std::tuple_element<0, TypeParam>::type;
	using OArchive = typename std::tuple_element<1, TypeParam>::type;
	using IArchive = typename std::tuple_element<2, TypeParam>::type;

	ObjectSplitMemberTest<Stream, OArchive, IArchive>();
}

}	// namespace object_split_member_test

}	// namespace hamon_serialization_test
