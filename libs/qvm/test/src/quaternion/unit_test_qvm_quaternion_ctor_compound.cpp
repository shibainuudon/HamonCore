/**
 *	@file	unit_test_qvm_quaternion_ctor_compound.cpp
 *
 *	@brief	実部と虚部を受け取る quaternion のコンストラクタのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace quaternion_test
{

TYPED_TEST(QuaternionTest, CtorCompoundTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;
	using vector2 = hamon::qvm::vector<T, 2>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(!std::is_constructible<quaternion, vector2>::value, "");
	static_assert(!std::is_constructible<quaternion, vector2, T>::value, "");
	static_assert(!std::is_constructible<quaternion, T, vector2>::value, "");
	static_assert(!std::is_constructible<quaternion, vector2, T, T>::value, "");
	static_assert(!std::is_constructible<quaternion, T, vector2, T>::value, "");
	static_assert(!std::is_constructible<quaternion, T, T, vector2>::value, "");

	static_assert(!std::is_constructible<quaternion, vector3>::value, "");
	static_assert( std::is_constructible<quaternion, vector3, T>::value, "");
	static_assert(!std::is_constructible<quaternion, T, vector3>::value, "");
	static_assert(!std::is_constructible<quaternion, vector3, T, T>::value, "");
	static_assert(!std::is_constructible<quaternion, T, vector3, T>::value, "");
	static_assert(!std::is_constructible<quaternion, T, T, vector3>::value, "");

	static_assert(!std::is_constructible<quaternion, vector4>::value, "");

	static_assert( std::is_nothrow_constructible<quaternion, vector3, T>::value, "");

	static_assert( hamon::is_implicitly_constructible<quaternion, vector3, T>::value, "");

	{
		HAMON_CONSTEXPR vector3 const q1(1, 2, 3);
		HAMON_CONSTEXPR quaternion const q2(q1, 4);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, q2[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, q2[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, q2[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, q2[3]);
	}
	{
		HAMON_CONSTEXPR vector3 const q1 { 2, 3, 4 };
		HAMON_CONSTEXPR quaternion const q2 { q1, 5 };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, q2[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, q2[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, q2[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, q2[3]);
	}
	{
		HAMON_CONSTEXPR vector3 const q1(3, 4, 5);
		HAMON_CONSTEXPR quaternion const q2 = {q1, 6};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, q2[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, q2[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, q2[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, q2[3]);
	}
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
