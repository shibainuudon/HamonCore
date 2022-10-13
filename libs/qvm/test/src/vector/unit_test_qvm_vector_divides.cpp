/**
 *	@file	unit_test_qvm_vector_divides.cpp
 *
 *	@brief	operator/のテスト
 */

#include <hamon/qvm/vector.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace vector_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector2DividesTest()
{
	using vector2  = hamon::qvm::vector<T, 2>;
	using vector2i = hamon::qvm::vector<int, 2>;
	using vector2f = hamon::qvm::vector<float, 2>;

	static_assert(std::is_same<decltype(std::declval<vector2&>()  /= vector2{}),  vector2&>::value, "");
	static_assert(std::is_same<decltype(std::declval<vector2&>()  /= vector2i{}), vector2&>::value, "");
	static_assert(std::is_same<decltype(std::declval<vector2&>()  /= vector2f{}), vector2&>::value, "");
	static_assert(std::is_same<decltype(std::declval<vector2i&>() /= vector2{}),  vector2i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<vector2i&>() /= vector2i{}), vector2i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<vector2i&>() /= vector2f{}), vector2i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<vector2f&>() /= vector2{}),  vector2f&>::value, "");
	static_assert(std::is_same<decltype(std::declval<vector2f&>() /= vector2i{}), vector2f&>::value, "");
	static_assert(std::is_same<decltype(std::declval<vector2f&>() /= vector2f{}), vector2f&>::value, "");

	// vector2 /= vector2
	{
		vector2 v{6, 12};
		VERIFY(v == vector2(6, 12));
		{
			auto t = (v /= vector2(2, 3));
			static_assert(std::is_same<decltype(t), vector2>::value, "");
			VERIFY(v == vector2(3, 4));
			VERIFY(v == t);
		}
		{
			auto t = (v /= vector2i(3, 2));
			static_assert(std::is_same<decltype(t), vector2>::value, "");
			VERIFY(v == vector2(1, 2));
			VERIFY(v == t);
		}
		{
			auto t = (v /= vector2f(0.5, 0.25));
			static_assert(std::is_same<decltype(t), vector2>::value, "");
			VERIFY(v == vector2(2, 8));
			VERIFY(v == t);
		}
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector3DividesTest()
{
	using vector3  = hamon::qvm::vector<T, 3>;
	using vector3i = hamon::qvm::vector<int, 3>;
	using vector3f = hamon::qvm::vector<float, 3>;

	static_assert(std::is_same<decltype(std::declval<vector3&>()  /= vector3{}),  vector3&>::value, "");
	static_assert(std::is_same<decltype(std::declval<vector3&>()  /= vector3i{}), vector3&>::value, "");
	static_assert(std::is_same<decltype(std::declval<vector3&>()  /= vector3f{}), vector3&>::value, "");
	static_assert(std::is_same<decltype(std::declval<vector3i&>() /= vector3{}),  vector3i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<vector3i&>() /= vector3i{}), vector3i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<vector3i&>() /= vector3f{}), vector3i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<vector3f&>() /= vector3{}),  vector3f&>::value, "");
	static_assert(std::is_same<decltype(std::declval<vector3f&>() /= vector3i{}), vector3f&>::value, "");
	static_assert(std::is_same<decltype(std::declval<vector3f&>() /= vector3f{}), vector3f&>::value, "");

	// vector3 /= vector3
	{
		vector3 v{6, 12, -16};
		VERIFY(v == vector3(6, 12, -16));
		{
			auto t = (v /= vector3(2, 3, -4));
			static_assert(std::is_same<decltype(t), vector3>::value, "");
			VERIFY(v == vector3(3, 4, 4));
			VERIFY(v == t);
		}
		{
			auto t = (v /= vector3i(3, 2, 4));
			static_assert(std::is_same<decltype(t), vector3>::value, "");
			VERIFY(v == vector3(1, 2, 1));
			VERIFY(v == t);
		}
		{
			auto t = (v /= vector3f(0.5, 0.25, 0.125));
			static_assert(std::is_same<decltype(t), vector3>::value, "");
			VERIFY(v == vector3(2, 8, 8));
			VERIFY(v == t);
		}
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector4DividesTest()
{
	using vector4  = hamon::qvm::vector<T, 4>;
	using vector4i = hamon::qvm::vector<int, 4>;
	using vector4f = hamon::qvm::vector<float, 4>;

	static_assert(std::is_same<decltype(std::declval<vector4&>()  /= vector4{}),  vector4&>::value, "");
	static_assert(std::is_same<decltype(std::declval<vector4&>()  /= vector4i{}), vector4&>::value, "");
	static_assert(std::is_same<decltype(std::declval<vector4&>()  /= vector4f{}), vector4&>::value, "");
	static_assert(std::is_same<decltype(std::declval<vector4i&>() /= vector4{}),  vector4i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<vector4i&>() /= vector4i{}), vector4i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<vector4i&>() /= vector4f{}), vector4i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<vector4f&>() /= vector4{}),  vector4f&>::value, "");
	static_assert(std::is_same<decltype(std::declval<vector4f&>() /= vector4i{}), vector4f&>::value, "");
	static_assert(std::is_same<decltype(std::declval<vector4f&>() /= vector4f{}), vector4f&>::value, "");

	// vector4 /= vector4
	{
		vector4 v{6, 12, -16, -10};
		VERIFY(v == vector4(6, 12, -16, -10));
		{
			auto t = (v /= vector4(2, 3, -4, 5));
			static_assert(std::is_same<decltype(t), vector4>::value, "");
			VERIFY(v == vector4(3, 4, 4, -2));
			VERIFY(v == t);
		}
		{
			auto t = (v /= vector4i(3, 2, 4, 1));
			static_assert(std::is_same<decltype(t), vector4>::value, "");
			VERIFY(v == vector4(1, 2, 1, -2));
			VERIFY(v == t);
		}
		{
			auto t = (v /= vector4f(0.5, 0.25, 0.125, -1.0));
			static_assert(std::is_same<decltype(t), vector4>::value, "");
			VERIFY(v == vector4(2, 8, 8, 2));
			VERIFY(v == t);
		}
	}

	return true;
}

