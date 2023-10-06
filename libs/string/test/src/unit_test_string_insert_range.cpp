/**
 *	@file	unit_test_string_insert_range.cpp
 *
 *	@brief	insert_range のテスト
 *
 *	template<container-compatible-range<charT> R>
 *	constexpr iterator insert_range(const_iterator p, R&& rg);
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
namespace insert_range_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
InsertRangeTest()
{
	//using string = hamon::basic_string<CharT>;

	// TODO

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, InsertRangeTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(InsertRangeTest<TypeParam>());
}

}	// namespace insert_range_test
}	// namespace string_test
}	// namespace hamon_test
