/**
 *	@file	unit_test_vector_clear.cpp
 *
 *	@brief	clear のテスト
 *
 *	constexpr void clear() noexcept;
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace clear_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR bool test()
{
	using T = int;
	using Vector = hamon::vector<T>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().clear()),
		void
	>::value, "");

	static_assert(noexcept(
		hamon::declval<Vector&>().clear()), "");

	{
		Vector v{1,2,3};
		VERIFY(v.size() == 3);
		VERIFY(v.capacity() >= 3);
		v.clear();
		VERIFY(v.size() == 0);
		VERIFY(v.capacity() >= 3);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, ClearTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace clear_test

}	// namespace hamon_vector_test