TYPED_TEST(VectorTest, DividesTest)
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

	static_assert(std::is_same<decltype(vector2{}  / vector2{}),  vector2>::value, "");
	static_assert(std::is_same<decltype(vector2{}  / vector2i{}), vector2>::value, "");
	static_assert(std::is_same<decltype(vector2i{} / vector2i{}), vector2i>::value, "");
	static_assert(std::is_same<decltype(vector2i{} / vector2f{}), vector2f>::value, "");
	static_assert(std::is_same<decltype(vector2f{} / vector2i{}), vector2f>::value, "");
	static_assert(std::is_same<decltype(vector2f{} / vector2f{}), vector2f>::value, "");

	static_assert(std::is_same<decltype(vector3{}  / vector3{}),  vector3>::value, "");
	static_assert(std::is_same<decltype(vector3{}  / vector3i{}), vector3>::value, "");
	static_assert(std::is_same<decltype(vector3i{} / vector3i{}), vector3i>::value, "");
	static_assert(std::is_same<decltype(vector3i{} / vector3f{}), vector3f>::value, "");
	static_assert(std::is_same<decltype(vector3f{} / vector3i{}), vector3f>::value, "");
	static_assert(std::is_same<decltype(vector3f{} / vector3f{}), vector3f>::value, "");

	static_assert(std::is_same<decltype(vector4{}  / vector4{}),  vector4>::value, "");
	static_assert(std::is_same<decltype(vector4{}  / vector4i{}), vector4>::value, "");
	static_assert(std::is_same<decltype(vector4i{} / vector4i{}), vector4i>::value, "");
	static_assert(std::is_same<decltype(vector4i{} / vector4f{}), vector4f>::value, "");
	static_assert(std::is_same<decltype(vector4f{} / vector4i{}), vector4f>::value, "");
	static_assert(std::is_same<decltype(vector4f{} / vector4f{}), vector4f>::value, "");

	// vector2 / vector2 -> vector2
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2 (  8,  9) / vector2 (  2, 3), vector2(4, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2 (-20, 27) / vector2 (-10,-9), vector2(2,-3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2f(-20, 27) / vector2 (-10,-9), vector2(2,-3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2 (-20, 27) / vector2f(-10,-9), vector2(2,-3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2i(-20, 27) / vector2 (-10,-9), vector2(2,-3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2 (-20, 27) / vector2i(-10,-9), vector2(2,-3));

	// vector3 / vector3 -> vector3
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3 (  8,  9, 16) / vector3 (  2, 3, 4), vector3(4, 3, 4));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3 (-20, 27,-32) / vector3 (-10,-9, 8), vector3(2,-3,-4));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3f(-20, 27,-32) / vector3 (-10,-9, 8), vector3(2,-3,-4));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3 (-20, 27,-32) / vector3f(-10,-9, 8), vector3(2,-3,-4));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3i(-20, 27,-32) / vector3 (-10,-9, 8), vector3(2,-3,-4));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3 (-20, 27,-32) / vector3i(-10,-9, 8), vector3(2,-3,-4));

	// vector4 / vector4 -> vector4
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4 (  8,  9, 16, 10) / vector4 (  2, 3, 4, 5), vector4(4, 3, 4, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4 (-20, 27,-32, 35) / vector4 (-10,-9, 8, 7), vector4(2,-3,-4, 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4f(-20, 27,-32, 35) / vector4 (-10,-9, 8, 7), vector4(2,-3,-4, 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4 (-20, 27,-32, 35) / vector4f(-10,-9, 8, 7), vector4(2,-3,-4, 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4i(-20, 27,-32, 35) / vector4 (-10,-9, 8, 7), vector4(2,-3,-4, 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4 (-20, 27,-32, 35) / vector4i(-10,-9, 8, 7), vector4(2,-3,-4, 5));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector2DividesTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector3DividesTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector4DividesTest<T>());
}

#undef VERIFY

}	// namespace vector_test

}	// namespace hamon_qvm_test
