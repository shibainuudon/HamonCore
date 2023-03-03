/**
 *	@file	unit_test_qvm_vector_minus.cpp
 *
 *	@brief	operator-のテスト
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
inline HAMON_CXX14_CONSTEXPR bool Vector2MinusTest()
{
	using vector2  = hamon::qvm::vector<T, 2>;
	using vector2i = hamon::qvm::vector<int, 2>;
	using vector2f = hamon::qvm::vector<float, 2>;

	static_assert(hamon::is_same<decltype(std::declval<vector2&>()  -= vector2{}),  vector2&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector2&>()  -= vector2i{}), vector2&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector2&>()  -= vector2f{}), vector2&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector2i&>() -= vector2{}),  vector2i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector2i&>() -= vector2i{}), vector2i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector2i&>() -= vector2f{}), vector2i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector2f&>() -= vector2{}),  vector2f&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector2f&>() -= vector2i{}), vector2f&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector2f&>() -= vector2f{}), vector2f&>::value, "");

	// vector2 -= vector2
	{
		vector2 v;
		VERIFY(v == vector2(0, 0));
		{
			auto t = (v -= vector2(2, 3));
			static_assert(hamon::is_same<decltype(t), vector2>::value, "");
			VERIFY(v == vector2(-2, -3));
			VERIFY(v == t);
		}
		{
			auto t = (v -= vector2f(3, 1));
			static_assert(hamon::is_same<decltype(t), vector2>::value, "");
			VERIFY(v == vector2(-5, -4));
			VERIFY(v == t);
		}
		{
			auto t = (v -= vector2i(4, 3));
			static_assert(hamon::is_same<decltype(t), vector2>::value, "");
			VERIFY(v == vector2(-9, -7));
			VERIFY(v == t);
		}
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector3MinusTest()
{
	using vector3  = hamon::qvm::vector<T, 3>;
	using vector3i = hamon::qvm::vector<int, 3>;
	using vector3f = hamon::qvm::vector<float, 3>;

	static_assert(hamon::is_same<decltype(std::declval<vector3&>()  -= vector3{}),  vector3&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3&>()  -= vector3i{}), vector3&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3&>()  -= vector3f{}), vector3&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3i&>() -= vector3{}),  vector3i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3i&>() -= vector3i{}), vector3i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3i&>() -= vector3f{}), vector3i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3f&>() -= vector3{}),  vector3f&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3f&>() -= vector3i{}), vector3f&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector3f&>() -= vector3f{}), vector3f&>::value, "");

	// vector3 -= vector3
	{
		vector3 v;
		VERIFY(v == vector3(0, 0, 0));
		{
			auto t = (v -= vector3(2, 3, -4));
			static_assert(hamon::is_same<decltype(t), vector3>::value, "");
			VERIFY(v == vector3(-2, -3, 4));
			VERIFY(v == t);
		}
		{
			auto t = (v -= vector3f(3, 1, 4));
			static_assert(hamon::is_same<decltype(t), vector3>::value, "");
			VERIFY(v == vector3(-5, -4, 0));
			VERIFY(v == t);
		}
		{
			auto t = (v -= vector3i(4, 3, 2));
			static_assert(hamon::is_same<decltype(t), vector3>::value, "");
			VERIFY(v == vector3(-9, -7, -2));
			VERIFY(v == t);
		}
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector4MinusTest()
{
	using vector4  = hamon::qvm::vector<T, 4>;
	using vector4i = hamon::qvm::vector<int, 4>;
	using vector4f = hamon::qvm::vector<float, 4>;

	static_assert(hamon::is_same<decltype(std::declval<vector4&>()  -= vector4{}),  vector4&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector4&>()  -= vector4i{}), vector4&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector4&>()  -= vector4f{}), vector4&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector4i&>() -= vector4{}),  vector4i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector4i&>() -= vector4i{}), vector4i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector4i&>() -= vector4f{}), vector4i&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector4f&>() -= vector4{}),  vector4f&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector4f&>() -= vector4i{}), vector4f&>::value, "");
	static_assert(hamon::is_same<decltype(std::declval<vector4f&>() -= vector4f{}), vector4f&>::value, "");

	// vector4 -= vector4
	{
		vector4 v;
		VERIFY(v == vector4(0, 0, 0, 0));
		{
			auto t = (v -= vector4(2, 3, -4, 5));
			static_assert(hamon::is_same<decltype(t), vector4>::value, "");
			VERIFY(v == vector4(-2, -3, 4, -5));
			VERIFY(v == t);
		}
		{
			auto t = (v -= vector4f(3, 1, 4, 1));
			static_assert(hamon::is_same<decltype(t), vector4>::value, "");
			VERIFY(v == vector4(-5, -4, 0, -6));
			VERIFY(v == t);
		}
		{
			auto t = (v -= vector4i(4, 3, 2, -1));
			static_assert(hamon::is_same<decltype(t), vector4>::value, "");
			VERIFY(v == vector4(-9, -7, -2, -5));
			VERIFY(v == t);
		}
	}

	return true;
}

TYPED_TEST(VectorTest, MinusTest)
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

	static_assert(hamon::is_same<decltype(vector2{}  - vector2{}),  vector2>::value, "");
	static_assert(hamon::is_same<decltype(vector2{}  - vector2i{}), vector2>::value, "");
	static_assert(hamon::is_same<decltype(vector2i{} - vector2i{}), vector2i>::value, "");
	static_assert(hamon::is_same<decltype(vector2i{} - vector2f{}), vector2f>::value, "");
	static_assert(hamon::is_same<decltype(vector2f{} - vector2i{}), vector2f>::value, "");
	static_assert(hamon::is_same<decltype(vector2f{} - vector2f{}), vector2f>::value, "");

	static_assert(hamon::is_same<decltype(vector3{}  - vector3{}),  vector3>::value, "");
	static_assert(hamon::is_same<decltype(vector3{}  - vector3i{}), vector3>::value, "");
	static_assert(hamon::is_same<decltype(vector3i{} - vector3i{}), vector3i>::value, "");
	static_assert(hamon::is_same<decltype(vector3i{} - vector3f{}), vector3f>::value, "");
	static_assert(hamon::is_same<decltype(vector3f{} - vector3i{}), vector3f>::value, "");
	static_assert(hamon::is_same<decltype(vector3f{} - vector3f{}), vector3f>::value, "");

	static_assert(hamon::is_same<decltype(vector4{}  - vector4{}),  vector4>::value, "");
	static_assert(hamon::is_same<decltype(vector4{}  - vector4i{}), vector4>::value, "");
	static_assert(hamon::is_same<decltype(vector4i{} - vector4i{}), vector4i>::value, "");
	static_assert(hamon::is_same<decltype(vector4i{} - vector4f{}), vector4f>::value, "");
	static_assert(hamon::is_same<decltype(vector4f{} - vector4i{}), vector4f>::value, "");
	static_assert(hamon::is_same<decltype(vector4f{} - vector4f{}), vector4f>::value, "");

	// vector2 - vector2 -> vector2
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2 ( 1, 2) - vector2 (3, 4), vector2(-2,-2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2 (-3, 4) - vector2 (0, 2), vector2(-3, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2f(-3, 4) - vector2 (0, 2), vector2(-3, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2 (-3, 4) - vector2f(0, 2), vector2(-3, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2i(-3, 4) - vector2 (0, 2), vector2(-3, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2 (-3, 4) - vector2i(0, 2), vector2(-3, 2));

	// vector3 - vector3 -> vector3
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3 ( 1, 2, 3) - vector3 (4, 5, 6), vector3(-3,-3,-3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3 (-3, 4, 5) - vector3 (0, 2,-1), vector3(-3, 2, 6));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3f(-3, 4, 5) - vector3 (0, 2,-1), vector3(-3, 2, 6));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3 (-3, 4, 5) - vector3f(0, 2,-1), vector3(-3, 2, 6));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3i(-3, 4, 5) - vector3 (0, 2,-1), vector3(-3, 2, 6));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3 (-3, 4, 5) - vector3i(0, 2,-1), vector3(-3, 2, 6));

	// vector4 - vector4 -> vector4
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4 ( 1, 2, 3, 4) - vector4 (5, 6, 7, 8), vector4(-4,-4,-4,-4));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4 (-3, 4, 5, 6) - vector4 (0, 2,-1, 3), vector4(-3, 2, 6, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4f(-3, 4, 5, 6) - vector4 (0, 2,-1, 3), vector4(-3, 2, 6, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4 (-3, 4, 5, 6) - vector4f(0, 2,-1, 3), vector4(-3, 2, 6, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4i(-3, 4, 5, 6) - vector4 (0, 2,-1, 3), vector4(-3, 2, 6, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4 (-3, 4, 5, 6) - vector4i(0, 2,-1, 3), vector4(-3, 2, 6, 3));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector2MinusTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector3MinusTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector4MinusTest<T>());
}

#undef VERIFY

}	// namespace vector_test

}	// namespace hamon_qvm_test
