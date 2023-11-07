/**
 *	@file	unit_test_string_view_swap.cpp
 *
 *	@brief
 */

#include <hamon/string_view/basic_string_view.hpp>
#include <hamon/utility/adl_swap.hpp>
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
inline HAMON_CXX14_CONSTEXPR bool SwapTest()
{
	using string_view = hamon::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	auto p1 = Helper::aababc();
	auto p2 = Helper::foo_bar();

	string_view sv1{p1};
	string_view sv2{p2};

	VERIFY(sv1.data() == p1);
	VERIFY(sv2.data() == p2);
	VERIFY(sv1.length() == 6);
	VERIFY(sv2.length() == 7);

	sv1.swap(sv2);

	VERIFY(sv1.data() == p2);
	VERIFY(sv2.data() == p1);
	VERIFY(sv1.length() == 7);
	VERIFY(sv2.length() == 6);

	hamon::adl_swap(sv1, sv2);

	VERIFY(sv1.data() == p1);
	VERIFY(sv2.data() == p2);
	VERIFY(sv1.length() == 6);
	VERIFY(sv2.length() == 7);

	return true;
}

TYPED_TEST(StringViewTest, SwapTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SwapTest<TypeParam>());
}

#undef VERIFY

}	// namespace string_view_test
}	// namespace hamon_test
