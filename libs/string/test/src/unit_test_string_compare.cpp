/**
 *	@file	unit_test_string_compare.cpp
 *
 *	@brief	compare のテスト
 *
 *	template<class T>
 *	constexpr int compare(const T& t) const noexcept(see below);
 *	template<class T>
 *	constexpr int compare(size_type pos1, size_type n1, const T& t) const;
 *	template<class T>
 *	constexpr int compare(size_type pos1, size_type n1, const T& t, size_type pos2, size_type n2 = npos) const;
 *	constexpr int compare(const basic_string& str) const noexcept;
 *	constexpr int compare(size_type pos1, size_type n1, const basic_string& str) const;
 *	constexpr int compare(size_type pos1, size_type n1, const basic_string& str, size_type pos2, size_type n2 = npos) const;
 *	constexpr int compare(const charT* s) const;
 *	constexpr int compare(size_type pos1, size_type n1, const charT* s) const;
 *	constexpr int compare(size_type pos1, size_type n1, const charT* s, size_type n2) const;
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
namespace compare_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
CompareTest()
{
	using string = hamon::basic_string<CharT>;
	using SizeType = typename string::size_type;
	using Traits = typename string::traits_type;
	using string_view = hamon::basic_string_view<CharT, Traits>;
	using Helper = StringTestHelper<CharT>;

	// template<class T>
	// constexpr int compare(const T& t) const noexcept(see below);
	{
		string const s1 = Helper::abc();
		string_view const s2 = Helper::abc();
		string_view const s3 = Helper::abcd();
		string_view const s4 = Helper::ab();
		string_view const s5 = Helper::abb();
		string_view const s6 = Helper::bcde();
		//static_assert(noexcept(s1.compare(s2)), "");	// TODO
		static_assert(hamon::is_same<decltype(s1.compare(s2)), int>::value, "");

		VERIFY(s1.compare(s1) == 0);
		VERIFY(s1.compare(s2) == 0);
		VERIFY(s1.compare(s3) <  0);
		VERIFY(s1.compare(s4) >  0);
		VERIFY(s1.compare(s5) >  0);
		VERIFY(s1.compare(s6) <  0);
	}

	// template<class T>
	// constexpr int compare(size_type pos1, size_type n1, const T& t) const;
	{
		string const s1 = Helper::abcd();
		string_view const s2 = Helper::abc();
		//static_assert(!noexcept(s1.compare(SizeType{}, SizeType{}, s2)), "");	// TODO
		static_assert(hamon::is_same<decltype(s1.compare(SizeType{}, SizeType{}, s2)), int>::value, "");

		VERIFY(s1.compare(0, 3, s2) == 0);	// "abc".compare("abc")
		VERIFY(s1.compare(1, 3, s2) >  0);	// "bcd".compare("abc")
		VERIFY(s1.compare(0,10, s2) >  0);	// "abcd".compare("abc")
		VERIFY(s1.compare(0, 2, s2) <  0);	// "ab".compare("abc")
	}

	// template<class T>
	// constexpr int compare(size_type pos1, size_type n1, const T& t, size_type pos2, size_type n2 = npos) const;
	{
		string const s1 = Helper::abcd();
		string_view const s2 = string_view{Helper::bcde()}.substr(0, 3);
		string_view const s3 = Helper::bcde();
		//static_assert(!noexcept(s1.compare(SizeType{}, SizeType{}, s2, SizeType{}, SizeType{})), "");	// TODO
		static_assert(hamon::is_same<decltype(s1.compare(SizeType{}, SizeType{}, s2, SizeType{}, SizeType{})), int>::value, "");

		VERIFY(s1.compare(1, 3, s2, 0) == 0);	// "bcd".compare("bcd")
		VERIFY(s1.compare(0, 3, s2, 0) <  0);	// "abc".compare("bcd")
		VERIFY(s1.compare(2, 2, s2, 1) == 0);	// "cd".compare("cd")
		VERIFY(s1.compare(3, 1, s2, 1) >  0);	// "d".compare("cd")

		VERIFY(s1.compare(1, 3, s3, 0, 3) == 0);	// "bcd".compare("bcd")
		VERIFY(s1.compare(0, 3, s3, 0, 3) <  0);	// "abc".compare("bcd")
		VERIFY(s1.compare(1, 2, s3, 0, 3) <  0);	// "bc".compare("bcd")
		VERIFY(s1.compare(1, 3, s3, 0, 2) >  0);	// "bcd".compare("bc")
		VERIFY(s1.compare(1, 3, s3, 0, 4) <  0);	// "bcd".compare("bcde")
	}

	// constexpr int compare(const basic_string& str) const noexcept;
	{
		string const s1 = Helper::abc();
		string const s2 = Helper::abc();
		string const s3 = Helper::abcd();
		string const s4 = Helper::ab();
		string const s5 = Helper::abb();
		string const s6 = Helper::bcde();
		//static_assert(noexcept(s1.compare(s2)), "");	// TODO
		static_assert(hamon::is_same<decltype(s1.compare(s2)), int>::value, "");

		VERIFY(s1.compare(s1) == 0);
		VERIFY(s1.compare(s2) == 0);
		VERIFY(s1.compare(s3) <  0);
		VERIFY(s1.compare(s4) >  0);
		VERIFY(s1.compare(s5) >  0);
		VERIFY(s1.compare(s6) <  0);
	}

	// constexpr int compare(size_type pos1, size_type n1, const basic_string& str) const;
	{
		string const s1 = Helper::abcd();
		string const s2 = Helper::abc();
		static_assert(!noexcept(s1.compare(SizeType{}, SizeType{}, s2)), "");
		static_assert(hamon::is_same<decltype(s1.compare(SizeType{}, SizeType{}, s2)), int>::value, "");

		VERIFY(s1.compare(0, 3, s2) == 0);	// "abc".compare("abc")
		VERIFY(s1.compare(1, 3, s2) >  0);	// "bcd".compare("abc")
		VERIFY(s1.compare(0,10, s2) >  0);	// "abcd".compare("abc")
		VERIFY(s1.compare(0, 2, s2) <  0);	// "ab".compare("abc")
	}

	// constexpr int compare(size_type pos1, size_type n1, const basic_string& str, size_type pos2, size_type n2 = npos) const;
	{
		string const s1 = Helper::abcd();
		string const s2 = string{Helper::bcde()}.substr(0, 3);
		string const s3 = Helper::bcde();
		static_assert(!noexcept(s1.compare(SizeType{}, SizeType{}, s2, SizeType{}, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s1.compare(SizeType{}, SizeType{}, s2, SizeType{}, SizeType{})), int>::value, "");

		VERIFY(s1.compare(1, 3, s2, 0) == 0);	// "bcd".compare("bcd")
		VERIFY(s1.compare(0, 3, s2, 0) <  0);	// "abc".compare("bcd")
		VERIFY(s1.compare(2, 2, s2, 1) == 0);	// "cd".compare("cd")
		VERIFY(s1.compare(3, 1, s2, 1) >  0);	// "d".compare("cd")

		VERIFY(s1.compare(1, 3, s3, 0, 3) == 0);	// "bcd".compare("bcd")
		VERIFY(s1.compare(0, 3, s3, 0, 3) <  0);	// "abc".compare("bcd")
		VERIFY(s1.compare(1, 2, s3, 0, 3) <  0);	// "bc".compare("bcd")
		VERIFY(s1.compare(1, 3, s3, 0, 2) >  0);	// "bcd".compare("bc")
		VERIFY(s1.compare(1, 3, s3, 0, 4) <  0);	// "bcd".compare("bcde")
	}

	// constexpr int compare(const charT* s) const;
	{
		string const s(Helper::abcd());
		//static_assert(noexcept(s.compare((CharT*)nullptr)), "");
		static_assert(hamon::is_same<decltype(s.compare((CharT*)nullptr)), int>::value, "");

		VERIFY(s.compare(Helper::abcd())  == 0);	// "abcd".compare("abcd")
		VERIFY(s.compare(Helper::abc())   >  0);	// "abcd".compare("abc")
		VERIFY(s.compare(Helper::abcde()) <  0);	// "abcd".compare("abcde")
		VERIFY(s.compare(Helper::abb())   >  0);	// "abcd".compare("abb")
	}

	// constexpr int compare(size_type pos1, size_type n1, const charT* s) const;
	{
		string const s(Helper::abcde());
		static_assert(!noexcept(s.compare(SizeType{}, SizeType{}, (CharT*)nullptr)), "");
		static_assert(hamon::is_same<decltype(s.compare(SizeType{}, SizeType{}, (CharT*)nullptr)), int>::value, "");

		VERIFY(s.compare(0, 3, Helper::abc()) == 0);	// "abc".compare("abc")
		VERIFY(s.compare(1, 3, Helper::abc()) >  0);	// "bcd".compare("abc")
		VERIFY(s.compare(0,10, Helper::abc()) >  0);	// "abcde".compare("abc")
		VERIFY(s.compare(0, 2, Helper::abc()) <  0);	// "ab".compare("abc")
	}

	// constexpr int compare(size_type pos1, size_type n1, const charT* s, size_type n2) const;
	{
		string const s(Helper::abcde());
		static_assert(!noexcept(s.compare(SizeType{}, SizeType{}, (CharT*)nullptr, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s.compare(SizeType{}, SizeType{}, (CharT*)nullptr, SizeType{})), int>::value, "");

		VERIFY(s.compare(0, 3, Helper::abcd(), 2) >  0);	// "abc".compare("ab")
		VERIFY(s.compare(0, 3, Helper::abcd(), 3) == 0);	// "abc".compare("abc")
		VERIFY(s.compare(0, 3, Helper::abcd(), 4) <  0);	// "abc".compare("abcd")
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, CompareTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(CompareTest<TypeParam>());
}

}	// namespace compare_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
