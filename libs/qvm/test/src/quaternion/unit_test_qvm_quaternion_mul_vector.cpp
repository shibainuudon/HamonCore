/**
 *	@file	unit_test_qvm_quaternion_mul_vector.cpp
 *
 *	@brief	ベクトルとクォータニオンの積のテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include <hamon/qvm/vector.hpp>
#include <hamon/type_traits/is_same.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"
#include <utility>

namespace hamon_qvm_test
{

namespace quaternion_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool MulVector3Test()
{
	using quaternion  = hamon::qvm::quaternion<T>;
	using quaternioni = hamon::qvm::quaternion<int>;
	using quaternionf = hamon::qvm::quaternion<float>;
	using vector3 = hamon::qvm::vector<T, 3>;

	static_assert(hamon::is_same<decltype(std::declval<vector3&>() *= quaternion{}),  vector3&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3&>() *= quaternioni{}), vector3&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3&>() *= quaternionf{}), vector3&>::value, "");

	// vector3 *= quaternion
	{
		vector3 v1 { 1, 2, 3 };
		{
			auto t = (v1 *= quaternion::identity());
			VERIFY(v1 == vector3{ 1, 2, 3 });
			VERIFY(v1 == t);
		}
		{
			auto t = (v1 *= quaternion(3, 4, 5, 6));
			VERIFY(v1 == vector3{ 166, 132, 242 });
			VERIFY(v1 == t);
		}
		{
			auto t = (v1 *= quaternioni(1, 2, 3, 4));
			VERIFY(v1 == vector3{ 3348, 6936, 5820 });
			VERIFY(v1 == t);
		}
	}

	return true;
}

TYPED_TEST(QuaternionTest, MulVectorTest)
{
	using T = TypeParam;
	using quaternion  = hamon::qvm::quaternion<T>;
	using quaternioni = hamon::qvm::quaternion<int>;
	using quaternionf = hamon::qvm::quaternion<float>;
	using vector3  = hamon::qvm::vector<T, 3>;
	using vector3i = hamon::qvm::vector<int, 3>;
	using vector3f = hamon::qvm::vector<float, 3>;

	static_assert(hamon::is_same<decltype(vector3{}  * quaternion{}),  vector3>::value, "");
	static_assert(hamon::is_same<decltype(vector3{}  * quaternioni{}), vector3>::value, "");
	static_assert(hamon::is_same<decltype(vector3{}  * quaternionf{}), vector3>::value, "");
	static_assert(hamon::is_same<decltype(vector3i{} * quaternion{}),  vector3i>::value, "");
	static_assert(hamon::is_same<decltype(vector3i{} * quaternioni{}), vector3i>::value, "");
	static_assert(hamon::is_same<decltype(vector3i{} * quaternionf{}), vector3i>::value, "");
	static_assert(hamon::is_same<decltype(vector3f{} * quaternion{}),  vector3f>::value, "");
	static_assert(hamon::is_same<decltype(vector3f{} * quaternioni{}), vector3f>::value, "");
	static_assert(hamon::is_same<decltype(vector3f{} * quaternionf{}), vector3f>::value, "");

	// vector3 * quaternion -> vector3
	{
		HAMON_CONSTEXPR vector3 const v1 { 1, 2, 3 };
		HAMON_CONSTEXPR auto const v2 = v1 * quaternion::identity();
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v1, v2);
	}
	{
		HAMON_CONSTEXPR auto const v = vector3{3, 4, 5} * quaternion{3, 1, 4, 1};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(101, -40, 157), v);
	}
	{
		HAMON_CONSTEXPR auto const v = vector3{3, 4, 5} * quaternioni{3, 1, 4, 1};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(101, -40, 157), v);
	}

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulVector3Test<T>());
}

#undef VERIFY

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
