/**
 *	@file	unit_test_string_replace_with_range.cpp
 *
 *	@brief	replace_with_range のテスト
 *
 *	template<container-compatible-range<charT> R>
 *	constexpr basic_string& replace_with_range(const_iterator i1, const_iterator i2, R&& rg);
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
namespace replace_with_range_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
ReplaceWithRangeTest()
{
	//using string = hamon::basic_string<CharT>;

	// TODO

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, ReplaceWithRangeTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(ReplaceWithRangeTest<TypeParam>());
}

}	// namespace replace_with_range_test
}	// namespace string_test
}	// namespace hamon_test
