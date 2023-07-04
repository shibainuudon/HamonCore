/**
 *	@file	unit_test_serialization_weak_ptr_polymorphic.cpp
 *
 *	@brief	std::weak_ptr のシリアライズのテスト
 */

#include <hamon/serialization/types/weak_ptr.hpp>
#include <hamon/serialization/types/shared_ptr.hpp>
#include <hamon/serialization/base_object.hpp>
#include <hamon/serialization/class_id.hpp>
#include <hamon/serialization/register_polymorphic_class.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <sstream>
#include <memory>
#include "serialization_test_archives.hpp"
#include "get_random_value.hpp"

namespace hamon_serialization_test
{

namespace weak_ptr_polymorphic_test
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
	friend void serialize(Archive& ar, Base& o)
	{
		ar & o.a;
	}

private:
	HAMON_SERIALIZATION_CLASS_ID("weak_ptr_polymorphic_test::Base");

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
	friend void serialize(Archive& ar, Derived& o)
	{
		ar & hamon::serialization::base_object<Base>(o);
		ar & o.b;
	}

private:
	HAMON_SERIALIZATION_CLASS_ID("weak_ptr_polymorphic_test::Derived");

public:
	static int instance_count;
};

int Derived::instance_count = 0;

HAMON_SERIALIZATION_REGISTER_POLYMORPHIC_CLASS(Derived)

template <typename Stream, typename OArchive, typename IArchive>
void WeakPtrPolymorphicTest()
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

using WeakPtrPolymorphicTestTypes = ::testing::Types<
	std::tuple<std::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>
>;

template <typename T>
class SerializationWeakPtrPolymorphicTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationWeakPtrPolymorphicTest, WeakPtrPolymorphicTestTypes);

TYPED_TEST(SerializationWeakPtrPolymorphicTest, WeakPtrPolymorphicTest)
{
	using Stream   = typename std::tuple_element<0, TypeParam>::type;
	using OArchive = typename std::tuple_element<1, TypeParam>::type;
	using IArchive = typename std::tuple_element<2, TypeParam>::type;

	WeakPtrPolymorphicTest<Stream, OArchive, IArchive>();
}

}	// namespace weak_ptr_polymorphic_test

}	// namespace hamon_serialization_test
