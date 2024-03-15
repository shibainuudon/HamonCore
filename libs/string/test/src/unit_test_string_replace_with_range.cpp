/**
 *	@file	unit_test_string_replace_with_range.cpp
 *
 *	@brief	replace_with_range のテスト
 *
 *	template<container-compatible-range<charT> R>
 *	constexpr basic_string& replace_with_range(const_iterator i1, const_iterator i2, R&& rg);
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
namespace replace_with_range_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
ReplaceWithRangeTest()
{
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		string s = Helper::abc();
		auto const rng = {0x41, 0x42, 0x43};
		auto& r = s.replace_with_range(s.begin(), s.end(), rng);
		VERIFY(&r == &s);
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 3);
		VERIFY(s[0] == 0x41);
		VERIFY(s[1] == 0x42);
		VERIFY(s[2] == 0x43);
	}
	{
		string s = Helper::abcde();
		CharT const arr[] = {1, 2, 3};
		auto& r = s.replace_with_range(s.begin() + 1, s.begin() + 3, arr);
		VERIFY(&r == &s);
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 6);
		VERIFY(s[0] == Helper::abcde()[0]);
		VERIFY(s[1] == 1);
		VERIFY(s[2] == 2);
		VERIFY(s[3] == 3);
		VERIFY(s[4] == Helper::abcde()[3]);
		VERIFY(s[5] == Helper::abcde()[4]);
	}
	{
		string s = Helper::abcde();
		CharT const arr[] = {1, 2, 3};
		test_input_range<CharT const> rng(arr);
		auto& r = s.replace_with_range(s.begin() + 1, s.begin() + 3, rng);
		VERIFY(&r == &s);
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 6);
		VERIFY(s[0] == Helper::abcde()[0]);
		VERIFY(s[1] == 1);
		VERIFY(s[2] == 2);
		VERIFY(s[3] == 3);
		VERIFY(s[4] == Helper::abcde()[3]);
		VERIFY(s[5] == Helper::abcde()[4]);
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, ReplaceWithRangeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(ReplaceWithRangeTest<TypeParam>());
}

}	// namespace replace_with_range_test
}	// namespace string_test
}	// namespace hamon_test
