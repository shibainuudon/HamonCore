/**
 *	@file	format_test_string.hpp
 *
 *	@brief
 */

#ifndef HAMON_FORMAT_TEST_STRING_HPP
#define HAMON_FORMAT_TEST_STRING_HPP

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

namespace string_test
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

}	// namespace string_test

}	// namespace hamon_format_test

template <class Container>
constexpr hamon::range_format
hamon::format_kind<hamon_format_test::string_test::test_range_format_string<Container>>
	= hamon::range_format::string;

template <class Container>
constexpr hamon::range_format
hamon::format_kind<hamon_format_test::string_test::test_range_format_debug_string<Container>>
	= hamon::range_format::debug_string;

namespace hamon_format_test
{

namespace string_test
{

//
// String
//

template <class CharT, class TestFunction>
void test_string(TestFunction check, auto&& input)
{
	check(SV("hello"), SV("{}"), input);
	check(SV("hello^42"), SV("{}^42"), input);
	check(SV("hello^42"), SV("{:}^42"), input);

	// *** align-fill & width ***
	check(SV("hello     "), SV("{:10}"), input);
	check(SV("hello*****"), SV("{:*<10}"), input);
	check(SV("__hello___"), SV("{:_^10}"), input);
	check(SV(":::::hello"), SV("{::>10}"), input);

	check(SV("hello     "), SV("{:{}}"), input, 10);
	check(SV("hello*****"), SV("{:*<{}}"), input, 10);
	check(SV("__hello___"), SV("{:_^{}}"), input, 10);
	check(SV(":::::hello"), SV("{::>{}}"), input, 10);

	// *** precision ***
	check(SV("hel"), SV("{:.3}"), input);
	check(SV("hel"), SV("{:.{}}"), input, 3);

	check(SV("hel  "), SV("{:5.3}"), input);
	check(SV("hel  "), SV("{:{}.{}}"), input, 5, 3);

	// *** type ***
	check(SV("hello"), SV("{:s}"), input);
	check(SV("\"hello\""), SV("{:?}"), input);
}

template <class CharT, class TestFunction>
void test_string(TestFunction check)
{
	// libc++ uses different containers for contiguous and non-contiguous ranges.
	hamon::basic_string<CharT> input = STR("hello");
	test_string<CharT>(check, test_range_format_string<hamon::basic_string<CharT>>{input});
	test_string<CharT>(check, test_range_format_string<hamon::basic_string_view<CharT>>{input});
	test_string<CharT>(check, test_range_format_string<hamon::list<CharT>>{hamon::list<CharT>{input.begin(), input.end()}});
}

//
// String range
//

template <class CharT, class TestFunction>
void test_range_string(TestFunction check, auto&& input)
{
	check(SV(R"([Hello, world])"), SV("{}"), input);
	check(SV(R"([Hello, world]^42)"), SV("{}^42"), input);
	check(SV(R"([Hello, world]^42)"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV(R"([Hello, world]     )"), SV("{:19}"), input);
	check(SV(R"([Hello, world]*****)"), SV("{:*<19}"), input);
	check(SV(R"(__[Hello, world]___)"), SV("{:_^19}"), input);
	check(SV(R"(#####[Hello, world])"), SV("{:#>19}"), input);

	check(SV(R"([Hello, world]     )"), SV("{:{}}"), input, 19);
	check(SV(R"([Hello, world]*****)"), SV("{:*<{}}"), input, 19);
	check(SV(R"(__[Hello, world]___)"), SV("{:_^{}}"), input, 19);
	check(SV(R"(#####[Hello, world])"), SV("{:#>{}}"), input, 19);

	// *** n
	check(SV(R"(_Hello, world_)"), SV("{:_^14n}"), input);

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
void test_range_string(TestFunction check)
{
	// libc++ uses different containers for contiguous and non-contiguous ranges.
	hamon::array input{STR("Hello"), STR("world")};
	test_range_string<CharT>(check,
		hamon::array{
			test_range_format_string<hamon::basic_string<CharT>>{input[0]},
			test_range_format_string<hamon::basic_string<CharT>>{input[1]}});
	test_range_string<CharT>(check,
		hamon::array{
			test_range_format_string<hamon::basic_string_view<CharT>>{input[0]},
			test_range_format_string<hamon::basic_string_view<CharT>>{input[1]}});
	test_range_string<CharT>(check,
		hamon::array{
			test_range_format_string<hamon::list<CharT>>{hamon::list<CharT>{input[0].begin(), input[0].end()}},
			test_range_format_string<hamon::list<CharT>>{hamon::list<CharT>{input[1].begin(), input[1].end()}}});
	test_range_string<CharT>(check,
		hamon::list{
			test_range_format_string<hamon::list<CharT>>{hamon::list<CharT>{input[0].begin(), input[0].end()}},
			test_range_format_string<hamon::list<CharT>>{hamon::list<CharT>{input[1].begin(), input[1].end()}}});
}

//
// Debug string
//

template <class CharT, class TestFunction>
void test_debug_string(TestFunction check, auto&& input)
{
	check(SV("\"hello\""), SV("{}"), input);
	check(SV("\"hello\"^42"), SV("{}^42"), input);
	check(SV("\"hello\"^42"), SV("{:}^42"), input);

	// *** align-fill & width ***
	check(SV("\"hello\"     "), SV("{:12}"), input);
	check(SV("\"hello\"*****"), SV("{:*<12}"), input);
	check(SV("__\"hello\"___"), SV("{:_^12}"), input);
	check(SV(":::::\"hello\""), SV("{::>12}"), input);

	check(SV("\"hello\"     "), SV("{:{}}"), input, 12);
	check(SV("\"hello\"*****"), SV("{:*<{}}"), input, 12);
	check(SV("__\"hello\"___"), SV("{:_^{}}"), input, 12);
	check(SV(":::::\"hello\""), SV("{::>{}}"), input, 12);

	// *** precision ***
	check(SV("\"he"), SV("{:.3}"), input);
	check(SV("\"he"), SV("{:.{}}"), input, 3);

	check(SV("\"he  "), SV("{:5.3}"), input);
	check(SV("\"he  "), SV("{:{}.{}}"), input, 5, 3);

	// *** type ***
	check(SV("\"hello\""), SV("{:s}"), input); // escape overrides the type option s
	check(SV("\"hello\""), SV("{:?}"), input);
}

template <class CharT, class TestFunction>
void test_debug_string(TestFunction check)
{
	// libc++ uses different containers for contiguous and non-contiguous ranges.
	hamon::basic_string<CharT> input = STR("hello");
	test_debug_string<CharT>(check, test_range_format_debug_string<hamon::basic_string<CharT>>{input});
	test_debug_string<CharT>(check, test_range_format_debug_string<hamon::basic_string_view<CharT>>{input});
	test_debug_string<CharT>(check, test_range_format_debug_string<hamon::list<CharT>>{hamon::list<CharT>{input.begin(), input.end()}});
}

//
// Debug string range
//

template <class CharT, class TestFunction>
void test_range_debug_string(TestFunction check, auto&& input)
{
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
	check(SV(R"(["Hello"   , "world"   ])"), SV("{::10}"), input);
	check(SV(R"(["Hello"***, "world"***])"), SV("{::*<10}"), input);
	check(SV(R"([_"Hello"__, _"world"__])"), SV("{::_^10}"), input);
	check(SV(R"([:::"Hello", :::"world"])"), SV("{:::>10}"), input);

	check(SV(R"(["Hello"   , "world"   ])"), SV("{::{}}"), input, 10);
	check(SV(R"(["Hello"***, "world"***])"), SV("{::*<{}}"), input, 10);
	check(SV(R"([_"Hello"__, _"world"__])"), SV("{::_^{}}"), input, 10);
	check(SV(R"([:::"Hello", :::"world"])"), SV("{:::>{}}"), input, 10);

	// *** precision ***
	check(SV(R"(["He, "wo])"), SV("{::.3}"), input);
	check(SV(R"(["He, "wo])"), SV("{::.{}}"), input, 3);

	// ***** Both have a format-spec
	check(SV(R"(^^[:::"Hello", :::"world"]^^^)"), SV("{:^^29::>10}"), input);
	check(SV(R"(^^[:::"Hello", :::"world"]^^^)"), SV("{:^^{}::>10}"), input, 29);
	check(SV(R"(^^[:::"Hello", :::"world"]^^^)"), SV("{:^^{}::>{}}"), input, 29, 10);

	check(SV(R"(^^[:::"Hello", :::"world"]^^^)"), SV("{:^^29::>10}"), input);
	check(SV(R"(^^[:::"Hello", :::"world"]^^^)"), SV("{:^^{}::>10}"), input, 29);
	check(SV(R"(^^[:::"Hello", :::"world"]^^^)"), SV("{:^^{}::>{}}"), input, 29, 10);
}

template <class CharT, class TestFunction>
void test_range_debug_string(TestFunction check)
{
	// libc++ uses different containers for contiguous and non-contiguous ranges.
	hamon::array input{STR("Hello"), STR("world")};
	test_range_debug_string<CharT>(check,
		hamon::array{
			test_range_format_debug_string<hamon::basic_string<CharT>>{input[0]},
			test_range_format_debug_string<hamon::basic_string<CharT>>{input[1]}});
	test_range_debug_string<CharT>(check,
		hamon::array{
			test_range_format_debug_string<hamon::basic_string_view<CharT>>{input[0]},
			test_range_format_debug_string<hamon::basic_string_view<CharT>>{input[1]}});
	test_range_debug_string<CharT>(check,
		hamon::array{
			test_range_format_debug_string<hamon::list<CharT>>{hamon::list<CharT>{input[0].begin(), input[0].end()}},
			test_range_format_debug_string<hamon::list<CharT>>{hamon::list<CharT>{input[1].begin(), input[1].end()}}});
	test_range_debug_string<CharT>(check,
		hamon::list{
			test_range_format_debug_string<hamon::list<CharT>>{hamon::list<CharT>{input[0].begin(), input[0].end()}},
			test_range_format_debug_string<hamon::list<CharT>>{hamon::list<CharT>{input[1].begin(), input[1].end()}}});
}

}	// namespace string_test

//
// Driver
//

template <class CharT, class TestFunction>
void test_string(TestFunction check)
{
	string_test::test_string<CharT>(check);
	string_test::test_range_string<CharT>(check);

	string_test::test_debug_string<CharT>(check);
	string_test::test_range_debug_string<CharT>(check);
}

}	// namespace hamon_format_test

#undef SV
#undef STR

#endif // HAMON_FORMAT_TEST_STRING_HPP
