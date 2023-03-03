/**
 *	@file	unit_test_qvm_quaternion_multiplies.cpp
 *
 *	@brief	operator*のテスト
 */

#include <hamon/qvm/quaternion.hpp>
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
inline HAMON_CXX14_CONSTEXPR bool MultipliesTest()
{
	using quaternion  = hamon::qvm::quaternion<T>;
	using quaternioni = hamon::qvm::quaternion<int>;
	using quaternionf = hamon::qvm::quaternion<float>;

	static_assert(hamon::is_same<decltype(std::declval<quaternion&>()  *= quaternion{}),  quaternion&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<quaternion&>()  *= quaternioni{}), quaternion&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<quaternion&>()  *= quaternionf{}), quaternion&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<quaternioni&>() *= quaternion{}),  quaternioni&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<quaternioni&>() *= quaternioni{}), quaternioni&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<quaternioni&>() *= quaternionf{}), quaternioni&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<quaternionf&>() *= quaternion{}),  quaternionf&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<quaternionf&>() *= quaternioni{}), quaternionf&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<quaternionf&>() *= quaternionf{}), quaternionf&>::value, "");

	// quaternion *= quaternion
	{
		quaternion q(2,3,4, 5);
		{
			auto t = (q *= quaternion(3,4, 5, 6));
			static_assert(hamon::is_same<decltype(t), quaternion>::value, "");
			VERIFY(quaternion(26,40,48, -8) == q);
			VERIFY(t == q);
		}
		{
			auto t = (q *= quaternionf(1,2,3,4));
			static_assert(hamon::is_same<decltype(t), quaternion>::value, "");
			VERIFY(quaternion(120,114,180, -282) == q);
			VERIFY(t == q);
		}
		{
			auto t = (q *= quaternioni(3,1,4,1));
			static_assert(hamon::is_same<decltype(t), quaternion>::value, "");
			VERIFY(quaternion(-450,-108,-1170,-1476) == q);
			VERIFY(t == q);
		}
	}

	return true;
}

TYPED_TEST(QuaternionTest, MultipliesTest)
{
	using T = TypeParam;
	using quaternion  = hamon::qvm::quaternion<T>;
	using quaternioni = hamon::qvm::quaternion<int>;
	using quaternionf = hamon::qvm::quaternion<float>;

	static_assert(hamon::is_same<decltype(quaternion{}  * quaternion{}),  quaternion>::value, "");
	static_assert(hamon::is_same<decltype(quaternion{}  * quaternioni{}), quaternion>::value, "");
	static_assert(hamon::is_same<decltype(quaternioni{} * quaternioni{}), quaternioni>::value, "");
	static_assert(hamon::is_same<decltype(quaternioni{} * quaternionf{}), quaternionf>::value, "");
	static_assert(hamon::is_same<decltype(quaternionf{} * quaternioni{}), quaternionf>::value, "");
	static_assert(hamon::is_same<decltype(quaternionf{} * quaternionf{}), quaternionf>::value, "");

	// quaternion * quaternion -> quaternion
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion (1,2,3,4) * quaternion (5,-6,7,8), quaternion(60,0,36,18));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion (1,2,3,4) * quaternionf(5,-6,7,8), quaternion(60,0,36,18));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternionf(1,2,3,4) * quaternion (5,-6,7,8), quaternion(60,0,36,18));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion (1,2,3,4) * quaternioni(5,-6,7,8), quaternion(60,0,36,18));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternioni(1,2,3,4) * quaternion (5,-6,7,8), quaternion(60,0,36,18));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(
		quaternion(1,2,3,4) * quaternion(5,6,-7,8) * quaternion(9,10,11,-12),
		quaternion(1134,-412,-106,-928));

	// identity * identity = identity
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion::identity() * quaternion::identity(), quaternion::identity());

	// ii = jj = kk = ijk = -1
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(1,0,0,0) * quaternion(1,0,0,0), quaternion(0,0,0,-1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(0,1,0,0) * quaternion(0,1,0,0), quaternion(0,0,0,-1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(0,0,1,0) * quaternion(0,0,1,0), quaternion(0,0,0,-1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(1,0,0,0) * quaternion(0,1,0,0) * quaternion(0,0,1,0), quaternion(0,0,0,-1));

	// ij = -ji = k
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(1,0,0,0) * quaternion(0,1,0,0), quaternion(0,0,1,0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(0,-1,0,0) * quaternion(1,0,0,0), quaternion(0,0,1,0));

	// jk = -kj = i
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(0,1,0,0) * quaternion(0,0,1,0), quaternion(1,0,0,0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(0,0,-1,0) * quaternion(0,1,0,0), quaternion(1,0,0,0));

	// ki = -ik = j
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(0,0,1,0) * quaternion(1,0,0,0), quaternion(0,1,0,0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(-1,0,0,0) * quaternion(0,0,1,0), quaternion(0,1,0,0));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MultipliesTest<T>());
}

#undef VERIFY

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
