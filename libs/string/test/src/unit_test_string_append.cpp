/**
 *	@file	unit_test_string_append.cpp
 *
 *	@brief	append のテスト
 *
 *	constexpr basic_string& append(const basic_string& str);
 *	constexpr basic_string& append(const basic_string& str, size_type pos, size_type n = npos);
 *	template<class T>
 *	constexpr basic_string& append(const T& t);
 *	template<class T>
 *	constexpr basic_string& append(const T& t, size_type pos, size_type n = npos);
 *	constexpr basic_string& append(const charT* s, size_type n);
 *	constexpr basic_string& append(const charT* s);
 *	constexpr basic_string& append(size_type n, charT c);
 *	template<class InputIterator>
 *	constexpr basic_string& append(InputIterator first, InputIterator last);
 *	constexpr basic_string& append(initializer_list<charT>);
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
namespace append_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
AppendTest()
{
	using string = hamon::basic_string<CharT>;
	using SizeType = typename string::size_type;
	using Helper = StringTestHelper<CharT>;

	// constexpr basic_string& append(const basic_string& str);
	{
		auto p1 = Helper::abb();
		auto p2 = Helper::bcde();
		string const s1 = p1;
		string s2 = p2;
		static_assert(!noexcept(s2.append(s1)), "");
		static_assert(hamon::is_same<decltype(s2.append(s1)), string&>::value, "");
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 4);
		VERIFY(s2[0] == p2[0]);
		VERIFY(s2[1] == p2[1]);
		VERIFY(s2[2] == p2[2]);
		VERIFY(s2[3] == p2[3]);
		{
			auto& r = s2.append(s1);
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
			auto& r = s2.append(s2);
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

	// constexpr basic_string& append(const basic_string& str, size_type pos, size_type n = npos);
	{
		auto p1 = Helper::abb();
		auto p2 = Helper::bcde();
		string const s1 = p1;
		string s2 = p2;
		static_assert(!noexcept(s2.append(s1, SizeType{})), "");
		static_assert(!noexcept(s2.append(s1, SizeType{}, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s2.append(s1, SizeType{})), string&>::value, "");
		static_assert(hamon::is_same<decltype(s2.append(s1, SizeType{}, SizeType{})), string&>::value, "");
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 4);
		VERIFY(s2[0] == p2[0]);
		VERIFY(s2[1] == p2[1]);
		VERIFY(s2[2] == p2[2]);
		VERIFY(s2[3] == p2[3]);
		{
			auto& r = s2.append(s1, 1);
			VERIFY(&r == &s2);
			VERIFY(GeneralCheck(s2));
			VERIFY(s2.size() == 6);
			VERIFY(s2[0] == p2[0]);
			VERIFY(s2[1] == p2[1]);
			VERIFY(s2[2] == p2[2]);
			VERIFY(s2[3] == p2[3]);
			VERIFY(s2[4] == p1[1]);
			VERIFY(s2[5] == p1[2]);
		}
		{
			auto& r = s2.append(s2, 2, 2);
			VERIFY(&r == &s2);
			VERIFY(GeneralCheck(s2));
			VERIFY(s2.size() == 8);
			VERIFY(s2[0] == p2[0]);
			VERIFY(s2[1] == p2[1]);
			VERIFY(s2[2] == p2[2]);
			VERIFY(s2[3] == p2[3]);
			VERIFY(s2[4] == p1[1]);
			VERIFY(s2[5] == p1[2]);
			VERIFY(s2[6] == p2[2]);
			VERIFY(s2[7] == p2[3]);
		}
	}

	// template<class T>
	// constexpr basic_string& append(const T& t);
	{
		using string_view = hamon::basic_string_view<CharT>;
		auto p1 = Helper::abb();
		auto p2 = Helper::bcde();
		string_view const s1 = p1;
		string s2 = p2;
		static_assert(!noexcept(s2.append(s1)), "");
		static_assert(hamon::is_same<decltype(s2.append(s1)), string&>::value, "");
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 4);
		VERIFY(s2[0] == p2[0]);
		VERIFY(s2[1] == p2[1]);
		VERIFY(s2[2] == p2[2]);
		VERIFY(s2[3] == p2[3]);
		{
			auto& r = s2.append(s1);
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
			auto& r = s2.append(string_view{s2});
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
#if defined(HAMON_HAS_STD_STRING_VIEW)
	{
		using string_view = std::basic_string_view<CharT>;
		auto p1 = Helper::abb();
		auto p2 = Helper::bcde();
		string_view const s1 = p1;
		string s2 = p2;
		static_assert(!noexcept(s2.append(s1)), "");
		static_assert(hamon::is_same<decltype(s2.append(s1)), string&>::value, "");
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 4);
		VERIFY(s2[0] == p2[0]);
		VERIFY(s2[1] == p2[1]);
		VERIFY(s2[2] == p2[2]);
		VERIFY(s2[3] == p2[3]);
		{
			auto& r = s2.append(s1);
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
			auto& r = s2.append(string_view{s2});
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
#endif

	// template<class T>
	// constexpr basic_string& append(const T& t, size_type pos, size_type n = npos);
	{
		using string_view = hamon::basic_string_view<CharT>;
		auto p1 = Helper::abb();
		auto p2 = Helper::bcde();
		string_view const s1 = p1;
		string s2 = p2;
		static_assert(!noexcept(s2.append(s1, SizeType{})), "");
		static_assert(!noexcept(s2.append(s1, SizeType{}, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s2.append(s1, SizeType{})), string&>::value, "");
		static_assert(hamon::is_same<decltype(s2.append(s1, SizeType{}, SizeType{})), string&>::value, "");
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 4);
		VERIFY(s2[0] == p2[0]);
		VERIFY(s2[1] == p2[1]);
		VERIFY(s2[2] == p2[2]);
		VERIFY(s2[3] == p2[3]);
		{
			auto& r = s2.append(s1, 1);
			VERIFY(&r == &s2);
			VERIFY(GeneralCheck(s2));
			VERIFY(s2.size() == 6);
			VERIFY(s2[0] == p2[0]);
			VERIFY(s2[1] == p2[1]);
			VERIFY(s2[2] == p2[2]);
			VERIFY(s2[3] == p2[3]);
			VERIFY(s2[4] == p1[1]);
			VERIFY(s2[5] == p1[2]);
		}
		{
			auto& r = s2.append(s2, 2, 2);
			VERIFY(&r == &s2);
			VERIFY(GeneralCheck(s2));
			VERIFY(s2.size() == 8);
			VERIFY(s2[0] == p2[0]);
			VERIFY(s2[1] == p2[1]);
			VERIFY(s2[2] == p2[2]);
			VERIFY(s2[3] == p2[3]);
			VERIFY(s2[4] == p1[1]);
			VERIFY(s2[5] == p1[2]);
			VERIFY(s2[6] == p2[2]);
			VERIFY(s2[7] == p2[3]);
		}
	}
#if defined(HAMON_HAS_STD_STRING_VIEW)
	{
		using string_view = std::basic_string_view<CharT>;
		auto p1 = Helper::abb();
		auto p2 = Helper::bcde();
		string_view const s1 = p1;
		string s2 = p2;
		static_assert(!noexcept(s2.append(s1, SizeType{})), "");
		static_assert(!noexcept(s2.append(s1, SizeType{}, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s2.append(s1, SizeType{})), string&>::value, "");
		static_assert(hamon::is_same<decltype(s2.append(s1, SizeType{}, SizeType{})), string&>::value, "");
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 4);
		VERIFY(s2[0] == p2[0]);
		VERIFY(s2[1] == p2[1]);
		VERIFY(s2[2] == p2[2]);
		VERIFY(s2[3] == p2[3]);
		{
			auto& r = s2.append(s1, 1);
			VERIFY(&r == &s2);
			VERIFY(GeneralCheck(s2));
			VERIFY(s2.size() == 6);
			VERIFY(s2[0] == p2[0]);
			VERIFY(s2[1] == p2[1]);
			VERIFY(s2[2] == p2[2]);
			VERIFY(s2[3] == p2[3]);
			VERIFY(s2[4] == p1[1]);
			VERIFY(s2[5] == p1[2]);
		}
		{
			auto& r = s2.append(s2, 2, 2);
			VERIFY(&r == &s2);
			VERIFY(GeneralCheck(s2));
			VERIFY(s2.size() == 8);
			VERIFY(s2[0] == p2[0]);
			VERIFY(s2[1] == p2[1]);
			VERIFY(s2[2] == p2[2]);
			VERIFY(s2[3] == p2[3]);
			VERIFY(s2[4] == p1[1]);
			VERIFY(s2[5] == p1[2]);
			VERIFY(s2[6] == p2[2]);
			VERIFY(s2[7] == p2[3]);
		}
	}
#endif

	// constexpr basic_string& append(const charT* s, size_type n);
	{
		auto p1 = Helper::abcde();
		auto p2 = Helper::abb();
		string s = p2;
		static_assert(!noexcept(s.append(p1, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s.append(p1, SizeType{})), string&>::value, "");
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 3);
		VERIFY(s[0] == p2[0]);
		VERIFY(s[1] == p2[1]);
		VERIFY(s[2] == p2[2]);
		{
			auto& r = s.append(p1, 2);
			VERIFY(&r == &s);
			VERIFY(GeneralCheck(s));
			VERIFY(s.size() == 5);
			VERIFY(s[0] == p2[0]);
			VERIFY(s[1] == p2[1]);
			VERIFY(s[2] == p2[2]);
			VERIFY(s[3] == p1[0]);
			VERIFY(s[4] == p1[1]);
		}
		{
			auto& r = s.append(s.data(), 4);
			VERIFY(&r == &s);
			VERIFY(GeneralCheck(s));
			VERIFY(s.size() == 9);
			VERIFY(s[0] == p2[0]);
			VERIFY(s[1] == p2[1]);
			VERIFY(s[2] == p2[2]);
			VERIFY(s[3] == p1[0]);
			VERIFY(s[4] == p1[1]);
			VERIFY(s[5] == p2[0]);
			VERIFY(s[6] == p2[1]);
			VERIFY(s[7] == p2[2]);
			VERIFY(s[8] == p1[0]);
		}
	}

	// constexpr basic_string& append(const charT* s);
	{
		auto p1 = Helper::abcde();
		auto p2 = Helper::abb();
		string s = p2;
		static_assert(!noexcept(s.append(p1)), "");
		static_assert(hamon::is_same<decltype(s.append(p1)), string&>::value, "");
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 3);
		VERIFY(s[0] == p2[0]);
		VERIFY(s[1] == p2[1]);
		VERIFY(s[2] == p2[2]);
		{
			auto& r = s.append(p1);
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
		{
			auto& r = s.append(s.data() + 1);
			VERIFY(&r == &s);
			VERIFY(GeneralCheck(s));
			VERIFY(s.size() == 15);
			VERIFY(s[ 0] == p2[0]);
			VERIFY(s[ 1] == p2[1]);
			VERIFY(s[ 2] == p2[2]);
			VERIFY(s[ 3] == p1[0]);
			VERIFY(s[ 4] == p1[1]);
			VERIFY(s[ 5] == p1[2]);
			VERIFY(s[ 6] == p1[3]);
			VERIFY(s[ 7] == p1[4]);
			VERIFY(s[ 8] == p2[1]);
			VERIFY(s[ 9] == p2[2]);
			VERIFY(s[10] == p1[0]);
			VERIFY(s[11] == p1[1]);
			VERIFY(s[12] == p1[2]);
			VERIFY(s[13] == p1[3]);
			VERIFY(s[14] == p1[4]);
		}
	}

	// constexpr basic_string& append(size_type n, charT c);
	{
		auto p = Helper::abcde();
		string s;
		static_assert(!noexcept(s.append(SizeType{}, CharT{})), "");
		static_assert(hamon::is_same<decltype(s.append(SizeType{}, CharT{})), string&>::value, "");
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 0);
		{
			auto& r = s.append(2, p[1]);
			VERIFY(&r == &s);
			VERIFY(GeneralCheck(s));
			VERIFY(s.size() == 2);
			VERIFY(s[0] == p[1]);
			VERIFY(s[1] == p[1]);
		}
		{
			auto& r = s.append(3, p[0]);
			VERIFY(&r == &s);
			VERIFY(GeneralCheck(s));
			VERIFY(s.size() == 5);
			VERIFY(s[0] == p[1]);
			VERIFY(s[1] == p[1]);
			VERIFY(s[2] == p[0]);
			VERIFY(s[3] == p[0]);
			VERIFY(s[4] == p[0]);
		}
		{
			auto& r = s.append(4, s[0]);
			VERIFY(&r == &s);
			VERIFY(GeneralCheck(s));
			VERIFY(s.size() == 9);
			VERIFY(s[0] == p[1]);
			VERIFY(s[1] == p[1]);
			VERIFY(s[2] == p[0]);
			VERIFY(s[3] == p[0]);
			VERIFY(s[4] == p[0]);
			VERIFY(s[5] == p[1]);
			VERIFY(s[6] == p[1]);
			VERIFY(s[7] == p[1]);
			VERIFY(s[8] == p[1]);
		}
	}

	// template<class InputIterator>
	// constexpr basic_string& append(InputIterator first, InputIterator last);
	{
		auto p = Helper::abcde();
		string s;
		static_assert(!noexcept(s.append(p, p)), "");
		static_assert(hamon::is_same<decltype(s.append(p, p)), string&>::value, "");
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 0);
		{
			auto& r = s.append(p, p + 2);
			VERIFY(&r == &s);
			VERIFY(GeneralCheck(s));
			VERIFY(s.size() == 2);
			VERIFY(s[0] == p[0]);
			VERIFY(s[1] == p[1]);
		}
		{
			auto& r = s.append(p + 1, p + 3);
			VERIFY(&r == &s);
			VERIFY(GeneralCheck(s));
			VERIFY(s.size() == 4);
			VERIFY(s[0] == p[0]);
			VERIFY(s[1] == p[1]);
			VERIFY(s[2] == p[1]);
			VERIFY(s[3] == p[2]);
		}
		{
			auto& r = s.append(s.begin(), s.end());
			VERIFY(&r == &s);
			VERIFY(GeneralCheck(s));
			VERIFY(s.size() == 8);
			VERIFY(s[0] == p[0]);
			VERIFY(s[1] == p[1]);
			VERIFY(s[2] == p[1]);
			VERIFY(s[3] == p[2]);
			VERIFY(s[4] == p[0]);
			VERIFY(s[5] == p[1]);
			VERIFY(s[6] == p[1]);
			VERIFY(s[7] == p[2]);
		}
	}

	// constexpr basic_string& append(initializer_list<charT>);
	{
		auto p = Helper::abcde();
		string s;
		static_assert(!noexcept(s.append(std::initializer_list<CharT>{})), "");
		static_assert(hamon::is_same<decltype(s.append(std::initializer_list<CharT>{})), string&>::value, "");
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 0);
		{
			auto& r = s.append({p[0], p[3], p[4], p[1], p[1]});
			VERIFY(&r == &s);
			VERIFY(GeneralCheck(s));
			VERIFY(s.size() == 5);
			VERIFY(s[0] == p[0]);
			VERIFY(s[1] == p[3]);
			VERIFY(s[2] == p[4]);
			VERIFY(s[3] == p[1]);
			VERIFY(s[4] == p[1]);
		}
		{
			auto& r = s.append({p[2], p[1]});
			VERIFY(&r == &s);
			VERIFY(GeneralCheck(s));
			VERIFY(s.size() == 7);
			VERIFY(s[0] == p[0]);
			VERIFY(s[1] == p[3]);
			VERIFY(s[2] == p[4]);
			VERIFY(s[3] == p[1]);
			VERIFY(s[4] == p[1]);
			VERIFY(s[5] == p[2]);
			VERIFY(s[6] == p[1]);
		}
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, AppendTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(AppendTest<TypeParam>());
}

}	// namespace append_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
