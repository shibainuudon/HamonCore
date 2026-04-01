/**
 *	@file	unit_test_bigint_algo_bit_shift_left.cpp
 *
 *	@brief	bigint_algo::bit_shift_left のテスト
 */

#include <hamon/bigint/bigint_algo/bit_shift_left.hpp>
#include <hamon/array.hpp>
#include <hamon/cstddef.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/inplace_vector.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "bigint_algo_test_helper.hpp"

namespace hamon_bigint_test
{

namespace bigint_algo_bit_shift_left_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR bool
test(VectorType a, hamon::size_t b, VectorType const& expected, bool overflow)
{
	bool f = hamon::bigint_algo::bit_shift_left(a, b);
	VERIFY(a == expected);
	VERIFY(f == overflow);
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntAlgoTest, BitShiftLeftTest)
{
#if 0
	for (hamon::size_t j = 0; j < 10000; ++j)
	{
		{
			hamon::vector<hamon::uint8_t> a{0x01};
			for (hamon::size_t i = 0; i < 64; ++i)
			{
				hamon::bigint_algo::bit_shift_left(a, i);
			}
		}
		{
			hamon::array<hamon::uint8_t, 8> a{0x01};
			for (hamon::size_t i = 0; i < 64; ++i)
			{
				hamon::bigint_algo::bit_shift_left(a, i);
			}
		}
	}
#endif

	// vector
	{
		using Vector = hamon::vector<hamon::uint8_t>;
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0},   0, Vector{0}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0},   1, Vector{0}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0},   2, Vector{0}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0},   8, Vector{0}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0}, 100, Vector{0}, false));
	}
	{
		using Vector = hamon::vector<hamon::uint8_t>;
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{1},  0, Vector{0x01}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{1},  1, Vector{0x02}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{1},  2, Vector{0x04}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{1},  3, Vector{0x08}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{1},  7, Vector{0x80}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{1},  8, Vector{0x00, 0x01}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{1},  9, Vector{0x00, 0x02}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{1}, 15, Vector{0x00, 0x80}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{1}, 16, Vector{0x00, 0x00, 0x01}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{1}, 17, Vector{0x00, 0x00, 0x02}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{1}, 23, Vector{0x00, 0x00, 0x80}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{1}, 24, Vector{0x00, 0x00, 0x00, 0x01}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{1}, 25, Vector{0x00, 0x00, 0x00, 0x02}, false));
	}
	{
		using Vector = hamon::vector<hamon::uint8_t>;
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF},  0, Vector{0xFF, 0xFF}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF},  1, Vector{0xFE, 0xFF, 0x01}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF},  2, Vector{0xFC, 0xFF, 0x03}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF},  3, Vector{0xF8, 0xFF, 0x07}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF},  7, Vector{0x80, 0xFF, 0x7F}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF},  8, Vector{0x00, 0xFF, 0xFF}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF},  9, Vector{0x00, 0xFE, 0xFF, 0x01}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF}, 15, Vector{0x00, 0x80, 0xFF, 0x7F}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF}, 16, Vector{0x00, 0x00, 0xFF, 0xFF}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF}, 17, Vector{0x00, 0x00, 0xFE, 0xFF, 0x01}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF}, 23, Vector{0x00, 0x00, 0x80, 0xFF, 0x7F}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF}, 24, Vector{0x00, 0x00, 0x00, 0xFF, 0xFF}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF}, 25, Vector{0x00, 0x00, 0x00, 0xFE, 0xFF, 0x01}, false));
	}
	{
		using Vector = hamon::vector<hamon::uint64_t>;
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFFFFFFFFFFFFFFFF},   0, Vector{0xFFFFFFFFFFFFFFFF}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFFFFFFFFFFFFFFFF},   1, Vector{0xFFFFFFFFFFFFFFFE, 0x0000000000000001}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFFFFFFFFFFFFFFFF},  63, Vector{0x8000000000000000, 0x7FFFFFFFFFFFFFFF}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFFFFFFFFFFFFFFFF},  64, Vector{0x0000000000000000, 0xFFFFFFFFFFFFFFFF}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFFFFFFFFFFFFFFFF},  65, Vector{0x0000000000000000, 0xFFFFFFFFFFFFFFFE, 0x0000000000000001}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFFFFFFFFFFFFFFFF}, 127, Vector{0x0000000000000000, 0x8000000000000000, 0x7FFFFFFFFFFFFFFF}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFFFFFFFFFFFFFFFF}, 128, Vector{0x0000000000000000, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFFFFFFFFFFFFFFFF}, 129, Vector{0x0000000000000000, 0x0000000000000000, 0xFFFFFFFFFFFFFFFE, 0x0000000000000001}, false));
	}

	// inplace_vector
	{
		using Vector = hamon::inplace_vector<hamon::uint8_t, 3>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0},   0, Vector{0}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0},   1, Vector{0}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0},   2, Vector{0}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0},   8, Vector{0}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0}, 100, Vector{0}, false));
	}
	{
		using Vector = hamon::inplace_vector<hamon::uint8_t, 3>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1},  0, Vector{0x01}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1},  1, Vector{0x02}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1},  2, Vector{0x04}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1},  3, Vector{0x08}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1},  7, Vector{0x80}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1},  8, Vector{0x00, 0x01}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1},  9, Vector{0x00, 0x02}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1}, 15, Vector{0x00, 0x80}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1}, 16, Vector{0x00, 0x00, 0x01}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1}, 17, Vector{0x00, 0x00, 0x02}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1}, 23, Vector{0x00, 0x00, 0x80}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1}, 24, Vector{0x00}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1}, 25, Vector{0x00}, true));
	}
	{
		using Vector = hamon::inplace_vector<hamon::uint8_t, 4>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF},  0, Vector{0xFF, 0xFF}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF},  1, Vector{0xFE, 0xFF, 0x01}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF},  2, Vector{0xFC, 0xFF, 0x03}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF},  3, Vector{0xF8, 0xFF, 0x07}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF},  7, Vector{0x80, 0xFF, 0x7F}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF},  8, Vector{0x00, 0xFF, 0xFF}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF},  9, Vector{0x00, 0xFE, 0xFF, 0x01}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF}, 15, Vector{0x00, 0x80, 0xFF, 0x7F}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF}, 16, Vector{0x00, 0x00, 0xFF, 0xFF}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF}, 17, Vector{0x00, 0x00, 0xFE, 0xFF}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF}, 23, Vector{0x00, 0x00, 0x80, 0xFF}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF}, 24, Vector{0x00, 0x00, 0x00, 0xFF}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF}, 25, Vector{0x00, 0x00, 0x00, 0xFE}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF}, 31, Vector{0x00, 0x00, 0x00, 0x80}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF}, 32, Vector{0x00}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF}, 33, Vector{0x00}, true));
	}

	// array
	{
		using Vector = hamon::array<hamon::uint8_t, 3>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0},   0, Vector{0}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0},   1, Vector{0}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0},   2, Vector{0}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0},   8, Vector{0}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0}, 100, Vector{0}, false));
	}
	{
		using Vector = hamon::array<hamon::uint8_t, 3>;
		HAMON_CXX14_CONSTEXPR Vector const a{0xFF, 0x7F, 0x00};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a,  0, Vector{0xFF, 0x7F, 0x00}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a,  1, Vector{0xFE, 0xFF, 0x00}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a,  2, Vector{0xFC, 0xFF, 0x01}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a,  7, Vector{0x80, 0xFF, 0x3F}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a,  8, Vector{0x00, 0xFF, 0x7F}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a,  9, Vector{0x00, 0xFE, 0xFF}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 10, Vector{0x00, 0xFC, 0xFF}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 15, Vector{0x00, 0x80, 0xFF}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 16, Vector{0x00, 0x00, 0xFF}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 17, Vector{0x00, 0x00, 0xFE}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 22, Vector{0x00, 0x00, 0xC0}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 23, Vector{0x00, 0x00, 0x80}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 24, Vector{0x00, 0x00, 0x00}, true));
	}
	{
		using Vector = hamon::array<hamon::uint64_t, 2>;
		HAMON_CXX14_CONSTEXPR Vector const a{0x0123456789ABCDEF, 0x00};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a,  0, Vector{0x0123456789ABCDEF, 0x0000000000000000}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a,  1, Vector{0x02468ACF13579BDE, 0x0000000000000000}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a,  2, Vector{0x048D159E26AF37BC, 0x0000000000000000}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a,  3, Vector{0x091A2B3C4D5E6F78, 0x0000000000000000}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a,  4, Vector{0x123456789ABCDEF0, 0x0000000000000000}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a,  5, Vector{0x2468ACF13579BDE0, 0x0000000000000000}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a,  6, Vector{0x48D159E26AF37BC0, 0x0000000000000000}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a,  7, Vector{0x91A2B3C4D5E6F780, 0x0000000000000000}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a,  8, Vector{0x23456789ABCDEF00, 0x0000000000000001}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a,  9, Vector{0x468ACF13579BDE00, 0x0000000000000002}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 10, Vector{0x8D159E26AF37BC00, 0x0000000000000004}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 11, Vector{0x1A2B3C4D5E6F7800, 0x0000000000000009}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 63, Vector{0x8000000000000000, 0x0091A2B3C4D5E6F7}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 64, Vector{0x0000000000000000, 0x0123456789ABCDEF}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 65, Vector{0x0000000000000000, 0x02468ACF13579BDE}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 66, Vector{0x0000000000000000, 0x048D159E26AF37BC}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 67, Vector{0x0000000000000000, 0x091A2B3C4D5E6F78}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 68, Vector{0x0000000000000000, 0x123456789ABCDEF0}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 69, Vector{0x0000000000000000, 0x2468ACF13579BDE0}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 70, Vector{0x0000000000000000, 0x48D159E26AF37BC0}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 71, Vector{0x0000000000000000, 0x91A2B3C4D5E6F780}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 72, Vector{0x0000000000000000, 0x23456789ABCDEF00}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 73, Vector{0x0000000000000000, 0x468ACF13579BDE00}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 74, Vector{0x0000000000000000, 0x8D159E26AF37BC00}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 75, Vector{0x0000000000000000, 0x1A2B3C4D5E6F7800}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a,126, Vector{0x0000000000000000, 0xC000000000000000}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a,127, Vector{0x0000000000000000, 0x8000000000000000}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a,128, Vector{0x0000000000000000, 0x0000000000000000}, true));
	}

	// MyVector
	{
		using Vector = MyVector<hamon::uint8_t, 3>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0},   0, Vector{0}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0},   1, Vector{0}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0},   2, Vector{0}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0},   8, Vector{0}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0}, 100, Vector{0}, false));
	}
	{
		using Vector = MyVector<hamon::uint8_t, 3>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1},  0, Vector{0x01}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1},  1, Vector{0x02}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1},  2, Vector{0x04}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1},  3, Vector{0x08}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1},  7, Vector{0x80}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1},  8, Vector{0x00, 0x01}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1},  9, Vector{0x00, 0x02}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1}, 15, Vector{0x00, 0x80}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1}, 16, Vector{0x00, 0x00, 0x01}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1}, 17, Vector{0x00, 0x00, 0x02}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1}, 23, Vector{0x00, 0x00, 0x80}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1}, 24, Vector{0x00}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{1}, 25, Vector{0x00}, true));
	}
	{
		using Vector = MyVector<hamon::uint8_t, 4>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF},  0, Vector{0xFF, 0xFF}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF},  1, Vector{0xFE, 0xFF, 0x01}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF},  2, Vector{0xFC, 0xFF, 0x03}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF},  3, Vector{0xF8, 0xFF, 0x07}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF},  7, Vector{0x80, 0xFF, 0x7F}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF},  8, Vector{0x00, 0xFF, 0xFF}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF},  9, Vector{0x00, 0xFE, 0xFF, 0x01}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF}, 15, Vector{0x00, 0x80, 0xFF, 0x7F}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF}, 16, Vector{0x00, 0x00, 0xFF, 0xFF}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF}, 17, Vector{0x00, 0x00, 0xFE, 0xFF}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF}, 23, Vector{0x00, 0x00, 0x80, 0xFF}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF}, 24, Vector{0x00, 0x00, 0x00, 0xFF}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF}, 25, Vector{0x00, 0x00, 0x00, 0xFE}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF}, 31, Vector{0x00, 0x00, 0x00, 0x80}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF}, 32, Vector{0x00}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{0xFF, 0xFF}, 33, Vector{0x00}, true));
	}
}

}	// namespace bigint_algo_bit_shift_left_test

}	// namespace hamon_bigint_test
