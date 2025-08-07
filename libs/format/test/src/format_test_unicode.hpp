/**
 *	@file	format_test_unicode.hpp
 *
 *	@brief
 */

#ifndef HAMON_FORMAT_TEST_UNICODE_HPP
#define HAMON_FORMAT_TEST_UNICODE_HPP

#include <hamon/detail/statically_widen.hpp>
#include <hamon/string_view.hpp>

#define SV(Str)		hamon::basic_string_view<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str))

namespace hamon_format_test
{

namespace unicode_test
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4566)	// ユニバーサル文字名 '' によって表示されている文字は、現在のコード ページ (932) で表示できません

template <typename CharT, typename TestFunction>
static void test_single_code_point_fill(TestFunction check)
{
	//*** 1-byte code points ***
	check(SV("* *"), SV("{:*^3}"), SV(" "));
	check(SV("*~*"), SV("{:*^3}"), SV("~"));

	//*** 2-byte code points ***
	check(SV("*\u00a1*"), SV("{:*^3}"), SV("\u00a1")); // INVERTED EXCLAMATION MARK
	check(SV("*\u07ff*"), SV("{:*^3}"), SV("\u07ff")); // NKO TAMAN SIGN

	//*** 3-byte code points ***
	check(SV("*\u0800*"), SV("{:*^3}"), SV("\u0800")); // SAMARITAN LETTER ALAF
	check(SV("*\ufffd*"), SV("{:*^3}"), SV("\ufffd")); // REPLACEMENT CHARACTER

	// 2 column ranges
	check(SV("*\u1100*"), SV("{:*^4}"), SV("\u1100")); // HANGUL CHOSEONG KIYEOK
	check(SV("*\u115f*"), SV("{:*^4}"), SV("\u115f")); // HANGUL CHOSEONG FILLER

	check(SV("*\u2329*"), SV("{:*^4}"), SV("\u2329")); // LEFT-POINTING ANGLE BRACKET
	check(SV("*\u232a*"), SV("{:*^4}"), SV("\u232a")); // RIGHT-POINTING ANGLE BRACKET

	check(SV("*\u2e80*"), SV("{:*^4}"), SV("\u2e80")); // CJK RADICAL REPEAT
	check(SV("*\u303e*"), SV("{:*^4}"), SV("\u303e")); // IDEOGRAPHIC VARIATION INDICATOR

	check(SV("*\u3041*"), SV("{:*^4}"), SV("\u3041")); // U+3041 HIRAGANA LETTER SMALL A
	check(SV("*\ua4d0*"), SV("{:*^3}"), SV("\ua4d0")); // U+A4D0 LISU LETTER BA

	check(SV("*\uac00*"), SV("{:*^4}"), SV("\uac00")); // <Hangul Syllable, First>
	check(SV("*\ud7a3*"), SV("{:*^4}"), SV("\ud7a3")); // Hangul Syllable Hih

	check(SV("*\uf900*"), SV("{:*^4}"), SV("\uf900")); // CJK COMPATIBILITY IDEOGRAPH-F900
	check(SV("*\ufaff*"), SV("{:*^4}"), SV("\ufaff")); // U+FB00 LATIN SMALL LIGATURE FF

	check(SV("*\ufe10*"), SV("{:*^4}"), SV("\ufe10")); // PRESENTATION FORM FOR VERTICAL COMMA
	check(SV("*\ufe19*"), SV("{:*^4}"), SV("\ufe19")); // PRESENTATION FORM FOR VERTICAL HORIZONTAL ELLIPSIS

	check(SV("*\ufe30*"), SV("{:*^4}"), SV("\ufe30")); // PRESENTATION FORM FOR VERTICAL TWO DOT LEADER
	check(SV("*\ufe70*"), SV("{:*^3}"), SV("\ufe70")); // U+FE70 ARABIC FATHATAN ISOLATED FORM

	check(SV("*\uff01*"), SV("{:*^4}"), SV("\uff01")); // U+FF01 FULLWIDTH EXCLAMATION MARK
	check(SV("*\uff60*"), SV("{:*^4}"), SV("\uff60")); // FULLWIDTH RIGHT WHITE PARENTHESIS

	check(SV("*\uffe0*"), SV("{:*^4}"), SV("\uffe0")); // FULLWIDTH CENT SIGN
	check(SV("*\uffe6*"), SV("{:*^4}"), SV("\uffe6")); // FULLWIDTH WON SIGN

	//*** 4-byte code points ***
	check(SV("*\U00010000*"), SV("{:*^3}"), SV("\U00010000")); // LINEAR B SYLLABLE B008 A
	check(SV("*\U0010FFFF*"), SV("{:*^3}"), SV("\U0010FFFF")); // Undefined Character

	// 2 column ranges
	check(SV("*\U0001f300*"), SV("{:*^4}"), SV("\U0001f300")); // CYCLONE
	check(SV("*\U0001f64f*"), SV("{:*^4}"), SV("\U0001f64f")); // PERSON WITH FOLDED HANDS
	check(SV("*\U0001f900*"), SV("{:*^4}"), SV("\U0001f900")); // CIRCLED CROSS FORMEE WITH FOUR DOTS
	check(SV("*\U0001f9ff*"), SV("{:*^4}"), SV("\U0001f9ff")); // NAZAR AMULET
	check(SV("*\U00020000*"), SV("{:*^4}"), SV("\U00020000")); // <CJK Ideograph Extension B, First>
	check(SV("*\U0002fffd*"), SV("{:*^4}"), SV("\U0002fffd")); // Undefined Character
	check(SV("*\U00030000*"), SV("{:*^4}"), SV("\U00030000")); // <CJK Ideograph Extension G, First>
	check(SV("*\U0003fffd*"), SV("{:*^4}"), SV("\U0003fffd")); // Undefined Character
}

