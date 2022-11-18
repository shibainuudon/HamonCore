/**
 *	@file	unit_test_serialization_unique_ptr.cpp
 *
 *	@brief	std::unique_ptr のシリアライズのテスト
 */

#include <hamon/serialization/unique_ptr.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <sstream>
#include <memory>
#include "serialization_test_archives.hpp"
#include "get_random_value.hpp"

namespace hamon_serialization_test
{

namespace unique_ptr_test
{

class Object
{
private:
	float a = get_random_value<float>();

private:
	friend bool operator==(Object const& lhs, Object const& rhs)
	{
		return lhs.a == rhs.a;
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
	}
};

template <typename Stream, typename OArchive, typename IArchive>
void UniquePtrTest()
{
	std::unique_ptr<int> p1;
	std::unique_ptr<int> p2(new int(42));
	std::unique_ptr<Object> p3(new Object());

	Stream str;
	{

		OArchive oa(str);
		
		oa << p1;
		oa << p2;
		oa << p3;
	}
	{
		std::unique_ptr<int> a;
		std::unique_ptr<int> b;
		std::unique_ptr<Object> c;

		IArchive ia(str);

		ia >> a;
		ia >> b;
		ia >> c;

		EXPECT_EQ(p1, a);
		EXPECT_EQ(nullptr, a);

		EXPECT_NE(p2, b);
		EXPECT_EQ(*p2, *b);

		EXPECT_NE(p3, c);
		EXPECT_EQ(*p3, *c);
	}
}

using UniquePtrTestTypes = ::testing::Types<
	std::tuple<std::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>
>;

template <typename T>
class SerializationUniquePtrTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationUniquePtrTest, UniquePtrTestTypes);

TYPED_TEST(SerializationUniquePtrTest, UniquePtrTest)
{
	using Stream   = typename std::tuple_element<0, TypeParam>::type;
	using OArchive = typename std::tuple_element<1, TypeParam>::type;
	using IArchive = typename std::tuple_element<2, TypeParam>::type;

	UniquePtrTest<Stream, OArchive, IArchive>();
}

}	// namespace unique_ptr_test

}	// namespace hamon_serialization_test
