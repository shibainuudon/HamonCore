/**
 *	@file	format_test_string_exceptions.hpp
 *
 *	@brief
 */

#ifndef HAMON_FORMAT_TEST_STRING_EXCEPTIONS_HPP
#define HAMON_FORMAT_TEST_STRING_EXCEPTIONS_HPP

#include <hamon/format/range_format.hpp>
#include <hamon/format/format_kind.hpp>
#include <hamon/array.hpp>
#include <hamon/detail/statically_widen.hpp>
#include <hamon/list.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/utility/move.hpp>
//#include "format_test_helper.hpp"

#define SV(Str)		hamon::basic_string_view<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str), sizeof(Str) - 1)
#define STR(Str)	hamon::basic_string<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str), sizeof(Str) - 1)

namespace hamon_format_test
{

namespace string_exceptions_test
{

//
// Types
//

template <class Container>
class test_range_format_string
{
public:
	explicit test_range_format_string(Container str) : str_(hamon::move(str)) {}

	typename Container::const_iterator begin() const { return str_.begin(); }
	typename Container::const_iterator end() const { return str_.end(); }

private:
	Container str_;
};

template <class Container>
class test_range_format_debug_string
{
public:
	explicit test_range_format_debug_string(Container str) : str_(hamon::move(str)) {}

	typename Container::const_iterator begin() const { return str_.begin(); }
	typename Container::const_iterator end() const { return str_.end(); }

private:
	Container str_;
};

}	// namespace string_exceptions_test

}	// namespace hamon_format_test

template <class Container>
constexpr hamon::range_format
hamon::format_kind<hamon_format_test::string_exceptions_test::test_range_format_string<Container>>
	= hamon::range_format::string;

template <class Container>
constexpr hamon::range_format
hamon::format_kind<hamon_format_test::string_exceptions_test::test_range_format_debug_string<Container>>
	= hamon::range_format::debug_string;

