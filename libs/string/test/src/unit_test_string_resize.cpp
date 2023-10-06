/**
 *	@file	unit_test_string_resize.cpp
 *
 *	@brief	resize のテスト
 *
 *	constexpr void resize(size_type n, charT c);
 *	constexpr void resize(size_type n);
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
namespace resize_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
ResizeTest()
{
	using string = hamon::basic_string<CharT>;
	using SizeType = typename string::size_type;
	using Helper = StringTestHelper<CharT>;

	{
		string s = Helper::abcde();
		static_assert(!noexcept(s.resize(SizeType{})), "");
		static_assert(!noexcept(s.resize(SizeType{}, CharT{})), "");
		static_assert(hamon::is_same<decltype(s.resize(SizeType{})), void>::value, "");
		static_assert(hamon::is_same<decltype(s.resize(SizeType{}, CharT{})), void>::value, "");

		VERIFY(s.size() == 5);

		s.resize(4);
		VERIFY(s.size() == 4);
		VERIFY(s[0] == Helper::abcde()[0]);
		VERIFY(s[1] == Helper::abcde()[1]);
		VERIFY(s[2] == Helper::abcde()[2]);
		VERIFY(s[3] == Helper::abcde()[3]);

		s.resize(3, Helper::abcde()[2]);
		VERIFY(s.size() == 3);
		VERIFY(s[0] == Helper::abcde()[0]);
		VERIFY(s[1] == Helper::abcde()[1]);
		VERIFY(s[2] == Helper::abcde()[2]);

		s.resize(4);
		VERIFY(s.size() == 4);
		VERIFY(s[0] == Helper::abcde()[0]);
		VERIFY(s[1] == Helper::abcde()[1]);
		VERIFY(s[2] == Helper::abcde()[2]);
		VERIFY(s[3] == CharT{});

		s.resize(6, Helper::abcde()[1]);
		VERIFY(s.size() == 6);
		VERIFY(s[0] == Helper::abcde()[0]);
		VERIFY(s[1] == Helper::abcde()[1]);
		VERIFY(s[2] == Helper::abcde()[2]);
		VERIFY(s[3] == CharT{});
		VERIFY(s[4] == Helper::abcde()[1]);
		VERIFY(s[5] == Helper::abcde()[1]);
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, ResizeTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(ResizeTest<TypeParam>());
}

}	// namespace resize_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
