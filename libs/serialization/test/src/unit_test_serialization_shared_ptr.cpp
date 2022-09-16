/**
 *	@file	unit_test_serialization_shared_ptr.cpp
 *
 *	@brief	std::shared_ptr のシリアライズのテスト
 */

#include <hamon/serialization/shared_ptr.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <sstream>
#include <memory>
#include "serialization_test_archives.hpp"
#include "serialization_test_utility.hpp"

namespace hamon_serialization_test
{

namespace shared_ptr_test
{

template <typename Stream, typename OArchive, typename IArchive>
void SharedPtrTest()
{
	std::shared_ptr<int> p1;
	std::shared_ptr<int> p2(new int(1));
	std::shared_ptr<int> p3(new int(2));
	std::shared_ptr<int> p4(p3);
	std::shared_ptr<int> p5(new int(3));
	std::shared_ptr<int> p6(p5);
	std::shared_ptr<int> p7(p5);
	std::shared_ptr<int> p8(new int(3));

	Stream str;
	{

		OArchive oa(str);
		
		oa << p1;
		oa << p2;
		oa << p3;
		oa << p4;
		oa << p5;
		oa << p6;
		oa << p7;
		oa << p8;
	}
	{
		std::shared_ptr<int> a;
		std::shared_ptr<int> b;
		std::shared_ptr<int> c;
		std::shared_ptr<int> d;
		std::shared_ptr<int> e;
		std::shared_ptr<int> f;
		std::shared_ptr<int> g;
		std::shared_ptr<int> h;

		IArchive ia(str);

		ia >> a;
		ia >> b;
		ia >> c;
		ia >> d;
		ia >> e;
		ia >> f;
		ia >> g;
		ia >> h;

		EXPECT_EQ(nullptr, a);
		EXPECT_NE(nullptr, b);
		EXPECT_NE(nullptr, c);
		EXPECT_NE(nullptr, d);
		EXPECT_NE(nullptr, e);
		EXPECT_NE(nullptr, f);
		EXPECT_NE(nullptr, g);
		EXPECT_NE(nullptr, h);
		
		EXPECT_EQ(1, *b);
		EXPECT_EQ(2, *c);
		EXPECT_EQ(2, *d);
		EXPECT_EQ(3, *e);
		EXPECT_EQ(3, *f);
		EXPECT_EQ(3, *g);
		EXPECT_EQ(3, *h);

		EXPECT_EQ(c, d);
		EXPECT_EQ(e, f);
		EXPECT_EQ(e, g);
		EXPECT_NE(e, h);
	}
}

using SharedPtrTestTypes = ::testing::Types<
	std::tuple<std::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>
>;

template <typename T>
class SerializationSharedPtrTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationSharedPtrTest, SharedPtrTestTypes);

TYPED_TEST(SerializationSharedPtrTest, SharedPtrTest)
{
	using Stream   = typename std::tuple_element<0, TypeParam>::type;
	using OArchive = typename std::tuple_element<1, TypeParam>::type;
	using IArchive = typename std::tuple_element<2, TypeParam>::type;

	SharedPtrTest<Stream, OArchive, IArchive>();
}

}	// namespace shared_ptr_test

}	// namespace hamon_serialization_test
