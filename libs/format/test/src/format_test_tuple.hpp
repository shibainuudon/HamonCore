/**
 *	@file	format_test_tuple.hpp
 *
 *	@brief
 */

#ifndef HAMON_FORMAT_TEST_TUPLE_HPP
#define HAMON_FORMAT_TEST_TUPLE_HPP

#include <hamon/concepts/same_as.hpp>
#include <hamon/detail/statically_widen.hpp>
#include <hamon/pair.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include "format_test_helper.hpp"

#define SV(Str)		hamon::basic_string_view<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str), sizeof(Str) - 1)
#define STR(Str)	hamon::basic_string<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str), sizeof(Str) - 1)
#define CSTR(Str)	HAMON_STATICALLY_WIDEN(CharT, Str)

namespace hamon_format_test
{

namespace tuple_test
{

//
// Generic tests for a tuple and pair with two elements.
//
template <class CharT, class TestFunction, class TupleOrPair>
void test_tuple_or_pair_int_int(TestFunction check, TupleOrPair&& input)
{
	check(SV("(42, 99)"), SV("{}"), input);
	check(SV("(42, 99)^42"), SV("{}^42"), input);
	check(SV("(42, 99)^42"), SV("{:}^42"), input);

	// *** align-fill & width ***
	check(SV("(42, 99)     "), SV("{:13}"), input);
	check(SV("(42, 99)*****"), SV("{:*<13}"), input);
	check(SV("__(42, 99)___"), SV("{:_^13}"), input);
	check(SV("#####(42, 99)"), SV("{:#>13}"), input);

	check(SV("(42, 99)     "), SV("{:{}}"), input, 13);
	check(SV("(42, 99)*****"), SV("{:*<{}}"), input, 13);
	check(SV("__(42, 99)___"), SV("{:_^{}}"), input, 13);
	check(SV("#####(42, 99)"), SV("{:#>{}}"), input, 13);

	// *** type ***
	check(SV("__42: 99___"), SV("{:_^11m}"), input);
	check(SV("__42, 99___"), SV("{:_^11n}"), input);
}

template <class CharT, class TestFunction, class TupleOrPair>
void test_tuple_or_pair_int_string(TestFunction check, TupleOrPair&& input)
{
	check(SV("(42, \"hello\")"), SV("{}"), input);
	check(SV("(42, \"hello\")^42"), SV("{}^42"), input);
	check(SV("(42, \"hello\")^42"), SV("{:}^42"), input);

	// *** align-fill & width ***
	check(SV("(42, \"hello\")     "), SV("{:18}"), input);
	check(SV("(42, \"hello\")*****"), SV("{:*<18}"), input);
	check(SV("__(42, \"hello\")___"), SV("{:_^18}"), input);
	check(SV("#####(42, \"hello\")"), SV("{:#>18}"), input);

	check(SV("(42, \"hello\")     "), SV("{:{}}"), input, 18);
	check(SV("(42, \"hello\")*****"), SV("{:*<{}}"), input, 18);
	check(SV("__(42, \"hello\")___"), SV("{:_^{}}"), input, 18);
	check(SV("#####(42, \"hello\")"), SV("{:#>{}}"), input, 18);

	// *** type ***
	check(SV("__42: \"hello\"___"), SV("{:_^16m}"), input);
	check(SV("__42, \"hello\"___"), SV("{:_^16n}"), input);
}

template <class CharT, class TestFunction, class TupleOrPair>
void test_escaping(TestFunction check, TupleOrPair&& input)
{
	static_assert(hamon::same_as<hamon::remove_cvref_t<decltype(hamon::get<0>(input))>, CharT>);
	static_assert(hamon::same_as<hamon::remove_cvref_t<decltype(hamon::get<1>(input))>, hamon::basic_string<CharT>>);

	check(SV(R"(('*', ""))"), SV("{}"), input);

	// Char
	hamon::get<0>(input) = CharT('\t');
	check(SV(R"(('\t', ""))"), SV("{}"), input);
	hamon::get<0>(input) = CharT('\n');
	check(SV(R"(('\n', ""))"), SV("{}"), input);
	hamon::get<0>(input) = CharT('\0');
	check(SV(R"(('\u{0}', ""))"), SV("{}"), input);

	// String
	hamon::get<0>(input) = CharT('*');
	hamon::get<1>(input) = SV("hello");
	check(SV("('*', \"hello\")"), SV("{}"), input);
}

//
// pair tests
//

template <class CharT, class TestFunction>
void test_pair_int_int(TestFunction check)
{
	test_tuple_or_pair_int_int<CharT>(check, hamon::make_pair(42, 99));
}

template <class CharT, class TestFunction>
void test_pair_int_string(TestFunction check)
{
	test_tuple_or_pair_int_string<CharT>(check, hamon::make_pair(42, SV("hello")));
	test_tuple_or_pair_int_string<CharT>(check, hamon::make_pair(42, STR("hello")));
	test_tuple_or_pair_int_string<CharT>(check, hamon::make_pair(42, CSTR("hello")));
}

//
// tuple tests
//

template <class CharT, class TestFunction>
void test_tuple_int(TestFunction check)
{
	auto input = hamon::make_tuple(42);

	check(SV("(42)"), SV("{}"), input);
	check(SV("(42)^42"), SV("{}^42"), input);
	check(SV("(42)^42"), SV("{:}^42"), input);

	// *** align-fill & width ***
	check(SV("(42)     "), SV("{:9}"), input);
	check(SV("(42)*****"), SV("{:*<9}"), input);
	check(SV("__(42)___"), SV("{:_^9}"), input);
	check(SV("#####(42)"), SV("{:#>9}"), input);

	check(SV("(42)     "), SV("{:{}}"), input, 9);
	check(SV("(42)*****"), SV("{:*<{}}"), input, 9);
	check(SV("__(42)___"), SV("{:_^{}}"), input, 9);
	check(SV("#####(42)"), SV("{:#>{}}"), input, 9);

	// *** type ***
	check(SV("__42___"), SV("{:_^7n}"), input);
}

template <class CharT, class TestFunction>
void test_tuple_int_string_color(TestFunction check)
{
	const auto input = hamon::make_tuple(42, SV("hello"), color::red);

	check(SV("(42, \"hello\", \"red\")"), SV("{}"), input);
	check(SV("(42, \"hello\", \"red\")^42"), SV("{}^42"), input);
	check(SV("(42, \"hello\", \"red\")^42"), SV("{:}^42"), input);

	// *** align-fill & width ***
	check(SV("(42, \"hello\", \"red\")     "), SV("{:25}"), input);
	check(SV("(42, \"hello\", \"red\")*****"), SV("{:*<25}"), input);
	check(SV("__(42, \"hello\", \"red\")___"), SV("{:_^25}"), input);
	check(SV("#####(42, \"hello\", \"red\")"), SV("{:#>25}"), input);

	check(SV("(42, \"hello\", \"red\")     "), SV("{:{}}"), input, 25);
	check(SV("(42, \"hello\", \"red\")*****"), SV("{:*<{}}"), input, 25);
	check(SV("__(42, \"hello\", \"red\")___"), SV("{:_^{}}"), input, 25);
	check(SV("#####(42, \"hello\", \"red\")"), SV("{:#>{}}"), input, 25);

	// *** type ***
	check(SV("__42, \"hello\", \"red\"___"), SV("{:_^23n}"), input);
}

template <class CharT, class TestFunction>
void test_tuple_int_int(TestFunction check)
{
	test_tuple_or_pair_int_int<CharT>(check, hamon::make_tuple(42, 99));
}

template <class CharT, class TestFunction>
void test_tuple_int_string(TestFunction check)
{
	test_tuple_or_pair_int_string<CharT>(check, hamon::make_tuple(42, SV("hello")));
	test_tuple_or_pair_int_string<CharT>(check, hamon::make_tuple(42, STR("hello")));
	test_tuple_or_pair_int_string<CharT>(check, hamon::make_tuple(42, CSTR("hello")));
}

//
// nested tests
//

template <class CharT, class TestFunction, class Nested>
void test_nested(TestFunction check, Nested&& input)
{
	// [format.formatter.spec]/2
	//   A debug-enabled specialization of formatter additionally provides a
	//   public, constexpr, non-static member function set_debug_format()
	//   which modifies the state of the formatter to be as if the type of the
	//   std-format-spec parsed by the last call to parse were ?.
	// pair and tuple are not debug-enabled specializations to the
	// set_debug_format is not propagated. The paper
	//   P2733 Fix handling of empty specifiers in std::format
	// addressed this.

	check(SV("(42, (\"hello\", \"red\"))"), SV("{}"), input);
	check(SV("(42, (\"hello\", \"red\"))^42"), SV("{}^42"), input);
	check(SV("(42, (\"hello\", \"red\"))^42"), SV("{:}^42"), input);

	// *** align-fill & width ***
	check(SV("(42, (\"hello\", \"red\"))     "), SV("{:27}"), input);
	check(SV("(42, (\"hello\", \"red\"))*****"), SV("{:*<27}"), input);
	check(SV("__(42, (\"hello\", \"red\"))___"), SV("{:_^27}"), input);
	check(SV("#####(42, (\"hello\", \"red\"))"), SV("{:#>27}"), input);

	check(SV("(42, (\"hello\", \"red\"))     "), SV("{:{}}"), input, 27);
	check(SV("(42, (\"hello\", \"red\"))*****"), SV("{:*<{}}"), input, 27);
	check(SV("__(42, (\"hello\", \"red\"))___"), SV("{:_^{}}"), input, 27);
	check(SV("#####(42, (\"hello\", \"red\"))"), SV("{:#>{}}"), input, 27);

	// *** type ***
	check(SV("__42: (\"hello\", \"red\")___"), SV("{:_^25m}"), input);
	check(SV("__42, (\"hello\", \"red\")___"), SV("{:_^25n}"), input);
}

}	// namespace tuple_test

template <class CharT, class TestFunction>
void test_tuple(TestFunction check)
{
	tuple_test::test_pair_int_int<CharT>(check);
	tuple_test::test_pair_int_string<CharT>(check);

	tuple_test::test_tuple_int<CharT>(check);
	tuple_test::test_tuple_int_int<CharT>(check);
	tuple_test::test_tuple_int_string<CharT>(check);
	tuple_test::test_tuple_int_string_color<CharT>(check);

	tuple_test::test_nested<CharT>(check, hamon::make_pair(42, hamon::make_pair(SV("hello"), color::red)));
	tuple_test::test_nested<CharT>(check, hamon::make_pair(42, hamon::make_tuple(SV("hello"), color::red)));
	tuple_test::test_nested<CharT>(check, hamon::make_tuple(42, hamon::make_pair(SV("hello"), color::red)));
	tuple_test::test_nested<CharT>(check, hamon::make_tuple(42, hamon::make_tuple(SV("hello"), color::red)));

	tuple_test::test_escaping<CharT>(check, hamon::make_pair(CharT('*'), STR("")));
	tuple_test::test_escaping<CharT>(check, hamon::make_tuple(CharT('*'), STR("")));

	// Test const ref-qualified types.
	check(SV("(42)"), SV("{}"), hamon::tuple<      int  >{42});
	check(SV("(42)"), SV("{}"), hamon::tuple<const int  >{42});

	int answer = 42;
	check(SV("(42)"), SV("{}"), hamon::tuple<      int& >{answer});
	check(SV("(42)"), SV("{}"), hamon::tuple<const int& >{answer});

	check(SV("(42)"), SV("{}"), hamon::tuple<      int&&>{42});
	check(SV("(42)"), SV("{}"), hamon::tuple<const int&&>{42});
}

}	// namespace hamon_format_test

#undef SV
#undef STR
#undef CSTR

#endif // HAMON_FORMAT_TEST_TUPLE_HPP
