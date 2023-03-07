/**
 *	@file	unit_test_qvm_vector_multiplies.cpp
 *
 *	@brief	operator*のテスト
 */

#include <hamon/qvm/vector/vector.hpp>
#include <hamon/qvm/vector/operators.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"

namespace hamon_qvm_test
{

namespace vector_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector2MultipliesTest()
{
	using vector2  = hamon::qvm::vector<T, 2>;
	using vector2i = hamon::qvm::vector<int, 2>;
	using vector2f = hamon::qvm::vector<float, 2>;

	static_assert(hamon::is_same<decltype(hamon::declval<vector2&>()  *= vector2{}),  vector2&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector2&>()  *= vector2i{}), vector2&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector2&>()  *= vector2f{}), vector2&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector2i&>() *= vector2{}),  vector2i&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector2i&>() *= vector2i{}), vector2i&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector2i&>() *= vector2f{}), vector2i&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector2f&>() *= vector2{}),  vector2f&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector2f&>() *= vector2i{}), vector2f&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector2f&>() *= vector2f{}), vector2f&>::value, "");

	// vector2 *= vector2
	{
		vector2 v{1, 2};
		VERIFY(v == vector2(1, 2));
		{
			auto t = (v *= vector2(2, 3));
			static_assert(hamon::is_same<decltype(t), vector2>::value, "");
			VERIFY(v == vector2(2, 6));
			VERIFY(v == t);
		}
		{
			auto t = (v *= vector2f(5, 2));
			static_assert(hamon::is_same<decltype(t), vector2>::value, "");
			VERIFY(v == vector2(10, 12));
			VERIFY(v == t);
		}
		{
			auto t = (v *= vector2i(4, 3));
			static_assert(hamon::is_same<decltype(t), vector2>::value, "");
			VERIFY(v == vector2(40, 36));
			VERIFY(v == t);
		}
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector3MultipliesTest()
{
	using vector3  = hamon::qvm::vector<T, 3>;
	using vector3i = hamon::qvm::vector<int, 3>;
	using vector3f = hamon::qvm::vector<float, 3>;

	static_assert(hamon::is_same<decltype(hamon::declval<vector3&>()  *= vector3{}),  vector3&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector3&>()  *= vector3i{}), vector3&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector3&>()  *= vector3f{}), vector3&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector3i&>() *= vector3{}),  vector3i&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector3i&>() *= vector3i{}), vector3i&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector3i&>() *= vector3f{}), vector3i&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector3f&>() *= vector3{}),  vector3f&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector3f&>() *= vector3i{}), vector3f&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector3f&>() *= vector3f{}), vector3f&>::value, "");

	// vector3 *= vector3
	{
		vector3 v{1, 2, 3};
		VERIFY(v == vector3(1, 2, 3));
		{
			auto t = (v *= vector3(2, 3, -4));
			static_assert(hamon::is_same<decltype(t), vector3>::value, "");
			VERIFY(v == vector3(2, 6, -12));
			VERIFY(v == t);
		}
		{
			auto t = (v *= vector3f(5, 2, 1));
			static_assert(hamon::is_same<decltype(t), vector3>::value, "");
			VERIFY(v == vector3(10, 12, -12));
			VERIFY(v == t);
		}
		{
			auto t = (v *= vector3i(4, 3, 2));
			static_assert(hamon::is_same<decltype(t), vector3>::value, "");
			VERIFY(v == vector3(40, 36, -24));
			VERIFY(v == t);
		}
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector4MultipliesTest()
{
	using vector4  = hamon::qvm::vector<T, 4>;
	using vector4i = hamon::qvm::vector<int, 4>;
	using vector4f = hamon::qvm::vector<float, 4>;

	static_assert(hamon::is_same<decltype(hamon::declval<vector4&>()  *= vector4{}),  vector4&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector4&>()  *= vector4i{}), vector4&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector4&>()  *= vector4f{}), vector4&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector4i&>() *= vector4{}),  vector4i&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector4i&>() *= vector4i{}), vector4i&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector4i&>() *= vector4f{}), vector4i&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector4f&>() *= vector4{}),  vector4f&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector4f&>() *= vector4i{}), vector4f&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector4f&>() *= vector4f{}), vector4f&>::value, "");

	// vector4 *= vector4
	{
		vector4 v{1, 2, 3, 4};
		VERIFY(v == vector4(1, 2, 3, 4));
		{
			auto t = (v *= vector4(2, 3, -4, 5));
			static_assert(hamon::is_same<decltype(t), vector4>::value, "");
			VERIFY(v == vector4(2, 6, -12, 20));
			VERIFY(v == t);
		}
		{
			auto t = (v *= vector4f(5, 2, 1, 3));
			static_assert(hamon::is_same<decltype(t), vector4>::value, "");
			VERIFY(v == vector4(10, 12, -12, 60));
			VERIFY(v == t);
		}
		{
			auto t = (v *= vector4i(4, 3, 2, -1));
			static_assert(hamon::is_same<decltype(t), vector4>::value, "");
			VERIFY(v == vector4(40, 36, -24, -60));
			VERIFY(v == t);
		}
	}

	return true;
}

