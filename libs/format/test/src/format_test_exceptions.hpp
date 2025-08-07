/**
 *	@file	format_test_exceptions.hpp
 *
 *	@brief
 */

#ifndef HAMON_FORMAT_TEST_EXCEPTIONS_HPP
#define HAMON_FORMAT_TEST_EXCEPTIONS_HPP

#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/concepts.hpp>
#include <hamon/detail/statically_widen.hpp>
#include <hamon/limits.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include "format_test_helper.hpp"

#define SV(Str)		hamon::basic_string_view<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str), sizeof(Str) - 1)

namespace hamon_format_test
{

namespace exceptions_test
{

template <typename CharT, typename ExceptionTest>
void test_char(ExceptionTest check_exception)
{
	// *** Sign ***
	check_exception(SV("{:-}"), CharT('*'));
	check_exception(SV("{:+}"), CharT('*'));
	check_exception(SV("{: }"), CharT('*'));

	check_exception(SV("{:-c}"), CharT('*'));
	check_exception(SV("{:+c}"), CharT('*'));
	check_exception(SV("{: c}"), CharT('*'));

	// *** alternate form ***
	check_exception(SV("{:#}"), CharT('*'));
	check_exception(SV("{:#c}"), CharT('*'));

	// *** zero-padding ***
	check_exception(SV("{:0}"), CharT('*'));
	check_exception(SV("{:0c}"), CharT('*'));

	// *** precision ***
	check_exception(SV("{:.}"), CharT('*'));
	check_exception(SV("{:.0}"), CharT('*'));
	check_exception(SV("{:.42}"), CharT('*'));

	check_exception(SV("{:.c}"), CharT('*'));
	check_exception(SV("{:.0c}"), CharT('*'));
	check_exception(SV("{:.42c}"), CharT('*'));

	check_exception(SV("{:.d}"), CharT('*'));
	check_exception(SV("{:.0d}"), CharT('*'));
	check_exception(SV("{:.42d}"), CharT('*'));

	// *** type ***
	check_exception(true,  SV("{:a}"), CharT('*'));
	check_exception(true,  SV("{:A}"), CharT('*'));
	check_exception(false, SV("{:b}"), CharT('*'));
	check_exception(false, SV("{:B}"), CharT('*'));
	check_exception(false, SV("{:c}"), CharT('*'));
	check_exception(false, SV("{:d}"), CharT('*'));
	check_exception(true,  SV("{:e}"), CharT('*'));
	check_exception(true,  SV("{:E}"), CharT('*'));
	check_exception(true,  SV("{:f}"), CharT('*'));
	check_exception(true,  SV("{:F}"), CharT('*'));
	check_exception(true,  SV("{:g}"), CharT('*'));
	check_exception(true,  SV("{:G}"), CharT('*'));
	check_exception(false, SV("{:o}"), CharT('*'));
	check_exception(true,  SV("{:p}"), CharT('*'));
	check_exception(true,  SV("{:P}"), CharT('*'));
	check_exception(true,  SV("{:s}"), CharT('*'));
	check_exception(false, SV("{:x}"), CharT('*'));
	check_exception(false, SV("{:X}"), CharT('*'));
	check_exception(false, SV("{:?}"), CharT('*'));
}

template <typename CharT, typename ExceptionTest, typename W, typename U>
void test_string_impl(ExceptionTest check_exception, const W& world, const U& universe)
{
	// *** sign ***
	check_exception(SV("hello {:-}"), world);

	// *** alternate form ***
	check_exception(SV("hello {:#}"), world);

	// *** zero-padding ***
	check_exception(SV("hello {:0}"), world);

	// *** width ***
	check_exception(SV("hello {:{}}"), world, -1);
	check_exception(SV("hello {:{}}"), world, unsigned(-1));
	check_exception(SV("hello {:{}}"), world);
	check_exception(SV("hello {:{}}"), world, universe);
	check_exception(SV("hello {:{0}}"), world, 1);
	check_exception(SV("hello {0:{}}"), world, 1);
	// Arg-id may not have leading zeros.
	check_exception(SV("hello {0:{01}}"), world, 1);

	// *** precision ***
	check_exception(SV("hello {:.{}}"), world, -1);
	check_exception(SV("hello {:.{}}"), world, ~0u);
	check_exception(SV("hello {:.{}}"), world);
	check_exception(SV("hello {:.{}}"), world, universe);
	check_exception(SV("hello {:.{0}}"), world, 1);
	check_exception(SV("hello {0:.{}}"), world, 1);
	// Arg-id may not have leading zeros.
	check_exception(SV("hello {0:.{01}}"), world, 1);

	// *** locale-specific form ***
	check_exception(SV("hello {:L}"), world);

	// *** type ***
	check_exception(true,  SV("{:a}"), world);
	check_exception(true,  SV("{:A}"), world);
	check_exception(true,  SV("{:b}"), world);
	check_exception(true,  SV("{:B}"), world);
	check_exception(true,  SV("{:c}"), world);
	check_exception(true,  SV("{:d}"), world);
	check_exception(true,  SV("{:e}"), world);
	check_exception(true,  SV("{:E}"), world);
	check_exception(true,  SV("{:f}"), world);
	check_exception(true,  SV("{:F}"), world);
	check_exception(true,  SV("{:g}"), world);
	check_exception(true,  SV("{:G}"), world);
	check_exception(true,  SV("{:o}"), world);
	check_exception(true,  SV("{:p}"), world);
	check_exception(true,  SV("{:P}"), world);
	check_exception(false, SV("{:s}"), world);
	check_exception(true,  SV("{:x}"), world);
	check_exception(true,  SV("{:X}"), world);
	check_exception(false, SV("{:?}"), world);
}

template <typename CharT, typename ExceptionTest>
void test_string(ExceptionTest check_exception)
{
	CharT world[] = { CharT('w'), CharT('o'), CharT('r'), CharT('l'), CharT('d'), 0 };
	CharT universe[] = { CharT('u'), CharT('n'), CharT('i'), CharT('v'), CharT('e'), CharT('r'), CharT('s'), CharT('e'), 0 };

	test_string_impl<CharT>(check_exception, world, universe);
	test_string_impl<CharT>(check_exception, static_cast<CharT*>(world), static_cast<CharT*>(universe));
	test_string_impl<CharT>(check_exception, static_cast<CharT const*>(world), static_cast<CharT const*>(universe));
	test_string_impl<CharT>(check_exception, hamon::basic_string<CharT>(world), hamon::basic_string<CharT>(universe));
	test_string_impl<CharT>(check_exception, hamon::basic_string_view<CharT>(world), hamon::basic_string_view<CharT>(universe));
}

template <typename CharT, typename ExceptionTest>
void test_bool(ExceptionTest check_exception)
{
	// *** Sign ***
	check_exception(SV("{:-}"), true);
	check_exception(SV("{:+}"), true);
	check_exception(SV("{: }"), true);

	check_exception(SV("{:-s}"), true);
	check_exception(SV("{:+s}"), true);
	check_exception(SV("{: s}"), true);

	// *** alternate form ***
	check_exception(SV("{:#}"), true);
	check_exception(SV("{:#s}"), true);

	// *** zero-padding ***
	check_exception(SV("{:0}"), true);
	check_exception(SV("{:0s}"), true);

	// *** precision ***
	check_exception(SV("{:.}"), true);
	check_exception(SV("{:.0}"), true);
	check_exception(SV("{:.42}"), true);

	check_exception(SV("{:.s}"), true);
	check_exception(SV("{:.0s}"), true);
	check_exception(SV("{:.42s}"), true);

	// *** type ***
	check_exception(true,  SV("{:a}"), true);
	check_exception(true,  SV("{:A}"), true);
	check_exception(false, SV("{:b}"), true);
	check_exception(false, SV("{:B}"), true);
	check_exception(true,  SV("{:c}"), true);
	check_exception(false, SV("{:d}"), true);
	check_exception(true,  SV("{:e}"), true);
	check_exception(true,  SV("{:E}"), true);
	check_exception(true,  SV("{:f}"), true);
	check_exception(true,  SV("{:F}"), true);
	check_exception(true,  SV("{:g}"), true);
	check_exception(true,  SV("{:G}"), true);
	check_exception(false, SV("{:o}"), true);
	check_exception(true,  SV("{:p}"), true);
	check_exception(true,  SV("{:P}"), true);
	check_exception(false, SV("{:s}"), true);
	check_exception(false, SV("{:x}"), true);
	check_exception(false, SV("{:X}"), true);
	check_exception(true,  SV("{:?}"), true);
}

template <typename CharT, typename I, typename ExceptionTest>
void test_integer_as_integer(ExceptionTest check_exception)
{
	// *** Width ***
	check_exception(SV("{:{}}"), I(42), true);
	check_exception(SV("{:{}}"), I(42), CharT('0'));
	check_exception(SV("{:{}}"), I(42), 42.0f);
	check_exception(SV("{:{}}"), I(42), 42.0);
	check_exception(SV("{:{}}"), I(42), 42.0l);

	// *** precision ***
	check_exception(SV("{:.}"),   I(0));
	check_exception(SV("{:.0}"),  I(0));
	check_exception(SV("{:.42}"), I(0));

	check_exception(SV("{:.{}}"), I(0));
	check_exception(SV("{:.{}}"), I(0), true);
	check_exception(SV("{:.{}}"), I(0), 1.0);

	// *** type ***
	check_exception(true,  SV("{:a}"), I(0));
	check_exception(true,  SV("{:A}"), I(0));
	check_exception(false, SV("{:b}"), I(0));
	check_exception(false, SV("{:B}"), I(0));
	check_exception(false, SV("{:c}"), I(0));
	check_exception(false, SV("{:d}"), I(0));
	check_exception(true,  SV("{:e}"), I(0));
	check_exception(true,  SV("{:E}"), I(0));
	check_exception(true,  SV("{:f}"), I(0));
	check_exception(true,  SV("{:F}"), I(0));
	check_exception(true,  SV("{:g}"), I(0));
	check_exception(true,  SV("{:G}"), I(0));
	check_exception(false, SV("{:o}"), I(0));
	check_exception(true,  SV("{:p}"), I(0));
	check_exception(true,  SV("{:P}"), I(0));
	check_exception(true,  SV("{:s}"), I(0));
	check_exception(false, SV("{:x}"), I(0));
	check_exception(false, SV("{:X}"), I(0));
	check_exception(true,  SV("{:?}"), I(0));
}

template <typename CharT, typename I, typename ExceptionTest>
void test_integer_as_char(ExceptionTest check_exception)
{
	// *** Sign ***
	check_exception(SV("answer is {:-c}"), I(42));
	check_exception(SV("answer is {:+c}"), I(42));
	check_exception(SV("answer is {: c}"), I(42));

	// *** alternate form ***
	check_exception(SV("answer is {:#c}"), I(42));

	// *** zero-padding & width ***
	check_exception(SV("answer is {:01c}"), I(42));

	// *** precision ***
	check_exception(SV("{:.c}"),   I(0));
	check_exception(SV("{:.0c}"),  I(0));
	check_exception(SV("{:.42c}"), I(0));

	check_exception(SV("{:.{}c}"), I(0));
	check_exception(SV("{:.{}c}"), I(0), true);
	check_exception(SV("{:.{}c}"), I(0), 1.0);

	// *** Validate range ***
	// The code has some duplications to keep the if statement readable.
	if constexpr (hamon::signed_integral<CharT>)
	{
		if constexpr (hamon::signed_integral<I> && sizeof(I) > sizeof(CharT))
		{
			check_exception(SV("{:c}"), hamon::numeric_limits<I>::min());
			check_exception(SV("{:c}"), hamon::numeric_limits<I>::max());
		}
		else if constexpr (hamon::unsigned_integral<I> && sizeof(I) >= sizeof(CharT))
		{
			check_exception(SV("{:c}"), hamon::numeric_limits<I>::max());
		}
	}
	else if constexpr (sizeof(I) > sizeof(CharT))
	{
		check_exception(SV("{:c}"), hamon::numeric_limits<I>::max());
	}
}

template <typename CharT, typename ExceptionTest>
void test_integer(ExceptionTest check_exception)
{
	test_integer_as_integer<CharT, signed char>(check_exception);
	test_integer_as_integer<CharT, signed short>(check_exception);
	test_integer_as_integer<CharT, signed int>(check_exception);
	test_integer_as_integer<CharT, signed long>(check_exception);
	test_integer_as_integer<CharT, signed long long>(check_exception);

	test_integer_as_integer<CharT, unsigned char>(check_exception);
	test_integer_as_integer<CharT, unsigned short>(check_exception);
	test_integer_as_integer<CharT, unsigned int>(check_exception);
	test_integer_as_integer<CharT, unsigned long>(check_exception);
	test_integer_as_integer<CharT, unsigned long long>(check_exception);

	test_integer_as_char<CharT, signed char>(check_exception);
	test_integer_as_char<CharT, signed short>(check_exception);
	test_integer_as_char<CharT, signed int>(check_exception);
	test_integer_as_char<CharT, signed long>(check_exception);
	test_integer_as_char<CharT, signed long long>(check_exception);

	test_integer_as_char<CharT, unsigned char>(check_exception);
	test_integer_as_char<CharT, unsigned short>(check_exception);
	test_integer_as_char<CharT, unsigned int>(check_exception);
	test_integer_as_char<CharT, unsigned long>(check_exception);
	test_integer_as_char<CharT, unsigned long long>(check_exception);
}

template <typename CharT, typename F, typename ExceptionTest>
void test_floating_point_impl(ExceptionTest check_exception)
{
	// *** Precision ***
	check_exception(SV("{:0.{}}"), F(42.0), true);
	check_exception(SV("{:0.{}}"), F(42.0), CharT('0'));
	check_exception(SV("{:0.{}}"), F(42.0), 42.0f);
	check_exception(SV("{:0.{}}"), F(42.0), 42.0);
	check_exception(SV("{:0.{}}"), F(42.0), 42.0l);

	// *** type ***
	check_exception(false, SV("{:a}"), F(1));
	check_exception(false, SV("{:A}"), F(1));
	check_exception(true,  SV("{:b}"), F(1));
	check_exception(true,  SV("{:B}"), F(1));
	check_exception(true,  SV("{:c}"), F(1));
	check_exception(true,  SV("{:d}"), F(1));
	check_exception(false, SV("{:e}"), F(1));
	check_exception(false, SV("{:E}"), F(1));
	check_exception(false, SV("{:f}"), F(1));
	check_exception(false, SV("{:F}"), F(1));
	check_exception(false, SV("{:g}"), F(1));
	check_exception(false, SV("{:G}"), F(1));
	check_exception(true,  SV("{:o}"), F(1));
	check_exception(true,  SV("{:p}"), F(1));
	check_exception(true,  SV("{:P}"), F(1));
	check_exception(true,  SV("{:s}"), F(1));
	check_exception(true,  SV("{:x}"), F(1));
	check_exception(true,  SV("{:X}"), F(1));
	check_exception(true,  SV("{:?}"), F(1));
}

template <typename CharT, typename ExceptionTest>
void test_floating_point(ExceptionTest check_exception)
{
	test_floating_point_impl<CharT, float>(check_exception);
	test_floating_point_impl<CharT, double>(check_exception);
	test_floating_point_impl<CharT, long double>(check_exception);
}

template <typename CharT, typename P, typename ExceptionTest>
void test_pointer_impl(ExceptionTest check_exception)
{
	// *** Sign ***
	check_exception(SV("{:-}"), P(nullptr));
	check_exception(SV("{:+}"), P(nullptr));
	check_exception(SV("{: }"), P(nullptr));

	// *** alternate form ***
	check_exception(SV("{:#}"), P(nullptr));

	// *** precision ***
	check_exception(SV("{:.}"),   P(nullptr));
	check_exception(SV("{:.0}"),  P(nullptr));
	check_exception(SV("{:.42}"), P(nullptr));

	check_exception(SV("{:.{}}"), P(nullptr));
	check_exception(SV("{:.{}}"), P(nullptr), true);
	check_exception(SV("{:.{}}"), P(nullptr), 1.0);

	// *** locale-specific form ***
	check_exception(SV("{:L}"), P(nullptr));

	// *** type ***
	check_exception(true,  SV("{:a}"), P(nullptr));
	check_exception(true,  SV("{:A}"), P(nullptr));
	check_exception(true,  SV("{:b}"), P(nullptr));
	check_exception(true,  SV("{:B}"), P(nullptr));
	check_exception(true,  SV("{:c}"), P(nullptr));
	check_exception(true,  SV("{:d}"), P(nullptr));
	check_exception(true,  SV("{:e}"), P(nullptr));
	check_exception(true,  SV("{:E}"), P(nullptr));
	check_exception(true,  SV("{:f}"), P(nullptr));
	check_exception(true,  SV("{:F}"), P(nullptr));
	check_exception(true,  SV("{:g}"), P(nullptr));
	check_exception(true,  SV("{:G}"), P(nullptr));
	check_exception(true,  SV("{:o}"), P(nullptr));
	check_exception(false, SV("{:p}"), P(nullptr));
	check_exception(false, SV("{:P}"), P(nullptr));
	check_exception(true,  SV("{:s}"), P(nullptr));
	check_exception(true,  SV("{:x}"), P(nullptr));
	check_exception(true,  SV("{:X}"), P(nullptr));
	check_exception(true,  SV("{:?}"), P(nullptr));
}

template <typename CharT, typename ExceptionTest>
void test_pointer(ExceptionTest check_exception)
{
	test_pointer_impl<CharT, hamon::nullptr_t>(check_exception);
	test_pointer_impl<CharT, void*>(check_exception);
	test_pointer_impl<CharT, const void*>(check_exception);
}

template <typename CharT, typename ExceptionTest>
void test_handle(ExceptionTest check_exception)
{
	// *** type ***
	check_exception(true,  SV("{:a}"), status::foo);
	check_exception(true,  SV("{:A}"), status::foo);
	check_exception(true,  SV("{:b}"), status::foo);
	check_exception(true,  SV("{:B}"), status::foo);
	check_exception(true,  SV("{:c}"), status::foo);
	check_exception(true,  SV("{:d}"), status::foo);
	check_exception(true,  SV("{:e}"), status::foo);
	check_exception(true,  SV("{:E}"), status::foo);
	check_exception(true,  SV("{:f}"), status::foo);
	check_exception(true,  SV("{:F}"), status::foo);
	check_exception(true,  SV("{:g}"), status::foo);
	check_exception(true,  SV("{:G}"), status::foo);
	check_exception(true,  SV("{:o}"), status::foo);
	check_exception(true,  SV("{:p}"), status::foo);
	check_exception(true,  SV("{:P}"), status::foo);
	check_exception(false, SV("{:s}"), status::foo);
	check_exception(false, SV("{:x}"), status::foo);
	check_exception(false, SV("{:X}"), status::foo);
	check_exception(true,  SV("{:?}"), status::foo);
}

}	// namespace exceptions_test

template <typename CharT, typename ExceptionTest>
void test_exceptions(ExceptionTest check_exception)
{
	// *** Test invalid format strings ***
	check_exception(SV("{"));
	check_exception(SV("{:"));
	check_exception(SV("{:"), 42);

	check_exception(SV("{0"));
	check_exception(SV("{0:"));
	check_exception(SV("{0:"), 42);

	check_exception(SV("}"));
	check_exception(SV("{:}-}"), 42);

	check_exception(SV("} "));
	check_exception(SV("{-"), 42);
	check_exception(SV("hello {}"));
	check_exception(SV("hello {0}"));
	check_exception(SV("hello {1}"), 42);

	exceptions_test::test_char<CharT>(check_exception);
	exceptions_test::test_string<CharT>(check_exception);
	exceptions_test::test_bool<CharT>(check_exception);
	exceptions_test::test_integer<CharT>(check_exception);
	exceptions_test::test_floating_point<CharT>(check_exception);
	exceptions_test::test_pointer<CharT>(check_exception);
	exceptions_test::test_handle<CharT>(check_exception);
}

}	// namespace hamon_format_test

#undef SV

#endif // HAMON_FORMAT_TEST_EXCEPTIONS_HPP
