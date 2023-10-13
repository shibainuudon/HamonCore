/**
 *	@file	unit_test_string_copy.cpp
 *
 *	@brief	copy のテスト
 *
 *	constexpr size_type copy(charT* s, size_type n, size_type pos = 0) const;
 */

#include <hamon/string/basic_string.hpp>
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
namespace copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
CopyTest()
{
	using string = hamon::basic_string<CharT>;
	using SizeType = typename string::size_type;
	using Helper = StringTestHelper<CharT>;

	auto p = Helper::abcde();
	string const s = p;

	{
		CharT result[5 + 1] = {};
		static_assert(!noexcept(s.copy(result, SizeType{})), "");
		static_assert(!noexcept(s.copy(result, SizeType{}, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s.copy(result, SizeType{})), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s.copy(result, SizeType{}, SizeType{})), SizeType>::value, "");
		auto r = s.copy(result, 5);
		VERIFY(r == 5);
		VERIFY(result[0] == p[0]);
		VERIFY(result[1] == p[1]);
		VERIFY(result[2] == p[2]);
		VERIFY(result[3] == p[3]);
		VERIFY(result[4] == p[4]);
		VERIFY(result[5] == CharT{});
	}
	{
		CharT result[5 + 1] = {};
		auto r = s.copy(result, 100);
		VERIFY(r == 5);
		VERIFY(result[0] == p[0]);
		VERIFY(result[1] == p[1]);
		VERIFY(result[2] == p[2]);
		VERIFY(result[3] == p[3]);
		VERIFY(result[4] == p[4]);
		VERIFY(result[5] == CharT{});
	}
	{
		CharT result[3 + 1] = {};
		auto r = s.copy(result, 3);
		VERIFY(r == 3);
		VERIFY(result[0] == p[0]);
		VERIFY(result[1] == p[1]);
		VERIFY(result[2] == p[2]);
		VERIFY(result[3] == CharT{});
	}
	{
		CharT result[3 + 1] = {};
		auto r = s.copy(result, 3, 2);
		VERIFY(r == 3);
		VERIFY(result[0] == p[2]);
		VERIFY(result[1] == p[3]);
		VERIFY(result[2] == p[4]);
		VERIFY(result[3] == CharT{});
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, CopyTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(CopyTest<TypeParam>());
}

}	// namespace copy_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
