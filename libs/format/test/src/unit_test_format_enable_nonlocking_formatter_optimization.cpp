/**
 *	@file	unit_test_format_enable_nonlocking_formatter_optimization.cpp
 *
 *	@brief	enable_nonlocking_formatter_optimization のテスト
 *
 *	template<class T>
 *	constexpr bool enable_nonlocking_formatter_optimization = false;
 */

#include <hamon/format.hpp>
#include <hamon/array.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/cstddef.hpp>
#include <hamon/deque.hpp>
#include <hamon/forward_list.hpp>
#include <hamon/list.hpp>
#include <hamon/map.hpp>
#include <hamon/pair.hpp>
#include <hamon/queue.hpp>
#include <hamon/set.hpp>
#include <hamon/span.hpp>
#include <hamon/stack.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/tuple.hpp>
#include <hamon/unordered_map.hpp>
#include <hamon/unordered_set.hpp>
#include <hamon/valarray.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_format_test
{

namespace enable_nonlocking_formatter_optimization_test
{

// Tests for P0645 Text Formatting
void test_P0645()
{
	static_assert(hamon::enable_nonlocking_formatter_optimization<char>);

	static_assert(hamon::enable_nonlocking_formatter_optimization<char*>);
	static_assert(hamon::enable_nonlocking_formatter_optimization<const char*>);
	static_assert(hamon::enable_nonlocking_formatter_optimization<char[42]>);

	static_assert(hamon::enable_nonlocking_formatter_optimization<hamon::basic_string<char>>);
	static_assert(hamon::enable_nonlocking_formatter_optimization<hamon::basic_string_view<char>>);

	static_assert(hamon::enable_nonlocking_formatter_optimization<wchar_t>);

	static_assert(hamon::enable_nonlocking_formatter_optimization<wchar_t*>);
	static_assert(hamon::enable_nonlocking_formatter_optimization<const wchar_t*>);
	static_assert(hamon::enable_nonlocking_formatter_optimization<wchar_t[42]>);

	static_assert(hamon::enable_nonlocking_formatter_optimization<hamon::basic_string<wchar_t>>);
	static_assert(hamon::enable_nonlocking_formatter_optimization<hamon::basic_string_view<wchar_t>>);

	static_assert(hamon::enable_nonlocking_formatter_optimization<bool>);

	static_assert(hamon::enable_nonlocking_formatter_optimization<signed char>);
	static_assert(hamon::enable_nonlocking_formatter_optimization<signed short>);
	static_assert(hamon::enable_nonlocking_formatter_optimization<signed int>);
	static_assert(hamon::enable_nonlocking_formatter_optimization<signed long>);
	static_assert(hamon::enable_nonlocking_formatter_optimization<signed long long>);

	static_assert(hamon::enable_nonlocking_formatter_optimization<unsigned char>);
	static_assert(hamon::enable_nonlocking_formatter_optimization<unsigned short>);
	static_assert(hamon::enable_nonlocking_formatter_optimization<unsigned int>);
	static_assert(hamon::enable_nonlocking_formatter_optimization<unsigned long>);
	static_assert(hamon::enable_nonlocking_formatter_optimization<unsigned long long>);

	static_assert(hamon::enable_nonlocking_formatter_optimization<float>);
	static_assert(hamon::enable_nonlocking_formatter_optimization<double>);
	static_assert(hamon::enable_nonlocking_formatter_optimization<long double>);

	static_assert(hamon::enable_nonlocking_formatter_optimization<hamon::nullptr_t>);
	static_assert(hamon::enable_nonlocking_formatter_optimization<void*>);
	static_assert(hamon::enable_nonlocking_formatter_optimization<const void*>);
}

// Tests for P1361 Integration of chrono with text formatting
//
// Some tests are commented out since these types haven't been implemented in
// chrono yet. After P1361 has been implemented these formatters should be all
// enabled.
void test_P1361()
{
	// The chrono formatters require localization support.
	// [time.format]/7
	//   If the chrono-specs is omitted, the chrono object is formatted as if by
	//   streaming it to std::ostringstream os with the formatting
	//   locale imbued and copying os.str() through the output iterator of the
	//   context with additional padding and adjustments as specified by the format
	//   specifiers.
	// In libc++ std:::ostringstream requires localization support.

	// TODO
#if 0//ndef TEST_HAS_NO_LOCALIZATION

	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::microseconds>);

	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::sys_time<std::chrono::microseconds>>);
#  if !defined(TEST_HAS_NO_EXPERIMENTAL_TZDB) && !defined(TEST_HAS_NO_TIME_ZONE_DATABASE) &&                           \
      !defined(TEST_HAS_NO_FILESYSTEM)
	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::utc_time<std::chrono::microseconds>>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::tai_time<std::chrono::microseconds>>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::gps_time<std::chrono::microseconds>>);
