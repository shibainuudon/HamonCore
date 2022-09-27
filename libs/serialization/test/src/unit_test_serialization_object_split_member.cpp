/**
 *	@file	unit_test_serialization_object_split_member.cpp
 *
 *	@brief	メンバー関数save/loadのテスト
 */

#include <hamon/serialization/access.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <sstream>
#include "serialization_test_archives.hpp"
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

public:
	static int s_save_invoke_count;
	static int s_load_invoke_count;

private:
	friend class hamon::serialization::access;

	template <typename Archive>
	void save(Archive& ar) const
	{
		++s_save_invoke_count;
		ar << a;
		ar << b;
		ar << c;
	}

	template <typename Archive>
	void load(Archive& ar)
	{
		++s_load_invoke_count;
		ar >> a;
		ar >> b;
		ar >> c;
	}
};

int Object::s_save_invoke_count = 0;
int Object::s_load_invoke_count = 0;

template <typename Stream, typename OArchive, typename IArchive>
void ObjectSplitMemberTest()
{
	Object::s_save_invoke_count = 0;
	Object::s_load_invoke_count = 0;

	Object t;
	Stream str;
	{
		OArchive oa(str);
		oa << t;
	}

	EXPECT_EQ(1, Object::s_save_invoke_count);
	EXPECT_EQ(0, Object::s_load_invoke_count);

	{
		Object tmp;
		EXPECT_NE(t, tmp);

		IArchive ia(str);
		ia >> tmp;

		EXPECT_EQ(t, tmp);
	}

	EXPECT_EQ(1, Object::s_save_invoke_count);
	EXPECT_EQ(1, Object::s_load_invoke_count);
}

using ObjectSplitMemberTestTypes = ::testing::Types<
	std::tuple<std::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>
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
