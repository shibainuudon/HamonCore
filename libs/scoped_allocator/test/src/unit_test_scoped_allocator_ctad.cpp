/**
 *	@file	unit_test_scoped_allocator_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 */

#include <hamon/scoped_allocator/scoped_allocator_adaptor.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/string.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

namespace hamon_scoped_allocator_test
{

namespace ctad_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX20_CONSTEXPR bool test()
{
	hamon::scoped_allocator_adaptor a
	{
		hamon::allocator<hamon::string>{},
		hamon::allocator<char>{}
	};

	static_assert(hamon::is_same<decltype(a),
		hamon::scoped_allocator_adaptor<
			hamon::allocator<hamon::string>,
			hamon::allocator<char>>
	>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(ScopedAllocatorTest, CtadTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace ctad_test

}	// namespace hamon_scoped_allocator_test

#endif
