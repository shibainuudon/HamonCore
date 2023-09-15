/**
 *	@file	unit_test_ranges_sized_range.cpp
 *
 *	@brief	ranges::sized_range のテスト
 */

#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/disable_sized_range.hpp>
#include <hamon/array.hpp>
#include <hamon/deque.hpp>
#include <hamon/forward_list.hpp>
#include <hamon/list.hpp>
#include <hamon/set.hpp>
#include <hamon/vector.hpp>
#include <string>
#include <unordered_set>
#include "ranges_test.hpp"

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_RANGES_SIZED_RANGE_TEST(B, ...)	\
	static_assert(B == hamon::ranges::sized_range<__VA_ARGS__>, "");	\
	static_assert(B == hamon::ranges::sized_range_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_RANGES_SIZED_RANGE_TEST(B, ...)	\
	static_assert(B == hamon::ranges::sized_range<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::ranges::sized_range_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_ranges_test
{

namespace sized_range_test
{

struct A {};
struct B {};

}	// namespace sized_range_test

}	// namespace hamon_ranges_test

HAMON_RANGES_START_NAMESPACE

template <>
HAMON_RANGES_SPECIALIZE_DISABLE_SIZED_RANGE(true,
	test_random_access_sized_range<hamon_ranges_test::sized_range_test::A>);

template <>
HAMON_RANGES_SPECIALIZE_DISABLE_SIZED_RANGE(true,
	test_bidirectional_sized_range<hamon_ranges_test::sized_range_test::B>);

HAMON_RANGES_END_NAMESPACE

HAMON_RANGES_SIZED_RANGE_TEST(true,  int      [2]);
HAMON_RANGES_SIZED_RANGE_TEST(true,  int const[2]);
HAMON_RANGES_SIZED_RANGE_TEST(false, int      []);
HAMON_RANGES_SIZED_RANGE_TEST(false, int const[]);
HAMON_RANGES_SIZED_RANGE_TEST(true,  int      (&)[2]);
HAMON_RANGES_SIZED_RANGE_TEST(true,  int const(&)[2]);
HAMON_RANGES_SIZED_RANGE_TEST(true,  int      (&&)[2]);
HAMON_RANGES_SIZED_RANGE_TEST(true,  int const(&&)[2]);
HAMON_RANGES_SIZED_RANGE_TEST(false, int      (*)[2]);
HAMON_RANGES_SIZED_RANGE_TEST(false, int const(*)[2]);
HAMON_RANGES_SIZED_RANGE_TEST(false, int      *);
HAMON_RANGES_SIZED_RANGE_TEST(false, int const*);

HAMON_RANGES_SIZED_RANGE_TEST(true,  hamon::array<int, 2>);
HAMON_RANGES_SIZED_RANGE_TEST(true,  hamon::vector<int>);
HAMON_RANGES_SIZED_RANGE_TEST(true,  hamon::deque<int>);
HAMON_RANGES_SIZED_RANGE_TEST(true,  hamon::list<int>);
HAMON_RANGES_SIZED_RANGE_TEST(false, hamon::forward_list<int>);
HAMON_RANGES_SIZED_RANGE_TEST(true,  hamon::set<int>);
HAMON_RANGES_SIZED_RANGE_TEST(true,  hamon::multiset<int>);
HAMON_RANGES_SIZED_RANGE_TEST(true,  std::unordered_set<int>);
HAMON_RANGES_SIZED_RANGE_TEST(true,  std::unordered_multiset<int>);
HAMON_RANGES_SIZED_RANGE_TEST(true,  std::string);

HAMON_RANGES_SIZED_RANGE_TEST(true,  test_contiguous_range<int>);
HAMON_RANGES_SIZED_RANGE_TEST(true,  test_contiguous_range<int>&);
HAMON_RANGES_SIZED_RANGE_TEST(true,  test_contiguous_range<int>&&);
HAMON_RANGES_SIZED_RANGE_TEST(true,  test_random_access_range<int>);
HAMON_RANGES_SIZED_RANGE_TEST(true,  test_random_access_range<int>&);
HAMON_RANGES_SIZED_RANGE_TEST(true,  test_random_access_range<int>&&);
HAMON_RANGES_SIZED_RANGE_TEST(false, test_bidirectional_range<int>);
HAMON_RANGES_SIZED_RANGE_TEST(false, test_bidirectional_range<int>&);
HAMON_RANGES_SIZED_RANGE_TEST(false, test_bidirectional_range<int>&&);
HAMON_RANGES_SIZED_RANGE_TEST(false, test_forward_range<int>);
HAMON_RANGES_SIZED_RANGE_TEST(false, test_forward_range<int>&);
HAMON_RANGES_SIZED_RANGE_TEST(false, test_forward_range<int>&&);
HAMON_RANGES_SIZED_RANGE_TEST(false, test_input_range<int>);
HAMON_RANGES_SIZED_RANGE_TEST(false, test_input_range<int>&);
HAMON_RANGES_SIZED_RANGE_TEST(false, test_input_range<int>&&);
HAMON_RANGES_SIZED_RANGE_TEST(false, test_output_range<int>);
HAMON_RANGES_SIZED_RANGE_TEST(false, test_output_range<int>&);
HAMON_RANGES_SIZED_RANGE_TEST(false, test_output_range<int>&&);

HAMON_RANGES_SIZED_RANGE_TEST(true,  test_contiguous_sized_range<int>);
HAMON_RANGES_SIZED_RANGE_TEST(true,  test_contiguous_sized_range<int>&);
HAMON_RANGES_SIZED_RANGE_TEST(true,  test_contiguous_sized_range<int>&&);
HAMON_RANGES_SIZED_RANGE_TEST(true,  test_random_access_sized_range<int>);
HAMON_RANGES_SIZED_RANGE_TEST(true,  test_random_access_sized_range<int>&);
HAMON_RANGES_SIZED_RANGE_TEST(true,  test_random_access_sized_range<int>&&);
HAMON_RANGES_SIZED_RANGE_TEST(true,  test_bidirectional_sized_range<int>);
HAMON_RANGES_SIZED_RANGE_TEST(true,  test_bidirectional_sized_range<int>&);
HAMON_RANGES_SIZED_RANGE_TEST(true,  test_bidirectional_sized_range<int>&&);
HAMON_RANGES_SIZED_RANGE_TEST(true,  test_forward_sized_range<int>);
HAMON_RANGES_SIZED_RANGE_TEST(true,  test_forward_sized_range<int>&);
HAMON_RANGES_SIZED_RANGE_TEST(true,  test_forward_sized_range<int>&&);
HAMON_RANGES_SIZED_RANGE_TEST(true,  test_input_sized_range<int>);
HAMON_RANGES_SIZED_RANGE_TEST(true,  test_input_sized_range<int>&);
HAMON_RANGES_SIZED_RANGE_TEST(true,  test_input_sized_range<int>&&);
HAMON_RANGES_SIZED_RANGE_TEST(true,  test_output_sized_range<int>);
HAMON_RANGES_SIZED_RANGE_TEST(true,  test_output_sized_range<int>&);
HAMON_RANGES_SIZED_RANGE_TEST(true,  test_output_sized_range<int>&&);

// Despite being disabled, this is still a sized_range because ranges::size(r)
// works, by using (ranges::end(r) - ranges::begin(r)).
HAMON_RANGES_SIZED_RANGE_TEST(true,  test_random_access_sized_range<hamon_ranges_test::sized_range_test::A>);
HAMON_RANGES_SIZED_RANGE_TEST(true,  test_random_access_sized_range<hamon_ranges_test::sized_range_test::A>&);

// This is not a sized range because ranges::size(r) cannot use member size,
// or ADL size, and (ranges::end(r) - ranges::begin(r)) is ill-formed for
// bidirectional iterators.
HAMON_RANGES_SIZED_RANGE_TEST(false, test_bidirectional_sized_range<hamon_ranges_test::sized_range_test::B>);
HAMON_RANGES_SIZED_RANGE_TEST(false, test_bidirectional_sized_range<hamon_ranges_test::sized_range_test::B>&);

#undef HAMON_RANGES_SIZED_RANGE_TEST
