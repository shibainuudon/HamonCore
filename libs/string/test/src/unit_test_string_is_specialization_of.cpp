/**
 *	@file	unit_test_string_is_specialization_of.cpp
 *
 *	@brief	is_specialization_of_basic_string のテスト
 */

#include <hamon/string/detail/is_specialization_of_basic_string.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/vector.hpp>
#include <string>
#include "string_test_helper.hpp"

namespace hamon_test
{
namespace string_test
{

TYPED_TEST(StringTest, IsSpecializationOfTest)
{
	static_assert(hamon::detail::is_specialization_of_basic_string<hamon::basic_string<TypeParam>>::value, "");
	static_assert(hamon::detail::is_specialization_of_basic_string<std::basic_string<TypeParam>>::value, "");

	static_assert(!hamon::detail::is_specialization_of_basic_string<hamon::basic_string_view<TypeParam>>::value, "");
	static_assert(!hamon::detail::is_specialization_of_basic_string<hamon::vector<TypeParam>>::value, "");
	static_assert(!hamon::detail::is_specialization_of_basic_string<TypeParam const*>::value, "");
}

}	// namespace string_test
}	// namespace hamon_test