// One column output is unaffected.
// Two column output is removed, thus the result is only the fill character.
template <typename CharT, typename TestFunction>
static void test_single_code_point_truncate(TestFunction check)
{
	//*** 1-byte code points ***
	check(SV("* *"), SV("{:*^3.1}"), SV(" "));
	check(SV("*~*"), SV("{:*^3.1}"), SV("~"));

	//*** 2-byte code points ***
	check(SV("*\u00a1*"), SV("{:*^3.1}"), SV("\u00a1")); // INVERTED EXCLAMATION MARK
	check(SV("*\u07ff*"), SV("{:*^3.1}"), SV("\u07ff")); // NKO TAMAN SIGN

	//*** 3.1-byte code points ***
	check(SV("*\u0800*"), SV("{:*^3.1}"), SV("\u0800")); // SAMARITAN LETTER ALAF
	check(SV("*\ufffd*"), SV("{:*^3.1}"), SV("\ufffd")); // REPLACEMENT CHARACTER

	// 2 column ranges
	check(SV("***"), SV("{:*^3.1}"), SV("\u1100")); // HANGUL CHOSEONG KIYEOK
	check(SV("***"), SV("{:*^3.1}"), SV("\u115f")); // HANGUL CHOSEONG FILLER

	check(SV("***"), SV("{:*^3.1}"), SV("\u2329")); // LEFT-POINTING ANGLE BRACKET
	check(SV("***"), SV("{:*^3.1}"), SV("\u232a")); // RIGHT-POINTING ANGLE BRACKET

	check(SV("***"), SV("{:*^3.1}"), SV("\u2e80")); // CJK RADICAL REPEAT
	check(SV("***"), SV("{:*^3.1}"), SV("\u303e")); // IDEOGRAPHIC VARIATION INDICATOR

	check(SV("***"), SV("{:*^3.1}"), SV("\u3041")); // U+3041 HIRAGANA LETTER SMALL A
	check(SV("*\ua4d0*"), SV("{:*^3.1}"), SV("\ua4d0")); // U+A4D0 LISU LETTER BA

	check(SV("***"), SV("{:*^3.1}"), SV("\uac00")); // <Hangul Syllable, First>
	check(SV("***"), SV("{:*^3.1}"), SV("\ud7a3")); // Hangul Syllable Hih

	check(SV("***"), SV("{:*^3.1}"), SV("\uf900")); // CJK COMPATIBILITY IDEOGRAPH-F900
	check(SV("***"), SV("{:*^3.1}"), SV("\ufaff")); // U+FB00 LATIN SMALL LIGATURE FF

	check(SV("***"), SV("{:*^3.1}"), SV("\ufe10")); // PRESENTATION FORM FOR VERTICAL COMMA
	check(SV("***"), SV("{:*^3.1}"), SV("\ufe19")); // PRESENTATION FORM FOR VERTICAL HORIZONTAL ELLIPSIS

	check(SV("***"), SV("{:*^3.1}"), SV("\ufe30")); // PRESENTATION FORM FOR VERTICAL TWO DOT LEADER
	check(SV("*\ufe70*"), SV("{:*^3.1}"), SV("\ufe70")); // U+FE70 ARABIC FATHATAN ISOLATED FORM

	check(SV("***"), SV("{:*^3.1}"), SV("\uff01"));      // U+FF01 FULLWIDTH EXCLAMATION MARK
	check(SV("***"), SV("{:*^3.1}"), SV("\uff60")); // FULLWIDTH RIGHT WHITE PARENTHESIS

	check(SV("***"), SV("{:*^3.1}"), SV("\uffe0")); // FULLWIDTH CENT SIGN
	check(SV("***"), SV("{:*^3.1}"), SV("\uffe6")); // FULLWIDTH WON SIGN

	//*** 3.1-byte code points ***
	check(SV("*\U00010000*"), SV("{:*^3.1}"), SV("\U00010000")); // LINEAR B SYLLABLE B008 A
	check(SV("*\U0010FFFF*"), SV("{:*^3.1}"), SV("\U0010FFFF")); // Undefined Character

	// 2 column ranges
	check(SV("***"), SV("{:*^3.1}"), SV("\U0001f300")); // CYCLONE
	check(SV("***"), SV("{:*^3.1}"), SV("\U0001f64f")); // PERSON WITH FOLDED HANDS
	check(SV("***"), SV("{:*^3.1}"), SV("\U0001f900")); // CIRCLED CROSS FORMEE WITH FOUR DOTS
	check(SV("***"), SV("{:*^3.1}"), SV("\U0001f9ff")); // NAZAR AMULET
	check(SV("***"), SV("{:*^3.1}"), SV("\U00020000")); // <CJK Ideograph Extension B, First>
	check(SV("***"), SV("{:*^3.1}"), SV("\U0002fffd")); // Undefined Character
	check(SV("***"), SV("{:*^3.1}"), SV("\U00030000")); // <CJK Ideograph Extension G, First>
	check(SV("***"), SV("{:*^3.1}"), SV("\U0003fffd")); // Undefined Character
}

