/**
 *	@file	unit_test_serialization_integral.cpp
 *
 *	@brief	整数型のシリアライズのテスト
 */

#include <hamon/serialization.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include "serialization_test_utility.hpp"

namespace hamon_serialization_test
{

namespace integral_test
{

template <typename Stream, typename OArchive, typename IArchive, typename T>
void IntegralTestSub()
{
	T const rnd = get_random_value<T>();
	T const min = std::numeric_limits<T>::min();
	T const max = std::numeric_limits<T>::max();
	T const low = std::numeric_limits<T>::lowest();

	Stream str;
	{
		OArchive oa(str);
		oa << rnd << min << max << low;
	}
	{
		T a;
		T b;
		T c;
		T d;

		IArchive ia(str);

		ia >> a >> b >> c >> d;
		EXPECT_EQ(a, rnd);
		EXPECT_EQ(b, min);
		EXPECT_EQ(c, max);
		EXPECT_EQ(d, low);
	}
}

template <typename Stream, typename OArchive, typename IArchive>
void IntegralTest()
{
	IntegralTestSub<Stream, OArchive, IArchive, bool>();
	IntegralTestSub<Stream, OArchive, IArchive, char>();
	IntegralTestSub<Stream, OArchive, IArchive, signed char>();
	IntegralTestSub<Stream, OArchive, IArchive, unsigned char>();
	IntegralTestSub<Stream, OArchive, IArchive, wchar_t>();
	IntegralTestSub<Stream, OArchive, IArchive, short>();
	IntegralTestSub<Stream, OArchive, IArchive, unsigned short>();
	IntegralTestSub<Stream, OArchive, IArchive, int>();
	IntegralTestSub<Stream, OArchive, IArchive, unsigned int>();
	IntegralTestSub<Stream, OArchive, IArchive, long>();
	IntegralTestSub<Stream, OArchive, IArchive, unsigned long>();
	IntegralTestSub<Stream, OArchive, IArchive, long long>();
	IntegralTestSub<Stream, OArchive, IArchive, unsigned long long>();
#if defined(HAMON_HAS_CXX20_CHAR8_T)
	IntegralTestSub<Stream, OArchive, IArchive, char8_t>();
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	IntegralTestSub<Stream, OArchive, IArchive, char16_t>();
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	IntegralTestSub<Stream, OArchive, IArchive, char32_t>();
#endif
}

using IntegralTestTypes = ::testing::Types<
	std::tuple<std::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>
>;

template <typename T>
class SerializationIntegralTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationIntegralTest, IntegralTestTypes);

TYPED_TEST(SerializationIntegralTest, IntegralTest)
{
	using Stream   = typename std::tuple_element<0, TypeParam>::type;
	using OArchive = typename std::tuple_element<1, TypeParam>::type;
	using IArchive = typename std::tuple_element<2, TypeParam>::type;
	IntegralTest<Stream, OArchive, IArchive>();
}

}	// namespace integral_test

}	// namespace hamon_serialization_test
