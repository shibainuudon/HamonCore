/**
 *	@file	unit_test_qvm_vector_div_scalar.cpp
 *
 *	@brief	スカラー商のテスト
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
inline HAMON_CXX14_CONSTEXPR bool Vector2DivScalarTest()
{
	using vector2  = hamon::qvm::vector<T, 2>;
	using vector2i = hamon::qvm::vector<int, 2>;
	using vector2f = hamon::qvm::vector<float, 2>;

	static_assert(hamon::is_same<decltype(std::declval<vector2&>()  /= T{}),     vector2&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector2&>()  /= int{}),   vector2&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector2&>()  /= float{}), vector2&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector2i&>() /= T{}),     vector2i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector2i&>() /= int{}),   vector2i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector2i&>() /= float{}), vector2i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector2f&>() /= T{}),     vector2f&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector2f&>() /= int{}),   vector2f&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector2f&>() /= float{}), vector2f&>::value, "");

	// vector2 /= スカラー
	{
		vector2 v(2, 4);
		{
			auto t = (v /= 2);
			static_assert(hamon::is_same<decltype(t), vector2>::value, "");
			VERIFY(v == vector2(1, 2));
			VERIFY(t == v);
		}
		{
			auto t = (v /= 0.5);
			static_assert(hamon::is_same<decltype(t), vector2>::value, "");
			VERIFY(v == vector2(2, 4));
			VERIFY(t == v);
		}
		{
			auto t = (v /= 0.5f);
			static_assert(hamon::is_same<decltype(t), vector2>::value, "");
			VERIFY(v == vector2(4, 8));
			VERIFY(t == v);
		}
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector3DivScalarTest()
{
	using vector3  = hamon::qvm::vector<T, 3>;
	using vector3i = hamon::qvm::vector<int, 3>;
	using vector3f = hamon::qvm::vector<float, 3>;

	static_assert(hamon::is_same<decltype(std::declval<vector3&>()  /= T{}),     vector3&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3&>()  /= int{}),   vector3&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3&>()  /= float{}), vector3&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3i&>() /= T{}),     vector3i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3i&>() /= int{}),   vector3i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3i&>() /= float{}), vector3i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3f&>() /= T{}),     vector3f&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3f&>() /= int{}),   vector3f&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3f&>() /= float{}), vector3f&>::value, "");

	// vector3 /= スカラー
	{
		vector3 v(2, 4, 6);
		{
			auto t = (v /= 2);
			static_assert(hamon::is_same<decltype(t), vector3>::value, "");
			VERIFY(v == vector3(1, 2, 3));
			VERIFY(t == v);
		}
		{
			auto t = (v /= 0.5);
			static_assert(hamon::is_same<decltype(t), vector3>::value, "");
			VERIFY(v == vector3(2, 4, 6));
			VERIFY(t == v);
		}
		{
			auto t = (v /= 0.5f);
			static_assert(hamon::is_same<decltype(t), vector3>::value, "");
			VERIFY(v == vector3(4, 8, 12));
			VERIFY(t == v);
		}
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector4DivScalarTest()
{
	using vector4  = hamon::qvm::vector<T, 4>;
	using vector4i = hamon::qvm::vector<int, 4>;
	using vector4f = hamon::qvm::vector<float, 4>;

	static_assert(hamon::is_same<decltype(std::declval<vector4&>()  /= T{}),     vector4&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector4&>()  /= int{}),   vector4&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector4&>()  /= float{}), vector4&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector4i&>() /= T{}),     vector4i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector4i&>() /= int{}),   vector4i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector4i&>() /= float{}), vector4i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector4f&>() /= T{}),     vector4f&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector4f&>() /= int{}),   vector4f&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector4f&>() /= float{}), vector4f&>::value, "");

	// vector4 /= スカラー
	{
		vector4 v(2, 4, 6, 8);
		{
			auto t = (v /= 2);
			static_assert(hamon::is_same<decltype(t), vector4>::value, "");
			VERIFY(v == vector4(1, 2, 3, 4));
			VERIFY(t == v);
		}
		{
			auto t = (v /= 0.5);
			static_assert(hamon::is_same<decltype(t), vector4>::value, "");
			VERIFY(v == vector4(2, 4, 6, 8));
			VERIFY(t == v);
		}
		{
			auto t = (v /= 0.5f);
			static_assert(hamon::is_same<decltype(t), vector4>::value, "");
			VERIFY(v == vector4(4, 8, 12, 16));
			VERIFY(t == v);
		}
	}

	return true;
}

TYPED_TEST(VectorTest, DivScalarTest)
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

	static_assert(hamon::is_same<decltype(vector2{}  / T{}),     vector2>::value, "");
	static_assert(hamon::is_same<decltype(vector2{}  / int{}),   vector2>::value, "");
	static_assert(hamon::is_same<decltype(vector2i{} / int{}),   vector2i>::value, "");
	static_assert(hamon::is_same<decltype(vector2i{} / float{}), vector2f>::value, "");
	static_assert(hamon::is_same<decltype(vector2f{} / int{}),   vector2f>::value, "");
	static_assert(hamon::is_same<decltype(vector2f{} / float{}), vector2f>::value, "");

	static_assert(hamon::is_same<decltype(vector3{}  / T{}),     vector3>::value, "");
	static_assert(hamon::is_same<decltype(vector3{}  / int{}),   vector3>::value, "");
	static_assert(hamon::is_same<decltype(vector3i{} / int{}),   vector3i>::value, "");
	static_assert(hamon::is_same<decltype(vector3i{} / float{}), vector3f>::value, "");
	static_assert(hamon::is_same<decltype(vector3f{} / int{}),   vector3f>::value, "");
	static_assert(hamon::is_same<decltype(vector3f{} / float{}), vector3f>::value, "");

	static_assert(hamon::is_same<decltype(vector4{}  / T{}),     vector4>::value, "");
	static_assert(hamon::is_same<decltype(vector4{}  / int{}),   vector4>::value, "");
	static_assert(hamon::is_same<decltype(vector4i{} / int{}),   vector4i>::value, "");
	static_assert(hamon::is_same<decltype(vector4i{} / float{}), vector4f>::value, "");
	static_assert(hamon::is_same<decltype(vector4f{} / int{}),   vector4f>::value, "");
	static_assert(hamon::is_same<decltype(vector4f{} / float{}), vector4f>::value, "");

	// vector2 / スカラー -> vector2
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2(-4, 8) / -4,    vector2(1, -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2(-4, 8) / -4.0f, vector2(1, -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2(-4, 8) / 0.25,  vector2(-16, 32));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2(-4, 8) / 0.25l, vector2(-16, 32));

	// vector3 / スカラー -> vector3
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-4, 8, -12) / -4,    vector3(1, -2, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-4, 8, -12) / -4.0f, vector3(1, -2, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-4, 8, -12) / 0.25,  vector3(-16, 32, -48));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-4, 8, -12) / 0.25l, vector3(-16, 32, -48));

	// vector4 / スカラー -> vector4
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-4, 8, -12, 16) / -4,    vector4(1, -2, 3, -4));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-4, 8, -12, 16) / 0.25f, vector4(-16, 32, -48, 64));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-4, 8, -12, 16) / 0.25,  vector4(-16, 32, -48, 64));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-4, 8, -12, 16) / 0.25l, vector4(-16, 32, -48, 64));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector2DivScalarTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector3DivScalarTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector4DivScalarTest<T>());
}

#undef VERIFY

}	// namespace vector_test

}	// namespace hamon_qvm_test
