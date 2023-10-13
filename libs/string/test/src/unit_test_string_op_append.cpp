/**
 *	@file	unit_test_string_op_append.cpp
 *
 *	@brief	operator+= のテスト
 *
 *	constexpr basic_string& operator+=(const basic_string& str);
 *	template<class T>
 *	constexpr basic_string& operator+=(const T& t);
 *	constexpr basic_string& operator+=(const charT* s);
 *	constexpr basic_string& operator+=(charT c);
 *	constexpr basic_string& operator+=(initializer_list<charT>);
 */

#include <hamon/string/basic_string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <initializer_list>
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
namespace op_append_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
OpAppendTest()
{
	using string = hamon::basic_string<CharT>;
	using Traits = typename string::traits_type;
	using string_view = hamon::basic_string_view<CharT, Traits>;
	using Helper = StringTestHelper<CharT>;

	// constexpr basic_string& operator+=(const basic_string& str);
	{
		auto p1 = Helper::abb();
		auto p2 = Helper::bcde();
		string const s1 = p1;
		string s2 = p2;
		static_assert(!noexcept(s2 += s1), "");
		static_assert(hamon::is_same<decltype(s2 += s1), string&>::value, "");
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 4);
		VERIFY(s2[0] == p2[0]);
		VERIFY(s2[1] == p2[1]);
		VERIFY(s2[2] == p2[2]);
		VERIFY(s2[3] == p2[3]);
		{
			auto& r = (s2 += s1);
			VERIFY(&r == &s2);
			VERIFY(GeneralCheck(s2));
			VERIFY(s2.size() == 7);
			VERIFY(s2[0] == p2[0]);
			VERIFY(s2[1] == p2[1]);
			VERIFY(s2[2] == p2[2]);
			VERIFY(s2[3] == p2[3]);
			VERIFY(s2[4] == p1[0]);
			VERIFY(s2[5] == p1[1]);
			VERIFY(s2[6] == p1[2]);
		}
		{
			auto& r = (s2 += s2);
			VERIFY(&r == &s2);
			VERIFY(GeneralCheck(s2));
			VERIFY(s2.size() == 14);
			VERIFY(s2[ 0] == p2[0]);
			VERIFY(s2[ 1] == p2[1]);
			VERIFY(s2[ 2] == p2[2]);
			VERIFY(s2[ 3] == p2[3]);
			VERIFY(s2[ 4] == p1[0]);
			VERIFY(s2[ 5] == p1[1]);
			VERIFY(s2[ 6] == p1[2]);
			VERIFY(s2[ 7] == p2[0]);
			VERIFY(s2[ 8] == p2[1]);
			VERIFY(s2[ 9] == p2[2]);
			VERIFY(s2[10] == p2[3]);
			VERIFY(s2[11] == p1[0]);
			VERIFY(s2[12] == p1[1]);
			VERIFY(s2[13] == p1[2]);
		}
	}

	// template<class T>
	// constexpr basic_string& operator+=(const T& t);
	{
		auto p1 = Helper::abb();
		auto p2 = Helper::bcde();
		string_view const s1 = p1;
		string s2 = p2;
		static_assert(!noexcept(s2 += s1), "");
		static_assert(hamon::is_same<decltype(s2 += s1), string&>::value, "");
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 4);
		VERIFY(s2[0] == p2[0]);
		VERIFY(s2[1] == p2[1]);
		VERIFY(s2[2] == p2[2]);
		VERIFY(s2[3] == p2[3]);
		auto& r = (s2 += s1);
		VERIFY(&r == &s2);
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 7);
		VERIFY(s2[0] == p2[0]);
		VERIFY(s2[1] == p2[1]);
		VERIFY(s2[2] == p2[2]);
		VERIFY(s2[3] == p2[3]);
		VERIFY(s2[4] == p1[0]);
		VERIFY(s2[5] == p1[1]);
		VERIFY(s2[6] == p1[2]);
	}

	// constexpr basic_string& operator+=(const charT* s);
	{
		auto p1 = Helper::abcde();
		auto p2 = Helper::abb();
		string s = p2;
		static_assert(!noexcept(s += p1), "");
		static_assert(hamon::is_same<decltype(s += p1), string&>::value, "");
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 3);
		VERIFY(s[0] == p2[0]);
		VERIFY(s[1] == p2[1]);
		VERIFY(s[2] == p2[2]);
		auto& r = (s += p1);
		VERIFY(&r == &s);
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 8);
		VERIFY(s[0] == p2[0]);
		VERIFY(s[1] == p2[1]);
		VERIFY(s[2] == p2[2]);
		VERIFY(s[3] == p1[0]);
		VERIFY(s[4] == p1[1]);
		VERIFY(s[5] == p1[2]);
		VERIFY(s[6] == p1[3]);
		VERIFY(s[7] == p1[4]);
	}

	// constexpr basic_string& operator+=(charT c);
	{
		auto p = Helper::abcde();
		string s = p;
		static_assert(!noexcept(s += CharT{}), "");
		static_assert(hamon::is_same<decltype(s += CharT{}), string&>::value, "");
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 5);
		VERIFY(s[0] == p[0]);
		VERIFY(s[1] == p[1]);
		VERIFY(s[2] == p[2]);
		VERIFY(s[3] == p[3]);
		VERIFY(s[4] == p[4]);
		auto& r = (s += p[1]);
		VERIFY(&r == &s);
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 6);
		VERIFY(s[0] == p[0]);
		VERIFY(s[1] == p[1]);
		VERIFY(s[2] == p[2]);
		VERIFY(s[3] == p[3]);
		VERIFY(s[4] == p[4]);
		VERIFY(s[5] == p[1]);
	}

	// constexpr basic_string& operator+=(initializer_list<charT>);
	{
		auto p = Helper::abcde();
		string s;
		static_assert(!noexcept(s += std::initializer_list<CharT>{}), "");
		static_assert(hamon::is_same<decltype(s += std::initializer_list<CharT>{}), string&>::value, "");
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 0);
		auto& r = (s += {p[0], p[3], p[4], p[1], p[1]});
		VERIFY(&r == &s);
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 5);
		VERIFY(s[0] == p[0]);
		VERIFY(s[1] == p[3]);
		VERIFY(s[2] == p[4]);
		VERIFY(s[3] == p[1]);
		VERIFY(s[4] == p[1]);
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, OpAppendTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(OpAppendTest<TypeParam>());
}

}	// namespace op_append_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
