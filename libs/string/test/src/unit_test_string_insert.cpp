/**
 *	@file	unit_test_string_insert.cpp
 *
 *	@brief	insert のテスト
 *
 *	constexpr basic_string& insert(size_type pos, const basic_string& str);
 *	constexpr basic_string& insert(size_type pos1, const basic_string& str, size_type pos2, size_type n = npos);
 *	template<class T>
 *	constexpr basic_string& insert(size_type pos, const T& t);
 *	template<class T>
 *	constexpr basic_string& insert(size_type pos1, const T& t, size_type pos2, size_type n = npos);
 *	constexpr basic_string& insert(size_type pos, const charT* s, size_type n);
 *	constexpr basic_string& insert(size_type pos, const charT* s);
 *	constexpr basic_string& insert(size_type pos, size_type n, charT c);
 *	constexpr iterator insert(const_iterator p, charT c);
 *	constexpr iterator insert(const_iterator p, size_type n, charT c);
 *	template<class InputIterator>
 *	constexpr iterator insert(const_iterator p, InputIterator first, InputIterator last);
 *	constexpr iterator insert(const_iterator p, initializer_list<charT>);
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
namespace insert_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
InsertTest()
{
	using string = hamon::basic_string<CharT>;
	using SizeType = typename string::size_type;
	using Iterator = typename string::iterator;
	using Helper = StringTestHelper<CharT>;

	// constexpr basic_string& insert(size_type pos, const basic_string& str);
	{
		auto p1 = Helper::abb();
		auto p2 = Helper::bcde();
		string const s1 = p1;
		string s2 = p2;
		static_assert(!noexcept(s2.insert(SizeType{}, s1)), "");
		static_assert(hamon::is_same<decltype(s2.insert(SizeType{}, s1)), string&>::value, "");
		VERIFY(s2.size() == 4);
		VERIFY(s2[0] == p2[0]);
		VERIFY(s2[1] == p2[1]);
		VERIFY(s2[2] == p2[2]);
		VERIFY(s2[3] == p2[3]);
		{
			auto& r = s2.insert(1, s1);
			VERIFY(&r == &s2);
			VERIFY(s2.size() == 7);
			VERIFY(s2[0] == p2[0]);
			VERIFY(s2[1] == p1[0]);
			VERIFY(s2[2] == p1[1]);
			VERIFY(s2[3] == p1[2]);
			VERIFY(s2[4] == p2[1]);
			VERIFY(s2[5] == p2[2]);
			VERIFY(s2[6] == p2[3]);
		}
	}

	// constexpr basic_string& insert(size_type pos1, const basic_string& str, size_type pos2, size_type n = npos);
	{
		auto p1 = Helper::abb();
		auto p2 = Helper::bcde();
		string const s1 = p1;
		string s2 = p2;
		static_assert(!noexcept(s2.insert(SizeType{}, s1, SizeType{})), "");
		static_assert(!noexcept(s2.insert(SizeType{}, s1, SizeType{}, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s2.insert(SizeType{}, s1, SizeType{})), string&>::value, "");
		static_assert(hamon::is_same<decltype(s2.insert(SizeType{}, s1, SizeType{}, SizeType{})), string&>::value, "");
		VERIFY(s2.size() == 4);
		VERIFY(s2[0] == p2[0]);
		VERIFY(s2[1] == p2[1]);
		VERIFY(s2[2] == p2[2]);
		VERIFY(s2[3] == p2[3]);
		{
			auto& r = s2.insert(1, s1, 1);
			VERIFY(&r == &s2);
			VERIFY(s2.size() == 6);
			VERIFY(s2[0] == p2[0]);
			VERIFY(s2[1] == p1[1]);
			VERIFY(s2[2] == p1[2]);
			VERIFY(s2[3] == p2[1]);
			VERIFY(s2[4] == p2[2]);
			VERIFY(s2[5] == p2[3]);
		}
		{
			auto& r = s2.insert(2, s2, 2, 2);
			VERIFY(&r == &s2);
			VERIFY(s2.size() == 8);
			VERIFY(s2[0] == p2[0]);
			VERIFY(s2[1] == p1[1]);
			VERIFY(s2[2] == p1[2]);
			VERIFY(s2[3] == p2[1]);
			VERIFY(s2[4] == p1[2]);
			VERIFY(s2[5] == p2[1]);
			VERIFY(s2[6] == p2[2]);
			VERIFY(s2[7] == p2[3]);
		}
	}

#if HAMON_CXX_STANDARD >= 17	// TODO
	using string_view = std::basic_string_view<CharT>;

	// template<class T>
	// constexpr basic_string& insert(size_type pos, const T& t);
	{
		auto p1 = Helper::abb();
		auto p2 = Helper::bcde();
		string_view const s1 = p1;
		string s2 = p2;
		static_assert(!noexcept(s2.insert(SizeType{}, s1)), "");
		static_assert(hamon::is_same<decltype(s2.insert(SizeType{}, s1)), string&>::value, "");
		VERIFY(s2.size() == 4);
		VERIFY(s2[0] == p2[0]);
		VERIFY(s2[1] == p2[1]);
		VERIFY(s2[2] == p2[2]);
		VERIFY(s2[3] == p2[3]);
		{
			auto& r = s2.insert(1, s1);
			VERIFY(&r == &s2);
			VERIFY(s2.size() == 7);
			VERIFY(s2[0] == p2[0]);
			VERIFY(s2[1] == p1[0]);
			VERIFY(s2[2] == p1[1]);
			VERIFY(s2[3] == p1[2]);
			VERIFY(s2[4] == p2[1]);
			VERIFY(s2[5] == p2[2]);
			VERIFY(s2[6] == p2[3]);
		}
	}

	// template<class T>
	// constexpr basic_string& insert(size_type pos1, const T& t, size_type pos2, size_type n = npos);
	{
		auto p1 = Helper::abb();
		auto p2 = Helper::bcde();
		string_view const s1 = p1;
		string s2 = p2;
		static_assert(!noexcept(s2.insert(SizeType{}, s1, SizeType{})), "");
		static_assert(!noexcept(s2.insert(SizeType{}, s1, SizeType{}, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s2.insert(SizeType{}, s1, SizeType{})), string&>::value, "");
		static_assert(hamon::is_same<decltype(s2.insert(SizeType{}, s1, SizeType{}, SizeType{})), string&>::value, "");
		VERIFY(s2.size() == 4);
		VERIFY(s2[0] == p2[0]);
		VERIFY(s2[1] == p2[1]);
		VERIFY(s2[2] == p2[2]);
		VERIFY(s2[3] == p2[3]);
		{
			auto& r = s2.insert(1, s1, 1);
			VERIFY(&r == &s2);
			VERIFY(s2.size() == 6);
			VERIFY(s2[0] == p2[0]);
			VERIFY(s2[1] == p1[1]);
			VERIFY(s2[2] == p1[2]);
			VERIFY(s2[3] == p2[1]);
			VERIFY(s2[4] == p2[2]);
			VERIFY(s2[5] == p2[3]);
		}
		{
			auto& r = s2.insert(2, s2, 2, 2);
			VERIFY(&r == &s2);
			VERIFY(s2.size() == 8);
			VERIFY(s2[0] == p2[0]);
			VERIFY(s2[1] == p1[1]);
			VERIFY(s2[2] == p1[2]);
			VERIFY(s2[3] == p2[1]);
			VERIFY(s2[4] == p1[2]);
			VERIFY(s2[5] == p2[1]);
			VERIFY(s2[6] == p2[2]);
			VERIFY(s2[7] == p2[3]);
		}
	}
#endif

	// constexpr basic_string& insert(size_type pos, const charT* s, size_type n);
	{
		auto p1 = Helper::abcde();
		auto p2 = Helper::abb();
		string s = p2;
		static_assert(!noexcept(s.insert(SizeType{}, p1, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s.insert(SizeType{}, p1, SizeType{})), string&>::value, "");
		VERIFY(s.size() == 3);
		VERIFY(s[0] == p2[0]);
		VERIFY(s[1] == p2[1]);
		VERIFY(s[2] == p2[2]);
		{
			auto& r = s.insert(1, p1, 2);
			VERIFY(&r == &s);
			VERIFY(s.size() == 5);
			VERIFY(s[0] == p2[0]);
			VERIFY(s[1] == p1[0]);
			VERIFY(s[2] == p1[1]);
			VERIFY(s[3] == p2[1]);
			VERIFY(s[4] == p2[2]);
		}
	}

	// constexpr basic_string& insert(size_type pos, const charT* s);
	{
		auto p1 = Helper::abcde();
		auto p2 = Helper::abb();
		string s = p2;
		static_assert(!noexcept(s.insert(SizeType{}, p1)), "");
		static_assert(hamon::is_same<decltype(s.insert(SizeType{}, p1)), string&>::value, "");
		VERIFY(s.size() == 3);
		VERIFY(s[0] == p2[0]);
		VERIFY(s[1] == p2[1]);
		VERIFY(s[2] == p2[2]);
		{
			auto& r = s.insert(2, p1);
			VERIFY(&r == &s);
			VERIFY(s.size() == 8);
			VERIFY(s[0] == p2[0]);
			VERIFY(s[1] == p2[1]);
			VERIFY(s[2] == p1[0]);
			VERIFY(s[3] == p1[1]);
			VERIFY(s[4] == p1[2]);
			VERIFY(s[5] == p1[3]);
			VERIFY(s[6] == p1[4]);
			VERIFY(s[7] == p2[2]);
		}
	}

	// constexpr basic_string& insert(size_type pos, size_type n, charT c);
	{
		auto p = Helper::abcde();
		string s;
		static_assert(!noexcept(s.insert(SizeType{}, SizeType{}, CharT{})), "");
		static_assert(hamon::is_same<decltype(s.insert(SizeType{}, SizeType{}, CharT{})), string&>::value, "");
		VERIFY(s.size() == 0);
		{
			auto& r = s.insert(0, 2, p[1]);
			VERIFY(&r == &s);
			VERIFY(s.size() == 2);
			VERIFY(s[0] == p[1]);
			VERIFY(s[1] == p[1]);
		}
		{
			auto& r = s.insert(1, 3, p[0]);
			VERIFY(&r == &s);
			VERIFY(s.size() == 5);
			VERIFY(s[0] == p[1]);
			VERIFY(s[1] == p[0]);
			VERIFY(s[2] == p[0]);
			VERIFY(s[3] == p[0]);
			VERIFY(s[4] == p[1]);
		}
	}

	// constexpr iterator insert(const_iterator p, charT c);
	{
		auto p = Helper::abcde();
		string s;
		static_assert(!noexcept(s.insert(s.begin(), CharT{})), "");
		static_assert(hamon::is_same<decltype(s.insert(s.begin(), CharT{})), Iterator>::value, "");
		VERIFY(s.size() == 0);
		{
			auto it = s.insert(s.begin(), p[1]);
			VERIFY(s.size() == 1);
			VERIFY(s[0] == p[1]);
			VERIFY(it == s.begin());
			VERIFY(*it == p[1]);
		}
		{
			auto it = s.insert(s.begin() + 1, p[0]);
			VERIFY(s.size() == 2);
			VERIFY(s[0] == p[1]);
			VERIFY(s[1] == p[0]);
			VERIFY(it == s.begin() + 1);
			VERIFY(*it == p[0]);
		}
	}

	// constexpr iterator insert(const_iterator p, size_type n, charT c);
	{
		auto p = Helper::abcde();
		string s;
		static_assert(!noexcept(s.insert(s.begin(), SizeType{}, CharT{})), "");
		static_assert(hamon::is_same<decltype(s.insert(s.begin(), SizeType{}, CharT{})), Iterator>::value, "");
		VERIFY(s.size() == 0);
		{
			auto it = s.insert(s.begin(), 2, p[1]);
			VERIFY(s.size() == 2);
			VERIFY(s[0] == p[1]);
			VERIFY(s[1] == p[1]);
			VERIFY(it == s.begin());
			VERIFY(*it == p[1]);
		}
		{
			auto it = s.insert(s.begin() + 1, 3, p[0]);
			VERIFY(s.size() == 5);
			VERIFY(s[0] == p[1]);
			VERIFY(s[1] == p[0]);
			VERIFY(s[2] == p[0]);
			VERIFY(s[3] == p[0]);
			VERIFY(s[4] == p[1]);
			VERIFY(it == s.begin() + 1);
			VERIFY(*it == p[0]);
		}
	}

	// template<class InputIterator>
	// constexpr iterator insert(const_iterator p, InputIterator first, InputIterator last);
	{
		auto p = Helper::abcde();
		string s;
		static_assert(!noexcept(s.insert(s.begin(), p, p)), "");
		static_assert(hamon::is_same<decltype(s.insert(s.begin(), p, p)), Iterator>::value, "");
		VERIFY(s.size() == 0);
		{
			auto it = s.insert(s.begin(), p, p + 3);
			VERIFY(s.size() == 3);
			VERIFY(s[0] == p[0]);
			VERIFY(s[1] == p[1]);
			VERIFY(s[2] == p[2]);
			VERIFY(it == s.begin());
			VERIFY(*it == p[0]);
		}
		{
			auto it = s.insert(s.begin() + 1, p + 3, p + 5);
			VERIFY(s.size() == 5);
			VERIFY(s[0] == p[0]);
			VERIFY(s[1] == p[3]);
			VERIFY(s[2] == p[4]);
			VERIFY(s[3] == p[1]);
			VERIFY(s[4] == p[2]);
			VERIFY(it == s.begin() + 1);
			VERIFY(*it == p[3]);
		}
	}

	// constexpr iterator insert(const_iterator p, initializer_list<charT>);
	{
		auto p = Helper::abcde();
		string s;
		static_assert(!noexcept(s.insert(s.begin(), std::initializer_list<CharT>{})), "");
		static_assert(hamon::is_same<decltype(s.insert(s.begin(), std::initializer_list<CharT>{})), Iterator>::value, "");
		VERIFY(s.size() == 0);
		{
			auto it = s.insert(s.begin(), {p[0], p[3], p[1]});
			VERIFY(s.size() == 3);
			VERIFY(s[0] == p[0]);
			VERIFY(s[1] == p[3]);
			VERIFY(s[2] == p[1]);
			VERIFY(it == s.begin());
			VERIFY(*it == p[0]);
		}
		{
			auto it = s.insert(s.begin() + 1, {p[1], p[2]});
			VERIFY(s.size() == 5);
			VERIFY(s[0] == p[0]);
			VERIFY(s[1] == p[1]);
			VERIFY(s[2] == p[2]);
			VERIFY(s[3] == p[3]);
			VERIFY(s[4] == p[1]);
			VERIFY(it == s.begin() + 1);
			VERIFY(*it == p[1]);
		}
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, InsertTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(InsertTest<TypeParam>());
}

}	// namespace insert_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
