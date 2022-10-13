/**
 *	@file	unit_test_qvm_vector_vector_cat.cpp
 *
 *	@brief	vector_catのテスト
 */

#include <hamon/qvm/vector.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"
#include <type_traits>
#include <array>

namespace hamon_qvm_test
{

namespace vector_test
{

TYPED_TEST(VectorTest, VectorCatTest)
{
	using T = TypeParam;
	using vector1 = hamon::qvm::vector<T, 1>;
	using vector2 = hamon::qvm::vector<T, 2>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;
	using vector5 = hamon::qvm::vector<T, 5>;
	using vector6 = hamon::qvm::vector<T, 6>;

	{
		HAMON_CONSTEXPR auto const v =
			hamon::qvm::vector_cat(vector1{3});
		static_assert(std::is_same<decltype(v), const vector1>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v[0]);
	}
	{
		HAMON_CONSTEXPR auto const v =
			hamon::qvm::vector_cat(vector2{1, 2}, vector1{3});
		static_assert(std::is_same<decltype(v), const vector3>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v[2]);
	}
	{
		HAMON_CONSTEXPR auto const v =
			hamon::qvm::vector_cat(vector1{4}, vector3{5, 6, 7});
		static_assert(std::is_same<decltype(v), const vector4>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, v[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7, v[3]);
	}
	{
		HAMON_CONSTEXPR auto const v =
			hamon::qvm::vector_cat(vector2{1, 2}, vector3{3, 4, 5});
		static_assert(std::is_same<decltype(v), const vector5>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, v[3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v[4]);
	}
	{
		HAMON_CONSTEXPR auto const v =
			hamon::qvm::vector_cat(vector1{1}, vector2{2, 3}, vector3{4, 5, 6});
		static_assert(std::is_same<decltype(v), const vector6>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, v[3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v[4]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, v[5]);
	}
	{
		HAMON_CONSTEXPR T const a[] = { 2 };
		HAMON_CONSTEXPR auto const v = hamon::qvm::vector_cat(a);
		static_assert(std::is_same<decltype(v), const vector1>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v[0]);
	}
	{
		HAMON_CONSTEXPR T const a1[] = { 1, 2 };
		HAMON_CONSTEXPR T const a2[] = { 3, 4, 5 };
		HAMON_CONSTEXPR auto const v = hamon::qvm::vector_cat(a1, a2);
		static_assert(std::is_same<decltype(v), const vector5>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, v[3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v[4]);
	}
	{
		HAMON_CONSTEXPR T const a1[] = { 1, 2, 3 };
		HAMON_CONSTEXPR T const a2[] = { 4, 5 };
		HAMON_CONSTEXPR T const a3[] = { 6 };
		HAMON_CONSTEXPR auto const v = hamon::qvm::vector_cat(a1, a2, a3);
		static_assert(std::is_same<decltype(v), const vector6>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, v[3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v[4]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, v[5]);
	}
	{
		HAMON_CONSTEXPR T const a[] = { 11 };
		HAMON_CONSTEXPR auto const v = hamon::qvm::vector_cat(a, vector2{12, 13});
		static_assert(std::is_same<decltype(v), const vector3>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, v[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, v[2]);
	}
	{
		HAMON_CONSTEXPR T const a[] = { 11, 12 };
		HAMON_CONSTEXPR auto const v = hamon::qvm::vector_cat(vector3{13, 14, 15}, a);
		static_assert(std::is_same<decltype(v), const vector5>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, v[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, v[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, v[3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, v[4]);
	}
	{
		HAMON_CXX14_CONSTEXPR std::array<T, 1> const a = { 2 };
		HAMON_CXX14_CONSTEXPR auto const v = hamon::qvm::vector_cat(a);
		static_assert(std::is_same<decltype(v), const vector1>::value, "");
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(2, v[0]);
	}
	{
		HAMON_CXX14_CONSTEXPR std::array<T, 2> const a1 = { 10, 11 };
		HAMON_CXX14_CONSTEXPR T const a2[] = { 12, 13, 14 };
		HAMON_CXX14_CONSTEXPR auto const v = hamon::qvm::vector_cat(a1, a2, vector2{15, 16});
		static_assert(std::is_same<decltype(v), const hamon::qvm::vector<T, 7>>::value, "");
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, v[0]);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(11, v[1]);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(12, v[2]);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(13, v[3]);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(14, v[4]);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(15, v[5]);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(16, v[6]);
	}
}

}	// namespace vector_test

}	// namespace hamon_qvm_test
