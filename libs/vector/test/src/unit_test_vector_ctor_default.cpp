/**
 *	@file	unit_test_vector_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	constexpr vector() noexcept(noexcept(Allocator()));
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace ctor_default_test
{

struct S1
{
	S1() = delete;
};

struct S2
{
	S2() {}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Vector = hamon::vector<T>;

	static_assert( hamon::is_default_constructible<Vector>::value, "");
	static_assert( hamon::is_nothrow_default_constructible<Vector>::value, "");
	static_assert( hamon::is_implicitly_default_constructible<Vector>::value, "");
	static_assert(!hamon::is_trivially_default_constructible<Vector>::value, "");

	{
		Vector v;
		VERIFY(v.size() == 0);
		VERIFY(v.empty());
	}
	{
		Vector v{};
		VERIFY(v.size() == 0);
		VERIFY(v.empty());
	}
	{
		Vector v = {};
		VERIFY(v.size() == 0);
		VERIFY(v.empty());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, CtorDefaultTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());
}

}	// namespace ctor_default_test

}	// namespace hamon_vector_test
