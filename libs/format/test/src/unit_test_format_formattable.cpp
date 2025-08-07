/**
 *	@file	unit_test_format_formattable.cpp
 *
 *	@brief	formattable のテスト
 *
 *	template<class T, class charT>
 *	concept formattable = see below;
 */

#include <hamon/format/formattable.hpp>
#include <hamon/format/formatter.hpp>
#include <hamon/array.hpp>
#include <hamon/bitset.hpp>
#include <hamon/chrono.hpp>
#include <hamon/complex.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/cstddef.hpp>
#include <hamon/deque.hpp>
#include <hamon/flat_map.hpp>
#include <hamon/flat_set.hpp>
#include <hamon/forward_list.hpp>
#include <hamon/list.hpp>
#include <hamon/map.hpp>
#include <hamon/memory.hpp>
#include <hamon/optional.hpp>
#include <hamon/pair.hpp>
#include <hamon/queue.hpp>
#include <hamon/set.hpp>
#include <hamon/span.hpp>
#include <hamon/stack.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/system_error/error_code.hpp>
#include <hamon/tuple.hpp>
#include <hamon/unordered_map.hpp>
#include <hamon/unordered_set.hpp>
#include <hamon/valarray.hpp>
#include <hamon/variant.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>

// TODO
#include <regex>

