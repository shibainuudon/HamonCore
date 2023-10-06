/**
 *	@file	unit_test_string_append_range.cpp
 *
 *	@brief	append_range のテスト
 *
 *	template<container-compatible-range<charT> R>
 *	constexpr basic_string& append_range(R&& rg);
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
namespace append_range_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
AppendRangeTest()
{
	//using string = hamon::basic_string<CharT>;

	// TODO

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, AppendRangeTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AppendRangeTest<TypeParam>());
}

}	// namespace append_range_test
}	// namespace string_test
}	// namespace hamon_test
