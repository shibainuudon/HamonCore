/**
 *	@file	unit_test_qvm_vector_mul_scalar.cpp
 *
 *	@brief	スカラー積のテスト
 */

#include <hamon/qvm/vector/vector.hpp>
#include <hamon/qvm/vector/operators.hpp>
#include <hamon/type_traits/is_same.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"
#include <utility>

namespace hamon_qvm_test
{

namespace vector_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector2MulScalarTest()
{
	using vector2  = hamon::qvm::vector<T, 2>;
	using vector2i = hamon::qvm::vector<int, 2>;
	using vector2f = hamon::qvm::vector<float, 2>;

	static_assert(hamon::is_same<decltype(std::declval<vector2&>()  *= T{}),     vector2&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector2&>()  *= int{}),   vector2&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector2&>()  *= float{}), vector2&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector2i&>() *= T{}),     vector2i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector2i&>() *= int{}),   vector2i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector2i&>() *= float{}), vector2i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector2f&>() *= T{}),     vector2f&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector2f&>() *= int{}),   vector2f&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector2f&>() *= float{}), vector2f&>::value, "");

	// vector2 *= スカラー
	{
		vector2 v(2, 3);
		{
			auto t = (v *= 4);
			static_assert(hamon::is_same<decltype(t), vector2>::value, "");
			VERIFY(v == vector2(8, 12));
			VERIFY(t == v);
		}
		{
			auto t = (v *= 0.5);
			static_assert(hamon::is_same<decltype(t), vector2>::value, "");
			VERIFY(v == vector2(4, 6));
			VERIFY(t == v);
		}
		{
			auto t = (v *= 0.5f);
			static_assert(hamon::is_same<decltype(t), vector2>::value, "");
			VERIFY(v == vector2(2, 3));
			VERIFY(t == v);
		}
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector3MulScalarTest()
{
	using vector3  = hamon::qvm::vector<T, 3>;
	using vector3i = hamon::qvm::vector<int, 3>;
	using vector3f = hamon::qvm::vector<float, 3>;

	static_assert(hamon::is_same<decltype(std::declval<vector3&>()  *= T{}),     vector3&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3&>()  *= int{}),   vector3&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3&>()  *= float{}), vector3&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3i&>() *= T{}),     vector3i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3i&>() *= int{}),   vector3i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3i&>() *= float{}), vector3i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3f&>() *= T{}),     vector3f&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3f&>() *= int{}),   vector3f&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3f&>() *= float{}), vector3f&>::value, "");

	// vector3 *= スカラー
	{
		vector3 v(2, 3, 4);
		{
			auto t = (v *= 4);
			static_assert(hamon::is_same<decltype(t), vector3>::value, "");
			VERIFY(v == vector3(8, 12, 16));
			VERIFY(t == v);
		}
		{
			auto t = (v *= 0.5);
			static_assert(hamon::is_same<decltype(t), vector3>::value, "");
			VERIFY(v == vector3(4, 6, 8));
			VERIFY(t == v);
		}
		{
			auto t = (v *= 0.5f);
			static_assert(hamon::is_same<decltype(t), vector3>::value, "");
			VERIFY(v == vector3(2, 3, 4));
			VERIFY(t == v);
		}
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector4MulScalarTest()
{
	using vector4  = hamon::qvm::vector<T, 4>;
	using vector4i = hamon::qvm::vector<int, 4>;
	using vector4f = hamon::qvm::vector<float, 4>;

	static_assert(hamon::is_same<decltype(std::declval<vector4&>()  *= T{}),     vector4&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector4&>()  *= int{}),   vector4&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector4&>()  *= float{}), vector4&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector4i&>() *= T{}),     vector4i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector4i&>() *= int{}),   vector4i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector4i&>() *= float{}), vector4i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector4f&>() *= T{}),     vector4f&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector4f&>() *= int{}),   vector4f&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector4f&>() *= float{}), vector4f&>::value, "");

	// vector4 *= スカラー
	{
		vector4 v(2, 3, 4, 5);
		{
			auto t = (v *= 4);
			static_assert(hamon::is_same<decltype(t), vector4>::value, "");
			VERIFY(v == vector4(8, 12, 16, 20));
			VERIFY(t == v);
		}
		{
			auto t = (v *= 0.5);
			static_assert(hamon::is_same<decltype(t), vector4>::value, "");
			VERIFY(v == vector4(4, 6, 8, 10));
			VERIFY(t == v);
		}
		{
			auto t = (v *= 0.5f);
			static_assert(hamon::is_same<decltype(t), vector4>::value, "");
			VERIFY(v == vector4(2, 3, 4, 5));
			VERIFY(t == v);
		}
	}

	return true;
}

