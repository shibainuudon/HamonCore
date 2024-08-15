/**
 *	@file	unit_test_memory_unique_ptr_dtor.cpp
 *
 *	@brief	デストラクタのテスト
 *
 *	constexpr ~unique_ptr();
 */

#include <hamon/memory/unique_ptr.hpp>
#include <hamon/type_traits/is_destructible.hpp>
#include <hamon/type_traits/is_nothrow_destructible.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace unique_ptr_test
{

namespace dtor_test
{

struct D
{
	int* counter;

	HAMON_CXX11_CONSTEXPR D(int* p) : counter(p) {}

	template <typename T>
	HAMON_CXX14_CONSTEXPR void operator()(T* p) const { (*counter)++; delete p; }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		int counter = 0;
		{
			hamon::unique_ptr<int, D> up(nullptr, D{&counter});
		}
		VERIFY(counter == 0);
	}
	{
		int counter = 0;
		{
			hamon::unique_ptr<int, D> up(new int, D{&counter});
		}
		VERIFY(counter == 1);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UniquePtrTest, DtorTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());

	{
		using UP = hamon::unique_ptr<int>;
		static_assert( hamon::is_destructible<UP>::value, "");
		static_assert( hamon::is_nothrow_destructible<UP>::value, "");
		static_assert(!hamon::is_trivially_destructible<UP>::value, "");
	}
}

}	// namespace dtor_test

}	// namespace unique_ptr_test

}	// namespace hamon_memory_test
