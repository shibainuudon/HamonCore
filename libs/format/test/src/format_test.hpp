/**
 *	@file	format_test.hpp
 *
 *	@brief
 */

#ifndef HAMON_FORMAT_TEST_HPP
#define HAMON_FORMAT_TEST_HPP

#include <hamon/concepts/same_as.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/detail/statically_widen.hpp>
#include <hamon/limits.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include "format_test_helper.hpp"

namespace hamon_format_test
{

#define SV(Str)		hamon::basic_string_view<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str))
#define STR(Str)	hamon::basic_string<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str))

template <typename CharT, typename TestFunction>
void test_partial(TestFunction check)
{
	// *** Test escaping  ***
	check(SV("{"), SV("{{"));
	check(SV("}"), SV("}}"));
	check(SV("{:^}"), SV("{{:^}}"));
	check(SV("{: ^}"), SV("{{:{}^}}"), CharT(' '));
	check(SV("{:{}^}"), SV("{{:{{}}^}}"));
	check(SV("{:{ }^}"), SV("{{:{{{}}}^}}"), CharT(' '));

	// *** Test argument ID ***
	check(SV("hello false true"), SV("hello {0:} {1:}"), false, true);
	check(SV("hello true false"), SV("hello {1:} {0:}"), false, true);

	// *** Test many arguments ***

	// [format.args]/1
	// An instance of basic_format_args provides access to formatting arguments.
	// Implementations should optimize the representation of basic_format_args
	// for a small number of formatting arguments.
	//
	// These's no guidances what "a small number of formatting arguments" is.
	// - fmtlib uses a 15 elements
	// - libc++ uses 12 elements
	// - MSVC STL uses a different approach regardless of the number of arguments
	// - libstdc++ has no implementation yet
	// fmtlib and libc++ use a similar approach, this approach can support 16
	// elements (based on design choices both support less elements). This test
	// makes sure "the large number of formatting arguments" code path is tested.
	check(
		SV("1234567890\t1234567890"),
		SV("{}{}{}{}{}{}{}{}{}{}\t{}{}{}{}{}{}{}{}{}{}"),
		1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0);

	// *** Test char format argument ***
	// The `char` to `wchar_t` formatting is tested separately.
	check(SV("hello 09azAZ!"),
		SV("hello {}{}{}{}{}{}{}"),
		CharT('0'),
		CharT('9'),
		CharT('a'),
		CharT('z'),
		CharT('A'),
		CharT('Z'),
		CharT('!'));

	// *** Test string format argument ***
	{
		CharT buffer[] = { CharT('0'), CharT('9'), CharT('a'), CharT('z'), CharT('A'), CharT('Z'), CharT('!'), 0 };
		CharT* data = buffer;
		check(SV("hello 09azAZ!"), SV("hello {}"), data);
	}
	{
		CharT buffer[] = { CharT('0'), CharT('9'), CharT('a'), CharT('z'), CharT('A'), CharT('Z'), CharT('!'), 0 };
		const CharT* data = buffer;
		check(SV("hello 09azAZ!"), SV("hello {}"), data);
	}
	{
		// https://github.com/llvm/llvm-project/issues/115935
		// Contents after the embedded null character are discarded.
		CharT buffer[] = { CharT('a'), CharT('b'), CharT('c'), 0, CharT('d'), CharT('e'), CharT('f'), 0 };
		check(SV("hello abc"), SV("hello {}"), buffer);
		// Even when the last element of the array is not null character.
		CharT buffer2[] = { CharT('a'), CharT('b'), CharT('c'), 0, CharT('d'), CharT('e'), CharT('f') };
		check(SV("hello abc"), SV("hello {}"), buffer2);
	}
	{
		hamon::basic_string<CharT> data = STR("world");
		check(SV("hello world"), SV("hello {}"), data);
	}
	{
		hamon::basic_string<CharT> buffer = STR("world");
		hamon::basic_string_view<CharT> data = buffer;
		check(SV("hello world"), SV("hello {}"), data);
	}

	// *** Test Boolean format argument ***
	check(SV("hello false true"), SV("hello {} {}"), false, true);

	// *** Test signed integral format argument ***
	check(SV("hello 42"), SV("hello {}"), static_cast<signed char>(42));
	check(SV("hello 42"), SV("hello {}"), static_cast<short>(42));
	check(SV("hello 42"), SV("hello {}"), static_cast<int>(42));
	check(SV("hello 42"), SV("hello {}"), static_cast<long>(42));
	check(SV("hello 42"), SV("hello {}"), static_cast<long long>(42));

	// ** Test unsigned integral format argument ***
	check(SV("hello 42"), SV("hello {}"), static_cast<unsigned char>(42));
	check(SV("hello 42"), SV("hello {}"), static_cast<unsigned short>(42));
	check(SV("hello 42"), SV("hello {}"), static_cast<unsigned>(42));
	check(SV("hello 42"), SV("hello {}"), static_cast<unsigned long>(42));
	check(SV("hello 42"), SV("hello {}"), static_cast<unsigned long long>(42));

	// *** Test floating point format argument ***
	check(SV("hello 42"), SV("hello {}"), static_cast<float>(42));
	check(SV("hello 42"), SV("hello {}"), static_cast<double>(42));
	check(SV("hello 42"), SV("hello {}"), static_cast<long double>(42));

	// *** Test pointer formatter argument ***
	check(SV("hello 0x0"), SV("hello {}"), nullptr);
	check(SV("hello 0x42"), SV("hello {}"), reinterpret_cast<void*>(0x42));
	check(SV("hello 0x42"), SV("hello {}"), reinterpret_cast<const void*>(0x42));

	// *** Test handle formatter argument ***
	// *** Valid permutations ***
	check(SV("answer is '0xaaaa'"), SV("answer is '{}'"), status::foo);
	check(SV("answer is '0xaaaa'"), SV("answer is '{:x}'"), status::foo);
	check(SV("answer is '0XAAAA'"), SV("answer is '{:X}'"), status::foo);
	check(SV("answer is 'foo'"), SV("answer is '{:s}'"), status::foo);

	check(SV("answer is '0x5555'"), SV("answer is '{}'"), status::bar);
	check(SV("answer is '0x5555'"), SV("answer is '{:x}'"), status::bar);
	check(SV("answer is '0X5555'"), SV("answer is '{:X}'"), status::bar);
	check(SV("answer is 'bar'"), SV("answer is '{:s}'"), status::bar);

	check(SV("answer is '0xaa55'"), SV("answer is '{}'"), status::foobar);
	check(SV("answer is '0xaa55'"), SV("answer is '{:x}'"), status::foobar);
	check(SV("answer is '0XAA55'"), SV("answer is '{:X}'"), status::foobar);
	check(SV("answer is 'foobar'"), SV("answer is '{:s}'"), status::foobar);

	// P2418 Changed the argument from a const reference to a forwarding reference.
	// This mainly affects handle classes, however since we use an abstraction
	// layer here it's "tricky" to verify whether this test would do the "right"
	// thing. So these tests are done separately.
}

namespace detail
{

template <typename CharT, typename TestFunction>
void test_buffer_copy(TestFunction check)
{
	// *** copy ***
	check(SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"),
		SV("{}"),
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"));

	check(SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"),
		SV("{}"),
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"));

	check(SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"),
		SV("{}"),
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"));

	check(SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"),
		SV("{}"),
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"));

	check(
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"),
		SV("{}"),
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"));

	// *** copy + push_back ***

	check(SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"X"),
		SV("{}X"),
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"));

	check(SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"X"),
		SV("{}X"),
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"));

	check(SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"X"),
		SV("{}X"),
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"));

	check(SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"X"),
		SV("{}X"),
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"));

	check(
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"X"),
		SV("{}X"),
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"));

	// ***  push_back + copy ***

	check(SV("X"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"),
		SV("X{}"),
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"));

	check(SV("X"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"),
		SV("X{}"),
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"));

	check(SV("X"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"),
		SV("X{}"),
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"));

	check(SV("X"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"),
		SV("X{}"),
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"));

	check(
		SV("X"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"),
		SV("X{}"),
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"));
}

template <typename CharT, typename TestFunction>
void test_buffer_fill(TestFunction check)
{
	// *** fill ***
	check(SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"), SV("{:|<64}"), SV(""));

	check(SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"),
		SV("{:|<128}"),
		SV(""));

	check(SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"),
		SV("{:|<256}"),
		SV(""));

	check(SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"),
		SV("{:|<512}"),
		SV(""));

	check(SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"),
		SV("{:|<1024}"),
		SV(""));

	// *** fill + push_back ***

	check(SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"X"),
		SV("{:|<64}X"),
		SV(""));

	check(SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"X"),
		SV("{:|<128}X"),
		SV(""));

	check(SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"X"),
		SV("{:|<256}X"),
		SV(""));

	check(SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"X"),
		SV("{:|<512}X"),
		SV(""));

	check(SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"X"),
		SV("{:|<1024}X"),
		SV(""));

	// *** push_back + fill ***

	check(SV("X"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"),
		SV("X{:|<64}"),
		SV(""));

	check(SV("X"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"),
		SV("X{:|<128}"),
		SV(""));

	check(SV("X"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"),
		SV("X{:|<256}"),
		SV(""));

	check(SV("X"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"),
		SV("X{:|<512}"),
		SV(""));

	check(SV("X"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"),
		SV("X{:|<1024}"),
		SV(""));
}

template <typename CharT, typename TestFunction>
void test_char(TestFunction check)
{
	// ***** Char type *****
	// *** align-fill & width ***
	check(SV("answer is '*     '"), SV("answer is '{:6}'"), CharT('*'));
	check(SV("answer is '     *'"), SV("answer is '{:>6}'"), CharT('*'));
	check(SV("answer is '*     '"), SV("answer is '{:<6}'"), CharT('*'));
	check(SV("answer is '  *   '"), SV("answer is '{:^6}'"), CharT('*'));

	check(SV("answer is '*     '"), SV("answer is '{:6c}'"), CharT('*'));
	check(SV("answer is '     *'"), SV("answer is '{:>6c}'"), CharT('*'));
	check(SV("answer is '*     '"), SV("answer is '{:<6c}'"), CharT('*'));
	check(SV("answer is '  *   '"), SV("answer is '{:^6c}'"), CharT('*'));

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	check(SV("answer is ':::::*'"), SV("answer is '{::>6}'"), CharT('*'));
	check(SV("answer is '*:::::'"), SV("answer is '{::<6}'"), CharT('*'));
	check(SV("answer is '::*:::'"), SV("answer is '{::^6}'"), CharT('*'));

	check(SV("answer is '-----*'"), SV("answer is '{:->6c}'"), CharT('*'));
	check(SV("answer is '*-----'"), SV("answer is '{:-<6c}'"), CharT('*'));
	check(SV("answer is '--*---'"), SV("answer is '{:-^6c}'"), CharT('*'));

	// *** locale-specific form ***
	// Note it has no effect but it's allowed.
	check(SV("answer is '*'"), SV("answer is '{:L}'"), '*');
	check(SV("answer is '*'"), SV("answer is '{:Lc}'"), '*');
}

template <typename CharT, typename TestFunction>
void test_char_as_integer(TestFunction check)
{
	// *** align-fill & width ***
	check(SV("answer is '42'"), SV("answer is '{:<1d}'"), CharT('*'));

	check(SV("answer is '42'"), SV("answer is '{:<2d}'"), CharT('*'));
	check(SV("answer is '42 '"), SV("answer is '{:<3d}'"), CharT('*'));

	check(SV("answer is '     42'"), SV("answer is '{:7d}'"), CharT('*'));
	check(SV("answer is '     42'"), SV("answer is '{:>7d}'"), CharT('*'));
	check(SV("answer is '42     '"), SV("answer is '{:<7d}'"), CharT('*'));
	check(SV("answer is '  42   '"), SV("answer is '{:^7d}'"), CharT('*'));

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	check(SV("answer is ':::::42'"), SV("answer is '{::>7d}'"), CharT('*'));
	check(SV("answer is '42:::::'"), SV("answer is '{::<7d}'"), CharT('*'));
	check(SV("answer is '::42:::'"), SV("answer is '{::^7d}'"), CharT('*'));

	// Test whether zero padding is ignored
	check(SV("answer is '     42'"), SV("answer is '{:>07d}'"), CharT('*'));
	check(SV("answer is '42     '"), SV("answer is '{:<07d}'"), CharT('*'));
	check(SV("answer is '  42   '"), SV("answer is '{:^07d}'"), CharT('*'));

	// *** Sign ***
	check(SV("answer is 42"), SV("answer is {:d}"), CharT('*'));
	check(SV("answer is 42"), SV("answer is {:-d}"), CharT('*'));
	check(SV("answer is +42"), SV("answer is {:+d}"), CharT('*'));
	check(SV("answer is  42"), SV("answer is {: d}"), CharT('*'));

	// *** alternate form ***
	check(SV("answer is +42"), SV("answer is {:+#d}"), CharT('*'));
	check(SV("answer is +101010"), SV("answer is {:+b}"), CharT('*'));
	check(SV("answer is +0b101010"), SV("answer is {:+#b}"), CharT('*'));
	check(SV("answer is +0B101010"), SV("answer is {:+#B}"), CharT('*'));
	check(SV("answer is +52"), SV("answer is {:+o}"), CharT('*'));
	check(SV("answer is +052"), SV("answer is {:+#o}"), CharT('*'));
	check(SV("answer is +2a"), SV("answer is {:+x}"), CharT('*'));
	check(SV("answer is +0x2a"), SV("answer is {:+#x}"), CharT('*'));
	check(SV("answer is +2A"), SV("answer is {:+X}"), CharT('*'));
	check(SV("answer is +0X2A"), SV("answer is {:+#X}"), CharT('*'));

	// *** zero-padding & width ***
	check(SV("answer is +00000000042"), SV("answer is {:+#012d}"), CharT('*'));
	check(SV("answer is +00000101010"), SV("answer is {:+012b}"), CharT('*'));
	check(SV("answer is +0b000101010"), SV("answer is {:+#012b}"), CharT('*'));
	check(SV("answer is +0B000101010"), SV("answer is {:+#012B}"), CharT('*'));
	check(SV("answer is +00000000052"), SV("answer is {:+012o}"), CharT('*'));
	check(SV("answer is +00000000052"), SV("answer is {:+#012o}"), CharT('*'));
	check(SV("answer is +0000000002a"), SV("answer is {:+012x}"), CharT('*'));
	check(SV("answer is +0x00000002a"), SV("answer is {:+#012x}"), CharT('*'));
	check(SV("answer is +0000000002A"), SV("answer is {:+012X}"), CharT('*'));

	check(SV("answer is +0X00000002A"), SV("answer is {:+#012X}"), CharT('*'));
}

// Using a const ref for world and universe so a string literal will be a character array.
// When passed as character array W and U have different types.
template <typename CharT, typename TestFunction, typename W, typename U>
void test_string_impl(TestFunction check, const W& world, const U& universe)
{
	// *** Valid input tests ***
	// Unused argument is ignored. TODO FMT what does the Standard mandate?
	check(SV("hello world"), SV("hello {}"), world, universe);
	check(SV("hello world and universe"), SV("hello {} and {}"), world, universe);
	check(SV("hello world"), SV("hello {0}"), world, universe);
	check(SV("hello universe"), SV("hello {1}"), world, universe);
	check(SV("hello universe and world"), SV("hello {1} and {0}"), world, universe);

	check(SV("hello world"), SV("hello {:_>}"), world);
	check(SV("hello world   "), SV("hello {:8}"), world);
	check(SV("hello    world"), SV("hello {:>8}"), world);
	check(SV("hello ___world"), SV("hello {:_>8}"), world);
	check(SV("hello _world__"), SV("hello {:_^8}"), world);
	check(SV("hello world___"), SV("hello {:_<8}"), world);

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	check(SV("hello :::world"), SV("hello {::>8}"), world);
	check(SV("hello <<<world"), SV("hello {:<>8}"), world);
	check(SV("hello ^^^world"), SV("hello {:^>8}"), world);

	check(SV("hello $world"), SV("hello {:$>{}}"), world, 6);
	check(SV("hello $world"), SV("hello {0:$>{1}}"), world, 6);
	check(SV("hello $world"), SV("hello {1:$>{0}}"), 6, world);

	check(SV("hello world"), SV("hello {:.5}"), world);
	check(SV("hello unive"), SV("hello {:.5}"), universe);

	check(SV("hello univer"), SV("hello {:.{}}"), universe, 6);
	check(SV("hello univer"), SV("hello {0:.{1}}"), universe, 6);
	check(SV("hello univer"), SV("hello {1:.{0}}"), 6, universe);

	check(SV("hello %world%"), SV("hello {:%^7.7}"), world);
	check(SV("hello univers"), SV("hello {:%^7.7}"), universe);
	check(SV("hello %world%"), SV("hello {:%^{}.{}}"), world, 7, 7);
	check(SV("hello %world%"), SV("hello {0:%^{1}.{2}}"), world, 7, 7);
	check(SV("hello %world%"), SV("hello {0:%^{2}.{1}}"), world, 7, 7);
	check(SV("hello %world%"), SV("hello {1:%^{0}.{2}}"), 7, world, 7);

	check(SV("hello world"), SV("hello {:_>s}"), world);
	check(SV("hello $world"), SV("hello {:$>{}s}"), world, 6);
	check(SV("hello world"), SV("hello {:.5s}"), world);
	check(SV("hello univer"), SV("hello {:.{}s}"), universe, 6);
	check(SV("hello %world%"), SV("hello {:%^7.7s}"), world);

	check(SV("hello #####uni"), SV("hello {:#>8.3s}"), universe);
	check(SV("hello ##uni###"), SV("hello {:#^8.3s}"), universe);
	check(SV("hello uni#####"), SV("hello {:#<8.3s}"), universe);

	// *** width ***
	// Width 0 allowed, but not useful for string arguments.
	check(SV("hello world"), SV("hello {:{}}"), world, 0);

	// *** precision ***

	// Precision 0 allowed, but not useful for string arguments.
	check(SV("hello "), SV("hello {:.{}}"), world, 0);
	// Precision may have leading zeros. Secondly tests the value is still base 10.
	check(SV("hello 0123456789"), SV("hello {:.000010}"), STR("0123456789abcdef"));
}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4566)	// ユニバーサル文字名 '' によって表示されている文字は、現在のコード ページ (932) で表示できません

template <typename CharT, typename TestFunction>
void test_string_unicode([[maybe_unused]] TestFunction check)
{
	// unicode.pass.cpp and ascii.pass.cpp have additional tests.

	// Make sure all possible types are tested. For clarity don't use macros.
	if constexpr (hamon::same_as<CharT, char>)
	{
		const char* c_string = "aßc";
		check(SV("*aßc*"), SV("{:*^5}"), c_string);
		check(SV("*aß*"), SV("{:*^4.2}"), c_string);

		check(SV("*aßc*"), SV("{:*^5}"), const_cast<char*>(c_string));
		check(SV("*aß*"), SV("{:*^4.2}"), const_cast<char*>(c_string));

		check(SV("*aßc*"), SV("{:*^5}"), "aßc");
		check(SV("*aß*"), SV("{:*^4.2}"), "aßc");

		check(SV("*aßc*"), SV("{:*^5}"), hamon::string("aßc"));
		check(SV("*aß*"), SV("{:*^4.2}"), hamon::string("aßc"));

		check(SV("*aßc*"), SV("{:*^5}"), hamon::string_view("aßc"));
		check(SV("*aß*"), SV("{:*^4.2}"), hamon::string_view("aßc"));
	}
	else
	{
		const wchar_t* c_string = L"aßc";
		check(SV("*aßc*"), SV("{:*^5}"), c_string);
		check(SV("*aß*"), SV("{:*^4.2}"), c_string);

		check(SV("*aßc*"), SV("{:*^5}"), const_cast<wchar_t*>(c_string));
		check(SV("*aß*"), SV("{:*^4.2}"), const_cast<wchar_t*>(c_string));

		check(SV("*aßc*"), SV("{:*^5}"), L"aßc");
		check(SV("*aß*"), SV("{:*^4.2}"), L"aßc");

		check(SV("*aßc*"), SV("{:*^5}"), hamon::wstring(L"aßc"));
		check(SV("*aß*"), SV("{:*^4.2}"), hamon::wstring(L"aßc"));

		check(SV("*aßc*"), SV("{:*^5}"), hamon::wstring_view(L"aßc"));
		check(SV("*aß*"), SV("{:*^4.2}"), hamon::wstring_view(L"aßc"));
	}

	// ß requires one column
	check(SV("aßc"), SV("{}"), STR("aßc"));

	check(SV("aßc"), SV("{:.3}"), STR("aßc"));
	check(SV("aß"), SV("{:.2}"), STR("aßc"));
	check(SV("a"), SV("{:.1}"), STR("aßc"));

	check(SV("aßc"), SV("{:3.3}"), STR("aßc"));
	check(SV("aß"), SV("{:2.2}"), STR("aßc"));
	check(SV("a"), SV("{:1.1}"), STR("aßc"));

	check(SV("aßc---"), SV("{:-<6}"), STR("aßc"));
	check(SV("-aßc--"), SV("{:-^6}"), STR("aßc"));
	check(SV("---aßc"), SV("{:->6}"), STR("aßc"));

#if defined(HAMON_MSVC)
	// MSVCでCharTがcharのとき、テストに失敗してしまう TODO
	if constexpr (!hamon::same_as<CharT, char>)
#endif
	{
		// \u1000 requires two columns
		check(SV("a\u1110c"), SV("{}"), STR("a\u1110c"));

		check(SV("a\u1100c"), SV("{:.4}"), STR("a\u1100c"));
		check(SV("a\u1100"), SV("{:.3}"), STR("a\u1100c"));
		check(SV("a"), SV("{:.2}"), STR("a\u1100c"));
		check(SV("a"), SV("{:.1}"), STR("a\u1100c"));

		check(SV("a\u1100c"), SV("{:-<4.4}"), STR("a\u1100c"));
		check(SV("a\u1100"), SV("{:-<3.3}"), STR("a\u1100c"));
		check(SV("a-"), SV("{:-<2.2}"), STR("a\u1100c"));
		check(SV("a"), SV("{:-<1.1}"), STR("a\u1100c"));

		check(SV("a\u1110c---"), SV("{:-<7}"), STR("a\u1110c"));
		check(SV("-a\u1110c--"), SV("{:-^7}"), STR("a\u1110c"));
		check(SV("---a\u1110c"), SV("{:->7}"), STR("a\u1110c"));

		// Examples used in P1868R2
		check(SV("*\u0041*"), SV("{:*^3}"), STR("\u0041")); // { LATIN CAPITAL LETTER A }
		check(SV("*\u00c1*"), SV("{:*^3}"), STR("\u00c1")); // { LATIN CAPITAL LETTER A WITH ACUTE }
		check(SV("*\u0041\u0301*"), SV("{:*^3}"), STR("\u0041\u0301"));	// { LATIN CAPITAL LETTER A } { COMBINING ACUTE ACCENT }
		check(SV("*\u0132*"), SV("{:*^3}"), STR("\u0132")); // { LATIN CAPITAL LIGATURE IJ }
		check(SV("*\u0394*"), SV("{:*^3}"), STR("\u0394")); // { GREEK CAPITAL LETTER DELTA }

		check(SV("*\u0429*"), SV("{:*^3}"), STR("\u0429"));         // { CYRILLIC CAPITAL LETTER SHCHA }
		check(SV("*\u05d0*"), SV("{:*^3}"), STR("\u05d0"));         // { HEBREW LETTER ALEF }
		check(SV("*\u0634*"), SV("{:*^3}"), STR("\u0634"));         // { ARABIC LETTER SHEEN }
		check(SV("*\u3009*"), SV("{:*^4}"), STR("\u3009"));         // { RIGHT-POINTING ANGLE BRACKET }
		check(SV("*\u754c*"), SV("{:*^4}"), STR("\u754c"));         // { CJK Unified Ideograph-754C }
		check(SV("*\U0001f921*"), SV("{:*^4}"), STR("\U0001f921")); // { UNICORN FACE }
		check(SV("*\U0001f468\u200d\U0001F469\u200d\U0001F467\u200d\U0001F466*"),
			SV("{:*^4}"),
			STR("\U0001f468\u200d\U0001F469\u200d\U0001F467\u200d\U0001F466")); // { Family: Man, Woman, Girl, Boy }
	}
}

HAMON_WARNING_PUSH()

template <typename CharT, typename TestFunction>
void test_string(TestFunction check)
{
	CharT world[] = { CharT('w'), CharT('o'), CharT('r'), CharT('l'), CharT('d'), 0 };
	CharT universe[] = { CharT('u'), CharT('n'), CharT('i'), CharT('v'), CharT('e'), CharT('r'), CharT('s'), CharT('e'), 0 };

	test_string_impl<CharT>(check, world, universe);
	test_string_impl<CharT>(check, static_cast<CharT*>(world), static_cast<CharT*>(universe));
	test_string_impl<CharT>(check, static_cast<CharT const*>(world), static_cast<CharT const*>(universe));
	test_string_impl<CharT>(check, hamon::basic_string<CharT>(world), hamon::basic_string<CharT>(universe));
	test_string_impl<CharT>(check, hamon::basic_string_view<CharT>(world), hamon::basic_string_view<CharT>(universe));

	test_string_unicode<CharT>(check);
}

template <typename CharT, typename TestFunction>
void test_bool(TestFunction check)
{
	// *** align-fill & width ***
	check(SV("answer is 'true   '"), SV("answer is '{:7}'"), true);
	check(SV("answer is '   true'"), SV("answer is '{:>7}'"), true);
	check(SV("answer is 'true   '"), SV("answer is '{:<7}'"), true);
	check(SV("answer is ' true  '"), SV("answer is '{:^7}'"), true);

	check(SV("answer is 'false   '"), SV("answer is '{:8s}'"), false);
	check(SV("answer is '   false'"), SV("answer is '{:>8s}'"), false);
	check(SV("answer is 'false   '"), SV("answer is '{:<8s}'"), false);
	check(SV("answer is ' false  '"), SV("answer is '{:^8s}'"), false);

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	check(SV("answer is ':::true'"), SV("answer is '{::>7}'"), true);
	check(SV("answer is 'true:::'"), SV("answer is '{::<7}'"), true);
	check(SV("answer is ':true::'"), SV("answer is '{::^7}'"), true);

	check(SV("answer is '---false'"), SV("answer is '{:->8s}'"), false);
	check(SV("answer is 'false---'"), SV("answer is '{:-<8s}'"), false);
	check(SV("answer is '-false--'"), SV("answer is '{:-^8s}'"), false);
}

template <typename CharT, typename TestFunction>
void test_bool_as_integer(TestFunction check)
{
	// *** align-fill & width ***
	check(SV("answer is '1'"), SV("answer is '{:<1d}'"), true);
	check(SV("answer is '1 '"), SV("answer is '{:<2d}'"), true);
	check(SV("answer is '0 '"), SV("answer is '{:<2d}'"), false);

	check(SV("answer is '     1'"), SV("answer is '{:6d}'"), true);
	check(SV("answer is '     1'"), SV("answer is '{:>6d}'"), true);
	check(SV("answer is '1     '"), SV("answer is '{:<6d}'"), true);
	check(SV("answer is '  1   '"), SV("answer is '{:^6d}'"), true);

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	check(SV("answer is ':::::0'"), SV("answer is '{::>6d}'"), false);
	check(SV("answer is '0:::::'"), SV("answer is '{::<6d}'"), false);
	check(SV("answer is '::0:::'"), SV("answer is '{::^6d}'"), false);

	// Test whether zero padding is ignored
	check(SV("answer is '     1'"), SV("answer is '{:>06d}'"), true);
	check(SV("answer is '1     '"), SV("answer is '{:<06d}'"), true);
	check(SV("answer is '  1   '"), SV("answer is '{:^06d}'"), true);

	// *** Sign ***
	check(SV("answer is 1"), SV("answer is {:d}"), true);
	check(SV("answer is 0"), SV("answer is {:-d}"), false);
	check(SV("answer is +1"), SV("answer is {:+d}"), true);
	check(SV("answer is  0"), SV("answer is {: d}"), false);

	// *** alternate form ***
	check(SV("answer is +1"), SV("answer is {:+#d}"), true);
	check(SV("answer is +1"), SV("answer is {:+b}"), true);
	check(SV("answer is +0b1"), SV("answer is {:+#b}"), true);
	check(SV("answer is +0B1"), SV("answer is {:+#B}"), true);
	check(SV("answer is +1"), SV("answer is {:+o}"), true);
	check(SV("answer is +01"), SV("answer is {:+#o}"), true);
	check(SV("answer is +1"), SV("answer is {:+x}"), true);
	check(SV("answer is +0x1"), SV("answer is {:+#x}"), true);
	check(SV("answer is +1"), SV("answer is {:+X}"), true);
	check(SV("answer is +0X1"), SV("answer is {:+#X}"), true);

	check(SV("answer is 0"), SV("answer is {:#d}"), false);
	check(SV("answer is 0"), SV("answer is {:b}"), false);
	check(SV("answer is 0b0"), SV("answer is {:#b}"), false);
	check(SV("answer is 0B0"), SV("answer is {:#B}"), false);
	check(SV("answer is 0"), SV("answer is {:o}"), false);
	check(SV("answer is 0"), SV("answer is {:#o}"), false);
	check(SV("answer is 0"), SV("answer is {:x}"), false);
	check(SV("answer is 0x0"), SV("answer is {:#x}"), false);
	check(SV("answer is 0"), SV("answer is {:X}"), false);
	check(SV("answer is 0X0"), SV("answer is {:#X}"), false);

	// *** zero-padding & width ***
	check(SV("answer is +00000000001"), SV("answer is {:+#012d}"), true);
	check(SV("answer is +00000000001"), SV("answer is {:+012b}"), true);
	check(SV("answer is +0b000000001"), SV("answer is {:+#012b}"), true);
	check(SV("answer is +0B000000001"), SV("answer is {:+#012B}"), true);
	check(SV("answer is +00000000001"), SV("answer is {:+012o}"), true);
	check(SV("answer is +00000000001"), SV("answer is {:+#012o}"), true);
	check(SV("answer is +00000000001"), SV("answer is {:+012x}"), true);
	check(SV("answer is +0x000000001"), SV("answer is {:+#012x}"), true);
	check(SV("answer is +00000000001"), SV("answer is {:+012X}"), true);
	check(SV("answer is +0X000000001"), SV("answer is {:+#012X}"), true);

	check(SV("answer is 000000000000"), SV("answer is {:#012d}"), false);
	check(SV("answer is 000000000000"), SV("answer is {:012b}"), false);
	check(SV("answer is 0b0000000000"), SV("answer is {:#012b}"), false);
	check(SV("answer is 0B0000000000"), SV("answer is {:#012B}"), false);
	check(SV("answer is 000000000000"), SV("answer is {:012o}"), false);
	check(SV("answer is 000000000000"), SV("answer is {:#012o}"), false);
	check(SV("answer is 000000000000"), SV("answer is {:012x}"), false);
	check(SV("answer is 0x0000000000"), SV("answer is {:#012x}"), false);
	check(SV("answer is 000000000000"), SV("answer is {:012X}"), false);
	check(SV("answer is 0X0000000000"), SV("answer is {:#012X}"), false);
}

template <typename CharT, typename I, typename TestFunction>
void test_unsigned_integer(TestFunction check)
{
	// *** align-fill & width ***
	check(SV("answer is '42'"), SV("answer is '{:<1}'"), I(42));
	check(SV("answer is '42'"), SV("answer is '{:<2}'"), I(42));
	check(SV("answer is '42 '"), SV("answer is '{:<3}'"), I(42));

	check(SV("answer is '     42'"), SV("answer is '{:7}'"), I(42));
	check(SV("answer is '     42'"), SV("answer is '{:>7}'"), I(42));
	check(SV("answer is '42     '"), SV("answer is '{:<7}'"), I(42));
	check(SV("answer is '  42   '"), SV("answer is '{:^7}'"), I(42));

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	check(SV("answer is ':::::42'"), SV("answer is '{::>7}'"), I(42));
	check(SV("answer is '42:::::'"), SV("answer is '{::<7}'"), I(42));
	check(SV("answer is '::42:::'"), SV("answer is '{::^7}'"), I(42));

	// Test whether zero padding is ignored
	check(SV("answer is '     42'"), SV("answer is '{:>07}'"), I(42));
	check(SV("answer is '42     '"), SV("answer is '{:<07}'"), I(42));
	check(SV("answer is '  42   '"), SV("answer is '{:^07}'"), I(42));

	// *** Sign ***
	check(SV("answer is 0"), SV("answer is {}"), I(0));
	check(SV("answer is 42"), SV("answer is {}"), I(42));
	check(SV("answer is 0"), SV("answer is {:-}"), I(0));
	check(SV("answer is 42"), SV("answer is {:-}"), I(42));
	check(SV("answer is +0"), SV("answer is {:+}"), I(0));
	check(SV("answer is +42"), SV("answer is {:+}"), I(42));
	check(SV("answer is  0"), SV("answer is {: }"), I(0));
	check(SV("answer is  42"), SV("answer is {: }"), I(42));

	// *** alternate form ***
	check(SV("answer is 0"), SV("answer is {:#}"), I(0));
	check(SV("answer is 0"), SV("answer is {:#d}"), I(0));
	check(SV("answer is 0"), SV("answer is {:b}"), I(0));
	check(SV("answer is 0b0"), SV("answer is {:#b}"), I(0));
	check(SV("answer is 0B0"), SV("answer is {:#B}"), I(0));
	check(SV("answer is 0"), SV("answer is {:o}"), I(0));
	check(SV("answer is 0"), SV("answer is {:#o}"), I(0));
	check(SV("answer is 0"), SV("answer is {:x}"), I(0));
	check(SV("answer is 0x0"), SV("answer is {:#x}"), I(0));
	check(SV("answer is 0"), SV("answer is {:X}"), I(0));
	check(SV("answer is 0X0"), SV("answer is {:#X}"), I(0));

	check(SV("answer is +42"), SV("answer is {:+#}"), I(42));
	check(SV("answer is +42"), SV("answer is {:+#d}"), I(42));
	check(SV("answer is +101010"), SV("answer is {:+b}"), I(42));
	check(SV("answer is +0b101010"), SV("answer is {:+#b}"), I(42));
	check(SV("answer is +0B101010"), SV("answer is {:+#B}"), I(42));
	check(SV("answer is +52"), SV("answer is {:+o}"), I(42));
	check(SV("answer is +052"), SV("answer is {:+#o}"), I(42));
	check(SV("answer is +2a"), SV("answer is {:+x}"), I(42));
	check(SV("answer is +0x2a"), SV("answer is {:+#x}"), I(42));
	check(SV("answer is +2A"), SV("answer is {:+X}"), I(42));
	check(SV("answer is +0X2A"), SV("answer is {:+#X}"), I(42));

	// *** zero-padding & width ***
	check(SV("answer is 000000000000"), SV("answer is {:#012}"), I(0));
	check(SV("answer is 000000000000"), SV("answer is {:#012d}"), I(0));
	check(SV("answer is 000000000000"), SV("answer is {:012b}"), I(0));
	check(SV("answer is 0b0000000000"), SV("answer is {:#012b}"), I(0));
	check(SV("answer is 0B0000000000"), SV("answer is {:#012B}"), I(0));
	check(SV("answer is 000000000000"), SV("answer is {:012o}"), I(0));
	check(SV("answer is 000000000000"), SV("answer is {:#012o}"), I(0));
	check(SV("answer is 000000000000"), SV("answer is {:012x}"), I(0));
	check(SV("answer is 0x0000000000"), SV("answer is {:#012x}"), I(0));
	check(SV("answer is 000000000000"), SV("answer is {:012X}"), I(0));
	check(SV("answer is 0X0000000000"), SV("answer is {:#012X}"), I(0));

	check(SV("answer is +00000000042"), SV("answer is {:+#012}"), I(42));
	check(SV("answer is +00000000042"), SV("answer is {:+#012d}"), I(42));
	check(SV("answer is +00000101010"), SV("answer is {:+012b}"), I(42));
	check(SV("answer is +0b000101010"), SV("answer is {:+#012b}"), I(42));
	check(SV("answer is +0B000101010"), SV("answer is {:+#012B}"), I(42));
	check(SV("answer is +00000000052"), SV("answer is {:+012o}"), I(42));
	check(SV("answer is +00000000052"), SV("answer is {:+#012o}"), I(42));
	check(SV("answer is +0000000002a"), SV("answer is {:+012x}"), I(42));
	check(SV("answer is +0x00000002a"), SV("answer is {:+#012x}"), I(42));
	check(SV("answer is +0000000002A"), SV("answer is {:+012X}"), I(42));
	check(SV("answer is +0X00000002A"), SV("answer is {:+#012X}"), I(42));
}

template <typename CharT, typename I, typename TestFunction>
void test_signed_integer(TestFunction check)
{
	// *** Sign ***
	check(SV("answer is -42"), SV("answer is {}"), I(-42));
	check(SV("answer is -42"), SV("answer is {:-}"), I(-42));
	check(SV("answer is -42"), SV("answer is {:+}"), I(-42));
	check(SV("answer is -42"), SV("answer is {: }"), I(-42));

	// *** alternate form ***
	check(SV("answer is -42"), SV("answer is {:#}"), I(-42));
	check(SV("answer is -42"), SV("answer is {:#d}"), I(-42));
	check(SV("answer is -101010"), SV("answer is {:b}"), I(-42));
	check(SV("answer is -0b101010"), SV("answer is {:#b}"), I(-42));
	check(SV("answer is -0B101010"), SV("answer is {:#B}"), I(-42));
	check(SV("answer is -52"), SV("answer is {:o}"), I(-42));
	check(SV("answer is -052"), SV("answer is {:#o}"), I(-42));
	check(SV("answer is -2a"), SV("answer is {:x}"), I(-42));
	check(SV("answer is -0x2a"), SV("answer is {:#x}"), I(-42));
	check(SV("answer is -2A"), SV("answer is {:X}"), I(-42));
	check(SV("answer is -0X2A"), SV("answer is {:#X}"), I(-42));

	// *** zero-padding & width ***
	check(SV("answer is -00000000042"), SV("answer is {:#012}"), I(-42));
	check(SV("answer is -00000000042"), SV("answer is {:#012d}"), I(-42));
	check(SV("answer is -00000101010"), SV("answer is {:012b}"), I(-42));
	check(SV("answer is -0b000101010"), SV("answer is {:#012b}"), I(-42));
	check(SV("answer is -0B000101010"), SV("answer is {:#012B}"), I(-42));
	check(SV("answer is -00000000052"), SV("answer is {:012o}"), I(-42));
	check(SV("answer is -00000000052"), SV("answer is {:#012o}"), I(-42));
	check(SV("answer is -0000000002a"), SV("answer is {:012x}"), I(-42));
	check(SV("answer is -0x00000002a"), SV("answer is {:#012x}"), I(-42));
	check(SV("answer is -0000000002A"), SV("answer is {:012X}"), I(-42));
	check(SV("answer is -0X00000002A"), SV("answer is {:#012X}"), I(-42));
}

template <typename CharT, typename I, typename TestFunction>
void test_integer_as_char(TestFunction check)
{
	// *** align-fill & width ***
	check(SV("answer is '*     '"), SV("answer is '{:6c}'"), I(42));
	check(SV("answer is '     *'"), SV("answer is '{:>6c}'"), I(42));
	check(SV("answer is '*     '"), SV("answer is '{:<6c}'"), I(42));
	check(SV("answer is '  *   '"), SV("answer is '{:^6c}'"), I(42));

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	check(SV("answer is ':::::*'"), SV("answer is '{::>6c}'"), I(42));
	check(SV("answer is '*:::::'"), SV("answer is '{::<6c}'"), I(42));
	check(SV("answer is '::*:::'"), SV("answer is '{::^6c}'"), I(42));

	// *** Sign ***
	check(SV("answer is *"), SV("answer is {:c}"), I(42));

	// *** locale-specific form ***
	// Note it has no effect but it's allowed.
	check(SV("answer is '*'"), SV("answer is '{:Lc}'"), I(42));
}

template <typename CharT, typename TestFunction>
void test_numeric_limits(TestFunction check)
{
	// *** check the minima and maxima ***
	check(SV("-0b10000000"), SV("{:#b}"), hamon::numeric_limits<hamon::int8_t>::min());
	check(SV("-0200"), SV("{:#o}"), hamon::numeric_limits<hamon::int8_t>::min());
	check(SV("-128"), SV("{:#}"), hamon::numeric_limits<hamon::int8_t>::min());
	check(SV("-0x80"), SV("{:#x}"), hamon::numeric_limits<hamon::int8_t>::min());

	check(SV("-0b1000000000000000"), SV("{:#b}"), hamon::numeric_limits<hamon::int16_t>::min());
	check(SV("-0100000"), SV("{:#o}"), hamon::numeric_limits<hamon::int16_t>::min());
	check(SV("-32768"), SV("{:#}"), hamon::numeric_limits<hamon::int16_t>::min());
	check(SV("-0x8000"), SV("{:#x}"), hamon::numeric_limits<hamon::int16_t>::min());

	check(SV("-0b10000000000000000000000000000000"), SV("{:#b}"), hamon::numeric_limits<hamon::int32_t>::min());
	check(SV("-020000000000"), SV("{:#o}"), hamon::numeric_limits<hamon::int32_t>::min());
	check(SV("-2147483648"), SV("{:#}"), hamon::numeric_limits<hamon::int32_t>::min());
	check(SV("-0x80000000"), SV("{:#x}"), hamon::numeric_limits<hamon::int32_t>::min());

	check(SV("-0b1000000000000000000000000000000000000000000000000000000000000000"),
		SV("{:#b}"), hamon::numeric_limits<hamon::int64_t>::min());
	check(SV("-01000000000000000000000"), SV("{:#o}"), hamon::numeric_limits<hamon::int64_t>::min());
	check(SV("-9223372036854775808"), SV("{:#}"), hamon::numeric_limits<hamon::int64_t>::min());
	check(SV("-0x8000000000000000"), SV("{:#x}"), hamon::numeric_limits<hamon::int64_t>::min());

	check(SV("0b1111111"), SV("{:#b}"), hamon::numeric_limits<hamon::int8_t>::max());
	check(SV("0177"), SV("{:#o}"), hamon::numeric_limits<hamon::int8_t>::max());
	check(SV("127"), SV("{:#}"), hamon::numeric_limits<hamon::int8_t>::max());
	check(SV("0x7f"), SV("{:#x}"), hamon::numeric_limits<hamon::int8_t>::max());

	check(SV("0b111111111111111"), SV("{:#b}"), hamon::numeric_limits<hamon::int16_t>::max());
	check(SV("077777"), SV("{:#o}"), hamon::numeric_limits<hamon::int16_t>::max());
	check(SV("32767"), SV("{:#}"), hamon::numeric_limits<hamon::int16_t>::max());
	check(SV("0x7fff"), SV("{:#x}"), hamon::numeric_limits<hamon::int16_t>::max());

	check(SV("0b1111111111111111111111111111111"), SV("{:#b}"), hamon::numeric_limits<hamon::int32_t>::max());
	check(SV("017777777777"), SV("{:#o}"), hamon::numeric_limits<hamon::int32_t>::max());
	check(SV("2147483647"), SV("{:#}"), hamon::numeric_limits<hamon::int32_t>::max());
	check(SV("0x7fffffff"), SV("{:#x}"), hamon::numeric_limits<hamon::int32_t>::max());

	check(SV("0b111111111111111111111111111111111111111111111111111111111111111"),
		SV("{:#b}"), hamon::numeric_limits<hamon::int64_t>::max());
	check(SV("0777777777777777777777"), SV("{:#o}"), hamon::numeric_limits<hamon::int64_t>::max());
	check(SV("9223372036854775807"), SV("{:#}"), hamon::numeric_limits<hamon::int64_t>::max());
	check(SV("0x7fffffffffffffff"), SV("{:#x}"), hamon::numeric_limits<hamon::int64_t>::max());

	check(SV("0b11111111"), SV("{:#b}"), hamon::numeric_limits<hamon::uint8_t>::max());
	check(SV("0377"), SV("{:#o}"), hamon::numeric_limits<hamon::uint8_t>::max());
	check(SV("255"), SV("{:#}"), hamon::numeric_limits<hamon::uint8_t>::max());
	check(SV("0xff"), SV("{:#x}"), hamon::numeric_limits<hamon::uint8_t>::max());

	check(SV("0b1111111111111111"), SV("{:#b}"), hamon::numeric_limits<hamon::uint16_t>::max());
	check(SV("0177777"), SV("{:#o}"), hamon::numeric_limits<hamon::uint16_t>::max());
	check(SV("65535"), SV("{:#}"), hamon::numeric_limits<hamon::uint16_t>::max());
	check(SV("0xffff"), SV("{:#x}"), hamon::numeric_limits<hamon::uint16_t>::max());

	check(SV("0b11111111111111111111111111111111"), SV("{:#b}"), hamon::numeric_limits<hamon::uint32_t>::max());
	check(SV("037777777777"), SV("{:#o}"), hamon::numeric_limits<hamon::uint32_t>::max());
	check(SV("4294967295"), SV("{:#}"), hamon::numeric_limits<hamon::uint32_t>::max());
	check(SV("0xffffffff"), SV("{:#x}"), hamon::numeric_limits<hamon::uint32_t>::max());

	check(SV("0b1111111111111111111111111111111111111111111111111111111111111111"),
		SV("{:#b}"), hamon::numeric_limits<hamon::uint64_t>::max());
	check(SV("01777777777777777777777"), SV("{:#o}"), hamon::numeric_limits<hamon::uint64_t>::max());
	check(SV("18446744073709551615"), SV("{:#}"), hamon::numeric_limits<hamon::uint64_t>::max());
	check(SV("0xffffffffffffffff"), SV("{:#x}"), hamon::numeric_limits<hamon::uint64_t>::max());
}

template <typename CharT, typename TestFunction>
void test_integer(TestFunction check)
{
	test_signed_integer<CharT, signed char>(check);
	test_signed_integer<CharT, signed short>(check);
	test_signed_integer<CharT, signed int>(check);
	test_signed_integer<CharT, signed long>(check);
	test_signed_integer<CharT, signed long long>(check);

	test_unsigned_integer<CharT, signed char>(check);
	test_unsigned_integer<CharT, signed short>(check);
	test_unsigned_integer<CharT, signed int>(check);
	test_unsigned_integer<CharT, signed long>(check);
	test_unsigned_integer<CharT, signed long long>(check);

	test_unsigned_integer<CharT, unsigned char>(check);
	test_unsigned_integer<CharT, unsigned short>(check);
	test_unsigned_integer<CharT, unsigned int>(check);
	test_unsigned_integer<CharT, unsigned long>(check);
	test_unsigned_integer<CharT, unsigned long long>(check);

	test_integer_as_char<CharT, signed char>(check);
	test_integer_as_char<CharT, signed short>(check);
	test_integer_as_char<CharT, signed int>(check);
	test_integer_as_char<CharT, signed long>(check);
	test_integer_as_char<CharT, signed long long>(check);

	test_integer_as_char<CharT, unsigned char>(check);
	test_integer_as_char<CharT, unsigned short>(check);
	test_integer_as_char<CharT, unsigned int>(check);
	test_integer_as_char<CharT, unsigned long>(check);
	test_integer_as_char<CharT, unsigned long long>(check);

	test_numeric_limits<CharT>(check);
}

template <typename CharT, typename F, typename TestFunction>
void test_floating_point_hex_lower_case(TestFunction check)
{
	auto nan_pos = hamon::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// Test whether the hexadecimal letters are the proper case.
	// The precision is too large for float, so two tests are used.
	check(SV("answer is '1.abcp+0'"), SV("answer is '{:a}'"), F(0x1.abcp+0));
	check(SV("answer is '1.defp+0'"), SV("answer is '{:a}'"), F(0x1.defp+0));

	// *** align-fill & width ***
	check(SV("answer is '   1p-2'"), SV("answer is '{:7a}'"), F(0.25));
	check(SV("answer is '   1p-2'"), SV("answer is '{:>7a}'"), F(0.25));
	check(SV("answer is '1p-2   '"), SV("answer is '{:<7a}'"), F(0.25));
	check(SV("answer is ' 1p-2  '"), SV("answer is '{:^7a}'"), F(0.25));

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	check(SV("answer is ':::1p-3'"), SV("answer is '{::>7a}'"), F(125e-3));
	check(SV("answer is '1p-3:::'"), SV("answer is '{::<7a}'"), F(125e-3));
	check(SV("answer is ':1p-3::'"), SV("answer is '{::^7a}'"), F(125e-3));

	check(SV("answer is '***inf'"), SV("answer is '{:*>6a}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is 'inf***'"), SV("answer is '{:*<6a}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '*inf**'"), SV("answer is '{:*^6a}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '###-inf'"), SV("answer is '{:#>7a}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf###'"), SV("answer is '{:#<7a}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '#-inf##'"), SV("answer is '{:#^7a}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is '^^^nan'"), SV("answer is '{:^>6a}'"), nan_pos);
	check(SV("answer is 'nan^^^'"), SV("answer is '{:^<6a}'"), nan_pos);
	check(SV("answer is '^nan^^'"), SV("answer is '{:^^6a}'"), nan_pos);

	check(SV("answer is '000-nan'"), SV("answer is '{:0>7a}'"), nan_neg);
	check(SV("answer is '-nan000'"), SV("answer is '{:0<7a}'"), nan_neg);
	check(SV("answer is '0-nan00'"), SV("answer is '{:0^7a}'"), nan_neg);

	// Test whether zero padding is ignored
	check(SV("answer is '   1p-2'"), SV("answer is '{:>07a}'"), F(0.25));
	check(SV("answer is '1p-2   '"), SV("answer is '{:<07a}'"), F(0.25));
	check(SV("answer is ' 1p-2  '"), SV("answer is '{:^07a}'"), F(0.25));

	// *** Sign ***
	check(SV("answer is '0p+0'"), SV("answer is '{:a}'"), F(0));
	check(SV("answer is '0p+0'"), SV("answer is '{:-a}'"), F(0));
	check(SV("answer is '+0p+0'"), SV("answer is '{:+a}'"), F(0));
	check(SV("answer is ' 0p+0'"), SV("answer is '{: a}'"), F(0));

	check(SV("answer is '-0p+0'"), SV("answer is '{:a}'"), F(-0.));
	check(SV("answer is '-0p+0'"), SV("answer is '{:-a}'"), F(-0.));
	check(SV("answer is '-0p+0'"), SV("answer is '{:+a}'"), F(-0.));
	check(SV("answer is '-0p+0'"), SV("answer is '{: a}'"), F(-0.));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	check(SV("answer is 'inf'"), SV("answer is '{:a}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is 'inf'"), SV("answer is '{:-a}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '+inf'"), SV("answer is '{:+a}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is ' inf'"), SV("answer is '{: a}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '-inf'"), SV("answer is '{:a}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{:-a}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{:+a}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{: a}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is 'nan'"), SV("answer is '{:a}'"), nan_pos);
	check(SV("answer is 'nan'"), SV("answer is '{:-a}'"), nan_pos);
	check(SV("answer is '+nan'"), SV("answer is '{:+a}'"), nan_pos);
	check(SV("answer is ' nan'"), SV("answer is '{: a}'"), nan_pos);

	check(SV("answer is '-nan'"), SV("answer is '{:a}'"), nan_neg);
	check(SV("answer is '-nan'"), SV("answer is '{:-a}'"), nan_neg);
	check(SV("answer is '-nan'"), SV("answer is '{:+a}'"), nan_neg);
	check(SV("answer is '-nan'"), SV("answer is '{: a}'"), nan_neg);

	// *** alternate form ***
	// When precision is zero there's no decimal point except when the alternate form is specified.
	check(SV("answer is '0p+0'"), SV("answer is '{:a}'"), F(0));
	check(SV("answer is '0.p+0'"), SV("answer is '{:#a}'"), F(0));

	check(SV("answer is '1p+1'"), SV("answer is '{:.0a}'"), F(2.5));
	check(SV("answer is '1.p+1'"), SV("answer is '{:#.0a}'"), F(2.5));
	check(SV("answer is '1.4p+1'"), SV("answer is '{:#a}'"), F(2.5));

	check(SV("answer is 'inf'"), SV("answer is '{:#a}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{:#a}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is 'nan'"), SV("answer is '{:#a}'"), nan_pos);
	check(SV("answer is '-nan'"), SV("answer is '{:#a}'"), nan_neg);

	// *** zero-padding & width ***
	check(SV("answer is '1p-5'"), SV("answer is '{:04a}'"), 0.03125);
	check(SV("answer is '+1p-5'"), SV("answer is '{:+05a}'"), 0.03125);
	check(SV("answer is '+01p-5'"), SV("answer is '{:+06a}'"), 0.03125);

	check(SV("answer is '0001p-5'"), SV("answer is '{:07a}'"), 0.03125);
	check(SV("answer is '0001p-5'"), SV("answer is '{:-07a}'"), 0.03125);
	check(SV("answer is '+001p-5'"), SV("answer is '{:+07a}'"), 0.03125);
	check(SV("answer is ' 001p-5'"), SV("answer is '{: 07a}'"), 0.03125);

	check(SV("answer is '       inf'"), SV("answer is '{:010a}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '       inf'"), SV("answer is '{:-010a}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      +inf'"), SV("answer is '{:+010a}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '       inf'"), SV("answer is '{: 010a}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '      -inf'"), SV("answer is '{:010a}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -inf'"), SV("answer is '{:-010a}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -inf'"), SV("answer is '{:+010a}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -inf'"), SV("answer is '{: 010a}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is '       nan'"), SV("answer is '{:010a}'"), nan_pos);
	check(SV("answer is '       nan'"), SV("answer is '{:-010a}'"), nan_pos);
	check(SV("answer is '      +nan'"), SV("answer is '{:+010a}'"), nan_pos);
	check(SV("answer is '       nan'"), SV("answer is '{: 010a}'"), nan_pos);

	check(SV("answer is '      -nan'"), SV("answer is '{:010a}'"), nan_neg);
	check(SV("answer is '      -nan'"), SV("answer is '{:-010a}'"), nan_neg);
	check(SV("answer is '      -nan'"), SV("answer is '{:+010a}'"), nan_neg);
	check(SV("answer is '      -nan'"), SV("answer is '{: 010a}'"), nan_neg);
}

template <typename CharT, typename F, typename TestFunction>
void test_floating_point_hex_upper_case(TestFunction check)
{
	auto nan_pos = hamon::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// Test whether the hexadecimal letters are the proper case.
	// The precision is too large for float, so two tests are used.
	check(SV("answer is '1.ABCP+0'"), SV("answer is '{:A}'"), F(0x1.abcp+0));
	check(SV("answer is '1.DEFP+0'"), SV("answer is '{:A}'"), F(0x1.defp+0));

	// *** align-fill & width ***
	check(SV("answer is '   1P-2'"), SV("answer is '{:7A}'"), F(0.25));
	check(SV("answer is '   1P-2'"), SV("answer is '{:>7A}'"), F(0.25));
	check(SV("answer is '1P-2   '"), SV("answer is '{:<7A}'"), F(0.25));
	check(SV("answer is ' 1P-2  '"), SV("answer is '{:^7A}'"), F(0.25));

	check(SV("answer is '---1P-3'"), SV("answer is '{:->7A}'"), F(125e-3));
	check(SV("answer is '1P-3---'"), SV("answer is '{:-<7A}'"), F(125e-3));
	check(SV("answer is '-1P-3--'"), SV("answer is '{:-^7A}'"), F(125e-3));

	check(SV("answer is '***INF'"), SV("answer is '{:*>6A}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is 'INF***'"), SV("answer is '{:*<6A}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '*INF**'"), SV("answer is '{:*^6A}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '###-INF'"), SV("answer is '{:#>7A}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-INF###'"), SV("answer is '{:#<7A}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '#-INF##'"), SV("answer is '{:#^7A}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is '^^^NAN'"), SV("answer is '{:^>6A}'"), nan_pos);
	check(SV("answer is 'NAN^^^'"), SV("answer is '{:^<6A}'"), nan_pos);
	check(SV("answer is '^NAN^^'"), SV("answer is '{:^^6A}'"), nan_pos);

	check(SV("answer is '000-NAN'"), SV("answer is '{:0>7A}'"), nan_neg);
	check(SV("answer is '-NAN000'"), SV("answer is '{:0<7A}'"), nan_neg);
	check(SV("answer is '0-NAN00'"), SV("answer is '{:0^7A}'"), nan_neg);

	// Test whether zero padding is ignored
	check(SV("answer is '   1P-2'"), SV("answer is '{:>07A}'"), F(0.25));
	check(SV("answer is '1P-2   '"), SV("answer is '{:<07A}'"), F(0.25));
	check(SV("answer is ' 1P-2  '"), SV("answer is '{:^07A}'"), F(0.25));

	// *** Sign ***
	check(SV("answer is '0P+0'"), SV("answer is '{:A}'"), F(0));
	check(SV("answer is '0P+0'"), SV("answer is '{:-A}'"), F(0));
	check(SV("answer is '+0P+0'"), SV("answer is '{:+A}'"), F(0));
	check(SV("answer is ' 0P+0'"), SV("answer is '{: A}'"), F(0));

	check(SV("answer is '-0P+0'"), SV("answer is '{:A}'"), F(-0.));
	check(SV("answer is '-0P+0'"), SV("answer is '{:-A}'"), F(-0.));
	check(SV("answer is '-0P+0'"), SV("answer is '{:+A}'"), F(-0.));
	check(SV("answer is '-0P+0'"), SV("answer is '{: A}'"), F(-0.));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	check(SV("answer is 'INF'"), SV("answer is '{:A}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is 'INF'"), SV("answer is '{:-A}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '+INF'"), SV("answer is '{:+A}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is ' INF'"), SV("answer is '{: A}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '-INF'"), SV("answer is '{:A}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-INF'"), SV("answer is '{:-A}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-INF'"), SV("answer is '{:+A}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-INF'"), SV("answer is '{: A}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is 'NAN'"), SV("answer is '{:A}'"), nan_pos);
	check(SV("answer is 'NAN'"), SV("answer is '{:-A}'"), nan_pos);
	check(SV("answer is '+NAN'"), SV("answer is '{:+A}'"), nan_pos);
	check(SV("answer is ' NAN'"), SV("answer is '{: A}'"), nan_pos);

	check(SV("answer is '-NAN'"), SV("answer is '{:A}'"), nan_neg);
	check(SV("answer is '-NAN'"), SV("answer is '{:-A}'"), nan_neg);
	check(SV("answer is '-NAN'"), SV("answer is '{:+A}'"), nan_neg);
	check(SV("answer is '-NAN'"), SV("answer is '{: A}'"), nan_neg);

	// *** alternate form ***
	// When precision is zero there's no decimal point except when the alternate form is specified.
	check(SV("answer is '0P+0'"), SV("answer is '{:A}'"), F(0));
	check(SV("answer is '0.P+0'"), SV("answer is '{:#A}'"), F(0));

	check(SV("answer is '1P+1'"), SV("answer is '{:.0A}'"), F(2.5));
	check(SV("answer is '1.P+1'"), SV("answer is '{:#.0A}'"), F(2.5));
	check(SV("answer is '1.4P+1'"), SV("answer is '{:#A}'"), F(2.5));

	check(SV("answer is 'INF'"), SV("answer is '{:#A}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-INF'"), SV("answer is '{:#A}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is 'NAN'"), SV("answer is '{:#A}'"), nan_pos);
	check(SV("answer is '-NAN'"), SV("answer is '{:#A}'"), nan_neg);

	// *** zero-padding & width ***
	check(SV("answer is '1P-5'"), SV("answer is '{:04A}'"), 0.03125);
	check(SV("answer is '+1P-5'"), SV("answer is '{:+05A}'"), 0.03125);
	check(SV("answer is '+01P-5'"), SV("answer is '{:+06A}'"), 0.03125);

	check(SV("answer is '0001P-5'"), SV("answer is '{:07A}'"), 0.03125);
	check(SV("answer is '0001P-5'"), SV("answer is '{:-07A}'"), 0.03125);
	check(SV("answer is '+001P-5'"), SV("answer is '{:+07A}'"), 0.03125);
	check(SV("answer is ' 001P-5'"), SV("answer is '{: 07A}'"), 0.03125);

	check(SV("answer is '       INF'"), SV("answer is '{:010A}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '       INF'"), SV("answer is '{:-010A}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      +INF'"), SV("answer is '{:+010A}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '       INF'"), SV("answer is '{: 010A}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '      -INF'"), SV("answer is '{:010A}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -INF'"), SV("answer is '{:-010A}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -INF'"), SV("answer is '{:+010A}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -INF'"), SV("answer is '{: 010A}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is '       NAN'"), SV("answer is '{:010A}'"), nan_pos);
	check(SV("answer is '       NAN'"), SV("answer is '{:-010A}'"), nan_pos);
	check(SV("answer is '      +NAN'"), SV("answer is '{:+010A}'"), nan_pos);
	check(SV("answer is '       NAN'"), SV("answer is '{: 010A}'"), nan_pos);

	check(SV("answer is '      -NAN'"), SV("answer is '{:010A}'"), nan_neg);
	check(SV("answer is '      -NAN'"), SV("answer is '{:-010A}'"), nan_neg);
	check(SV("answer is '      -NAN'"), SV("answer is '{:+010A}'"), nan_neg);
	check(SV("answer is '      -NAN'"), SV("answer is '{: 010A}'"), nan_neg);
}

template <typename CharT, typename F, typename TestFunction>
void test_floating_point_hex_lower_case_precision(TestFunction check)
{
	auto nan_pos = hamon::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	check(SV("answer is '   1.000000p-2'"), SV("answer is '{:14.6a}'"), F(0.25));
	check(SV("answer is '   1.000000p-2'"), SV("answer is '{:>14.6a}'"), F(0.25));
	check(SV("answer is '1.000000p-2   '"), SV("answer is '{:<14.6a}'"), F(0.25));
	check(SV("answer is ' 1.000000p-2  '"), SV("answer is '{:^14.6a}'"), F(0.25));

	check(SV("answer is '---1.000000p-3'"), SV("answer is '{:->14.6a}'"), F(125e-3));
	check(SV("answer is '1.000000p-3---'"), SV("answer is '{:-<14.6a}'"), F(125e-3));
	check(SV("answer is '-1.000000p-3--'"), SV("answer is '{:-^14.6a}'"), F(125e-3));

	check(SV("answer is '***inf'"), SV("answer is '{:*>6.6a}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is 'inf***'"), SV("answer is '{:*<6.6a}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '*inf**'"), SV("answer is '{:*^6.6a}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '###-inf'"), SV("answer is '{:#>7.6a}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf###'"), SV("answer is '{:#<7.6a}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '#-inf##'"), SV("answer is '{:#^7.6a}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is '^^^nan'"), SV("answer is '{:^>6.6a}'"), nan_pos);
	check(SV("answer is 'nan^^^'"), SV("answer is '{:^<6.6a}'"), nan_pos);
	check(SV("answer is '^nan^^'"), SV("answer is '{:^^6.6a}'"), nan_pos);

	check(SV("answer is '000-nan'"), SV("answer is '{:0>7.6a}'"), nan_neg);
	check(SV("answer is '-nan000'"), SV("answer is '{:0<7.6a}'"), nan_neg);
	check(SV("answer is '0-nan00'"), SV("answer is '{:0^7.6a}'"), nan_neg);

	// Test whether zero padding is ignored
	check(SV("answer is '   1.000000p-2'"), SV("answer is '{:>014.6a}'"), F(0.25));
	check(SV("answer is '1.000000p-2   '"), SV("answer is '{:<014.6a}'"), F(0.25));
	check(SV("answer is ' 1.000000p-2  '"), SV("answer is '{:^014.6a}'"), F(0.25));

	// *** Sign ***
	check(SV("answer is '0.000000p+0'"), SV("answer is '{:.6a}'"), F(0));
	check(SV("answer is '0.000000p+0'"), SV("answer is '{:-.6a}'"), F(0));
	check(SV("answer is '+0.000000p+0'"), SV("answer is '{:+.6a}'"), F(0));
	check(SV("answer is ' 0.000000p+0'"), SV("answer is '{: .6a}'"), F(0));

	check(SV("answer is '-0.000000p+0'"), SV("answer is '{:.6a}'"), F(-0.));
	check(SV("answer is '-0.000000p+0'"), SV("answer is '{:-.6a}'"), F(-0.));
	check(SV("answer is '-0.000000p+0'"), SV("answer is '{:+.6a}'"), F(-0.));
	check(SV("answer is '-0.000000p+0'"), SV("answer is '{: .6a}'"), F(-0.));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	check(SV("answer is 'inf'"), SV("answer is '{:.6a}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is 'inf'"), SV("answer is '{:-.6a}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '+inf'"), SV("answer is '{:+.6a}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is ' inf'"), SV("answer is '{: .6a}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '-inf'"), SV("answer is '{:.6a}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{:-.6a}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{:+.6a}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{: .6a}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is 'nan'"), SV("answer is '{:.6a}'"), nan_pos);
	check(SV("answer is 'nan'"), SV("answer is '{:-.6a}'"), nan_pos);
	check(SV("answer is '+nan'"), SV("answer is '{:+.6a}'"), nan_pos);
	check(SV("answer is ' nan'"), SV("answer is '{: .6a}'"), nan_pos);

	check(SV("answer is '-nan'"), SV("answer is '{:.6a}'"), nan_neg);
	check(SV("answer is '-nan'"), SV("answer is '{:-.6a}'"), nan_neg);
	check(SV("answer is '-nan'"), SV("answer is '{:+.6a}'"), nan_neg);
	check(SV("answer is '-nan'"), SV("answer is '{: .6a}'"), nan_neg);

	// *** alternate form ***
	check(SV("answer is '1.400000p+1'"), SV("answer is '{:#.6a}'"), F(2.5));

	check(SV("answer is 'inf'"), SV("answer is '{:#.6a}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{:#.6a}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is 'nan'"), SV("answer is '{:#.6a}'"), nan_pos);
	check(SV("answer is '-nan'"), SV("answer is '{:#.6a}'"), nan_neg);

	// *** zero-padding & width ***
	check(SV("answer is '1.000000p-5'"), SV("answer is '{:011.6a}'"), 0.03125);
	check(SV("answer is '+1.000000p-5'"), SV("answer is '{:+012.6a}'"), 0.03125);
	check(SV("answer is '+01.000000p-5'"), SV("answer is '{:+013.6a}'"), 0.03125);

	check(SV("answer is '0001.000000p-5'"), SV("answer is '{:014.6a}'"), 0.03125);
	check(SV("answer is '0001.000000p-5'"), SV("answer is '{:-014.6a}'"), 0.03125);
	check(SV("answer is '+001.000000p-5'"), SV("answer is '{:+014.6a}'"), 0.03125);
	check(SV("answer is ' 001.000000p-5'"), SV("answer is '{: 014.6a}'"), 0.03125);

	check(SV("answer is '       inf'"), SV("answer is '{:010.6a}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '       inf'"), SV("answer is '{:-010.6a}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      +inf'"), SV("answer is '{:+010.6a}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '       inf'"), SV("answer is '{: 010.6a}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '      -inf'"), SV("answer is '{:010.6a}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -inf'"), SV("answer is '{:-010.6a}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -inf'"), SV("answer is '{:+010.6a}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -inf'"), SV("answer is '{: 010.6a}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is '       nan'"), SV("answer is '{:010.6a}'"), nan_pos);
	check(SV("answer is '       nan'"), SV("answer is '{:-010.6a}'"), nan_pos);
	check(SV("answer is '      +nan'"), SV("answer is '{:+010.6a}'"), nan_pos);
	check(SV("answer is '       nan'"), SV("answer is '{: 010.6a}'"), nan_pos);

	check(SV("answer is '      -nan'"), SV("answer is '{:010.6a}'"), nan_neg);
	check(SV("answer is '      -nan'"), SV("answer is '{:-010.6a}'"), nan_neg);
	check(SV("answer is '      -nan'"), SV("answer is '{:+010.6a}'"), nan_neg);
	check(SV("answer is '      -nan'"), SV("answer is '{: 010.6a}'"), nan_neg);
}

template <typename CharT, typename F, typename TestFunction>
void test_floating_point_hex_upper_case_precision(TestFunction check)
{
	auto nan_pos = hamon::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	check(SV("answer is '   1.000000P-2'"), SV("answer is '{:14.6A}'"), F(0.25));
	check(SV("answer is '   1.000000P-2'"), SV("answer is '{:>14.6A}'"), F(0.25));
	check(SV("answer is '1.000000P-2   '"), SV("answer is '{:<14.6A}'"), F(0.25));
	check(SV("answer is ' 1.000000P-2  '"), SV("answer is '{:^14.6A}'"), F(0.25));

	check(SV("answer is '---1.000000P-3'"), SV("answer is '{:->14.6A}'"), F(125e-3));
	check(SV("answer is '1.000000P-3---'"), SV("answer is '{:-<14.6A}'"), F(125e-3));
	check(SV("answer is '-1.000000P-3--'"), SV("answer is '{:-^14.6A}'"), F(125e-3));

	check(SV("answer is '***INF'"), SV("answer is '{:*>6.6A}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is 'INF***'"), SV("answer is '{:*<6.6A}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '*INF**'"), SV("answer is '{:*^6.6A}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '###-INF'"), SV("answer is '{:#>7.6A}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-INF###'"), SV("answer is '{:#<7.6A}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '#-INF##'"), SV("answer is '{:#^7.6A}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is '^^^NAN'"), SV("answer is '{:^>6.6A}'"), nan_pos);
	check(SV("answer is 'NAN^^^'"), SV("answer is '{:^<6.6A}'"), nan_pos);
	check(SV("answer is '^NAN^^'"), SV("answer is '{:^^6.6A}'"), nan_pos);

	check(SV("answer is '000-NAN'"), SV("answer is '{:0>7.6A}'"), nan_neg);
	check(SV("answer is '-NAN000'"), SV("answer is '{:0<7.6A}'"), nan_neg);
	check(SV("answer is '0-NAN00'"), SV("answer is '{:0^7.6A}'"), nan_neg);

	// Test whether zero padding is ignored
	check(SV("answer is '   1.000000P-2'"), SV("answer is '{:>014.6A}'"), F(0.25));
	check(SV("answer is '1.000000P-2   '"), SV("answer is '{:<014.6A}'"), F(0.25));
	check(SV("answer is ' 1.000000P-2  '"), SV("answer is '{:^014.6A}'"), F(0.25));

	// *** Sign ***
	check(SV("answer is '0.000000P+0'"), SV("answer is '{:.6A}'"), F(0));
	check(SV("answer is '0.000000P+0'"), SV("answer is '{:-.6A}'"), F(0));
	check(SV("answer is '+0.000000P+0'"), SV("answer is '{:+.6A}'"), F(0));
	check(SV("answer is ' 0.000000P+0'"), SV("answer is '{: .6A}'"), F(0));

	check(SV("answer is '-0.000000P+0'"), SV("answer is '{:.6A}'"), F(-0.));
	check(SV("answer is '-0.000000P+0'"), SV("answer is '{:-.6A}'"), F(-0.));
	check(SV("answer is '-0.000000P+0'"), SV("answer is '{:+.6A}'"), F(-0.));
	check(SV("answer is '-0.000000P+0'"), SV("answer is '{: .6A}'"), F(-0.));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	check(SV("answer is 'INF'"), SV("answer is '{:.6A}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is 'INF'"), SV("answer is '{:-.6A}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '+INF'"), SV("answer is '{:+.6A}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is ' INF'"), SV("answer is '{: .6A}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '-INF'"), SV("answer is '{:.6A}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-INF'"), SV("answer is '{:-.6A}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-INF'"), SV("answer is '{:+.6A}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-INF'"), SV("answer is '{: .6A}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is 'NAN'"), SV("answer is '{:.6A}'"), nan_pos);
	check(SV("answer is 'NAN'"), SV("answer is '{:-.6A}'"), nan_pos);
	check(SV("answer is '+NAN'"), SV("answer is '{:+.6A}'"), nan_pos);
	check(SV("answer is ' NAN'"), SV("answer is '{: .6A}'"), nan_pos);

	check(SV("answer is '-NAN'"), SV("answer is '{:.6A}'"), nan_neg);
	check(SV("answer is '-NAN'"), SV("answer is '{:-.6A}'"), nan_neg);
	check(SV("answer is '-NAN'"), SV("answer is '{:+.6A}'"), nan_neg);
	check(SV("answer is '-NAN'"), SV("answer is '{: .6A}'"), nan_neg);

	// *** alternate form ***
	check(SV("answer is '1.400000P+1'"), SV("answer is '{:#.6A}'"), F(2.5));

	check(SV("answer is 'INF'"), SV("answer is '{:#.6A}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-INF'"), SV("answer is '{:#.6A}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is 'NAN'"), SV("answer is '{:#.6A}'"), nan_pos);
	check(SV("answer is '-NAN'"), SV("answer is '{:#.6A}'"), nan_neg);

	// *** zero-padding & width ***
	check(SV("answer is '1.000000P-5'"), SV("answer is '{:011.6A}'"), 0.03125);
	check(SV("answer is '+1.000000P-5'"), SV("answer is '{:+012.6A}'"), 0.03125);
	check(SV("answer is '+01.000000P-5'"), SV("answer is '{:+013.6A}'"), 0.03125);

	check(SV("answer is '0001.000000P-5'"), SV("answer is '{:014.6A}'"), 0.03125);
	check(SV("answer is '0001.000000P-5'"), SV("answer is '{:-014.6A}'"), 0.03125);
	check(SV("answer is '+001.000000P-5'"), SV("answer is '{:+014.6A}'"), 0.03125);
	check(SV("answer is ' 001.000000P-5'"), SV("answer is '{: 014.6A}'"), 0.03125);

	check(SV("answer is '       INF'"), SV("answer is '{:010.6A}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '       INF'"), SV("answer is '{:-010.6A}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      +INF'"), SV("answer is '{:+010.6A}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '       INF'"), SV("answer is '{: 010.6A}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '      -INF'"), SV("answer is '{:010.6A}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -INF'"), SV("answer is '{:-010.6A}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -INF'"), SV("answer is '{:+010.6A}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -INF'"), SV("answer is '{: 010.6A}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is '       NAN'"), SV("answer is '{:010.6A}'"), nan_pos);
	check(SV("answer is '       NAN'"), SV("answer is '{:-010.6A}'"), nan_pos);
	check(SV("answer is '      +NAN'"), SV("answer is '{:+010.6A}'"), nan_pos);
	check(SV("answer is '       NAN'"), SV("answer is '{: 010.6A}'"), nan_pos);

	check(SV("answer is '      -NAN'"), SV("answer is '{:010.6A}'"), nan_neg);
	check(SV("answer is '      -NAN'"), SV("answer is '{:-010.6A}'"), nan_neg);
	check(SV("answer is '      -NAN'"), SV("answer is '{:+010.6A}'"), nan_neg);
	check(SV("answer is '      -NAN'"), SV("answer is '{: 010.6A}'"), nan_neg);
}

template <typename CharT, typename F, typename TestFunction>
void test_floating_point_scientific_lower_case(TestFunction check)
{
	auto nan_pos = hamon::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	check(SV("answer is '   2.500000e-01'"), SV("answer is '{:15e}'"), F(0.25));
	check(SV("answer is '   2.500000e-01'"), SV("answer is '{:>15e}'"), F(0.25));
	check(SV("answer is '2.500000e-01   '"), SV("answer is '{:<15e}'"), F(0.25));
	check(SV("answer is ' 2.500000e-01  '"), SV("answer is '{:^15e}'"), F(0.25));

	check(SV("answer is '---1.250000e-01'"), SV("answer is '{:->15e}'"), F(125e-3));
	check(SV("answer is '1.250000e-01---'"), SV("answer is '{:-<15e}'"), F(125e-3));
	check(SV("answer is '-1.250000e-01--'"), SV("answer is '{:-^15e}'"), F(125e-3));

	check(SV("answer is '***inf'"), SV("answer is '{:*>6e}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is 'inf***'"), SV("answer is '{:*<6e}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '*inf**'"), SV("answer is '{:*^6e}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '###-inf'"), SV("answer is '{:#>7e}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf###'"), SV("answer is '{:#<7e}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '#-inf##'"), SV("answer is '{:#^7e}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is '^^^nan'"), SV("answer is '{:^>6e}'"), nan_pos);
	check(SV("answer is 'nan^^^'"), SV("answer is '{:^<6e}'"), nan_pos);
	check(SV("answer is '^nan^^'"), SV("answer is '{:^^6e}'"), nan_pos);

	check(SV("answer is '000-nan'"), SV("answer is '{:0>7e}'"), nan_neg);
	check(SV("answer is '-nan000'"), SV("answer is '{:0<7e}'"), nan_neg);
	check(SV("answer is '0-nan00'"), SV("answer is '{:0^7e}'"), nan_neg);

	// Test whether zero padding is ignored
	check(SV("answer is '   2.500000e-01'"), SV("answer is '{:>015e}'"), F(0.25));
	check(SV("answer is '2.500000e-01   '"), SV("answer is '{:<015e}'"), F(0.25));
	check(SV("answer is ' 2.500000e-01  '"), SV("answer is '{:^015e}'"), F(0.25));

	// *** Sign ***
	check(SV("answer is '0.000000e+00'"), SV("answer is '{:e}'"), F(0));
	check(SV("answer is '0.000000e+00'"), SV("answer is '{:-e}'"), F(0));
	check(SV("answer is '+0.000000e+00'"), SV("answer is '{:+e}'"), F(0));
	check(SV("answer is ' 0.000000e+00'"), SV("answer is '{: e}'"), F(0));

	check(SV("answer is '-0.000000e+00'"), SV("answer is '{:e}'"), F(-0.));
	check(SV("answer is '-0.000000e+00'"), SV("answer is '{:-e}'"), F(-0.));
	check(SV("answer is '-0.000000e+00'"), SV("answer is '{:+e}'"), F(-0.));
	check(SV("answer is '-0.000000e+00'"), SV("answer is '{: e}'"), F(-0.));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	check(SV("answer is 'inf'"), SV("answer is '{:e}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is 'inf'"), SV("answer is '{:-e}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '+inf'"), SV("answer is '{:+e}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is ' inf'"), SV("answer is '{: e}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '-inf'"), SV("answer is '{:e}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{:-e}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{:+e}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{: e}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is 'nan'"), SV("answer is '{:e}'"), nan_pos);
	check(SV("answer is 'nan'"), SV("answer is '{:-e}'"), nan_pos);
	check(SV("answer is '+nan'"), SV("answer is '{:+e}'"), nan_pos);
	check(SV("answer is ' nan'"), SV("answer is '{: e}'"), nan_pos);

	check(SV("answer is '-nan'"), SV("answer is '{:e}'"), nan_neg);
	check(SV("answer is '-nan'"), SV("answer is '{:-e}'"), nan_neg);
	check(SV("answer is '-nan'"), SV("answer is '{:+e}'"), nan_neg);
	check(SV("answer is '-nan'"), SV("answer is '{: e}'"), nan_neg);

	// *** alternate form **
	// When precision is zero there's no decimal point except when the alternate form is specified.
	check(SV("answer is '0e+00'"), SV("answer is '{:.0e}'"), F(0));
	check(SV("answer is '0.e+00'"), SV("answer is '{:#.0e}'"), F(0));

	check(SV("answer is '0.000000e+00'"), SV("answer is '{:#e}'"), F(0));
	check(SV("answer is '2.500000e+00'"), SV("answer is '{:#e}'"), F(2.5));

	check(SV("answer is 'inf'"), SV("answer is '{:#e}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{:#e}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is 'nan'"), SV("answer is '{:#e}'"), nan_pos);
	check(SV("answer is '-nan'"), SV("answer is '{:#e}'"), nan_neg);

	// *** zero-padding & width ***
	check(SV("answer is '3.125000e-02'"), SV("answer is '{:07e}'"), 0.03125);
	check(SV("answer is '+3.125000e-02'"), SV("answer is '{:+07e}'"), 0.03125);
	check(SV("answer is '+3.125000e-02'"), SV("answer is '{:+08e}'"), 0.03125);
	check(SV("answer is '+3.125000e-02'"), SV("answer is '{:+09e}'"), 0.03125);

	check(SV("answer is '003.125000e-02'"), SV("answer is '{:014e}'"), 0.03125);
	check(SV("answer is '003.125000e-02'"), SV("answer is '{:-014e}'"), 0.03125);
	check(SV("answer is '+03.125000e-02'"), SV("answer is '{:+014e}'"), 0.03125);
	check(SV("answer is ' 03.125000e-02'"), SV("answer is '{: 014e}'"), 0.03125);

	check(SV("answer is '       inf'"), SV("answer is '{:010e}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '       inf'"), SV("answer is '{:-010e}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      +inf'"), SV("answer is '{:+010e}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '       inf'"), SV("answer is '{: 010e}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '      -inf'"), SV("answer is '{:010e}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -inf'"), SV("answer is '{:-010e}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -inf'"), SV("answer is '{:+010e}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -inf'"), SV("answer is '{: 010e}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is '       nan'"), SV("answer is '{:010e}'"), nan_pos);
	check(SV("answer is '       nan'"), SV("answer is '{:-010e}'"), nan_pos);
	check(SV("answer is '      +nan'"), SV("answer is '{:+010e}'"), nan_pos);
	check(SV("answer is '       nan'"), SV("answer is '{: 010e}'"), nan_pos);

	check(SV("answer is '      -nan'"), SV("answer is '{:010e}'"), nan_neg);
	check(SV("answer is '      -nan'"), SV("answer is '{:-010e}'"), nan_neg);
	check(SV("answer is '      -nan'"), SV("answer is '{:+010e}'"), nan_neg);
	check(SV("answer is '      -nan'"), SV("answer is '{: 010e}'"), nan_neg);

	// *** precision ***
	check(SV("answer is '3e-02'"), SV("answer is '{:.0e}'"), 0.03125);
	check(SV("answer is '3.1e-02'"), SV("answer is '{:.1e}'"), 0.03125);
	check(SV("answer is '3.125e-02'"), SV("answer is '{:.3e}'"), 0.03125);
	check(SV("answer is '3.1250000000e-02'"), SV("answer is '{:.10e}'"), 0.03125);
}

template <typename CharT, typename F, typename TestFunction>
void test_floating_point_scientific_upper_case(TestFunction check)
{
	auto nan_pos = hamon::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	check(SV("answer is '   2.500000E-01'"), SV("answer is '{:15E}'"), F(0.25));
	check(SV("answer is '   2.500000E-01'"), SV("answer is '{:>15E}'"), F(0.25));
	check(SV("answer is '2.500000E-01   '"), SV("answer is '{:<15E}'"), F(0.25));
	check(SV("answer is ' 2.500000E-01  '"), SV("answer is '{:^15E}'"), F(0.25));

	check(SV("answer is '---1.250000E-01'"), SV("answer is '{:->15E}'"), F(125e-3));
	check(SV("answer is '1.250000E-01---'"), SV("answer is '{:-<15E}'"), F(125e-3));
	check(SV("answer is '-1.250000E-01--'"), SV("answer is '{:-^15E}'"), F(125e-3));

	check(SV("answer is '***INF'"), SV("answer is '{:*>6E}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is 'INF***'"), SV("answer is '{:*<6E}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '*INF**'"), SV("answer is '{:*^6E}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '###-INF'"), SV("answer is '{:#>7E}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-INF###'"), SV("answer is '{:#<7E}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '#-INF##'"), SV("answer is '{:#^7E}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is '^^^NAN'"), SV("answer is '{:^>6E}'"), nan_pos);
	check(SV("answer is 'NAN^^^'"), SV("answer is '{:^<6E}'"), nan_pos);
	check(SV("answer is '^NAN^^'"), SV("answer is '{:^^6E}'"), nan_pos);

	check(SV("answer is '000-NAN'"), SV("answer is '{:0>7E}'"), nan_neg);
	check(SV("answer is '-NAN000'"), SV("answer is '{:0<7E}'"), nan_neg);
	check(SV("answer is '0-NAN00'"), SV("answer is '{:0^7E}'"), nan_neg);

	// Test whether zero padding is ignored
	check(SV("answer is '   2.500000E-01'"), SV("answer is '{:>015E}'"), F(0.25));
	check(SV("answer is '2.500000E-01   '"), SV("answer is '{:<015E}'"), F(0.25));
	check(SV("answer is ' 2.500000E-01  '"), SV("answer is '{:^015E}'"), F(0.25));

	// *** Sign ***
	check(SV("answer is '0.000000E+00'"), SV("answer is '{:E}'"), F(0));
	check(SV("answer is '0.000000E+00'"), SV("answer is '{:-E}'"), F(0));
	check(SV("answer is '+0.000000E+00'"), SV("answer is '{:+E}'"), F(0));
	check(SV("answer is ' 0.000000E+00'"), SV("answer is '{: E}'"), F(0));

	check(SV("answer is '-0.000000E+00'"), SV("answer is '{:E}'"), F(-0.));
	check(SV("answer is '-0.000000E+00'"), SV("answer is '{:-E}'"), F(-0.));
	check(SV("answer is '-0.000000E+00'"), SV("answer is '{:+E}'"), F(-0.));
	check(SV("answer is '-0.000000E+00'"), SV("answer is '{: E}'"), F(-0.));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	check(SV("answer is 'INF'"), SV("answer is '{:E}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is 'INF'"), SV("answer is '{:-E}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '+INF'"), SV("answer is '{:+E}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is ' INF'"), SV("answer is '{: E}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '-INF'"), SV("answer is '{:E}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-INF'"), SV("answer is '{:-E}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-INF'"), SV("answer is '{:+E}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-INF'"), SV("answer is '{: E}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is 'NAN'"), SV("answer is '{:E}'"), nan_pos);
	check(SV("answer is 'NAN'"), SV("answer is '{:-E}'"), nan_pos);
	check(SV("answer is '+NAN'"), SV("answer is '{:+E}'"), nan_pos);
	check(SV("answer is ' NAN'"), SV("answer is '{: E}'"), nan_pos);

	check(SV("answer is '-NAN'"), SV("answer is '{:E}'"), nan_neg);
	check(SV("answer is '-NAN'"), SV("answer is '{:-E}'"), nan_neg);
	check(SV("answer is '-NAN'"), SV("answer is '{:+E}'"), nan_neg);
	check(SV("answer is '-NAN'"), SV("answer is '{: E}'"), nan_neg);

	// *** alternate form **
	// When precision is zero there's no decimal point except when the alternate form is specified.
	check(SV("answer is '0E+00'"), SV("answer is '{:.0E}'"), F(0));
	check(SV("answer is '0.E+00'"), SV("answer is '{:#.0E}'"), F(0));

	check(SV("answer is '0.000000E+00'"), SV("answer is '{:#E}'"), F(0));
	check(SV("answer is '2.500000E+00'"), SV("answer is '{:#E}'"), F(2.5));

	check(SV("answer is 'INF'"), SV("answer is '{:#E}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-INF'"), SV("answer is '{:#E}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is 'NAN'"), SV("answer is '{:#E}'"), nan_pos);
	check(SV("answer is '-NAN'"), SV("answer is '{:#E}'"), nan_neg);

	// *** zero-padding & width ***
	check(SV("answer is '3.125000E-02'"), SV("answer is '{:07E}'"), 0.03125);
	check(SV("answer is '+3.125000E-02'"), SV("answer is '{:+07E}'"), 0.03125);
	check(SV("answer is '+3.125000E-02'"), SV("answer is '{:+08E}'"), 0.03125);
	check(SV("answer is '+3.125000E-02'"), SV("answer is '{:+09E}'"), 0.03125);

	check(SV("answer is '003.125000E-02'"), SV("answer is '{:014E}'"), 0.03125);
	check(SV("answer is '003.125000E-02'"), SV("answer is '{:-014E}'"), 0.03125);
	check(SV("answer is '+03.125000E-02'"), SV("answer is '{:+014E}'"), 0.03125);
	check(SV("answer is ' 03.125000E-02'"), SV("answer is '{: 014E}'"), 0.03125);

	check(SV("answer is '       INF'"), SV("answer is '{:010E}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '       INF'"), SV("answer is '{:-010E}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      +INF'"), SV("answer is '{:+010E}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '       INF'"), SV("answer is '{: 010E}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '      -INF'"), SV("answer is '{:010E}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -INF'"), SV("answer is '{:-010E}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -INF'"), SV("answer is '{:+010E}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -INF'"), SV("answer is '{: 010E}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is '       NAN'"), SV("answer is '{:010E}'"), nan_pos);
	check(SV("answer is '       NAN'"), SV("answer is '{:-010E}'"), nan_pos);
	check(SV("answer is '      +NAN'"), SV("answer is '{:+010E}'"), nan_pos);
	check(SV("answer is '       NAN'"), SV("answer is '{: 010E}'"), nan_pos);

	check(SV("answer is '      -NAN'"), SV("answer is '{:010E}'"), nan_neg);
	check(SV("answer is '      -NAN'"), SV("answer is '{:-010E}'"), nan_neg);
	check(SV("answer is '      -NAN'"), SV("answer is '{:+010E}'"), nan_neg);
	check(SV("answer is '      -NAN'"), SV("answer is '{: 010E}'"), nan_neg);

	// *** precision ***
	check(SV("answer is '3E-02'"), SV("answer is '{:.0E}'"), 0.03125);
	check(SV("answer is '3.1E-02'"), SV("answer is '{:.1E}'"), 0.03125);
	check(SV("answer is '3.125E-02'"), SV("answer is '{:.3E}'"), 0.03125);
	check(SV("answer is '3.1250000000E-02'"), SV("answer is '{:.10E}'"), 0.03125);
}

template <typename CharT, typename F, typename TestFunction>
void test_floating_point_fixed_lower_case(TestFunction check)
{
	auto nan_pos = hamon::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	check(SV("answer is '   0.250000'"), SV("answer is '{:11f}'"), F(0.25));
	check(SV("answer is '   0.250000'"), SV("answer is '{:>11f}'"), F(0.25));
	check(SV("answer is '0.250000   '"), SV("answer is '{:<11f}'"), F(0.25));
	check(SV("answer is ' 0.250000  '"), SV("answer is '{:^11f}'"), F(0.25));

	check(SV("answer is '---0.125000'"), SV("answer is '{:->11f}'"), F(125e-3));
	check(SV("answer is '0.125000---'"), SV("answer is '{:-<11f}'"), F(125e-3));
	check(SV("answer is '-0.125000--'"), SV("answer is '{:-^11f}'"), F(125e-3));

	check(SV("answer is '***inf'"), SV("answer is '{:*>6f}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is 'inf***'"), SV("answer is '{:*<6f}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '*inf**'"), SV("answer is '{:*^6f}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '###-inf'"), SV("answer is '{:#>7f}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf###'"), SV("answer is '{:#<7f}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '#-inf##'"), SV("answer is '{:#^7f}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is '^^^nan'"), SV("answer is '{:^>6f}'"), nan_pos);
	check(SV("answer is 'nan^^^'"), SV("answer is '{:^<6f}'"), nan_pos);
	check(SV("answer is '^nan^^'"), SV("answer is '{:^^6f}'"), nan_pos);

	check(SV("answer is '000-nan'"), SV("answer is '{:0>7f}'"), nan_neg);
	check(SV("answer is '-nan000'"), SV("answer is '{:0<7f}'"), nan_neg);
	check(SV("answer is '0-nan00'"), SV("answer is '{:0^7f}'"), nan_neg);

	// Test whether zero padding is ignored
	check(SV("answer is '   0.250000'"), SV("answer is '{:>011f}'"), F(0.25));
	check(SV("answer is '0.250000   '"), SV("answer is '{:<011f}'"), F(0.25));
	check(SV("answer is ' 0.250000  '"), SV("answer is '{:^011f}'"), F(0.25));

	// *** Sign ***
	check(SV("answer is '0.000000'"), SV("answer is '{:f}'"), F(0));
	check(SV("answer is '0.000000'"), SV("answer is '{:-f}'"), F(0));
	check(SV("answer is '+0.000000'"), SV("answer is '{:+f}'"), F(0));
	check(SV("answer is ' 0.000000'"), SV("answer is '{: f}'"), F(0));

	check(SV("answer is '-0.000000'"), SV("answer is '{:f}'"), F(-0.));
	check(SV("answer is '-0.000000'"), SV("answer is '{:-f}'"), F(-0.));
	check(SV("answer is '-0.000000'"), SV("answer is '{:+f}'"), F(-0.));
	check(SV("answer is '-0.000000'"), SV("answer is '{: f}'"), F(-0.));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	check(SV("answer is 'inf'"), SV("answer is '{:f}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is 'inf'"), SV("answer is '{:-f}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '+inf'"), SV("answer is '{:+f}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is ' inf'"), SV("answer is '{: f}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '-inf'"), SV("answer is '{:f}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{:-f}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{:+f}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{: f}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is 'nan'"), SV("answer is '{:f}'"), nan_pos);
	check(SV("answer is 'nan'"), SV("answer is '{:-f}'"), nan_pos);
	check(SV("answer is '+nan'"), SV("answer is '{:+f}'"), nan_pos);
	check(SV("answer is ' nan'"), SV("answer is '{: f}'"), nan_pos);

	check(SV("answer is '-nan'"), SV("answer is '{:f}'"), nan_neg);
	check(SV("answer is '-nan'"), SV("answer is '{:-f}'"), nan_neg);
	check(SV("answer is '-nan'"), SV("answer is '{:+f}'"), nan_neg);
	check(SV("answer is '-nan'"), SV("answer is '{: f}'"), nan_neg);

	// *** alternate form **
	// When precision is zero there's no decimal point except when the alternate form is specified.
	check(SV("answer is '0'"), SV("answer is '{:.0f}'"), F(0));
	check(SV("answer is '0.'"), SV("answer is '{:#.0f}'"), F(0));

	check(SV("answer is '0.000000'"), SV("answer is '{:#f}'"), F(0));
	check(SV("answer is '2.500000'"), SV("answer is '{:#f}'"), F(2.5));

	check(SV("answer is 'inf'"), SV("answer is '{:#f}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{:#f}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is 'nan'"), SV("answer is '{:#f}'"), nan_pos);
	check(SV("answer is '-nan'"), SV("answer is '{:#f}'"), nan_neg);

	// *** zero-padding & width ***
	check(SV("answer is '0.031250'"), SV("answer is '{:07f}'"), 0.03125);
	check(SV("answer is '+0.031250'"), SV("answer is '{:+07f}'"), 0.03125);
	check(SV("answer is '+0.031250'"), SV("answer is '{:+08f}'"), 0.03125);
	check(SV("answer is '+0.031250'"), SV("answer is '{:+09f}'"), 0.03125);

	check(SV("answer is '000.031250'"), SV("answer is '{:010f}'"), 0.03125);
	check(SV("answer is '000.031250'"), SV("answer is '{:-010f}'"), 0.03125);
	check(SV("answer is '+00.031250'"), SV("answer is '{:+010f}'"), 0.03125);
	check(SV("answer is ' 00.031250'"), SV("answer is '{: 010f}'"), 0.03125);

	check(SV("answer is '       inf'"), SV("answer is '{:010f}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '       inf'"), SV("answer is '{:-010f}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      +inf'"), SV("answer is '{:+010f}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '       inf'"), SV("answer is '{: 010f}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '      -inf'"), SV("answer is '{:010f}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -inf'"), SV("answer is '{:-010f}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -inf'"), SV("answer is '{:+010f}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -inf'"), SV("answer is '{: 010f}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is '       nan'"), SV("answer is '{:010f}'"), nan_pos);
	check(SV("answer is '       nan'"), SV("answer is '{:-010f}'"), nan_pos);
	check(SV("answer is '      +nan'"), SV("answer is '{:+010f}'"), nan_pos);
	check(SV("answer is '       nan'"), SV("answer is '{: 010f}'"), nan_pos);

	check(SV("answer is '      -nan'"), SV("answer is '{:010f}'"), nan_neg);
	check(SV("answer is '      -nan'"), SV("answer is '{:-010f}'"), nan_neg);
	check(SV("answer is '      -nan'"), SV("answer is '{:+010f}'"), nan_neg);
	check(SV("answer is '      -nan'"), SV("answer is '{: 010f}'"), nan_neg);

	// *** precision ***
	check(SV("answer is '0'"), SV("answer is '{:.0f}'"), 0.03125);
	check(SV("answer is '0.0'"), SV("answer is '{:.1f}'"), 0.03125);
	check(SV("answer is '0.03125'"), SV("answer is '{:.5f}'"), 0.03125);
	check(SV("answer is '0.0312500000'"), SV("answer is '{:.10f}'"), 0.03125);
}

template <typename CharT, typename F, typename TestFunction>
void test_floating_point_fixed_upper_case(TestFunction check)
{
	auto nan_pos = hamon::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	check(SV("answer is '   0.250000'"), SV("answer is '{:11F}'"), F(0.25));
	check(SV("answer is '   0.250000'"), SV("answer is '{:>11F}'"), F(0.25));
	check(SV("answer is '0.250000   '"), SV("answer is '{:<11F}'"), F(0.25));
	check(SV("answer is ' 0.250000  '"), SV("answer is '{:^11F}'"), F(0.25));

	check(SV("answer is '---0.125000'"), SV("answer is '{:->11F}'"), F(125e-3));
	check(SV("answer is '0.125000---'"), SV("answer is '{:-<11F}'"), F(125e-3));
	check(SV("answer is '-0.125000--'"), SV("answer is '{:-^11F}'"), F(125e-3));

	check(SV("answer is '***INF'"), SV("answer is '{:*>6F}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is 'INF***'"), SV("answer is '{:*<6F}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '*INF**'"), SV("answer is '{:*^6F}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '###-INF'"), SV("answer is '{:#>7F}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-INF###'"), SV("answer is '{:#<7F}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '#-INF##'"), SV("answer is '{:#^7F}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is '^^^NAN'"), SV("answer is '{:^>6F}'"), nan_pos);
	check(SV("answer is 'NAN^^^'"), SV("answer is '{:^<6F}'"), nan_pos);
	check(SV("answer is '^NAN^^'"), SV("answer is '{:^^6F}'"), nan_pos);

	check(SV("answer is '000-NAN'"), SV("answer is '{:0>7F}'"), nan_neg);
	check(SV("answer is '-NAN000'"), SV("answer is '{:0<7F}'"), nan_neg);
	check(SV("answer is '0-NAN00'"), SV("answer is '{:0^7F}'"), nan_neg);

	// Test whether zero padding is ignored
	check(SV("answer is '   0.250000'"), SV("answer is '{:>011F}'"), F(0.25));
	check(SV("answer is '0.250000   '"), SV("answer is '{:<011F}'"), F(0.25));
	check(SV("answer is ' 0.250000  '"), SV("answer is '{:^011F}'"), F(0.25));

	// *** Sign ***
	check(SV("answer is '0.000000'"), SV("answer is '{:F}'"), F(0));
	check(SV("answer is '0.000000'"), SV("answer is '{:-F}'"), F(0));
	check(SV("answer is '+0.000000'"), SV("answer is '{:+F}'"), F(0));
	check(SV("answer is ' 0.000000'"), SV("answer is '{: F}'"), F(0));

	check(SV("answer is '-0.000000'"), SV("answer is '{:F}'"), F(-0.));
	check(SV("answer is '-0.000000'"), SV("answer is '{:-F}'"), F(-0.));
	check(SV("answer is '-0.000000'"), SV("answer is '{:+F}'"), F(-0.));
	check(SV("answer is '-0.000000'"), SV("answer is '{: F}'"), F(-0.));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	check(SV("answer is 'INF'"), SV("answer is '{:F}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is 'INF'"), SV("answer is '{:-F}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '+INF'"), SV("answer is '{:+F}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is ' INF'"), SV("answer is '{: F}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '-INF'"), SV("answer is '{:F}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-INF'"), SV("answer is '{:-F}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-INF'"), SV("answer is '{:+F}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-INF'"), SV("answer is '{: F}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is 'NAN'"), SV("answer is '{:F}'"), nan_pos);
	check(SV("answer is 'NAN'"), SV("answer is '{:-F}'"), nan_pos);
	check(SV("answer is '+NAN'"), SV("answer is '{:+F}'"), nan_pos);
	check(SV("answer is ' NAN'"), SV("answer is '{: F}'"), nan_pos);

	check(SV("answer is '-NAN'"), SV("answer is '{:F}'"), nan_neg);
	check(SV("answer is '-NAN'"), SV("answer is '{:-F}'"), nan_neg);
	check(SV("answer is '-NAN'"), SV("answer is '{:+F}'"), nan_neg);
	check(SV("answer is '-NAN'"), SV("answer is '{: F}'"), nan_neg);

	// *** alternate form **
	// When precision is zero there's no decimal point except when the alternate form is specified.
	check(SV("answer is '0'"), SV("answer is '{:.0F}'"), F(0));
	check(SV("answer is '0.'"), SV("answer is '{:#.0F}'"), F(0));

	check(SV("answer is '0.000000'"), SV("answer is '{:#F}'"), F(0));
	check(SV("answer is '2.500000'"), SV("answer is '{:#F}'"), F(2.5));

	check(SV("answer is 'INF'"), SV("answer is '{:#F}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-INF'"), SV("answer is '{:#F}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is 'NAN'"), SV("answer is '{:#F}'"), nan_pos);
	check(SV("answer is '-NAN'"), SV("answer is '{:#F}'"), nan_neg);

	// *** zero-padding & width ***
	check(SV("answer is '0.031250'"), SV("answer is '{:07F}'"), 0.03125);
	check(SV("answer is '+0.031250'"), SV("answer is '{:+07F}'"), 0.03125);
	check(SV("answer is '+0.031250'"), SV("answer is '{:+08F}'"), 0.03125);
	check(SV("answer is '+0.031250'"), SV("answer is '{:+09F}'"), 0.03125);

	check(SV("answer is '000.031250'"), SV("answer is '{:010F}'"), 0.03125);
	check(SV("answer is '000.031250'"), SV("answer is '{:-010F}'"), 0.03125);
	check(SV("answer is '+00.031250'"), SV("answer is '{:+010F}'"), 0.03125);
	check(SV("answer is ' 00.031250'"), SV("answer is '{: 010F}'"), 0.03125);

	check(SV("answer is '       INF'"), SV("answer is '{:010F}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '       INF'"), SV("answer is '{:-010F}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      +INF'"), SV("answer is '{:+010F}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '       INF'"), SV("answer is '{: 010F}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '      -INF'"), SV("answer is '{:010F}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -INF'"), SV("answer is '{:-010F}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -INF'"), SV("answer is '{:+010F}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -INF'"), SV("answer is '{: 010F}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is '       NAN'"), SV("answer is '{:010F}'"), nan_pos);
	check(SV("answer is '       NAN'"), SV("answer is '{:-010F}'"), nan_pos);
	check(SV("answer is '      +NAN'"), SV("answer is '{:+010F}'"), nan_pos);
	check(SV("answer is '       NAN'"), SV("answer is '{: 010F}'"), nan_pos);

	check(SV("answer is '      -NAN'"), SV("answer is '{:010F}'"), nan_neg);
	check(SV("answer is '      -NAN'"), SV("answer is '{:-010F}'"), nan_neg);
	check(SV("answer is '      -NAN'"), SV("answer is '{:+010F}'"), nan_neg);
	check(SV("answer is '      -NAN'"), SV("answer is '{: 010F}'"), nan_neg);

	// *** precision ***
	check(SV("answer is '0'"), SV("answer is '{:.0F}'"), 0.03125);
	check(SV("answer is '0.0'"), SV("answer is '{:.1F}'"), 0.03125);
	check(SV("answer is '0.03125'"), SV("answer is '{:.5F}'"), 0.03125);
	check(SV("answer is '0.0312500000'"), SV("answer is '{:.10F}'"), 0.03125);
}

template <typename CharT, typename F, typename TestFunction>
void test_floating_point_general_lower_case(TestFunction check)
{
	auto nan_pos = hamon::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	check(SV("answer is '   0.25'"), SV("answer is '{:7g}'"), F(0.25));
	check(SV("answer is '   0.25'"), SV("answer is '{:>7g}'"), F(0.25));
	check(SV("answer is '0.25   '"), SV("answer is '{:<7g}'"), F(0.25));
	check(SV("answer is ' 0.25  '"), SV("answer is '{:^7g}'"), F(0.25));

	check(SV("answer is '---0.125'"), SV("answer is '{:->8g}'"), F(125e-3));
	check(SV("answer is '0.125---'"), SV("answer is '{:-<8g}'"), F(125e-3));
	check(SV("answer is '-0.125--'"), SV("answer is '{:-^8g}'"), F(125e-3));

	check(SV("answer is '***inf'"), SV("answer is '{:*>6g}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is 'inf***'"), SV("answer is '{:*<6g}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '*inf**'"), SV("answer is '{:*^6g}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '###-inf'"), SV("answer is '{:#>7g}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf###'"), SV("answer is '{:#<7g}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '#-inf##'"), SV("answer is '{:#^7g}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is '^^^nan'"), SV("answer is '{:^>6g}'"), nan_pos);
	check(SV("answer is 'nan^^^'"), SV("answer is '{:^<6g}'"), nan_pos);
	check(SV("answer is '^nan^^'"), SV("answer is '{:^^6g}'"), nan_pos);

	check(SV("answer is '000-nan'"), SV("answer is '{:0>7g}'"), nan_neg);
	check(SV("answer is '-nan000'"), SV("answer is '{:0<7g}'"), nan_neg);
	check(SV("answer is '0-nan00'"), SV("answer is '{:0^7g}'"), nan_neg);

	// Test whether zero padding is ignored
	check(SV("answer is '   0.25'"), SV("answer is '{:>07g}'"), F(0.25));
	check(SV("answer is '0.25   '"), SV("answer is '{:<07g}'"), F(0.25));
	check(SV("answer is ' 0.25  '"), SV("answer is '{:^07g}'"), F(0.25));

	// *** Sign ***
	check(SV("answer is '0'"), SV("answer is '{:g}'"), F(0));
	check(SV("answer is '0'"), SV("answer is '{:-g}'"), F(0));
	check(SV("answer is '+0'"), SV("answer is '{:+g}'"), F(0));
	check(SV("answer is ' 0'"), SV("answer is '{: g}'"), F(0));

	check(SV("answer is '-0'"), SV("answer is '{:g}'"), F(-0.));
	check(SV("answer is '-0'"), SV("answer is '{:-g}'"), F(-0.));
	check(SV("answer is '-0'"), SV("answer is '{:+g}'"), F(-0.));
	check(SV("answer is '-0'"), SV("answer is '{: g}'"), F(-0.));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	check(SV("answer is 'inf'"), SV("answer is '{:g}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is 'inf'"), SV("answer is '{:-g}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '+inf'"), SV("answer is '{:+g}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is ' inf'"), SV("answer is '{: g}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '-inf'"), SV("answer is '{:g}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{:-g}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{:+g}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{: g}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is 'nan'"), SV("answer is '{:g}'"), nan_pos);
	check(SV("answer is 'nan'"), SV("answer is '{:-g}'"), nan_pos);
	check(SV("answer is '+nan'"), SV("answer is '{:+g}'"), nan_pos);
	check(SV("answer is ' nan'"), SV("answer is '{: g}'"), nan_pos);

	check(SV("answer is '-nan'"), SV("answer is '{:g}'"), nan_neg);
	check(SV("answer is '-nan'"), SV("answer is '{:-g}'"), nan_neg);
	check(SV("answer is '-nan'"), SV("answer is '{:+g}'"), nan_neg);
	check(SV("answer is '-nan'"), SV("answer is '{: g}'"), nan_neg);

	// *** alternate form **
	// When precision is zero there's no decimal point except when the alternate form is specified.
	check(SV("answer is '0'"), SV("answer is '{:.0g}'"), F(0));
	check(SV("answer is '0.'"), SV("answer is '{:#.0g}'"), F(0));

	check(SV("answer is '0.00000'"), SV("answer is '{:#g}'"), F(0));
	check(SV("answer is '2.50000'"), SV("answer is '{:#g}'"), F(2.5));

	check(SV("answer is 'inf'"), SV("answer is '{:#g}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{:#g}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is 'nan'"), SV("answer is '{:#g}'"), nan_pos);
	check(SV("answer is '-nan'"), SV("answer is '{:#g}'"), nan_neg);

	// *** zero-padding & width ***
	check(SV("answer is '0.03125'"), SV("answer is '{:06g}'"), 0.03125);
	check(SV("answer is '+0.03125'"), SV("answer is '{:+06g}'"), 0.03125);
	check(SV("answer is '+0.03125'"), SV("answer is '{:+07g}'"), 0.03125);
	check(SV("answer is '+0.03125'"), SV("answer is '{:+08g}'"), 0.03125);

	check(SV("answer is '000.03125'"), SV("answer is '{:09g}'"), 0.03125);
	check(SV("answer is '000.03125'"), SV("answer is '{:-09g}'"), 0.03125);
	check(SV("answer is '+00.03125'"), SV("answer is '{:+09g}'"), 0.03125);
	check(SV("answer is ' 00.03125'"), SV("answer is '{: 09g}'"), 0.03125);

	check(SV("answer is '       inf'"), SV("answer is '{:010g}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '       inf'"), SV("answer is '{:-010g}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      +inf'"), SV("answer is '{:+010g}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '       inf'"), SV("answer is '{: 010g}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '      -inf'"), SV("answer is '{:010g}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -inf'"), SV("answer is '{:-010g}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -inf'"), SV("answer is '{:+010g}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -inf'"), SV("answer is '{: 010g}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is '       nan'"), SV("answer is '{:010g}'"), nan_pos);
	check(SV("answer is '       nan'"), SV("answer is '{:-010g}'"), nan_pos);
	check(SV("answer is '      +nan'"), SV("answer is '{:+010g}'"), nan_pos);
	check(SV("answer is '       nan'"), SV("answer is '{: 010g}'"), nan_pos);

	check(SV("answer is '      -nan'"), SV("answer is '{:010g}'"), nan_neg);
	check(SV("answer is '      -nan'"), SV("answer is '{:-010g}'"), nan_neg);
	check(SV("answer is '      -nan'"), SV("answer is '{:+010g}'"), nan_neg);
	check(SV("answer is '      -nan'"), SV("answer is '{: 010g}'"), nan_neg);

	// *** precision ***
	check(SV("answer is '0.03'"), SV("answer is '{:.0g}'"), 0.03125);
	check(SV("answer is '0.03'"), SV("answer is '{:.1g}'"), 0.03125);
	check(SV("answer is '0.031'"), SV("answer is '{:.2g}'"), 0.03125);
	check(SV("answer is '0.0312'"), SV("answer is '{:.3g}'"), 0.03125);
	check(SV("answer is '0.03125'"), SV("answer is '{:.4g}'"), 0.03125);
	check(SV("answer is '0.03125'"), SV("answer is '{:.5g}'"), 0.03125);
	check(SV("answer is '0.03125'"), SV("answer is '{:.10g}'"), 0.03125);

	// *** precision & alternate form ***

	// Output validated with  printf("%#xg")
	check(SV("answer is '1.'"), SV("answer is '{:#.{}g}'"), 1.2, 0);
	check(SV("answer is '1.'"), SV("answer is '{:#.{}g}'"), 1.2, 1);
	check(SV("answer is '1.2'"), SV("answer is '{:#.{}g}'"), 1.2, 2);
	check(SV("answer is '1.20'"), SV("answer is '{:#.{}g}'"), 1.2, 3);
	check(SV("answer is '1.200'"), SV("answer is '{:#.{}g}'"), 1.2, 4);
	check(SV("answer is '1.2000'"), SV("answer is '{:#.{}g}'"), 1.2, 5);
	check(SV("answer is '1.20000'"), SV("answer is '{:#.{}g}'"), 1.2, 6);

	check(SV("answer is '1.e+03'"), SV("answer is '{:#.{}g}'"), 1200.0, 0);
	check(SV("answer is '1.e+03'"), SV("answer is '{:#.{}g}'"), 1200.0, 1);
	check(SV("answer is '1.2e+03'"), SV("answer is '{:#.{}g}'"), 1200.0, 2);
	check(SV("answer is '1.20e+03'"), SV("answer is '{:#.{}g}'"), 1200.0, 3);
	check(SV("answer is '1200.'"), SV("answer is '{:#.{}g}'"), 1200.0, 4);
	check(SV("answer is '1200.0'"), SV("answer is '{:#.{}g}'"), 1200.0, 5);
	check(SV("answer is '1200.00'"), SV("answer is '{:#.{}g}'"), 1200.0, 6);

	check(SV("answer is '1.e+06'"), SV("answer is '{:#.{}g}'"), 1200000.0, 0);
	check(SV("answer is '1.e+06'"), SV("answer is '{:#.{}g}'"), 1200000.0, 1);
	check(SV("answer is '1.2e+06'"), SV("answer is '{:#.{}g}'"), 1200000.0, 2);
	check(SV("answer is '1.20e+06'"), SV("answer is '{:#.{}g}'"), 1200000.0, 3);
	check(SV("answer is '1.200e+06'"), SV("answer is '{:#.{}g}'"), 1200000.0, 4);
	check(SV("answer is '1.2000e+06'"), SV("answer is '{:#.{}g}'"), 1200000.0, 5);
	check(SV("answer is '1.20000e+06'"), SV("answer is '{:#.{}g}'"), 1200000.0, 6);
}

template <typename CharT, typename F, typename TestFunction>
void test_floating_point_general_upper_case(TestFunction check)
{
	auto nan_pos = hamon::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	check(SV("answer is '   0.25'"), SV("answer is '{:7G}'"), F(0.25));
	check(SV("answer is '   0.25'"), SV("answer is '{:>7G}'"), F(0.25));
	check(SV("answer is '0.25   '"), SV("answer is '{:<7G}'"), F(0.25));
	check(SV("answer is ' 0.25  '"), SV("answer is '{:^7G}'"), F(0.25));

	check(SV("answer is '---0.125'"), SV("answer is '{:->8G}'"), F(125e-3));
	check(SV("answer is '0.125---'"), SV("answer is '{:-<8G}'"), F(125e-3));
	check(SV("answer is '-0.125--'"), SV("answer is '{:-^8G}'"), F(125e-3));

	check(SV("answer is '***INF'"), SV("answer is '{:*>6G}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is 'INF***'"), SV("answer is '{:*<6G}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '*INF**'"), SV("answer is '{:*^6G}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '###-INF'"), SV("answer is '{:#>7G}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-INF###'"), SV("answer is '{:#<7G}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '#-INF##'"), SV("answer is '{:#^7G}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is '^^^NAN'"), SV("answer is '{:^>6G}'"), nan_pos);
	check(SV("answer is 'NAN^^^'"), SV("answer is '{:^<6G}'"), nan_pos);
	check(SV("answer is '^NAN^^'"), SV("answer is '{:^^6G}'"), nan_pos);

	check(SV("answer is '000-NAN'"), SV("answer is '{:0>7G}'"), nan_neg);
	check(SV("answer is '-NAN000'"), SV("answer is '{:0<7G}'"), nan_neg);
	check(SV("answer is '0-NAN00'"), SV("answer is '{:0^7G}'"), nan_neg);

	// Test whether zero padding is ignored
	check(SV("answer is '   0.25'"), SV("answer is '{:>07G}'"), F(0.25));
	check(SV("answer is '0.25   '"), SV("answer is '{:<07G}'"), F(0.25));
	check(SV("answer is ' 0.25  '"), SV("answer is '{:^07G}'"), F(0.25));

	// *** Sign ***
	check(SV("answer is '0'"), SV("answer is '{:G}'"), F(0));
	check(SV("answer is '0'"), SV("answer is '{:-G}'"), F(0));
	check(SV("answer is '+0'"), SV("answer is '{:+G}'"), F(0));
	check(SV("answer is ' 0'"), SV("answer is '{: G}'"), F(0));

	check(SV("answer is '-0'"), SV("answer is '{:G}'"), F(-0.));
	check(SV("answer is '-0'"), SV("answer is '{:-G}'"), F(-0.));
	check(SV("answer is '-0'"), SV("answer is '{:+G}'"), F(-0.));
	check(SV("answer is '-0'"), SV("answer is '{: G}'"), F(-0.));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	check(SV("answer is 'INF'"), SV("answer is '{:G}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is 'INF'"), SV("answer is '{:-G}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '+INF'"), SV("answer is '{:+G}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is ' INF'"), SV("answer is '{: G}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '-INF'"), SV("answer is '{:G}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-INF'"), SV("answer is '{:-G}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-INF'"), SV("answer is '{:+G}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-INF'"), SV("answer is '{: G}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is 'NAN'"), SV("answer is '{:G}'"), nan_pos);
	check(SV("answer is 'NAN'"), SV("answer is '{:-G}'"), nan_pos);
	check(SV("answer is '+NAN'"), SV("answer is '{:+G}'"), nan_pos);
	check(SV("answer is ' NAN'"), SV("answer is '{: G}'"), nan_pos);

	check(SV("answer is '-NAN'"), SV("answer is '{:G}'"), nan_neg);
	check(SV("answer is '-NAN'"), SV("answer is '{:-G}'"), nan_neg);
	check(SV("answer is '-NAN'"), SV("answer is '{:+G}'"), nan_neg);
	check(SV("answer is '-NAN'"), SV("answer is '{: G}'"), nan_neg);

	// *** alternate form **
	// When precision is zero there's no decimal point except when the alternate form is specified.
	check(SV("answer is '0'"), SV("answer is '{:.0G}'"), F(0));
	check(SV("answer is '0.'"), SV("answer is '{:#.0G}'"), F(0));

	check(SV("answer is '0.00000'"), SV("answer is '{:#G}'"), F(0));
	check(SV("answer is '2.50000'"), SV("answer is '{:#G}'"), F(2.5));

	check(SV("answer is 'INF'"), SV("answer is '{:#G}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-INF'"), SV("answer is '{:#G}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is 'NAN'"), SV("answer is '{:#G}'"), nan_pos);
	check(SV("answer is '-NAN'"), SV("answer is '{:#G}'"), nan_neg);

	// *** zero-padding & width ***
	check(SV("answer is '0.03125'"), SV("answer is '{:06G}'"), 0.03125);
	check(SV("answer is '+0.03125'"), SV("answer is '{:+06G}'"), 0.03125);
	check(SV("answer is '+0.03125'"), SV("answer is '{:+07G}'"), 0.03125);
	check(SV("answer is '+0.03125'"), SV("answer is '{:+08G}'"), 0.03125);

	check(SV("answer is '000.03125'"), SV("answer is '{:09G}'"), 0.03125);
	check(SV("answer is '000.03125'"), SV("answer is '{:-09G}'"), 0.03125);
	check(SV("answer is '+00.03125'"), SV("answer is '{:+09G}'"), 0.03125);
	check(SV("answer is ' 00.03125'"), SV("answer is '{: 09G}'"), 0.03125);

	check(SV("answer is '       INF'"), SV("answer is '{:010G}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '       INF'"), SV("answer is '{:-010G}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      +INF'"), SV("answer is '{:+010G}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '       INF'"), SV("answer is '{: 010G}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '      -INF'"), SV("answer is '{:010G}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -INF'"), SV("answer is '{:-010G}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -INF'"), SV("answer is '{:+010G}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -INF'"), SV("answer is '{: 010G}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is '       NAN'"), SV("answer is '{:010G}'"), nan_pos);
	check(SV("answer is '       NAN'"), SV("answer is '{:-010G}'"), nan_pos);
	check(SV("answer is '      +NAN'"), SV("answer is '{:+010G}'"), nan_pos);
	check(SV("answer is '       NAN'"), SV("answer is '{: 010G}'"), nan_pos);

	check(SV("answer is '      -NAN'"), SV("answer is '{:010G}'"), nan_neg);
	check(SV("answer is '      -NAN'"), SV("answer is '{:-010G}'"), nan_neg);
	check(SV("answer is '      -NAN'"), SV("answer is '{:+010G}'"), nan_neg);
	check(SV("answer is '      -NAN'"), SV("answer is '{: 010G}'"), nan_neg);

	// *** precision ***
	check(SV("answer is '0.03'"), SV("answer is '{:.0G}'"), 0.03125);
	check(SV("answer is '0.03'"), SV("answer is '{:.1G}'"), 0.03125);
	check(SV("answer is '0.031'"), SV("answer is '{:.2G}'"), 0.03125);
	check(SV("answer is '0.0312'"), SV("answer is '{:.3G}'"), 0.03125);
	check(SV("answer is '0.03125'"), SV("answer is '{:.4G}'"), 0.03125);
	check(SV("answer is '0.03125'"), SV("answer is '{:.5G}'"), 0.03125);
	check(SV("answer is '0.03125'"), SV("answer is '{:.10G}'"), 0.03125);

	// *** precision & alternate form ***

	// Output validated with  printf("%#xg")
	check(SV("answer is '1.'"), SV("answer is '{:#.{}G}'"), 1.2, 0);
	check(SV("answer is '1.'"), SV("answer is '{:#.{}G}'"), 1.2, 1);
	check(SV("answer is '1.2'"), SV("answer is '{:#.{}G}'"), 1.2, 2);
	check(SV("answer is '1.20'"), SV("answer is '{:#.{}G}'"), 1.2, 3);
	check(SV("answer is '1.200'"), SV("answer is '{:#.{}G}'"), 1.2, 4);
	check(SV("answer is '1.2000'"), SV("answer is '{:#.{}G}'"), 1.2, 5);
	check(SV("answer is '1.20000'"), SV("answer is '{:#.{}G}'"), 1.2, 6);

	check(SV("answer is '1.E+03'"), SV("answer is '{:#.{}G}'"), 1200.0, 0);
	check(SV("answer is '1.E+03'"), SV("answer is '{:#.{}G}'"), 1200.0, 1);
	check(SV("answer is '1.2E+03'"), SV("answer is '{:#.{}G}'"), 1200.0, 2);
	check(SV("answer is '1.20E+03'"), SV("answer is '{:#.{}G}'"), 1200.0, 3);
	check(SV("answer is '1200.'"), SV("answer is '{:#.{}G}'"), 1200.0, 4);
	check(SV("answer is '1200.0'"), SV("answer is '{:#.{}G}'"), 1200.0, 5);
	check(SV("answer is '1200.00'"), SV("answer is '{:#.{}G}'"), 1200.0, 6);

	check(SV("answer is '1.E+06'"), SV("answer is '{:#.{}G}'"), 1200000.0, 0);
	check(SV("answer is '1.E+06'"), SV("answer is '{:#.{}G}'"), 1200000.0, 1);
	check(SV("answer is '1.2E+06'"), SV("answer is '{:#.{}G}'"), 1200000.0, 2);
	check(SV("answer is '1.20E+06'"), SV("answer is '{:#.{}G}'"), 1200000.0, 3);
	check(SV("answer is '1.200E+06'"), SV("answer is '{:#.{}G}'"), 1200000.0, 4);
	check(SV("answer is '1.2000E+06'"), SV("answer is '{:#.{}G}'"), 1200000.0, 5);
	check(SV("answer is '1.20000E+06'"), SV("answer is '{:#.{}G}'"), 1200000.0, 6);
}

template <typename CharT, typename F, typename TestFunction>
void test_floating_point_default(TestFunction check)
{
	auto nan_pos = hamon::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	check(SV("answer is '   0.25'"), SV("answer is '{:7}'"), F(0.25));
	check(SV("answer is '   0.25'"), SV("answer is '{:>7}'"), F(0.25));
	check(SV("answer is '0.25   '"), SV("answer is '{:<7}'"), F(0.25));
	check(SV("answer is ' 0.25  '"), SV("answer is '{:^7}'"), F(0.25));

	check(SV("answer is '---0.125'"), SV("answer is '{:->8}'"), F(125e-3));
	check(SV("answer is '0.125---'"), SV("answer is '{:-<8}'"), F(125e-3));
	check(SV("answer is '-0.125--'"), SV("answer is '{:-^8}'"), F(125e-3));

	check(SV("answer is '***inf'"), SV("answer is '{:*>6}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is 'inf***'"), SV("answer is '{:*<6}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '*inf**'"), SV("answer is '{:*^6}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '###-inf'"), SV("answer is '{:#>7}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf###'"), SV("answer is '{:#<7}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '#-inf##'"), SV("answer is '{:#^7}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is '^^^nan'"), SV("answer is '{:^>6}'"), nan_pos);
	check(SV("answer is 'nan^^^'"), SV("answer is '{:^<6}'"), nan_pos);
	check(SV("answer is '^nan^^'"), SV("answer is '{:^^6}'"), nan_pos);

	check(SV("answer is '000-nan'"), SV("answer is '{:0>7}'"), nan_neg);
	check(SV("answer is '-nan000'"), SV("answer is '{:0<7}'"), nan_neg);
	check(SV("answer is '0-nan00'"), SV("answer is '{:0^7}'"), nan_neg);

	// Test whether zero padding is ignored
	check(SV("answer is '   0.25'"), SV("answer is '{:>07}'"), F(0.25));
	check(SV("answer is '0.25   '"), SV("answer is '{:<07}'"), F(0.25));
	check(SV("answer is ' 0.25  '"), SV("answer is '{:^07}'"), F(0.25));

	// *** Sign ***
	check(SV("answer is '0'"), SV("answer is '{:}'"), F(0));
	check(SV("answer is '0'"), SV("answer is '{:-}'"), F(0));
	check(SV("answer is '+0'"), SV("answer is '{:+}'"), F(0));
	check(SV("answer is ' 0'"), SV("answer is '{: }'"), F(0));

	check(SV("answer is '-0'"), SV("answer is '{:}'"), F(-0.));
	check(SV("answer is '-0'"), SV("answer is '{:-}'"), F(-0.));
	check(SV("answer is '-0'"), SV("answer is '{:+}'"), F(-0.));
	check(SV("answer is '-0'"), SV("answer is '{: }'"), F(-0.));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	check(SV("answer is 'inf'"), SV("answer is '{:}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is 'inf'"), SV("answer is '{:-}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '+inf'"), SV("answer is '{:+}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is ' inf'"), SV("answer is '{: }'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '-inf'"), SV("answer is '{:}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{:-}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{:+}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{: }'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is 'nan'"), SV("answer is '{:}'"), nan_pos);
	check(SV("answer is 'nan'"), SV("answer is '{:-}'"), nan_pos);
	check(SV("answer is '+nan'"), SV("answer is '{:+}'"), nan_pos);
	check(SV("answer is ' nan'"), SV("answer is '{: }'"), nan_pos);

	check(SV("answer is '-nan'"), SV("answer is '{:}'"), nan_neg);
	check(SV("answer is '-nan'"), SV("answer is '{:-}'"), nan_neg);
	check(SV("answer is '-nan'"), SV("answer is '{:+}'"), nan_neg);
	check(SV("answer is '-nan'"), SV("answer is '{: }'"), nan_neg);

	// *** alternate form ***
	check(SV("answer is '0.'"), SV("answer is '{:#}'"), F(0));
	check(SV("answer is '2.5'"), SV("answer is '{:#}'"), F(2.5));

	check(SV("answer is 'inf'"), SV("answer is '{:#}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{:#}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is 'nan'"), SV("answer is '{:#}'"), nan_pos);
	check(SV("answer is '-nan'"), SV("answer is '{:#}'"), nan_neg);

	// *** zero-padding & width ***
	check(SV("answer is '0.03125'"), SV("answer is '{:07}'"), 0.03125);
	check(SV("answer is '+0.03125'"), SV("answer is '{:+07}'"), 0.03125);
	check(SV("answer is '+0.03125'"), SV("answer is '{:+08}'"), 0.03125);
	check(SV("answer is '+00.03125'"), SV("answer is '{:+09}'"), 0.03125);

	check(SV("answer is '0000.03125'"), SV("answer is '{:010}'"), 0.03125);
	check(SV("answer is '0000.03125'"), SV("answer is '{:-010}'"), 0.03125);
	check(SV("answer is '+000.03125'"), SV("answer is '{:+010}'"), 0.03125);
	check(SV("answer is ' 000.03125'"), SV("answer is '{: 010}'"), 0.03125);

	check(SV("answer is '       inf'"), SV("answer is '{:010}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '       inf'"), SV("answer is '{:-010}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      +inf'"), SV("answer is '{:+010}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '       inf'"), SV("answer is '{: 010}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '      -inf'"), SV("answer is '{:010}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -inf'"), SV("answer is '{:-010}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -inf'"), SV("answer is '{:+010}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -inf'"), SV("answer is '{: 010}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is '       nan'"), SV("answer is '{:010}'"), nan_pos);
	check(SV("answer is '       nan'"), SV("answer is '{:-010}'"), nan_pos);
	check(SV("answer is '      +nan'"), SV("answer is '{:+010}'"), nan_pos);
	check(SV("answer is '       nan'"), SV("answer is '{: 010}'"), nan_pos);

	check(SV("answer is '      -nan'"), SV("answer is '{:010}'"), nan_neg);
	check(SV("answer is '      -nan'"), SV("answer is '{:-010}'"), nan_neg);
	check(SV("answer is '      -nan'"), SV("answer is '{:+010}'"), nan_neg);
	check(SV("answer is '      -nan'"), SV("answer is '{: 010}'"), nan_neg);
}

template <typename CharT, typename F, typename TestFunction>
void test_floating_point_default_precision(TestFunction check)
{
	auto nan_pos = hamon::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	check(SV("answer is '   0.25'"), SV("answer is '{:7.6}'"), F(0.25));
	check(SV("answer is '   0.25'"), SV("answer is '{:>7.6}'"), F(0.25));
	check(SV("answer is '0.25   '"), SV("answer is '{:<7.6}'"), F(0.25));
	check(SV("answer is ' 0.25  '"), SV("answer is '{:^7.6}'"), F(0.25));

	check(SV("answer is '---0.125'"), SV("answer is '{:->8.6}'"), F(125e-3));
	check(SV("answer is '0.125---'"), SV("answer is '{:-<8.6}'"), F(125e-3));
	check(SV("answer is '-0.125--'"), SV("answer is '{:-^8.6}'"), F(125e-3));

	check(SV("answer is '***inf'"), SV("answer is '{:*>6.6}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is 'inf***'"), SV("answer is '{:*<6.6}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '*inf**'"), SV("answer is '{:*^6.6}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '###-inf'"), SV("answer is '{:#>7.6}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf###'"), SV("answer is '{:#<7.6}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '#-inf##'"), SV("answer is '{:#^7.6}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is '^^^nan'"), SV("answer is '{:^>6.6}'"), nan_pos);
	check(SV("answer is 'nan^^^'"), SV("answer is '{:^<6.6}'"), nan_pos);
	check(SV("answer is '^nan^^'"), SV("answer is '{:^^6.6}'"), nan_pos);

	check(SV("answer is '000-nan'"), SV("answer is '{:0>7.6}'"), nan_neg);
	check(SV("answer is '-nan000'"), SV("answer is '{:0<7.6}'"), nan_neg);
	check(SV("answer is '0-nan00'"), SV("answer is '{:0^7.6}'"), nan_neg);

	// Test whether zero padding is ignored
	check(SV("answer is '   0.25'"), SV("answer is '{:>07.6}'"), F(0.25));
	check(SV("answer is '0.25   '"), SV("answer is '{:<07.6}'"), F(0.25));
	check(SV("answer is ' 0.25  '"), SV("answer is '{:^07.6}'"), F(0.25));

	// *** Sign ***
	check(SV("answer is '0'"), SV("answer is '{:.6}'"), F(0));
	check(SV("answer is '0'"), SV("answer is '{:-.6}'"), F(0));
	check(SV("answer is '+0'"), SV("answer is '{:+.6}'"), F(0));
	check(SV("answer is ' 0'"), SV("answer is '{: .6}'"), F(0));

	check(SV("answer is '-0'"), SV("answer is '{:.6}'"), F(-0.));
	check(SV("answer is '-0'"), SV("answer is '{:-.6}'"), F(-0.));
	check(SV("answer is '-0'"), SV("answer is '{:+.6}'"), F(-0.));
	check(SV("answer is '-0'"), SV("answer is '{: .6}'"), F(-0.));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	check(SV("answer is 'inf'"), SV("answer is '{:.6}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is 'inf'"), SV("answer is '{:-.6}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '+inf'"), SV("answer is '{:+.6}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is ' inf'"), SV("answer is '{: .6}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '-inf'"), SV("answer is '{:.6}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{:-.6}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{:+.6}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{: .6}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is 'nan'"), SV("answer is '{:.6}'"), nan_pos);
	check(SV("answer is 'nan'"), SV("answer is '{:-.6}'"), nan_pos);
	check(SV("answer is '+nan'"), SV("answer is '{:+.6}'"), nan_pos);
	check(SV("answer is ' nan'"), SV("answer is '{: .6}'"), nan_pos);

	check(SV("answer is '-nan'"), SV("answer is '{:.6}'"), nan_neg);
	check(SV("answer is '-nan'"), SV("answer is '{:-.6}'"), nan_neg);
	check(SV("answer is '-nan'"), SV("answer is '{:+.6}'"), nan_neg);
	check(SV("answer is '-nan'"), SV("answer is '{: .6}'"), nan_neg);

	// *** alternate form **
	// When precision is zero there's no decimal point except when the alternate form is specified.
	// Note unlike the g and G option the trailing zeros are still removed.
	check(SV("answer is '0'"), SV("answer is '{:.0}'"), F(0));
	check(SV("answer is '0.'"), SV("answer is '{:#.0}'"), F(0));

	check(SV("answer is '0.'"), SV("answer is '{:#.6}'"), F(0));
	check(SV("answer is '2.5'"), SV("answer is '{:#.6}'"), F(2.5));

	check(SV("answer is 'inf'"), SV("answer is '{:#.6}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '-inf'"), SV("answer is '{:#.6}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is 'nan'"), SV("answer is '{:#.6}'"), nan_pos);
	check(SV("answer is '-nan'"), SV("answer is '{:#.6}'"), nan_neg);

	// *** zero-padding & width ***
	check(SV("answer is '0.03125'"), SV("answer is '{:06.6}'"), 0.03125);
	check(SV("answer is '+0.03125'"), SV("answer is '{:+06.6}'"), 0.03125);
	check(SV("answer is '+0.03125'"), SV("answer is '{:+07.6}'"), 0.03125);
	check(SV("answer is '+0.03125'"), SV("answer is '{:+08.6}'"), 0.03125);

	check(SV("answer is '000.03125'"), SV("answer is '{:09.6}'"), 0.03125);
	check(SV("answer is '000.03125'"), SV("answer is '{:-09.6}'"), 0.03125);
	check(SV("answer is '+00.03125'"), SV("answer is '{:+09.6}'"), 0.03125);
	check(SV("answer is ' 00.03125'"), SV("answer is '{: 09.6}'"), 0.03125);

	check(SV("answer is '       inf'"), SV("answer is '{:010.6}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '       inf'"), SV("answer is '{:-010.6}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      +inf'"), SV("answer is '{:+010.6}'"), hamon::numeric_limits<F>::infinity());
	check(SV("answer is '       inf'"), SV("answer is '{: 010.6}'"), hamon::numeric_limits<F>::infinity());

	check(SV("answer is '      -inf'"), SV("answer is '{:010.6}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -inf'"), SV("answer is '{:-010.6}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -inf'"), SV("answer is '{:+010.6}'"), -hamon::numeric_limits<F>::infinity());
	check(SV("answer is '      -inf'"), SV("answer is '{: 010.6}'"), -hamon::numeric_limits<F>::infinity());

	check(SV("answer is '       nan'"), SV("answer is '{:010.6}'"), nan_pos);
	check(SV("answer is '       nan'"), SV("answer is '{:-010.6}'"), nan_pos);
	check(SV("answer is '      +nan'"), SV("answer is '{:+010.6}'"), nan_pos);
	check(SV("answer is '       nan'"), SV("answer is '{: 010.6}'"), nan_pos);

	check(SV("answer is '      -nan'"), SV("answer is '{:010.6}'"), nan_neg);
	check(SV("answer is '      -nan'"), SV("answer is '{:-010.6}'"), nan_neg);
	check(SV("answer is '      -nan'"), SV("answer is '{:+010.6}'"), nan_neg);
	check(SV("answer is '      -nan'"), SV("answer is '{: 010.6}'"), nan_neg);

	// *** precision ***
	check(SV("answer is '0.03'"), SV("answer is '{:.0}'"), 0.03125);
	check(SV("answer is '0.03'"), SV("answer is '{:.1}'"), 0.03125);
	check(SV("answer is '0.031'"), SV("answer is '{:.2}'"), 0.03125);
	check(SV("answer is '0.0312'"), SV("answer is '{:.3}'"), 0.03125);
	check(SV("answer is '0.03125'"), SV("answer is '{:.4}'"), 0.03125);
	check(SV("answer is '0.03125'"), SV("answer is '{:.5}'"), 0.03125);
	check(SV("answer is '0.03125'"), SV("answer is '{:.10}'"), 0.03125);

	// *** precision & alternate form ***

	check(SV("answer is '1.'"), SV("answer is '{:#.{}}'"), 1.2, 0);
	check(SV("answer is '1.'"), SV("answer is '{:#.{}}'"), 1.2, 1);
	check(SV("answer is '1.2'"), SV("answer is '{:#.{}}'"), 1.2, 2);
	check(SV("answer is '1.2'"), SV("answer is '{:#.{}}'"), 1.2, 3);
	check(SV("answer is '1.2'"), SV("answer is '{:#.{}}'"), 1.2, 4);
	check(SV("answer is '1.2'"), SV("answer is '{:#.{}}'"), 1.2, 5);
	check(SV("answer is '1.2'"), SV("answer is '{:#.{}}'"), 1.2, 6);

	check(SV("answer is '1.e+03'"), SV("answer is '{:#.{}}'"), 1200.0, 0);
	check(SV("answer is '1.e+03'"), SV("answer is '{:#.{}}'"), 1200.0, 1);
	check(SV("answer is '1.2e+03'"), SV("answer is '{:#.{}}'"), 1200.0, 2);
	check(SV("answer is '1.2e+03'"), SV("answer is '{:#.{}}'"), 1200.0, 3);
	check(SV("answer is '1200.'"), SV("answer is '{:#.{}}'"), 1200.0, 4);
	check(SV("answer is '1200.'"), SV("answer is '{:#.{}}'"), 1200.0, 5);
	check(SV("answer is '1200.'"), SV("answer is '{:#.{}}'"), 1200.0, 6);

	check(SV("answer is '1.e+06'"), SV("answer is '{:#.{}}'"), 1200000.0, 0);
	check(SV("answer is '1.e+06'"), SV("answer is '{:#.{}}'"), 1200000.0, 1);
	check(SV("answer is '1.2e+06'"), SV("answer is '{:#.{}}'"), 1200000.0, 2);
	check(SV("answer is '1.2e+06'"), SV("answer is '{:#.{}}'"), 1200000.0, 3);
	check(SV("answer is '1.2e+06'"), SV("answer is '{:#.{}}'"), 1200000.0, 4);
	check(SV("answer is '1.2e+06'"), SV("answer is '{:#.{}}'"), 1200000.0, 5);
	check(SV("answer is '1.2e+06'"), SV("answer is '{:#.{}}'"), 1200000.0, 6);
}

template <typename CharT, typename F, typename TestFunction>
void test_floating_point_PR58714(TestFunction check)
{
	check(SV("+1234"), SV("{:+}"), F(1234.0));
	check(SV("+1.348p+10"), SV("{:+a}"), F(1234.0));
	check(SV("+1.234000e+03"), SV("{:+e}"), F(1234.0));
	check(SV("+1234.000000"), SV("{:+f}"), F(1234.0));
	check(SV("+1234"), SV("{:+g}"), F(1234.0));

	check(SV("1234."), SV("{:#}"), F(1234.0));
	check(SV("1.348p+10"), SV("{:#a}"), F(1234.0));
	check(SV("1.234000e+03"), SV("{:#e}"), F(1234.0));
	check(SV("1234.000000"), SV("{:#f}"), F(1234.0));
	check(SV("1234.00"), SV("{:#g}"), F(1234.0));

	check(SV("4.e+30"), SV("{:#}"), F(4.0e+30));
	check(SV("1.p+102"), SV("{:#a}"), F(0x4.0p+100));
	check(SV("4.000000e+30"), SV("{:#e}"), F(4.0e+30));
	check(SV("5070602400912917605986812821504.000000"), SV("{:#f}"), F(0x4.0p+100));
	check(SV("4.00000e+30"), SV("{:#g}"), F(4.0e+30));

	check(SV("1234."), SV("{:#.6}"), F(1234.0)); // # does not restore zeros
	check(SV("1.348000p+10"), SV("{:#.6a}"), F(1234.0));
	check(SV("1.234000e+03"), SV("{:#.6e}"), F(1234.0));
	check(SV("1234.000000"), SV("{:#.6f}"), F(1234.0));
	check(SV("1234.00"), SV("{:#.6g}"), F(1234.0));

	check(SV("-1234."), SV("{:#}"), F(-1234.0));
	check(SV("-1.348p+10"), SV("{:#a}"), F(-1234.0));
	check(SV("-1.234000e+03"), SV("{:#e}"), F(-1234.0));
	check(SV("-1234.000000"), SV("{:#f}"), F(-1234.0));
	check(SV("-1234.00"), SV("{:#g}"), F(-1234.0));

	check(SV("-1234."), SV("{:#.6}"), F(-1234.0)); // # does not restore zeros
	check(SV("-1.348000p+10"), SV("{:#.6a}"), F(-1234.0));
	check(SV("-1.234000e+03"), SV("{:#.6e}"), F(-1234.0));
	check(SV("-1234.000000"), SV("{:#.6f}"), F(-1234.0));
	check(SV("-1234.00"), SV("{:#.6g}"), F(-1234.0));

	check(SV("+1234."), SV("{:+#}"), F(1234.0));
	check(SV("+1.348p+10"), SV("{:+#a}"), F(1234.0));
	check(SV("+1.234000e+03"), SV("{:+#e}"), F(1234.0));
	check(SV("+1234.000000"), SV("{:+#f}"), F(1234.0));
	check(SV("+1234.00"), SV("{:+#g}"), F(1234.0));

	check(SV("+1234."), SV("{:+#.6}"), F(1234.0)); // # does not restore zeros
	check(SV("+1.348000p+10"), SV("{:+#.6a}"), F(1234.0));
	check(SV("+1.234000e+03"), SV("{:+#.6e}"), F(1234.0));
	check(SV("+1234.000000"), SV("{:+#.6f}"), F(1234.0));
	check(SV("+1234.00"), SV("{:+#.6g}"), F(1234.0));
}

template <typename CharT, typename F, typename TestFunction>
void test_floating_point_impl(TestFunction check)
{
	test_floating_point_hex_lower_case<CharT, F>(check);
	test_floating_point_hex_upper_case<CharT, F>(check);
	test_floating_point_hex_lower_case_precision<CharT, F>(check);
	test_floating_point_hex_upper_case_precision<CharT, F>(check);

	test_floating_point_scientific_lower_case<CharT, F>(check);
	test_floating_point_scientific_upper_case<CharT, F>(check);

	test_floating_point_fixed_lower_case<CharT, F>(check);
	test_floating_point_fixed_upper_case<CharT, F>(check);

	test_floating_point_general_lower_case<CharT, F>(check);
	test_floating_point_general_upper_case<CharT, F>(check);

	test_floating_point_default<CharT, F>(check);
	test_floating_point_default_precision<CharT, F>(check);

	test_floating_point_PR58714<CharT, F>(check);
}

template <typename CharT, typename TestFunction>
void test_floating_point(TestFunction check)
{
	test_floating_point_impl<CharT, float>(check);
	test_floating_point_impl<CharT, double>(check);
//	test_floating_point_impl<CharT, long double>(check);	// TODO
}

template <typename CharT, typename P, typename TestFunction>
void test_pointer_impl(TestFunction check)
{
	// *** align-fill & width ***
	check(SV("answer is '   0x0'"), SV("answer is '{:6}'"),  P(nullptr));
	check(SV("answer is '   0x0'"), SV("answer is '{:>6}'"), P(nullptr));
	check(SV("answer is '0x0   '"), SV("answer is '{:<6}'"), P(nullptr));
	check(SV("answer is ' 0x0  '"), SV("answer is '{:^6}'"), P(nullptr));

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	check(SV("answer is ':::0x0'"), SV("answer is '{::>6}'"), P(nullptr));
	check(SV("answer is '0x0:::'"), SV("answer is '{::<6}'"), P(nullptr));
	check(SV("answer is ':0x0::'"), SV("answer is '{::^6}'"), P(nullptr));

	// Test whether zero padding is ignored
	check(SV("answer is ':::0x0'"), SV("answer is '{::>06}'"), P(nullptr));
	check(SV("answer is '0x0:::'"), SV("answer is '{::<06}'"), P(nullptr));
	check(SV("answer is ':0x0::'"), SV("answer is '{::^06}'"), P(nullptr));

	// *** zero-padding ***
	check(SV("answer is '0x0000'"), SV("answer is '{:06}'"),  P(nullptr));
	check(SV("answer is '0x0000'"), SV("answer is '{:06p}'"), P(nullptr));
	check(SV("answer is '0X0000'"), SV("answer is '{:06P}'"), P(nullptr));
}

template <typename CharT, typename TestFunction>
void test_pointer(TestFunction check)
{
	test_pointer_impl<CharT, hamon::nullptr_t>(check);
	test_pointer_impl<CharT, void*>(check);
	test_pointer_impl<CharT, const void*>(check);
}

template <typename CharT, typename TestFunction>
void test_buffer_optimizations(TestFunction check)
{
#ifdef _LIBCPP_VERSION
	// Used to validate our test sets are the proper size.
	// To test the chunked operations it needs to be larger than the internal
	// buffer. Picked a nice looking number.
	constexpr int minimum = 3 * 256;
#else
	constexpr int minimum = 1;
#endif

	// Copy
	hamon::basic_string<CharT> str = STR(
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog."
		"The quick brown fox jumps over the lazy dog.");
	assert(str.size() > minimum);
	check(hamon::basic_string_view<CharT>{str}, SV("{}"), str);

	// Fill
	hamon::basic_string<CharT> fill(minimum, CharT('*'));
	check(hamon::basic_string_view<CharT>{str + fill},        SV("{:*<{}}"), str, str.size() + minimum);
	check(hamon::basic_string_view<CharT>{fill + str + fill}, SV("{:*^{}}"), str, minimum + str.size() + minimum);
	check(hamon::basic_string_view<CharT>{fill + str},        SV("{:*>{}}"), str, minimum + str.size());
}

}	// namespace detail

template <typename CharT, typename TestFunction>
void test_full(TestFunction check)
{
	test_partial<CharT>(check);

	detail::test_buffer_copy<CharT>(check);
	detail::test_buffer_fill<CharT>(check);
	detail::test_char<CharT>(check);
	detail::test_char_as_integer<CharT>(check);
	detail::test_string<CharT>(check);
	detail::test_bool<CharT>(check);
	detail::test_bool_as_integer<CharT>(check);
	detail::test_integer<CharT>(check);
	detail::test_floating_point<CharT>(check);
	detail::test_pointer<CharT>(check);
	detail::test_buffer_optimizations<CharT>(check);
}

#undef SV
#undef STR

}	// namespace hamon_format_test

#endif // HAMON_FORMAT_TEST_HPP
