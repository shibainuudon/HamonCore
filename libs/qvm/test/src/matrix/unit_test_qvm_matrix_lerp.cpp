/**
 *	@file	unit_test_qvm_matrix_lerp.cpp
 *
 *	@brief	lerpのテスト
 */

#include <hamon/qvm/matrix.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace matrix_test
{

TYPED_TEST(MatrixFloatTest, LerpTest)
{
	using T = TypeParam;
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;
	using matrix3x4 = hamon::qvm::matrix<T, 3, 4>;
	using matrix4x3 = hamon::qvm::matrix<T, 4, 3>;
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(std::is_same<decltype(lerp(matrix3x3{}, matrix3x3{}, T{})),  matrix3x3>::value, "");
	static_assert(std::is_same<decltype(lerp(matrix3x3{}, matrix3x3{}, 0.0f)), matrix3x3>::value, "");
	static_assert(std::is_same<decltype(lerp(matrix3x3{}, matrix3x3{}, 0.0L)), hamon::qvm::matrix<long double, 3, 3>>::value, "");
	static_assert(std::is_same<decltype(lerp(matrix3x4{}, matrix3x4{}, T{})),  matrix3x4>::value, "");
	static_assert(std::is_same<decltype(lerp(matrix3x4{}, matrix3x4{}, 0.0f)), matrix3x4>::value, "");
	static_assert(std::is_same<decltype(lerp(matrix3x4{}, matrix3x4{}, 0.0L)), hamon::qvm::matrix<long double, 3, 4>>::value, "");
	static_assert(std::is_same<decltype(lerp(matrix4x3{}, matrix4x3{}, T{})),  matrix4x3>::value, "");
	static_assert(std::is_same<decltype(lerp(matrix4x3{}, matrix4x3{}, 0.0f)), matrix4x3>::value, "");
	static_assert(std::is_same<decltype(lerp(matrix4x3{}, matrix4x3{}, 0.0L)), hamon::qvm::matrix<long double, 4, 3>>::value, "");
	static_assert(std::is_same<decltype(lerp(matrix4x4{}, matrix4x4{}, T{})),  matrix4x4>::value, "");
	static_assert(std::is_same<decltype(lerp(matrix4x4{}, matrix4x4{}, 0.0f)), matrix4x4>::value, "");
	static_assert(std::is_same<decltype(lerp(matrix4x4{}, matrix4x4{}, 0.0L)), hamon::qvm::matrix<long double, 4, 4>>::value, "");

	{
		HAMON_CONSTEXPR matrix3x3 const m1
		{
			0, 0, 0,
			0, 0, 0,
			0, 0, 0,
		};
		HAMON_CONSTEXPR matrix3x3 const m2
		{
			0,  1, -2,
			4, -5,  6,
			8,  9, 10,
		};

		{
			HAMON_CONSTEXPR auto const m3 = lerp(m1, m2, T(0.0));
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0.0,  0.0,  0.0), m3[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0.0,  0.0,  0.0), m3[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0.0,  0.0,  0.0), m3[2]);
		}
		{
			HAMON_CONSTEXPR auto const m3 = lerp(m1, m2, T(0.5));
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0.0,  0.5, -1.0), m3[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 2.0, -2.5,  3.0), m3[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 4.0,  4.5,  5.0), m3[2]);
		}
		{
			HAMON_CONSTEXPR auto const m3 = lerp(m1, m2, T(1.0));
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0.0,  1.0, -2.0), m3[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 4.0, -5.0,  6.0), m3[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 8.0,  9.0, 10.0), m3[2]);
		}
	}
	{
		HAMON_CONSTEXPR matrix3x3 const m1
		{
			10, 10, 10,
			20, 20, 20,
			30, 30, 30,
		};
		HAMON_CONSTEXPR matrix3x3 const m2
		{
			11, 12, 13,
			21, 22, 23,
			31, 32, 33,
		};

		{
			HAMON_CONSTEXPR auto const m3 = lerp(m1, m2, T(0.0));
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 10.0, 10.0, 10.0), m3[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 20.0, 20.0, 20.0), m3[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 30.0, 30.0, 30.0), m3[2]);
		}
		{
			HAMON_CONSTEXPR auto const m3 = lerp(m1, m2, 0.5);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 10.5, 11.0, 11.5), m3[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 20.5, 21.0, 21.5), m3[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 30.5, 31.0, 31.5), m3[2]);
		}
		{
			HAMON_CONSTEXPR auto const m3 = lerp(m1, m2, 1.0f);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 11.0, 12.0, 13.0), m3[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 21.0, 22.0, 23.0), m3[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 31.0, 32.0, 33.0), m3[2]);
		}
	}
	{
		HAMON_CONSTEXPR matrix3x4 const m1
		{
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
		};
		HAMON_CONSTEXPR matrix3x4 const m2
		{
			0,  1, -2,  3,
			4, -5,  6,  7,
			8,  9, 10,-11,
		};

		{
			HAMON_CONSTEXPR auto const m3 = lerp(m1, m2, T(0.0));
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 0.0,  0.0,  0.0,  0.0), m3[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 0.0,  0.0,  0.0,  0.0), m3[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 0.0,  0.0,  0.0,  0.0), m3[2]);
		}
		{
			HAMON_CONSTEXPR auto const m3 = lerp(m1, m2, T(0.5));
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 0.0,  0.5, -1.0,  1.5), m3[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 2.0, -2.5,  3.0,  3.5), m3[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 4.0,  4.5,  5.0, -5.5), m3[2]);
		}
		{
			HAMON_CONSTEXPR auto const m3 = lerp(m1, m2, T(1.0));
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 0.0,  1.0, -2.0,  3.0), m3[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 4.0, -5.0,  6.0,  7.0), m3[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 8.0,  9.0, 10.0,-11.0), m3[2]);
		}
	}
	{
		HAMON_CONSTEXPR matrix3x4 const m1
		{
			10, 10, 10, 10,
			20, 20, 20, 20,
			30, 30, 30, 30,
		};
		HAMON_CONSTEXPR matrix3x4 const m2
		{
			11, 12, 13, 14,
			21, 22, 23, 24,
			31, 32, 33, 34,
		};

		{
			HAMON_CONSTEXPR auto const m3 = lerp(m1, m2, T(0.0));
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 10.0, 10.0, 10.0, 10.0), m3[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 20.0, 20.0, 20.0, 20.0), m3[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 30.0, 30.0, 30.0, 30.0), m3[2]);
		}
		{
			HAMON_CONSTEXPR auto const m3 = lerp(m1, m2, 0.5);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 10.5, 11.0, 11.5, 12.0), m3[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 20.5, 21.0, 21.5, 22.0), m3[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 30.5, 31.0, 31.5, 32.0), m3[2]);
		}
		{
			HAMON_CONSTEXPR auto const m3 = lerp(m1, m2, 1.0f);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 11.0, 12.0, 13.0, 14.0), m3[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 21.0, 22.0, 23.0, 24.0), m3[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 31.0, 32.0, 33.0, 34.0), m3[2]);
		}
	}
	{
		HAMON_CONSTEXPR matrix4x3 const m1
		{
			0, 0, 0,
			0, 0, 0,
			0, 0, 0,
			0, 0, 0,
		};
		HAMON_CONSTEXPR matrix4x3 const m2
		{
			  0,  1, -2,
			  4, -5,  6,
			  8,  9, 10,
			-12, 13, 14,
		};

		{
			HAMON_CONSTEXPR auto const m3 = lerp(m1, m2, T(0.0));
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0.0,  0.0,  0.0), m3[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0.0,  0.0,  0.0), m3[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0.0,  0.0,  0.0), m3[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0.0,  0.0,  0.0), m3[3]);
		}
		{
			HAMON_CONSTEXPR auto const m3 = lerp(m1, m2, T(0.5));
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0.0,  0.5, -1.0), m3[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 2.0, -2.5,  3.0), m3[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 4.0,  4.5,  5.0), m3[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-6.0,  6.5,  7.0), m3[3]);
		}
		{
			HAMON_CONSTEXPR auto const m3 = lerp(m1, m2, T(1.0));
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(  0.0,  1.0, -2.0), m3[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(  4.0, -5.0,  6.0), m3[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(  8.0,  9.0, 10.0), m3[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-12.0, 13.0, 14.0), m3[3]);
		}
	}
	{
		HAMON_CONSTEXPR matrix4x3 const m1
		{
			10, 10, 10,
			20, 20, 20,
			30, 30, 30,
			40, 40, 40,
		};
		HAMON_CONSTEXPR matrix4x3 const m2
		{
			11, 12, 13,
			21, 22, 23,
			31, 32, 33,
			41, 42, 43,
		};

		{
			HAMON_CONSTEXPR auto const m3 = lerp(m1, m2, T(0.0));
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 10.0, 10.0, 10.0), m3[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 20.0, 20.0, 20.0), m3[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 30.0, 30.0, 30.0), m3[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 40.0, 40.0, 40.0), m3[3]);
		}
		{
			HAMON_CONSTEXPR auto const m3 = lerp(m1, m2, 0.5);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 10.5, 11.0, 11.5), m3[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 20.5, 21.0, 21.5), m3[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 30.5, 31.0, 31.5), m3[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 40.5, 41.0, 41.5), m3[3]);
		}
		{
			HAMON_CONSTEXPR auto const m3 = lerp(m1, m2, 1.0f);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 11.0, 12.0, 13.0), m3[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 21.0, 22.0, 23.0), m3[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 31.0, 32.0, 33.0), m3[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 41.0, 42.0, 43.0), m3[3]);
		}
	}
	{
		HAMON_CONSTEXPR matrix4x4 const m1
		{
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
		};
		HAMON_CONSTEXPR matrix4x4 const m2
		{
			  0,  1, -2,  3,
			  4, -5,  6,  7,
			  8,  9, 10,-11,
			-12, 13, 14, 15,
		};

		{
			HAMON_CONSTEXPR auto const m3 = lerp(m1, m2, T(0.0));
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 0.0,  0.0,  0.0,  0.0), m3[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 0.0,  0.0,  0.0,  0.0), m3[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 0.0,  0.0,  0.0,  0.0), m3[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 0.0,  0.0,  0.0,  0.0), m3[3]);
		}
		{
			HAMON_CONSTEXPR auto const m3 = lerp(m1, m2, T(0.5));
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 0.0,  0.5, -1.0,  1.5), m3[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 2.0, -2.5,  3.0,  3.5), m3[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 4.0,  4.5,  5.0, -5.5), m3[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-6.0,  6.5,  7.0,  7.5), m3[3]);
		}
		{
			HAMON_CONSTEXPR auto const m3 = lerp(m1, m2, T(1.0));
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(  0.0,  1.0, -2.0,  3.0), m3[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(  4.0, -5.0,  6.0,  7.0), m3[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(  8.0,  9.0, 10.0,-11.0), m3[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-12.0, 13.0, 14.0, 15.0), m3[3]);
		}
	}
	{
		HAMON_CONSTEXPR matrix4x4 const m1
		{
			10, 10, 10, 10,
			20, 20, 20, 20,
			30, 30, 30, 30,
			40, 40, 40, 40,
		};
		HAMON_CONSTEXPR matrix4x4 const m2
		{
			11, 12, 13, 14,
			21, 22, 23, 24,
			31, 32, 33, 34,
			41, 42, 43, 44,
		};

		{
			HAMON_CONSTEXPR auto const m3 = lerp(m1, m2, T(0.0));
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 10.0, 10.0, 10.0, 10.0), m3[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 20.0, 20.0, 20.0, 20.0), m3[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 30.0, 30.0, 30.0, 30.0), m3[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 40.0, 40.0, 40.0, 40.0), m3[3]);
		}
		{
			HAMON_CONSTEXPR auto const m3 = lerp(m1, m2, 0.5);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 10.5, 11.0, 11.5, 12.0), m3[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 20.5, 21.0, 21.5, 22.0), m3[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 30.5, 31.0, 31.5, 32.0), m3[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 40.5, 41.0, 41.5, 42.0), m3[3]);
		}
		{
			HAMON_CONSTEXPR auto const m3 = lerp(m1, m2, 1.0f);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 11.0, 12.0, 13.0, 14.0), m3[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 21.0, 22.0, 23.0, 24.0), m3[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 31.0, 32.0, 33.0, 34.0), m3[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 41.0, 42.0, 43.0, 44.0), m3[3]);
		}
	}
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