TYPED_TEST(VectorTest, MultipliesTest)
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

	static_assert(hamon::is_same<decltype(vector2{}  * vector2{}),  vector2>::value, "");
	static_assert(hamon::is_same<decltype(vector2{}  * vector2i{}), vector2>::value, "");
	static_assert(hamon::is_same<decltype(vector2i{} * vector2i{}), vector2i>::value, "");
	static_assert(hamon::is_same<decltype(vector2i{} * vector2f{}), vector2f>::value, "");
	static_assert(hamon::is_same<decltype(vector2f{} * vector2i{}), vector2f>::value, "");
	static_assert(hamon::is_same<decltype(vector2f{} * vector2f{}), vector2f>::value, "");

	static_assert(hamon::is_same<decltype(vector3{}  * vector3{}),  vector3>::value, "");
	static_assert(hamon::is_same<decltype(vector3{}  * vector3i{}), vector3>::value, "");
	static_assert(hamon::is_same<decltype(vector3i{} * vector3i{}), vector3i>::value, "");
	static_assert(hamon::is_same<decltype(vector3i{} * vector3f{}), vector3f>::value, "");
	static_assert(hamon::is_same<decltype(vector3f{} * vector3i{}), vector3f>::value, "");
	static_assert(hamon::is_same<decltype(vector3f{} * vector3f{}), vector3f>::value, "");

	static_assert(hamon::is_same<decltype(vector4{}  * vector4{}),  vector4>::value, "");
	static_assert(hamon::is_same<decltype(vector4{}  * vector4i{}), vector4>::value, "");
	static_assert(hamon::is_same<decltype(vector4i{} * vector4i{}), vector4i>::value, "");
	static_assert(hamon::is_same<decltype(vector4i{} * vector4f{}), vector4f>::value, "");
	static_assert(hamon::is_same<decltype(vector4f{} * vector4i{}), vector4f>::value, "");
	static_assert(hamon::is_same<decltype(vector4f{} * vector4f{}), vector4f>::value, "");

	// vector2 * vector2 -> vector2
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2 ( 1, 2) * vector2 (3, 4), vector2( 3, 8));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2 (-3, 4) * vector2 (3, 1), vector2(-9, 4));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2f(-3, 4) * vector2 (3, 1), vector2(-9, 4));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2 (-3, 4) * vector2f(3, 1), vector2(-9, 4));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2i(-3, 4) * vector2 (3, 1), vector2(-9, 4));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2 (-3, 4) * vector2i(3, 1), vector2(-9, 4));

	// vector3 * vector3 -> vector3
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3 ( 1, 2, 3) * vector3 (4, 5, 6), vector3( 4,10, 18));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3 (-3, 4,-5) * vector3 (3, 1,-4), vector3(-9, 4, 20));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3f(-3, 4,-5) * vector3 (3, 1,-4), vector3(-9, 4, 20));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3 (-3, 4,-5) * vector3f(3, 1,-4), vector3(-9, 4, 20));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3i(-3, 4,-5) * vector3 (3, 1,-4), vector3(-9, 4, 20));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3 (-3, 4,-5) * vector3i(3, 1,-4), vector3(-9, 4, 20));

	// vector4 * vector4 -> vector4
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4 ( 1, 2, 3, 4) * vector4 (5, 6, 7, 8), vector4( 5,12, 21, 32));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4 (-3, 4,-5, 6) * vector4 (3, 1,-4,-2), vector4(-9, 4, 20,-12));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4f(-3, 4,-5, 6) * vector4 (3, 1,-4,-2), vector4(-9, 4, 20,-12));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4 (-3, 4,-5, 6) * vector4f(3, 1,-4,-2), vector4(-9, 4, 20,-12));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4i(-3, 4,-5, 6) * vector4 (3, 1,-4,-2), vector4(-9, 4, 20,-12));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4 (-3, 4,-5, 6) * vector4i(3, 1,-4,-2), vector4(-9, 4, 20,-12));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector2MultipliesTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector3MultipliesTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector4MultipliesTest<T>());
}

#undef VERIFY

}	// namespace vector_test

}	// namespace hamon_qvm_test
