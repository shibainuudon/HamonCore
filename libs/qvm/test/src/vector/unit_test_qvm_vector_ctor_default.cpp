/**
 *	@file	unit_test_qvm_vector_ctor_default.cpp
 *
 *	@brief	vector のデフォルトコンストラクタのテスト
 */

#include <hamon/qvm/vector/vector.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_implicitly_default_constructible.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_destructible.hpp>
#include <hamon/type_traits/is_nothrow_destructible.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"

namespace hamon_qvm_test
{

namespace vector_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR bool IsZero(hamon::qvm::vector<T, N> const& v)
{
	for (hamon::size_t i = 0; i < N; ++i)
	{
		VERIFY(v[i] == 0);
	}
	return true;
}

template <typename T, hamon::size_t N>
void CtorDefaultTest()
{
	using vector_type = hamon::qvm::vector<T, N>;

	static_assert(sizeof(vector_type) == sizeof(T) * N, "");
	static_assert(hamon::is_default_constructible<vector_type>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<vector_type>::value, "");
	static_assert(hamon::is_implicitly_default_constructible<vector_type>::value, "");
	static_assert(hamon::is_destructible<vector_type>::value, "");
	static_assert(hamon::is_nothrow_destructible<vector_type>::value, "");
	static_assert(hamon::is_trivially_destructible<vector_type>::value, "");

	{
		HAMON_CONSTEXPR vector_type const v;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, v[N-1]);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IsZero(v));
	}
	{
		HAMON_CONSTEXPR vector_type const v{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, v[N-1]);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IsZero(v));
	}
	{
		HAMON_CONSTEXPR vector_type const v = {};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, v[N-1]);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IsZero(v));
	}
}

TYPED_TEST(VectorTest, CtorDefaultTest)
{
	using T = TypeParam;

	CtorDefaultTest<T, 1>();
	CtorDefaultTest<T, 2>();
	CtorDefaultTest<T, 3>();
	CtorDefaultTest<T, 4>();
}

#undef VERIFY

}	// namespace vector_test

}	// namespace hamon_qvm_test
