/**
 *	@file	unit_test_string_substr.cpp
 *
 *	@brief	substr のテスト
 *
 *	constexpr basic_string substr(size_type pos = 0, size_type n = npos) const &;
 *	constexpr basic_string substr(size_type pos = 0, size_type n = npos) &&;
 */

#include <hamon/string/basic_string.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
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
namespace substr_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
SubstrTest()
{
	using string = hamon::basic_string<CharT>;
	using SizeType = typename string::size_type;
	using Helper = StringTestHelper<CharT>;

	// constexpr basic_string substr(size_type pos = 0, size_type n = npos) const &;
	{
		auto p = Helper::abcde();
		string const s = p;
		static_assert(!noexcept(s.substr()), "");
		static_assert(!noexcept(s.substr(SizeType{})), "");
		static_assert(!noexcept(s.substr(SizeType{}, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s.substr()), string>::value, "");
		static_assert(hamon::is_same<decltype(s.substr(SizeType{})), string>::value, "");
		static_assert(hamon::is_same<decltype(s.substr(SizeType{}, SizeType{})), string>::value, "");

		{
			auto r = s.substr();
			VERIFY(r.size() == 5);
			VERIFY(r[0] == p[0]);
			VERIFY(r[1] == p[1]);
			VERIFY(r[2] == p[2]);
			VERIFY(r[3] == p[3]);
			VERIFY(r[4] == p[4]);
		}
		{
			auto r = s.substr(2);
			VERIFY(r.size() == 3);
			VERIFY(r[0] == p[2]);
			VERIFY(r[1] == p[3]);
			VERIFY(r[2] == p[4]);
		}
		{
			auto r = s.substr(1, 4);
			VERIFY(r.size() == 4);
			VERIFY(r[0] == p[1]);
			VERIFY(r[1] == p[2]);
			VERIFY(r[2] == p[3]);
			VERIFY(r[3] == p[4]);
		}
	}

	// constexpr basic_string substr(size_type pos = 0, size_type n = npos) &&;
	{
		auto p = Helper::abcde();
		string const s = p;
		static_assert(!noexcept(string{s}.substr()), "");
		static_assert(!noexcept(string{s}.substr(SizeType{})), "");
		static_assert(!noexcept(string{s}.substr(SizeType{}, SizeType{})), "");
		static_assert(hamon::is_same<decltype(string{s}.substr()), string>::value, "");
		static_assert(hamon::is_same<decltype(string{s}.substr(SizeType{})), string>::value, "");
		static_assert(hamon::is_same<decltype(string{s}.substr(SizeType{}, SizeType{})), string>::value, "");
		
		{
			auto r = string{s}.substr();
			VERIFY(r.size() == 5);
			VERIFY(r[0] == p[0]);
			VERIFY(r[1] == p[1]);
			VERIFY(r[2] == p[2]);
			VERIFY(r[3] == p[3]);
			VERIFY(r[4] == p[4]);
		}
		{
			auto r = string{s}.substr(2);
			VERIFY(r.size() == 3);
			VERIFY(r[0] == p[2]);
			VERIFY(r[1] == p[3]);
			VERIFY(r[2] == p[4]);
		}
		{
			auto r = string{s}.substr(1, 4);
			VERIFY(r.size() == 4);
			VERIFY(r[0] == p[1]);
			VERIFY(r[1] == p[2]);
			VERIFY(r[2] == p[3]);
			VERIFY(r[3] == p[4]);
		}
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, SubstrTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubstrTest<TypeParam>());
}

}	// namespace substr_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
