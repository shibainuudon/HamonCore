/**
 *	@file	unit_test_vector_at.cpp
 *
 *	@brief	at のテスト
 *
 *	constexpr const_reference at(size_type n) const;
 *	constexpr reference       at(size_type n);
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace at_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Vector = hamon::vector<T>;
	using SizeType = typename Vector::size_type;
	using Reference = typename Vector::reference;
	using ConstReference = typename Vector::const_reference;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().at(hamon::declval<SizeType>())),
		Reference
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector const&>().at(hamon::declval<SizeType>())),
		ConstReference
	>::value, "");

	static_assert(!noexcept(
		hamon::declval<Vector&>().at(hamon::declval<SizeType>())), "");
	static_assert(!noexcept(
		hamon::declval<Vector const&>().at(hamon::declval<SizeType>())), "");

	{
		Vector v{1,2,3};
		VERIFY(v.at(0) == 1);
		VERIFY(v.at(1) == 2);
		VERIFY(v.at(2) == 3);

		v.at(0) = 10;
		v.at(2) = 20;

		VERIFY(v.at(0) == 10);
		VERIFY(v.at(1) == 2);
		VERIFY(v.at(2) == 20);
	}
	{
		Vector const v{1,2,3};
		VERIFY(v.at(0) == 1);
		VERIFY(v.at(1) == 2);
		VERIFY(v.at(2) == 3);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, AtTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());

	{
		hamon::vector<int> v{1,2,3};
		EXPECT_EQ(1, v.at(0));
		EXPECT_EQ(2, v.at(1));
		EXPECT_EQ(3, v.at(2));
#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW((void)v.at(3), hamon::out_of_range);
#endif
	}
	{
		hamon::vector<int> const v{1,2,3};
		EXPECT_EQ(1, v.at(0));
		EXPECT_EQ(2, v.at(1));
		EXPECT_EQ(3, v.at(2));
#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW((void)v.at(3), hamon::out_of_range);
#endif
	}
}

}	// namespace at_test

}	// namespace hamon_vector_test
