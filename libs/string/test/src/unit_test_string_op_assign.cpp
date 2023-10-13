/**
 *	@file	unit_test_string_op_assign.cpp
 *
 *	@brief	operator= のテスト
 *
 *	constexpr basic_string& operator=(const basic_string& str);
 *	constexpr basic_string& operator=(basic_string&& str) noexcept(...);
 *	template<class T>
 *	constexpr basic_string& operator=(const T& t);
 *	constexpr basic_string& operator=(const charT* s);
 *	basic_string& operator=(nullptr_t) = delete;
 *	constexpr basic_string& operator=(charT c);
 *	constexpr basic_string& operator=(initializer_list<charT>);
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
namespace op_assign_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
OpAssignTest()
{
	using string = hamon::basic_string<CharT>;
	using Traits = typename string::traits_type;
	using string_view = hamon::basic_string_view<CharT, Traits>;
	using Helper = StringTestHelper<CharT>;

	// constexpr basic_string& operator=(const basic_string& str);
	static_assert( hamon::is_copy_assignable          <string>::value, "is_copy_assignable");
	static_assert(!hamon::is_nothrow_copy_assignable  <string>::value, "is_nothrow_copy_assignable");
	static_assert(!hamon::is_trivially_copy_assignable<string>::value, "is_trivially_copy_assignable");
	{
		string s1;
		VERIFY(GeneralCheck(s1));
		VERIFY(s1.size() == 0);
		string const s2{Helper::abcde()};
		s1 = s2;
		VERIFY(GeneralCheck(s1));
		VERIFY(s1.size() == 5);
		VERIFY(s1[0] == Helper::abcde()[0]);
		VERIFY(s1[1] == Helper::abcde()[1]);
		VERIFY(s1[2] == Helper::abcde()[2]);
		VERIFY(s1[3] == Helper::abcde()[3]);
		VERIFY(s1[4] == Helper::abcde()[4]);

		string const s3{Helper::long_str()};
		s1 = s3;
		VERIFY(GeneralCheck(s1));
		VERIFY(s1.size() == 43);
		VERIFY(s1[ 0] == Helper::long_str()[ 0]);
		VERIFY(s1[ 1] == Helper::long_str()[ 1]);
		VERIFY(s1[ 2] == Helper::long_str()[ 2]);
		VERIFY(s1[ 3] == Helper::long_str()[ 3]);
		VERIFY(s1[41] == Helper::long_str()[41]);
		VERIFY(s1[42] == Helper::long_str()[42]);

		s1 = s2;
		VERIFY(GeneralCheck(s1));
		VERIFY(s1.size() == 5);
		VERIFY(s1[0] == Helper::abcde()[0]);
		VERIFY(s1[1] == Helper::abcde()[1]);
		VERIFY(s1[2] == Helper::abcde()[2]);
		VERIFY(s1[3] == Helper::abcde()[3]);
		VERIFY(s1[4] == Helper::abcde()[4]);
	}

	// constexpr basic_string& operator=(basic_string&& str) noexcept(...);
	static_assert( hamon::is_move_assignable          <string>::value, "is_move_assignable");
	static_assert( hamon::is_nothrow_move_assignable  <string>::value, "is_nothrow_move_assignable");
	static_assert(!hamon::is_trivially_move_assignable<string>::value, "is_trivially_move_assignable");
	{
		string s1;
		VERIFY(GeneralCheck(s1));
		VERIFY(s1.size() == 0);
		string s2{Helper::abcde()};
		s1 = hamon::move(s2);
		VERIFY(GeneralCheck(s1));
		VERIFY(s1.size() == 5);
		VERIFY(s1[0] == Helper::abcde()[0]);
		VERIFY(s1[1] == Helper::abcde()[1]);
		VERIFY(s1[2] == Helper::abcde()[2]);
		VERIFY(s1[3] == Helper::abcde()[3]);
		VERIFY(s1[4] == Helper::abcde()[4]);

		s1 = string{Helper::long_str()};
		VERIFY(GeneralCheck(s1));
		VERIFY(s1.size() == 43);
		VERIFY(s1[ 0] == Helper::long_str()[ 0]);
		VERIFY(s1[ 1] == Helper::long_str()[ 1]);
		VERIFY(s1[ 2] == Helper::long_str()[ 2]);
		VERIFY(s1[ 3] == Helper::long_str()[ 3]);
		VERIFY(s1[41] == Helper::long_str()[41]);
		VERIFY(s1[42] == Helper::long_str()[42]);
		VERIFY(s1[43] == CharT{});

		s1 = string{Helper::abcde()};
		VERIFY(GeneralCheck(s1));
		VERIFY(s1.size() == 5);
		VERIFY(s1[0] == Helper::abcde()[0]);
		VERIFY(s1[1] == Helper::abcde()[1]);
		VERIFY(s1[2] == Helper::abcde()[2]);
		VERIFY(s1[3] == Helper::abcde()[3]);
		VERIFY(s1[4] == Helper::abcde()[4]);
	}

	// template<class T>
	// constexpr basic_string& operator=(const T& t);
	static_assert( hamon::is_assignable          <string, const string_view&>::value, "is_assignable");
	static_assert(!hamon::is_nothrow_assignable  <string, const string_view&>::value, "is_nothrow_assignable");
	static_assert(!hamon::is_trivially_assignable<string, const string_view&>::value, "is_trivially_assignable");
	{
		string_view const s1{Helper::abcde()};
		string s2;
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 0);
		s2 = s1;
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 5);
		VERIFY(s2[0] == Helper::abcde()[0]);
		VERIFY(s2[1] == Helper::abcde()[1]);
		VERIFY(s2[2] == Helper::abcde()[2]);
		VERIFY(s2[3] == Helper::abcde()[3]);
		VERIFY(s2[4] == Helper::abcde()[4]);
	}

	// constexpr basic_string& operator=(const charT* s);
	static_assert( hamon::is_assignable          <string, const CharT*>::value, "is_assignable");
	static_assert(!hamon::is_nothrow_assignable  <string, const CharT*>::value, "is_nothrow_assignable");
	static_assert(!hamon::is_trivially_assignable<string, const CharT*>::value, "is_trivially_assignable");
	{
		string s;
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 0);
		s = Helper::abcde();
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 5);
		VERIFY(s[0] == Helper::abcde()[0]);
		VERIFY(s[1] == Helper::abcde()[1]);
		VERIFY(s[2] == Helper::abcde()[2]);
		VERIFY(s[3] == Helper::abcde()[3]);
		VERIFY(s[4] == Helper::abcde()[4]);
	}

	// basic_string& operator=(nullptr_t) = delete;
	static_assert(!hamon::is_assignable<string, std::nullptr_t>::value, "is_assignable");

	// constexpr basic_string& operator=(charT c);
	static_assert( hamon::is_assignable          <string, CharT>::value, "is_assignable");
	static_assert(!hamon::is_nothrow_assignable  <string, CharT>::value, "is_nothrow_assignable");
	static_assert(!hamon::is_trivially_assignable<string, CharT>::value, "is_trivially_assignable");
	{
		string s;
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 0);
		s = Helper::abcde()[2];
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 1);
		VERIFY(s[0] == Helper::abcde()[2]);
	}

	// constexpr basic_string& operator=(initializer_list<charT>);
	static_assert( hamon::is_assignable          <string, std::initializer_list<CharT>>::value, "is_assignable");
	static_assert(!hamon::is_nothrow_assignable  <string, std::initializer_list<CharT>>::value, "is_nothrow_assignable");
	static_assert(!hamon::is_trivially_assignable<string, std::initializer_list<CharT>>::value, "is_trivially_assignable");
	{
		string s;
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 0);
		s = { Helper::abcde()[2], Helper::abcde()[1], Helper::abcde()[2] };
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 3);
		VERIFY(s[0] == Helper::abcde()[2]);
		VERIFY(s[1] == Helper::abcde()[1]);
		VERIFY(s[2] == Helper::abcde()[2]);
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, OpAssignTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(OpAssignTest<TypeParam>());
}

}	// namespace op_assign_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
