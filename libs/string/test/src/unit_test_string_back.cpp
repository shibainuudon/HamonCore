/**
 *	@file	unit_test_string_back.cpp
 *
 *	@brief	back のテスト
 *
 *	constexpr const charT& back() const;
 *	constexpr charT&       back();
 */

#include <hamon/string/basic_string.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include "constexpr_test.hpp"
#include "string_test_helper.hpp"

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_GCC("-Wmaybe-uninitialized")

namespace hamon_test
{
namespace string_test
{
namespace back_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
BackTest()
{
	using string = hamon::basic_string<CharT>;
	using Reference = typename string::reference;
	using ConstReference = typename string::const_reference;
	using Helper = StringTestHelper<CharT>;

	{
		auto p = Helper::abcde();
		string const s = p;
		static_assert(noexcept(s.back()), "");
		static_assert(hamon::is_same<decltype(s.back()), ConstReference>::value, "");
		VERIFY(s.back() == p[4]);
		VERIFY(s.back() == s[4]);
	}
	{
		auto p = Helper::abcde();
		string s = p;
		static_assert(noexcept(s.back()), "");
		static_assert(hamon::is_same<decltype(s.back()), Reference>::value, "");
		VERIFY(s.back() == p[4]);
		VERIFY(s.back() == s[4]);
		s.back() = CharT{};
		VERIFY(s.back() != p[4]);
		VERIFY(s.back() == CharT{});
		VERIFY(s.back() == s[4]);
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, BackTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(BackTest<TypeParam>());
}

}	// namespace back_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
