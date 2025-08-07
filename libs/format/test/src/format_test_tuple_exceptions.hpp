/**
 *	@file	format_test_tuple_exceptions.hpp
 *
 *	@brief
 */

#ifndef HAMON_FORMAT_TEST_TUPLE_EXCEPTIONS_HPP
#define HAMON_FORMAT_TEST_TUPLE_EXCEPTIONS_HPP

#include <hamon/detail/statically_widen.hpp>
#include <hamon/pair.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/tuple.hpp>
#include "format_test_helper.hpp"

#define SV(Str)		hamon::basic_string_view<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str), sizeof(Str) - 1)
#define STR(Str)	hamon::basic_string<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str), sizeof(Str) - 1)
#define CSTR(Str)	HAMON_STATICALLY_WIDEN(CharT, Str)

namespace hamon_format_test
{

namespace tuple_exceptions_test
{

//
// Generic tests for a tuple and pair with two elements.
//
template <class CharT, class ExceptionTest, class TupleOrPair>
void test_tuple_or_pair_int_int(ExceptionTest check_exception, TupleOrPair&& input)
{
	check_exception(SV("{:}<}"), input);
	check_exception(SV("{:{<}"), input);

	// *** sign ***
	check_exception(SV("{:-}"), input);
	check_exception(SV("{:+}"), input);
	check_exception(SV("{: }"), input);

	// *** alternate form ***
	check_exception(SV("{:#}"), input);

	// *** zero-padding ***
	check_exception(SV("{:0}"), input);

	// *** precision ***
	check_exception(SV("{:.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{:L}"), input);

	// *** type ***
	check_exception(SV("{:a}"), input);
	check_exception(SV("{:A}"), input);
	check_exception(SV("{:b}"), input);
	check_exception(SV("{:B}"), input);
	check_exception(SV("{:c}"), input);
	check_exception(SV("{:d}"), input);
	check_exception(SV("{:e}"), input);
	check_exception(SV("{:E}"), input);
	check_exception(SV("{:f}"), input);
	check_exception(SV("{:F}"), input);
	check_exception(SV("{:g}"), input);
	check_exception(SV("{:G}"), input);
	check_exception(SV("{:o}"), input);
	check_exception(SV("{:p}"), input);
	check_exception(SV("{:P}"), input);
	check_exception(SV("{:s}"), input);
	check_exception(SV("{:x}"), input);
	check_exception(SV("{:X}"), input);
	check_exception(SV("{:?}"), input);
}

template <class CharT, class ExceptionTest, class TupleOrPair>
void test_tuple_or_pair_int_string(ExceptionTest check_exception, TupleOrPair&& input)
{
	check_exception(SV("{:}<}"), input);
	check_exception(SV("{:{<}"), input);

	// *** sign ***
	check_exception(SV("{:-}"), input);
	check_exception(SV("{:+}"), input);
	check_exception(SV("{: }"), input);

	// *** alternate form ***
	check_exception(SV("{:#}"), input);

	// *** zero-padding ***
	check_exception(SV("{:0}"), input);

	// *** precision ***
	check_exception(SV("{:.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{:L}"), input);

	// *** type ***
	check_exception(SV("{:a}"), input);
	check_exception(SV("{:A}"), input);
	check_exception(SV("{:b}"), input);
	check_exception(SV("{:B}"), input);
	check_exception(SV("{:c}"), input);
	check_exception(SV("{:d}"), input);
	check_exception(SV("{:e}"), input);
	check_exception(SV("{:E}"), input);
	check_exception(SV("{:f}"), input);
	check_exception(SV("{:F}"), input);
	check_exception(SV("{:g}"), input);
	check_exception(SV("{:G}"), input);
	check_exception(SV("{:o}"), input);
	check_exception(SV("{:p}"), input);
	check_exception(SV("{:P}"), input);
	check_exception(SV("{:s}"), input);
	check_exception(SV("{:x}"), input);
	check_exception(SV("{:X}"), input);
	check_exception(SV("{:?}"), input);
}

//
// pair tests
//

template <class CharT, class ExceptionTest>
void test_pair_int_int(ExceptionTest check_exception)
{
	test_tuple_or_pair_int_int<CharT>(check_exception, hamon::make_pair(42, 99));
}

template <class CharT, class ExceptionTest>
void test_pair_int_string(ExceptionTest check_exception)
{
	test_tuple_or_pair_int_string<CharT>(check_exception, hamon::make_pair(42, SV("hello")));
	test_tuple_or_pair_int_string<CharT>(check_exception, hamon::make_pair(42, STR("hello")));
	test_tuple_or_pair_int_string<CharT>(check_exception, hamon::make_pair(42, CSTR("hello")));
}

//
// tuple tests
//

template <class CharT, class ExceptionTest>
void test_tuple_int(ExceptionTest check_exception)
{
	auto input = hamon::make_tuple(42);

	check_exception(SV("{:}<}"), input);
	check_exception(SV("{:{<}"), input);

	// *** sign ***
	check_exception(SV("{:-}"), input);
	check_exception(SV("{:+}"), input);
	check_exception(SV("{: }"), input);

	// *** alternate form ***
	check_exception(SV("{:#}"), input);

	// *** zero-padding ***
	check_exception(SV("{:0}"), input);

	// *** precision ***
	check_exception(SV("{:.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{:L}"), input);

	// *** type ***
	check_exception(SV("{:m}"), input);

	check_exception(SV("{:a}"), input);
	check_exception(SV("{:A}"), input);
	check_exception(SV("{:b}"), input);
	check_exception(SV("{:B}"), input);
	check_exception(SV("{:c}"), input);
	check_exception(SV("{:d}"), input);
	check_exception(SV("{:e}"), input);
	check_exception(SV("{:E}"), input);
	check_exception(SV("{:f}"), input);
	check_exception(SV("{:F}"), input);
	check_exception(SV("{:g}"), input);
	check_exception(SV("{:G}"), input);
	check_exception(SV("{:o}"), input);
	check_exception(SV("{:p}"), input);
	check_exception(SV("{:P}"), input);
	check_exception(SV("{:s}"), input);
	check_exception(SV("{:x}"), input);
	check_exception(SV("{:X}"), input);
	check_exception(SV("{:?}"), input);
}

template <class CharT, class ExceptionTest>
void test_tuple_int_string_color(ExceptionTest check_exception)
{
	const auto input = hamon::make_tuple(42, SV("hello"), color::red);

	check_exception(SV("{:}<}"), input);
	check_exception(SV("{:{<}"), input);

	// *** sign ***
	check_exception(SV("{:-}"), input);
	check_exception(SV("{:+}"), input);
	check_exception(SV("{: }"), input);

	// *** alternate form ***
	check_exception(SV("{:#}"), input);

	// *** zero-padding ***
	check_exception(SV("{:0}"), input);

	// *** precision ***
	check_exception(SV("{:.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{:L}"), input);

	// *** type ***
	check_exception(SV("{:m}"), input);

	check_exception(SV("{:a}"), input);
	check_exception(SV("{:A}"), input);
	check_exception(SV("{:b}"), input);
	check_exception(SV("{:B}"), input);
	check_exception(SV("{:c}"), input);
	check_exception(SV("{:d}"), input);
	check_exception(SV("{:e}"), input);
	check_exception(SV("{:E}"), input);
	check_exception(SV("{:f}"), input);
	check_exception(SV("{:F}"), input);
	check_exception(SV("{:g}"), input);
	check_exception(SV("{:G}"), input);
	check_exception(SV("{:o}"), input);
	check_exception(SV("{:p}"), input);
	check_exception(SV("{:P}"), input);
	check_exception(SV("{:s}"), input);
	check_exception(SV("{:x}"), input);
	check_exception(SV("{:X}"), input);
	check_exception(SV("{:?}"), input);
}

template <class CharT, class ExceptionTest>
void test_tuple_int_int(ExceptionTest check_exception)
{
	test_tuple_or_pair_int_int<CharT>(check_exception, hamon::make_tuple(42, 99));
}

template <class CharT, class ExceptionTest>
void test_tuple_int_string(ExceptionTest check_exception)
{
	test_tuple_or_pair_int_string<CharT>(check_exception, hamon::make_tuple(42, SV("hello")));
	test_tuple_or_pair_int_string<CharT>(check_exception, hamon::make_tuple(42, STR("hello")));
	test_tuple_or_pair_int_string<CharT>(check_exception, hamon::make_tuple(42, CSTR("hello")));
}

//
// nested tests
//

template <class CharT, class ExceptionTest, class Nested>
void test_nested(ExceptionTest check_exception, Nested&& input)
{
	check_exception(SV("{:}<}"), input);
	check_exception(SV("{:{<}"), input);

	// *** sign ***
	check_exception(SV("{:-}"), input);
	check_exception(SV("{:+}"), input);
	check_exception(SV("{: }"), input);

	// *** alternate form ***
	check_exception(SV("{:#}"), input);

	// *** zero-padding ***
	check_exception(SV("{:0}"), input);

	// *** precision ***
	check_exception(SV("{:.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{:L}"), input);

	// *** type ***
	check_exception(SV("{:a}"), input);
	check_exception(SV("{:A}"), input);
	check_exception(SV("{:b}"), input);
	check_exception(SV("{:B}"), input);
	check_exception(SV("{:c}"), input);
	check_exception(SV("{:d}"), input);
	check_exception(SV("{:e}"), input);
	check_exception(SV("{:E}"), input);
	check_exception(SV("{:f}"), input);
	check_exception(SV("{:F}"), input);
	check_exception(SV("{:g}"), input);
	check_exception(SV("{:G}"), input);
	check_exception(SV("{:o}"), input);
	check_exception(SV("{:p}"), input);
	check_exception(SV("{:P}"), input);
	check_exception(SV("{:s}"), input);
	check_exception(SV("{:x}"), input);
	check_exception(SV("{:X}"), input);
	check_exception(SV("{:?}"), input);
}

}	// namespace tuple_exceptions_test

template <class CharT, class ExceptionTest>
void test_tuple_exceptions(ExceptionTest check_exception)
{
	tuple_exceptions_test::test_pair_int_int<CharT>(check_exception);
	tuple_exceptions_test::test_pair_int_string<CharT>(check_exception);

	tuple_exceptions_test::test_tuple_int<CharT>(check_exception);
	tuple_exceptions_test::test_tuple_int_int<CharT>(check_exception);
	tuple_exceptions_test::test_tuple_int_string<CharT>(check_exception);
	tuple_exceptions_test::test_tuple_int_string_color<CharT>(check_exception);

	tuple_exceptions_test::test_nested<CharT>(check_exception, hamon::make_pair(42, hamon::make_pair(SV("hello"), color::red)));
	tuple_exceptions_test::test_nested<CharT>(check_exception, hamon::make_pair(42, hamon::make_tuple(SV("hello"), color::red)));
	tuple_exceptions_test::test_nested<CharT>(check_exception, hamon::make_tuple(42, hamon::make_pair(SV("hello"), color::red)));
	tuple_exceptions_test::test_nested<CharT>(check_exception, hamon::make_tuple(42, hamon::make_tuple(SV("hello"), color::red)));
}

}	// namespace hamon_format_test

#undef SV
#undef STR
#undef CSTR

#endif // HAMON_FORMAT_TEST_TUPLE_EXCEPTIONS_HPP
