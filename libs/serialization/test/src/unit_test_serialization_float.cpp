/**
 *	@file	unit_test_serialization_float.cpp
 *
 *	@brief	浮動小数点型のシリアライズのテスト
 */

#include <hamon/cmath/isnan.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <sstream>
#include "serialization_test_archives.hpp"
#include "get_random_value.hpp"

namespace hamon_serialization_test
{

namespace float_test
{

template <typename Stream, typename OArchive, typename IArchive, typename T>
void FloatTest()
{
	T const rnd1  = get_random_value<T>();
	T const rnd2  = get_random_value<T>(T(0), T(10));
	T const zero  = T(0);
	T const one   = T(1);
	T const minus = T(-1);
	T const min   = hamon::numeric_limits<T>::min();
	T const max   = hamon::numeric_limits<T>::max();
	T const low   = hamon::numeric_limits<T>::lowest();
	T const inf   = hamon::numeric_limits<T>::infinity();
	T const inf2  = -hamon::numeric_limits<T>::infinity();
	T const nan   = hamon::numeric_limits<T>::quiet_NaN();
	T const nan2  = -hamon::numeric_limits<T>::quiet_NaN();

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
			<< low
			<< inf
			<< inf2
			<< nan
			<< nan2;
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
		T i;
		T j;
		T k;
		T l;

		IArchive ia(str);

		ia >> a >> b >> c >> d >> e >> f >> g >> h >> i >> j >> k >> l;
		EXPECT_EQ(a, rnd1);
		EXPECT_EQ(b, rnd2);
		EXPECT_EQ(c, zero);
		EXPECT_EQ(d, one);
		EXPECT_EQ(e, minus);
		EXPECT_EQ(f, min);
		EXPECT_EQ(g, max);
		EXPECT_EQ(h, low);
		EXPECT_EQ(i, inf);
		EXPECT_EQ(j, inf2);
		EXPECT_TRUE(hamon::isnan(k));
		EXPECT_TRUE(hamon::isnan(l));
	}
}

using FloatTestTypes = ::testing::Types<
	std::tuple<std::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>
>;

template <typename T>
class SerializationFloatTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationFloatTest, FloatTestTypes);

TYPED_TEST(SerializationFloatTest, FloatTest)
{
	using Stream   = typename std::tuple_element<0, TypeParam>::type;
	using OArchive = typename std::tuple_element<1, TypeParam>::type;
	using IArchive = typename std::tuple_element<2, TypeParam>::type;

	FloatTest<Stream, OArchive, IArchive, float>();
	FloatTest<Stream, OArchive, IArchive, double>();
#if !defined(__EMSCRIPTEN__)
	FloatTest<Stream, OArchive, IArchive, long double>();
#endif
}

}	// namespace float_test

}	// namespace hamon_serialization_test
