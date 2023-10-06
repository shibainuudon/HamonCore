/**
 *	@file	unit_test_string_dtor.cpp
 *
 *	@brief	デストラクタのテスト
 *
 *	constexpr ~basic_string();
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
namespace dtor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
DtorTest()
{
	using string = hamon::basic_string<CharT>;

	// constexpr ~basic_string();
	static_assert( hamon::is_destructible<string>::value, "is_destructible");
	static_assert( hamon::is_nothrow_destructible<string>::value, "is_nothrow_destructible");
	static_assert(!hamon::is_trivially_destructible<string>::value, "is_trivially_destructible");

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, DtorTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(DtorTest<TypeParam>());
}

}	// namespace dtor_test
}	// namespace string_test
}	// namespace hamon_test
