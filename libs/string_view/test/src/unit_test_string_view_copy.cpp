/**
 *	@file	unit_test_string_view_copy.cpp
 *
 *	@brief
 */

#include <hamon/string_view/basic_string_view.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "string_view_test_helper.hpp"

namespace hamon_test
{
namespace string_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX14_CONSTEXPR bool CopyTest()
{
	using string_view = hamon::basic_string_view<CharT>;

	auto str = StringViewTestHelper<CharT>::foo_bar();
	string_view sv{str};

	{
		CharT buffer[16] {};
		auto len = sv.copy(buffer, 7);
		VERIFY(len == 7);
		VERIFY(str[0] == buffer[0]);
	}
	{
		CharT buffer[16] {};
		auto len = sv.copy(buffer, 7, 1);
		VERIFY(len == 6);
		VERIFY(str[1] == buffer[0]);
	}
	{
		CharT buffer[16] {};
		auto len = sv.copy(buffer, 3, 1);
		VERIFY(len == 3);
		VERIFY(str[1] == buffer[0]);
	}
	{
		CharT buffer[16] {};
		auto len = sv.copy(buffer, 7, 6);
		VERIFY(len == 1);
		VERIFY(str[6] == buffer[0]);
	}
	{
		CharT buffer[16] {};
		auto len = sv.copy(buffer, 7, 7);
		VERIFY(len == 0);
		VERIFY(str[7] == buffer[0]);
	}
	return true;
}

TYPED_TEST(StringViewTest, CopyTest)
{
	using CharT = TypeParam;

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CopyTest<CharT>());

#if !defined(HAMON_NO_EXCEPTIONS)
// GCCかつReleaseビルドのときにコンパイルエラーになってしまう
#if !(defined(HAMON_GCC) && defined(NDEBUG))
	using string_view = hamon::basic_string_view<CharT>;
	{
		auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv{str};
		CharT buffer[16] {};
		EXPECT_THROW(sv.copy(buffer, 7, 8), hamon::out_of_range);
	}
#endif
#endif
}

#undef VERIFY

}	// namespace string_view_test
}	// namespace hamon_test