// The examples used in that paper.
template <typename CharT, typename TestFunction>
static void test_P1868(TestFunction check)
{
	// Fill
	check(SV("*\u0041*"), SV("{:*^3}"), SV("\u0041")); // { LATIN CAPITAL LETTER A }
	check(SV("*\u00c1*"), SV("{:*^3}"), SV("\u00c1")); // { LATIN CAPITAL LETTER A WITH ACUTE }
	check(SV("*\u0041\u0301*"), SV("{:*^3}"), SV("\u0041\u0301")); // { LATIN CAPITAL LETTER A } { COMBINING ACUTE ACCENT }
	check(SV("*\u0132*"), SV("{:*^3}"), SV("\u0132")); // { LATIN CAPITAL LIGATURE IJ }
	check(SV("*\u0394*"), SV("{:*^3}"), SV("\u0394")); // { GREEK CAPITAL LETTER DELTA }

	check(SV("*\u0429*"), SV("{:*^3}"), SV("\u0429"));         // { CYRILLIC CAPITAL LETTER SHCHA }
	check(SV("*\u05d0*"), SV("{:*^3}"), SV("\u05d0"));         // { HEBREW LETTER ALEF }
	check(SV("*\u0634*"), SV("{:*^3}"), SV("\u0634"));         // { ARABIC LETTER SHEEN }
	check(SV("*\u3009*"), SV("{:*^4}"), SV("\u3009"));         // { RIGHT-POINTING ANGLE BRACKET }
	check(SV("*\u754c*"), SV("{:*^4}"), SV("\u754c"));         // { CJK Unified Ideograph-754C }
	check(SV("*\U0001f921*"), SV("{:*^4}"), SV("\U0001f921")); // { UNICORN FACE }
	check(SV("*\U0001f468\u200d\U0001F469\u200d\U0001F467\u200d\U0001F466*"),
		SV("{:*^4}"),
		SV("\U0001f468\u200d\U0001F469\u200d\U0001F467\u200d\U0001F466")); // { Family: Man, Woman, Girl, Boy }

	// Truncate to 1 column: 1 column grapheme clusters are kept together.
	check(SV("*\u0041*"), SV("{:*^3.1}"), SV("\u0041")); // { LATIN CAPITAL LETTER A }
	check(SV("*\u00c1*"), SV("{:*^3.1}"), SV("\u00c1")); // { LATIN CAPITAL LETTER A WITH ACUTE }
	check(SV("*\u0041\u0301*"), SV("{:*^3.1}"), SV("\u0041\u0301"));  // { LATIN CAPITAL LETTER A } { COMBINING ACUTE ACCENT }
	check(SV("*\u0132*"), SV("{:*^3.1}"), SV("\u0132")); // { LATIN CAPITAL LIGATURE IJ }
	check(SV("*\u0394*"), SV("{:*^3.1}"), SV("\u0394")); // { GREEK CAPITAL LETTER DELTA }

	check(SV("*\u0429*"), SV("{:*^3.1}"), SV("\u0429")); // { CYRILLIC CAPITAL LETTER SHCHA }
	check(SV("*\u05d0*"), SV("{:*^3.1}"), SV("\u05d0")); // { HEBREW LETTER ALEF }
	check(SV("*\u0634*"), SV("{:*^3.1}"), SV("\u0634")); // { ARABIC LETTER SHEEN }
	check(SV("***"), SV("{:*^3.1}"), SV("\u3009"));      // { RIGHT-POINTING ANGLE BRACKET }
	check(SV("***"), SV("{:*^3.1}"), SV("\u754c"));      // { CJK Unified Ideograph-754C }
	check(SV("***"), SV("{:*^3.1}"), SV("\U0001f921"));  // { UNICORN FACE }
	check(SV("***"),
		SV("{:*^3.1}"),
		SV("\U0001f468\u200d\U0001F469\u200d\U0001F467\u200d\U0001F466")); // { Family: Man, Woman, Girl, Boy }

	// Truncate to 2 column: 2 column grapheme clusters are kept together.
	check(SV("*\u0041*"), SV("{:*^3.2}"), SV("\u0041")); // { LATIN CAPITAL LETTER A }
	check(SV("*\u00c1*"), SV("{:*^3.2}"), SV("\u00c1")); // { LATIN CAPITAL LETTER A WITH ACUTE }
	check(SV("*\u0041\u0301*"), SV("{:*^3.2}"), SV("\u0041\u0301"));  // { LATIN CAPITAL LETTER A } { COMBINING ACUTE ACCENT }
	check(SV("*\u0132*"), SV("{:*^3.2}"), SV("\u0132")); // { LATIN CAPITAL LIGATURE IJ }
	check(SV("*\u0394*"), SV("{:*^3.2}"), SV("\u0394")); // { GREEK CAPITAL LETTER DELTA }

	check(SV("*\u0429*"), SV("{:*^3.2}"), SV("\u0429"));         // { CYRILLIC CAPITAL LETTER SHCHA }
	check(SV("*\u05d0*"), SV("{:*^3.2}"), SV("\u05d0"));         // { HEBREW LETTER ALEF }
	check(SV("*\u0634*"), SV("{:*^3.2}"), SV("\u0634"));         // { ARABIC LETTER SHEEN }
	check(SV("*\u3009*"), SV("{:*^4.2}"), SV("\u3009"));         // { RIGHT-POINTING ANGLE BRACKET }
	check(SV("*\u754c*"), SV("{:*^4.2}"), SV("\u754c"));         // { CJK Unified Ideograph-754C }
	check(SV("*\U0001f921*"), SV("{:*^4.2}"), SV("\U0001f921")); // { UNICORN FACE }
	check(SV("*\U0001f468\u200d\U0001F469\u200d\U0001F467\u200d\U0001F466*"),
		SV("{:*^4.2}"),
		SV("\U0001f468\u200d\U0001F469\u200d\U0001F467\u200d\U0001F466")); // { Family: Man, Woman, Girl, Boy }
}

