/**
 *	@file	unit_test_string_replace.cpp
 *
 *	@brief	replace のテスト
 *
 *	constexpr basic_string& replace(size_type pos1, size_type n1, const basic_string& str);
 *	constexpr basic_string& replace(size_type pos1, size_type n1, const basic_string& str, size_type pos2, size_type n2 = npos);
 *	template<class T>
 *	constexpr basic_string& replace(size_type pos1, size_type n1, const T& t);
 *	template<class T>
 *	constexpr basic_string& replace(size_type pos1, size_type n1, const T& t, size_type pos2, size_type n2 = npos);
 *	constexpr basic_string& replace(size_type pos, size_type n1, const charT* s, size_type n2);
 *	constexpr basic_string& replace(size_type pos, size_type n1, const charT* s);
 *	constexpr basic_string& replace(size_type pos, size_type n1, size_type n2, charT c);
 *	constexpr basic_string& replace(const_iterator i1, const_iterator i2, const basic_string& str);
 *	template<class T>
 *	constexpr basic_string& replace(const_iterator i1, const_iterator i2, const T& t);
 *	constexpr basic_string& replace(const_iterator i1, const_iterator i2, const charT* s, size_type n);
 *	constexpr basic_string& replace(const_iterator i1, const_iterator i2, const charT* s);
 *	constexpr basic_string& replace(const_iterator i1, const_iterator i2, size_type n, charT c);
 *	template<class InputIterator>
 *	constexpr basic_string& replace(const_iterator i1, const_iterator i2, InputIterator j1, InputIterator j2);
 *	constexpr basic_string& replace(const_iterator, const_iterator, initializer_list<charT>);
 */

#include <hamon/string/basic_string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <initializer_list>
#include "constexpr_test.hpp"
#include "string_test_helper.hpp"

