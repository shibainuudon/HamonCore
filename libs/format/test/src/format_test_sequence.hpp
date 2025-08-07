/**
 *	@file	format_test_sequence.hpp
 *
 *	@brief
 */

#ifndef HAMON_FORMAT_TEST_SEQUENCE_HPP
#define HAMON_FORMAT_TEST_SEQUENCE_HPP

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

namespace sequence_test
{

//
// Char
//

template <class CharT, class TestFunction>
void test_char_default(TestFunction check, auto&& input)
{
	// Note when no range-underlying-spec is present the char is escaped,
	check(SV("['H', 'e', 'l', 'l', 'o']"), SV("{}"), input);
	check(SV("['H', 'e', 'l', 'l', 'o']^42"), SV("{}^42"), input);
	check(SV("['H', 'e', 'l', 'l', 'o']^42"), SV("{:}^42"), input);

	// when one is present there is no escaping,
	check(SV("[H, e, l, l, o]"), SV("{::}"), input);
	check(SV("[H, e, l, l, o]"), SV("{::<}"), input);
	// unless forced by the type specifier.
	check(SV("['H', 'e', 'l', 'l', 'o']"), SV("{::?}"), input);
	check(SV("['H', 'e', 'l', 'l', 'o']"), SV("{::<?}"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("['H', 'e', 'l', 'l', 'o']     "), SV("{:30}"), input);
	check(SV("['H', 'e', 'l', 'l', 'o']*****"), SV("{:*<30}"), input);
	check(SV("__['H', 'e', 'l', 'l', 'o']___"), SV("{:_^30}"), input);
	check(SV("#####['H', 'e', 'l', 'l', 'o']"), SV("{:#>30}"), input);

	check(SV("['H', 'e', 'l', 'l', 'o']     "), SV("{:{}}"), input, 30);
	check(SV("['H', 'e', 'l', 'l', 'o']*****"), SV("{:*<{}}"), input, 30);
	check(SV("__['H', 'e', 'l', 'l', 'o']___"), SV("{:_^{}}"), input, 30);
	check(SV("#####['H', 'e', 'l', 'l', 'o']"), SV("{:#>{}}"), input, 30);

	// *** n
	check(SV("__'H', 'e', 'l', 'l', 'o'___"), SV("{:_^28n}"), input);

	// ***** Only underlying has a format-spec
	check(SV("[H   , e   , l   , l   , o   ]"), SV("{::4}"), input);
	check(SV("[H***, e***, l***, l***, o***]"), SV("{::*<4}"), input);
	check(SV("[_H__, _e__, _l__, _l__, _o__]"), SV("{::_^4}"), input);
	check(SV("[:::H, :::e, :::l, :::l, :::o]"), SV("{:::>4}"), input);

	check(SV("[H   , e   , l   , l   , o   ]"), SV("{::{}}"), input, 4);
	check(SV("[H***, e***, l***, l***, o***]"), SV("{::*<{}}"), input, 4);
	check(SV("[_H__, _e__, _l__, _l__, _o__]"), SV("{::_^{}}"), input, 4);
	check(SV("[:::H, :::e, :::l, :::l, :::o]"), SV("{:::>{}}"), input, 4);

	// *** sign ***
	check(SV("[72, 101, 108, 108, 111]"), SV("{::-d}"), input);
	check(SV("[+72, +101, +108, +108, +111]"), SV("{::+d}"), input);
	check(SV("[ 72,  101,  108,  108,  111]"), SV("{:: d}"), input);

	// *** alternate form ***
	check(SV("[0x48, 0x65, 0x6c, 0x6c, 0x6f]"), SV("{::#x}"), input);

	// *** zero-padding ***
	check(SV("[00110, 00145, 00154, 00154, 00157]"), SV("{::05o}"), input);

	// *** locale-specific form ***
	check(SV("[H, e, l, l, o]"), SV("{::L}"), input);

	// ***** Both have a format-spec
	check(SV("^^[:H, :e, :l, :l, :o]^^^"), SV("{:^^25::>2}"), input);
	check(SV("^^[:H, :e, :l, :l, :o]^^^"), SV("{:^^{}::>2}"), input, 25);
	check(SV("^^[:H, :e, :l, :l, :o]^^^"), SV("{:^^{}::>{}}"), input, 25, 2);
}

template <class CharT, class TestFunction>
void test_char_string(TestFunction check, auto&& input)
{
	check(SV("Hello"), SV("{:s}"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("Hello   "), SV("{:8s}"), input);
	check(SV("Hello***"), SV("{:*<8s}"), input);
	check(SV("_Hello__"), SV("{:_^8s}"), input);
	check(SV("###Hello"), SV("{:#>8s}"), input);

	check(SV("Hello   "), SV("{:{}s}"), input, 8);
	check(SV("Hello***"), SV("{:*<{}s}"), input, 8);
	check(SV("_Hello__"), SV("{:_^{}s}"), input, 8);
	check(SV("###Hello"), SV("{:#>{}s}"), input, 8);
}

template <class CharT, class TestFunction>
void test_char_escaped_string(TestFunction check, auto&& input)
{
	check(SV(R"("\"Hello'")"), SV("{:?s}"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV(R"("\"Hello'"   )"), SV("{:13?s}"), input);
	check(SV(R"("\"Hello'"***)"), SV("{:*<13?s}"), input);
	check(SV(R"(_"\"Hello'"__)"), SV("{:_^13?s}"), input);
	check(SV(R"(###"\"Hello'")"), SV("{:#>13?s}"), input);

	check(SV(R"("\"Hello'"   )"), SV("{:{}?s}"), input, 13);
	check(SV(R"("\"Hello'"***)"), SV("{:*<{}?s}"), input, 13);
	check(SV(R"(_"\"Hello'"__)"), SV("{:_^{}?s}"), input, 13);
	check(SV(R"(###"\"Hello'")"), SV("{:#>{}?s}"), input, 13);
}

template <class CharT, class TestFunction>
void test_char(TestFunction check)
{
	test_char_default<CharT>(
		check, hamon::array{ CharT('H'), CharT('e'), CharT('l'), CharT('l'), CharT('o') });

	// This tests two different implementations in libc++. A basic_string_view
	// formatter if the range is contiguous, a basic_string otherwise.
	test_char_escaped_string<CharT>(
		check,
		hamon::array{ CharT('"'), CharT('H'), CharT('e'), CharT('l'), CharT('l'), CharT('o'), CharT('\'') });
	test_char_escaped_string<CharT>(
		check,
		hamon::list{ CharT('"'), CharT('H'), CharT('e'), CharT('l'), CharT('l'), CharT('o'), CharT('\'') });

	// This tests two different implementations in libc++. A basic_string_view
	// formatter if the range is contiguous, a basic_string otherwise.
	test_char_string<CharT>(
		check, hamon::array{ CharT('H'), CharT('e'), CharT('l'), CharT('l'), CharT('o') });
	test_char_string<CharT>(
		check, hamon::list{ CharT('H'), CharT('e'), CharT('l'), CharT('l'), CharT('o') });
}

//
// char -> wchar_t
//

template <class TestFunction>
void test_char_to_wchar(TestFunction check)
{
	test_char_default<wchar_t>(check, hamon::array{ 'H', 'e', 'l', 'l', 'o' });
}

//
// Bool
//

template <class CharT, class TestFunction>
void test_bool(TestFunction check)
{
	hamon::array input{ true, true, false };

	check(SV("[true, true, false]"), SV("{}"), input);
	check(SV("[true, true, false]^42"), SV("{}^42"), input);
	check(SV("[true, true, false]^42"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("[true, true, false]     "), SV("{:24}"), input);
	check(SV("[true, true, false]*****"), SV("{:*<24}"), input);
	check(SV("__[true, true, false]___"), SV("{:_^24}"), input);
	check(SV("#####[true, true, false]"), SV("{:#>24}"), input);

	check(SV("[true, true, false]     "), SV("{:{}}"), input, 24);
	check(SV("[true, true, false]*****"), SV("{:*<{}}"), input, 24);
	check(SV("__[true, true, false]___"), SV("{:_^{}}"), input, 24);
	check(SV("#####[true, true, false]"), SV("{:#>{}}"), input, 24);

	// *** n
	check(SV("__true, true, false___"), SV("{:_^22n}"), input);

	// ***** Only underlying has a format-spec
	check(SV("[true   , true   , false  ]"), SV("{::7}"), input);
	check(SV("[true***, true***, false**]"), SV("{::*<7}"), input);
	check(SV("[_true__, _true__, _false_]"), SV("{::_^7}"), input);
	check(SV("[:::true, :::true, ::false]"), SV("{:::>7}"), input);

	check(SV("[true   , true   , false  ]"), SV("{::{}}"), input, 7);
	check(SV("[true***, true***, false**]"), SV("{::*<{}}"), input, 7);
	check(SV("[_true__, _true__, _false_]"), SV("{::_^{}}"), input, 7);
	check(SV("[:::true, :::true, ::false]"), SV("{:::>{}}"), input, 7);

	// *** sign ***
	check(SV("[1, 1, 0]"), SV("{::-d}"), input);
	check(SV("[+1, +1, +0]"), SV("{::+d}"), input);
	check(SV("[ 1,  1,  0]"), SV("{:: d}"), input);

	// *** alternate form ***
	check(SV("[0x1, 0x1, 0x0]"), SV("{::#x}"), input);

	// *** zero-padding ***
	check(SV("[00001, 00001, 00000]"), SV("{::05o}"), input);

	// *** locale-specific form ***
	check(SV("[true, true, false]"), SV("{::L}"), input);

	// ***** Both have a format-spec
	check(SV("^^[:::true, :::true, ::false]^^^"), SV("{:^^32::>7}"), input);
	check(SV("^^[:::true, :::true, ::false]^^^"), SV("{:^^{}::>7}"), input, 32);
	check(SV("^^[:::true, :::true, ::false]^^^"), SV("{:^^{}::>{}}"), input, 32, 7);
}

//
// Integral
//

template <class CharT, class TestFunction>
void test_int(TestFunction check, auto&& input, auto make_range)
{
	check(SV("[1, 2, 42, -42]"), SV("{}"), make_range(input));
	check(SV("[1, 2, 42, -42]^42"), SV("{}^42"), make_range(input));
	check(SV("[1, 2, 42, -42]^42"), SV("{:}^42"), make_range(input));

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("[1, 2, 42, -42]     "), SV("{:20}"), make_range(input));
	check(SV("[1, 2, 42, -42]*****"), SV("{:*<20}"), make_range(input));
	check(SV("__[1, 2, 42, -42]___"), SV("{:_^20}"), make_range(input));
	check(SV("#####[1, 2, 42, -42]"), SV("{:#>20}"), make_range(input));

	check(SV("[1, 2, 42, -42]     "), SV("{:{}}"), make_range(input), 20);
	check(SV("[1, 2, 42, -42]*****"), SV("{:*<{}}"), make_range(input), 20);
	check(SV("__[1, 2, 42, -42]___"), SV("{:_^{}}"), make_range(input), 20);
	check(SV("#####[1, 2, 42, -42]"), SV("{:#>{}}"), make_range(input), 20);

	// *** n
	check(SV("__1, 2, 42, -42___"), SV("{:_^18n}"), make_range(input));

	// ***** Only underlying has a format-spec
	check(SV("[    1,     2,    42,   -42]"), SV("{::5}"), make_range(input));
	check(SV("[1****, 2****, 42***, -42**]"), SV("{::*<5}"), make_range(input));
	check(SV("[__1__, __2__, _42__, _-42_]"), SV("{::_^5}"), make_range(input));
	check(SV("[::::1, ::::2, :::42, ::-42]"), SV("{:::>5}"), make_range(input));

	check(SV("[    1,     2,    42,   -42]"), SV("{::{}}"), make_range(input), 5);
	check(SV("[1****, 2****, 42***, -42**]"), SV("{::*<{}}"), make_range(input), 5);
	check(SV("[__1__, __2__, _42__, _-42_]"), SV("{::_^{}}"), make_range(input), 5);
	check(SV("[::::1, ::::2, :::42, ::-42]"), SV("{:::>{}}"), make_range(input), 5);

	// *** sign ***
	check(SV("[1, 2, 42, -42]"), SV("{::-}"), make_range(input));
	check(SV("[+1, +2, +42, -42]"), SV("{::+}"), make_range(input));
	check(SV("[ 1,  2,  42, -42]"), SV("{:: }"), make_range(input));

	// *** alternate form ***
	check(SV("[0x1, 0x2, 0x2a, -0x2a]"), SV("{::#x}"), make_range(input));

	// *** zero-padding ***
	check(SV("[00001, 00002, 00042, -0042]"), SV("{::05}"), make_range(input));
	check(SV("[00001, 00002, 0002a, -002a]"), SV("{::05x}"), make_range(input));
	check(SV("[0x001, 0x002, 0x02a, -0x2a]"), SV("{::#05x}"), make_range(input));

	// *** locale-specific form ***
	check(SV("[1, 2, 42, -42]"), SV("{::L}"), make_range(input)); // does nothing in this test, but is accepted.

	// ***** Both have a format-spec
	check(SV("^^[::::1, ::::2, :::42, ::-42]^^^"), SV("{:^^33::>5}"), make_range(input));
	check(SV("^^[::::1, ::::2, :::42, ::-42]^^^"), SV("{:^^{}::>5}"), make_range(input), 33);
	check(SV("^^[::::1, ::::2, :::42, ::-42]^^^"), SV("{:^^{}::>{}}"), make_range(input), 33, 5);
}

template <class CharT, class TestFunction>
void test_int(TestFunction check)
{
	test_int<CharT>(check, hamon::array{ 1, 2, 42, -42 }, hamon::identity());
	test_int<CharT>(check, hamon::list{ 1, 2, 42, -42 }, hamon::identity());
	test_int<CharT>(check, hamon::vector{ 1, 2, 42, -42 }, hamon::identity());
	hamon::array input{ 1, 2, 42, -42 };
	test_int<CharT>(check, hamon::span{ input }, hamon::identity());
}

//
// Floating point
//

template <class CharT, class TestFunction>
void test_floating_point(TestFunction check, auto&& input)
{
	check(SV("[-42.5, 0, 1.25, 42.5]"), SV("{}"), input);
	check(SV("[-42.5, 0, 1.25, 42.5]^42"), SV("{}^42"), input);
	check(SV("[-42.5, 0, 1.25, 42.5]^42"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("[-42.5, 0, 1.25, 42.5]     "), SV("{:27}"), input);
	check(SV("[-42.5, 0, 1.25, 42.5]*****"), SV("{:*<27}"), input);
	check(SV("__[-42.5, 0, 1.25, 42.5]___"), SV("{:_^27}"), input);
	check(SV("#####[-42.5, 0, 1.25, 42.5]"), SV("{:#>27}"), input);

	check(SV("[-42.5, 0, 1.25, 42.5]     "), SV("{:{}}"), input, 27);
	check(SV("[-42.5, 0, 1.25, 42.5]*****"), SV("{:*<{}}"), input, 27);
	check(SV("__[-42.5, 0, 1.25, 42.5]___"), SV("{:_^{}}"), input, 27);
	check(SV("#####[-42.5, 0, 1.25, 42.5]"), SV("{:#>{}}"), input, 27);

	// *** n
	check(SV("__-42.5, 0, 1.25, 42.5___"), SV("{:_^25n}"), input);

	// ***** Only underlying has a format-spec
	check(SV("[-42.5,     0,  1.25,  42.5]"), SV("{::5}"), input);
	check(SV("[-42.5, 0****, 1.25*, 42.5*]"), SV("{::*<5}"), input);
	check(SV("[-42.5, __0__, 1.25_, 42.5_]"), SV("{::_^5}"), input);
	check(SV("[-42.5, ::::0, :1.25, :42.5]"), SV("{:::>5}"), input);

	check(SV("[-42.5,     0,  1.25,  42.5]"), SV("{::{}}"), input, 5);
	check(SV("[-42.5, 0****, 1.25*, 42.5*]"), SV("{::*<{}}"), input, 5);
	check(SV("[-42.5, __0__, 1.25_, 42.5_]"), SV("{::_^{}}"), input, 5);
	check(SV("[-42.5, ::::0, :1.25, :42.5]"), SV("{:::>{}}"), input, 5);

	// *** sign ***
	check(SV("[-42.5, 0, 1.25, 42.5]"), SV("{::-}"), input);
	check(SV("[-42.5, +0, +1.25, +42.5]"), SV("{::+}"), input);
	check(SV("[-42.5,  0,  1.25,  42.5]"), SV("{:: }"), input);

	// *** alternate form ***
	check(SV("[-42.5, 0., 1.25, 42.5]"), SV("{::#}"), input);

	// *** zero-padding ***
	check(SV("[-42.5, 00000, 01.25, 042.5]"), SV("{::05}"), input);
	check(SV("[-42.5, 0000., 01.25, 042.5]"), SV("{::#05}"), input);

	// *** precision ***
	check(SV("[-42, 0, 1.2, 42]"), SV("{::.2}"), input);
	check(SV("[-42.500, 0.000, 1.250, 42.500]"), SV("{::.3f}"), input);

	check(SV("[-42, 0, 1.2, 42]"), SV("{::.{}}"), input, 2);
	check(SV("[-42.500, 0.000, 1.250, 42.500]"), SV("{::.{}f}"), input, 3);

	// *** locale-specific form ***
	check(SV("[-42.5, 0, 1.25, 42.5]"), SV("{::L}"), input); // does not require locales present
#ifndef TEST_HAS_NO_LOCALIZATION
	// TODO FMT Enable with locale testing active
#  if 0
	std::locale::global(std::locale(LOCALE_fr_FR_UTF_8));
	check(SV("[-42,5, 0, 1,25, 42,5]"), SV("{::L}"), input);

	std::locale::global(std::locale(LOCALE_en_US_UTF_8));
	check(SV("[-42.5, 0, 1.25, 42.5]"), SV("{::L}"), input);

	std::locale::global(std::locale::classic());
#  endif
#endif // TEST_HAS_NO_LOCALIZATION

	// ***** Both have a format-spec
	check(SV("^^[-42.5, ::::0, :1.25, :42.5]^^^"), SV("{:^^33::>5}"), input);
	check(SV("^^[-42.5, ::::0, :1.25, :42.5]^^^"), SV("{:^^{}::>5}"), input, 33);
	check(SV("^^[-42.5, ::::0, :1.25, :42.5]^^^"), SV("{:^^{}::>{}}"), input, 33, 5);

	check(SV("^^[::-42, ::::0, ::1.2, :::42]^^^"), SV("{:^^33::>5.2}"), input);
	check(SV("^^[::-42, ::::0, ::1.2, :::42]^^^"), SV("{:^^{}::>5.2}"), input, 33);
	check(SV("^^[::-42, ::::0, ::1.2, :::42]^^^"), SV("{:^^{}::>{}.2}"), input, 33, 5);
	check(SV("^^[::-42, ::::0, ::1.2, :::42]^^^"), SV("{:^^{}::>{}.{}}"), input, 33, 5, 2);
}

template <class CharT, class TestFunction>
void test_floating_point(TestFunction check)
{
	test_floating_point<CharT>(check, hamon::array{ -42.5f, 0.0f, 1.25f, 42.5f });
	test_floating_point<CharT>(check, hamon::vector{ -42.5, 0.0, 1.25, 42.5 });

	hamon::array input{ -42.5l, 0.0l, 1.25l, 42.5l };
	test_floating_point<CharT>(check, hamon::span{ input });
}

//
// Pointer
//

template <class CharT, class TestFunction>
void test_pointer(TestFunction check, auto&& input)
{
	check(SV("[0x0]"), SV("{}"), input);
	check(SV("[0x0]^42"), SV("{}^42"), input);
	check(SV("[0x0]^42"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("[0x0]     "), SV("{:10}"), input);
	check(SV("[0x0]*****"), SV("{:*<10}"), input);
	check(SV("__[0x0]___"), SV("{:_^10}"), input);
	check(SV("#####[0x0]"), SV("{:#>10}"), input);

	check(SV("[0x0]     "), SV("{:{}}"), input, 10);
	check(SV("[0x0]*****"), SV("{:*<{}}"), input, 10);
	check(SV("__[0x0]___"), SV("{:_^{}}"), input, 10);
	check(SV("#####[0x0]"), SV("{:#>{}}"), input, 10);

	// *** n
	check(SV("_0x0_"), SV("{:_^5n}"), input);

	// ***** Only underlying has a format-spec
	check(SV("[  0x0]"), SV("{::5}"), input);
	check(SV("[0x0**]"), SV("{::*<5}"), input);
	check(SV("[_0x0_]"), SV("{::_^5}"), input);
	check(SV("[::0x0]"), SV("{:::>5}"), input);

	check(SV("[  0x0]"), SV("{::{}}"), input, 5);
	check(SV("[0x0**]"), SV("{::*<{}}"), input, 5);
	check(SV("[_0x0_]"), SV("{::_^{}}"), input, 5);
	check(SV("[::0x0]"), SV("{:::>{}}"), input, 5);

	// *** zero-padding ***
	check(SV("[0x0000]"), SV("{::06}"), input);
	check(SV("[0x0000]"), SV("{::06p}"), input);
	check(SV("[0X0000]"), SV("{::06P}"), input);

	// ***** Both have a format-spec
	check(SV("^^[::0x0]^^^"), SV("{:^^12::>5}"), input);
	check(SV("^^[::0x0]^^^"), SV("{:^^{}::>5}"), input, 12);
	check(SV("^^[::0x0]^^^"), SV("{:^^{}::>{}}"), input, 12, 5);

	check(SV("^^[::0x0]^^^"), SV("{:^^12::>5}"), input);
	check(SV("^^[::0x0]^^^"), SV("{:^^{}::>5}"), input, 12);
	check(SV("^^[::0x0]^^^"), SV("{:^^{}::>{}}"), input, 12, 5);
}

template <class CharT, class TestFunction>
void test_pointer(TestFunction check)
{
	test_pointer<CharT>(check, hamon::array{ nullptr });
	test_pointer<CharT>(check, hamon::array{ static_cast<const void*>(0) });
	test_pointer<CharT>(check, hamon::array{ static_cast<void*>(0) });
}

//
// String
//

template <class CharT, class TestFunction>
void test_string(TestFunction check, auto&& input)
{
	check(SV(R"(["Hello", "world"])"), SV("{}"), input);
	check(SV(R"(["Hello", "world"]^42)"), SV("{}^42"), input);
	check(SV(R"(["Hello", "world"]^42)"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV(R"(["Hello", "world"]     )"), SV("{:23}"), input);
	check(SV(R"(["Hello", "world"]*****)"), SV("{:*<23}"), input);
	check(SV(R"(__["Hello", "world"]___)"), SV("{:_^23}"), input);
	check(SV(R"(#####["Hello", "world"])"), SV("{:#>23}"), input);

	check(SV(R"(["Hello", "world"]     )"), SV("{:{}}"), input, 23);
	check(SV(R"(["Hello", "world"]*****)"), SV("{:*<{}}"), input, 23);
	check(SV(R"(__["Hello", "world"]___)"), SV("{:_^{}}"), input, 23);
	check(SV(R"(#####["Hello", "world"])"), SV("{:#>{}}"), input, 23);

	// *** n
	check(SV(R"(_"Hello", "world"_)"), SV("{:_^18n}"), input);

	// ***** Only underlying has a format-spec
	check(SV(R"([Hello   , world   ])"), SV("{::8}"), input);
	check(SV(R"([Hello***, world***])"), SV("{::*<8}"), input);
	check(SV(R"([_Hello__, _world__])"), SV("{::_^8}"), input);
	check(SV(R"([:::Hello, :::world])"), SV("{:::>8}"), input);

	check(SV(R"([Hello   , world   ])"), SV("{::{}}"), input, 8);
	check(SV(R"([Hello***, world***])"), SV("{::*<{}}"), input, 8);
	check(SV(R"([_Hello__, _world__])"), SV("{::_^{}}"), input, 8);
	check(SV(R"([:::Hello, :::world])"), SV("{:::>{}}"), input, 8);

	// *** precision ***
	check(SV(R"([Hel, wor])"), SV("{::.3}"), input);
	check(SV(R"([Hel, wor])"), SV("{::.{}}"), input, 3);

	// ***** Both have a format-spec
	check(SV(R"(^^[:::Hello, :::world]^^^)"), SV("{:^^25::>8}"), input);
	check(SV(R"(^^[:::Hello, :::world]^^^)"), SV("{:^^{}::>8}"), input, 25);
	check(SV(R"(^^[:::Hello, :::world]^^^)"), SV("{:^^{}::>{}}"), input, 25, 8);

	check(SV(R"(^^[:::Hello, :::world]^^^)"), SV("{:^^25::>8}"), input);
	check(SV(R"(^^[:::Hello, :::world]^^^)"), SV("{:^^{}::>8}"), input, 25);
	check(SV(R"(^^[:::Hello, :::world]^^^)"), SV("{:^^{}::>{}}"), input, 25, 8);
}

template <class CharT, class TestFunction>
void test_string(TestFunction check)
{
	test_string<CharT>(check, hamon::array{ CSTR("Hello"), CSTR("world") });
	test_string<CharT>(check, hamon::array{ STR("Hello"), STR("world") });
	test_string<CharT>(check, hamon::array{ SV("Hello"), SV("world") });
}

//
// Handle
//

template <class CharT, class TestFunction>
void test_status(TestFunction check)
{
	hamon::array input{ status::foo, status::bar, status::foobar };

	check(SV("[0xaaaa, 0x5555, 0xaa55]"), SV("{}"), input);
	check(SV("[0xaaaa, 0x5555, 0xaa55]^42"), SV("{}^42"), input);
	check(SV("[0xaaaa, 0x5555, 0xaa55]^42"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("[0xaaaa, 0x5555, 0xaa55]     "), SV("{:29}"), input);
	check(SV("[0xaaaa, 0x5555, 0xaa55]*****"), SV("{:*<29}"), input);
	check(SV("__[0xaaaa, 0x5555, 0xaa55]___"), SV("{:_^29}"), input);
	check(SV("#####[0xaaaa, 0x5555, 0xaa55]"), SV("{:#>29}"), input);

	check(SV("[0xaaaa, 0x5555, 0xaa55]     "), SV("{:{}}"), input, 29);
	check(SV("[0xaaaa, 0x5555, 0xaa55]*****"), SV("{:*<{}}"), input, 29);
	check(SV("__[0xaaaa, 0x5555, 0xaa55]___"), SV("{:_^{}}"), input, 29);
	check(SV("#####[0xaaaa, 0x5555, 0xaa55]"), SV("{:#>{}}"), input, 29);

	// *** n
	check(SV("__0xaaaa, 0x5555, 0xaa55___"), SV("{:_^27n}"), input);

	// ***** Only underlying has a format-spec
	check(SV("[0xaaaa, 0x5555, 0xaa55]"), SV("{::x}"), input);
	check(SV("[0XAAAA, 0X5555, 0XAA55]"), SV("{::X}"), input);
	check(SV("[foo, bar, foobar]"), SV("{::s}"), input);

	// ***** Both have a format-spec
	check(SV("^^[0XAAAA, 0X5555, 0XAA55]^^^"), SV("{:^^29:X}"), input);
	check(SV("^^[0XAAAA, 0X5555, 0XAA55]^^^"), SV("{:^^{}:X}"), input, 29);
}

//
// Pair
//

template <class CharT, class TestFunction>
void test_pair_tuple(TestFunction check, auto&& input)
{
	// [format.range.formatter]/3
	//   For range_formatter<T, charT>, the format-spec in a
	//   range-underlying-spec, if any, is interpreted by formatter<T, charT>.
	//
	//   template<class ParseContext>
	//   constexpr typename ParseContext::iterator
	//    parse(ParseContext& ctx);
	// [format.tuple]/7
	//   ... if e.set_debug_format() is a valid expression, calls
	//   e.set_debug_format().
	// So when there is no range-underlying-spec, there is no need to call parse
	// thus the char element is not escaped.
	// TODO FMT P2733 addresses this issue.
	check(SV("[(1, 'a'), (42, '*')]"), SV("{}"), input);
	check(SV("[(1, 'a'), (42, '*')]^42"), SV("{}^42"), input);
	check(SV("[(1, 'a'), (42, '*')]^42"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("[(1, 'a'), (42, '*')]     "), SV("{:26}"), input);
	check(SV("[(1, 'a'), (42, '*')]*****"), SV("{:*<26}"), input);
	check(SV("__[(1, 'a'), (42, '*')]___"), SV("{:_^26}"), input);
	check(SV("#####[(1, 'a'), (42, '*')]"), SV("{:#>26}"), input);

	check(SV("[(1, 'a'), (42, '*')]     "), SV("{:{}}"), input, 26);
	check(SV("[(1, 'a'), (42, '*')]*****"), SV("{:*<{}}"), input, 26);
	check(SV("__[(1, 'a'), (42, '*')]___"), SV("{:_^{}}"), input, 26);
	check(SV("#####[(1, 'a'), (42, '*')]"), SV("{:#>{}}"), input, 26);

	// *** n
	check(SV("__(1, 'a'), (42, '*')___"), SV("{:_^24n}"), input);
	check(SV("__(1, 'a'), (42, '*')___"), SV("{:_^24nm}"), input); // m should have no effect

	// *** type ***
	check(SV("__{(1, 'a'), (42, '*')}___"), SV("{:_^26m}"), input);

	// ***** Only underlying has a format-spec
	check(SV("[(1, 'a')   , (42, '*')  ]"), SV("{::11}"), input);
	check(SV("[(1, 'a')***, (42, '*')**]"), SV("{::*<11}"), input);
	check(SV("[_(1, 'a')__, _(42, '*')_]"), SV("{::_^11}"), input);
	check(SV("[###(1, 'a'), ##(42, '*')]"), SV("{::#>11}"), input);

	check(SV("[(1, 'a')   , (42, '*')  ]"), SV("{::{}}"), input, 11);
	check(SV("[(1, 'a')***, (42, '*')**]"), SV("{::*<{}}"), input, 11);
	check(SV("[_(1, 'a')__, _(42, '*')_]"), SV("{::_^{}}"), input, 11);
	check(SV("[###(1, 'a'), ##(42, '*')]"), SV("{::#>{}}"), input, 11);

	// *** type ***
	check(SV("[1: 'a', 42: '*']"), SV("{::m}"), input);
	check(SV("[1, 'a', 42, '*']"), SV("{::n}"), input);

	// ***** Both have a format-spec
	check(SV("^^[###(1, 'a'), ##(42, '*')]^^^"), SV("{:^^31:#>11}"), input);
	check(SV("^^[###(1, 'a'), ##(42, '*')]^^^"), SV("{:^^31:#>11}"), input);
	check(SV("^^[###(1, 'a'), ##(42, '*')]^^^"), SV("{:^^{}:#>11}"), input, 31);
	check(SV("^^[###(1, 'a'), ##(42, '*')]^^^"), SV("{:^^{}:#>{}}"), input, 31, 11);

	check(SV("1: 'a', 42: '*'"), SV("{:n:m}"), input);
	check(SV("1, 'a', 42, '*'"), SV("{:n:n}"), input);
	check(SV("{1: 'a', 42: '*'}"), SV("{:m:m}"), input);
	check(SV("{1, 'a', 42, '*'}"), SV("{:m:n}"), input);
}

template <class CharT, class TestFunction>
void test_pair_tuple(TestFunction check)
{
	test_pair_tuple<CharT>(
		check, hamon::array{ hamon::make_pair(1, CharT('a')), hamon::make_pair(42, CharT('*')) });
	test_pair_tuple<CharT>(
		check, hamon::array{ hamon::make_tuple(1, CharT('a')), hamon::make_tuple(42, CharT('*')) });
}

//
// Tuple 1
//

template <class CharT, class TestFunction>
void test_tuple_int(TestFunction check)
{
	hamon::array input{ hamon::make_tuple(42), hamon::make_tuple(99) };

	check(SV("[(42), (99)]"), SV("{}"), input);
	check(SV("[(42), (99)]^42"), SV("{}^42"), input);
	check(SV("[(42), (99)]^42"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("[(42), (99)]     "), SV("{:17}"), input);
	check(SV("[(42), (99)]*****"), SV("{:*<17}"), input);
	check(SV("__[(42), (99)]___"), SV("{:_^17}"), input);
	check(SV("#####[(42), (99)]"), SV("{:#>17}"), input);

	check(SV("[(42), (99)]     "), SV("{:{}}"), input, 17);
	check(SV("[(42), (99)]*****"), SV("{:*<{}}"), input, 17);
	check(SV("__[(42), (99)]___"), SV("{:_^{}}"), input, 17);
	check(SV("#####[(42), (99)]"), SV("{:#>{}}"), input, 17);

	// *** n
	check(SV("__(42), (99)___"), SV("{:_^15n}"), input);

	// ***** Only underlying has a format-spec
	check(SV("[(42)   , (99)   ]"), SV("{::7}"), input);
	check(SV("[(42)***, (99)***]"), SV("{::*<7}"), input);
	check(SV("[_(42)__, _(99)__]"), SV("{::_^7}"), input);
	check(SV("[###(42), ###(99)]"), SV("{::#>7}"), input);

	check(SV("[(42)   , (99)   ]"), SV("{::{}}"), input, 7);
	check(SV("[(42)***, (99)***]"), SV("{::*<{}}"), input, 7);
	check(SV("[_(42)__, _(99)__]"), SV("{::_^{}}"), input, 7);
	check(SV("[###(42), ###(99)]"), SV("{::#>{}}"), input, 7);

	// *** type ***
	check(SV("[42, 99]"), SV("{::n}"), input);

	// ***** Both have a format-spec
	check(SV("^^[###(42), ###(99)]^^^"), SV("{:^^23:#>7}"), input);
	check(SV("^^[###(42), ###(99)]^^^"), SV("{:^^23:#>7}"), input);
	check(SV("^^[###(42), ###(99)]^^^"), SV("{:^^{}:#>7}"), input, 23);
	check(SV("^^[###(42), ###(99)]^^^"), SV("{:^^{}:#>{}}"), input, 23, 7);
}

//
// Tuple 3
//

template <class CharT, class TestFunction>
void test_tuple_int_int_int(TestFunction check)
{
	hamon::array input{ hamon::make_tuple(42, 99, 0), hamon::make_tuple(1, 10, 100) };

	check(SV("[(42, 99, 0), (1, 10, 100)]"), SV("{}"), input);
	check(SV("[(42, 99, 0), (1, 10, 100)]^42"), SV("{}^42"), input);
	check(SV("[(42, 99, 0), (1, 10, 100)]^42"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("[(42, 99, 0), (1, 10, 100)]     "), SV("{:32}"), input);
	check(SV("[(42, 99, 0), (1, 10, 100)]*****"), SV("{:*<32}"), input);
	check(SV("__[(42, 99, 0), (1, 10, 100)]___"), SV("{:_^32}"), input);
	check(SV("#####[(42, 99, 0), (1, 10, 100)]"), SV("{:#>32}"), input);

	check(SV("[(42, 99, 0), (1, 10, 100)]     "), SV("{:{}}"), input, 32);
	check(SV("[(42, 99, 0), (1, 10, 100)]*****"), SV("{:*<{}}"), input, 32);
	check(SV("__[(42, 99, 0), (1, 10, 100)]___"), SV("{:_^{}}"), input, 32);
	check(SV("#####[(42, 99, 0), (1, 10, 100)]"), SV("{:#>{}}"), input, 32);

	// *** n
	check(SV("__(42, 99, 0), (1, 10, 100)___"), SV("{:_^30n}"), input);

	// ***** Only underlying has a format-spec
	check(SV("[(42, 99, 0)   , (1, 10, 100)  ]"), SV("{::14}"), input);
	check(SV("[(42, 99, 0)***, (1, 10, 100)**]"), SV("{::*<14}"), input);
	check(SV("[_(42, 99, 0)__, _(1, 10, 100)_]"), SV("{::_^14}"), input);
	check(SV("[###(42, 99, 0), ##(1, 10, 100)]"), SV("{::#>14}"), input);

	check(SV("[(42, 99, 0)   , (1, 10, 100)  ]"), SV("{::{}}"), input, 14);
	check(SV("[(42, 99, 0)***, (1, 10, 100)**]"), SV("{::*<{}}"), input, 14);
	check(SV("[_(42, 99, 0)__, _(1, 10, 100)_]"), SV("{::_^{}}"), input, 14);
	check(SV("[###(42, 99, 0), ##(1, 10, 100)]"), SV("{::#>{}}"), input, 14);

	// *** type ***
	check(SV("[42, 99, 0, 1, 10, 100]"), SV("{::n}"), input);

	// ***** Both have a format-spec
	check(SV("^^[###(42, 99, 0), ##(1, 10, 100)]^^^"), SV("{:^^37:#>14}"), input);
	check(SV("^^[###(42, 99, 0), ##(1, 10, 100)]^^^"), SV("{:^^37:#>14}"), input);
	check(SV("^^[###(42, 99, 0), ##(1, 10, 100)]^^^"), SV("{:^^{}:#>14}"), input, 37);
	check(SV("^^[###(42, 99, 0), ##(1, 10, 100)]^^^"), SV("{:^^{}:#>{}}"), input, 37, 14);
}

//
// Ranges
//

template <class CharT, class Iterator, class TestFunction, class Array>
void test_with_ranges_impl(TestFunction check, Array input)
{
	auto make_range = [](auto& in)
	{
		using Diff = hamon::iter_difference_t<Iterator>;
		hamon::counted_iterator it(Iterator(in.data()), static_cast<Diff>(in.size()));
		hamon::ranges::subrange range{ hamon::move(it), hamon::default_sentinel };
		return range;
	};
	test_int<CharT>(check, input, make_range);
}

template <class CharT, class TestFunction>
void test_with_ranges(TestFunction check)
{
	hamon::array input{ 1, 2, 42, -42 };
	test_with_ranges_impl<CharT, input_iterator_wrapper<int>>(check, input);
	test_with_ranges_impl<CharT, forward_iterator_wrapper<int>>(check, input);
	test_with_ranges_impl<CharT, bidirectional_iterator_wrapper<int>>(check, input);
	test_with_ranges_impl<CharT, random_access_iterator_wrapper<int>>(check, input);
	test_with_ranges_impl<CharT, contiguous_iterator_wrapper<int>>(check, input);
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
template <class CharT, class TestFunction>
void test_adaptor(TestFunction check)
{
	static_assert(hamon::format_kind<non_contiguous<CharT>> == hamon::range_format::sequence);
	static_assert(hamon::ranges::sized_range<non_contiguous<CharT>>);
	static_assert(!hamon::ranges::contiguous_range<non_contiguous<CharT>>);
	test_char_string<CharT>(
		check,
		non_contiguous<CharT>{hamon::deque{ CharT('H'), CharT('e'), CharT('l'), CharT('l'), CharT('o') }});

	static_assert(hamon::format_kind<contiguous<CharT>> == hamon::range_format::sequence);
	static_assert(hamon::ranges::sized_range<contiguous<CharT>>);
	static_assert(hamon::ranges::contiguous_range<contiguous<CharT>>);
	test_char_string<CharT>(
		check,
		contiguous<CharT>{hamon::vector{ CharT('H'), CharT('e'), CharT('l'), CharT('l'), CharT('o') }});
}

}	// namespace sequence_test

//
// Driver
//

template <class CharT, class TestFunction>
void test_sequence(TestFunction check)
{
	sequence_test::test_char<CharT>(check);

	if (hamon::same_as<CharT, wchar_t>) // avoid testing twice
	{
		sequence_test::test_char_to_wchar(check);
	}

	sequence_test::test_bool<CharT>(check);
	sequence_test::test_int<CharT>(check);
	sequence_test::test_floating_point<CharT>(check);
	sequence_test::test_pointer<CharT>(check);
	sequence_test::test_string<CharT>(check);

	sequence_test::test_status<CharT>(check); // Has its own handler with its own parser

	sequence_test::test_pair_tuple<CharT>(check);
	sequence_test::test_tuple_int<CharT>(check);
	sequence_test::test_tuple_int_int_int<CharT>(check);

	sequence_test::test_with_ranges<CharT>(check);

	sequence_test::test_adaptor<CharT>(check);
}

}	// namespace hamon_format_test

#undef SV
#undef STR
#undef CSTR

#endif // HAMON_FORMAT_TEST_SEQUENCE_HPP
