/**
 *	@file	unit_test_serialization_weak_ptr_polymorphic_version.cpp
 *
 *	@brief	std::weak_ptr のシリアライズ(バージョンあり)のテスト
 */

#include <hamon/serialization/weak_ptr.hpp>
#include <hamon/serialization/shared_ptr.hpp>
#include <hamon/serialization/base_object.hpp>
#include <hamon/serialization/class_id.hpp>
#include <hamon/serialization/export_class.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <sstream>
#include <memory>
#include "serialization_test_archives.hpp"
#include "serialization_test_utility.hpp"

namespace hamon_serialization_test
{

namespace weak_ptr_polymorphic_version_test
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
		EXPECT_EQ(10u, version);
		ar & o.a;
	}

	friend constexpr hamon::serialization::version_t get_class_version(Base const&)
	{
		return 10;
	}

private:
	HAMON_SERIALIZATION_CLASS_ID("weak_ptr_polymorphic_version_test::Base");

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
		return Base::GetValue() + b;
	}

private:
	int b = get_random_value<int>(-1000, 1000);

private:
	template <typename Archive>
	friend void serialize(Archive& ar, Derived& o, hamon::serialization::version_t version)
	{
		EXPECT_EQ(20u, version);
		ar & hamon::serialization::base_object<Base>(o);
		ar & o.b;
	}

	friend constexpr hamon::serialization::version_t get_class_version(Derived const&)
	{
		return 20;
	}

private:
	HAMON_SERIALIZATION_CLASS_ID("weak_ptr_polymorphic_version_test::Derived");

public:
	static int instance_count;
};

int Derived::instance_count = 0;

HAMON_SERIALIZATION_EXPORT_CLASS(Derived);

template <typename Stream, typename OArchive, typename IArchive>
void WeakPtrPolymorphicVersionTest()
{
	EXPECT_EQ(0, Base::instance_count);
	EXPECT_EQ(0, Derived::instance_count);

	{
		std::weak_ptr<Base>      p0;
		std::shared_ptr<Base>    p1(new Base());
		std::shared_ptr<Base>    p2(new Derived());
		std::shared_ptr<Derived> p3(new Derived());
		std::weak_ptr<Base>      p4(p2);
		std::weak_ptr<Base>      p5(p3);
		std::weak_ptr<Derived>   p6(p3);

		EXPECT_EQ(3, Base::instance_count);
		EXPECT_EQ(2, Derived::instance_count);

		Stream str;
		{
			OArchive oa(str);
			oa << p0;
			oa << p1;
			oa << p2;
			oa << p3;
			oa << p4;
			oa << p5;
			oa << p6;

			EXPECT_EQ(3, Base::instance_count);
			EXPECT_EQ(2, Derived::instance_count);
		}

		EXPECT_EQ(3, Base::instance_count);
		EXPECT_EQ(2, Derived::instance_count);

		{
			std::weak_ptr<Base>      a;
			std::shared_ptr<Base>    b;
			std::shared_ptr<Base>    c;
			std::shared_ptr<Derived> d;
			std::weak_ptr<Base>      e;
			std::weak_ptr<Base>      f;
			std::weak_ptr<Derived>   g;

			IArchive ia(str);

			EXPECT_EQ(3, Base::instance_count);
			EXPECT_EQ(2, Derived::instance_count);

			ia >> a;
			ia >> b;
			ia >> c;
			ia >> d;
			ia >> e;
			ia >> f;
			ia >> g;

			EXPECT_EQ(6, Base::instance_count);
			EXPECT_EQ(4, Derived::instance_count);

			EXPECT_TRUE(a.expired());
			EXPECT_NE(nullptr, b);
			EXPECT_NE(nullptr, c);
			EXPECT_NE(nullptr, d);
			EXPECT_FALSE(e.expired());
			EXPECT_FALSE(f.expired());
			EXPECT_FALSE(g.expired());

			EXPECT_EQ(p1->GetValue(), b->GetValue());
			EXPECT_EQ(p2->GetValue(), c->GetValue());
			EXPECT_EQ(p3->GetValue(), d->GetValue());
			EXPECT_EQ(p4.lock()->GetValue(), e.lock()->GetValue());
			EXPECT_EQ(p5.lock()->GetValue(), f.lock()->GetValue());
			EXPECT_EQ(p6.lock()->GetValue(), g.lock()->GetValue());
			EXPECT_TRUE(p1 != b);
			EXPECT_TRUE(p2 != c);
			EXPECT_TRUE(p3 != d);
			EXPECT_TRUE(p4.lock() != e.lock());
			EXPECT_TRUE(p5.lock() != f.lock());
			EXPECT_TRUE(p6.lock() != g.lock());
			EXPECT_TRUE(c == e.lock());
			EXPECT_TRUE(d == f.lock());
			EXPECT_TRUE(d == g.lock());
		}

		EXPECT_EQ(3, Base::instance_count);
		EXPECT_EQ(2, Derived::instance_count);
	}

	EXPECT_EQ(0, Base::instance_count);
	EXPECT_EQ(0, Derived::instance_count);
}

using WeakPtrPolymorphicVersionTestTypes = ::testing::Types<
	std::tuple<std::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>
>;

template <typename T>
class SerializationWeakPtrPolymorphicVersionTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationWeakPtrPolymorphicVersionTest, WeakPtrPolymorphicVersionTestTypes);

TYPED_TEST(SerializationWeakPtrPolymorphicVersionTest, WeakPtrPolymorphicVersionTest)
{
	using Stream   = typename std::tuple_element<0, TypeParam>::type;
	using OArchive = typename std::tuple_element<1, TypeParam>::type;
	using IArchive = typename std::tuple_element<2, TypeParam>::type;

	WeakPtrPolymorphicVersionTest<Stream, OArchive, IArchive>();
}

}	// namespace weak_ptr_polymorphic_version_test

}	// namespace hamon_serialization_test
