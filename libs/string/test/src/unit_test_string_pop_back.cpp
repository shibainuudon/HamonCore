/**
 *	@file	unit_test_string_pop_back.cpp
 *
 *	@brief	pop_back のテスト
 *
 *	constexpr void pop_back();
 */

#include <hamon/string/basic_string.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include "constexpr_test.hpp"
#include "string_test_helper.hpp"

HAMON_WARNING_PUSH()
#if defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION >= 120000)
HAMON_WARNING_DISABLE_GCC("-Wstringop-overread")
#endif

namespace hamon_test
{
namespace string_test
{
namespace pop_back_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
PopBackTest()
{
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// constexpr void pop_back();
	{
		auto p = Helper::abcde();
		string s = p;
//		static_assert(!noexcept(s.pop_back()), "");
		static_assert(hamon::is_same<decltype(s.pop_back()), void>::value, "");
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 5);
		VERIFY(s[0] == p[0]);
		VERIFY(s[1] == p[1]);
		VERIFY(s[2] == p[2]);
		VERIFY(s[3] == p[3]);
		VERIFY(s[4] == p[4]);

		s.pop_back();
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 4);
		VERIFY(s[0] == p[0]);
		VERIFY(s[1] == p[1]);
		VERIFY(s[2] == p[2]);
		VERIFY(s[3] == p[3]);

		s.pop_back();
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 3);
		VERIFY(s[0] == p[0]);
		VERIFY(s[1] == p[1]);
		VERIFY(s[2] == p[2]);
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, PopBackTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(PopBackTest<TypeParam>());
}

}	// namespace pop_back_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
