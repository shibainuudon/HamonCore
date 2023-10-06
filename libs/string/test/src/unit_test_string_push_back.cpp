/**
 *	@file	unit_test_string_push_back.cpp
 *
 *	@brief	push_back のテスト
 *
 *	constexpr void push_back(charT c);
 */

#include <hamon/string/basic_string.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include "constexpr_test.hpp"
#include "string_test_helper.hpp"

namespace hamon_test
{
namespace string_test
{
namespace push_back_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
PushBackTest()
{
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// constexpr void push_back(charT c);
	{
		auto p = Helper::abcde();
		string s;
		static_assert(!noexcept(s.push_back(CharT{})), "");
		static_assert(hamon::is_same<decltype(s.push_back(CharT{})), void>::value, "");
		VERIFY(s.size() == 0);
		s.push_back(p[1]);
		VERIFY(s.size() == 1);
		VERIFY(s[0] == p[1]);
		s.push_back(p[3]);
		VERIFY(s.size() == 2);
		VERIFY(s[0] == p[1]);
		VERIFY(s[1] == p[3]);
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, PushBackTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(PushBackTest<TypeParam>());
}

}	// namespace push_back_test
}	// namespace string_test
}	// namespace hamon_test
