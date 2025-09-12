/**
 *	@file	unit_test_string_contains.cpp
 *
 *	@brief	contains のテスト
 *
 *	constexpr bool contains(basic_string_view<charT, traits> x) const noexcept;
 *	constexpr bool contains(charT x) const noexcept;
 *	constexpr bool contains(const charT* x) const;
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
namespace contains_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
ContainsTest()
{
#if !defined(HAMON_USE_STD_STRING) || HAMON_CXX_STANDARD >= 23
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// constexpr bool contains(basic_string_view<charT, traits> x) const noexcept;
	{
		using string_view = hamon::basic_string_view<CharT>;
		auto p = Helper::abcd();
		string const s = p;
		static_assert(noexcept(s.contains(string_view{})), "");
		static_assert(hamon::is_same<decltype(s.contains(string_view{})), bool>::value, "");
		VERIFY(!(s.contains(string_view{Helper::abcde()})));
		VERIFY( (s.contains(string_view{Helper::abcd()})));
		VERIFY( (s.contains(string_view{Helper::abc()})));
		VERIFY( (s.contains(string_view{Helper::ab()})));
		VERIFY( (s.contains(string_view{Helper::bcd()})));
		VERIFY(!(s.contains(string_view{Helper::abb()})));
	}
#if defined(HAMON_HAS_STD_STRING_VIEW)
	{
		using string_view = std::basic_string_view<CharT>;
		auto p = Helper::abcd();
		string const s = p;
		//static_assert(noexcept(s.contains(string_view{})), "");
		static_assert(hamon::is_same<decltype(s.contains(string_view{})), bool>::value, "");
		VERIFY(!(s.contains(string_view{Helper::abcde()})));
		VERIFY( (s.contains(string_view{Helper::abcd()})));
		VERIFY( (s.contains(string_view{Helper::abc()})));
		VERIFY( (s.contains(string_view{Helper::ab()})));
		VERIFY( (s.contains(string_view{Helper::bcd()})));
		VERIFY(!(s.contains(string_view{Helper::abb()})));
	}
#endif

	// constexpr bool contains(charT x) const noexcept;
	{
		string const s = Helper::abc();
		static_assert(noexcept(s.contains(CharT{})), "");
		static_assert(hamon::is_same<decltype(s.contains(CharT{})), bool>::value, "");
		VERIFY( (s.contains(Helper::abcd()[0])));	// 'a'
		VERIFY( (s.contains(Helper::abcd()[1])));	// 'b'
		VERIFY( (s.contains(Helper::abcd()[2])));	// 'c'
		VERIFY(!(s.contains(Helper::abcd()[3])));	// 'd'
	}
	{
		string const s = Helper::bcd();
		VERIFY(!(s.contains(Helper::abcd()[0])));	// 'a'
		VERIFY( (s.contains(Helper::abcd()[1])));	// 'b'
		VERIFY( (s.contains(Helper::abcd()[2])));	// 'c'
		VERIFY( (s.contains(Helper::abcd()[3])));	// 'd'
	}

	// constexpr bool contains(const charT* x) const;
	{
		auto p = Helper::abcd();
		string const s = p;
		//static_assert(noexcept(s.contains(p)), "");
		static_assert(hamon::is_same<decltype(s.contains(p)), bool>::value, "");
		VERIFY(!(s.contains(Helper::abcde())));
		VERIFY( (s.contains(Helper::abcd())));
		VERIFY( (s.contains(Helper::abc())));
		VERIFY( (s.contains(Helper::ab())));
		VERIFY( (s.contains(Helper::bcd())));
		VERIFY(!(s.contains(Helper::abb())));
	}
#endif

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, ContainsTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(ContainsTest<TypeParam>());
}

}	// namespace contains_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
