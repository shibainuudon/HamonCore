/**
 *	@file	unit_test_serialization_integral.cpp
 *
 *	@brief	整数型のシリアライズのテスト
 */

#include <hamon/serialization.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <sstream>
#include <limits>
#include "serialization_test_utility.hpp"

namespace hamon_serialization_test
{

namespace integral_test
{

template <typename Stream, typename OArchive, typename IArchive, typename T>
void IntegralTest()
{
	T const rnd1  = get_random_value<T>();
	T const rnd2  = get_random_value<T>(T(0), T(10));
	T const zero  = T(0);
	T const one   = T(1);
	T const minus = T(-1);
	T const min   = std::numeric_limits<T>::min();
	T const max   = std::numeric_limits<T>::max();
	T const low   = std::numeric_limits<T>::lowest();

	Stream str;
	{
		OArchive oa(str);
		oa	<< rnd1
			<< rnd2
			<< zero
			<< one
			<< minus
			<< min
			<< max
			<< low;
	}
	{
		T a;
		T b;
		T c;
		T d;
		T e;
		T f;
		T g;
		T h;

		IArchive ia(str);

		ia >> a >> b >> c >> d >> e >> f >> g >> h;
		EXPECT_EQ(a, rnd1);
		EXPECT_EQ(b, rnd2);
		EXPECT_EQ(c, zero);
		EXPECT_EQ(d, one);
		EXPECT_EQ(e, minus);
		EXPECT_EQ(f, min);
		EXPECT_EQ(g, max);
		EXPECT_EQ(h, low);
	}
}

using IntegralTestTypes = ::testing::Types<
	std::tuple<std::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>
>;

template <typename T>
class SerializationIntegralTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationIntegralTest, IntegralTestTypes);

TYPED_TEST(SerializationIntegralTest, IntegralTest)
{
	using Stream   = typename std::tuple_element<0, TypeParam>::type;
	using OArchive = typename std::tuple_element<1, TypeParam>::type;
	using IArchive = typename std::tuple_element<2, TypeParam>::type;

	IntegralTest<Stream, OArchive, IArchive, bool>();
	IntegralTest<Stream, OArchive, IArchive, char>();
	IntegralTest<Stream, OArchive, IArchive, signed char>();
	IntegralTest<Stream, OArchive, IArchive, unsigned char>();
	IntegralTest<Stream, OArchive, IArchive, wchar_t>();
	IntegralTest<Stream, OArchive, IArchive, short>();
	IntegralTest<Stream, OArchive, IArchive, unsigned short>();
	IntegralTest<Stream, OArchive, IArchive, int>();
	IntegralTest<Stream, OArchive, IArchive, unsigned int>();
	IntegralTest<Stream, OArchive, IArchive, long>();
	IntegralTest<Stream, OArchive, IArchive, unsigned long>();
	IntegralTest<Stream, OArchive, IArchive, long long>();
	IntegralTest<Stream, OArchive, IArchive, unsigned long long>();
#if defined(HAMON_HAS_CXX20_CHAR8_T)
	IntegralTest<Stream, OArchive, IArchive, char8_t>();
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	IntegralTest<Stream, OArchive, IArchive, char16_t>();
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	IntegralTest<Stream, OArchive, IArchive, char32_t>();
#endif
}

}	// namespace integral_test

}	// namespace hamon_serialization_test
