﻿/**
 *	@file	unit_test_string_insert_range.cpp
 *
 *	@brief	insert_range のテスト
 *
 *	template<container-compatible-range<charT> R>
 *	constexpr iterator insert_range(const_iterator p, R&& rg);
 */

#include <hamon/string/basic_string.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include "constexpr_test.hpp"
#include "string_test_helper.hpp"
#include "ranges_test.hpp"

namespace hamon_test
{
namespace string_test
{
namespace insert_range_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
InsertRangeTest()
{
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		string s = Helper::abc();
		auto const rng = {0x41, 0x42, 0x43};
		auto it = s.insert_range(s.begin(), rng);
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 6);
		VERIFY(s[0] == 0x41);
		VERIFY(s[1] == 0x42);
		VERIFY(s[2] == 0x43);
		VERIFY(s[3] == Helper::abc()[0]);
		VERIFY(s[4] == Helper::abc()[1]);
		VERIFY(s[5] == Helper::abc()[2]);
		VERIFY(it == s.begin());
	}
	{
		string s = Helper::abc();
		auto const rng = {0x41, 0x42, 0x43};
		auto it = s.insert_range(s.end(), rng);
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 6);
		VERIFY(s[0] == Helper::abc()[0]);
		VERIFY(s[1] == Helper::abc()[1]);
		VERIFY(s[2] == Helper::abc()[2]);
		VERIFY(s[3] == 0x41);
		VERIFY(s[4] == 0x42);
		VERIFY(s[5] == 0x43);
		VERIFY(it == s.begin() + 3);
	}
	{
		string s = Helper::ABCDE();
		CharT const arr[] = {1, 2, 3, 4};
		auto it = s.insert_range(s.begin() + 2, arr);
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 9);
		VERIFY(s[0] == Helper::ABCDE()[0]);
		VERIFY(s[1] == Helper::ABCDE()[1]);
		VERIFY(s[2] == 1);
		VERIFY(s[3] == 2);
		VERIFY(s[4] == 3);
		VERIFY(s[5] == 4);
		VERIFY(s[6] == Helper::ABCDE()[2]);
		VERIFY(s[7] == Helper::ABCDE()[3]);
		VERIFY(s[8] == Helper::ABCDE()[4]);
		VERIFY(it == s.begin() + 2);
	}
	{
		string s = Helper::ABCDE();
		CharT const arr[] = {1, 2, 3, 4};
		test_input_range<CharT const> rng(arr);
		auto it = s.insert_range(s.begin() + 2, rng);
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 9);
		VERIFY(s[0] == Helper::ABCDE()[0]);
		VERIFY(s[1] == Helper::ABCDE()[1]);
		VERIFY(s[2] == 1);
		VERIFY(s[3] == 2);
		VERIFY(s[4] == 3);
		VERIFY(s[5] == 4);
		VERIFY(s[6] == Helper::ABCDE()[2]);
		VERIFY(s[7] == Helper::ABCDE()[3]);
		VERIFY(s[8] == Helper::ABCDE()[4]);
		VERIFY(it == s.begin() + 2);
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, InsertRangeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(InsertRangeTest<TypeParam>());
}

}	// namespace insert_range_test
}	// namespace string_test
}	// namespace hamon_test
