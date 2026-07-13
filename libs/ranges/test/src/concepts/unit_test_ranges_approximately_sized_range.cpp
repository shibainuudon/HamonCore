/**
 *	@file	unit_test_ranges_approximately_sized_range.cpp
 *
 *	@brief	ranges::approximately_sized_range のテスト
 */

#include <hamon/ranges/concepts/approximately_sized_range.hpp>
#include <hamon/config.hpp>
#include "ranges_test.hpp"

#define HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(B, ...)	\
	static_assert(B == hamon::ranges::approximately_sized_range<__VA_ARGS__>, "")

namespace hamon_ranges_test
{

namespace approximately_sized_range_test
{

HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  int      [2]);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  int const[2]);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(false, int      []);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(false, int const[]);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  int      (&)[2]);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  int const(&)[2]);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  int      (&&)[2]);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  int const(&&)[2]);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(false, int      (*)[2]);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(false, int const(*)[2]);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(false, int      *);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(false, int const*);

HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  test_contiguous_range<int>);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  test_contiguous_range<int>&);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  test_contiguous_range<int>&&);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  test_random_access_range<int>);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  test_random_access_range<int>&);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  test_random_access_range<int>&&);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(false, test_bidirectional_range<int>);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(false, test_bidirectional_range<int>&);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(false, test_bidirectional_range<int>&&);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(false, test_forward_range<int>);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(false, test_forward_range<int>&);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(false, test_forward_range<int>&&);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(false, test_input_range<int>);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(false, test_input_range<int>&);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(false, test_input_range<int>&&);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(false, test_output_range<int>);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(false, test_output_range<int>&);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(false, test_output_range<int>&&);

HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  test_contiguous_sized_range<int>);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  test_contiguous_sized_range<int>&);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  test_contiguous_sized_range<int>&&);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  test_random_access_sized_range<int>);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  test_random_access_sized_range<int>&);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  test_random_access_sized_range<int>&&);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  test_bidirectional_sized_range<int>);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  test_bidirectional_sized_range<int>&);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  test_bidirectional_sized_range<int>&&);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  test_forward_sized_range<int>);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  test_forward_sized_range<int>&);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  test_forward_sized_range<int>&&);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  test_input_sized_range<int>);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  test_input_sized_range<int>&);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  test_input_sized_range<int>&&);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  test_output_sized_range<int>);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  test_output_sized_range<int>&);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  test_output_sized_range<int>&&);

struct R1
{
	using iterator = input_iterator_wrapper<int>;
	using sentinel = test_sentinel<iterator>;

	iterator begin() const;
	sentinel end()   const;
};

struct R2
{
	using iterator = input_iterator_wrapper<int>;
	using sentinel = test_sentinel<iterator>;

	iterator begin() const;
	sentinel end()   const;
	int reserve_hint() const;
};

struct R3
{
	using iterator = input_iterator_wrapper<int>;
	using sentinel = test_sentinel<iterator>;

	iterator begin() const;
	sentinel end()   const;
	friend int reserve_hint(R3 const&);
};

HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(false, R1);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  R2);
HAMON_RANGES_APPROXIMATELY_SIZED_RANGE_TEST(true,  R3);

}	// namespace approximately_sized_range_test

}	// namespace hamon_ranges_test
