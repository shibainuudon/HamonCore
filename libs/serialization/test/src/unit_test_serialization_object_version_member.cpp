/**
 *	@file	unit_test_serialization_object_version_member.cpp
 *
 *	@brief	メンバー関数serialize(バージョンあり)のテスト
 */

#include <hamon/serialization/access.hpp>
#include <hamon/serialization/version.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <sstream>
#include "serialization_test_archives.hpp"
#include "serialization_test_utility.hpp"

namespace hamon_serialization_test
{

namespace object_version_member_test
{

// get_class_version のオーバーロードなし
class Object1
{
private:
	int a = get_random_value<int>();

private:
	friend bool operator==(Object1 const& lhs, Object1 const& rhs)
	{
		return lhs.a == rhs.a;
	}

	friend bool operator!=(Object1 const& lhs, Object1 const& rhs)
	{
		return !(lhs == rhs);
	}

private:
	friend class hamon::serialization::access;

	template <typename Archive>
	void serialize(Archive& ar, hamon::serialization::version_t version)
	{
		EXPECT_EQ(0u, version);
		ar & a;
	}
};

// メンバ関数 get_class_version
class Object2
{
private:
	int a = get_random_value<int>();

private:
	friend bool operator==(Object2 const& lhs, Object2 const& rhs)
	{
		return lhs.a == rhs.a;
	}

	friend bool operator!=(Object2 const& lhs, Object2 const& rhs)
	{
		return !(lhs == rhs);
	}

private:
	friend class hamon::serialization::access;

	template <typename Archive>
	void serialize(Archive& ar, hamon::serialization::version_t version)
	{
		EXPECT_EQ(3u, version);
		ar & a;
	}

	constexpr hamon::serialization::version_t get_class_version() const
	{
		return 3;
	}
};

// フリー関数 get_class_version
class Object3
{
private:
	int a = get_random_value<int>();

private:
	friend bool operator==(Object3 const& lhs, Object3 const& rhs)
	{
		return lhs.a == rhs.a;
	}

	friend bool operator!=(Object3 const& lhs, Object3 const& rhs)
	{
		return !(lhs == rhs);
	}

private:
	friend class hamon::serialization::access;

	template <typename Archive>
	void serialize(Archive& ar, hamon::serialization::version_t version)
	{
		EXPECT_EQ(4u, version);
		ar & a;
	}

	friend constexpr hamon::serialization::version_t get_class_version(Object3 const&)
	{
		return 4;
	}
};

template <typename Stream, typename OArchive, typename IArchive>
void ObjectVersionMemberTest()
{
	Object1 t1;
	Object2 t2;
	Object3 t3;
	Stream str;
	{
		OArchive oa(str);
		oa << t1;
		oa << t2;
		oa << t3;
	}
	{
		Object1 tmp1;
		Object2 tmp2;
		Object3 tmp3;
		EXPECT_NE(t1, tmp1);
		EXPECT_NE(t2, tmp2);
		EXPECT_NE(t3, tmp3);

		IArchive ia(str);
		ia >> tmp1;
		ia >> tmp2;
		ia >> tmp3;

		EXPECT_EQ(t1, tmp1);
		EXPECT_EQ(t2, tmp2);
		EXPECT_EQ(t3, tmp3);
	}
}

using ObjectVersionMemberTestTypes = ::testing::Types<
	std::tuple<std::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>
>;

template <typename T>
class SerializationObjectVersionMemberTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationObjectVersionMemberTest, ObjectVersionMemberTestTypes);

TYPED_TEST(SerializationObjectVersionMemberTest, ObjectVersionMemberTest)
{
	using Stream   = typename std::tuple_element<0, TypeParam>::type;
	using OArchive = typename std::tuple_element<1, TypeParam>::type;
	using IArchive = typename std::tuple_element<2, TypeParam>::type;

	ObjectVersionMemberTest<Stream, OArchive, IArchive>();
}

}	// namespace object_version_member_test

}	// namespace hamon_serialization_test
