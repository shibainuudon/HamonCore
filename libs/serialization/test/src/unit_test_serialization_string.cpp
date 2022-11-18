/**
 *	@file	unit_test_serialization_string.cpp
 *
 *	@brief	std::stringのシリアライズのテスト
 */

#include <hamon/serialization/string.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <sstream>
#include <string>
#include "serialization_test_archives.hpp"
#include "get_random_value.hpp"

namespace hamon_serialization_test
{

namespace string_test
{

template <typename Stream, typename OArchive, typename IArchive, typename TString>
void StringTestSub(TString const& s)
{
	Stream str;
	{
		OArchive oa(str);
		oa << s;
	}
	{
		TString a;

		IArchive ia(str);

		ia >> a;
		EXPECT_EQ(s, a);
	}
}

template <typename Stream, typename OArchive, typename IArchive>
void StringTest()
{
	StringTestSub<Stream, OArchive, IArchive>(std::string{});
	StringTestSub<Stream, OArchive, IArchive>(std::string("Hello World"));
	StringTestSub<Stream, OArchive, IArchive>(std::string(
		"0123 !\"#$%&'()-=^~|\\[]{}`@;:+*/?<>,._abcde \r\n\t\"\\\v\b"));

	StringTestSub<Stream, OArchive, IArchive>(std::wstring{});
	StringTestSub<Stream, OArchive, IArchive>(std::wstring(L"Hello World"));
	StringTestSub<Stream, OArchive, IArchive>(std::wstring(
		L"0123 !\"#$%&'()-=^~|\\[]{}`@;:+*/?<>,._abcde \r\n\t\"\\\v\b漢字\u3042\u3044\u3046"));

#if defined(HAMON_HAS_CXX20_CHAR8_T)
	StringTestSub<Stream, OArchive, IArchive>(std::u8string{});
	StringTestSub<Stream, OArchive, IArchive>(std::u8string(u8"Hello World"));
	StringTestSub<Stream, OArchive, IArchive>(std::u8string(
		u8"0123 !\"#$%&'()-=^~|\\[]{}`@;:+*/?<>,._abcde \r\n\t\"\\\v\b漢字\u3042\u3044\u3046"));
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	StringTestSub<Stream, OArchive, IArchive>(std::u16string{});
	StringTestSub<Stream, OArchive, IArchive>(std::u16string(u"Hello World"));
	StringTestSub<Stream, OArchive, IArchive>(std::u16string(
		u"0123 !\"#$%&'()-=^~|\\[]{}`@;:+*/?<>,._abcde \r\n\t\"\\\v\b漢字\u3042\u3044\u3046"));
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	StringTestSub<Stream, OArchive, IArchive>(std::u32string{});
	StringTestSub<Stream, OArchive, IArchive>(std::u32string(U"Hello World"));
	StringTestSub<Stream, OArchive, IArchive>(std::u32string(
		U"0123 !\"#$%&'()-=^~|\\[]{}`@;:+*/?<>,._abcde \r\n\t\"\\\v\b漢字\u3042\u3044\u3046"));
#endif
}

using StringTestTypes = ::testing::Types<
	std::tuple<std::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	std::tuple<std::stringstream,  hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>,
	std::tuple<std::wstringstream, hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>
>;

template <typename T>
class SerializationStringTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationStringTest, StringTestTypes);

TYPED_TEST(SerializationStringTest, StringTest)
{
	using Stream   = typename std::tuple_element<0, TypeParam>::type;
	using OArchive = typename std::tuple_element<1, TypeParam>::type;
	using IArchive = typename std::tuple_element<2, TypeParam>::type;

	StringTest<Stream, OArchive, IArchive>();
}

}	// namespace string_test

}	// namespace hamon_serialization_test
