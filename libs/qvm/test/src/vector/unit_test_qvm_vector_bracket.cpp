/**
 *	@file	unit_test_qvm_vector_bracket.cpp
 *
 *	@brief	operator[]のテスト
 */

#include <hamon/qvm/vector/vector.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace vector_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector2BracketTest()
{
	using vector2 = hamon::qvm::vector<T, 2>;

	{
		vector2 v{1, 2};
		static_assert(std::is_same<decltype(v[0]), T&>::value, "");
		static_assert(std::is_same<decltype(v[1]), T&>::value, "");
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);

		v[0] = -3;
		v[1] =  4;

		VERIFY(v[0] == -3);
		VERIFY(v[1] ==  4);
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector3BracketTest()
{
	using vector3 = hamon::qvm::vector<T, 3>;

	{
		vector3 v{1, 2, 3};
		static_assert(std::is_same<decltype(v[0]), T&>::value, "");
		static_assert(std::is_same<decltype(v[1]), T&>::value, "");
		static_assert(std::is_same<decltype(v[2]), T&>::value, "");
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);

		v[0] = -3;
		v[1] =  4;
		v[2] = -5;

		VERIFY(v[0] == -3);
		VERIFY(v[1] ==  4);
		VERIFY(v[2] == -5);
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector4BracketTest()
{
	using vector4 = hamon::qvm::vector<T, 4>;

	{
		vector4 v{1, 2, 3, 4};
		static_assert(std::is_same<decltype(v[0]), T&>::value, "");
		static_assert(std::is_same<decltype(v[1]), T&>::value, "");
		static_assert(std::is_same<decltype(v[2]), T&>::value, "");
		static_assert(std::is_same<decltype(v[3]), T&>::value, "");
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
		VERIFY(v[3] == 4);

		v[0] = -3;
		v[1] =  4;
		v[2] = -5;
		v[3] =  6;

		VERIFY(v[0] == -3);
		VERIFY(v[1] ==  4);
		VERIFY(v[2] == -5);
		VERIFY(v[3] ==  6);
	}

	return true;
}

TYPED_TEST(VectorTest, BracketTest)
{
	using T = TypeParam;
	using vector2 = hamon::qvm::vector<T, 2>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;

	{
		HAMON_CONSTEXPR vector2 const v{1, 2};
		static_assert(std::is_same<decltype(v[0]), T const&>::value, "");
		static_assert(std::is_same<decltype(v[1]), T const&>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v[1]);
	}
	{
		HAMON_CONSTEXPR vector3 const v{3, 4, 5};
		static_assert(std::is_same<decltype(v[0]), T const&>::value, "");
		static_assert(std::is_same<decltype(v[1]), T const&>::value, "");
		static_assert(std::is_same<decltype(v[2]), T const&>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, v[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v[2]);
	}
	{
		HAMON_CONSTEXPR vector4 const v{5, 6, 7, 8};
		static_assert(std::is_same<decltype(v[0]), T const&>::value, "");
		static_assert(std::is_same<decltype(v[1]), T const&>::value, "");
		static_assert(std::is_same<decltype(v[2]), T const&>::value, "");
		static_assert(std::is_same<decltype(v[3]), T const&>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, v[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7, v[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8, v[3]);
	}

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector2BracketTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector3BracketTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector4BracketTest<T>());
}

#undef VERIFY

}	// namespace vector_test

}	// namespace hamon_qvm_test
