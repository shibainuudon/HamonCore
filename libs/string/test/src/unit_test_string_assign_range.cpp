/**
 *	@file	unit_test_string_assign_range.cpp
 *
 *	@brief	assign_range のテスト
 *
 *	template<container-compatible-range<charT> R>
 *	constexpr basic_string& assign_range(R&& rg);
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
namespace assign_range_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
AssignRangeTest()
{
	//using string = hamon::basic_string<CharT>;

	// TODO

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, AssignRangeTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AssignRangeTest<TypeParam>());
}

}	// namespace assign_range_test
}	// namespace string_test
}	// namespace hamon_test
