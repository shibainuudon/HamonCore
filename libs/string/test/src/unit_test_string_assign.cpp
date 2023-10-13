/**
 *	@file	unit_test_string_assign.cpp
 *
 *	@brief	assign のテスト
 *
 *	constexpr basic_string& assign(const basic_string& str);
 *	constexpr basic_string& assign(basic_string&& str) noexcept(...);
 *	constexpr basic_string& assign(const basic_string& str, size_type pos, size_type n = npos);
 *	template<class T>
 *	constexpr basic_string& assign(const T& t);
 *	template<class T>
 *	constexpr basic_string& assign(const T& t, size_type pos, size_type n = npos);
 *	constexpr basic_string& assign(const charT* s, size_type n);
 *	constexpr basic_string& assign(const charT* s);
 *	constexpr basic_string& assign(size_type n, charT c);
 *	template<class InputIterator>
 *	constexpr basic_string& assign(InputIterator first, InputIterator last);
 *	constexpr basic_string& assign(initializer_list<charT>);
 */

#include <hamon/string/basic_string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
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
namespace assign_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
AssignTest()
{
	using string = hamon::basic_string<CharT>;
	using SizeType = typename string::size_type;
	using Traits = typename string::traits_type;
	using string_view = hamon::basic_string_view<CharT, Traits>;
	using Helper = StringTestHelper<CharT>;

	// constexpr basic_string& assign(const basic_string& str);
	{
		auto p1 = Helper::abb();
		auto p2 = Helper::bcde();
		string const s1 = p1;
		string s2 = p2;
		static_assert(!noexcept(s2.assign(s1)), "");
		static_assert(hamon::is_same<decltype(s2.assign(s1)), string&>::value, "");
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 4);
		VERIFY(s2[0] == p2[0]);
		VERIFY(s2[1] == p2[1]);
		VERIFY(s2[2] == p2[2]);
		VERIFY(s2[3] == p2[3]);
		{
			auto& r = s2.assign(s1);
			VERIFY(&r == &s2);
			VERIFY(GeneralCheck(s2));
			VERIFY(s2.size() == 3);
			VERIFY(s2[0] == p1[0]);
			VERIFY(s2[1] == p1[1]);
			VERIFY(s2[2] == p1[2]);
		}
		{
			auto& r = s2.assign(s2);
			VERIFY(&r == &s2);
			VERIFY(GeneralCheck(s2));
			VERIFY(s2.size() == 3);
			VERIFY(s2[0] == p1[0]);
			VERIFY(s2[1] == p1[1]);
			VERIFY(s2[2] == p1[2]);
		}
	}

	// constexpr basic_string& assign(basic_string&& str) noexcept(...);
	{
		auto p1 = Helper::abb();
		auto p2 = Helper::bcde();
		string s1 = p1;
		string s2 = p2;
		static_assert(noexcept(s2.assign(hamon::move(s1))), "");
		static_assert(hamon::is_same<decltype(s2.assign(hamon::move(s1))), string&>::value, "");
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 4);
		VERIFY(s2[0] == p2[0]);
		VERIFY(s2[1] == p2[1]);
		VERIFY(s2[2] == p2[2]);
		VERIFY(s2[3] == p2[3]);
		{
			auto& r = s2.assign(hamon::move(s1));
			VERIFY(&r == &s2);
			VERIFY(GeneralCheck(s2));
			VERIFY(s2.size() == 3);
			VERIFY(s2[0] == p1[0]);
			VERIFY(s2[1] == p1[1]);
			VERIFY(s2[2] == p1[2]);
		}
	}

	// constexpr basic_string& assign(const basic_string& str, size_type pos, size_type n = npos);
	{
		auto p1 = Helper::abb();
		auto p2 = Helper::bcde();
		string const s1 = p1;
		string s2 = p2;
		static_assert(!noexcept(s2.assign(s1, SizeType{})), "");
		static_assert(!noexcept(s2.assign(s1, SizeType{}, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s2.assign(s1, SizeType{})), string&>::value, "");
		static_assert(hamon::is_same<decltype(s2.assign(s1, SizeType{}, SizeType{})), string&>::value, "");
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 4);
		VERIFY(s2[0] == p2[0]);
		VERIFY(s2[1] == p2[1]);
		VERIFY(s2[2] == p2[2]);
		VERIFY(s2[3] == p2[3]);
		{
			auto& r = s2.assign(s1, 1);
			VERIFY(&r == &s2);
			VERIFY(GeneralCheck(s2));
			VERIFY(s2.size() == 2);
			VERIFY(s2[0] == p1[1]);
			VERIFY(s2[1] == p1[2]);
		}
		{
			auto& r = s2.assign(s1, 0, 1);
			VERIFY(&r == &s2);
			VERIFY(GeneralCheck(s2));
			VERIFY(s2.size() == 1);
			VERIFY(s2[0] == p1[0]);
		}
	}

	// template<class T>
	// constexpr basic_string& assign(const T& t);
	{
		auto p1 = Helper::abb();
		auto p2 = Helper::bcde();
		string_view const s1 = p1;
		string s2 = p2;
		static_assert(!noexcept(s2.assign(s1)), "");
		static_assert(hamon::is_same<decltype(s2.assign(s1)), string&>::value, "");
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 4);
		VERIFY(s2[0] == p2[0]);
		VERIFY(s2[1] == p2[1]);
		VERIFY(s2[2] == p2[2]);
		VERIFY(s2[3] == p2[3]);
		{
			auto& r = s2.assign(s1);
			VERIFY(&r == &s2);
			VERIFY(GeneralCheck(s2));
			VERIFY(s2.size() == 3);
			VERIFY(s2[0] == p1[0]);
			VERIFY(s2[1] == p1[1]);
			VERIFY(s2[2] == p1[2]);
		}
	}

	// template<class T>
	// constexpr basic_string& assign(const T& t, size_type pos, size_type n = npos);
	{
		auto p1 = Helper::abb();
		auto p2 = Helper::bcde();
		string_view const s1 = p1;
		string s2 = p2;
		static_assert(!noexcept(s2.assign(s1, SizeType{})), "");
		static_assert(!noexcept(s2.assign(s1, SizeType{}, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s2.assign(s1, SizeType{})), string&>::value, "");
		static_assert(hamon::is_same<decltype(s2.assign(s1, SizeType{}, SizeType{})), string&>::value, "");
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 4);
		VERIFY(s2[0] == p2[0]);
		VERIFY(s2[1] == p2[1]);
		VERIFY(s2[2] == p2[2]);
		VERIFY(s2[3] == p2[3]);
		{
			auto& r = s2.assign(s1, 1);
			VERIFY(&r == &s2);
			VERIFY(GeneralCheck(s2));
			VERIFY(s2.size() == 2);
			VERIFY(s2[0] == p1[1]);
			VERIFY(s2[1] == p1[2]);
		}
		{
			auto& r = s2.assign(s1, 0, 1);
			VERIFY(&r == &s2);
			VERIFY(GeneralCheck(s2));
			VERIFY(s2.size() == 1);
			VERIFY(s2[0] == p1[0]);
		}
	}

	// constexpr basic_string& assign(const charT* s, size_type n);
	{
		auto p1 = Helper::abcde();
		auto p2 = Helper::abb();
		string s = p2;
		static_assert(!noexcept(s.assign(p1, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s.assign(p1, SizeType{})), string&>::value, "");
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 3);
		VERIFY(s[0] == p2[0]);
		VERIFY(s[1] == p2[1]);
		VERIFY(s[2] == p2[2]);
		{
			auto& r = s.assign(p1, 2);
			VERIFY(&r == &s);
			VERIFY(GeneralCheck(s));
			VERIFY(s.size() == 2);
			VERIFY(s[0] == p1[0]);
			VERIFY(s[1] == p1[1]);
		}
	}

	// constexpr basic_string& assign(const charT* s);
	{
		auto p1 = Helper::abcde();
		auto p2 = Helper::abb();
		string s = p2;
		static_assert(!noexcept(s.assign(p1)), "");
		static_assert(hamon::is_same<decltype(s.assign(p1)), string&>::value, "");
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 3);
		VERIFY(s[0] == p2[0]);
		VERIFY(s[1] == p2[1]);
		VERIFY(s[2] == p2[2]);
		{
			auto& r = s.assign(p1);
			VERIFY(&r == &s);
			VERIFY(GeneralCheck(s));
			VERIFY(s.size() == 5);
			VERIFY(s[0] == p1[0]);
			VERIFY(s[1] == p1[1]);
			VERIFY(s[2] == p1[2]);
			VERIFY(s[3] == p1[3]);
			VERIFY(s[4] == p1[4]);
		}
	}

	// constexpr basic_string& assign(size_type n, charT c);
	{
		auto p = Helper::abcde();
		string s;
		static_assert(!noexcept(s.assign(SizeType{}, CharT{})), "");
		static_assert(hamon::is_same<decltype(s.assign(SizeType{}, CharT{})), string&>::value, "");
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 0);
		{
			auto const c = p[1];
			auto& r = s.assign(2, c);
			VERIFY(&r == &s);
			VERIFY(GeneralCheck(s));
			VERIFY(s.size() == 2);
			VERIFY(s[0] == c);
			VERIFY(s[1] == c);
		}
		{
			auto const c = p[0];
			auto& r = s.assign(40, c);
			VERIFY(&r == &s);
			VERIFY(GeneralCheck(s));
			VERIFY(s.size() == 40);
			VERIFY(s[0] == c);
			VERIFY(s[1] == c);
			VERIFY(s[2] == c);
			VERIFY(s[38] == c);
			VERIFY(s[39] == c);
		}
		{
			auto const c = p[2];
			auto& r = s.assign(3, c);
			VERIFY(&r == &s);
			VERIFY(GeneralCheck(s));
			VERIFY(s.size() == 3);
			VERIFY(s[0] == c);
			VERIFY(s[1] == c);
			VERIFY(s[2] == c);
		}
	}

	// template<class InputIterator>
	// constexpr basic_string& assign(InputIterator first, InputIterator last);
	{
		auto p = Helper::abcde();
		string s;
		static_assert(!noexcept(s.assign(p, p)), "");
		static_assert(hamon::is_same<decltype(s.assign(p, p)), string&>::value, "");
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 0);
		{
			auto& r = s.assign(p, p + 2);
			VERIFY(&r == &s);
			VERIFY(GeneralCheck(s));
			VERIFY(s.size() == 2);
			VERIFY(s[0] == p[0]);
			VERIFY(s[1] == p[1]);
		}
		{
			auto& r = s.assign(p + 1, p + 4);
			VERIFY(&r == &s);
			VERIFY(GeneralCheck(s));
			VERIFY(s.size() == 3);
			VERIFY(s[0] == p[1]);
			VERIFY(s[1] == p[2]);
			VERIFY(s[2] == p[3]);
		}
	}

	// constexpr basic_string& assign(initializer_list<charT>);
	{
		auto p = Helper::abcde();
		string s;
		static_assert(!noexcept(s.assign(std::initializer_list<CharT>{})), "");
		static_assert(hamon::is_same<decltype(s.assign(std::initializer_list<CharT>{})), string&>::value, "");
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 0);
		{
			auto& r = s.assign({p[0], p[3], p[4], p[1], p[1]});
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
			auto& r = s.assign({p[2], p[1]});
			VERIFY(&r == &s);
			VERIFY(GeneralCheck(s));
			VERIFY(s.size() == 2);
			VERIFY(s[0] == p[2]);
			VERIFY(s[1] == p[1]);
		}
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, AssignTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(AssignTest<TypeParam>());
}

}	// namespace assign_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
