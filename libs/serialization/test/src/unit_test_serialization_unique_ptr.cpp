/**
 *	@file	unit_test_serialization_unique_ptr.cpp
 *
 *	@brief	hamon::unique_ptr のシリアライズのテスト
 */

#include <hamon/serialization/types/unique_ptr.hpp>
#include <hamon/sstream/stringstream.hpp>
#include <hamon/sstream/wstringstream.hpp>
#include <hamon/memory/unique_ptr.hpp>
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

namespace unique_ptr_test
{

class Object
{
private:
	float a = get_random_value<float>();

private:
	friend bool operator==(Object const& lhs, Object const& rhs)
	{
		return lhs.a == rhs.a;
	}

	friend bool operator!=(Object const& lhs, Object const& rhs)
	{
		return !(lhs == rhs);
	}

private:
	friend class hamon::serialization::access;

	template <typename Archive>
	void serialize(Archive& ar)
	{
		ar & a;
	}
};

template <typename Stream, typename OArchive, typename IArchive,
	template <typename...> class UniquePtr
>
void UniquePtrTest()
{
	UniquePtr<int> p1;
	UniquePtr<int> p2(new int(42));
	UniquePtr<Object> p3(new Object());

	Stream str;
	{

		OArchive oa(str);
		
		oa << p1;
		oa << p2;
		oa << p3;
	}
	{
		UniquePtr<int> a;
		UniquePtr<int> b;
		UniquePtr<Object> c;

		IArchive ia(str);

		ia >> a;
		ia >> b;
		ia >> c;

		EXPECT_EQ(p1, a);
		EXPECT_EQ(nullptr, a);

		EXPECT_NE(p2, b);
		EXPECT_EQ(*p2, *b);

		EXPECT_NE(p3, c);
		EXPECT_EQ(*p3, *c);
	}
}

using UniquePtrTestTypes = ::testing::Types<
	hamon::tuple<hamon::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	hamon::tuple<hamon::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	hamon::tuple<hamon::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	hamon::tuple<hamon::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	hamon::tuple<hamon::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	hamon::tuple<hamon::stringstream,  hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>,
	hamon::tuple<hamon::wstringstream, hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>
>;

template <typename T>
class SerializationUniquePtrTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationUniquePtrTest, UniquePtrTestTypes);

TYPED_TEST(SerializationUniquePtrTest, UniquePtrTest)
{
	using Stream   = typename hamon::tuple_element<0, TypeParam>::type;
	using OArchive = typename hamon::tuple_element<1, TypeParam>::type;
	using IArchive = typename hamon::tuple_element<2, TypeParam>::type;

	UniquePtrTest<Stream, OArchive, IArchive, hamon::unique_ptr>();
#if !defined(HAMON_NO_STD)
	UniquePtrTest<Stream, OArchive, IArchive, std::unique_ptr>();
#endif
}

}	// namespace unique_ptr_test

}	// namespace hamon_serialization_test
