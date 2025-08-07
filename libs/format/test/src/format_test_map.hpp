/**
 *	@file	format_test_map.hpp
 *
 *	@brief
 */

#ifndef HAMON_FORMAT_TEST_MAP_HPP
#define HAMON_FORMAT_TEST_MAP_HPP

#include <hamon/format/format_kind.hpp>
#include <hamon/format/range_format.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/detail/statically_widen.hpp>
#include <hamon/deque.hpp>
#include <hamon/flat_map.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/map.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/unordered_map.hpp>
#include <hamon/utility/move.hpp>

#define SV(Str)		hamon::basic_string_view<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str), sizeof(Str) - 1)
#define STR(Str)	hamon::basic_string<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str), sizeof(Str) - 1)

namespace hamon_format_test
{

namespace map_test
{

//
// Char
//

template <class CharT, class TestFunction>
void test_char(TestFunction check)
{
	hamon::map<CharT, CharT> input{{CharT('a'), CharT('A')}, {CharT('c'), CharT('C')}, {CharT('b'), CharT('B')}};

	check(SV("{'a': 'A', 'b': 'B', 'c': 'C'}"), SV("{}"), input);
	check(SV("{'a': 'A', 'b': 'B', 'c': 'C'}^42"), SV("{}^42"), input);
	check(SV("{'a': 'A', 'b': 'B', 'c': 'C'}^42"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("{'a': 'A', 'b': 'B', 'c': 'C'}     "), SV("{:35}"), input);
	check(SV("{'a': 'A', 'b': 'B', 'c': 'C'}*****"), SV("{:*<35}"), input);
	check(SV("__{'a': 'A', 'b': 'B', 'c': 'C'}___"), SV("{:_^35}"), input);
	check(SV("#####{'a': 'A', 'b': 'B', 'c': 'C'}"), SV("{:#>35}"), input);

	check(SV("{'a': 'A', 'b': 'B', 'c': 'C'}     "), SV("{:{}}"), input, 35);
	check(SV("{'a': 'A', 'b': 'B', 'c': 'C'}*****"), SV("{:*<{}}"), input, 35);
	check(SV("__{'a': 'A', 'b': 'B', 'c': 'C'}___"), SV("{:_^{}}"), input, 35);
	check(SV("#####{'a': 'A', 'b': 'B', 'c': 'C'}"), SV("{:#>{}}"), input, 35);

	// *** n
	check(SV("__'a': 'A', 'b': 'B', 'c': 'C'___"), SV("{:_^33n}"), input);

	// *** type ***
	check(SV("__{'a': 'A', 'b': 'B', 'c': 'C'}___"), SV("{:_^35m}"), input); // the m type does the same as the default.

	// ***** Only underlying has a format-spec

	check(SV("{'a': 'A'     , 'b': 'B'     , 'c': 'C'     }"), SV("{::13}"), input);
	check(SV("{'a': 'A'*****, 'b': 'B'*****, 'c': 'C'*****}"), SV("{::*<13}"), input);
	check(SV("{__'a': 'A'___, __'b': 'B'___, __'c': 'C'___}"), SV("{::_^13}"), input);
	check(SV("{#####'a': 'A', #####'b': 'B', #####'c': 'C'}"), SV("{::#>13}"), input);

	check(SV("{'a': 'A'     , 'b': 'B'     , 'c': 'C'     }"), SV("{::{}}"), input, 13);
	check(SV("{'a': 'A'*****, 'b': 'B'*****, 'c': 'C'*****}"), SV("{::*<{}}"), input, 13);
	check(SV("{__'a': 'A'___, __'b': 'B'___, __'c': 'C'___}"), SV("{::_^{}}"), input, 13);
	check(SV("{#####'a': 'A', #####'b': 'B', #####'c': 'C'}"), SV("{::#>{}}"), input, 13);

	// *** type ***
	check(SV("{'a': 'A', 'b': 'B', 'c': 'C'}"), SV("{::m}"), input);
	check(SV("{'a': 'A', 'b': 'B', 'c': 'C'}"), SV("{::n}"), input);

	// ***** Both have a format-spec
	check(SV("^^{###'a': 'A', ###'b': 'B', ###'c': 'C'}^^^"), SV("{:^^44:#>11}"), input);
	check(SV("^^{###'a': 'A', ###'b': 'B', ###'c': 'C'}^^^"), SV("{:^^{}:#>11}"), input, 44);
	check(SV("^^{###'a': 'A', ###'b': 'B', ###'c': 'C'}^^^"), SV("{:^^{}:#>{}}"), input, 44, 11);
}

//
// char -> wchar_t
//

template <class TestFunction>
void test_char_to_wchar(TestFunction check)
{
	hamon::map<char, char> input{{'a', 'A'}, {'c', 'C'}, {'b', 'B'}};

	using CharT = wchar_t;
	check(SV("{'a': 'A', 'b': 'B', 'c': 'C'}"), SV("{}"), input);
	check(SV("{'a': 'A', 'b': 'B', 'c': 'C'}^42"), SV("{}^42"), input);
	check(SV("{'a': 'A', 'b': 'B', 'c': 'C'}^42"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("{'a': 'A', 'b': 'B', 'c': 'C'}     "), SV("{:35}"), input);
	check(SV("{'a': 'A', 'b': 'B', 'c': 'C'}*****"), SV("{:*<35}"), input);
	check(SV("__{'a': 'A', 'b': 'B', 'c': 'C'}___"), SV("{:_^35}"), input);
	check(SV("#####{'a': 'A', 'b': 'B', 'c': 'C'}"), SV("{:#>35}"), input);

	check(SV("{'a': 'A', 'b': 'B', 'c': 'C'}     "), SV("{:{}}"), input, 35);
	check(SV("{'a': 'A', 'b': 'B', 'c': 'C'}*****"), SV("{:*<{}}"), input, 35);
	check(SV("__{'a': 'A', 'b': 'B', 'c': 'C'}___"), SV("{:_^{}}"), input, 35);
	check(SV("#####{'a': 'A', 'b': 'B', 'c': 'C'}"), SV("{:#>{}}"), input, 35);

	// *** n
	check(SV("__'a': 'A', 'b': 'B', 'c': 'C'___"), SV("{:_^33n}"), input);

	// *** type ***
	check(SV("__{'a': 'A', 'b': 'B', 'c': 'C'}___"), SV("{:_^35m}"), input); // the m type does the same as the default.

	// ***** Only underlying has a format-spec
	check(SV("{'a': 'A'     , 'b': 'B'     , 'c': 'C'     }"), SV("{::13}"), input);
	check(SV("{'a': 'A'*****, 'b': 'B'*****, 'c': 'C'*****}"), SV("{::*<13}"), input);
	check(SV("{__'a': 'A'___, __'b': 'B'___, __'c': 'C'___}"), SV("{::_^13}"), input);
	check(SV("{#####'a': 'A', #####'b': 'B', #####'c': 'C'}"), SV("{::#>13}"), input);

	check(SV("{'a': 'A'     , 'b': 'B'     , 'c': 'C'     }"), SV("{::{}}"), input, 13);
	check(SV("{'a': 'A'*****, 'b': 'B'*****, 'c': 'C'*****}"), SV("{::*<{}}"), input, 13);
	check(SV("{__'a': 'A'___, __'b': 'B'___, __'c': 'C'___}"), SV("{::_^{}}"), input, 13);
	check(SV("{#####'a': 'A', #####'b': 'B', #####'c': 'C'}"), SV("{::#>{}}"), input, 13);

	// *** type ***
	check(SV("{'a': 'A', 'b': 'B', 'c': 'C'}"), SV("{::m}"), input);
	check(SV("{'a': 'A', 'b': 'B', 'c': 'C'}"), SV("{::n}"), input);

	// ***** Both have a format-spec
	check(SV("^^{###'a': 'A', ###'b': 'B', ###'c': 'C'}^^^"), SV("{:^^44:#>11}"), input);
	check(SV("^^{###'a': 'A', ###'b': 'B', ###'c': 'C'}^^^"), SV("{:^^{}:#>11}"), input, 44);
	check(SV("^^{###'a': 'A', ###'b': 'B', ###'c': 'C'}^^^"), SV("{:^^{}:#>{}}"), input, 44, 11);
}

//
// Bool
//
template <class CharT, class TestFunction>
void test_bool(TestFunction check, auto&& input)
{
	check(SV("{false: 0, true: 42, true: 1}"), SV("{}"), input);
	check(SV("{false: 0, true: 42, true: 1}^42"), SV("{}^42"), input);
	check(SV("{false: 0, true: 42, true: 1}^42"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("{false: 0, true: 42, true: 1}     "), SV("{:34}"), input);
	check(SV("{false: 0, true: 42, true: 1}*****"), SV("{:*<34}"), input);
	check(SV("__{false: 0, true: 42, true: 1}___"), SV("{:_^34}"), input);
	check(SV("#####{false: 0, true: 42, true: 1}"), SV("{:#>34}"), input);

	check(SV("{false: 0, true: 42, true: 1}     "), SV("{:{}}"), input, 34);
	check(SV("{false: 0, true: 42, true: 1}*****"), SV("{:*<{}}"), input, 34);
	check(SV("__{false: 0, true: 42, true: 1}___"), SV("{:_^{}}"), input, 34);
	check(SV("#####{false: 0, true: 42, true: 1}"), SV("{:#>{}}"), input, 34);

	// *** n
	check(SV("__false: 0, true: 42, true: 1___"), SV("{:_^32n}"), input);

	// *** type ***
	check(SV("__{false: 0, true: 42, true: 1}___"), SV("{:_^34m}"), input); // the m type does the same as the default.

	// ***** Only underlying has a format-spec
	check(SV("{false: 0  , true: 42  , true: 1   }"), SV("{::10}"), input);
	check(SV("{false: 0**, true: 42**, true: 1***}"), SV("{::*<10}"), input);
	check(SV("{_false: 0_, _true: 42_, _true: 1__}"), SV("{::_^10}"), input);
	check(SV("{##false: 0, ##true: 42, ###true: 1}"), SV("{::#>10}"), input);

	check(SV("{false: 0  , true: 42  , true: 1   }"), SV("{::{}}"), input, 10);
	check(SV("{false: 0**, true: 42**, true: 1***}"), SV("{::*<{}}"), input, 10);
	check(SV("{_false: 0_, _true: 42_, _true: 1__}"), SV("{::_^{}}"), input, 10);
	check(SV("{##false: 0, ##true: 42, ###true: 1}"), SV("{::#>{}}"), input, 10);

	// ***** Both have a format-spec
	check(SV("^^{##false: 0, ##true: 42, ###true: 1}^^^"), SV("{:^^41:#>10}"), input);
	check(SV("^^{##false: 0, ##true: 42, ###true: 1}^^^"), SV("{:^^{}:#>10}"), input, 41);
	check(SV("^^{##false: 0, ##true: 42, ###true: 1}^^^"), SV("{:^^{}:#>{}}"), input, 41, 10);
}

template <class CharT, class TestFunction>
void test_bool(TestFunction check)
{
	// duplicates are stored in order of insertion
	test_bool<CharT>(check, hamon::multimap<bool, int>{{true, 42}, {false, 0}, {true, 1}});
	test_bool<CharT>(check, hamon::flat_multimap<bool, int, hamon::less<bool>, hamon::deque<bool>>{{true, 42}, {false, 0}, {true, 1}});
}

//
// Integral
//

template <class CharT, class TestFunction>
void test_int(TestFunction check, auto&& input)
{
	check(SV("{-42: 42, 1: -1, 42: -42}"), SV("{}"), input);
	check(SV("{-42: 42, 1: -1, 42: -42}^42"), SV("{}^42"), input);
	check(SV("{-42: 42, 1: -1, 42: -42}^42"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("{-42: 42, 1: -1, 42: -42}     "), SV("{:30}"), input);
	check(SV("{-42: 42, 1: -1, 42: -42}*****"), SV("{:*<30}"), input);
	check(SV("__{-42: 42, 1: -1, 42: -42}___"), SV("{:_^30}"), input);
	check(SV("#####{-42: 42, 1: -1, 42: -42}"), SV("{:#>30}"), input);

	check(SV("{-42: 42, 1: -1, 42: -42}     "), SV("{:{}}"), input, 30);
	check(SV("{-42: 42, 1: -1, 42: -42}*****"), SV("{:*<{}}"), input, 30);
	check(SV("__{-42: 42, 1: -1, 42: -42}___"), SV("{:_^{}}"), input, 30);
	check(SV("#####{-42: 42, 1: -1, 42: -42}"), SV("{:#>{}}"), input, 30);

	// *** n
	check(SV("__-42: 42, 1: -1, 42: -42___"), SV("{:_^28n}"), input);

	// *** type ***
	check(SV("__{-42: 42, 1: -1, 42: -42}___"), SV("{:_^30m}"), input); // the m type does the same as the default.

	// ***** Only underlying has a format-spec
	check(SV("{-42: 42   , 1: -1     , 42: -42   }"), SV("{::10}"), input);
	check(SV("{-42: 42***, 1: -1*****, 42: -42***}"), SV("{::*<10}"), input);
	check(SV("{_-42: 42__, __1: -1___, _42: -42__}"), SV("{::_^10}"), input);
	check(SV("{###-42: 42, #####1: -1, ###42: -42}"), SV("{::#>10}"), input);

	check(SV("{-42: 42   , 1: -1     , 42: -42   }"), SV("{::{}}"), input, 10);
	check(SV("{-42: 42***, 1: -1*****, 42: -42***}"), SV("{::*<{}}"), input, 10);
	check(SV("{_-42: 42__, __1: -1___, _42: -42__}"), SV("{::_^{}}"), input, 10);
	check(SV("{###-42: 42, #####1: -1, ###42: -42}"), SV("{::#>{}}"), input, 10);

	// ***** Both have a format-spec
	check(SV("^^{###-42: 42, #####1: -1, ###42: -42}^^^"), SV("{:^^41:#>10}"), input);
	check(SV("^^{###-42: 42, #####1: -1, ###42: -42}^^^"), SV("{:^^{}:#>10}"), input, 41);
	check(SV("^^{###-42: 42, #####1: -1, ###42: -42}^^^"), SV("{:^^{}:#>{}}"), input, 41, 10);
}

template <class CharT, class TestFunction>
void test_int(TestFunction check)
{
	test_int<CharT>(check, hamon::map<int, int>{{1, -1}, {42, -42}, {-42, 42}});
	test_int<CharT>(check, hamon::flat_map<int, int>{{1, -1}, {42, -42}, {-42, 42}});
}

//
// Floating point
//

template <class CharT, class TestFunction>
void test_floating_point(TestFunction check)
{
	hamon::map<double, double> input{{1.0, -1.0}, {-42, 42}};

	check(SV("{-42: 42, 1: -1}"), SV("{}"), input);
	check(SV("{-42: 42, 1: -1}^42"), SV("{}^42"), input);
	check(SV("{-42: 42, 1: -1}^42"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("{-42: 42, 1: -1}     "), SV("{:21}"), input);
	check(SV("{-42: 42, 1: -1}*****"), SV("{:*<21}"), input);
	check(SV("__{-42: 42, 1: -1}___"), SV("{:_^21}"), input);
	check(SV("#####{-42: 42, 1: -1}"), SV("{:#>21}"), input);

	check(SV("{-42: 42, 1: -1}     "), SV("{:{}}"), input, 21);
	check(SV("{-42: 42, 1: -1}*****"), SV("{:*<{}}"), input, 21);
	check(SV("__{-42: 42, 1: -1}___"), SV("{:_^{}}"), input, 21);
	check(SV("#####{-42: 42, 1: -1}"), SV("{:#>{}}"), input, 21);

	// *** n
	check(SV("__-42: 42, 1: -1___"), SV("{:_^19n}"), input);

	// *** type ***
	check(SV("__{-42: 42, 1: -1}___"), SV("{:_^21m}"), input); // the m type does the same as the default.

	// ***** Only underlying has a format-spec
	check(SV("{-42: 42   , 1: -1     }"), SV("{::10}"), input);
	check(SV("{-42: 42***, 1: -1*****}"), SV("{::*<10}"), input);
	check(SV("{_-42: 42__, __1: -1___}"), SV("{::_^10}"), input);
	check(SV("{###-42: 42, #####1: -1}"), SV("{::#>10}"), input);

	check(SV("{-42: 42   , 1: -1     }"), SV("{::{}}"), input, 10);
	check(SV("{-42: 42***, 1: -1*****}"), SV("{::*<{}}"), input, 10);
	check(SV("{_-42: 42__, __1: -1___}"), SV("{::_^{}}"), input, 10);
	check(SV("{###-42: 42, #####1: -1}"), SV("{::#>{}}"), input, 10);

	// ***** Both have a format-spec
	check(SV("^^{###-42: 42, #####1: -1}^^^"), SV("{:^^29:#>10}"), input);
	check(SV("^^{###-42: 42, #####1: -1}^^^"), SV("{:^^{}:#>10}"), input, 29);
	check(SV("^^{###-42: 42, #####1: -1}^^^"), SV("{:^^{}:#>{}}"), input, 29, 10);
}

//
// Pointer
//

template <class CharT, class TestFunction>
void test_pointer(TestFunction check)
{
	hamon::unordered_map<const void*, hamon::nullptr_t> input{{0, 0}};

	check(SV("{0x0: 0x0}"), SV("{}"), input);
	check(SV("{0x0: 0x0}^42"), SV("{}^42"), input);
	check(SV("{0x0: 0x0}^42"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("{0x0: 0x0}     "), SV("{:15}"), input);
	check(SV("{0x0: 0x0}*****"), SV("{:*<15}"), input);
	check(SV("__{0x0: 0x0}___"), SV("{:_^15}"), input);
	check(SV("#####{0x0: 0x0}"), SV("{:#>15}"), input);

	check(SV("{0x0: 0x0}     "), SV("{:{}}"), input, 15);
	check(SV("{0x0: 0x0}*****"), SV("{:*<{}}"), input, 15);
	check(SV("__{0x0: 0x0}___"), SV("{:_^{}}"), input, 15);
	check(SV("#####{0x0: 0x0}"), SV("{:#>{}}"), input, 15);

	// *** n
	check(SV("__0x0: 0x0___"), SV("{:_^13n}"), input);

	// *** type ***
	check(SV("__{0x0: 0x0}___"), SV("{:_^15m}"), input); // the m type does the same as the default.

	// ***** Only underlying has a format-spec
	check(SV("{0x0: 0x0     }"), SV("{::13}"), input);
	check(SV("{0x0: 0x0*****}"), SV("{::*<13}"), input);
	check(SV("{__0x0: 0x0___}"), SV("{::_^13}"), input);
	check(SV("{#####0x0: 0x0}"), SV("{::#>13}"), input);

	check(SV("{0x0: 0x0     }"), SV("{::{}}"), input, 13);
	check(SV("{0x0: 0x0*****}"), SV("{::*<{}}"), input, 13);
	check(SV("{__0x0: 0x0___}"), SV("{::_^{}}"), input, 13);
	check(SV("{#####0x0: 0x0}"), SV("{::#>{}}"), input, 13);

	// ***** Both have a format-spec
	check(SV("^^{###0x0: 0x0}^^^"), SV("{:^^18:#>11}"), input);
	check(SV("^^{###0x0: 0x0}^^^"), SV("{:^^{}:#>11}"), input, 18);
	check(SV("^^{###0x0: 0x0}^^^"), SV("{:^^{}:#>{}}"), input, 18, 11);
}

//
// String
//

template <class CharT, class TestFunction>
void test_string(TestFunction check)
{
	hamon::map<hamon::basic_string<CharT>, hamon::basic_string<CharT>> input{
		{STR("hello"), STR("HELLO")}, {STR("world"), STR("WORLD")}};

	check(SV(R"({"hello": "HELLO", "world": "WORLD"})"), SV("{}"), input);
	check(SV(R"({"hello": "HELLO", "world": "WORLD"}^42)"), SV("{}^42"), input);
	check(SV(R"({"hello": "HELLO", "world": "WORLD"}^42)"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV(R"({"hello": "HELLO", "world": "WORLD"}     )"), SV("{:41}"), input);
	check(SV(R"({"hello": "HELLO", "world": "WORLD"}*****)"), SV("{:*<41}"), input);
	check(SV(R"(__{"hello": "HELLO", "world": "WORLD"}___)"), SV("{:_^41}"), input);
	check(SV(R"(#####{"hello": "HELLO", "world": "WORLD"})"), SV("{:#>41}"), input);

	check(SV(R"({"hello": "HELLO", "world": "WORLD"}     )"), SV("{:{}}"), input, 41);
	check(SV(R"({"hello": "HELLO", "world": "WORLD"}*****)"), SV("{:*<{}}"), input, 41);
	check(SV(R"(__{"hello": "HELLO", "world": "WORLD"}___)"), SV("{:_^{}}"), input, 41);
	check(SV(R"(#####{"hello": "HELLO", "world": "WORLD"})"), SV("{:#>{}}"), input, 41);

	// *** n
	check(SV(R"(__"hello": "HELLO", "world": "WORLD"___)"), SV("{:_^39n}"), input);

	// *** type ***
	check(SV(R"(__{"hello": "HELLO", "world": "WORLD"}___)"), SV("{:_^41m}"), input);

	// ***** Only underlying has a format-spec
	check(SV(R"({"hello": "HELLO"     , "world": "WORLD"     })"), SV("{::21}"), input);
	check(SV(R"({"hello": "HELLO"*****, "world": "WORLD"*****})"), SV("{::*<21}"), input);
	check(SV(R"({__"hello": "HELLO"___, __"world": "WORLD"___})"), SV("{::_^21}"), input);
	check(SV(R"({#####"hello": "HELLO", #####"world": "WORLD"})"), SV("{::#>21}"), input);

	check(SV(R"({"hello": "HELLO"     , "world": "WORLD"     })"), SV("{::{}}"), input, 21);
	check(SV(R"({"hello": "HELLO"*****, "world": "WORLD"*****})"), SV("{::*<{}}"), input, 21);
	check(SV(R"({__"hello": "HELLO"___, __"world": "WORLD"___})"), SV("{::_^{}}"), input, 21);
	check(SV(R"({#####"hello": "HELLO", #####"world": "WORLD"})"), SV("{::#>{}}"), input, 21);

	// ***** Both have a format-spec

	check(SV(R"(^^{#####"hello": "HELLO", #####"world": "WORLD"}^^^)"), SV("{:^^51:#>21}"), input);
	check(SV(R"(^^{#####"hello": "HELLO", #####"world": "WORLD"}^^^)"), SV("{:^^{}:#>21}"), input, 51);
	check(SV(R"(^^{#####"hello": "HELLO", #####"world": "WORLD"}^^^)"), SV("{:^^{}:#>{}}"), input, 51, 21);
}

//
// Handle
//

template <class CharT, class TestFunction>
void test_status(TestFunction check)
{
	hamon::unordered_multimap<status, status> input{{status::foobar, status::foo}, {status::foobar, status::bar}};

	check(SV("{0xaa55: 0xaaaa, 0xaa55: 0x5555}"), SV("{}"), input);
	check(SV("{0xaa55: 0xaaaa, 0xaa55: 0x5555}^42"), SV("{}^42"), input);
	check(SV("{0xaa55: 0xaaaa, 0xaa55: 0x5555}^42"), SV("{:}^42"), input);

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check(SV("{0xaa55: 0xaaaa, 0xaa55: 0x5555}     "), SV("{:37}"), input);
	check(SV("{0xaa55: 0xaaaa, 0xaa55: 0x5555}*****"), SV("{:*<37}"), input);
	check(SV("__{0xaa55: 0xaaaa, 0xaa55: 0x5555}___"), SV("{:_^37}"), input);
	check(SV("#####{0xaa55: 0xaaaa, 0xaa55: 0x5555}"), SV("{:#>37}"), input);

	check(SV("{0xaa55: 0xaaaa, 0xaa55: 0x5555}     "), SV("{:{}}"), input, 37);
	check(SV("{0xaa55: 0xaaaa, 0xaa55: 0x5555}*****"), SV("{:*<{}}"), input, 37);
	check(SV("__{0xaa55: 0xaaaa, 0xaa55: 0x5555}___"), SV("{:_^{}}"), input, 37);
	check(SV("#####{0xaa55: 0xaaaa, 0xaa55: 0x5555}"), SV("{:#>{}}"), input, 37);

	// *** n
	check(SV("__0xaa55: 0xaaaa, 0xaa55: 0x5555___"), SV("{:_^35n}"), input);

	// *** type ***
	check(SV("__{0xaa55: 0xaaaa, 0xaa55: 0x5555}___"), SV("{:_^37}"), input); // the m type does the same as the default.

	// Underlying can't have a format-spec
}

//
// Adaptor
//

class adaptor
{
	using adaptee = hamon::map<int, int>;

public:
	using key_type = typename adaptee::key_type;
	using mapped_type = typename adaptee::mapped_type;
	using iterator = typename adaptee::iterator;

	iterator begin() { return data_.begin(); }
	iterator end() { return data_.end(); }

	explicit adaptor(hamon::map<int, int>&& data) : data_(hamon::move(data)) {}

private:
	adaptee data_;
};

static_assert(hamon::format_kind<adaptor> == hamon::range_format::map);

template <class CharT, class TestFunction>
void test_adaptor(TestFunction check)
{
	test_int<CharT>(check, adaptor{ hamon::map<int, int>{{1, -1}, {42, -42}, {-42, 42}} });
}

}	// namespace map_test

//
// Driver
//

template <class CharT, class TestFunction>
void test_map(TestFunction check)
{
	map_test::test_char<CharT>(check);
	if (hamon::same_as<CharT, wchar_t>) // avoid testing twice
	{
		map_test::test_char_to_wchar(check);
	}
	map_test::test_bool<CharT>(check);
	map_test::test_int<CharT>(check);
	map_test::test_floating_point<CharT>(check);
	map_test::test_pointer<CharT>(check);
	map_test::test_string<CharT>(check);
	map_test::test_status<CharT>(check);
	map_test::test_adaptor<CharT>(check);
}

}	// namespace hamon_format_test

#undef SV
#undef STR

#endif // HAMON_FORMAT_TEST_MAP_HPP
