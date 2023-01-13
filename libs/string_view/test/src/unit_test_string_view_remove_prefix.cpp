/**
 *	@file	unit_test_string_view_remove_prefix.cpp
 *
 *	@brief
 */

#include <hamon/string_view/basic_string_view.hpp>
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
inline HAMON_CXX14_CONSTEXPR bool RemovePrefixTest()
{
	using string_view = hamon::basic_string_view<CharT>;

	{
		auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv{str};

		VERIFY(sv.data() == str);
		VERIFY(sv.length() == 7);

		sv.remove_prefix(1);

		VERIFY(sv.data() == str + 1);
		VERIFY(sv.length() == 6);

		sv.remove_prefix(2);

		VERIFY(sv.data() == str + 3);
		VERIFY(sv.length() == 4);
	}
	return true;
}

TYPED_TEST(StringViewTest, RemovePrefixTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemovePrefixTest<TypeParam>());
}

#undef VERIFY

}	// namespace string_view_test
}	// namespace hamon_test
