/**
 *	@file	unit_test_serialization_string.cpp
 *
 *	@brief	hamon::stringのシリアライズのテスト
 */

#include <hamon/serialization/types/string.hpp>
#include <hamon/sstream/stringstream.hpp>
#include <hamon/sstream/wstringstream.hpp>
#include <hamon/string.hpp>
#include <hamon/tuple.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "serialization_test_archives.hpp"
#include "get_random_value.hpp"

#if !defined(HAMON_NO_STD)
#include <string>
#endif

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

template <typename Stream, typename OArchive, typename IArchive,
	template <typename...> class BasicString
>
void StringTest()
{
	StringTestSub<Stream, OArchive, IArchive>(BasicString<char>{});
	StringTestSub<Stream, OArchive, IArchive>(BasicString<char>("Hello World"));
	StringTestSub<Stream, OArchive, IArchive>(BasicString<char>(
		"0123 !\"#$%&'()-=^~|\\[]{}`@;:+*/?<>,._abcde \r\n\t\"\\\v\b"));

	StringTestSub<Stream, OArchive, IArchive>(BasicString<wchar_t>{});
	StringTestSub<Stream, OArchive, IArchive>(BasicString<wchar_t>(L"Hello World"));
	StringTestSub<Stream, OArchive, IArchive>(BasicString<wchar_t>(
		L"0123 !\"#$%&'()-=^~|\\[]{}`@;:+*/?<>,._abcde \r\n\t\"\\\v\b漢字\u3042\u3044\u3046"));

#if defined(HAMON_HAS_CXX20_CHAR8_T)
	StringTestSub<Stream, OArchive, IArchive>(BasicString<char8_t>{});
	StringTestSub<Stream, OArchive, IArchive>(BasicString<char8_t>(u8"Hello World"));
	StringTestSub<Stream, OArchive, IArchive>(BasicString<char8_t>(
		u8"0123 !\"#$%&'()-=^~|\\[]{}`@;:+*/?<>,._abcde \r\n\t\"\\\v\b漢字\u3042\u3044\u3046"));
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	StringTestSub<Stream, OArchive, IArchive>(BasicString<char16_t>{});
	StringTestSub<Stream, OArchive, IArchive>(BasicString<char16_t>(u"Hello World"));
	StringTestSub<Stream, OArchive, IArchive>(BasicString<char16_t>(
		u"0123 !\"#$%&'()-=^~|\\[]{}`@;:+*/?<>,._abcde \r\n\t\"\\\v\b漢字\u3042\u3044\u3046"));
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	StringTestSub<Stream, OArchive, IArchive>(BasicString<char32_t>{});
	StringTestSub<Stream, OArchive, IArchive>(BasicString<char32_t>(U"Hello World"));
	StringTestSub<Stream, OArchive, IArchive>(BasicString<char32_t>(
		U"0123 !\"#$%&'()-=^~|\\[]{}`@;:+*/?<>,._abcde \r\n\t\"\\\v\b漢字\u3042\u3044\u3046"));
#endif
}

using StringTestTypes = ::testing::Types<
	hamon::tuple<hamon::stringstream,  hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	hamon::tuple<hamon::wstringstream, hamon::serialization::text_oarchive,   hamon::serialization::text_iarchive>,
	hamon::tuple<hamon::stringstream,  hamon::serialization::binary_oarchive, hamon::serialization::binary_iarchive>,
	hamon::tuple<hamon::stringstream,  hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	hamon::tuple<hamon::wstringstream, hamon::serialization::json_oarchive,   hamon::serialization::json_iarchive>,
	hamon::tuple<hamon::stringstream,  hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>,
	hamon::tuple<hamon::wstringstream, hamon::serialization::xml_oarchive,    hamon::serialization::xml_iarchive>
>;

template <typename T>
class SerializationStringTest : public ::testing::Test {};

TYPED_TEST_SUITE(SerializationStringTest, StringTestTypes);

TYPED_TEST(SerializationStringTest, StringTest)
{
	using Stream   = typename hamon::tuple_element<0, TypeParam>::type;
	using OArchive = typename hamon::tuple_element<1, TypeParam>::type;
	using IArchive = typename hamon::tuple_element<2, TypeParam>::type;

	StringTest<Stream, OArchive, IArchive, hamon::basic_string>();
#if !defined(HAMON_NO_STD)
//	StringTest<Stream, OArchive, IArchive, std::basic_string>();
#endif
}

}	// namespace string_test

}	// namespace hamon_serialization_test