#  endif // !defined(TEST_HAS_NO_EXPERIMENTAL_TZDB) && !defined(TEST_HAS_NO_TIME_ZONE_DATABASE) &&
	// !defined(TEST_HAS_NO_FILESYSTEM)
	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::file_time<std::chrono::microseconds>>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::local_time<std::chrono::microseconds>>);

	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::day>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::month>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::year>);

	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::weekday>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::weekday_indexed>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::weekday_last>);

	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::month_day>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::month_day_last>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::month_weekday>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::month_weekday_last>);

	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::year_month>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::year_month_day>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::year_month_day_last>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::year_month_weekday>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::year_month_weekday_last>);

	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::hh_mm_ss<std::chrono::microseconds>>);

#  if !defined(TEST_HAS_NO_EXPERIMENTAL_TZDB)
	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::sys_info>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::local_info>);

#    if !defined(TEST_HAS_NO_TIME_ZONE_DATABASE) && !defined(TEST_HAS_NO_FILESYSTEM)
	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::chrono::zoned_time<std::chrono::microseconds>>);
#    endif // !defined(TEST_HAS_NO_TIME_ZONE_DATABASE) && !defined(TEST_HAS_NO_FILESYSTEM)
#  endif   // !defined(TEST_HAS_NO_EXPERIMENTAL_TZDB)

#endif // TEST_HAS_NO_LOCALIZATION
}

// Tests for P1636 Formatters for library types
//
// The paper hasn't been voted in so currently all formatters are disabled.
// Note the paper has been abandoned, the types are kept since other papers may
// introduce these formatters.
void test_P1636()
{
	// TODO
#if 0// ndef TEST_HAS_NO_THREADS
	static_assert(!hamon::enable_nonlocking_formatter_optimization<std::thread::id>);
#endif
}

template <class Vector>
void test_P2286_vector_bool()
{
	static_assert(!hamon::enable_nonlocking_formatter_optimization<Vector>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<typename Vector::reference>);

	// The const_reference shall be a bool.
	// However libc++ uses a __bit_const_reference<vector> when
	// _LIBCPP_ABI_BITSET_VECTOR_BOOL_CONST_SUBSCRIPT_RETURN_BOOL is defined.
	static_assert(!hamon::enable_nonlocking_formatter_optimization<const Vector&>);
	static_assert(hamon::enable_nonlocking_formatter_optimization<typename Vector::const_reference> ==
		hamon::same_as<typename Vector::const_reference, bool>);
}

// Tests for P2286 Formatting ranges
void test_P2286() {
	static_assert(!hamon::enable_nonlocking_formatter_optimization<hamon::array<int, 42>>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<hamon::vector<int>>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<hamon::deque<int>>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<hamon::forward_list<int>>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<hamon::list<int>>);

	static_assert(!hamon::enable_nonlocking_formatter_optimization<hamon::set<int>>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<hamon::map<int, int>>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<hamon::multiset<int>>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<hamon::multimap<int, int>>);

	static_assert(!hamon::enable_nonlocking_formatter_optimization<hamon::unordered_set<int>>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<hamon::unordered_map<int, int>>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<hamon::unordered_multiset<int>>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<hamon::unordered_multimap<int, int>>);

	static_assert(!hamon::enable_nonlocking_formatter_optimization<hamon::stack<int>>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<hamon::queue<int>>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<hamon::priority_queue<int>>);

	static_assert(!hamon::enable_nonlocking_formatter_optimization<hamon::span<int>>);

	static_assert(!hamon::enable_nonlocking_formatter_optimization<hamon::valarray<int>>);

	static_assert(!hamon::enable_nonlocking_formatter_optimization<hamon::pair<int, int>>);
	static_assert(!hamon::enable_nonlocking_formatter_optimization<hamon::tuple<int>>);

	// TODO
//	test_P2286_vector_bool<hamon::vector<bool>>();
//	test_P2286_vector_bool<hamon::vector<bool, hamon::allocator<bool>>>();
	//test_P2286_vector_bool<hamon::vector<bool, min_allocator<bool>>>();
}

// The trait does not care about whether the type is formattable, obviously the
// trait for non formattable types are not used.
struct not_formattable_nonlocking_disabled {};
struct not_formattable_nonlocking_enabled {};

}	// namespace enable_nonlocking_formatter_optimization_test

}	// namespace hamon_format_test

template <>
inline constexpr bool hamon::enable_nonlocking_formatter_optimization<
	hamon_format_test::enable_nonlocking_formatter_optimization_test::not_formattable_nonlocking_enabled> = true;

namespace hamon_format_test
{

namespace enable_nonlocking_formatter_optimization_test
{

static_assert(!hamon::enable_nonlocking_formatter_optimization<not_formattable_nonlocking_disabled>);
static_assert( hamon::enable_nonlocking_formatter_optimization<not_formattable_nonlocking_enabled>);

GTEST_TEST(FormatTest, BasicFormatParseContextTest)
{
	test_P0645();
	test_P1361();
	test_P1636();
	test_P2286();
}

}	// namespace enable_nonlocking_formatter_optimization_test

}	// namespace hamon_format_test
