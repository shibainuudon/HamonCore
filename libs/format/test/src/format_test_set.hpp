/**
 *	@file	format_test_set.hpp
 *
 *	@brief
 */

#ifndef HAMON_FORMAT_TEST_SET_HPP
#define HAMON_FORMAT_TEST_SET_HPP

#include <hamon/format/format_kind.hpp>
#include <hamon/format/range_format.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/pair.hpp>
#include <hamon/set.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/tuple.hpp>
#include <hamon/unordered_set.hpp>
#include <hamon/utility/move.hpp>
#include "format_test_helper.hpp"

#define SV(Str)		hamon::basic_string_view<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str), sizeof(Str) - 1)
#define STR(Str)	hamon::basic_string<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str), sizeof(Str) - 1)

namespace hamon_format_test
{

namespace set_test
{

//
// Char
//

template <class CharT, class TestFunction>
void test_char_default(TestFunction check)
{
	hamon::set input{ CharT('a'), CharT('c'), CharT('b') }; // input not sorted.

	// Note when no range-underlying-spec is present the char is escaped,
	check(SV("{'a', 'b', 'c'}"), SV("{}"), input);
	check(SV("{'a', 'b', 'c'}^42"), SV("{}^42"), input);
	check(SV("{'a', 'b', 'c'}^42"), SV("{:}^42"), input);
	// when one is present there is no escaping,
	check(SV("{a, b, c}"), SV("{::}"), input);
	check(SV("{a, b, c}"), SV("{::<}"), input);
	// unless forced by the type specifier.
	check(SV("{'a', 'b', 'c'}"), SV("{::?}"), input);
	check(SV("{'a', 'b', 'c'}"), SV("{::<?}"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("{'a', 'b', 'c'}     "), SV("{:20}"), input);
	check(SV("{'a', 'b', 'c'}*****"), SV("{:*<20}"), input);
	check(SV("__{'a', 'b', 'c'}___"), SV("{:_^20}"), input);
	check(SV("#####{'a', 'b', 'c'}"), SV("{:#>20}"), input);

	check(SV("{'a', 'b', 'c'}     "), SV("{:{}}"), input, 20);
	check(SV("{'a', 'b', 'c'}*****"), SV("{:*<{}}"), input, 20);
	check(SV("__{'a', 'b', 'c'}___"), SV("{:_^{}}"), input, 20);
	check(SV("#####{'a', 'b', 'c'}"), SV("{:#>{}}"), input, 20);

	// *** n
	check(SV("__'a', 'b', 'c'___"), SV("{:_^18n}"), input);

	// ***** Only underlying has a format-spec
	check(SV("{a   , b   , c   }"), SV("{::4}"), input);
	check(SV("{a***, b***, c***}"), SV("{::*<4}"), input);
	check(SV("{_a__, _b__, _c__}"), SV("{::_^4}"), input);
	check(SV("{:::a, :::b, :::c}"), SV("{:::>4}"), input);

	check(SV("{a   , b   , c   }"), SV("{::{}}"), input, 4);
	check(SV("{a***, b***, c***}"), SV("{::*<{}}"), input, 4);
	check(SV("{_a__, _b__, _c__}"), SV("{::_^{}}"), input, 4);
	check(SV("{:::a, :::b, :::c}"), SV("{:::>{}}"), input, 4);

	// *** sign ***
	check(SV("{97, 98, 99}"), SV("{::-d}"), input);
	check(SV("{+97, +98, +99}"), SV("{::+d}"), input);
	check(SV("{ 97,  98,  99}"), SV("{:: d}"), input);

	// *** alternate form ***
	check(SV("{0x61, 0x62, 0x63}"), SV("{::#x}"), input);

	// *** zero-padding ***
	check(SV("{00141, 00142, 00143}"), SV("{::05o}"), input);

	// *** locale-specific form ***
	check(SV("{a, b, c}"), SV("{::L}"), input);

	// ***** Both have a format-spec
	check(SV("^^{:a, :b, :c}^^^"), SV("{:^^17::>2}"), input);
	check(SV("^^{:a, :b, :c}^^^"), SV("{:^^{}::>2}"), input, 17);
	check(SV("^^{:a, :b, :c}^^^"), SV("{:^^{}::>{}}"), input, 17, 2);
}

// A set can be written as a string, based on
//   [tab:formatter.range.type]
//   s  T shall be charT. ...
// This does not seem very useful, but it is allowed.
template <class CharT, class TestFunction>
void test_char_string(TestFunction check)
{
	hamon::set input{ CharT('a'), CharT('c'), CharT('b') }; // input not sorted.

	check(SV("abc"), SV("{:s}"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("abc   "), SV("{:6s}"), input);
	check(SV("abc***"), SV("{:*<6s}"), input);
	check(SV("_abc__"), SV("{:_^6s}"), input);
	check(SV("###abc"), SV("{:#>6s}"), input);

	check(SV("abc   "), SV("{:{}s}"), input, 6);
	check(SV("abc***"), SV("{:*<{}s}"), input, 6);
	check(SV("_abc__"), SV("{:_^{}s}"), input, 6);
	check(SV("###abc"), SV("{:#>{}s}"), input, 6);
}

// A set can be written as a debug_string, based on
//   [tab:formatter.range.type]
//   ?s T shall be charT. ...
// This does not seem very useful, but it is allowed.
template <class CharT, class TestFunction>
void test_char_escaped_string(TestFunction check)
{
	hamon::set input{ CharT('a'), CharT('c'), CharT('b') }; // input not sorted.

	check(SV("\"abc\""), SV("{:?s}"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV(R"("abc"   )"), SV("{:8?s}"), input);
	check(SV(R"("abc"***)"), SV("{:*<8?s}"), input);
	check(SV(R"(_"abc"__)"), SV("{:_^8?s}"), input);
	check(SV(R"(###"abc")"), SV("{:#>8?s}"), input);

	check(SV(R"("abc"   )"), SV("{:{}?s}"), input, 8);
	check(SV(R"("abc"***)"), SV("{:*<{}?s}"), input, 8);
	check(SV(R"(_"abc"__)"), SV("{:_^{}?s}"), input, 8);
	check(SV(R"(###"abc")"), SV("{:#>{}?s}"), input, 8);
}

template <class CharT, class TestFunction>
void test_char(TestFunction check)
{
	test_char_default<CharT>(check);
	test_char_string<CharT>(check);
	test_char_escaped_string<CharT>(check);
}

//
// char -> wchar_t
//

template <class TestFunction>
void test_char_to_wchar(TestFunction check)
{
	hamon::set input{ 'a', 'c', 'b' }; // input not sorted.

	using CharT = wchar_t;

	// Note when no range-underlying-spec is present the char is escaped,
	check(SV("{'a', 'b', 'c'}"), SV("{}"), input);
	check(SV("{'a', 'b', 'c'}^42"), SV("{}^42"), input);
	check(SV("{'a', 'b', 'c'}^42"), SV("{:}^42"), input);
	// when one is present there is no escaping,
	check(SV("{a, b, c}"), SV("{::}"), input);
	check(SV("{a, b, c}"), SV("{::<}"), input);
	// unless forced by the type specifier.
	check(SV("{'a', 'b', 'c'}"), SV("{::?}"), input);
	check(SV("{'a', 'b', 'c'}"), SV("{::<?}"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("{'a', 'b', 'c'}     "), SV("{:20}"), input);
	check(SV("{'a', 'b', 'c'}*****"), SV("{:*<20}"), input);
	check(SV("__{'a', 'b', 'c'}___"), SV("{:_^20}"), input);
	check(SV("#####{'a', 'b', 'c'}"), SV("{:#>20}"), input);

	check(SV("{'a', 'b', 'c'}     "), SV("{:{}}"), input, 20);
	check(SV("{'a', 'b', 'c'}*****"), SV("{:*<{}}"), input, 20);
	check(SV("__{'a', 'b', 'c'}___"), SV("{:_^{}}"), input, 20);
	check(SV("#####{'a', 'b', 'c'}"), SV("{:#>{}}"), input, 20);

	// *** n
	check(SV("__'a', 'b', 'c'___"), SV("{:_^18n}"), input);

	// ***** Only underlying has a format-spec
	check(SV("{a   , b   , c   }"), SV("{::4}"), input);
	check(SV("{a***, b***, c***}"), SV("{::*<4}"), input);
	check(SV("{_a__, _b__, _c__}"), SV("{::_^4}"), input);
	check(SV("{:::a, :::b, :::c}"), SV("{:::>4}"), input);

	check(SV("{a   , b   , c   }"), SV("{::{}}"), input, 4);
	check(SV("{a***, b***, c***}"), SV("{::*<{}}"), input, 4);
	check(SV("{_a__, _b__, _c__}"), SV("{::_^{}}"), input, 4);
	check(SV("{:::a, :::b, :::c}"), SV("{:::>{}}"), input, 4);

	// *** sign ***
	check(SV("{97, 98, 99}"), SV("{::-d}"), input);
	check(SV("{+97, +98, +99}"), SV("{::+d}"), input);
	check(SV("{ 97,  98,  99}"), SV("{:: d}"), input);

	// *** alternate form ***
	check(SV("{0x61, 0x62, 0x63}"), SV("{::#x}"), input);

	// *** zero-padding ***
	check(SV("{00141, 00142, 00143}"), SV("{::05o}"), input);

	// *** locale-specific form ***
	check(SV("{a, b, c}"), SV("{::L}"), input);

	// ***** Both have a format-spec
	check(SV("^^{:a, :b, :c}^^^"), SV("{:^^17::>2}"), input);
	check(SV("^^{:a, :b, :c}^^^"), SV("{:^^{}::>2}"), input, 17);
	check(SV("^^{:a, :b, :c}^^^"), SV("{:^^{}::>{}}"), input, 17, 2);
}

//
// Bool
//

template <class CharT, class TestFunction>
void test_bool(TestFunction check)
{
	hamon::set input{ true, false };

	check(SV("{false, true}"), SV("{}"), input);
	check(SV("{false, true}^42"), SV("{}^42"), input);
	check(SV("{false, true}^42"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("{false, true}     "), SV("{:18}"), input);
	check(SV("{false, true}*****"), SV("{:*<18}"), input);
	check(SV("__{false, true}___"), SV("{:_^18}"), input);
	check(SV("#####{false, true}"), SV("{:#>18}"), input);

	check(SV("{false, true}     "), SV("{:{}}"), input, 18);
	check(SV("{false, true}*****"), SV("{:*<{}}"), input, 18);
	check(SV("__{false, true}___"), SV("{:_^{}}"), input, 18);
	check(SV("#####{false, true}"), SV("{:#>{}}"), input, 18);

	// *** n
	check(SV("__false, true___"), SV("{:_^16n}"), input);

	// ***** Only underlying has a format-spec
	check(SV("{false  , true   }"), SV("{::7}"), input);
	check(SV("{false**, true***}"), SV("{::*<7}"), input);
	check(SV("{_false_, _true__}"), SV("{::_^7}"), input);
	check(SV("{::false, :::true}"), SV("{:::>7}"), input);

	check(SV("{false  , true   }"), SV("{::{}}"), input, 7);
	check(SV("{false**, true***}"), SV("{::*<{}}"), input, 7);
	check(SV("{_false_, _true__}"), SV("{::_^{}}"), input, 7);
	check(SV("{::false, :::true}"), SV("{:::>{}}"), input, 7);

	// *** sign ***
	check(SV("{0, 1}"), SV("{::-d}"), input);
	check(SV("{+0, +1}"), SV("{::+d}"), input);
	check(SV("{ 0,  1}"), SV("{:: d}"), input);

	// *** alternate form ***
	check(SV("{0x0, 0x1}"), SV("{::#x}"), input);

	// *** zero-padding ***
	check(SV("{00000, 00001}"), SV("{::05o}"), input);

	// *** locale-specific form ***
	check(SV("{false, true}"), SV("{::L}"), input);

	// ***** Both have a format-spec
	check(SV("^^{::false, :::true}^^^"), SV("{:^^23::>7}"), input);
	check(SV("^^{::false, :::true}^^^"), SV("{:^^{}::>7}"), input, 23);
	check(SV("^^{::false, :::true}^^^"), SV("{:^^{}::>{}}"), input, 23, 7);
}

template <class CharT, class TestFunction>
void test_bool_multiset(TestFunction check)
{
	hamon::multiset<bool, hamon::greater<bool>> input{ true, false, true }; // unordered

	check(SV("{true, true, false}"), SV("{}"), input);
	check(SV("{true, true, false}^42"), SV("{}^42"), input);
	check(SV("{true, true, false}^42"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("{true, true, false}     "), SV("{:24}"), input);
	check(SV("{true, true, false}*****"), SV("{:*<24}"), input);
	check(SV("__{true, true, false}___"), SV("{:_^24}"), input);
	check(SV("#####{true, true, false}"), SV("{:#>24}"), input);

	check(SV("{true, true, false}     "), SV("{:{}}"), input, 24);
	check(SV("{true, true, false}*****"), SV("{:*<{}}"), input, 24);
	check(SV("__{true, true, false}___"), SV("{:_^{}}"), input, 24);
	check(SV("#####{true, true, false}"), SV("{:#>{}}"), input, 24);

	// *** n
	check(SV("__true, true, false___"), SV("{:_^22n}"), input);

	// ***** Only underlying has a format-spec
	check(SV("{true   , true   , false  }"), SV("{::7}"), input);
	check(SV("{true***, true***, false**}"), SV("{::*<7}"), input);
	check(SV("{_true__, _true__, _false_}"), SV("{::_^7}"), input);
	check(SV("{:::true, :::true, ::false}"), SV("{:::>7}"), input);

	check(SV("{true   , true   , false  }"), SV("{::{}}"), input, 7);
	check(SV("{true***, true***, false**}"), SV("{::*<{}}"), input, 7);
	check(SV("{_true__, _true__, _false_}"), SV("{::_^{}}"), input, 7);
	check(SV("{:::true, :::true, ::false}"), SV("{:::>{}}"), input, 7);

	// *** sign ***
	check(SV("{1, 1, 0}"), SV("{::-d}"), input);
	check(SV("{+1, +1, +0}"), SV("{::+d}"), input);
	check(SV("{ 1,  1,  0}"), SV("{:: d}"), input);

	// *** alternate form ***
	check(SV("{0x1, 0x1, 0x0}"), SV("{::#x}"), input);

	// *** zero-padding ***
	check(SV("{00001, 00001, 00000}"), SV("{::05o}"), input);

	// *** locale-specific form ***
	check(SV("{true, true, false}"), SV("{::L}"), input);

	// ***** Both have a format-spec
	check(SV("^^{:::true, :::true, ::false}^^^"), SV("{:^^32::>7}"), input);
	check(SV("^^{:::true, :::true, ::false}^^^"), SV("{:^^{}::>7}"), input, 32);
	check(SV("^^{:::true, :::true, ::false}^^^"), SV("{:^^{}::>{}}"), input, 32, 7);
}

//
// Integral
//

template <class CharT, class TestFunction>
void test_int(TestFunction check, auto&& input)
{
	check(SV("{-42, 1, 2, 42}"), SV("{}"), input);
	check(SV("{-42, 1, 2, 42}^42"), SV("{}^42"), input);
	check(SV("{-42, 1, 2, 42}^42"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("{-42, 1, 2, 42}     "), SV("{:20}"), input);
	check(SV("{-42, 1, 2, 42}*****"), SV("{:*<20}"), input);
	check(SV("__{-42, 1, 2, 42}___"), SV("{:_^20}"), input);
	check(SV("#####{-42, 1, 2, 42}"), SV("{:#>20}"), input);

	check(SV("{-42, 1, 2, 42}     "), SV("{:{}}"), input, 20);
	check(SV("{-42, 1, 2, 42}*****"), SV("{:*<{}}"), input, 20);
	check(SV("__{-42, 1, 2, 42}___"), SV("{:_^{}}"), input, 20);
	check(SV("#####{-42, 1, 2, 42}"), SV("{:#>{}}"), input, 20);

	// *** n
	check(SV("__-42, 1, 2, 42___"), SV("{:_^18n}"), input);

	// ***** Only underlying has a format-spec
	check(SV("{  -42,     1,     2,    42}"), SV("{::5}"), input);
	check(SV("{-42**, 1****, 2****, 42***}"), SV("{::*<5}"), input);
	check(SV("{_-42_, __1__, __2__, _42__}"), SV("{::_^5}"), input);
	check(SV("{::-42, ::::1, ::::2, :::42}"), SV("{:::>5}"), input);

	check(SV("{  -42,     1,     2,    42}"), SV("{::{}}"), input, 5);
	check(SV("{-42**, 1****, 2****, 42***}"), SV("{::*<{}}"), input, 5);
	check(SV("{_-42_, __1__, __2__, _42__}"), SV("{::_^{}}"), input, 5);
	check(SV("{::-42, ::::1, ::::2, :::42}"), SV("{:::>{}}"), input, 5);

	// *** sign ***
	check(SV("{-42, 1, 2, 42}"), SV("{::-}"), input);
	check(SV("{-42, +1, +2, +42}"), SV("{::+}"), input);
	check(SV("{-42,  1,  2,  42}"), SV("{:: }"), input);

	// *** alternate form ***
	check(SV("{-0x2a, 0x1, 0x2, 0x2a}"), SV("{::#x}"), input);

	// *** zero-padding ***
	check(SV("{-0042, 00001, 00002, 00042}"), SV("{::05}"), input);
	check(SV("{-002a, 00001, 00002, 0002a}"), SV("{::05x}"), input);
	check(SV("{-0x2a, 0x001, 0x002, 0x02a}"), SV("{::#05x}"), input);

	// *** locale-specific form ***
	check(SV("{-42, 1, 2, 42}"), SV("{::L}"), input); // does nothing in this test, but is accepted.

	// ***** Both have a format-spec
	check(SV("^^{::-42, ::::1, ::::2, :::42}^^^"), SV("{:^^33::>5}"), input);
	check(SV("^^{::-42, ::::1, ::::2, :::42}^^^"), SV("{:^^{}::>5}"), input, 33);
	check(SV("^^{::-42, ::::1, ::::2, :::42}^^^"), SV("{:^^{}::>{}}"), input, 33, 5);
}

template <class CharT, class TestFunction>
void test_int(TestFunction check)
{
	test_int<CharT>(check, hamon::set{ 1, 42, 2, -42 });      // unsorted
	test_int<CharT>(check, hamon::multiset{ 1, 42, 2, -42 }); // unsorted
}

//
// Floating point
//

template <class CharT, class TestFunction>
void test_floating_point(TestFunction check, auto&& input)
{
	check(SV("{-42.5, 0, 1.25, 42.5}"), SV("{}"), input);
	check(SV("{-42.5, 0, 1.25, 42.5}^42"), SV("{}^42"), input);
	check(SV("{-42.5, 0, 1.25, 42.5}^42"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("{-42.5, 0, 1.25, 42.5}     "), SV("{:27}"), input);
	check(SV("{-42.5, 0, 1.25, 42.5}*****"), SV("{:*<27}"), input);
	check(SV("__{-42.5, 0, 1.25, 42.5}___"), SV("{:_^27}"), input);
	check(SV("#####{-42.5, 0, 1.25, 42.5}"), SV("{:#>27}"), input);

	check(SV("{-42.5, 0, 1.25, 42.5}     "), SV("{:{}}"), input, 27);
	check(SV("{-42.5, 0, 1.25, 42.5}*****"), SV("{:*<{}}"), input, 27);
	check(SV("__{-42.5, 0, 1.25, 42.5}___"), SV("{:_^{}}"), input, 27);
	check(SV("#####{-42.5, 0, 1.25, 42.5}"), SV("{:#>{}}"), input, 27);

	// *** n
	check(SV("__-42.5, 0, 1.25, 42.5___"), SV("{:_^25n}"), input);

	// ***** Only underlying has a format-spec
	check(SV("{-42.5,     0,  1.25,  42.5}"), SV("{::5}"), input);
	check(SV("{-42.5, 0****, 1.25*, 42.5*}"), SV("{::*<5}"), input);
	check(SV("{-42.5, __0__, 1.25_, 42.5_}"), SV("{::_^5}"), input);
	check(SV("{-42.5, ::::0, :1.25, :42.5}"), SV("{:::>5}"), input);

	check(SV("{-42.5,     0,  1.25,  42.5}"), SV("{::{}}"), input, 5);
	check(SV("{-42.5, 0****, 1.25*, 42.5*}"), SV("{::*<{}}"), input, 5);
	check(SV("{-42.5, __0__, 1.25_, 42.5_}"), SV("{::_^{}}"), input, 5);
	check(SV("{-42.5, ::::0, :1.25, :42.5}"), SV("{:::>{}}"), input, 5);

	// *** sign ***
	check(SV("{-42.5, 0, 1.25, 42.5}"), SV("{::-}"), input);
	check(SV("{-42.5, +0, +1.25, +42.5}"), SV("{::+}"), input);
	check(SV("{-42.5,  0,  1.25,  42.5}"), SV("{:: }"), input);

	// *** alternate form ***
	check(SV("{-42.5, 0., 1.25, 42.5}"), SV("{::#}"), input);

	// *** zero-padding ***
	check(SV("{-42.5, 00000, 01.25, 042.5}"), SV("{::05}"), input);
	check(SV("{-42.5, 0000., 01.25, 042.5}"), SV("{::#05}"), input);

	// *** precision ***
	check(SV("{-42, 0, 1.2, 42}"), SV("{::.2}"), input);
	check(SV("{-42.500, 0.000, 1.250, 42.500}"), SV("{::.3f}"), input);

	check(SV("{-42, 0, 1.2, 42}"), SV("{::.{}}"), input, 2);
	check(SV("{-42.500, 0.000, 1.250, 42.500}"), SV("{::.{}f}"), input, 3);

	// *** locale-specific form ***
	check(SV("{-42.5, 0, 1.25, 42.5}"), SV("{::L}"), input); // does not require locales present
#ifndef TEST_HAS_NO_LOCALIZATION
	// TODO FMT Enable with locale testing active
#  if 0
	std::locale::global(std::locale(LOCALE_fr_FR_UTF_8));
	check(SV("{-42,5, 0, 1,25, 42,5}"), SV("{::L}"), input);

	std::locale::global(std::locale(LOCALE_en_US_UTF_8));
	check(SV("{-42.5, 0, 1.25, 42.5}"), SV("{::L}"), input);

	std::locale::global(std::locale::classic());
#  endif
#endif // TEST_HAS_NO_LOCALIZATION

	// ***** Both have a format-spec
	check(SV("^^{-42.5, ::::0, :1.25, :42.5}^^^"), SV("{:^^33::>5}"), input);
	check(SV("^^{-42.5, ::::0, :1.25, :42.5}^^^"), SV("{:^^{}::>5}"), input, 33);
	check(SV("^^{-42.5, ::::0, :1.25, :42.5}^^^"), SV("{:^^{}::>{}}"), input, 33, 5);

	check(SV("^^{::-42, ::::0, ::1.2, :::42}^^^"), SV("{:^^33::>5.2}"), input);
	check(SV("^^{::-42, ::::0, ::1.2, :::42}^^^"), SV("{:^^{}::>5.2}"), input, 33);
	check(SV("^^{::-42, ::::0, ::1.2, :::42}^^^"), SV("{:^^{}::>{}.2}"), input, 33, 5);
	check(SV("^^{::-42, ::::0, ::1.2, :::42}^^^"), SV("{:^^{}::>{}.{}}"), input, 33, 5, 2);
}

template <class CharT, class TestFunction>
void test_floating_point(TestFunction check)
{
	test_floating_point<CharT>(check, hamon::set{ -42.5f, 0.0f, 1.25f, 42.5f });
	test_floating_point<CharT>(check, hamon::multiset{ -42.5, 0.0, 1.25, 42.5 });
	test_floating_point<CharT>(check, hamon::set{ -42.5l, 0.0l, 1.25l, 42.5l });
}

//
// Pointer
//

template <class CharT, class TestFunction>
void test_pointer(TestFunction check, auto&& input)
{
	check(SV("{0x0}"), SV("{}"), input);
	check(SV("{0x0}^42"), SV("{}^42"), input);
	check(SV("{0x0}^42"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("{0x0}     "), SV("{:10}"), input);
	check(SV("{0x0}*****"), SV("{:*<10}"), input);
	check(SV("__{0x0}___"), SV("{:_^10}"), input);
	check(SV("#####{0x0}"), SV("{:#>10}"), input);

	check(SV("{0x0}     "), SV("{:{}}"), input, 10);
	check(SV("{0x0}*****"), SV("{:*<{}}"), input, 10);
	check(SV("__{0x0}___"), SV("{:_^{}}"), input, 10);
	check(SV("#####{0x0}"), SV("{:#>{}}"), input, 10);

	// *** n
	check(SV("_0x0_"), SV("{:_^5n}"), input);

	// ***** Only underlying has a format-spec
	check(SV("{  0x0}"), SV("{::5}"), input);
	check(SV("{0x0**}"), SV("{::*<5}"), input);
	check(SV("{_0x0_}"), SV("{::_^5}"), input);
	check(SV("{::0x0}"), SV("{:::>5}"), input);

	check(SV("{  0x0}"), SV("{::{}}"), input, 5);
	check(SV("{0x0**}"), SV("{::*<{}}"), input, 5);
	check(SV("{_0x0_}"), SV("{::_^{}}"), input, 5);
	check(SV("{::0x0}"), SV("{:::>{}}"), input, 5);

	// *** zero-padding ***
	check(SV("{0x0000}"), SV("{::06}"), input);
	check(SV("{0x0000}"), SV("{::06p}"), input);
	check(SV("{0X0000}"), SV("{::06P}"), input);

	// ***** Both have a format-spec
	check(SV("^^{::0x0}^^^"), SV("{:^^12::>5}"), input);
	check(SV("^^{::0x0}^^^"), SV("{:^^{}::>5}"), input, 12);
	check(SV("^^{::0x0}^^^"), SV("{:^^{}::>{}}"), input, 12, 5);

	check(SV("^^{::0x0}^^^"), SV("{:^^12::>5}"), input);
	check(SV("^^{::0x0}^^^"), SV("{:^^{}::>5}"), input, 12);
	check(SV("^^{::0x0}^^^"), SV("{:^^{}::>{}}"), input, 12, 5);
}

template <class CharT, class TestFunction>
void test_pointer(TestFunction check)
{
	// Note nullptr_t can only be equality compared so not used in a set.
	test_pointer<CharT>(check, hamon::unordered_set{ static_cast<const void*>(0) });
	test_pointer<CharT>(check, hamon::unordered_multiset{ static_cast<void*>(0) });
}

//
// String
//

template <class CharT, class TestFunction>
void test_string(TestFunction check, auto&& input)
{
	check(SV(R"({"Hello", "world"})"), SV("{}"), input);
	check(SV(R"({"Hello", "world"}^42)"), SV("{}^42"), input);
	check(SV(R"({"Hello", "world"}^42)"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV(R"({"Hello", "world"}     )"), SV("{:23}"), input);
	check(SV(R"({"Hello", "world"}*****)"), SV("{:*<23}"), input);
	check(SV(R"(__{"Hello", "world"}___)"), SV("{:_^23}"), input);
	check(SV(R"(#####{"Hello", "world"})"), SV("{:#>23}"), input);

	check(SV(R"({"Hello", "world"}     )"), SV("{:{}}"), input, 23);
	check(SV(R"({"Hello", "world"}*****)"), SV("{:*<{}}"), input, 23);
	check(SV(R"(__{"Hello", "world"}___)"), SV("{:_^{}}"), input, 23);
	check(SV(R"(#####{"Hello", "world"})"), SV("{:#>{}}"), input, 23);

	// *** n
	check(SV(R"(_"Hello", "world"_)"), SV("{:_^18n}"), input);

	// ***** Only underlying has a format-spec
	check(SV(R"({Hello   , world   })"), SV("{::8}"), input);
	check(SV(R"({Hello***, world***})"), SV("{::*<8}"), input);
	check(SV(R"({_Hello__, _world__})"), SV("{::_^8}"), input);
	check(SV(R"({:::Hello, :::world})"), SV("{:::>8}"), input);

	check(SV(R"({Hello   , world   })"), SV("{::{}}"), input, 8);
	check(SV(R"({Hello***, world***})"), SV("{::*<{}}"), input, 8);
	check(SV(R"({_Hello__, _world__})"), SV("{::_^{}}"), input, 8);
	check(SV(R"({:::Hello, :::world})"), SV("{:::>{}}"), input, 8);

	// *** precision ***
	check(SV(R"({Hel, wor})"), SV("{::.3}"), input);

	check(SV(R"({Hel, wor})"), SV("{::.{}}"), input, 3);

	// ***** Both have a format-spec
	check(SV(R"(^^{:::Hello, :::world}^^^)"), SV("{:^^25::>8}"), input);
	check(SV(R"(^^{:::Hello, :::world}^^^)"), SV("{:^^{}::>8}"), input, 25);
	check(SV(R"(^^{:::Hello, :::world}^^^)"), SV("{:^^{}::>{}}"), input, 25, 8);

	check(SV(R"(^^{:::Hello, :::world}^^^)"), SV("{:^^25::>8}"), input);
	check(SV(R"(^^{:::Hello, :::world}^^^)"), SV("{:^^{}::>8}"), input, 25);
	check(SV(R"(^^{:::Hello, :::world}^^^)"), SV("{:^^{}::>{}}"), input, 25, 8);
}

template <class CharT, class TestFunction>
void test_string(TestFunction check)
{
	test_string<CharT>(check, hamon::set{ STR("Hello"), STR("world") });
	test_string<CharT>(check, hamon::set{ SV("Hello"), SV("world") });
}

//
// Handle
//

template <class CharT, class TestFunction>
void test_status(TestFunction check)
{
	hamon::set input{ status::foo, status::bar, status::foobar }; // unordered input

	check(SV("{0x5555, 0xaa55, 0xaaaa}"), SV("{}"), input);
	check(SV("{0x5555, 0xaa55, 0xaaaa}^42"), SV("{}^42"), input);
	check(SV("{0x5555, 0xaa55, 0xaaaa}^42"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("{0x5555, 0xaa55, 0xaaaa}     "), SV("{:29}"), input);
	check(SV("{0x5555, 0xaa55, 0xaaaa}*****"), SV("{:*<29}"), input);
	check(SV("__{0x5555, 0xaa55, 0xaaaa}___"), SV("{:_^29}"), input);
	check(SV("#####{0x5555, 0xaa55, 0xaaaa}"), SV("{:#>29}"), input);

	check(SV("{0x5555, 0xaa55, 0xaaaa}     "), SV("{:{}}"), input, 29);
	check(SV("{0x5555, 0xaa55, 0xaaaa}*****"), SV("{:*<{}}"), input, 29);
	check(SV("__{0x5555, 0xaa55, 0xaaaa}___"), SV("{:_^{}}"), input, 29);
	check(SV("#####{0x5555, 0xaa55, 0xaaaa}"), SV("{:#>{}}"), input, 29);

	// *** n
	check(SV("__0x5555, 0xaa55, 0xaaaa___"), SV("{:_^27n}"), input);

	// ***** Only underlying has a format-spec
	check(SV("{0x5555, 0xaa55, 0xaaaa}"), SV("{::x}"), input);
	check(SV("{0X5555, 0XAA55, 0XAAAA}"), SV("{::X}"), input);
	check(SV("{bar, foobar, foo}"), SV("{::s}"), input);

	// ***** Both have a format-spec
	check(SV("^^{0X5555, 0XAA55, 0XAAAA}^^^"), SV("{:^^29:X}"), input);
	check(SV("^^{0X5555, 0XAA55, 0XAAAA}^^^"), SV("{:^^{}:X}"), input, 29);
}

//
// Pair
//

template <class CharT, class TestFunction>
void test_pair_tuple(TestFunction check, auto&& input)
{
	check(SV("{(1, 'a'), (42, '*')}"), SV("{}"), input);
	check(SV("{(1, 'a'), (42, '*')}^42"), SV("{}^42"), input);
	check(SV("{(1, 'a'), (42, '*')}^42"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("{(1, 'a'), (42, '*')}     "), SV("{:26}"), input);
	check(SV("{(1, 'a'), (42, '*')}*****"), SV("{:*<26}"), input);
	check(SV("__{(1, 'a'), (42, '*')}___"), SV("{:_^26}"), input);
	check(SV("#####{(1, 'a'), (42, '*')}"), SV("{:#>26}"), input);

	check(SV("{(1, 'a'), (42, '*')}     "), SV("{:{}}"), input, 26);
	check(SV("{(1, 'a'), (42, '*')}*****"), SV("{:*<{}}"), input, 26);
	check(SV("__{(1, 'a'), (42, '*')}___"), SV("{:_^{}}"), input, 26);
	check(SV("#####{(1, 'a'), (42, '*')}"), SV("{:#>{}}"), input, 26);

	// *** n
	check(SV("__(1, 'a'), (42, '*')___"), SV("{:_^24n}"), input);
	check(SV("__(1, 'a'), (42, '*')___"), SV("{:_^24nm}"), input); // m should have no effect

	// *** type ***
	check(SV("__{(1, 'a'), (42, '*')}___"), SV("{:_^26m}"), input);

	// ***** Only underlying has a format-spec
	check(SV("{(1, 'a')   , (42, '*')  }"), SV("{::11}"), input);
	check(SV("{(1, 'a')***, (42, '*')**}"), SV("{::*<11}"), input);
	check(SV("{_(1, 'a')__, _(42, '*')_}"), SV("{::_^11}"), input);
	check(SV("{###(1, 'a'), ##(42, '*')}"), SV("{::#>11}"), input);

	check(SV("{(1, 'a')   , (42, '*')  }"), SV("{::{}}"), input, 11);
	check(SV("{(1, 'a')***, (42, '*')**}"), SV("{::*<{}}"), input, 11);
	check(SV("{_(1, 'a')__, _(42, '*')_}"), SV("{::_^{}}"), input, 11);
	check(SV("{###(1, 'a'), ##(42, '*')}"), SV("{::#>{}}"), input, 11);

	// *** type ***
	check(SV("{1: 'a', 42: '*'}"), SV("{::m}"), input);
	check(SV("{1, 'a', 42, '*'}"), SV("{::n}"), input);

	// ***** Both have a format-spec
	check(SV("^^{###(1, 'a'), ##(42, '*')}^^^"), SV("{:^^31:#>11}"), input);
	check(SV("^^{###(1, 'a'), ##(42, '*')}^^^"), SV("{:^^31:#>11}"), input);
	check(SV("^^{###(1, 'a'), ##(42, '*')}^^^"), SV("{:^^{}:#>11}"), input, 31);
	check(SV("^^{###(1, 'a'), ##(42, '*')}^^^"), SV("{:^^{}:#>{}}"), input, 31, 11);

	check(SV("1: 'a', 42: '*'"), SV("{:n:m}"), input);
	check(SV("1, 'a', 42, '*'"), SV("{:n:n}"), input);
	check(SV("{1: 'a', 42: '*'}"), SV("{:m:m}"), input);
	check(SV("{1, 'a', 42, '*'}"), SV("{:m:n}"), input);
}

template <class CharT, class TestFunction>
void test_pair_tuple(TestFunction check)
{
	test_pair_tuple<CharT>(check, hamon::set{ hamon::make_pair(1, CharT('a')), hamon::make_pair(42, CharT('*')) });
	test_pair_tuple<CharT>(check, hamon::set{ hamon::make_tuple(1, CharT('a')), hamon::make_tuple(42, CharT('*')) });
}

//
// Tuple 1
//

template <class CharT, class TestFunction>
void test_tuple_int(TestFunction check)
{
	hamon::set input{ hamon::make_tuple(42), hamon::make_tuple(99) };

	check(SV("{(42), (99)}"), SV("{}"), input);
	check(SV("{(42), (99)}^42"), SV("{}^42"), input);
	check(SV("{(42), (99)}^42"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("{(42), (99)}     "), SV("{:17}"), input);
	check(SV("{(42), (99)}*****"), SV("{:*<17}"), input);
	check(SV("__{(42), (99)}___"), SV("{:_^17}"), input);
	check(SV("#####{(42), (99)}"), SV("{:#>17}"), input);

	check(SV("{(42), (99)}     "), SV("{:{}}"), input, 17);
	check(SV("{(42), (99)}*****"), SV("{:*<{}}"), input, 17);
	check(SV("__{(42), (99)}___"), SV("{:_^{}}"), input, 17);
	check(SV("#####{(42), (99)}"), SV("{:#>{}}"), input, 17);

	// *** n
	check(SV("__(42), (99)___"), SV("{:_^15n}"), input);

	// ***** Only underlying has a format-spec
	check(SV("{(42)   , (99)   }"), SV("{::7}"), input);
	check(SV("{(42)***, (99)***}"), SV("{::*<7}"), input);
	check(SV("{_(42)__, _(99)__}"), SV("{::_^7}"), input);
	check(SV("{###(42), ###(99)}"), SV("{::#>7}"), input);

	check(SV("{(42)   , (99)   }"), SV("{::{}}"), input, 7);
	check(SV("{(42)***, (99)***}"), SV("{::*<{}}"), input, 7);
	check(SV("{_(42)__, _(99)__}"), SV("{::_^{}}"), input, 7);
	check(SV("{###(42), ###(99)}"), SV("{::#>{}}"), input, 7);

	// *** type ***
	check(SV("{42, 99}"), SV("{::n}"), input);

	// ***** Both have a format-spec
	check(SV("^^{###(42), ###(99)}^^^"), SV("{:^^23:#>7}"), input);
	check(SV("^^{###(42), ###(99)}^^^"), SV("{:^^23:#>7}"), input);
	check(SV("^^{###(42), ###(99)}^^^"), SV("{:^^{}:#>7}"), input, 23);
	check(SV("^^{###(42), ###(99)}^^^"), SV("{:^^{}:#>{}}"), input, 23, 7);
}

//
// Tuple 3
//

template <class CharT, class TestFunction>
void test_tuple_int_int_int(TestFunction check)
{
	hamon::set input{ hamon::make_tuple(42, 99, 0), hamon::make_tuple(1, 10, 100) }; // unordered

	check(SV("{(1, 10, 100), (42, 99, 0)}"), SV("{}"), input);
	check(SV("{(1, 10, 100), (42, 99, 0)}^42"), SV("{}^42"), input);
	check(SV("{(1, 10, 100), (42, 99, 0)}^42"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("{(1, 10, 100), (42, 99, 0)}     "), SV("{:32}"), input);
	check(SV("{(1, 10, 100), (42, 99, 0)}*****"), SV("{:*<32}"), input);
	check(SV("__{(1, 10, 100), (42, 99, 0)}___"), SV("{:_^32}"), input);
	check(SV("#####{(1, 10, 100), (42, 99, 0)}"), SV("{:#>32}"), input);

	check(SV("{(1, 10, 100), (42, 99, 0)}     "), SV("{:{}}"), input, 32);
	check(SV("{(1, 10, 100), (42, 99, 0)}*****"), SV("{:*<{}}"), input, 32);
	check(SV("__{(1, 10, 100), (42, 99, 0)}___"), SV("{:_^{}}"), input, 32);
	check(SV("#####{(1, 10, 100), (42, 99, 0)}"), SV("{:#>{}}"), input, 32);

	// *** n
	check(SV("__(1, 10, 100), (42, 99, 0)___"), SV("{:_^30n}"), input);

	// ***** Only underlying has a format-spec
	check(SV("{(1, 10, 100)  , (42, 99, 0)   }"), SV("{::14}"), input);
	check(SV("{(1, 10, 100)**, (42, 99, 0)***}"), SV("{::*<14}"), input);
	check(SV("{_(1, 10, 100)_, _(42, 99, 0)__}"), SV("{::_^14}"), input);
	check(SV("{##(1, 10, 100), ###(42, 99, 0)}"), SV("{::#>14}"), input);

	check(SV("{(1, 10, 100)  , (42, 99, 0)   }"), SV("{::{}}"), input, 14);
	check(SV("{(1, 10, 100)**, (42, 99, 0)***}"), SV("{::*<{}}"), input, 14);
	check(SV("{_(1, 10, 100)_, _(42, 99, 0)__}"), SV("{::_^{}}"), input, 14);
	check(SV("{##(1, 10, 100), ###(42, 99, 0)}"), SV("{::#>{}}"), input, 14);

	// *** type ***
	check(SV("{1, 10, 100, 42, 99, 0}"), SV("{::n}"), input);

	// ***** Both have a format-spec
	check(SV("^^{##(1, 10, 100), ###(42, 99, 0)}^^^"), SV("{:^^37:#>14}"), input);
	check(SV("^^{##(1, 10, 100), ###(42, 99, 0)}^^^"), SV("{:^^37:#>14}"), input);
	check(SV("^^{##(1, 10, 100), ###(42, 99, 0)}^^^"), SV("{:^^{}:#>14}"), input, 37);
	check(SV("^^{##(1, 10, 100), ###(42, 99, 0)}^^^"), SV("{:^^{}:#>{}}"), input, 37, 14);
}

//
// Adaptor
//

class adaptor
{
	using adaptee = hamon::set<int>;

public:
	using key_type = typename adaptee::key_type;
	using iterator = typename adaptee::iterator;

	iterator begin() { return data_.begin(); }
	iterator end() { return data_.end(); }

	explicit adaptor(hamon::set<int>&& data) : data_(hamon::move(data)) {}

private:
	adaptee data_;
};

static_assert(hamon::format_kind<adaptor> == hamon::range_format::set);

template <class CharT, class TestFunction>
void test_adaptor(TestFunction check)
{
	test_int<CharT>(check, adaptor{ hamon::set{1, 42, 2, -42} });
}

}	// namespace set_test

//
// Driver
//

template <class CharT, class TestFunction>
void test_set(TestFunction check)
{
	set_test::test_char<CharT>(check);

	if (hamon::same_as<CharT, wchar_t>) // avoid testing twice
	{
		set_test::test_char_to_wchar(check);
	}

	set_test::test_bool<CharT>(check);
	set_test::test_bool_multiset<CharT>(check);
	set_test::test_int<CharT>(check);
	set_test::test_floating_point<CharT>(check);
	set_test::test_pointer<CharT>(check);
	set_test::test_string<CharT>(check);

	set_test::test_status<CharT>(check); // Has its own handler with its own parser

	set_test::test_pair_tuple<CharT>(check);
	set_test::test_tuple_int<CharT>(check);
	set_test::test_tuple_int_int_int<CharT>(check);

	set_test::test_adaptor<CharT>(check);
}

}	// namespace hamon_format_test

#undef SV
#undef STR

#endif // HAMON_FORMAT_TEST_SET_HPP
