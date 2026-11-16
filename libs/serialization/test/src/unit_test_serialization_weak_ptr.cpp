/**
 *	@file	unit_test_serialization_weak_ptr.cpp
 *
 *	@brief	hamon::weak_ptr のシリアライズのテスト
 */

#include <hamon/serialization/types/weak_ptr.hpp>
#include <hamon/serialization/types/shared_ptr.hpp>
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

namespace weak_ptr_test
{

template <typename Stream, typename OArchive, typename IArchive,
	template <typename...> class WeakPtr,
	template <typename...> class SharedPtr
>
void WeakPtrTest()
{
	Stream str;
	{
		WeakPtr<int>   p1;
		SharedPtr<int> p2(new int(10));
		WeakPtr<int>   p3(p2);
		WeakPtr<int>   p4;
		SharedPtr<int> p5(new int(20));
		WeakPtr<int>   p6(p5);
		p4 = p5;

		OArchive oa(str);
		oa << p1 << p2 << p3 << p4 << p5 << p6;
	}
	{
		WeakPtr<int>   a;
		SharedPtr<int> b;
		WeakPtr<int>   c;
		WeakPtr<int>   d;
		SharedPtr<int> e;
		WeakPtr<int>   f;

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
	hamon::tuple<hamon::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	hamon::tuple<hamon::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	hamon::tuple<hamon::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	hamon::tuple<hamon::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	hamon::tuple<hamon::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	hamon::tuple<hamon::stringstream,  hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>,
	hamon::tuple<hamon::wstringstream, hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>
>;

template <typename T>
class SerializationWeakPtrTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationWeakPtrTest, WeakPtrTestTypes);

TYPED_TEST(SerializationWeakPtrTest, WeakPtrTest)
{
	using Stream   = typename hamon::tuple_element<0, TypeParam>::type;
	using OArchive = typename hamon::tuple_element<1, TypeParam>::type;
	using IArchive = typename hamon::tuple_element<2, TypeParam>::type;

	WeakPtrTest<Stream, OArchive, IArchive, hamon::weak_ptr, hamon::shared_ptr>();
#if !defined(HAMON_NO_STD)
	WeakPtrTest<Stream, OArchive, IArchive, std::weak_ptr, std::shared_ptr>();
#endif
}

}	// namespace weak_ptr_test

}	// namespace hamon_serialization_test
