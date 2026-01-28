/**
 *	@file	unit_test_bigint_pow_n.cpp
 *
 *	@brief	pow_n のテスト
 */

#include <hamon/bigint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_pow_n_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
test(BigInt const& x, hamon::uintmax_t y, BigInt const& expected, bool overflow)
{
	BigInt out{};
	bool f = hamon::pow_n(out, x, y);
	VERIFY(f == overflow)
	if (!overflow)
	{
		VERIFY(out == expected);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntAlgoTest, PowNTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{ 0},   0, hamon::uint128_t{1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{ 0},   1, hamon::uint128_t{0}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{ 0},   2, hamon::uint128_t{0}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{ 0},   3, hamon::uint128_t{0}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{ 0},  10, hamon::uint128_t{0}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{ 0}, 128, hamon::uint128_t{0}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{ 1},   0, hamon::uint128_t{1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{ 1},   1, hamon::uint128_t{1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{ 1},   2, hamon::uint128_t{1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{ 1},   3, hamon::uint128_t{1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{ 1},  10, hamon::uint128_t{1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{ 1}, 128, hamon::uint128_t{1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{ 2},   0, hamon::uint128_t{1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{ 2},   1, hamon::uint128_t{2}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{ 2},   2, hamon::uint128_t{4}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{ 2},   3, hamon::uint128_t{8}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{ 2},  10, hamon::uint128_t{1024}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{ 2}, 127, hamon::uint128_t{"170141183460469231731687303715884105728"}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{ 2}, 128, hamon::uint128_t{}, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{10},   0, hamon::uint128_t{1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{10},   1, hamon::uint128_t{10}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{10},   2, hamon::uint128_t{100}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{10},   3, hamon::uint128_t{1000}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{10},  10, hamon::uint128_t{10000000000}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{10},  37, hamon::uint128_t{"10000000000000000000000000000000000000"}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{10},  38, hamon::uint128_t{"100000000000000000000000000000000000000"}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::uint128_t{10},  39, hamon::uint128_t{}, true));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{  0},   0, hamon::int128_t{1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{  0},   1, hamon::int128_t{0}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{  0},   2, hamon::int128_t{0}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{  0},   3, hamon::int128_t{0}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{  0},  10, hamon::int128_t{0}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{  0}, 128, hamon::int128_t{0}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{  1},   0, hamon::int128_t{1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{  1},   1, hamon::int128_t{1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{  1},   2, hamon::int128_t{1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{  1},   3, hamon::int128_t{1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{  1},  10, hamon::int128_t{1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{  1}, 128, hamon::int128_t{1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{ -1},   0, hamon::int128_t{1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{ -1},   1, hamon::int128_t{-1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{ -1},   2, hamon::int128_t{1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{ -1},   3, hamon::int128_t{-1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{ -1},  10, hamon::int128_t{1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{ -1}, 128, hamon::int128_t{1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{  2},   0, hamon::int128_t{1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{  2},   1, hamon::int128_t{2}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{  2},   2, hamon::int128_t{4}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{  2},   3, hamon::int128_t{8}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{  2},  10, hamon::int128_t{1024}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{  2}, 127, hamon::int128_t{"170141183460469231731687303715884105728"}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{  2}, 128, hamon::int128_t{}, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{ -2},   0, hamon::int128_t{1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{ -2},   1, hamon::int128_t{-2}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{ -2},   2, hamon::int128_t{4}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{ -2},   3, hamon::int128_t{-8}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{ -2},  10, hamon::int128_t{1024}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{ -2}, 127, hamon::int128_t{"-170141183460469231731687303715884105728"}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{ -2}, 128, hamon::int128_t{}, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{ 10},   0, hamon::int128_t{1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{ 10},   1, hamon::int128_t{10}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{ 10},   2, hamon::int128_t{100}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{ 10},   3, hamon::int128_t{1000}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{ 10},  10, hamon::int128_t{10000000000}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{ 10},  37, hamon::int128_t{"10000000000000000000000000000000000000"}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{ 10},  38, hamon::int128_t{"100000000000000000000000000000000000000"}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{ 10},  39, hamon::int128_t{}, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{-10},   0, hamon::int128_t{1}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{-10},   1, hamon::int128_t{-10}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{-10},   2, hamon::int128_t{100}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{-10},   3, hamon::int128_t{-1000}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{-10},  10, hamon::int128_t{10000000000}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{-10},  37, hamon::int128_t{"-10000000000000000000000000000000000000"}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{-10},  38, hamon::int128_t{"100000000000000000000000000000000000000"}, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::int128_t{-10},  39, hamon::int128_t{}, true));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{  0},   0, hamon::bigint{1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{  0},   1, hamon::bigint{0}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{  0},   2, hamon::bigint{0}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{  0},   3, hamon::bigint{0}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{  0},  10, hamon::bigint{0}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{  0}, 128, hamon::bigint{0}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{  1},   0, hamon::bigint{1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{  1},   1, hamon::bigint{1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{  1},   2, hamon::bigint{1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{  1},   3, hamon::bigint{1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{  1},  10, hamon::bigint{1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{  1}, 128, hamon::bigint{1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{ -1},   0, hamon::bigint{1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{ -1},   1, hamon::bigint{-1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{ -1},   2, hamon::bigint{1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{ -1},   3, hamon::bigint{-1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{ -1},  10, hamon::bigint{1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{ -1}, 128, hamon::bigint{1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{  2},   0, hamon::bigint{1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{  2},   1, hamon::bigint{2}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{  2},   2, hamon::bigint{4}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{  2},   3, hamon::bigint{8}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{  2},  10, hamon::bigint{1024}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{  2}, 127, hamon::bigint{"170141183460469231731687303715884105728"}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{  2}, 128, hamon::bigint{"340282366920938463463374607431768211456"}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{ -2},   0, hamon::bigint{1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{ -2},   1, hamon::bigint{-2}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{ -2},   2, hamon::bigint{4}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{ -2},   3, hamon::bigint{-8}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{ -2},  10, hamon::bigint{1024}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{ -2}, 127, hamon::bigint{"-170141183460469231731687303715884105728"}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{ -2}, 128, hamon::bigint{"340282366920938463463374607431768211456"}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{ 10},   0, hamon::bigint{1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{ 10},   1, hamon::bigint{10}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{ 10},   2, hamon::bigint{100}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{ 10},   3, hamon::bigint{1000}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{ 10},  10, hamon::bigint{10000000000}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{ 10},  37, hamon::bigint{"10000000000000000000000000000000000000"}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{ 10},  38, hamon::bigint{"100000000000000000000000000000000000000"}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{ 10},  39, hamon::bigint{"1000000000000000000000000000000000000000"}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{-10},   0, hamon::bigint{1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{-10},   1, hamon::bigint{-10}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{-10},   2, hamon::bigint{100}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{-10},   3, hamon::bigint{-1000}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{-10},  10, hamon::bigint{10000000000}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{-10},  37, hamon::bigint{"-10000000000000000000000000000000000000"}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{-10},  38, hamon::bigint{"100000000000000000000000000000000000000"}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{-10},  39, hamon::bigint{"-1000000000000000000000000000000000000000"}, false));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{12345}, 10, hamon::bigint{"82207405646327461794954634291560556640625"}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{12345}, 11, hamon::bigint{"1014850422703912515858714960329315071728515625"}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{12345}, 12, hamon::bigint{"12528328468279800008275836185265394560488525390625"}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{12345}, 13, hamon::bigint{"154662214940914131102165197707101295849230845947265625"}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{-12345}, 10, hamon::bigint{"82207405646327461794954634291560556640625"}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{-12345}, 11, hamon::bigint{"-1014850422703912515858714960329315071728515625"}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{-12345}, 12, hamon::bigint{"12528328468279800008275836185265394560488525390625"}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::bigint{-12345}, 13, hamon::bigint{"-154662214940914131102165197707101295849230845947265625"}, false));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{ 0},   0, hamon::inplace_bigint<128>{1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{ 0},   1, hamon::inplace_bigint<128>{0}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{ 0},   2, hamon::inplace_bigint<128>{0}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{ 0},   3, hamon::inplace_bigint<128>{0}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{ 0},  10, hamon::inplace_bigint<128>{0}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{ 0}, 128, hamon::inplace_bigint<128>{0}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{ 1},   0, hamon::inplace_bigint<128>{1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{ 1},   1, hamon::inplace_bigint<128>{1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{ 1},   2, hamon::inplace_bigint<128>{1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{ 1},   3, hamon::inplace_bigint<128>{1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{ 1},  10, hamon::inplace_bigint<128>{1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{ 1}, 128, hamon::inplace_bigint<128>{1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{ 2},   0, hamon::inplace_bigint<128>{1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{ 2},   1, hamon::inplace_bigint<128>{2}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{ 2},   2, hamon::inplace_bigint<128>{4}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{ 2},   3, hamon::inplace_bigint<128>{8}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{ 2},  10, hamon::inplace_bigint<128>{1024}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{ 2}, 127, hamon::inplace_bigint<128>{"170141183460469231731687303715884105728"}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{ 2}, 128, hamon::inplace_bigint<128>{}, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{10},   0, hamon::inplace_bigint<128>{1}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{10},   1, hamon::inplace_bigint<128>{10}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{10},   2, hamon::inplace_bigint<128>{100}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{10},   3, hamon::inplace_bigint<128>{1000}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{10},  10, hamon::inplace_bigint<128>{10000000000}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{10},  37, hamon::inplace_bigint<128>{"10000000000000000000000000000000000000"}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{10},  38, hamon::inplace_bigint<128>{"100000000000000000000000000000000000000"}, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_bigint<128>{10},  39, hamon::inplace_bigint<128>{}, true));

}

}	// namespace bigint_pow_n_test

}	// namespace hamon_bigint_test
