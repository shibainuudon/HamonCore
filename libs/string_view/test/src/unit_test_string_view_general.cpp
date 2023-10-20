/**
 *	@file	unit_test_string_view_general.cpp
 *
 *	@brief
 */

#include <hamon/string_view/basic_string_view.hpp>
#include <hamon/type_traits/is_trivially_copyable.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "string_view_test_helper.hpp"

namespace hamon_test
{
namespace string_view_test
{

TYPED_TEST(StringViewTest, GeneralTest)
{
	using string_view = hamon::basic_string_view<TypeParam>;
	static_assert(hamon::is_trivially_copyable<string_view>::value, "[string.view.template.general]/4");
}

}	// namespace string_view_test
}	// namespace hamon_test
