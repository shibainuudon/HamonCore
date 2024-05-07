/**
 *	@file	unit_test_vector_data.cpp
 *
 *	@brief	data のテスト
 *
 *	constexpr T*       data() noexcept;
 *	constexpr const T* data() const noexcept;
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace data_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Vector = hamon::vector<T>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().data()),
		T*
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector const&>().data()),
		T const*
	>::value, "");

	static_assert(noexcept(
		hamon::declval<Vector&>().data()), "");
	static_assert(noexcept(
		hamon::declval<Vector const&>().data()), "");

	{
		Vector v{1,2,3};
		auto p = v.data();
		VERIFY(*p == 1);

		*p = 42;

		VERIFY(v[0] == 42);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
	}
	{
		Vector const v{1,2,3};
		auto p = v.data();
		VERIFY(*p == 1);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, DataTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace data_test

}	// namespace hamon_vector_test