namespace hamon_test
{
namespace string_test
{
namespace replace_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
ReplaceTest()
{
	using string = hamon::basic_string<CharT>;
	using SizeType = typename string::size_type;
	using ConstIterator = typename string::const_iterator;
	using Helper = StringTestHelper<CharT>;

	// constexpr basic_string& replace(size_type pos1, size_type n1, const basic_string& str);
	{
		auto p1 = Helper::abcde();
		auto p2 = Helper::ABCDE();
		string const s1 = p1;
		string s2 = p2;
		static_assert(!noexcept(s2.replace(SizeType{}, SizeType{}, s1)), "");
		static_assert(hamon::is_same<decltype(s2.replace(SizeType{}, SizeType{}, s1)), string&>::value, "");
		{
			auto& r = s2.replace(1, 2, s1);
			VERIFY(&r == &s2);
			VERIFY(s2.size() == 8);
			VERIFY(s2[0] == p2[0]);
			VERIFY(s2[1] == p1[0]);
			VERIFY(s2[2] == p1[1]);
			VERIFY(s2[3] == p1[2]);
			VERIFY(s2[4] == p1[3]);
			VERIFY(s2[5] == p1[4]);
			VERIFY(s2[6] == p2[3]);
			VERIFY(s2[7] == p2[4]);
		}
	}

	// constexpr basic_string& replace(size_type pos1, size_type n1, const basic_string& str, size_type pos2, size_type n2 = npos);
	{
		auto p1 = Helper::abcde();
		auto p2 = Helper::ABCDE();
		string const s1 = p1;
		string s2 = p2;
		static_assert(!noexcept(s2.replace(SizeType{}, SizeType{}, s1, SizeType{})), "");
		static_assert(!noexcept(s2.replace(SizeType{}, SizeType{}, s1, SizeType{}, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s2.replace(SizeType{}, SizeType{}, s1, SizeType{})), string&>::value, "");
		static_assert(hamon::is_same<decltype(s2.replace(SizeType{}, SizeType{}, s1, SizeType{}, SizeType{})), string&>::value, "");
		{
			auto& r = s2.replace(1, 2, s1, 2, 3);
			VERIFY(&r == &s2);
			VERIFY(s2.size() == 6);
			VERIFY(s2[0] == p2[0]);
			VERIFY(s2[1] == p1[2]);
			VERIFY(s2[2] == p1[3]);
			VERIFY(s2[3] == p1[4]);
			VERIFY(s2[4] == p2[3]);
			VERIFY(s2[5] == p2[4]);
		}
		{
			auto& r = s2.replace(2, 3, s1, 4);
			VERIFY(&r == &s2);
			VERIFY(s2.size() == 4);
			VERIFY(s2[0] == p2[0]);
			VERIFY(s2[1] == p1[2]);
			VERIFY(s2[2] == p1[4]);
			VERIFY(s2[3] == p2[4]);
		}
	}

#if HAMON_CXX_STANDARD >= 17	// TODO
	using string_view = std::basic_string_view<CharT>;

	// template<class T>
	// constexpr basic_string& replace(size_type pos1, size_type n1, const T& t);
	{
		auto p1 = Helper::abcde();
		auto p2 = Helper::ABCDE();
		string_view const s1 = p1;
		string s2 = p2;
		static_assert(!noexcept(s2.replace(SizeType{}, SizeType{}, s1)), "");
		static_assert(hamon::is_same<decltype(s2.replace(SizeType{}, SizeType{}, s1)), string&>::value, "");
		{
			auto& r = s2.replace(1, 2, s1);
			VERIFY(&r == &s2);
			VERIFY(s2.size() == 8);
			VERIFY(s2[0] == p2[0]);
			VERIFY(s2[1] == p1[0]);
			VERIFY(s2[2] == p1[1]);
			VERIFY(s2[3] == p1[2]);
			VERIFY(s2[4] == p1[3]);
			VERIFY(s2[5] == p1[4]);
			VERIFY(s2[6] == p2[3]);
			VERIFY(s2[7] == p2[4]);
		}
	}

	// template<class T>
	// constexpr basic_string& replace(size_type pos1, size_type n1, const T& t, size_type pos2, size_type n2 = npos);
	{
		auto p1 = Helper::abcde();
		auto p2 = Helper::ABCDE();
		string_view const s1 = p1;
		string s2 = p2;
		static_assert(!noexcept(s2.replace(SizeType{}, SizeType{}, s1, SizeType{})), "");
		static_assert(!noexcept(s2.replace(SizeType{}, SizeType{}, s1, SizeType{}, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s2.replace(SizeType{}, SizeType{}, s1, SizeType{})), string&>::value, "");
		static_assert(hamon::is_same<decltype(s2.replace(SizeType{}, SizeType{}, s1, SizeType{}, SizeType{})), string&>::value, "");
		{
			auto& r = s2.replace(1, 2, s1, 2, 3);
			VERIFY(&r == &s2);
			VERIFY(s2.size() == 6);
			VERIFY(s2[0] == p2[0]);
			VERIFY(s2[1] == p1[2]);
			VERIFY(s2[2] == p1[3]);
			VERIFY(s2[3] == p1[4]);
			VERIFY(s2[4] == p2[3]);
			VERIFY(s2[5] == p2[4]);
		}
		{
			auto& r = s2.replace(2, 3, s1, 4);
			VERIFY(&r == &s2);
			VERIFY(s2.size() == 4);
			VERIFY(s2[0] == p2[0]);
			VERIFY(s2[1] == p1[2]);
			VERIFY(s2[2] == p1[4]);
			VERIFY(s2[3] == p2[4]);
		}
	}

	// template<class T>
	// constexpr basic_string& replace(const_iterator i1, const_iterator i2, const T& t);
	{
		auto p1 = Helper::abcde();
		auto p2 = Helper::ABCDE();
		string_view const s1 = p1;
		string s2 = p2;
		static_assert(!noexcept(s2.replace(ConstIterator{}, ConstIterator{}, s1)), "");
		static_assert(hamon::is_same<decltype(s2.replace(ConstIterator{}, ConstIterator{}, s1)), string&>::value, "");
		{
			auto& r = s2.replace(s2.begin() + 1, s2.begin() + 3, s1);
			VERIFY(&r == &s2);
			VERIFY(s2.size() == 8);
			VERIFY(s2[0] == p2[0]);
			VERIFY(s2[1] == p1[0]);
			VERIFY(s2[2] == p1[1]);
			VERIFY(s2[3] == p1[2]);
			VERIFY(s2[4] == p1[3]);
			VERIFY(s2[5] == p1[4]);
			VERIFY(s2[6] == p2[3]);
			VERIFY(s2[7] == p2[4]);
		}
	}
#endif

	// constexpr basic_string& replace(size_type pos, size_type n1, const charT* s, size_type n2);
	{
		auto p1 = Helper::abcde();
		auto p2 = Helper::ABCDE();
		string s = p1;
		static_assert(!noexcept(s.replace(SizeType{}, SizeType{}, p2, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s.replace(SizeType{}, SizeType{}, p2, SizeType{})), string&>::value, "");
		{
			auto& r = s.replace(1, 3, p2, 2);
			VERIFY(&r == &s);
			VERIFY(s.size() == 4);
			VERIFY(s[0] == p1[0]);
			VERIFY(s[1] == p2[0]);
			VERIFY(s[2] == p2[1]);
			VERIFY(s[3] == p1[4]);
		}
	}

	// constexpr basic_string& replace(size_type pos, size_type n1, const charT* s);
	{
		auto p1 = Helper::abcde();
		auto p2 = Helper::ABCDE();
		string s = p1;
		static_assert(!noexcept(s.replace(SizeType{}, SizeType{}, p2)), "");
		static_assert(hamon::is_same<decltype(s.replace(SizeType{}, SizeType{}, p2)), string&>::value, "");
		{
			auto& r = s.replace(1, 3, p2);
			VERIFY(&r == &s);
			VERIFY(s.size() == 7);
			VERIFY(s[0] == p1[0]);
			VERIFY(s[1] == p2[0]);
			VERIFY(s[2] == p2[1]);
			VERIFY(s[3] == p2[2]);
			VERIFY(s[4] == p2[3]);
			VERIFY(s[5] == p2[4]);
			VERIFY(s[6] == p1[4]);
		}
	}

	// constexpr basic_string& replace(size_type pos, size_type n1, size_type n2, charT c);
	{
		auto p1 = Helper::abcde();
		auto p2 = Helper::ABCDE();
		string s = p1;
		static_assert(!noexcept(s.replace(SizeType{}, SizeType{}, SizeType{}, CharT{})), "");
		static_assert(hamon::is_same<decltype(s.replace(SizeType{}, SizeType{}, SizeType{}, CharT{})), string&>::value, "");
		{
			auto& r = s.replace(2, 2, 3, p2[0]);
			VERIFY(&r == &s);
			VERIFY(s.size() == 6);
			VERIFY(s[0] == p1[0]);
			VERIFY(s[1] == p1[1]);
			VERIFY(s[2] == p2[0]);
			VERIFY(s[3] == p2[0]);
			VERIFY(s[4] == p2[0]);
			VERIFY(s[5] == p1[4]);
		}
	}

	// constexpr basic_string& replace(const_iterator i1, const_iterator i2, const basic_string& str);
	{
		auto p1 = Helper::abcde();
		auto p2 = Helper::ABCDE();
		string const s1 = p1;
		string s2 = p2;
		static_assert(!noexcept(s2.replace(ConstIterator{}, ConstIterator{}, s1)), "");
		static_assert(hamon::is_same<decltype(s2.replace(ConstIterator{}, ConstIterator{}, s1)), string&>::value, "");
		{
			auto& r = s2.replace(s2.begin() + 1, s2.begin() + 3, s1);
			VERIFY(&r == &s2);
			VERIFY(s2.size() == 8);
			VERIFY(s2[0] == p2[0]);
			VERIFY(s2[1] == p1[0]);
			VERIFY(s2[2] == p1[1]);
			VERIFY(s2[3] == p1[2]);
			VERIFY(s2[4] == p1[3]);
			VERIFY(s2[5] == p1[4]);
			VERIFY(s2[6] == p2[3]);
			VERIFY(s2[7] == p2[4]);
		}
	}

	// constexpr basic_string& replace(const_iterator i1, const_iterator i2, const charT* s, size_type n);
	{
		auto p1 = Helper::abcde();
		auto p2 = Helper::ABCDE();
		string s = p1;
		static_assert(!noexcept(s.replace(ConstIterator{}, ConstIterator{}, p2, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s.replace(ConstIterator{}, ConstIterator{}, p2, SizeType{})), string&>::value, "");
		{
			auto& r = s.replace(s.begin() + 1, s.begin() + 4, p2, 2);
			VERIFY(&r == &s);
			VERIFY(s.size() == 4);
			VERIFY(s[0] == p1[0]);
			VERIFY(s[1] == p2[0]);
			VERIFY(s[2] == p2[1]);
			VERIFY(s[3] == p1[4]);
		}
	}

	// constexpr basic_string& replace(const_iterator i1, const_iterator i2, const charT* s);
	{
		auto p1 = Helper::abcde();
		auto p2 = Helper::ABCDE();
		string s = p1;
		static_assert(!noexcept(s.replace(ConstIterator{}, ConstIterator{}, p2)), "");
		static_assert(hamon::is_same<decltype(s.replace(ConstIterator{}, ConstIterator{}, p2)), string&>::value, "");
		{
			auto& r = s.replace(s.begin() + 1, s.begin() + 3, p2);
			VERIFY(&r == &s);
			VERIFY(s.size() == 8);
			VERIFY(s[0] == p1[0]);
			VERIFY(s[1] == p2[0]);
			VERIFY(s[2] == p2[1]);
			VERIFY(s[3] == p2[2]);
			VERIFY(s[4] == p2[3]);
			VERIFY(s[5] == p2[4]);
			VERIFY(s[6] == p1[3]);
			VERIFY(s[7] == p1[4]);
		}
	}

	// constexpr basic_string& replace(const_iterator i1, const_iterator i2, size_type n, charT c);
	{
		auto p1 = Helper::abcde();
		auto p2 = Helper::ABCDE();
		string s = p1;
		static_assert(!noexcept(s.replace(ConstIterator{}, ConstIterator{}, SizeType{}, CharT{})), "");
		static_assert(hamon::is_same<decltype(s.replace(ConstIterator{}, ConstIterator{}, SizeType{}, CharT{})), string&>::value, "");
		{
			auto& r = s.replace(s.begin() + 2, s.begin() + 4, 3, p2[0]);
			VERIFY(&r == &s);
			VERIFY(s.size() == 6);
			VERIFY(s[0] == p1[0]);
			VERIFY(s[1] == p1[1]);
			VERIFY(s[2] == p2[0]);
			VERIFY(s[3] == p2[0]);
			VERIFY(s[4] == p2[0]);
			VERIFY(s[5] == p1[4]);
		}
	}

	// template<class InputIterator>
	// constexpr basic_string& replace(const_iterator i1, const_iterator i2, InputIterator j1, InputIterator j2);
	{
		auto p1 = Helper::abcde();
		auto p2 = Helper::ABCDE();
		string s = p1;
		static_assert(!noexcept(s.replace(ConstIterator{}, ConstIterator{}, p2, p2)), "");
		static_assert(hamon::is_same<decltype(s.replace(ConstIterator{}, ConstIterator{}, p2, p2)), string&>::value, "");
		{
			auto& r = s.replace(s.begin() + 1, s.begin() + 3, p2, p2 + 2);
			VERIFY(&r == &s);
			VERIFY(s.size() == 5);
			VERIFY(s[0] == p1[0]);
			VERIFY(s[1] == p2[0]);
			VERIFY(s[2] == p2[1]);
			VERIFY(s[3] == p1[3]);
			VERIFY(s[4] == p1[4]);
		}
	}

	// constexpr basic_string& replace(const_iterator, const_iterator, initializer_list<charT>);
	{
		auto p1 = Helper::abcde();
		auto p2 = Helper::ABCDE();
		string s = p1;
		static_assert(!noexcept(s.replace(ConstIterator{}, ConstIterator{}, std::initializer_list<CharT>{})), "");
		static_assert(hamon::is_same<decltype(s.replace(ConstIterator{}, ConstIterator{}, std::initializer_list<CharT>{})), string&>::value, "");
		{
			auto& r = s.replace(s.begin() + 1, s.begin() + 4, {p2[0], p2[3]});
			VERIFY(&r == &s);
			VERIFY(s.size() == 4);
			VERIFY(s[0] == p1[0]);
			VERIFY(s[1] == p2[0]);
			VERIFY(s[2] == p2[3]);
			VERIFY(s[3] == p1[4]);
		}
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, ReplaceTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(ReplaceTest<TypeParam>());
}

}	// namespace replace_test
}	// namespace string_test
}	// namespace hamon_test
