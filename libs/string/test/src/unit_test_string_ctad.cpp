/**
 *	@file	unit_test_string_ctad.cpp
 *
 *	@brief	推論補助 のテスト
 */

#include <hamon/string/basic_string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/array.hpp>
#include <hamon/config.hpp>
#include "constexpr_test.hpp"
#include "string_test_helper.hpp"

namespace hamon_test
{
namespace string_test
{
namespace ctad_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
CtadTest()
{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	using string = hamon::basic_string<CharT>;
	using Traits = typename string::traits_type;
	using string_view = hamon::basic_string_view<CharT, Traits>;
	using Helper = StringTestHelper<CharT>;

	{
		hamon::basic_string s = Helper::abc();
		static_assert(hamon::is_same<decltype(s), string>::value, "");
		VERIFY(GeneralCheck(s));
		VERIFY(s == Helper::abc());
	}
	{
		auto const c = Helper::abc()[1];
		hamon::basic_string s(3, c);
		static_assert(hamon::is_same<decltype(s), string>::value, "");
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 3);
		VERIFY(s[0] == c);
		VERIFY(s[1] == c);
		VERIFY(s[2] == c);
	}
	{
		auto const p = Helper::abcde();
		hamon::basic_string s {p[2], p[1], p[3], p[0]};
		static_assert(hamon::is_same<decltype(s), string>::value, "");
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 4);
		VERIFY(s[0] == p[2]);
		VERIFY(s[1] == p[1]);
		VERIFY(s[2] == p[3]);
		VERIFY(s[3] == p[0]);
	}
	{
		auto const p = Helper::abcde();
		hamon::basic_string s(p + 1, p + 4);
		static_assert(hamon::is_same<decltype(s), string>::value, "");
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 3);
		VERIFY(s[0] == p[1]);
		VERIFY(s[1] == p[2]);
		VERIFY(s[2] == p[3]);
	}
	{
		hamon::array<CharT, 5> const arr {1, 2, 3, 4, 5};
		hamon::basic_string s(arr.begin(), arr.end());
		static_assert(hamon::is_same<decltype(s), string>::value, "");
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 5);
		VERIFY(s[0] == 1);
		VERIFY(s[1] == 2);
		VERIFY(s[2] == 3);
		VERIFY(s[3] == 4);
		VERIFY(s[4] == 5);
	}
	{
		auto const p = Helper::abcde();
		string_view const sv{p};
		hamon::basic_string s(sv);
		static_assert(hamon::is_same<decltype(s), string>::value, "");
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 5);
		VERIFY(s[0] == p[0]);
		VERIFY(s[1] == p[1]);
		VERIFY(s[2] == p[2]);
		VERIFY(s[3] == p[3]);
		VERIFY(s[4] == p[4]);
	}
	{
		auto const p = Helper::abcde();
		string_view const sv{p};
		hamon::basic_string s(sv, 1, 3);
		static_assert(hamon::is_same<decltype(s), string>::value, "");
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 3);
		VERIFY(s[0] == p[1]);
		VERIFY(s[1] == p[2]);
		VERIFY(s[2] == p[3]);
	}
	{
		CharT const rng[] = {1, 2, 3, 4};
		hamon::basic_string s(hamon::from_range, rng);
		static_assert(hamon::is_same<decltype(s), string>::value, "");
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 4);
		VERIFY(s[0] == 1);
		VERIFY(s[1] == 2);
		VERIFY(s[2] == 3);
		VERIFY(s[3] == 4);
	}
	{
		hamon::array<CharT, 5> const rng {1, 2, 3, 4, 5};
		hamon::basic_string s(hamon::from_range, rng);
		static_assert(hamon::is_same<decltype(s), string>::value, "");
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 5);
		VERIFY(s[0] == 1);
		VERIFY(s[1] == 2);
		VERIFY(s[2] == 3);
		VERIFY(s[3] == 4);
		VERIFY(s[4] == 5);
	}
#endif

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, CtadTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(CtadTest<TypeParam>());
}

}	// namespace ctad_test
}	// namespace string_test
}	// namespace hamon_test
