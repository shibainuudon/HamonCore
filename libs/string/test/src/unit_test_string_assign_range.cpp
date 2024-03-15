/**
 *	@file	unit_test_string_assign_range.cpp
 *
 *	@brief	assign_range のテスト
 *
 *	template<container-compatible-range<charT> R>
 *	constexpr basic_string& assign_range(R&& rg);
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
namespace assign_range_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
AssignRangeTest()
{
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		string s = Helper::abc();
		auto const rng = {0x41, 0x42, 0x43};
		s.assign_range(rng);
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 3);
		VERIFY(s[0] == 0x41);
		VERIFY(s[1] == 0x42);
		VERIFY(s[2] == 0x43);
	}

	{
		string s = Helper::ABCDE();
		CharT const arr[] = {1, 2, 3, 4};
		s.assign_range(arr);
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 4);
		VERIFY(s[0] == 1);
		VERIFY(s[1] == 2);
		VERIFY(s[2] == 3);
		VERIFY(s[3] == 4);
	}

	{
		string s = Helper::ABCDE();
		CharT const arr[] = {10,20,30};
		test_input_range<CharT const> rng(arr);
		s.assign_range(rng);
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 3);
		VERIFY(s[0] == 10);
		VERIFY(s[1] == 20);
		VERIFY(s[2] == 30);
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, AssignRangeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(AssignRangeTest<TypeParam>());
}

}	// namespace assign_range_test
}	// namespace string_test
}	// namespace hamon_test
