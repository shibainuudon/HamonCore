/**
 *	@file	unit_test_string_starts_with.cpp
 *
 *	@brief	starts_with のテスト
 *
 *	constexpr bool starts_with(basic_string_view<charT, traits> x) const noexcept;
 *	constexpr bool starts_with(charT x) const noexcept;
 *	constexpr bool starts_with(const charT* x) const;
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
namespace starts_with_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
StartsWithTest()
{
#if HAMON_CXX_STANDARD >= 20	// TODO
	using string = hamon::basic_string<CharT>;
	using string_view = std::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	// constexpr bool starts_with(basic_string_view<charT, traits> x) const noexcept;
	{
		auto p = Helper::abcd();
		string const s = p;
		static_assert(noexcept(s.starts_with(string_view{p})), "");
		static_assert(hamon::is_same<decltype(s.starts_with(string_view{p})), bool>::value, "");
		VERIFY(!(s.starts_with(string_view{Helper::abcde()})));
		VERIFY( (s.starts_with(string_view{Helper::abcd()})));
		VERIFY( (s.starts_with(string_view{Helper::abc()})));
		VERIFY( (s.starts_with(string_view{Helper::ab()})));
		VERIFY(!(s.starts_with(string_view{Helper::abb()})));
		VERIFY(!(s.starts_with(string_view{Helper::bcde()})));
	}

	// constexpr bool starts_with(charT x) const noexcept;
	{
		string const s = Helper::abcd();
		static_assert(noexcept(s.starts_with(CharT{})), "");
		static_assert(hamon::is_same<decltype(s.starts_with(CharT{})), bool>::value, "");
		VERIFY( (s.starts_with(Helper::abcd()[0])));	// 'a'
		VERIFY(!(s.starts_with(Helper::abcd()[1])));	// 'b'
		VERIFY(!(s.starts_with(Helper::abcd()[2])));	// 'c'
	}
	{
		string const s = Helper::bcde();
		VERIFY(!(s.starts_with(Helper::abcd()[0])));	// 'a'
		VERIFY( (s.starts_with(Helper::abcd()[1])));	// 'b'
		VERIFY(!(s.starts_with(Helper::abcd()[2])));	// 'c'
	}

	// constexpr bool starts_with(const charT* x) const;
	{
		auto p = Helper::abcd();
		string const s = p;
		static_assert(noexcept(s.starts_with(p)), "");
		static_assert(hamon::is_same<decltype(s.starts_with(p)), bool>::value, "");
		VERIFY(!(s.starts_with(Helper::abcde())));
		VERIFY( (s.starts_with(Helper::abcd())));
		VERIFY( (s.starts_with(Helper::abc())));
		VERIFY( (s.starts_with(Helper::ab())));
		VERIFY(!(s.starts_with(Helper::abb())));
		VERIFY(!(s.starts_with(Helper::bcde())));
	}
#endif

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, StartsWithTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(StartsWithTest<TypeParam>());
}

}	// namespace starts_with_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
