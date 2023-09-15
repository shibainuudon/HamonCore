/**
 *	@file	unit_test_serialization_object_free.cpp
 *
 *	@brief	フリー関数serializeのテスト
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

namespace object_free_test
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
	hamon::string d;

private:
	friend bool operator==(Object const& lhs, Object const& rhs)
	{
		return
			lhs.a == rhs.a &&
			lhs.b == rhs.b &&
			lhs.c[0] == rhs.c[0] &&
			lhs.c[1] == rhs.c[1] &&
			lhs.c[2] == rhs.c[2] &&
			lhs.d == rhs.d &&
			true;
	}

	friend bool operator!=(Object const& lhs, Object const& rhs)
	{
		return !(lhs == rhs);
	}
};

template <typename Archive>
void serialize(Archive& ar, Object& o)
{
	ar & o.a;
	ar & o.b;
	ar & o.c;
	ar & o.d;
}

template <typename Stream, typename OArchive, typename IArchive>
void ObjectFreeTest()
{
	Object t;
	t.d = "The quick brown fox jumps over the lazy dog";

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

using ObjectFreeTestTypes = ::testing::Types<
	std::tuple<std::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>
>;

template <typename T>
class SerializationObjectFreeTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationObjectFreeTest, ObjectFreeTestTypes);

TYPED_TEST(SerializationObjectFreeTest, ObjectFreeTest)
{
	using Stream   = typename std::tuple_element<0, TypeParam>::type;
	using OArchive = typename std::tuple_element<1, TypeParam>::type;
	using IArchive = typename std::tuple_element<2, TypeParam>::type;

	ObjectFreeTest<Stream, OArchive, IArchive>();
}

}	// namespace object_free_test

}	// namespace hamon_serialization_test
