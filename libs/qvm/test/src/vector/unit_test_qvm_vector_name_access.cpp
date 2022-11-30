/**
 *	@file	unit_test_qvm_vector_name_access.cpp
 *
 *	@brief	名前でのアクセスのテスト
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
inline HAMON_CXX14_CONSTEXPR bool Vector2NameAccessTest()
{
	using vector2 = hamon::qvm::vector<T, 2>;

	{
		vector2 v{1, 2};
		static_assert(std::is_same<decltype(v.x()), T&>::value, "");
		static_assert(std::is_same<decltype(v.y()), T&>::value, "");
		VERIFY(v.x() == 1);
		VERIFY(v.y() == 2);

		v.x() = -3;
		v.y() =  4;

		VERIFY(v.x() == -3);
		VERIFY(v.y() ==  4);
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector3NameAccessTest()
{
	using vector3 = hamon::qvm::vector<T, 3>;

	{
		vector3 v{1, 2, 3};
		static_assert(std::is_same<decltype(v.x()), T&>::value, "");
		static_assert(std::is_same<decltype(v.y()), T&>::value, "");
		static_assert(std::is_same<decltype(v.z()), T&>::value, "");
		VERIFY(v.x() == 1);
		VERIFY(v.y() == 2);
		VERIFY(v.z() == 3);

		v.x() = -3;
		v.y() =  4;
		v.z() = -5;

		VERIFY(v.x() == -3);
		VERIFY(v.y() ==  4);
		VERIFY(v.z() == -5);
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector4NameAccessTest()
{
	using vector4 = hamon::qvm::vector<T, 4>;

	{
		vector4 v{1, 2, 3, 4};
		static_assert(std::is_same<decltype(v.x()), T&>::value, "");
		static_assert(std::is_same<decltype(v.y()), T&>::value, "");
		static_assert(std::is_same<decltype(v.z()), T&>::value, "");
		static_assert(std::is_same<decltype(v.w()), T&>::value, "");
		VERIFY(v.x() == 1);
		VERIFY(v.y() == 2);
		VERIFY(v.z() == 3);
		VERIFY(v.w() == 4);

		v.x() = -3;
		v.y() =  4;
		v.z() = -5;
		v.w() =  6;

		VERIFY(v.x() == -3);
		VERIFY(v.y() ==  4);
		VERIFY(v.z() == -5);
		VERIFY(v.w() ==  6);
	}

	return true;
}

TYPED_TEST(VectorTest, NameAccessTest)
{
	using T = TypeParam;
	using vector2 = hamon::qvm::vector<T, 2>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;

	{
		HAMON_CONSTEXPR vector2 const v{1, 2};
		static_assert(std::is_same<decltype(v.x()), T const&>::value, "");
		static_assert(std::is_same<decltype(v.y()), T const&>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v.x());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v.y());
	}
	{
		HAMON_CONSTEXPR vector3 const v{3, 4, 5};
		static_assert(std::is_same<decltype(v.x()), T const&>::value, "");
		static_assert(std::is_same<decltype(v.y()), T const&>::value, "");
		static_assert(std::is_same<decltype(v.z()), T const&>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v.x());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, v.y());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v.z());
	}
	{
		HAMON_CONSTEXPR vector4 const v{5, 6, 7, 8};
		static_assert(std::is_same<decltype(v.x()), T const&>::value, "");
		static_assert(std::is_same<decltype(v.y()), T const&>::value, "");
		static_assert(std::is_same<decltype(v.z()), T const&>::value, "");
		static_assert(std::is_same<decltype(v.w()), T const&>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v.x());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, v.y());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7, v.z());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8, v.w());
	}

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector2NameAccessTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector3NameAccessTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector4NameAccessTest<T>());
}

#undef VERIFY

}	// namespace vector_test

}	// namespace hamon_qvm_test
