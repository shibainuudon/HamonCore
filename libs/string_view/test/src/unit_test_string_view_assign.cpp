/**
 *	@file	unit_test_string_view_assign.cpp
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
inline HAMON_CXX14_CONSTEXPR bool AssignTest()
{
	using string_view = hamon::basic_string_view<CharT>;
	{
		auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv2{str};
	
		string_view sv1;
		VERIFY(sv1.length() == 0);
		VERIFY(sv1.data() == nullptr);
		VERIFY(sv1.empty());

		sv1 = sv2;
		VERIFY(sv1.length() == 7);
		VERIFY(sv1.data() == str);
		VERIFY(!sv1.empty());
	}
	return true;
}

TYPED_TEST(StringViewTest, AssignTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AssignTest<TypeParam>());
}

#undef VERIFY

}	// namespace string_view_test
}	// namespace hamon_test