TYPED_TEST(VectorTest, MulScalarTest)
{
	using T = TypeParam;
	using vector2  = hamon::qvm::vector<T, 2>;
	using vector2i = hamon::qvm::vector<int, 2>;
	using vector2f = hamon::qvm::vector<float, 2>;
	using vector3  = hamon::qvm::vector<T, 3>;
	using vector3i = hamon::qvm::vector<int, 3>;
	using vector3f = hamon::qvm::vector<float, 3>;
	using vector4  = hamon::qvm::vector<T, 4>;
	using vector4i = hamon::qvm::vector<int, 4>;
	using vector4f = hamon::qvm::vector<float, 4>;

	static_assert(hamon::is_same<decltype(vector2{}  * T{}),     vector2>::value, "");
	static_assert(hamon::is_same<decltype(vector2{}  * int{}),   vector2>::value, "");
	static_assert(hamon::is_same<decltype(vector2i{} * int{}),   vector2i>::value, "");
	static_assert(hamon::is_same<decltype(vector2i{} * float{}), vector2f>::value, "");
	static_assert(hamon::is_same<decltype(vector2f{} * int{}),   vector2f>::value, "");
	static_assert(hamon::is_same<decltype(vector2f{} * float{}), vector2f>::value, "");

	static_assert(hamon::is_same<decltype(vector3{}  * T{}),     vector3>::value, "");
	static_assert(hamon::is_same<decltype(vector3{}  * int{}),   vector3>::value, "");
	static_assert(hamon::is_same<decltype(vector3i{} * int{}),   vector3i>::value, "");
	static_assert(hamon::is_same<decltype(vector3i{} * float{}), vector3f>::value, "");
	static_assert(hamon::is_same<decltype(vector3f{} * int{}),   vector3f>::value, "");
	static_assert(hamon::is_same<decltype(vector3f{} * float{}), vector3f>::value, "");

	static_assert(hamon::is_same<decltype(vector4{}  * T{}),     vector4>::value, "");
	static_assert(hamon::is_same<decltype(vector4{}  * int{}),   vector4>::value, "");
	static_assert(hamon::is_same<decltype(vector4i{} * int{}),   vector4i>::value, "");
	static_assert(hamon::is_same<decltype(vector4i{} * float{}), vector4f>::value, "");
	static_assert(hamon::is_same<decltype(vector4f{} * int{}),   vector4f>::value, "");
	static_assert(hamon::is_same<decltype(vector4f{} * float{}), vector4f>::value, "");

	static_assert(hamon::is_same<decltype(T{}     * vector2{}),  vector2>::value, "");
	static_assert(hamon::is_same<decltype(int{}   * vector2{}),  vector2>::value, "");
	static_assert(hamon::is_same<decltype(int{}   * vector2i{}), vector2i>::value, "");
	static_assert(hamon::is_same<decltype(float{} * vector2i{}), vector2f>::value, "");
	static_assert(hamon::is_same<decltype(int{}   * vector2f{}), vector2f>::value, "");
	static_assert(hamon::is_same<decltype(float{} * vector2f{}), vector2f>::value, "");

	static_assert(hamon::is_same<decltype(T{}     * vector3{}),  vector3>::value, "");
	static_assert(hamon::is_same<decltype(int{}   * vector3{}),  vector3>::value, "");
	static_assert(hamon::is_same<decltype(int{}   * vector3i{}), vector3i>::value, "");
	static_assert(hamon::is_same<decltype(float{} * vector3i{}), vector3f>::value, "");
	static_assert(hamon::is_same<decltype(int{}   * vector3f{}), vector3f>::value, "");
	static_assert(hamon::is_same<decltype(float{} * vector3f{}), vector3f>::value, "");

	static_assert(hamon::is_same<decltype(T{}     * vector4{}),  vector4>::value, "");
	static_assert(hamon::is_same<decltype(int{}   * vector4{}),  vector4>::value, "");
	static_assert(hamon::is_same<decltype(int{}   * vector4i{}), vector4i>::value, "");
	static_assert(hamon::is_same<decltype(float{} * vector4i{}), vector4f>::value, "");
	static_assert(hamon::is_same<decltype(int{}   * vector4f{}), vector4f>::value, "");
	static_assert(hamon::is_same<decltype(float{} * vector4f{}), vector4f>::value, "");

	// vector2 * スカラー -> vector2
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2(-3, 42) * -4,   vector2(12, -168));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2( 4, 6)  * 2.5f, vector2(10, 15));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2(-3, 42) * -4.0, vector2(12, -168));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2( 4, 6)  * 2.5l, vector2(10, 15));

	// スカラー * vector2 -> vector2
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5    * vector2(7, -8), vector2(35, -40));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.5f * vector2(4, -6), vector2(-6, 9));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5.0  * vector2(7, -8), vector2(35, -40));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.5l * vector2(4, -6), vector2(-6, 9));

	// vector3 * スカラー -> vector3
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-3, 42, 5) * -4,   vector3(12, -168, -20));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 4,  6, 2) * 2.5f, vector3(10, 15, 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-3, 42, 5) * -4.0, vector3(12, -168, -20));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 4,  6, 2) * 2.5l, vector3(10, 15, 5));

	// スカラー * vector3 -> vector3
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5    * vector3(7, -8, 9),  vector3(35, -40, 45));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.5f * vector3(4, -6, -2), vector3(-6, 9, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5.0  * vector3(7, -8, 9),  vector3(35, -40, 45));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.5l * vector3(4, -6, -2), vector3(-6, 9, 3));

	// vector4 * スカラー -> vector4
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-3, 42, 5,   4) * -4,   vector4(12, -168, -20, -16));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 4,  6, 2, -10) * 2.5f, vector4(10, 15, 5, -25));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 4,  6, 2, -10) * 2.5,  vector4(10, 15, 5, -25));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 4,  6, 2, -10) * 2.5l, vector4(10, 15, 5, -25));

	// スカラー * vector4 -> vector4
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5    * vector4(7, -8,  9, 2), vector4(35, -40, 45, 10));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.5f * vector4(4, -6, -2, 8), vector4(-6, 9, 3, -12));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.5  * vector4(4, -6, -2, 8), vector4(-6, 9, 3, -12));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.5l * vector4(4, -6, -2, 8), vector4(-6, 9, 3, -12));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector2MulScalarTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector3MulScalarTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector4MulScalarTest<T>());
}

#undef VERIFY

}	// namespace vector_test

}	// namespace hamon_qvm_test