namespace hamon_format_test
{

namespace string_exceptions_test
{

//
// String
//

template <class CharT, class ExceptionTest>
void test_string(ExceptionTest check_exception, auto&& input)
{
	// *** align-fill & width ***
	check_exception(SV("{:}<}"), input);
	check_exception(SV("{:{<}"), input);

	// *** sign ***
	check_exception(SV("{:-}"), input);

	// *** alternate form ***
	check_exception(SV("{:#}"), input);

	// *** zero-padding ***
	check_exception(SV("{:0}"), input);

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
	check_exception(false, SV("{:s}"), input);
	check_exception(true,  SV("{:x}"), input);
	check_exception(true,  SV("{:X}"), input);
	check_exception(false, SV("{:?}"), input);
	check_exception(true,  SV("{:m}"), input);
	check_exception(true,  SV("{:n}"), input);
	check_exception(true,  SV("{:?s}"), input);
}

template <class CharT, class ExceptionTest>
void test_string(ExceptionTest check_exception)
{
	// libc++ uses different containers for contiguous and non-contiguous ranges.
	hamon::basic_string<CharT> input = STR("hello");
	test_string<CharT>(check_exception, test_range_format_string<hamon::basic_string<CharT>>{input});
	test_string<CharT>(check_exception, test_range_format_string<hamon::basic_string_view<CharT>>{input});
	test_string<CharT>(check_exception, test_range_format_string<hamon::list<CharT>>{hamon::list<CharT>{input.begin(), input.end()}});
}

//
// String range
//

template <class CharT, class ExceptionTest>
void test_range_string(ExceptionTest check_exception, auto&& input)
{
	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check_exception(SV("{:}<}"), input);
	check_exception(SV("{:{<}"), input);

	// *** sign ***
	check_exception(SV("{:-}"), input);

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
void test_range_string(ExceptionTest check_exception)
{
	// libc++ uses different containers for contiguous and non-contiguous ranges.
	hamon::array input{STR("Hello"), STR("world")};
	test_range_string<CharT>(check_exception,
		hamon::array{
			test_range_format_string<hamon::basic_string<CharT>>{input[0]},
			test_range_format_string<hamon::basic_string<CharT>>{input[1]}});
	test_range_string<CharT>(check_exception,
		hamon::array{
			test_range_format_string<hamon::basic_string_view<CharT>>{input[0]},
			test_range_format_string<hamon::basic_string_view<CharT>>{input[1]}});
	test_range_string<CharT>(check_exception,
		hamon::array{
			test_range_format_string<hamon::list<CharT>>{hamon::list<CharT>{input[0].begin(), input[0].end()}},
			test_range_format_string<hamon::list<CharT>>{hamon::list<CharT>{input[1].begin(), input[1].end()}}});
	test_range_string<CharT>(check_exception,
		hamon::list{
			test_range_format_string<hamon::list<CharT>>{hamon::list<CharT>{input[0].begin(), input[0].end()}},
			test_range_format_string<hamon::list<CharT>>{hamon::list<CharT>{input[1].begin(), input[1].end()}}});
}

//
// Debug string
//

template <class CharT, class ExceptionTest>
void test_debug_string(ExceptionTest check_exception, auto&& input)
{
	// *** align-fill & width ***
	check_exception(SV("{:}<}"), input);
	check_exception(SV("{:{<}"), input);

	// *** sign ***
	check_exception(SV("{:-}"), input);

	// *** alternate form ***
	check_exception(SV("{:#}"), input);

	// *** zero-padding ***
	check_exception(SV("{:0}"), input);

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
	check_exception(false, SV("{:s}"), input);
	check_exception(true,  SV("{:x}"), input);
	check_exception(true,  SV("{:X}"), input);
	check_exception(false, SV("{:?}"), input);
	check_exception(true,  SV("{:m}"), input);
	check_exception(true,  SV("{:n}"), input);
	check_exception(true,  SV("{:?s}"), input);
}

template <class CharT, class ExceptionTest>
void test_debug_string(ExceptionTest check_exception)
{
	// libc++ uses different containers for contiguous and non-contiguous ranges.
	hamon::basic_string<CharT> input = STR("hello");
	test_debug_string<CharT>(check_exception, test_range_format_debug_string<hamon::basic_string<CharT>>{input});
	test_debug_string<CharT>(check_exception, test_range_format_debug_string<hamon::basic_string_view<CharT>>{input});
	test_debug_string<CharT>(check_exception, test_range_format_debug_string<hamon::list<CharT>>{hamon::list<CharT>{input.begin(), input.end()}});
}

//
// Debug string range
//

template <class CharT, class ExceptionTest>
void test_range_debug_string(ExceptionTest check_exception, auto&& input)
{
	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check_exception(SV("{:}<}"), input);
	check_exception(SV("{:{<}"), input);

	// *** sign ***
	check_exception(SV("{:-}"), input);

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
	check_exception(SV("{:^^{}::>10}"), input);
	check_exception(SV("{:^^{}::>{}}"), input, 29);
}

template <class CharT, class ExceptionTest>
void test_range_debug_string(ExceptionTest check_exception)
{
	// libc++ uses different containers for contiguous and non-contiguous ranges.
	hamon::array input{STR("Hello"), STR("world")};
	test_range_debug_string<CharT>(check_exception,
		hamon::array{
			test_range_format_debug_string<hamon::basic_string<CharT>>{input[0]},
			test_range_format_debug_string<hamon::basic_string<CharT>>{input[1]}});
	test_range_debug_string<CharT>(check_exception,
		hamon::array{
			test_range_format_debug_string<hamon::basic_string_view<CharT>>{input[0]},
			test_range_format_debug_string<hamon::basic_string_view<CharT>>{input[1]}});
	test_range_debug_string<CharT>(check_exception,
		hamon::array{
			test_range_format_debug_string<hamon::list<CharT>>{hamon::list<CharT>{input[0].begin(), input[0].end()}},
			test_range_format_debug_string<hamon::list<CharT>>{hamon::list<CharT>{input[1].begin(), input[1].end()}}});
	test_range_debug_string<CharT>(check_exception,
		hamon::list{
			test_range_format_debug_string<hamon::list<CharT>>{hamon::list<CharT>{input[0].begin(), input[0].end()}},
			test_range_format_debug_string<hamon::list<CharT>>{hamon::list<CharT>{input[1].begin(), input[1].end()}}});
}

}	// namespace string_exceptions_test

//
// Driver
//

template <class CharT, class ExceptionTest>
void test_string_exceptions(ExceptionTest check_exception)
{
	string_exceptions_test::test_string<CharT>(check_exception);
	string_exceptions_test::test_range_string<CharT>(check_exception);

	string_exceptions_test::test_debug_string<CharT>(check_exception);
	string_exceptions_test::test_range_debug_string<CharT>(check_exception);
}

}	// namespace hamon_format_test

#undef SV
#undef STR

#endif // HAMON_FORMAT_TEST_STRING_EXCEPTIONS_HPP
