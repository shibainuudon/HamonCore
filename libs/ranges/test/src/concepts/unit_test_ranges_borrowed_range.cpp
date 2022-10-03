/**
 *	@file	unit_test_ranges_borrowed_range.cpp
 *
 *	@brief	ranges::borrowed_range のテスト
 */

#include <hamon/ranges/concepts/borrowed_range.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
//#include <hamon/ranges/views/subrange.hpp>
//#include <hamon/ranges/views/empty_view.hpp>
//#include <hamon/ranges/views/iota_view.hpp>
//#include <hamon/ranges/views/ref_view.hpp>
//#include <hamon/string_view.hpp>
//#include <hamon/span.hpp>
#include "ranges_test.hpp"

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_RANGES_BORROWED_RANGE_TEST_IMPL(B, ...)	\
	static_assert(B == hamon::ranges::borrowed_range<__VA_ARGS__>, "")
#else
#  define HAMON_RANGES_BORROWED_RANGE_TEST_IMPL(B, ...)	\
	static_assert(B == hamon::ranges::borrowed_range<__VA_ARGS__>::value, "")
#endif

#define HAMON_RANGES_BORROWED_RANGE_TEST(B, ...)	                 \
	HAMON_RANGES_BORROWED_RANGE_TEST_IMPL(B,    __VA_ARGS__ );	     \
	HAMON_RANGES_BORROWED_RANGE_TEST_IMPL(B,    __VA_ARGS__ const);  \
	HAMON_RANGES_BORROWED_RANGE_TEST_IMPL(true, __VA_ARGS__ &);	     \
	HAMON_RANGES_BORROWED_RANGE_TEST_IMPL(true, __VA_ARGS__ const&); \
	HAMON_RANGES_BORROWED_RANGE_TEST_IMPL(B,    __VA_ARGS__ &&);	 \
	HAMON_RANGES_BORROWED_RANGE_TEST_IMPL(B,    __VA_ARGS__ const&&)

namespace hamon_ranges_test
{

namespace borrowed_range_test
{

struct A {};
struct B {};

}	// namespace borrowed_range_test

}	// namespace hamon_ranges_test

HAMON_RANGES_START_NAMESPACE

template <>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true,
	hamon_ranges_test::test_contiguous_range<hamon_ranges_test::borrowed_range_test::A>);

template <>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true,
	hamon_ranges_test::test_random_access_range<hamon_ranges_test::borrowed_range_test::B>);

HAMON_RANGES_END_NAMESPACE

HAMON_RANGES_BORROWED_RANGE_TEST_IMPL(false, int      [2]);
HAMON_RANGES_BORROWED_RANGE_TEST_IMPL(false, int const[2]);
HAMON_RANGES_BORROWED_RANGE_TEST_IMPL(false, int      []);
HAMON_RANGES_BORROWED_RANGE_TEST_IMPL(false, int const[]);
HAMON_RANGES_BORROWED_RANGE_TEST_IMPL(true,  int      (&)[2]);
HAMON_RANGES_BORROWED_RANGE_TEST_IMPL(true,  int const(&)[2]);
HAMON_RANGES_BORROWED_RANGE_TEST_IMPL(false, int      (&&)[2]);
HAMON_RANGES_BORROWED_RANGE_TEST_IMPL(false, int const(&&)[2]);
HAMON_RANGES_BORROWED_RANGE_TEST_IMPL(false, int      (*)[2]);
HAMON_RANGES_BORROWED_RANGE_TEST_IMPL(false, int const(*)[2]);
HAMON_RANGES_BORROWED_RANGE_TEST_IMPL(false, int      *);
HAMON_RANGES_BORROWED_RANGE_TEST_IMPL(false, int const*);