#ifdef _LIBCPP_VERSION
// Tests the libc++ specific behaviour for malformed UTF-sequences. The
// Standard doesn't specify how to handle this.
template <typename CharT, typename TestFunction>
static void test_malformed_code_point(TestFunction check)
{
	if constexpr (sizeof(CharT) == 1)
	{
		// Malformed at end.
		check(SV("*ZZZZ\x8f*"), SV("{:*^7}"), SV("ZZZZ\x8f"));
		check(SV("*ZZZZ\xcf*"), SV("{:*^7}"), SV("ZZZZ\xcf"));
		check(SV("*ZZZZ\xef*"), SV("{:*^7}"), SV("ZZZZ\xef"));
		check(SV("*ZZZZ\xff*"), SV("{:*^7}"), SV("ZZZZ\xff"));

		// Malformed in middle, no continuation
		check(SV("*ZZZZ\x8fZ*"), SV("{:*^8}"), SV("ZZZZ\x8fZ"));
		check(SV("*ZZZZ\xcfZ*"), SV("{:*^8}"), SV("ZZZZ\xcfZ"));
		check(SV("*ZZZZ\xefZ*"), SV("{:*^8}"), SV("ZZZZ\xefZ"));
		check(SV("*ZZZZ\xffZ*"), SV("{:*^8}"), SV("ZZZZ\xffZ"));

		check(SV("*ZZZZ\x8fZZ*"), SV("{:*^9}"), SV("ZZZZ\x8fZZ"));
		check(SV("*ZZZZ\xcfZZ*"), SV("{:*^9}"), SV("ZZZZ\xcfZZ"));
		check(SV("*ZZZZ\xefZZ*"), SV("{:*^9}"), SV("ZZZZ\xefZZ"));
		check(SV("*ZZZZ\xffZZ*"), SV("{:*^9}"), SV("ZZZZ\xffZZ"));

		check(SV("*ZZZZ\x8fZZZ*"), SV("{:*^10}"), SV("ZZZZ\x8fZZZ"));
		check(SV("*ZZZZ\xcfZZZ*"), SV("{:*^10}"), SV("ZZZZ\xcfZZZ"));
		check(SV("*ZZZZ\xefZZZ*"), SV("{:*^10}"), SV("ZZZZ\xefZZZ"));
		check(SV("*ZZZZ\xffZZZ*"), SV("{:*^10}"), SV("ZZZZ\xffZZZ"));

		check(SV("*ZZZZ\x8fZZZZ*"), SV("{:*^11}"), SV("ZZZZ\x8fZZZZ"));
		check(SV("*ZZZZ\xcfZZZZ*"), SV("{:*^11}"), SV("ZZZZ\xcfZZZZ"));
		check(SV("*ZZZZ\xefZZZZ*"), SV("{:*^11}"), SV("ZZZZ\xefZZZZ"));
		check(SV("*ZZZZ\xffZZZZ*"), SV("{:*^11}"), SV("ZZZZ\xffZZZZ"));

		// Invalid continuations
		check(SV("\xc2\x00"), SV("{}"), SV("\xc2\x00"));
		check(SV("\xc2\x40"), SV("{}"), SV("\xc2\x40"));
		check(SV("\xc2\xc0"), SV("{}"), SV("\xc2\xc0"));

		check(SV("\xe0\x00\x80"), SV("{}"), SV("\xe0\x00\x80"));
		check(SV("\xe0\x40\x80"), SV("{}"), SV("\xe0\x40\x80"));
		check(SV("\xe0\xc0\x80"), SV("{}"), SV("\xe0\xc0\x80"));

		check(SV("\xe0\x80\x00"), SV("{}"), SV("\xe0\x80\x00"));
		check(SV("\xe0\x80\x40"), SV("{}"), SV("\xe0\x80\x40"));
		check(SV("\xe0\x80\xc0"), SV("{}"), SV("\xe0\x80\xc0"));

		check(SV("\xf0\x80\x80\x00"), SV("{}"), SV("\xf0\x80\x80\x00"));
		check(SV("\xf0\x80\x80\x40"), SV("{}"), SV("\xf0\x80\x80\x40"));
		check(SV("\xf0\x80\x80\xc0"), SV("{}"), SV("\xf0\x80\x80\xc0"));

		check(SV("\xf0\x80\x00\x80"), SV("{}"), SV("\xf0\x80\x00\x80"));
		check(SV("\xf0\x80\x40\x80"), SV("{}"), SV("\xf0\x80\x40\x80"));
		check(SV("\xf0\x80\xc0\x80"), SV("{}"), SV("\xf0\x80\xc0\x80"));

		check(SV("\xf0\x00\x80\x80"), SV("{}"), SV("\xf0\x00\x80\x80"));
		check(SV("\xf0\x40\x80\x80"), SV("{}"), SV("\xf0\x40\x80\x80"));
		check(SV("\xf0\xc0\x80\x80"), SV("{}"), SV("\xf0\xc0\x80\x80"));

		// Premature end.
		check(SV("*ZZZZ\xef\xf5*"), SV("{:*^8}"), SV("ZZZZ\xef\xf5"));
		check(SV("*ZZZZ\xef\xf5ZZZZ*"), SV("{:*^12}"), SV("ZZZZ\xef\xf5ZZZZ"));
		check(SV("*ZZZZ\xff\xf5\xf5*"), SV("{:*^9}"), SV("ZZZZ\xff\xf5\xf5"));
		check(SV("*ZZZZ\xff\xf5\xf5ZZZZ*"), SV("{:*^13}"), SV("ZZZZ\xff\xf5\xf5ZZZZ"));

	}
	else if constexpr (sizeof(CharT) == 2)
	{
		// TODO FMT Add these tests.
	}
	// UTF-32 doesn't combine characters, thus no corruption tests.
}
#endif

HAMON_WARNING_PUSH()

}	// namespace unicode_test

template <class CharT, class TestFunction>
void test_unicode(TestFunction check)
{
	unicode_test::test_single_code_point_fill<CharT>(check);
	unicode_test::test_single_code_point_truncate<CharT>(check);
	unicode_test::test_P1868<CharT>(check);

#ifdef _LIBCPP_VERSION
	unicode_test::test_malformed_code_point<CharT>(check);
#endif
}

}	// namespace hamon_format_test

#undef SV

#endif // HAMON_FORMAT_TEST_UNICODE_HPP
