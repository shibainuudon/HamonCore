/**
 *	@file	unit_test_serialization_unique_ptr_polymorphic_version.cpp
 *
 *	@brief	std::unique_ptr のシリアライズ(バージョンあり)のテスト
 */

#include <hamon/serialization/unique_ptr.hpp>
#include <hamon/serialization/base_object.hpp>
#include <hamon/serialization/class_id.hpp>
#include <hamon/serialization/register_polymorphic_class.hpp>
#include <hamon/serialization/version.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <sstream>
#include <memory>
#include "serialization_test_archives.hpp"
#include "get_random_value.hpp"

namespace hamon_serialization_test
{

namespace unique_ptr_polymorphic_version_test
{

class Base
{
public:
	Base() { ++Base::instance_count; }
	virtual ~Base() { --Base::instance_count; }

	virtual float GetValue() const { return a; }

private:
	float a = get_random_value<float>(0.0f, 10.0f);

private:
	template <typename Archive>
	friend void serialize(Archive& ar, Base& o, hamon::serialization::version_t version)
	{
		EXPECT_EQ(3u, version);
		ar & o.a;
	}
	
	hamon::serialization::version_t get_class_version() const
	{
		return 3;
	}

private:
	HAMON_SERIALIZATION_CLASS_ID("unique_ptr_polymorphic_version_test::Base");

public:
	static int instance_count;
};

int Base::instance_count = 0;

class Derived : public Base
{
public:
	Derived() { ++Derived::instance_count; }
	~Derived() { --Derived::instance_count; }

	float GetValue() const override
	{
		return Base::GetValue() + static_cast<float>(b);
	}

private:
	int b = get_random_value<int>(-1000, 1000);

private:
	template <typename Archive>
	friend void serialize(Archive& ar, Derived& o, hamon::serialization::version_t version)
	{
		EXPECT_EQ(4u, version);
		ar & hamon::serialization::base_object<Base>(o);
		ar & o.b;
	}
	
	hamon::serialization::version_t get_class_version() const
	{
		return 4;
	}

private:
	HAMON_SERIALIZATION_CLASS_ID("unique_ptr_polymorphic_version_test::Derived");

public:
	static int instance_count;
};

int Derived::instance_count = 0;

HAMON_SERIALIZATION_REGISTER_POLYMORPHIC_CLASS(Derived)

template <typename Stream, typename OArchive, typename IArchive>
void UniquePtrPolymorphicVersionTest()
{
	EXPECT_EQ(0, Base::instance_count);
	EXPECT_EQ(0, Derived::instance_count);

	{
		std::unique_ptr<Base>    p1(new Base());
		std::unique_ptr<Base>    p2(new Derived());
		std::unique_ptr<Derived> p3(new Derived());

		EXPECT_EQ(3, Base::instance_count);
		EXPECT_EQ(2, Derived::instance_count);

		Stream str;
		{
			OArchive oa(str);
			oa << p1;
			oa << p2;
			oa << p3;

			EXPECT_EQ(3, Base::instance_count);
			EXPECT_EQ(2, Derived::instance_count);
		}

		EXPECT_EQ(3, Base::instance_count);
		EXPECT_EQ(2, Derived::instance_count);

		{
			std::unique_ptr<Base>    a;
			std::unique_ptr<Base>    b;
			std::unique_ptr<Derived> c;

			IArchive ia(str);

			EXPECT_EQ(3, Base::instance_count);
			EXPECT_EQ(2, Derived::instance_count);

			ia >> a;
			ia >> b;
			ia >> c;

			EXPECT_EQ(6, Base::instance_count);
			EXPECT_EQ(4, Derived::instance_count);

			EXPECT_EQ(p1->GetValue(), a->GetValue());
			EXPECT_EQ(p2->GetValue(), b->GetValue());
			EXPECT_EQ(p3->GetValue(), c->GetValue());
			EXPECT_TRUE(p1 != a);
			EXPECT_TRUE(p2 != b);
			EXPECT_TRUE(p3 != c);
		}

		EXPECT_EQ(3, Base::instance_count);
		EXPECT_EQ(2, Derived::instance_count);
	}

	EXPECT_EQ(0, Base::instance_count);
	EXPECT_EQ(0, Derived::instance_count);
}

using UniquePtrPolymorphicVersionTestTypes = ::testing::Types<
	std::tuple<std::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>
>;

template <typename T>
class SerializationUniquePtrPolymorphicVersionTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationUniquePtrPolymorphicVersionTest, UniquePtrPolymorphicVersionTestTypes);

TYPED_TEST(SerializationUniquePtrPolymorphicVersionTest, UniquePtrPolymorphicVersionTest)
{
	using Stream   = typename std::tuple_element<0, TypeParam>::type;
	using OArchive = typename std::tuple_element<1, TypeParam>::type;
	using IArchive = typename std::tuple_element<2, TypeParam>::type;

	UniquePtrPolymorphicVersionTest<Stream, OArchive, IArchive>();
}

}	// namespace unique_ptr_polymorphic_version_test

}	// namespace hamon_serialization_test
