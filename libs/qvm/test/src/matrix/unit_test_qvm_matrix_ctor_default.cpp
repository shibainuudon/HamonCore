/**
 *	@file	unit_test_qvm_matrix_ctor_default.cpp
 *
 *	@brief	matrix のデフォルトコンストラクタのテスト
 */

#include <hamon/qvm/matrix.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_implicitly_default_constructible.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_destructible.hpp>
#include <hamon/type_traits/is_nothrow_destructible.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"

namespace hamon_qvm_test
{

namespace matrix_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N, hamon::size_t M>
inline HAMON_CXX14_CONSTEXPR bool IsZero(hamon::qvm::matrix<T, N, M> const& m)
{
	for (hamon::size_t i = 0; i < N; ++i)
	{
		for (hamon::size_t j = 0; j < M; ++j)
		{
			VERIFY(m[i][j] == 0);
		}
	}
	return true;
}

template <typename T, hamon::size_t N, hamon::size_t M>
void CtorDefaultTest()
{
	using matrix_type = hamon::qvm::matrix<T, N, M>;

	static_assert(sizeof(matrix_type) == sizeof(T) * N * M, "");
	static_assert(hamon::is_default_constructible<matrix_type>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<matrix_type>::value, "");
	static_assert(hamon::is_implicitly_default_constructible<matrix_type>::value, "");
	static_assert(hamon::is_destructible<matrix_type>::value, "");
	static_assert(hamon::is_nothrow_destructible<matrix_type>::value, "");
	static_assert(hamon::is_trivially_destructible<matrix_type>::value, "");

	{
		HAMON_CONSTEXPR matrix_type const m;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, m[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, m[N-1][M-1]);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IsZero(m));
	}
	{
		HAMON_CONSTEXPR matrix_type const m{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, m[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, m[N-1][M-1]);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IsZero(m));
	}
	{
		HAMON_CONSTEXPR matrix_type const m = {};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, m[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, m[N-1][M-1]);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IsZero(m));
	}
}

TYPED_TEST(MatrixTest, CtorDefaultTest)
{
	using T = TypeParam;

	CtorDefaultTest<T, 1, 1>();
	CtorDefaultTest<T, 1, 2>();
	CtorDefaultTest<T, 1, 3>();
	CtorDefaultTest<T, 1, 4>();
	CtorDefaultTest<T, 2, 1>();
	CtorDefaultTest<T, 2, 2>();
	CtorDefaultTest<T, 2, 3>();
	CtorDefaultTest<T, 2, 4>();
	CtorDefaultTest<T, 3, 1>();
	CtorDefaultTest<T, 3, 2>();
	CtorDefaultTest<T, 3, 3>();
	CtorDefaultTest<T, 3, 4>();
	CtorDefaultTest<T, 4, 1>();
	CtorDefaultTest<T, 4, 2>();
	CtorDefaultTest<T, 4, 3>();
	CtorDefaultTest<T, 4, 4>();
}

#undef VERIFY

}	// namespace matrix_test

}	// namespace hamon_qvm_test
