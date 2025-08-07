/**
 *	@file	format_test_sequence_exceptions.hpp
 *
 *	@brief
 */

#ifndef HAMON_FORMAT_TEST_SEQUENCE_EXCEPTIONS_HPP
#define HAMON_FORMAT_TEST_SEQUENCE_EXCEPTIONS_HPP

#include <hamon/format/format_kind.hpp>
#include <hamon/format/range_format.hpp>
#include <hamon/array.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/deque.hpp>
#include <hamon/detail/statically_widen.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/iterator/counted_iterator.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/list.hpp>
#include <hamon/pair.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/contiguous_range.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/span.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/tuple.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/vector.hpp>
#include "format_test_helper.hpp"
#include "iterator_test.hpp"

#define SV(Str)		hamon::basic_string_view<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str), sizeof(Str) - 1)
#define STR(Str)	hamon::basic_string<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str), sizeof(Str) - 1)
#define CSTR(Str)	HAMON_STATICALLY_WIDEN(CharT, Str)

namespace hamon_format_test
{

namespace sequence_exceptions_test
{

//
// Char
//

template <class CharT, class ExceptionTest>
void test_char_default(ExceptionTest check_exception, auto&& input)
{
	// ***** underlying has no format-spec

	// *** align-fill & width ***
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
	check_exception(true,  SV("{:a}"), input);
	check_exception(true,  SV("{:A}"), input);
	check_exception(true,  SV("{:b}"), input);
	check_exception(true,  SV("{:B}"), input);
	check_exception(true,  SV("{:c}"), input);
	check_exception(true,  SV("{:d}"), input);
	check_exception(true,  SV("{:e}"), input);
	check_exception(true,  SV("{:E}"), input);
	check_exception(true,  SV("{:f}"), input);
	check_exception(true,  SV("{:F}"), input);
	check_exception(true,  SV("{:g}"), input);
	check_exception(true,  SV("{:G}"), input);
	check_exception(true,  SV("{:o}"), input);
	check_exception(true,  SV("{:p}"), input);
	check_exception(true,  SV("{:P}"), input);
//	check_exception(false, SV("{:s}"), input);	// TODO
	check_exception(true,  SV("{:x}"), input);
	check_exception(true,  SV("{:X}"), input);
	check_exception(true,  SV("{:?}"), input);
	check_exception(true,  SV("{:m}"), input);
	check_exception(false, SV("{:n}"), input);
//	check_exception(false, SV("{:?s}"), input);	// TODO

	// ***** Only underlying has a format-spec
	check_exception(SV("{::}<}"), input);
	check_exception(SV("{::{<}"), input);

	// *** sign ***
	check_exception(SV("{::-}"), input);
	check_exception(SV("{::+}"), input);
	check_exception(SV("{:: }"), input);

	// *** alternate form ***
	check_exception(SV("{::#}"), input);

	// *** zero-padding ***
	check_exception(SV("{::05}"), input);

	// *** precision ***
	check_exception(SV("{::.}"), input);

	// *** locale-specific form ***

	// *** type ***
	check_exception(true,  SV("{::a}"), input);
	check_exception(true,  SV("{::A}"), input);
	check_exception(false, SV("{::b}"), input);
	check_exception(false, SV("{::B}"), input);
	check_exception(false, SV("{::c}"), input);
	check_exception(false, SV("{::d}"), input);
	check_exception(true,  SV("{::e}"), input);
	check_exception(true,  SV("{::E}"), input);
	check_exception(true,  SV("{::f}"), input);
	check_exception(true,  SV("{::F}"), input);
	check_exception(true,  SV("{::g}"), input);
	check_exception(true,  SV("{::G}"), input);
	check_exception(false, SV("{::o}"), input);
	check_exception(true,  SV("{::p}"), input);
	check_exception(true,  SV("{::P}"), input);
	check_exception(true,  SV("{::s}"), input);
	check_exception(false, SV("{::x}"), input);
	check_exception(false, SV("{::X}"), input);
	check_exception(false, SV("{::?}"), input);
	check_exception(true,  SV("{::m}"), input);
	check_exception(true,  SV("{::n}"), input);
	check_exception(true,  SV("{::?s}"), input);

	// ***** Both have a format-spec
	check_exception(SV("{:^^{}::>2}"), input);
	check_exception(SV("{:^^{}::>{}}"), input, 25);
}

template <class CharT, class ExceptionTest>
void test_char_string(ExceptionTest check_exception, auto&& input)
{
	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check_exception(SV("{:}<s}"), input);
	check_exception(SV("{:{<s}"), input);

	// *** sign ***
	check_exception(SV("{:-s}"), input);
	check_exception(SV("{:+s}"), input);
	check_exception(SV("{: s}"), input);

	// *** alternate form ***
	check_exception(SV("{:#s}"), input);

	// *** zero-padding ***
	check_exception(SV("{:0s}"), input);

	// *** precision ***
	check_exception(SV("{:.s}"), input);

	// *** locale-specific form ***
	check_exception(SV("{:Ls}"), input);

	// *** n
	check_exception(SV("{:ns}"), input);

	// *** type ***
	check_exception(SV("{:m}"), input);
	check_exception(SV("{::<s}"), input);

	// ***** Only underlying has a format-spec
	check_exception(SV("{:s:}"), input);

	check_exception(true,  SV("{::a}"), input);
	check_exception(true,  SV("{::A}"), input);
	check_exception(false, SV("{::b}"), input);
	check_exception(false, SV("{::B}"), input);
	check_exception(false, SV("{::c}"), input);
	check_exception(false, SV("{::d}"), input);
	check_exception(true,  SV("{::e}"), input);
	check_exception(true,  SV("{::E}"), input);
	check_exception(true,  SV("{::f}"), input);
	check_exception(true,  SV("{::F}"), input);
	check_exception(true,  SV("{::g}"), input);
	check_exception(true,  SV("{::G}"), input);
	check_exception(false, SV("{::o}"), input);
	check_exception(true,  SV("{::p}"), input);
	check_exception(true,  SV("{::P}"), input);
	check_exception(true,  SV("{::s}"), input);
	check_exception(false, SV("{::x}"), input);
	check_exception(false, SV("{::X}"), input);
	check_exception(false, SV("{::?}"), input);
	check_exception(true,  SV("{::m}"), input);
	check_exception(true,  SV("{::n}"), input);
	check_exception(true,  SV("{::?s}"), input);

	// ***** Both have a format-spec
	check_exception(SV("{:5s:5}"), input);
}

template <class CharT, class ExceptionTest>
void test_char_escaped_string(ExceptionTest check_exception, auto&& input)
{
	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check_exception(SV("{:}<?s}"), input);
	check_exception(SV("{:{<?s}"), input);
	check_exception(SV("{::<?s}"), input);

	// *** sign ***
	check_exception(SV("{:-?s}"), input);
	check_exception(SV("{:+?s}"), input);
	check_exception(SV("{: ?s}"), input);

	// *** alternate form ***
	check_exception(SV("{:#?s}"), input);

	// *** zero-padding ***
	check_exception(SV("{:0?s}"), input);

	// *** precision ***
	check_exception(SV("{:.?s}"), input);

	// *** locale-specific form ***
	check_exception(SV("{:L?s}"), input);

	// *** n
	check_exception(SV("{:n?s}"), input);

	// *** type ***
	check_exception(SV("{:m}"), input);

	// ***** Only underlying has a format-spec
	check_exception(SV("{:?s:}"), input);

	// ***** Both have a format-spec
	check_exception(SV("{:5?s:5}"), input);
}

template <class CharT, class ExceptionTest>
void test_char(ExceptionTest check_exception)
{
	test_char_default<CharT>(
		check_exception, hamon::array{ CharT('H'), CharT('e'), CharT('l'), CharT('l'), CharT('o') });

	// This tests two different implementations in libc++. A basic_string_view
	// formatter if the range is contiguous, a basic_string otherwise.
	test_char_escaped_string<CharT>(
		check_exception,
		hamon::array{ CharT('"'), CharT('H'), CharT('e'), CharT('l'), CharT('l'), CharT('o'), CharT('\'') });
	test_char_escaped_string<CharT>(
		check_exception,
		hamon::list{ CharT('"'), CharT('H'), CharT('e'), CharT('l'), CharT('l'), CharT('o'), CharT('\'') });

	// This tests two different implementations in libc++. A basic_string_view
	// formatter if the range is contiguous, a basic_string otherwise.
	test_char_string<CharT>(
		check_exception, hamon::array{ CharT('H'), CharT('e'), CharT('l'), CharT('l'), CharT('o') });
	test_char_string<CharT>(
		check_exception, hamon::list{ CharT('H'), CharT('e'), CharT('l'), CharT('l'), CharT('o') });
}

//
// char -> wchar_t
//

template <class ExceptionTest>
void test_char_to_wchar(ExceptionTest check_exception)
{
	test_char_default<wchar_t>(check_exception, hamon::array{ 'H', 'e', 'l', 'l', 'o' });

	// The types s and ?s may only be used when using range_formatter<T, charT>
	// where the types T and charT are the same. This means this can't be used for
	// range_formatter<wchar_t, char> even when formatter<wchar_t, char> has a
	// debug-enabled specialization.

	using CharT = wchar_t;
	check_exception(SV("{:s}"), hamon::array{ 'H', 'e', 'l', 'l', 'o' });
	check_exception(SV("{:?s}"), hamon::array{ 'H', 'e', 'l', 'l', 'o' });
}

//
// Bool
//

template <class CharT, class ExceptionTest>
void test_bool(ExceptionTest check_exception)
{
	hamon::array input{ true, true, false };

	// ***** underlying has no format-spec

	// *** align-fill & width ***
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
	check_exception(true,  SV("{:a}"), input);
	check_exception(true,  SV("{:A}"), input);
	check_exception(true,  SV("{:b}"), input);
	check_exception(true,  SV("{:B}"), input);
	check_exception(true,  SV("{:c}"), input);
	check_exception(true,  SV("{:d}"), input);
	check_exception(true,  SV("{:e}"), input);
	check_exception(true,  SV("{:E}"), input);
	check_exception(true,  SV("{:f}"), input);
	check_exception(true,  SV("{:F}"), input);
	check_exception(true,  SV("{:g}"), input);
	check_exception(true,  SV("{:G}"), input);
	check_exception(true,  SV("{:o}"), input);
	check_exception(true,  SV("{:p}"), input);
	check_exception(true,  SV("{:P}"), input);
	check_exception(true,  SV("{:s}"), input);
	check_exception(true,  SV("{:x}"), input);
	check_exception(true,  SV("{:X}"), input);
	check_exception(true,  SV("{:?}"), input);
	check_exception(true,  SV("{:m}"), input);
	check_exception(false, SV("{:n}"), input);
	check_exception(true,  SV("{:?s}"), input);

	// ***** Only underlying has a format-spec
	check_exception(SV("{::}<}"), input);
	check_exception(SV("{::{<}"), input);

	// *** sign ***
	check_exception(SV("{::-}"), input);
	check_exception(SV("{::+}"), input);
	check_exception(SV("{:: }"), input);

	// *** alternate form ***
	check_exception(SV("{::#}"), input);

	// *** zero-padding ***
	check_exception(SV("{::05}"), input);

	// *** precision ***
	check_exception(SV("{::.}"), input);

	// *** type ***
	check_exception(true,  SV("{::a}"), input);
	check_exception(true,  SV("{::A}"), input);
	check_exception(false, SV("{::b}"), input);
	check_exception(false, SV("{::B}"), input);
	check_exception(true,  SV("{::c}"), input);
	check_exception(false, SV("{::d}"), input);
	check_exception(true,  SV("{::e}"), input);
	check_exception(true,  SV("{::E}"), input);
	check_exception(true,  SV("{::f}"), input);
	check_exception(true,  SV("{::F}"), input);
	check_exception(true,  SV("{::g}"), input);
	check_exception(true,  SV("{::G}"), input);
	check_exception(false, SV("{::o}"), input);
	check_exception(true,  SV("{::p}"), input);
	check_exception(true,  SV("{::P}"), input);
	check_exception(false, SV("{::s}"), input);
	check_exception(false, SV("{::x}"), input);
	check_exception(false, SV("{::X}"), input);
	check_exception(true,  SV("{::?}"), input);
	check_exception(true,  SV("{::m}"), input);
	check_exception(true,  SV("{::n}"), input);
	check_exception(true,  SV("{::?s}"), input);

	// ***** Both have a format-spec
	check_exception(SV("{:^^{}::>5}"), input);
	check_exception(SV("{:^^{}::>{}}"), input, 32);
}

//
// Integral
//

template <class CharT, class ExceptionTest>
void test_int(ExceptionTest check_exception, auto&& input, auto make_range)
{
	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check_exception(SV("{:}<}"), make_range(input));
	check_exception(SV("{:{<}"), make_range(input));

	// *** sign ***
	check_exception(SV("{:-}"), make_range(input));
	check_exception(SV("{:+}"), make_range(input));
	check_exception(SV("{: }"), make_range(input));

	// *** alternate form ***
	check_exception(SV("{:#}"), make_range(input));

	// *** zero-padding ***
	check_exception(SV("{:0}"), make_range(input));

	// *** precision ***
	check_exception(SV("{:.}"), make_range(input));

	// *** locale-specific form ***
	check_exception(SV("{:L}"), make_range(input));

	// *** type ***
	check_exception(true,  SV("{:a}"), make_range(input));
	check_exception(true,  SV("{:A}"), make_range(input));
	check_exception(true,  SV("{:b}"), make_range(input));
	check_exception(true,  SV("{:B}"), make_range(input));
	check_exception(true,  SV("{:c}"), make_range(input));
	check_exception(true,  SV("{:d}"), make_range(input));
	check_exception(true,  SV("{:e}"), make_range(input));
	check_exception(true,  SV("{:E}"), make_range(input));
	check_exception(true,  SV("{:f}"), make_range(input));
	check_exception(true,  SV("{:F}"), make_range(input));
	check_exception(true,  SV("{:g}"), make_range(input));
	check_exception(true,  SV("{:G}"), make_range(input));
	check_exception(true,  SV("{:o}"), make_range(input));
	check_exception(true,  SV("{:p}"), make_range(input));
	check_exception(true,  SV("{:P}"), make_range(input));
	check_exception(true,  SV("{:s}"), make_range(input));
	check_exception(true,  SV("{:x}"), make_range(input));
	check_exception(true,  SV("{:X}"), make_range(input));
	check_exception(true,  SV("{:?}"), make_range(input));
	check_exception(true,  SV("{:m}"), make_range(input));
	check_exception(false, SV("{:n}"), make_range(input));
	check_exception(true,  SV("{:?s}"), make_range(input));

	// ***** Only underlying has a format-spec
	check_exception(SV("{::}<}"), make_range(input));
	check_exception(SV("{::{<}"), make_range(input));

	// *** precision ***
	check_exception(SV("{::.}"), make_range(input));

	// *** type ***
	check_exception(true,  SV("{::a}"), make_range(input));
	check_exception(true,  SV("{::A}"), make_range(input));
	check_exception(false, SV("{::b}"), make_range(input));
	check_exception(false, SV("{::B}"), make_range(input));
//	check_exception(false, SV("{::c}"), make_range(input));	// TODO
	check_exception(false, SV("{::d}"), make_range(input));
	check_exception(true,  SV("{::e}"), make_range(input));
	check_exception(true,  SV("{::E}"), make_range(input));
	check_exception(true,  SV("{::f}"), make_range(input));
	check_exception(true,  SV("{::F}"), make_range(input));
	check_exception(true,  SV("{::g}"), make_range(input));
	check_exception(true,  SV("{::G}"), make_range(input));
	check_exception(false, SV("{::o}"), make_range(input));
	check_exception(true,  SV("{::p}"), make_range(input));
	check_exception(true,  SV("{::P}"), make_range(input));
	check_exception(true,  SV("{::s}"), make_range(input));
	check_exception(false, SV("{::x}"), make_range(input));
	check_exception(false, SV("{::X}"), make_range(input));
	check_exception(true,  SV("{::?}"), make_range(input));
	check_exception(true,  SV("{::m}"), make_range(input));
	check_exception(true,  SV("{::n}"), make_range(input));
	check_exception(true,  SV("{::?s}"), make_range(input));

	// ***** Both have a format-spec
	check_exception(SV("{:^^{}::>5}"), make_range(input));
	check_exception(SV("{:^^{}::>{}}"), make_range(input), 33);
}

template <class CharT, class ExceptionTest>
void test_int(ExceptionTest check_exception)
{
	test_int<CharT>(check_exception, hamon::array{ 1, 2, 42, -42 }, hamon::identity());
	test_int<CharT>(check_exception, hamon::list{ 1, 2, 42, -42 }, hamon::identity());
	test_int<CharT>(check_exception, hamon::vector{ 1, 2, 42, -42 }, hamon::identity());
	hamon::array input{ 1, 2, 42, -42 };
	test_int<CharT>(check_exception, hamon::span{ input }, hamon::identity());
}

//
// Floating point
//

template <class CharT, class ExceptionTest>
void test_floating_point(ExceptionTest check_exception, auto&& input)
{
	// ***** underlying has no format-spec

	// *** align-fill & width ***
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
	check_exception(true,  SV("{:a}"), input);
	check_exception(true,  SV("{:A}"), input);
	check_exception(true,  SV("{:b}"), input);
	check_exception(true,  SV("{:B}"), input);
	check_exception(true,  SV("{:c}"), input);
	check_exception(true,  SV("{:d}"), input);
	check_exception(true,  SV("{:e}"), input);
	check_exception(true,  SV("{:E}"), input);
	check_exception(true,  SV("{:f}"), input);
	check_exception(true,  SV("{:F}"), input);
	check_exception(true,  SV("{:g}"), input);
	check_exception(true,  SV("{:G}"), input);
	check_exception(true,  SV("{:o}"), input);
	check_exception(true,  SV("{:p}"), input);
	check_exception(true,  SV("{:P}"), input);
	check_exception(true,  SV("{:s}"), input);
	check_exception(true,  SV("{:x}"), input);
	check_exception(true,  SV("{:X}"), input);
	check_exception(true,  SV("{:?}"), input);
	check_exception(true,  SV("{:m}"), input);
	check_exception(false, SV("{:n}"), input);
	check_exception(true,  SV("{:?s}"), input);

	// ***** Only underlying has a format-spec
	check_exception(SV("{::}<}"), input);
	check_exception(SV("{::{<}"), input);

	// *** precision ***
	check_exception(SV("{::.}"), input);

	// *** type ***
	check_exception(false, SV("{::a}"), input);
	check_exception(false, SV("{::A}"), input);
	check_exception(true,  SV("{::b}"), input);
	check_exception(true,  SV("{::B}"), input);
	check_exception(true,  SV("{::c}"), input);
	check_exception(true,  SV("{::d}"), input);
	check_exception(false, SV("{::e}"), input);
	check_exception(false, SV("{::E}"), input);
	check_exception(false, SV("{::f}"), input);
	check_exception(false, SV("{::F}"), input);
	check_exception(false, SV("{::g}"), input);
	check_exception(false, SV("{::G}"), input);
	check_exception(true,  SV("{::o}"), input);
	check_exception(true,  SV("{::p}"), input);
	check_exception(true,  SV("{::P}"), input);
	check_exception(true,  SV("{::s}"), input);
	check_exception(true,  SV("{::x}"), input);
	check_exception(true,  SV("{::X}"), input);
	check_exception(true,  SV("{::?}"), input);
	check_exception(true,  SV("{::m}"), input);
	check_exception(true,  SV("{::n}"), input);
	check_exception(true,  SV("{::?s}"), input);

	// ***** Both have a format-spec
	check_exception(SV("{:^^{}::>5.2}"), input);
	check_exception(SV("{:^^{}::>{}.2}"), input, 33);
	check_exception(SV("{:^^{}::>{}.{}}"), input, 33, 5);
}

template <class CharT, class ExceptionTest>
void test_floating_point(ExceptionTest check_exception)
{
	test_floating_point<CharT>(check_exception, hamon::array{ -42.5f, 0.0f, 1.25f, 42.5f });
	test_floating_point<CharT>(check_exception, hamon::vector{ -42.5, 0.0, 1.25, 42.5 });

	hamon::array input{ -42.5l, 0.0l, 1.25l, 42.5l };
	test_floating_point<CharT>(check_exception, hamon::span{ input });
}

//
// Pointer
//

template <class CharT, class ExceptionTest>
void test_pointer(ExceptionTest check_exception, auto&& input)
{
	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check_exception(SV("{:}<}"), input);
	check_exception(SV("{:{<}"), input);

	// *** sign ***
	check_exception(SV("{:#}"), input);

	// *** alternate form ***
	check_exception(SV("{:#}"), input);

	// *** zero-padding ***
	check_exception(SV("{:0}"), input);

	// *** precision ***
	check_exception(SV("{:.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{:L}"), input);

	// *** type ***
	check_exception(true,  SV("{:a}"), input);
	check_exception(true,  SV("{:A}"), input);
	check_exception(true,  SV("{:b}"), input);
	check_exception(true,  SV("{:B}"), input);
	check_exception(true,  SV("{:c}"), input);
	check_exception(true,  SV("{:d}"), input);
	check_exception(true,  SV("{:e}"), input);
	check_exception(true,  SV("{:E}"), input);
	check_exception(true,  SV("{:f}"), input);
	check_exception(true,  SV("{:F}"), input);
	check_exception(true,  SV("{:g}"), input);
	check_exception(true,  SV("{:G}"), input);
	check_exception(true,  SV("{:o}"), input);
	check_exception(true,  SV("{:p}"), input);
	check_exception(true,  SV("{:P}"), input);
	check_exception(true,  SV("{:s}"), input);
	check_exception(true,  SV("{:x}"), input);
	check_exception(true,  SV("{:X}"), input);
	check_exception(true,  SV("{:?}"), input);
	check_exception(true,  SV("{:m}"), input);
	check_exception(false, SV("{:n}"), input);
	check_exception(true,  SV("{:?s}"), input);

	// ***** Only underlying has a format-spec
	check_exception(SV("{::}<}"), input);
	check_exception(SV("{::{<}"), input);

	// *** sign ***
	check_exception(SV("{::-}"), input);

	// *** alternate form ***
	check_exception(SV("{::#}"), input);

	// *** precision ***
	check_exception(SV("{::.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{::L}"), input);

	// *** type ***
	check_exception(true,  SV("{::a}"), input);
	check_exception(true,  SV("{::A}"), input);
	check_exception(true,  SV("{::b}"), input);
	check_exception(true,  SV("{::B}"), input);
	check_exception(true,  SV("{::c}"), input);
	check_exception(true,  SV("{::d}"), input);
	check_exception(true,  SV("{::e}"), input);
	check_exception(true,  SV("{::E}"), input);
	check_exception(true,  SV("{::f}"), input);
	check_exception(true,  SV("{::F}"), input);
	check_exception(true,  SV("{::g}"), input);
	check_exception(true,  SV("{::G}"), input);
	check_exception(true,  SV("{::o}"), input);
	check_exception(false, SV("{::p}"), input);
	check_exception(false, SV("{::P}"), input);
	check_exception(true,  SV("{::s}"), input);
	check_exception(true,  SV("{::x}"), input);
	check_exception(true,  SV("{::X}"), input);
	check_exception(true,  SV("{::?}"), input);
	check_exception(true,  SV("{::m}"), input);
	check_exception(true,  SV("{::n}"), input);
	check_exception(true,  SV("{::?s}"), input);

	// ***** Both have a format-spec
	check_exception(SV("{:^^{}::>5}"), input);
	check_exception(SV("{:^^{}::>{}}"), input, 12);
}

template <class CharT, class ExceptionTest>
void test_pointer(ExceptionTest check_exception)
{
	test_pointer<CharT>(check_exception, hamon::array{ nullptr });
	test_pointer<CharT>(check_exception, hamon::array{ static_cast<const void*>(0) });
	test_pointer<CharT>(check_exception, hamon::array{ static_cast<void*>(0) });
}

//
// String
//

template <class CharT, class ExceptionTest>
void test_string(ExceptionTest check_exception, auto&& input)
{
	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check_exception(SV("{:}<}"), input);
	check_exception(SV("{:{<}"), input);

	// *** sign ***
	check_exception(SV("{:#}"), input);

	// *** alternate form ***
	check_exception(SV("{:#}"), input);

	// *** zero-padding ***
	check_exception(SV("{:0}"), input);

	// *** precision ***
	check_exception(SV("{:.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{:L}"), input);

	// *** type ***
	check_exception(true,  SV("{:a}"), input);
	check_exception(true,  SV("{:A}"), input);
	check_exception(true,  SV("{:b}"), input);
	check_exception(true,  SV("{:B}"), input);
	check_exception(true,  SV("{:c}"), input);
	check_exception(true,  SV("{:d}"), input);
	check_exception(true,  SV("{:e}"), input);
	check_exception(true,  SV("{:E}"), input);
	check_exception(true,  SV("{:f}"), input);
	check_exception(true,  SV("{:F}"), input);
	check_exception(true,  SV("{:g}"), input);
	check_exception(true,  SV("{:G}"), input);
	check_exception(true,  SV("{:o}"), input);
	check_exception(true,  SV("{:p}"), input);
	check_exception(true,  SV("{:P}"), input);
	check_exception(true,  SV("{:s}"), input);
	check_exception(true,  SV("{:x}"), input);
	check_exception(true,  SV("{:X}"), input);
	check_exception(true,  SV("{:?}"), input);
	check_exception(true,  SV("{:m}"), input);
	check_exception(false, SV("{:n}"), input);
	check_exception(true,  SV("{:?s}"), input);

	// ***** Only underlying has a format-spec
	check_exception(SV("{::}<}"), input);
	check_exception(SV("{::{<}"), input);

	// *** sign ***
	check_exception(SV("{::-}"), input);

	// *** alternate form ***
	check_exception(SV("{::#}"), input);

	// *** zero-padding ***
	check_exception(SV("{::05}"), input);

	// *** precision ***
	check_exception(SV("{::.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{::L}"), input);

	// *** type ***
	check_exception(true,  SV("{::a}"), input);
	check_exception(true,  SV("{::A}"), input);
	check_exception(true,  SV("{::b}"), input);
	check_exception(true,  SV("{::B}"), input);
	check_exception(true,  SV("{::c}"), input);
	check_exception(true,  SV("{::d}"), input);
	check_exception(true,  SV("{::e}"), input);
	check_exception(true,  SV("{::E}"), input);
	check_exception(true,  SV("{::f}"), input);
	check_exception(true,  SV("{::F}"), input);
	check_exception(true,  SV("{::g}"), input);
	check_exception(true,  SV("{::G}"), input);
	check_exception(true,  SV("{::o}"), input);
	check_exception(true,  SV("{::p}"), input);
	check_exception(true,  SV("{::P}"), input);
	check_exception(false, SV("{::s}"), input);
	check_exception(true,  SV("{::x}"), input);
	check_exception(true,  SV("{::X}"), input);
	check_exception(false, SV("{::?}"), input);
	check_exception(true,  SV("{::m}"), input);
	check_exception(true,  SV("{::n}"), input);
	check_exception(true,  SV("{::?s}"), input);

	// ***** Both have a format-spec
	check_exception(SV("{:^^{}::>8}"), input);
	check_exception(SV("{:^^{}::>{}}"), input, 25);
}

template <class CharT, class ExceptionTest>
void test_string(ExceptionTest check_exception)
{
	test_string<CharT>(check_exception, hamon::array{ CSTR("Hello"), CSTR("world") });
	test_string<CharT>(check_exception, hamon::array{ STR("Hello"), STR("world") });
	test_string<CharT>(check_exception, hamon::array{ SV("Hello"), SV("world") });
}

//
// Handle
//

template <class CharT, class ExceptionTest>
void test_status(ExceptionTest check_exception)
{
	hamon::array input{ status::foo, status::bar, status::foobar };

	// ***** underlying has no format-spec

	// *** align-fill & width ***
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
	check_exception(true,  SV("{:a}"), input);
	check_exception(true,  SV("{:A}"), input);
	check_exception(true,  SV("{:b}"), input);
	check_exception(true,  SV("{:B}"), input);
	check_exception(true,  SV("{:c}"), input);
	check_exception(true,  SV("{:d}"), input);
	check_exception(true,  SV("{:e}"), input);
	check_exception(true,  SV("{:E}"), input);
	check_exception(true,  SV("{:f}"), input);
	check_exception(true,  SV("{:F}"), input);
	check_exception(true,  SV("{:g}"), input);
	check_exception(true,  SV("{:G}"), input);
	check_exception(true,  SV("{:o}"), input);
	check_exception(true,  SV("{:p}"), input);
	check_exception(true,  SV("{:P}"), input);
	check_exception(true,  SV("{:s}"), input);
	check_exception(true,  SV("{:x}"), input);
	check_exception(true,  SV("{:X}"), input);
	check_exception(true,  SV("{:?}"), input);
	check_exception(true,  SV("{:m}"), input);
	check_exception(false, SV("{:n}"), input);
	check_exception(true,  SV("{:?s}"), input);

	// ***** Only underlying has a format-spec

	check_exception(SV("{::*<7}"), input);

	// *** type ***
	check_exception(true,  SV("{::a}"), input);
	check_exception(true,  SV("{::A}"), input);
	check_exception(true,  SV("{::b}"), input);
	check_exception(true,  SV("{::B}"), input);
	check_exception(true,  SV("{::c}"), input);
	check_exception(true,  SV("{::d}"), input);
	check_exception(true,  SV("{::e}"), input);
	check_exception(true,  SV("{::E}"), input);
	check_exception(true,  SV("{::f}"), input);
	check_exception(true,  SV("{::F}"), input);
	check_exception(true,  SV("{::g}"), input);
	check_exception(true,  SV("{::G}"), input);
	check_exception(true,  SV("{::o}"), input);
	check_exception(true,  SV("{::p}"), input);
	check_exception(true,  SV("{::P}"), input);
	check_exception(false, SV("{::s}"), input);
	check_exception(false, SV("{::x}"), input);
	check_exception(false, SV("{::X}"), input);
	check_exception(true,  SV("{::?}"), input);
	check_exception(true,  SV("{::m}"), input);
	check_exception(true,  SV("{::n}"), input);
	check_exception(true,  SV("{::?s}"), input);

	// ***** Both have a format-spec
	check_exception(SV("{:^^{}:X}"), input);
}

//
// Pair
//

template <class CharT, class ExceptionTest>
void test_pair_tuple(ExceptionTest check_exception, auto&& input)
{
	// ***** underlying has no format-spec

	// *** align-fill & width ***
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
	check_exception(true,  SV("{:a}"), input);
	check_exception(true,  SV("{:A}"), input);
	check_exception(true,  SV("{:b}"), input);
	check_exception(true,  SV("{:B}"), input);
	check_exception(true,  SV("{:c}"), input);
	check_exception(true,  SV("{:d}"), input);
	check_exception(true,  SV("{:e}"), input);
	check_exception(true,  SV("{:E}"), input);
	check_exception(true,  SV("{:f}"), input);
	check_exception(true,  SV("{:F}"), input);
	check_exception(true,  SV("{:g}"), input);
	check_exception(true,  SV("{:G}"), input);
	check_exception(true,  SV("{:o}"), input);
	check_exception(true,  SV("{:p}"), input);
	check_exception(true,  SV("{:P}"), input);
	check_exception(true,  SV("{:s}"), input);
	check_exception(true,  SV("{:x}"), input);
	check_exception(true,  SV("{:X}"), input);
	check_exception(true,  SV("{:?}"), input);
	check_exception(false, SV("{:m}"), input);
	check_exception(false, SV("{:n}"), input);
	check_exception(true,  SV("{:?s}"), input);

	// ***** Only underlying has a format-spec
	check_exception(SV("{::}<}"), input);
	check_exception(SV("{::{<}"), input);

	// *** sign ***
	check_exception(SV("{::-}"), input);
	check_exception(SV("{::+}"), input);
	check_exception(SV("{:: }"), input);

	// *** alternate form ***
	check_exception(SV("{::#}"), input);

	// *** zero-padding ***
	check_exception(SV("{::05}"), input);

	// *** precision ***
	check_exception(SV("{::.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{::L}"), input);

	// *** type ***
	check_exception(true,  SV("{::a}"), input);
	check_exception(true,  SV("{::A}"), input);
	check_exception(true,  SV("{::b}"), input);
	check_exception(true,  SV("{::B}"), input);
	check_exception(true,  SV("{::c}"), input);
	check_exception(true,  SV("{::d}"), input);
	check_exception(true,  SV("{::e}"), input);
	check_exception(true,  SV("{::E}"), input);
	check_exception(true,  SV("{::f}"), input);
	check_exception(true,  SV("{::F}"), input);
	check_exception(true,  SV("{::g}"), input);
	check_exception(true,  SV("{::G}"), input);
	check_exception(true,  SV("{::o}"), input);
	check_exception(true,  SV("{::p}"), input);
	check_exception(true,  SV("{::P}"), input);
	check_exception(true,  SV("{::s}"), input);
	check_exception(true,  SV("{::x}"), input);
	check_exception(true,  SV("{::X}"), input);
	check_exception(true,  SV("{::?}"), input);
	check_exception(false, SV("{::m}"), input);
	check_exception(false, SV("{::n}"), input);
	check_exception(true,  SV("{::?s}"), input);

	// ***** Both have a format-spec
	check_exception(SV("{:^^{}:#>5}"), input);
	check_exception(SV("{:^^{}:#>{}}"), input, 31);
}

template <class CharT, class ExceptionTest>
void test_pair_tuple(ExceptionTest check_exception)
{
	test_pair_tuple<CharT>(
		check_exception, hamon::array{ hamon::make_pair(1, CharT('a')), hamon::make_pair(42, CharT('*')) });
	test_pair_tuple<CharT>(
		check_exception, hamon::array{ hamon::make_tuple(1, CharT('a')), hamon::make_tuple(42, CharT('*')) });
}

//
// Tuple 1
//

template <class CharT, class ExceptionTest>
void test_tuple_int(ExceptionTest check_exception)
{
	hamon::array input{ hamon::make_tuple(42), hamon::make_tuple(99) };

	// ***** underlying has no format-spec

	// *** align-fill & width ***
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
	check_exception(true,  SV("{:a}"), input);
	check_exception(true,  SV("{:A}"), input);
	check_exception(true,  SV("{:b}"), input);
	check_exception(true,  SV("{:B}"), input);
	check_exception(true,  SV("{:c}"), input);
	check_exception(true,  SV("{:d}"), input);
	check_exception(true,  SV("{:e}"), input);
	check_exception(true,  SV("{:E}"), input);
	check_exception(true,  SV("{:f}"), input);
	check_exception(true,  SV("{:F}"), input);
	check_exception(true,  SV("{:g}"), input);
	check_exception(true,  SV("{:G}"), input);
	check_exception(true,  SV("{:o}"), input);
	check_exception(true,  SV("{:p}"), input);
	check_exception(true,  SV("{:P}"), input);
	check_exception(true,  SV("{:s}"), input);
	check_exception(true,  SV("{:x}"), input);
	check_exception(true,  SV("{:X}"), input);
	check_exception(true,  SV("{:?}"), input);
	check_exception(true,  SV("{:m}"), input);
	check_exception(false, SV("{:n}"), input);
	check_exception(true,  SV("{:?s}"), input);

	// ***** Only underlying has a format-spec
	check_exception(SV("{::}<}"), input);
	check_exception(SV("{::{<}"), input);

	// *** sign ***
	check_exception(SV("{::-}"), input);
	check_exception(SV("{::+}"), input);
	check_exception(SV("{:: }"), input);

	// *** alternate form ***
	check_exception(SV("{::#}"), input);

	// *** zero-padding ***
	check_exception(SV("{::05}"), input);

	// *** precision ***
	check_exception(SV("{::.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{::L}"), input);

	// *** type ***
	check_exception(true,  SV("{::a}"), input);
	check_exception(true,  SV("{::A}"), input);
	check_exception(true,  SV("{::b}"), input);
	check_exception(true,  SV("{::B}"), input);
	check_exception(true,  SV("{::c}"), input);
	check_exception(true,  SV("{::d}"), input);
	check_exception(true,  SV("{::e}"), input);
	check_exception(true,  SV("{::E}"), input);
	check_exception(true,  SV("{::f}"), input);
	check_exception(true,  SV("{::F}"), input);
	check_exception(true,  SV("{::g}"), input);
	check_exception(true,  SV("{::G}"), input);
	check_exception(true,  SV("{::o}"), input);
	check_exception(true,  SV("{::p}"), input);
	check_exception(true,  SV("{::P}"), input);
	check_exception(true,  SV("{::s}"), input);
	check_exception(true,  SV("{::x}"), input);
	check_exception(true,  SV("{::X}"), input);
	check_exception(true,  SV("{::?}"), input);
	check_exception(true,  SV("{::m}"), input);
	check_exception(false, SV("{::n}"), input);
	check_exception(true,  SV("{::?s}"), input);

	// ***** Both have a format-spec
	check_exception(SV("{:^^{}:#>5}"), input);
	check_exception(SV("{:^^{}:#>{}}"), input, 23);
}

//
// Tuple 3
//

template <class CharT, class ExceptionTest>
void test_tuple_int_int_int(ExceptionTest check_exception)
{
	hamon::array input{ hamon::make_tuple(42, 99, 0), hamon::make_tuple(1, 10, 100) };

	// ***** underlying has no format-spec

	// *** align-fill & width ***
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
	check_exception(true,  SV("{:a}"), input);
	check_exception(true,  SV("{:A}"), input);
	check_exception(true,  SV("{:b}"), input);
	check_exception(true,  SV("{:B}"), input);
	check_exception(true,  SV("{:c}"), input);
	check_exception(true,  SV("{:d}"), input);
	check_exception(true,  SV("{:e}"), input);
	check_exception(true,  SV("{:E}"), input);
	check_exception(true,  SV("{:f}"), input);
	check_exception(true,  SV("{:F}"), input);
	check_exception(true,  SV("{:g}"), input);
	check_exception(true,  SV("{:G}"), input);
	check_exception(true,  SV("{:o}"), input);
	check_exception(true,  SV("{:p}"), input);
	check_exception(true,  SV("{:P}"), input);
	check_exception(true,  SV("{:s}"), input);
	check_exception(true,  SV("{:x}"), input);
	check_exception(true,  SV("{:X}"), input);
	check_exception(true,  SV("{:?}"), input);
	check_exception(true,  SV("{:m}"), input);
	check_exception(false, SV("{:n}"), input);
	check_exception(true,  SV("{:?s}"), input);

	// ***** Only underlying has a format-spec
	check_exception(SV("{::}<}"), input);
	check_exception(SV("{::{<}"), input);

	// *** sign ***
	check_exception(SV("{::-}"), input);
	check_exception(SV("{::+}"), input);
	check_exception(SV("{:: }"), input);

	// *** alternate form ***
	check_exception(SV("{::#}"), input);

	// *** zero-padding ***
	check_exception(SV("{::05}"), input);

	// *** precision ***
	check_exception(SV("{::.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{::L}"), input);

	// *** type ***
	check_exception(true,  SV("{::a}"), input);
	check_exception(true,  SV("{::A}"), input);
	check_exception(true,  SV("{::b}"), input);
	check_exception(true,  SV("{::B}"), input);
	check_exception(true,  SV("{::c}"), input);
	check_exception(true,  SV("{::d}"), input);
	check_exception(true,  SV("{::e}"), input);
	check_exception(true,  SV("{::E}"), input);
	check_exception(true,  SV("{::f}"), input);
	check_exception(true,  SV("{::F}"), input);
	check_exception(true,  SV("{::g}"), input);
	check_exception(true,  SV("{::G}"), input);
	check_exception(true,  SV("{::o}"), input);
	check_exception(true,  SV("{::p}"), input);
	check_exception(true,  SV("{::P}"), input);
	check_exception(true,  SV("{::s}"), input);
	check_exception(true,  SV("{::x}"), input);
	check_exception(true,  SV("{::X}"), input);
	check_exception(true,  SV("{::?}"), input);
	check_exception(true,  SV("{::m}"), input);
	check_exception(false, SV("{::n}"), input);
	check_exception(true,  SV("{::?s}"), input);

	// ***** Both have a format-spec
	check_exception(SV("{:^^{}:#>5}"), input);
	check_exception(SV("{:^^{}:#>{}}"), input, 37);
}

//
// Ranges
//

template <class CharT, class Iterator, class ExceptionTest, class Array>
void test_with_ranges_impl(ExceptionTest check_exception, Array input)
{
	auto make_range = [](auto& in)
	{
		using Diff = hamon::iter_difference_t<Iterator>;
		hamon::counted_iterator it(Iterator(in.data()), static_cast<Diff>(in.size()));
		hamon::ranges::subrange range{ hamon::move(it), hamon::default_sentinel };
		return range;
	};
	test_int<CharT>(check_exception, input, make_range);
}

template <class CharT, class ExceptionTest>
void test_with_ranges(ExceptionTest check_exception)
{
	hamon::array input{ 1, 2, 42, -42 };
	test_with_ranges_impl<CharT, input_iterator_wrapper<int>>(check_exception, input);
	test_with_ranges_impl<CharT, forward_iterator_wrapper<int>>(check_exception, input);
	test_with_ranges_impl<CharT, bidirectional_iterator_wrapper<int>>(check_exception, input);
	test_with_ranges_impl<CharT, random_access_iterator_wrapper<int>>(check_exception, input);
	test_with_ranges_impl<CharT, contiguous_iterator_wrapper<int>>(check_exception, input);
}

//
// Adaptor
//

template <class CharT>
class non_contiguous
{
	// A deque iterator is random access, but not contiguous.
	using adaptee = hamon::deque<CharT>;

public:
	using iterator = typename adaptee::iterator;
	using pointer = typename adaptee::pointer;

