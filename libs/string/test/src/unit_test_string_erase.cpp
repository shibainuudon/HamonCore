/**
 *	@file	unit_test_string_erase.cpp
 *
 *	@brief	erase のテスト
 */

#include <hamon/string/erase.hpp>
#include <hamon/string/basic_string.hpp>
#include <hamon/config.hpp>
#include "constexpr_test.hpp"
#include "string_test_helper.hpp"

namespace hamon_test
{
namespace string_test
{
namespace erase_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
EraseTest()
{
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;
	{
		string s = Helper::abcde();
		CharT const c = Helper::abcde()[0];	// 'a'
		auto r = hamon::erase(s, c);
		VERIFY(s == Helper::bcde());
		VERIFY(r == 1);
	}
	{
		string s = Helper::abbccc();
		CharT const c = Helper::abcde()[2];	// 'c'
		auto r = hamon::erase(s, c);
		VERIFY(s == Helper::abb());
		VERIFY(r == 3);
	}
	{
		string s = Helper::abbccc();
		CharT const c = Helper::abcde()[3];	// 'd'
		auto r = hamon::erase(s, c);
		VERIFY(s == Helper::abbccc());
		VERIFY(r == 0);
	}
	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, EraseTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(EraseTest<TypeParam>());
}

}	// namespace erase_test
}	// namespace string_test
}	// namespace hamon_test