namespace hamon_format_test
{

namespace formattable_test
{

template <class T, class CharT>
void assert_is_not_formattable()
{
	static_assert(!hamon::formattable<      T, CharT>);
	static_assert(!hamon::formattable<      T&, CharT>);
	static_assert(!hamon::formattable<      T&&, CharT>);
	static_assert(!hamon::formattable<const T, CharT>);
	static_assert(!hamon::formattable<const T&, CharT>);
	static_assert(!hamon::formattable<const T&&, CharT>);
}

template <class T, class CharT>
void assert_is_formattable()
{
	// Only formatters for CharT == char || CharT == wchar_t are enabled for the
	// standard formatters. When CharT is a different type the formatter should
	// be disabled.
	if constexpr (hamon::same_as<CharT, char> || hamon::same_as<CharT, wchar_t>)
	{
		static_assert(hamon::formattable<      T, CharT>);
		static_assert(hamon::formattable<      T&, CharT>);
		static_assert(hamon::formattable<      T&&, CharT>);
		static_assert(hamon::formattable<const T, CharT>);
		static_assert(hamon::formattable<const T&, CharT>);
		static_assert(hamon::formattable<const T&&, CharT>);
	}
	else
	{
		assert_is_not_formattable<T, CharT>();
	}
}

// Tests for P0645 Text Formatting
template <class CharT>
void test_P0645()
{
	// Tests the special formatter that converts a char to a wchar_t.
	assert_is_formattable<char, wchar_t>();

	assert_is_formattable<CharT, CharT>();

	assert_is_formattable<CharT*, CharT>();
	assert_is_formattable<const CharT*, CharT>();
	assert_is_formattable<CharT[42], CharT>();
	if constexpr (!hamon::same_as<CharT, int>)
	{
		// string and string_view only work with proper character types
		assert_is_formattable<hamon::basic_string<CharT>, CharT>();
		assert_is_formattable<hamon::basic_string_view<CharT>, CharT>();
	}

	assert_is_formattable<bool, CharT>();

	assert_is_formattable<signed char, CharT>();
	assert_is_formattable<signed short, CharT>();
	assert_is_formattable<signed int, CharT>();
	assert_is_formattable<signed long, CharT>();
	assert_is_formattable<signed long long, CharT>();

	assert_is_formattable<unsigned char, CharT>();
	assert_is_formattable<unsigned short, CharT>();
	assert_is_formattable<unsigned int, CharT>();
	assert_is_formattable<unsigned long, CharT>();
	assert_is_formattable<unsigned long long, CharT>();

	assert_is_formattable<float, CharT>();
	assert_is_formattable<double, CharT>();
	assert_is_formattable<long double, CharT>();

	assert_is_formattable<hamon::nullptr_t, CharT>();
	assert_is_formattable<void*, CharT>();
	assert_is_formattable<const void*, CharT>();
}

// Tests for P1361 Integration of chrono with text formatting
//
// Some tests are commented out since these types haven't been implemented in
// chrono yet. After P1361 has been implemented these formatters should be all
// enabled.
template <class CharT>
void test_P1361()
{
#if 0	// TODO
	// The chrono formatters require localization support.
	// [time.format]/7
	//   If the chrono-specs is omitted, the chrono object is formatted as if by
	//   streaming it to std::ostringstream os with the formatting
	//   locale imbued and copying os.str() through the output iterator of the
	//   context with additional padding and adjustments as specified by the format
	//   specifiers.
	// In libc++ std:::ostringstream requires localization support.
#ifndef TEST_HAS_NO_LOCALIZATION

	assert_is_formattable<hamon::chrono::microseconds, CharT>();

	assert_is_formattable<hamon::chrono::sys_time<hamon::chrono::microseconds>, CharT>();
#  if !defined(TEST_HAS_NO_EXPERIMENTAL_TZDB) && !defined(TEST_HAS_NO_TIME_ZONE_DATABASE) &&                           \
      !defined(TEST_HAS_NO_FILESYSTEM)
// TODO
//	assert_is_formattable<hamon::chrono::utc_time<hamon::chrono::microseconds>, CharT>();
//	assert_is_formattable<hamon::chrono::tai_time<hamon::chrono::microseconds>, CharT>();
//	assert_is_formattable<hamon::chrono::gps_time<hamon::chrono::microseconds>, CharT>();

#  endif // !defined(TEST_HAS_NO_EXPERIMENTAL_TZDB) && !defined(TEST_HAS_NO_TIME_ZONE_DATABASE) &&
	// !defined(TEST_HAS_NO_FILESYSTEM)

//	assert_is_formattable<hamon::chrono::file_time<hamon::chrono::microseconds>, CharT>();
	assert_is_formattable<hamon::chrono::local_time<hamon::chrono::microseconds>, CharT>();

	assert_is_formattable<hamon::chrono::day, CharT>();
	assert_is_formattable<hamon::chrono::month, CharT>();
	assert_is_formattable<hamon::chrono::year, CharT>();

	assert_is_formattable<hamon::chrono::weekday, CharT>();
	assert_is_formattable<hamon::chrono::weekday_indexed, CharT>();
	assert_is_formattable<hamon::chrono::weekday_last, CharT>();

	assert_is_formattable<hamon::chrono::month_day, CharT>();
	assert_is_formattable<hamon::chrono::month_day_last, CharT>();
	assert_is_formattable<hamon::chrono::month_weekday, CharT>();
	assert_is_formattable<hamon::chrono::month_weekday_last, CharT>();

	assert_is_formattable<hamon::chrono::year_month, CharT>();
	assert_is_formattable<hamon::chrono::year_month_day, CharT>();
	assert_is_formattable<hamon::chrono::year_month_day_last, CharT>();
	assert_is_formattable<hamon::chrono::year_month_weekday, CharT>();
	assert_is_formattable<hamon::chrono::year_month_weekday_last, CharT>();

//	assert_is_formattable<hamon::chrono::hh_mm_ss<hamon::chrono::microseconds>, CharT>();

#  if !defined(TEST_HAS_NO_EXPERIMENTAL_TZDB)
//	assert_is_formattable<hamon::chrono::sys_info, CharT>();
//	assert_is_formattable<hamon::chrono::local_info, CharT>();

#    if !defined(TEST_HAS_NO_TIME_ZONE_DATABASE) && !defined(TEST_HAS_NO_FILESYSTEM)
//	assert_is_formattable<hamon::chrono::zoned_time<hamon::chrono::microseconds>, CharT>();
#    endif // !defined(TEST_HAS_NO_TIME_ZONE_DATABASE) && !defined(TEST_HAS_NO_FILESYSTEM)
#  endif   // !defined(TEST_HAS_NO_EXPERIMENTAL_TZDB)

#endif // TEST_HAS_NO_LOCALIZATION
#endif
}

// Tests for P1636 Formatters for library types
//
// The paper hasn't been voted in so currently all formatters are disabled.
// Note the paper has been abandoned, the types are kept since other papers may
// introduce these formatters.
template <class CharT>
void test_P1636()
{
	assert_is_not_formattable<std::basic_streambuf<CharT>, CharT>();
	assert_is_not_formattable<hamon::bitset<42>, CharT>();
	assert_is_not_formattable<hamon::complex<double>, CharT>();
	assert_is_not_formattable<hamon::error_code, CharT>();
//	assert_is_not_formattable<hamon::filesystem::path, CharT>();	// TODO
	assert_is_not_formattable<hamon::shared_ptr<int>, CharT>();
#ifndef TEST_HAS_NO_LOCALIZATION
	if constexpr (!hamon::same_as<CharT, int>) // sub_match only works with proper character types
	{
		assert_is_not_formattable<std::sub_match<CharT*>, CharT>();
	}
#endif
#ifndef TEST_HAS_NO_THREADS
//	assert_is_formattable<std::thread::id, CharT>();	// TODO
#endif
	assert_is_not_formattable<hamon::unique_ptr<int>, CharT>();
}

template <class CharT, class Vector>
void test_P2286_vector_bool()
{
	assert_is_formattable<Vector, CharT>();
	assert_is_formattable<typename Vector::reference, CharT>();

	// The const_reference shall be a bool.
	// However libc++ uses a __bit_const_reference<vector> when
	// _LIBCPP_ABI_BITSET_VECTOR_BOOL_CONST_SUBSCRIPT_RETURN_BOOL is defined.
	assert_is_formattable<const Vector&, CharT>();
	assert_is_formattable<typename Vector::const_reference, CharT>();
}

// Tests for P2286 Formatting ranges
template <class CharT>
void test_P2286()
{
	assert_is_formattable<hamon::array<int, 42>, CharT>();
	assert_is_formattable<hamon::vector<int>, CharT>();
	assert_is_formattable<hamon::deque<int>, CharT>();
	assert_is_formattable<hamon::forward_list<int>, CharT>();
	assert_is_formattable<hamon::list<int>, CharT>();

	assert_is_formattable<hamon::set<int>, CharT>();
	assert_is_formattable<hamon::map<int, int>, CharT>();
	assert_is_formattable<hamon::multiset<int>, CharT>();
	assert_is_formattable<hamon::multimap<int, int>, CharT>();

	assert_is_formattable<hamon::flat_set<int>, CharT>();
	assert_is_formattable<hamon::flat_map<int, int>, CharT>();
	assert_is_formattable<hamon::flat_multiset<int>, CharT>();
	assert_is_formattable<hamon::flat_multimap<int, int>, CharT>();

	assert_is_formattable<hamon::unordered_set<int>, CharT>();
	assert_is_formattable<hamon::unordered_map<int, int>, CharT>();
	assert_is_formattable<hamon::unordered_multiset<int>, CharT>();
	assert_is_formattable<hamon::unordered_multimap<int, int>, CharT>();

#if 0	// TODO
	assert_is_formattable<hamon::stack<int>, CharT>();
	assert_is_formattable<hamon::queue<int>, CharT>();
	assert_is_formattable<hamon::priority_queue<int>, CharT>();
#endif

	assert_is_formattable<hamon::span<int>, CharT>();

	assert_is_formattable<hamon::valarray<int>, CharT>();

	assert_is_formattable<hamon::pair<int, int>, CharT>();
	assert_is_formattable<hamon::tuple<int>, CharT>();

#if 0	// TODO
	test_P2286_vector_bool<CharT, hamon::vector<bool>>();
	test_P2286_vector_bool<CharT, hamon::vector<bool, hamon::allocator<bool>>>();
//	test_P2286_vector_bool<CharT, hamon::vector<bool, min_allocator<bool>>>();	// TODO
#endif
}

// Tests volatile qualified objects are no longer formattable.
template <class CharT>
void test_LWG3631()
{
	assert_is_not_formattable<volatile CharT, CharT>();

	assert_is_not_formattable<volatile bool, CharT>();

	assert_is_not_formattable<volatile signed int, CharT>();
	assert_is_not_formattable<volatile unsigned int, CharT>();

	assert_is_not_formattable<volatile hamon::chrono::microseconds, CharT>();
	assert_is_not_formattable<volatile hamon::chrono::sys_time<hamon::chrono::microseconds>, CharT>();
	assert_is_not_formattable<volatile hamon::chrono::day, CharT>();

	assert_is_not_formattable<hamon::array<volatile int, 42>, CharT>();

	assert_is_not_formattable<hamon::pair<volatile int, int>, CharT>();
	assert_is_not_formattable<hamon::pair<int, volatile int>, CharT>();
	assert_is_not_formattable<hamon::pair<volatile int, volatile int>, CharT>();
}

void test_LWG3944()
{
	assert_is_not_formattable<char*, wchar_t>();
	assert_is_not_formattable<const char*, wchar_t>();
	assert_is_not_formattable<char[42], wchar_t>();
	assert_is_not_formattable<hamon::string, wchar_t>();
	assert_is_not_formattable<hamon::string_view, wchar_t>();

	assert_is_formattable<hamon::vector<char>, wchar_t>();
	assert_is_formattable<hamon::set<char>, wchar_t>();
	assert_is_formattable<hamon::map<char, char>, wchar_t>();
	assert_is_formattable<hamon::tuple<char>, wchar_t>();
}

class c
{
	void f();
	void fc() const;
	static void sf();
};

enum e { a };

enum class ec { a };

template <class CharT>
void test_disabled()
{
	assert_is_not_formattable<const char*, wchar_t>();
	assert_is_not_formattable<const char*, char8_t>();
	assert_is_not_formattable<const char*, char16_t>();
	assert_is_not_formattable<const char*, char32_t>();

	assert_is_not_formattable<c, CharT>();
	assert_is_not_formattable<const c, CharT>();
	assert_is_not_formattable<volatile c, CharT>();
	assert_is_not_formattable<const volatile c, CharT>();

	assert_is_not_formattable<e, CharT>();
	assert_is_not_formattable<const e, CharT>();
	assert_is_not_formattable<volatile e, CharT>();
	assert_is_not_formattable<const volatile e, CharT>();

	assert_is_not_formattable<ec, CharT>();
	assert_is_not_formattable<const ec, CharT>();
	assert_is_not_formattable<volatile ec, CharT>();
	assert_is_not_formattable<const volatile ec, CharT>();

	assert_is_not_formattable<int*, CharT>();
	assert_is_not_formattable<const int*, CharT>();
	assert_is_not_formattable<volatile int*, CharT>();
	assert_is_not_formattable<const volatile int*, CharT>();

	assert_is_not_formattable<c*, CharT>();
	assert_is_not_formattable<const c*, CharT>();
	assert_is_not_formattable<volatile c*, CharT>();
	assert_is_not_formattable<const volatile c*, CharT>();

	assert_is_not_formattable<e*, CharT>();
	assert_is_not_formattable<const e*, CharT>();
	assert_is_not_formattable<volatile e*, CharT>();
	assert_is_not_formattable<const volatile e*, CharT>();

	assert_is_not_formattable<ec*, CharT>();
	assert_is_not_formattable<const ec*, CharT>();
	assert_is_not_formattable<volatile ec*, CharT>();
	assert_is_not_formattable<const volatile ec*, CharT>();

	assert_is_not_formattable<void (*)(), CharT>();
	assert_is_not_formattable<void (c::*)(), CharT>();
	assert_is_not_formattable<void (c::*)() const, CharT>();

	assert_is_not_formattable<hamon::optional<int>, CharT>();
	assert_is_not_formattable<hamon::variant<int>, CharT>();

	assert_is_not_formattable<hamon::shared_ptr<c>, CharT>();
	assert_is_not_formattable<hamon::unique_ptr<c>, CharT>();

	assert_is_not_formattable<hamon::array<c, 42>, CharT>();
	assert_is_not_formattable<hamon::vector<c>, CharT>();
	assert_is_not_formattable<hamon::deque<c>, CharT>();
	assert_is_not_formattable<hamon::forward_list<c>, CharT>();
	assert_is_not_formattable<hamon::list<c>, CharT>();

	assert_is_not_formattable<hamon::set<c>, CharT>();
	assert_is_not_formattable<hamon::map<c, int>, CharT>();
	assert_is_not_formattable<hamon::multiset<c>, CharT>();
	assert_is_not_formattable<hamon::multimap<c, int>, CharT>();

	assert_is_not_formattable<hamon::unordered_set<c>, CharT>();
	assert_is_not_formattable<hamon::unordered_map<c, int>, CharT>();
	assert_is_not_formattable<hamon::unordered_multiset<c>, CharT>();
	assert_is_not_formattable<hamon::unordered_multimap<c, int>, CharT>();

	assert_is_not_formattable<hamon::stack<c>, CharT>();
	assert_is_not_formattable<hamon::queue<c>, CharT>();
	assert_is_not_formattable<hamon::priority_queue<c>, CharT>();

	assert_is_not_formattable<hamon::span<c>, CharT>();

	assert_is_not_formattable<hamon::valarray<c>, CharT>();

	assert_is_not_formattable<hamon::pair<c, int>, CharT>();
	assert_is_not_formattable<hamon::tuple<c>, CharT>();

	assert_is_not_formattable<hamon::optional<c>, CharT>();
	assert_is_not_formattable<hamon::variant<c>, CharT>();
}

struct abstract
{
	virtual ~abstract() = 0;
};

}	// namespace formattable_test

}	// namespace hamon_format_test

template <class CharT>
	requires hamon::same_as<CharT, char> || hamon::same_as<CharT, wchar_t>
struct hamon::formatter<hamon_format_test::formattable_test::abstract, CharT>
{
	template <class ParseContext>
	constexpr typename ParseContext::iterator
	parse(ParseContext& parse_ctx)
	{
		return parse_ctx.begin();
	}

	template <class FormatContext>
	typename FormatContext::iterator
	format(const hamon_format_test::formattable_test::abstract&, FormatContext& ctx) const
	{
		return ctx.out();
	}
};

namespace hamon_format_test
{

namespace formattable_test
{

template <class CharT>
void test_abstract_class()
{
	assert_is_formattable<abstract, CharT>();
}

template <class CharT>
void test()
{
	test_P0645<CharT>();
	test_P1361<CharT>();
	test_P1636<CharT>();
	test_P2286<CharT>();
	test_LWG3631<CharT>();
	test_LWG3944();
	test_abstract_class<CharT>();
	test_disabled<CharT>();
}

GTEST_TEST(FormatTest, FormattableTest)
{
	test<char>();
	test<wchar_t>();
	test<char8_t>();
	test<char16_t>();
	test<char32_t>();
}

}	// namespace formattable_test

}	// namespace hamon_format_test
