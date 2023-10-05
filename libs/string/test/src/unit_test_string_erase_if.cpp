/**
 *	@file	unit_test_string_erase_if.cpp
 *
 *	@brief	erase_if のテスト
 */

#include <hamon/string/erase_if.hpp>
#include <hamon/string/basic_string.hpp>
#include <hamon/config.hpp>
#include "constexpr_test.hpp"
#include "string_test_helper.hpp"

namespace hamon_test
{
namespace string_test
{
namespace erase_if_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
EraseIfTest()
{
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;
	{
		string s = Helper::abcde();
		auto r = hamon::erase_if(s, [](CharT c) { return c == Helper::abcde()[0]; });	// 'a'
		VERIFY(s == Helper::bcde());
		VERIFY(r == 1);
	}
	{
		string s = Helper::abbccc();
		auto r = hamon::erase_if(s, [](CharT c) { return c == Helper::abcde()[2]; });	// 'c'
		VERIFY(s == Helper::abb());
		VERIFY(r == 3);
	}
	{
		string s = Helper::abbccc();
		auto r = hamon::erase_if(s, [](CharT c) { return c == Helper::abcde()[3]; });	// 'd'
		VERIFY(s == Helper::abbccc());
		VERIFY(r == 0);
	}
	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, EraseIfTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(EraseIfTest<TypeParam>());
}

}	// namespace erase_if_test
}	// namespace string_test
}	// namespace hamon_test
