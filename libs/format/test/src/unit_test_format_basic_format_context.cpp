/**
 *	@file	unit_test_format_basic_format_context.cpp
 *
 *	@brief	basic_format_context のテスト
 *
 *	template<class Out, class charT>
 *	class basic_format_context;
 */

#include <hamon/format/basic_format_context.hpp>
#include <hamon/format/basic_format_args.hpp>
#include <hamon/format/make_format_args.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/detail/statically_widen.hpp>
#include <hamon/iterator/back_insert_iterator.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include <locale>
#include "noexcept_test.hpp"
#include "format_test_helper.hpp"


#include <hamon/format/other/__format_context_create.hpp>

namespace hamon_format_test
{

namespace basic_format_context_test
{

/** Creates a std::basic_format_context as-if the formatting function takes no locale. */
template <class OutIt, class CharT>
hamon::basic_format_context<OutIt, CharT> test_format_context_create(
	OutIt out_it,
	hamon::basic_format_args<hamon::basic_format_context<OutIt, CharT>> args)
{
	return hamon::__format_context_create(hamon::move(out_it), args);
}

/** Creates a std::basic_format_context as-if the formatting function takes locale. */
template <class OutIt, class CharT>
hamon::basic_format_context<OutIt, CharT> test_format_context_create(
	OutIt out_it,
	hamon::basic_format_args<hamon::basic_format_context<OutIt, CharT>> args,
	std::locale const& loc)
{
	return hamon::__format_context_create(hamon::move(out_it), args, loc);
}

/// Returns whether the basic_format_arg contains a type T with the expected value.
template <class Context, class T>
bool test_basic_format_arg(hamon::basic_format_arg<Context> arg, T expected)
{
	auto visitor = [expected](auto a)
	{
		if constexpr (hamon::same_as<decltype(a), T>)
		{
			return a == expected;
		}
		else
		{
			return false;
		}
	};
#if 1//TEST_STD_VER >= 26 && defined(TEST_HAS_EXPLICIT_THIS_PARAMETER)
	return arg.visit(hamon::move(visitor));
#else
	return hamon::visit_format_arg(hamon::move(visitor), arg);
#endif
}

namespace arg_test
{

template <class OutIt, class CharT>
void test()
{
	bool b = true;
	CharT c = CharT('a');
	int a = 42;
	hamon::basic_string<CharT> string = HAMON_STATICALLY_WIDEN(CharT, "string");
	auto store = hamon::make_format_args<hamon::basic_format_context<OutIt, CharT>>(b, c, a, string);
	hamon::basic_format_args args = store;

	hamon::basic_string<CharT> output;
	const hamon::basic_format_context context = test_format_context_create(OutIt{ output }, args);
	//LIBCPP_ASSERT(args.__size() == 4);
	HAMON_ASSERT_NOEXCEPT_TRUE(context.arg(0));
	for (hamon::size_t i = 0, e = args.__size(); i != e; ++i)
	{
		EXPECT_TRUE(context.arg(i));
	}
	EXPECT_TRUE(!context.arg(args.__size()));

	EXPECT_TRUE(test_basic_format_arg(context.arg(0), true));
	EXPECT_TRUE(test_basic_format_arg(context.arg(1), CharT('a')));
	EXPECT_TRUE(test_basic_format_arg(context.arg(2), 42));
	EXPECT_TRUE(test_basic_format_arg(context.arg(3), hamon::basic_string_view<CharT>(string)));
}

void test()
{
	test<hamon::back_insert_iterator<hamon::basic_string<char>>, char>();
	test<hamon::back_insert_iterator<hamon::basic_string<wchar_t>>, wchar_t>();
}

}	// namespace arg_test

namespace locale_test
{

template <class OutIt, class CharT>
void test()
{
	std::locale en_US{ LOCALE_en_US_UTF_8 };
	std::locale fr_FR{ LOCALE_fr_FR_UTF_8 };
	hamon::basic_string<CharT> string = HAMON_STATICALLY_WIDEN(CharT, "string");
	// The type of the object is an exposition only type. The temporary is needed
	// to extend the lifetime of the object since args stores a pointer to the
	// data in this object.
	int a = 42;
	bool b = true;
	CharT c = CharT('a');
	auto format_arg_store = hamon::make_format_args<hamon::basic_format_context<OutIt, CharT>>(b, c, a, string);
	hamon::basic_format_args args = format_arg_store;

	{
		hamon::basic_string<CharT> output;
		OutIt out_it{ output };
		hamon::basic_format_context context = test_format_context_create(out_it, args, en_US);
		EXPECT_TRUE(args.__size() == 4);
		EXPECT_TRUE(test_basic_format_arg(context.arg(0), true));
		EXPECT_TRUE(test_basic_format_arg(context.arg(1), CharT('a')));
		EXPECT_TRUE(test_basic_format_arg(context.arg(2), 42));
		EXPECT_TRUE(test_basic_format_arg(context.arg(3), hamon::basic_string_view<CharT>(string)));

		context.out() = CharT('a');
		EXPECT_TRUE(output.size() == 1);
		EXPECT_TRUE(output.front() == CharT('a'));

		EXPECT_TRUE(context.locale() != fr_FR);
		EXPECT_TRUE(context.locale() == en_US);
	}

	{
		hamon::basic_string<CharT> output;
		OutIt out_it{ output };
		hamon::basic_format_context context = test_format_context_create(out_it, args, fr_FR);
		EXPECT_TRUE(args.__size() == 4);
		EXPECT_TRUE(test_basic_format_arg(context.arg(0), true));
		EXPECT_TRUE(test_basic_format_arg(context.arg(1), CharT('a')));
		EXPECT_TRUE(test_basic_format_arg(context.arg(2), 42));
		EXPECT_TRUE(test_basic_format_arg(context.arg(3), hamon::basic_string_view<CharT>(string)));

		context.out() = CharT('a');
		EXPECT_TRUE(output.size() == 1);
		EXPECT_TRUE(output.front() == CharT('a'));

		EXPECT_TRUE(context.locale() == fr_FR);
		EXPECT_TRUE(context.locale() != en_US);
	}
}

void test()
{
	test<hamon::back_insert_iterator<hamon::basic_string<char>>, char>();
	test<hamon::back_insert_iterator<hamon::basic_string<wchar_t>>, wchar_t>();
}

}	// namespace locale_test

namespace out_test
{

template <class OutIt, class CharT>
void test(hamon::basic_format_args<hamon::basic_format_context<OutIt, CharT>> args)
{
	{
		hamon::basic_string<CharT> str = hamon::basic_string<CharT>(3, CharT(' '));
		hamon::basic_format_context context = test_format_context_create(OutIt{ str.begin() }, args);

		// Note this operation is moving the iterator
		OutIt out_it = context.out();
		*out_it++ = CharT('a');
		*out_it++ = CharT('b');
		*out_it++ = CharT('c');

		EXPECT_TRUE(str.size() == 3);
		EXPECT_TRUE(str[0] == CharT('a'));
		EXPECT_TRUE(str[1] == CharT('b'));
		EXPECT_TRUE(str[2] == CharT('c'));
	}
}

void test()
{
	test(hamon::basic_format_args(
		hamon::make_format_args<
			hamon::basic_format_context<hamon::basic_string<char>::iterator, char>>()));
	test(hamon::basic_format_args(
		hamon::make_format_args<
			hamon::basic_format_context<hamon::basic_string<wchar_t>::iterator, wchar_t>>()));
	test(hamon::basic_format_args(
		hamon::make_format_args<
			hamon::basic_format_context<hamon::basic_string<char8_t>::iterator, char8_t>>()));
	test(hamon::basic_format_args(
		hamon::make_format_args<
			hamon::basic_format_context<hamon::basic_string<char16_t>::iterator, char16_t>>()));
	test(hamon::basic_format_args(
		hamon::make_format_args<
			hamon::basic_format_context<hamon::basic_string<char32_t>::iterator, char32_t>>()));
}

}	// namespace out_test

namespace advance_to_test
{

template <class OutIt, class CharT>
void test(hamon::basic_format_args<hamon::basic_format_context<OutIt, CharT>> args)
{
	{
		hamon::basic_string<CharT> str[3] = {
			hamon::basic_string<CharT>{1}, hamon::basic_string<CharT>{1}, hamon::basic_string<CharT>{1} };
		hamon::basic_format_context context = test_format_context_create(OutIt{ str[0].begin() }, args);
		*context.out() = CharT('a');
		context.advance_to(OutIt{ str[1].begin() });
		*context.out() = CharT('b');
		context.advance_to(OutIt{ str[2].begin() });
		*context.out() = CharT('c');

		EXPECT_TRUE(str[0].size() == 1);
		EXPECT_TRUE(str[0].front() == CharT('a'));
		EXPECT_TRUE(str[1].size() == 1);
		EXPECT_TRUE(str[1].front() == CharT('b'));
		EXPECT_TRUE(str[2].size() == 1);
		EXPECT_TRUE(str[2].front() == CharT('c'));
	}
}

void test()
{
	test(hamon::basic_format_args(
		hamon::make_format_args<
			hamon::basic_format_context<hamon::basic_string<char>::iterator, char>>()));
	test(hamon::basic_format_args(
		hamon::make_format_args<
			hamon::basic_format_context<hamon::basic_string<wchar_t>::iterator, wchar_t>>()));
	test(hamon::basic_format_args(
		hamon::make_format_args<
			hamon::basic_format_context<hamon::basic_string<char8_t>::iterator, char8_t>>()));
	test(hamon::basic_format_args(
		hamon::make_format_args<
			hamon::basic_format_context<hamon::basic_string<char16_t>::iterator, char16_t>>()));
	test(hamon::basic_format_args(
		hamon::make_format_args<
			hamon::basic_format_context<hamon::basic_string<char32_t>::iterator, char32_t>>()));
}

}	// namespace advance_to_test

GTEST_TEST(FormatTest, BasicFormatContextTest)
{
	arg_test::test();
	locale_test::test();
	out_test::test();
	advance_to_test::test();
}

}	// namespace basic_format_context_test

}	// namespace hamon_format_test
