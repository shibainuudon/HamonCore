/**
 *	@file	unit_test_string_erase.cpp
 *
 *	@brief	erase のテスト
 *
 *	constexpr basic_string& erase(size_type pos = 0, size_type n = npos);
 *	constexpr iterator erase(const_iterator p);
 *	constexpr iterator erase(const_iterator first, const_iterator last);
 */

#include <hamon/string/basic_string.hpp>
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
namespace erase_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
EraseTest()
{
	using string = hamon::basic_string<CharT>;
	using SizeType = typename string::size_type;
	using ConstIterator = typename string::const_iterator;
	using Iterator = typename string::iterator;
	using Helper = StringTestHelper<CharT>;

	// constexpr basic_string& erase(size_type pos = 0, size_type n = npos);
	{
		auto p = Helper::abcde();
		string s = p;
		static_assert(!noexcept(s.erase()), "");
		static_assert(!noexcept(s.erase(SizeType{})), "");
		static_assert(!noexcept(s.erase(SizeType{}, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s.erase()), string&>::value, "");
		static_assert(hamon::is_same<decltype(s.erase(SizeType{})), string&>::value, "");
		static_assert(hamon::is_same<decltype(s.erase(SizeType{}, SizeType{})), string&>::value, "");
		VERIFY(s.size() == 5);
		VERIFY(s[0] == p[0]);
		VERIFY(s[1] == p[1]);
		VERIFY(s[2] == p[2]);
		VERIFY(s[3] == p[3]);
		VERIFY(s[4] == p[4]);
		{
			auto& r = s.erase(1, 2);
			VERIFY(s.size() == 3);
			VERIFY(s[0] == p[0]);
			VERIFY(s[1] == p[3]);
			VERIFY(s[2] == p[4]);
			VERIFY(&r == &s);
		}
		{
			auto& r = s.erase(2);
			VERIFY(s.size() == 2);
			VERIFY(s[0] == p[0]);
			VERIFY(s[1] == p[3]);
			VERIFY(&r == &s);
		}
		{
			auto& r = s.erase();
			VERIFY(s.size() == 0);
			VERIFY(&r == &s);
		}
	}

	// constexpr iterator erase(const_iterator p);
	{
		auto p = Helper::abcde();
		string s = p;
//		static_assert(!noexcept(s.erase(ConstIterator{})), "");
		static_assert(hamon::is_same<decltype(s.erase(ConstIterator{})), Iterator>::value, "");
		VERIFY(s.size() == 5);
		VERIFY(s[0] == p[0]);
		VERIFY(s[1] == p[1]);
		VERIFY(s[2] == p[2]);
		VERIFY(s[3] == p[3]);
		VERIFY(s[4] == p[4]);
		{
			auto it = s.erase(s.begin() + 2);
			VERIFY(s.size() == 4);
			VERIFY(s[0] == p[0]);
			VERIFY(s[1] == p[1]);
			VERIFY(s[2] == p[3]);
			VERIFY(s[3] == p[4]);
			VERIFY(it == s.begin() + 2);
		}
		{
			auto it = s.erase(s.begin() + 3);
			VERIFY(s.size() == 3);
			VERIFY(s[0] == p[0]);
			VERIFY(s[1] == p[1]);
			VERIFY(s[2] == p[3]);
			VERIFY(it == s.end());
		}
	}

	// constexpr iterator erase(const_iterator first, const_iterator last);
	{
		auto p = Helper::abcde();
		string s = p;
//		static_assert(!noexcept(s.erase(ConstIterator{}, ConstIterator{})), "");
		static_assert(hamon::is_same<decltype(s.erase(ConstIterator{}, ConstIterator{})), Iterator>::value, "");
		VERIFY(s.size() == 5);
		VERIFY(s[0] == p[0]);
		VERIFY(s[1] == p[1]);
		VERIFY(s[2] == p[2]);
		VERIFY(s[3] == p[3]);
		VERIFY(s[4] == p[4]);
		{
			auto it = s.erase(s.begin() + 1, s.begin() + 3);
			VERIFY(s.size() == 3);
			VERIFY(s[0] == p[0]);
			VERIFY(s[1] == p[3]);
			VERIFY(s[2] == p[4]);
			VERIFY(it == s.begin() + 1);
		}
		{
			auto it = s.erase(s.begin(), s.end());
			VERIFY(s.size() == 0);
			VERIFY(it == s.end());
		}
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, EraseTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(EraseTest<TypeParam>());
}

}	// namespace erase_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
