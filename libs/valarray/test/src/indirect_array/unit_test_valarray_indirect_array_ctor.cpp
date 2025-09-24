/**
 *	@file	unit_test_valarray_indirect_array_ctor.cpp
 *
 *	@brief	コンストラクタのテスト
 *
 *	indirect_array(const indirect_array&);
 *	indirect_array() = delete;
 */

#include <hamon/valarray/indirect_array.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace indirect_array_ctor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	static_assert(!hamon::is_default_constructible<hamon::indirect_array<T>>::value, "");

	static_assert( hamon::is_copy_constructible<hamon::indirect_array<T>>::value, "");
	static_assert(!hamon::is_nothrow_copy_constructible<hamon::indirect_array<T>>::value, "");
	static_assert(!hamon::is_trivially_copy_constructible<hamon::indirect_array<T>>::value, "");
	static_assert( hamon::is_implicitly_copy_constructible<hamon::indirect_array<T>>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, IndirectArrayCtorTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace indirect_array_ctor_test

}	// namespace hamon_valarray_test
