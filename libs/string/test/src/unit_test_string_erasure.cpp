/**
 *	@file	unit_test_string_erasure.cpp
 *
 *	@brief	erase, erase_if のテスト
 * 
 *	template<class charT, class traits, class Allocator, class U>
 *	constexpr typename basic_string<charT, traits, Allocator>::size_type
 *	erase(basic_string<charT, traits, Allocator>& c, const U& value);
 *
 *	template<class charT, class traits, class Allocator, class Predicate>
 *	constexpr typename basic_string<charT, traits, Allocator>::size_type
 *	erase_if(basic_string<charT, traits, Allocator>& c, Predicate pred);
 */

#include <hamon/string/erase.hpp>
#include <hamon/string/erase_if.hpp>
#include <hamon/string/basic_string.hpp>
#include <hamon/config.hpp>
#include "constexpr_test.hpp"
#include "string_test_helper.hpp"

namespace hamon_test
{
namespace string_test
{
namespace erasure_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
EraseTest()
{
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// template<class charT, class traits, class Allocator, class U>
	// constexpr typename basic_string<charT, traits, Allocator>::size_type
	// erase(basic_string<charT, traits, Allocator>& c, const U& value);
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

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
EraseIfTest()
{
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// template<class charT, class traits, class Allocator, class Predicate>
	// constexpr typename basic_string<charT, traits, Allocator>::size_type
	// erase_if(basic_string<charT, traits, Allocator>& c, Predicate pred);
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

TYPED_TEST(StringTest, ErasureTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(EraseTest<TypeParam>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(EraseIfTest<TypeParam>());
}

}	// namespace erasure_test
}	// namespace string_test
}	// namespace hamon_test
