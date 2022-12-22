/**
 *	@file	unit_test_qvm_vector_at.cpp
 *
 *	@brief	atのテスト
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
inline HAMON_CXX14_CONSTEXPR bool Vector2AtTest()
{
	using vector2 = hamon::qvm::vector<T, 2>;

	{
		vector2 v{1, 2};
		static_assert(std::is_same<decltype(v.at(0)), T&>::value, "");
		static_assert(std::is_same<decltype(v.at(1)), T&>::value, "");
		VERIFY(v.at(0) == 1);
		VERIFY(v.at(1) == 2);

		v.at(0) = -3;
		v.at(1) =  4;

		VERIFY(v.at(0) == -3);
		VERIFY(v.at(1) ==  4);
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector3AtTest()
{
	using vector3 = hamon::qvm::vector<T, 3>;

	{
		vector3 v{1, 2, 3};
		static_assert(std::is_same<decltype(v.at(0)), T&>::value, "");
		static_assert(std::is_same<decltype(v.at(1)), T&>::value, "");
		static_assert(std::is_same<decltype(v.at(2)), T&>::value, "");
		VERIFY(v.at(0) == 1);
		VERIFY(v.at(1) == 2);
		VERIFY(v.at(2) == 3);

		v.at(0) = -3;
		v.at(1) =  4;
		v.at(2) = -5;

		VERIFY(v.at(0) == -3);
		VERIFY(v.at(1) ==  4);
		VERIFY(v.at(2) == -5);
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector4AtTest()
{
	using vector4 = hamon::qvm::vector<T, 4>;

	{
		vector4 v{1, 2, 3, 4};
		static_assert(std::is_same<decltype(v.at(0)), T&>::value, "");
		static_assert(std::is_same<decltype(v.at(1)), T&>::value, "");
		static_assert(std::is_same<decltype(v.at(2)), T&>::value, "");
		static_assert(std::is_same<decltype(v.at(3)), T&>::value, "");
		VERIFY(v.at(0) == 1);
		VERIFY(v.at(1) == 2);
		VERIFY(v.at(2) == 3);
		VERIFY(v.at(3) == 4);

		v.at(0) = -3;
		v.at(1) =  4;
		v.at(2) = -5;
		v.at(3) =  6;

		VERIFY(v.at(0) == -3);
		VERIFY(v.at(1) ==  4);
		VERIFY(v.at(2) == -5);
		VERIFY(v.at(3) ==  6);
	}

	return true;
}

TYPED_TEST(VectorTest, AtTest)
{
	using T = TypeParam;
	using vector2 = hamon::qvm::vector<T, 2>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;

	{
		HAMON_CONSTEXPR vector2 const v{1, 2};
		static_assert(std::is_same<decltype(v.at(0)), T const&>::value, "");
		static_assert(std::is_same<decltype(v.at(1)), T const&>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v.at(0));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v.at(1));
#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW((void)v.at(2), std::out_of_range);
#endif
	}
	{
		HAMON_CONSTEXPR vector3 const v{3, 4, 5};
		static_assert(std::is_same<decltype(v.at(0)), T const&>::value, "");
		static_assert(std::is_same<decltype(v.at(1)), T const&>::value, "");
		static_assert(std::is_same<decltype(v.at(2)), T const&>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v.at(0));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, v.at(1));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v.at(2));
	}
	{
		HAMON_CONSTEXPR vector4 const v{5, 6, 7, 8};
		static_assert(std::is_same<decltype(v.at(0)), T const&>::value, "");
		static_assert(std::is_same<decltype(v.at(1)), T const&>::value, "");
		static_assert(std::is_same<decltype(v.at(2)), T const&>::value, "");
		static_assert(std::is_same<decltype(v.at(3)), T const&>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v.at(0));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, v.at(1));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7, v.at(2));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8, v.at(3));
	}

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		vector2 v{1, 2};
		EXPECT_THROW((void)v.at(2), std::out_of_range);
	}
	{
		vector2 const v{5, 6};
		EXPECT_THROW((void)v.at(2), std::out_of_range);
	}
	{
		vector3 v{1, 2, 3};
		EXPECT_THROW((void)v.at(3), std::out_of_range);
	}
	{
		vector3 const v{5, 6, 7};
		EXPECT_THROW((void)v.at(3), std::out_of_range);
	}
	{
		vector4 v{1, 2, 3, 4};
		EXPECT_THROW((void)v.at(4), std::out_of_range);
	}
	{
		vector4 const v{5, 6, 7, 8};
		EXPECT_THROW((void)v.at(4), std::out_of_range);
	}
#endif

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector2AtTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector3AtTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector4AtTest<T>());
}

#undef VERIFY

}	// namespace vector_test

}	// namespace hamon_qvm_test
