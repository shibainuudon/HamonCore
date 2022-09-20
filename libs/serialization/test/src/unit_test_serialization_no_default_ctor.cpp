/**
 *	@file	unit_test_serialization_no_default_ctor.cpp
 *
 *	@brief	デフォルトコンストラクタを持たないクラスのシリアライズのテスト
 */

#include <hamon/serialization/unique_ptr.hpp>
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
	ar << p->GetA();
	ar << p->GetB();
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
	std::unique_ptr<Object> p1(new Object(42));
	std::unique_ptr<Object> p2(new Object(2, 3.5f));

	Stream str;
	{

		OArchive oa(str);
		
		oa << p1;
		oa << p2;
	}

	std::string expected =
R"({
    "value0": {
        "version": 0,
        "has_value": true,
        "class_id": "",
        "value": {
            "version": 0,
            "value0": 42,
            "value1": 0
        }
    },
    "value1": {
        "version": 0,
        "has_value": true,
        "class_id": "",
        "value": {
            "version": 0,
            "value0": 2,
            "value1": 3.5
        }
    }
})";
	EXPECT_EQ(expected, str.str());

    {
		std::unique_ptr<Object> a;
		std::unique_ptr<Object> b;

		IArchive ia(str);

		ia >> a;
		ia >> b;

		EXPECT_EQ(p1->GetA(), a->GetA());
		EXPECT_EQ(p1->GetB(), a->GetB());
		EXPECT_EQ(p2->GetA(), b->GetA());
		EXPECT_EQ(p2->GetB(), b->GetB());
		EXPECT_NE(p1, a);
		EXPECT_NE(p2, b);
	}
}

using NoDefaultCtorTestTypes = ::testing::Types<
	//std::tuple<std::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	//std::tuple<std::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	//std::tuple<std::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>/*,
	std::tuple<std::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>*/
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
