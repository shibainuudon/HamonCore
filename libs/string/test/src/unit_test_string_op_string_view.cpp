/**
 *	@file	unit_test_string_op_string_view.cpp
 *
 *	@brief	op_string_view のテスト
 *
 *	constexpr operator basic_string_view<charT, traits>() const noexcept;
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
namespace op_string_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
OpStringViewTest()
{
	//using string = hamon::basic_string<CharT>;

	// TODO

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, OpStringViewTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(OpStringViewTest<TypeParam>());
}

}	// namespace op_string_view_test
}	// namespace string_test
}	// namespace hamon_test
