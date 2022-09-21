﻿/**
 *	@file	unit_test_serialization_no_default_ctor.cpp
 *
 *	@brief	デフォルトコンストラクタを持たないクラスのシリアライズのテスト
 */

#include <hamon/serialization/unique_ptr.hpp>
#include <hamon/serialization/shared_ptr.hpp>
#include <hamon/serialization/weak_ptr.hpp>
#include <hamon/memory/construct_at.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <sstream>
#include <memory>
#include "serialization_test_archives.hpp"
#include "serialization_test_utility.hpp"

namespace hamon_serialization_test
{

namespace no_default_ctor_test
{

class Object
{
public:
	Object(int a)
		: a(a), b(0)
	{}

	Object(int a, float b)
		: a(a), b(b)
	{}

private:
	int   a;
	float b;

public:
	int   GetA() const { return a; }
	float GetB() const { return b; }
};

template <typename Archive>
void save_construct_data(Archive& ar, Object const* p)
{
	ar << hamon::serialization::make_nvp("a", p->GetA());
	ar << hamon::serialization::make_nvp("b", p->GetB());
}

template <typename Archive>
void load_construct_data(Archive& ar, Object* p)
{
	int   a;
	float b;
	ar >> a;
	ar >> b;
	hamon::construct_at(p, a, b);
}

template <typename Stream, typename OArchive, typename IArchive>
void NoDefaultCtorTest()
{
	std::unique_ptr<Object> p0;
	std::unique_ptr<Object> p1(new Object(42));
	std::unique_ptr<Object> p2(new Object(2, 3.5f));
	std::shared_ptr<Object> p3(new Object(56));
	std::shared_ptr<Object> p4(new Object(3, 4.5f));
	std::weak_ptr<Object>   p5(p4);

	Stream str;
	{

		OArchive oa(str);
		
		oa << hamon::serialization::make_nvp("p0", p0);
		oa << hamon::serialization::make_nvp("p1", p1);
		oa << hamon::serialization::make_nvp("p2", p2);
		oa << hamon::serialization::make_nvp("p3", p3);
		oa << hamon::serialization::make_nvp("p4", p4);
		oa << hamon::serialization::make_nvp("p5", p5);
	}

#if 0
	std::string expected =
R"({
    "p0": {
        "has_value": false
    },
    "p1": {
        "has_value": true,
        "class_id": "",
        "value": {
            "version": 0,
            "a": 42,
            "b": 0
        }
    },
    "p2": {
        "has_value": true,
        "class_id": "",
        "value": {
            "version": 0,
            "a": 2,
            "b": 3.5
        }
    },
    "p3": {
        "has_value": true,
        "shared_index": -1,
        "class_id": "",
        "value": {
            "version": 0,
            "a": 56,
            "b": 0
        }
    },
    "p4": {
        "has_value": true,
        "shared_index": -1,
        "class_id": "",
        "value": {
            "version": 0,
            "a": 3,
            "b": 4.5
        }
    },
    "p5": {
        "has_value": true,
        "shared_index": 1
    }
})";
	EXPECT_EQ(expected, str.str());
#endif

    {
		std::unique_ptr<Object> a;
		std::unique_ptr<Object> b;
		std::unique_ptr<Object> c;
		std::shared_ptr<Object> d;
		std::shared_ptr<Object> e;
		std::weak_ptr<Object>   f;

		IArchive ia(str);

		ia >> a;
		ia >> b;
		ia >> c;
		ia >> d;
		ia >> e;
		ia >> f;

		EXPECT_EQ(nullptr, a);
		EXPECT_NE(nullptr, b);
		EXPECT_NE(nullptr, c);
		EXPECT_NE(nullptr, d);
		EXPECT_NE(nullptr, e);
		EXPECT_NE(nullptr, f.lock());
		EXPECT_EQ(p1->GetA(), b->GetA());
		EXPECT_EQ(p1->GetB(), b->GetB());
		EXPECT_EQ(p2->GetA(), c->GetA());
		EXPECT_EQ(p2->GetB(), c->GetB());
		EXPECT_EQ(p3->GetA(), d->GetA());
		EXPECT_EQ(p3->GetB(), d->GetB());
		EXPECT_EQ(p4->GetA(), e->GetA());
		EXPECT_EQ(p4->GetB(), e->GetB());
		EXPECT_EQ(p5.lock()->GetA(), f.lock()->GetA());
		EXPECT_EQ(p5.lock()->GetB(), f.lock()->GetB());
		EXPECT_NE(p1, b);
		EXPECT_NE(p2, c);
		EXPECT_NE(p3, d);
		EXPECT_NE(p4, e);
		EXPECT_NE(p5.lock(), f.lock());
	}
}

using NoDefaultCtorTestTypes = ::testing::Types<
	std::tuple<std::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>
>;

template <typename T>
class SerializationNoDefaultCtorTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationNoDefaultCtorTest, NoDefaultCtorTestTypes);

TYPED_TEST(SerializationNoDefaultCtorTest, NoDefaultCtorTest)
{
	using Stream   = typename std::tuple_element<0, TypeParam>::type;
	using OArchive = typename std::tuple_element<1, TypeParam>::type;
	using IArchive = typename std::tuple_element<2, TypeParam>::type;

	NoDefaultCtorTest<Stream, OArchive, IArchive>();
}

}	// namespace no_default_ctor_test

}	// namespace hamon_serialization_test
