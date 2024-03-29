﻿/**
 *	@file	unit_test_qvm_matrix_all.cpp
 *
 *	@brief	allのテスト
 */

#include <hamon/qvm/matrix/matrix.hpp>
#include <hamon/qvm/common/all.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"

namespace hamon_qvm_test
{

namespace matrix_test
{

TYPED_TEST(MatrixTest, AllTest)
{
	using matrix3x3b = hamon::qvm::matrix<bool, 3, 3>;
	using matrix3x4b = hamon::qvm::matrix<bool, 3, 4>;
	using matrix4x3b = hamon::qvm::matrix<bool, 4, 3>;

	// matrix3x3b
	{
		HAMON_CONSTEXPR matrix3x3b const m
		{
			true,  true,  true,
			true,  true,  true,
			true,  true,  true,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true, hamon::qvm::all(m));
	}
	{
		HAMON_CONSTEXPR matrix3x3b const m
		{
			true,  false, true,
			true,  true,  true,
			true,  true,  true,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::qvm::all(m));
	}
	{
		HAMON_CONSTEXPR matrix3x3b const m
		{
			true,  true,  true,
			false, true,  true,
			true,  true,  true,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::qvm::all(m));
	}
	{
		HAMON_CONSTEXPR matrix3x3b const m
		{
			true,  true,  true,
			true,  true,  true,
			true,  true,  false,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::qvm::all(m));
	}
	{
		HAMON_CONSTEXPR matrix3x3b const m
		{
			false, false, false,
			false, true,  false,
			false, false, false,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::qvm::all(m));
	}
	{
		HAMON_CONSTEXPR matrix3x3b const m
		{
			false, false, false,
			false, false, false,
			false, false, false,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::qvm::all(m));
	}

	// matrix3x4b
	{
		HAMON_CONSTEXPR matrix3x4b const m
		{
			true,  true,  true,  true,
			true,  true,  true,  true,
			true,  true,  true,  true,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true, hamon::qvm::all(m));
	}
	{
		HAMON_CONSTEXPR matrix3x4b const m
		{
			false, true,  true,  true,
			true,  true,  true,  true,
			true,  true,  true,  true,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::qvm::all(m));
	}
	{
		HAMON_CONSTEXPR matrix3x4b const m
		{
			true,  true,  true,  true,
			true,  true,  true,  false,
			true,  true,  true,  true,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::qvm::all(m));
	}
	{
		HAMON_CONSTEXPR matrix3x4b const m
		{
			true,  true,  true,  true,
			true,  true,  true,  true,
			true,  true,  true,  false,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::qvm::all(m));
	}
	{
		HAMON_CONSTEXPR matrix3x4b const m
		{
			true,  false, false, false,
			false, false, false, false,
			false, false, false, false,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::qvm::all(m));
	}
	{
		HAMON_CONSTEXPR matrix3x4b const m
		{
			false, false, false, false,
			false, false, false, false,
			false, false, false, false,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::qvm::all(m));
	}

	// matrix4x3b
	{
		HAMON_CONSTEXPR matrix4x3b const m
		{
			true,  true,  true,
			true,  true,  true,
			true,  true,  true,
			true,  true,  true,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true, hamon::qvm::all(m));
	}
	{
		HAMON_CONSTEXPR matrix4x3b const m
		{
			true,  true,  false,
			true,  true,  true,
			true,  true,  true,
			true,  true,  true,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::qvm::all(m));
	}
	{
		HAMON_CONSTEXPR matrix4x3b const m
		{
			true,  true,  true,
			false, true,  true,
			true,  true,  true,
			true,  true,  true,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::qvm::all(m));
	}
	{
		HAMON_CONSTEXPR matrix4x3b const m
		{
			true,  true,  true,
			true,  true,  true,
			false, true,  true,
			true,  true,  true,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::qvm::all(m));
	}
	{
		HAMON_CONSTEXPR matrix4x3b const m
		{
			true,  true,  true,
			true,  true,  true,
			true,  true,  true,
			true,  false, true,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::qvm::all(m));
	}
	{
		HAMON_CONSTEXPR matrix4x3b const m
		{
			false, false, false,
			false, false, false,
			false, false, false,
			false, false, true,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::qvm::all(m));
	}
	{
		HAMON_CONSTEXPR matrix4x3b const m
		{
			false, false, false,
			false, false, false,
			false, false, false,
			false, false, false,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::qvm::all(m));
	}
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
