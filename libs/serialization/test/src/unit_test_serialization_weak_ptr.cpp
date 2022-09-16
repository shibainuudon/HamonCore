/**
 *	@file	unit_test_serialization_weak_ptr.cpp
 *
 *	@brief	std::weak_ptr のシリアライズのテスト
 */

#include <hamon/serialization/weak_ptr.hpp>
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

namespace weak_ptr_test
{

template <typename Stream, typename OArchive, typename IArchive>
void WeakPtrTest()
{
	Stream str;
	{
		std::weak_ptr<int>   p1;
		std::shared_ptr<int> p2(new int(10));
		std::weak_ptr<int>   p3(p2);
		std::weak_ptr<int>   p4;
		std::shared_ptr<int> p5(new int(20));
		std::weak_ptr<int>   p6(p5);
		p4 = p5;

		OArchive oa(str);
		oa << p1 << p2 << p3 << p4 << p5 << p6;
	}
	{
		std::weak_ptr<int>   a;
		std::shared_ptr<int> b;
		std::weak_ptr<int>   c;
		std::weak_ptr<int>   d;
		std::shared_ptr<int> e;
		std::weak_ptr<int>   f;

		IArchive ia(str);

		ia >> a >> b >> c >> d >> e >> f;

		EXPECT_TRUE(a.expired());

		EXPECT_EQ(10, *b);

		EXPECT_TRUE(!c.expired());
		EXPECT_EQ(10, *(c.lock()));
		EXPECT_TRUE(b == c.lock());

		EXPECT_TRUE(!d.expired());
		EXPECT_EQ(20, *(d.lock()));
		EXPECT_TRUE(e == d.lock());

		EXPECT_EQ(20, *e);

		EXPECT_TRUE(!f.expired());
		EXPECT_EQ(20, *(f.lock()));
		EXPECT_TRUE(e == f.lock());
	}
}

using WeakPtrTestTypes = ::testing::Types<
	std::tuple<std::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>
>;

template <typename T>
class SerializationWeakPtrTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationWeakPtrTest, WeakPtrTestTypes);

TYPED_TEST(SerializationWeakPtrTest, WeakPtrTest)
{
	using Stream   = typename std::tuple_element<0, TypeParam>::type;
	using OArchive = typename std::tuple_element<1, TypeParam>::type;
	using IArchive = typename std::tuple_element<2, TypeParam>::type;

	WeakPtrTest<Stream, OArchive, IArchive>();
}

}	// namespace weak_ptr_test

}	// namespace hamon_serialization_test
