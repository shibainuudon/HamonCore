/**
 *	@file	unit_test_serialization_weak_ptr_polymorphic.cpp
 *
 *	@brief	hamon::weak_ptr のシリアライズのテスト
 */

#include <hamon/serialization/types/weak_ptr.hpp>
#include <hamon/serialization/types/shared_ptr.hpp>
#include <hamon/serialization/base_object.hpp>
#include <hamon/serialization/class_id.hpp>
#include <hamon/serialization/register_polymorphic_class.hpp>
#include <hamon/sstream/stringstream.hpp>
#include <hamon/sstream/wstringstream.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/memory/weak_ptr.hpp>
#include <hamon/tuple.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "serialization_test_archives.hpp"
#include "get_random_value.hpp"

#if !defined(HAMON_NO_STD)
#include <memory>
#endif

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

template <typename Stream, typename OArchive, typename IArchive,
	template <typename...> class WeakPtr,
	template <typename...> class SharedPtr
>
void WeakPtrPolymorphicTest()
{
	EXPECT_EQ(0, Base::instance_count);
	EXPECT_EQ(0, Derived::instance_count);

	{
		WeakPtr<Base>      p0;
		SharedPtr<Base>    p1(new Base());
		SharedPtr<Base>    p2(new Derived());
		SharedPtr<Derived> p3(new Derived());
		WeakPtr<Base>      p4(p2);
		WeakPtr<Base>      p5(p3);
		WeakPtr<Derived>   p6(p3);

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
			WeakPtr<Base>      a;
			SharedPtr<Base>    b;
			SharedPtr<Base>    c;
			SharedPtr<Derived> d;
			WeakPtr<Base>      e;
			WeakPtr<Base>      f;
			WeakPtr<Derived>   g;

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
	hamon::tuple<hamon::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	hamon::tuple<hamon::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	hamon::tuple<hamon::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	hamon::tuple<hamon::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	hamon::tuple<hamon::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	hamon::tuple<hamon::stringstream,  hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>,
	hamon::tuple<hamon::wstringstream, hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>
>;

template <typename T>
class SerializationWeakPtrPolymorphicTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationWeakPtrPolymorphicTest, WeakPtrPolymorphicTestTypes);

TYPED_TEST(SerializationWeakPtrPolymorphicTest, WeakPtrPolymorphicTest)
{
	using Stream   = typename hamon::tuple_element<0, TypeParam>::type;
	using OArchive = typename hamon::tuple_element<1, TypeParam>::type;
	using IArchive = typename hamon::tuple_element<2, TypeParam>::type;

	WeakPtrPolymorphicTest<Stream, OArchive, IArchive, hamon::weak_ptr, hamon::shared_ptr>();
#if !defined(HAMON_NO_STD)
	WeakPtrPolymorphicTest<Stream, OArchive, IArchive, std::weak_ptr, std::shared_ptr>();
#endif
}

}	// namespace weak_ptr_polymorphic_test

}	// namespace hamon_serialization_test
