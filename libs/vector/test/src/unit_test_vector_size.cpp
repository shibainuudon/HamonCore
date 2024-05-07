/**
 *	@file	unit_test_vector_size.cpp
 *
 *	@brief	size のテスト
 *
 *	constexpr size_type size() const noexcept;
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace size_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Vector = hamon::vector<T>;
	using SizeType = typename Vector::size_type;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector const&>().size()),
		SizeType
	>::value, "");
	static_assert(noexcept(
		hamon::declval<Vector const&>().size()), "");

	{
		Vector const v;
		VERIFY(v.size() == 0);
	}
	{
		Vector const v{1,3,4};
		VERIFY(v.size() == 3);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, SizeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace size_test

}	// namespace hamon_vector_test