	iterator begin() { return data_.begin(); }
	iterator end() { return data_.end(); }

	explicit non_contiguous(adaptee&& data) : data_(hamon::move(data)) {}

private:
	adaptee data_;
};

template <class CharT>
class contiguous
{
	// A vector iterator is contiguous.
	using adaptee = hamon::vector<CharT>;

public:
	using iterator = typename adaptee::iterator;
	using pointer = typename adaptee::pointer;

	iterator begin() { return data_.begin(); }
	iterator end() { return data_.end(); }

	explicit contiguous(adaptee&& data) : data_(hamon::move(data)) {}

private:
	adaptee data_;
};

// This tests two different implementations in libc++. A basic_string_view
// formatter if the range is contiguous, a basic_string otherwise.
template <class CharT, class ExceptionTest>
void test_adaptor(ExceptionTest check_exception)
{
	static_assert(hamon::format_kind<non_contiguous<CharT>> == hamon::range_format::sequence);
	static_assert(hamon::ranges::sized_range<non_contiguous<CharT>>);
	static_assert(!hamon::ranges::contiguous_range<non_contiguous<CharT>>);
	test_char_string<CharT>(
		check_exception,
		non_contiguous<CharT>{hamon::deque{ CharT('H'), CharT('e'), CharT('l'), CharT('l'), CharT('o') }});

	static_assert(hamon::format_kind<contiguous<CharT>> == hamon::range_format::sequence);
	static_assert(hamon::ranges::sized_range<contiguous<CharT>>);
	static_assert(hamon::ranges::contiguous_range<contiguous<CharT>>);
	test_char_string<CharT>(
		check_exception,
		contiguous<CharT>{hamon::vector{ CharT('H'), CharT('e'), CharT('l'), CharT('l'), CharT('o') }});
}

}	// namespace sequence_exceptions_test

//
// Driver
//

template <class CharT, class ExceptionTest>
void test_sequence_exceptions(ExceptionTest check_exception)
{
	sequence_exceptions_test::test_char<CharT>(check_exception);

	if (hamon::same_as<CharT, wchar_t>) // avoid testing twice
	{
		sequence_exceptions_test::test_char_to_wchar(check_exception);
	}

	sequence_exceptions_test::test_bool<CharT>(check_exception);
	sequence_exceptions_test::test_int<CharT>(check_exception);
	sequence_exceptions_test::test_floating_point<CharT>(check_exception);
	sequence_exceptions_test::test_pointer<CharT>(check_exception);
	sequence_exceptions_test::test_string<CharT>(check_exception);

	sequence_exceptions_test::test_status<CharT>(check_exception); // Has its own handler with its own parser

	sequence_exceptions_test::test_pair_tuple<CharT>(check_exception);
	sequence_exceptions_test::test_tuple_int<CharT>(check_exception);
	sequence_exceptions_test::test_tuple_int_int_int<CharT>(check_exception);

	sequence_exceptions_test::test_with_ranges<CharT>(check_exception);

	sequence_exceptions_test::test_adaptor<CharT>(check_exception);
}

}	// namespace hamon_format_test

#undef SV
#undef STR
#undef CSTR

#endif // HAMON_FORMAT_TEST_SEQUENCE_EXCEPTIONS_HPP
