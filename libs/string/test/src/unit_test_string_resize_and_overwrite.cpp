/**
 *	@file	unit_test_string_resize_and_overwrite.cpp
 *
 *	@brief	resize_and_overwrite のテスト
 *
 *	template<class Operation>
 *	constexpr void resize_and_overwrite(size_type n, Operation op);
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
namespace resize_and_overwrite_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
ResizeAndOverwriteTest()
{
	//using string = hamon::basic_string<CharT>;

	// TODO

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, ResizeAndOverwriteTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(ResizeAndOverwriteTest<TypeParam>());
}

}	// namespace resize_and_overwrite_test
}	// namespace string_test
}	// namespace hamon_test