#if 0 // TODO
HAMON_RANGES_BORROWED_RANGE_TEST(true,  hamon::ranges::subrange<int*>);
HAMON_RANGES_BORROWED_RANGE_TEST(true,  hamon::ranges::subrange<contiguous_iterator_wrapper<int>>);
HAMON_RANGES_BORROWED_RANGE_TEST(true,  hamon::ranges::subrange<random_access_iterator_wrapper<int>>);
HAMON_RANGES_BORROWED_RANGE_TEST(true,  hamon::ranges::subrange<bidirectional_iterator_wrapper<int>>);
HAMON_RANGES_BORROWED_RANGE_TEST(true,  hamon::ranges::subrange<forward_iterator_wrapper<int>>);
HAMON_RANGES_BORROWED_RANGE_TEST(true,  hamon::ranges::subrange<input_iterator_wrapper<int>>);

#if !(defined(HAMON_STDLIB_DINKUMWARE) && defined(HAMON_USE_STD_RANGES))
HAMON_RANGES_BORROWED_RANGE_TEST(true, hamon::ranges::empty_view<int>);
#endif
HAMON_RANGES_BORROWED_RANGE_TEST(true, hamon::ranges::iota_view<int>);
HAMON_RANGES_BORROWED_RANGE_TEST(true, hamon::ranges::iota_view<int, int>);
HAMON_RANGES_BORROWED_RANGE_TEST(true, hamon::ranges::ref_view<int[5]>);

HAMON_RANGES_BORROWED_RANGE_TEST(true, hamon::string_view);
HAMON_RANGES_BORROWED_RANGE_TEST(true, hamon::wstring_view);
#if defined(HAMON_HAS_CXX20_CHAR8_T)
HAMON_RANGES_BORROWED_RANGE_TEST(true, hamon::u8string_view);
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
HAMON_RANGES_BORROWED_RANGE_TEST(true, hamon::u16string_view);
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
HAMON_RANGES_BORROWED_RANGE_TEST(true, hamon::u32string_view);
#endif

HAMON_RANGES_BORROWED_RANGE_TEST(true, hamon::span<int>);
HAMON_RANGES_BORROWED_RANGE_TEST(true, hamon::span<int, 99>);
#endif

HAMON_RANGES_BORROWED_RANGE_TEST(true,  test_contiguous_range<hamon_ranges_test::borrowed_range_test::A>);
HAMON_RANGES_BORROWED_RANGE_TEST(false, test_contiguous_range<hamon_ranges_test::borrowed_range_test::B>);
HAMON_RANGES_BORROWED_RANGE_TEST(false, test_random_access_range<hamon_ranges_test::borrowed_range_test::A>);
HAMON_RANGES_BORROWED_RANGE_TEST(true,  test_random_access_range<hamon_ranges_test::borrowed_range_test::B>);

HAMON_RANGES_BORROWED_RANGE_TEST(false, test_contiguous_range<int>);
HAMON_RANGES_BORROWED_RANGE_TEST(false, test_random_access_range<int>);
HAMON_RANGES_BORROWED_RANGE_TEST(false, test_bidirectional_range<int>);
HAMON_RANGES_BORROWED_RANGE_TEST(false, test_forward_range<int>);
HAMON_RANGES_BORROWED_RANGE_TEST(false, test_input_range<int>);
HAMON_RANGES_BORROWED_RANGE_TEST(false, test_output_range<int>);

HAMON_RANGES_BORROWED_RANGE_TEST(false, test_contiguous_sized_range<int>);
HAMON_RANGES_BORROWED_RANGE_TEST(false, test_random_access_sized_range<int>);
HAMON_RANGES_BORROWED_RANGE_TEST(false, test_bidirectional_sized_range<int>);
HAMON_RANGES_BORROWED_RANGE_TEST(false, test_forward_sized_range<int>);
HAMON_RANGES_BORROWED_RANGE_TEST(false, test_input_sized_range<int>);
HAMON_RANGES_BORROWED_RANGE_TEST(false, test_output_sized_range<int>);

#undef HAMON_RANGES_BORROWED_RANGE_TEST_IMPL
#undef HAMON_RANGES_BORROWED_RANGE_TEST
