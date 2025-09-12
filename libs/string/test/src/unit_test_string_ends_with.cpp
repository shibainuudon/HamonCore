/**
 *	@file	unit_test_string_ends_with.cpp
 *
 *	@brief	ends_with のテスト
 *
 *	constexpr bool ends_with(basic_string_view<charT, traits> x) const noexcept;
 *	constexpr bool ends_with(charT x) const noexcept;
 *	constexpr bool ends_with(const charT* x) const;
 */

#include <hamon/string/basic_string.hpp>
#include <hamon/string_view.hpp>
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
namespace ends_with_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
EndsWithTest()
{
#if !defined(HAMON_USE_STD_STRING) || HAMON_CXX_STANDARD >= 20
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// constexpr bool ends_with(basic_string_view<charT, traits> x) const noexcept;
	{
		using string_view = hamon::basic_string_view<CharT>;
		auto p = Helper::abcd();
		string const s = p;
		static_assert(noexcept(s.ends_with(string_view{})), "");
		static_assert(hamon::is_same<decltype(s.ends_with(string_view{})), bool>::value, "");
		VERIFY(!(s.ends_with(string_view{Helper::abcde()})));
		VERIFY( (s.ends_with(string_view{Helper::abcd()})));
		VERIFY(!(s.ends_with(string_view{Helper::abc()})));
		VERIFY(!(s.ends_with(string_view{Helper::ab()})));
		VERIFY( (s.ends_with(string_view{Helper::bcd()})));
	}
#if defined(HAMON_HAS_STD_STRING_VIEW)
	{
		using string_view = std::basic_string_view<CharT>;
		auto p = Helper::abcd();
		string const s = p;
//		static_assert(noexcept(s.ends_with(string_view{})), "");
		static_assert(hamon::is_same<decltype(s.ends_with(string_view{})), bool>::value, "");
		VERIFY(!(s.ends_with(string_view{Helper::abcde()})));
		VERIFY( (s.ends_with(string_view{Helper::abcd()})));
		VERIFY(!(s.ends_with(string_view{Helper::abc()})));
		VERIFY(!(s.ends_with(string_view{Helper::ab()})));
		VERIFY( (s.ends_with(string_view{Helper::bcd()})));
	}
#endif

	// constexpr bool ends_with(charT x) const noexcept;
	{
		string const s = Helper::abcd();
		static_assert(noexcept(s.ends_with(CharT{})), "");
		static_assert(hamon::is_same<decltype(s.ends_with(CharT{})), bool>::value, "");
		VERIFY(!(s.ends_with(Helper::abcd()[0])));	// 'a'
		VERIFY(!(s.ends_with(Helper::abcd()[1])));	// 'b'
		VERIFY(!(s.ends_with(Helper::abcd()[2])));	// 'c'
		VERIFY( (s.ends_with(Helper::abcd()[3])));	// 'd'
	}
	{
		string const s = Helper::abc();
		VERIFY(!(s.ends_with(Helper::abcd()[0])));	// 'a'
		VERIFY(!(s.ends_with(Helper::abcd()[1])));	// 'b'
		VERIFY( (s.ends_with(Helper::abcd()[2])));	// 'c'
		VERIFY(!(s.ends_with(Helper::abcd()[3])));	// 'd'
	}

	// constexpr bool ends_with(const charT* x) const;
	{
		auto p = Helper::abcd();
		string const s = p;
		//static_assert(noexcept(s.ends_with(p)), "");
		static_assert(hamon::is_same<decltype(s.ends_with(p)), bool>::value, "");
		VERIFY(!(s.ends_with(Helper::abcde())));
		VERIFY( (s.ends_with(Helper::abcd())));
		VERIFY(!(s.ends_with(Helper::abc())));
		VERIFY(!(s.ends_with(Helper::ab())));
		VERIFY( (s.ends_with(Helper::bcd())));
	}
#endif

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, EndsWithTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(EndsWithTest<TypeParam>());
}

}	// namespace ends_with_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
