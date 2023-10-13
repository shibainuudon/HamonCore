/**
 *	@file	unit_test_string_c_str.cpp
 *
 *	@brief	c_str のテスト
 *
 *	constexpr const charT* c_str() const noexcept;
 */

#include <hamon/string/basic_string.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include "constexpr_test.hpp"
#include "string_test_helper.hpp"

namespace hamon_test
{
namespace string_test
{
namespace c_str_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
CStrTest()
{
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		auto src = Helper::abcde();
		string const s = src;
		static_assert(noexcept(s.c_str()), "");
		static_assert(hamon::is_same<decltype(s.c_str()), const CharT*>::value, "");

		auto p = s.c_str();
		VERIFY(p + 0 == &s[0]);
		VERIFY(p + 1 == &s[1]);
		VERIFY(p + 2 == &s[2]);
		VERIFY(p + 3 == &s[3]);
		VERIFY(p + 4 == &s[4]);

		VERIFY(p[0] == src[0]);
		VERIFY(p[1] == src[1]);
		VERIFY(p[2] == src[2]);
		VERIFY(p[3] == src[3]);
		VERIFY(p[4] == src[4]);
		VERIFY(p[5] == CharT{});
	}
	{
		string const s{};
		auto p = s.c_str();
		VERIFY(p[0] == CharT{});
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, CStrTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(CStrTest<TypeParam>());
}

}	// namespace c_str_test
}	// namespace string_test
}	// namespace hamon_test
