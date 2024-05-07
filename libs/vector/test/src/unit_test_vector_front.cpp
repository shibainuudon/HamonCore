/**
 *	@file	unit_test_vector_front.cpp
 *
 *	@brief	front のテスト
 *
 *	constexpr reference       front();
 *	constexpr const_reference front() const;
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace front_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Vector = hamon::vector<T>;
	using Reference = typename Vector::reference;
	using ConstReference = typename Vector::const_reference;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().front()),
		Reference
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector const&>().front()),
		ConstReference
	>::value, "");

#if 0
	static_assert(!noexcept(
		hamon::declval<Vector&>().front()), "");
	static_assert(!noexcept(
		hamon::declval<Vector const&>().front()), "");
#endif

	{
		Vector v{1,2,3};
		VERIFY(v.front() == 1);

		v.front() = 42;

		VERIFY(v[0] == 42);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
	}
	{
		Vector const v{1,2,3};
		VERIFY(v.front() == 1);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, FrontTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace front_test

}	// namespace hamon_vector_test
