/**
 *	@file	unit_test_string_append_range.cpp
 *
 *	@brief	append_range のテスト
 *
 *	template<container-compatible-range<charT> R>
 *	constexpr basic_string& append_range(R&& rg);
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
namespace append_range_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
AppendRangeTest()
{
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		string s = Helper::abc();
		auto const rng = {0x41, 0x42, 0x43};
		s.append_range(rng);
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 6);
		VERIFY(s[0] == Helper::abc()[0]);
		VERIFY(s[1] == Helper::abc()[1]);
		VERIFY(s[2] == Helper::abc()[2]);
		VERIFY(s[3] == 0x41);
		VERIFY(s[4] == 0x42);
		VERIFY(s[5] == 0x43);
	}

	{
		string s = Helper::ABCDE();
		CharT const arr[] = {1, 2, 3, 4};
		s.append_range(arr);
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 9);
		VERIFY(s[0] == Helper::ABCDE()[0]);
		VERIFY(s[1] == Helper::ABCDE()[1]);
		VERIFY(s[2] == Helper::ABCDE()[2]);
		VERIFY(s[3] == Helper::ABCDE()[3]);
		VERIFY(s[4] == Helper::ABCDE()[4]);
		VERIFY(s[5] == 1);
		VERIFY(s[6] == 2);
		VERIFY(s[7] == 3);
		VERIFY(s[8] == 4);
	}

	{
		string s = Helper::abc();
		CharT const arr[] = {1, 2, 3, 4};
		test_input_range<CharT const> rng(arr);
		s.append_range(rng);
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 7);
		VERIFY(s[0] == Helper::abc()[0]);
		VERIFY(s[1] == Helper::abc()[1]);
		VERIFY(s[2] == Helper::abc()[2]);
		VERIFY(s[3] == 1);
		VERIFY(s[4] == 2);
		VERIFY(s[5] == 3);
		VERIFY(s[6] == 4);
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, AppendRangeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(AppendRangeTest<TypeParam>());
}

}	// namespace append_range_test
}	// namespace string_test
}	// namespace hamon_test
