/**
 *	@file	unit_test_format_basic_format_args.cpp
 *
 *	@brief	basic_format_args のテスト
 *
 *	template<class Context>
 *	class basic_format_args;
 */

#include <hamon/format/basic_format_args.hpp>
#include <hamon/format/basic_format_context.hpp>
#include <hamon/format/make_format_args.hpp>
#include <hamon/format/make_wformat_args.hpp>
#include <hamon/format/format_context.hpp>
#include <hamon/format/wformat_context.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/detail/statically_widen.hpp>
#include <hamon/limits.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_signed.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_format_test
{

namespace basic_format_args_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
/*HAMON_CXX20_CONSTEXPR*/ bool ctor_test()
{
	using Context = hamon::basic_format_context<CharT*, CharT>;
	static_assert(!hamon::is_default_constructible_v<hamon::basic_format_args<Context>>);

	int i              = 1;
	char c             = 'c';
	hamon::nullptr_t p = nullptr;

	{
		auto store = hamon::make_format_args<Context>(i);
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::basic_format_args<Context>{store});
		hamon::basic_format_args<Context> format_args{store};
		VERIFY(format_args.get(0));
		VERIFY(!format_args.get(1));
	}
	{
		auto store = hamon::make_format_args<Context>(i, c);
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::basic_format_args<Context>{store});
		hamon::basic_format_args<Context> format_args{store};
		VERIFY(format_args.get(0));
		VERIFY(format_args.get(1));
		VERIFY(!format_args.get(2));
	}
	{
		auto store = hamon::make_format_args<Context>(i, c, p);
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::basic_format_args<Context>{store});
		hamon::basic_format_args<Context> format_args{store};
		VERIFY(format_args.get(0));
		VERIFY(format_args.get(1));
		VERIFY(format_args.get(2));
		VERIFY(!format_args.get(3));
	}

	// Note the Standard way to create a format-arg-store is by using make_format_args.
	static_assert(hamon::same_as<
		decltype(hamon::basic_format_args(hamon::make_format_args(i))),
		hamon::basic_format_args<hamon::format_context>>);

	static_assert(hamon::same_as<
		decltype(hamon::basic_format_args(hamon::make_wformat_args(i))),
		hamon::basic_format_args<hamon::wformat_context>>);

	return true;
}

template <class Context, class To, class From>
void test(From value)
{
	auto store = hamon::make_format_args<Context>(value);
	const hamon::basic_format_args<Context> format_args{store};

	auto visitor = [v = To(value)](auto a)
		{
			(void)v;
			if constexpr (hamon::is_same_v<To, decltype(a)>)
			{
				EXPECT_TRUE(v == a);
			}
			else
			{
				EXPECT_TRUE(false);
			}
		};
#if 1//TEST_STD_VER >= 26 && defined(TEST_HAS_EXPLICIT_THIS_PARAMETER)
	format_args.get(0).visit(visitor);
#else
	(void)visitor;
//	std::visit_format_arg(visitor, format_args.get(0));
#endif
}

// Some types, as an extension, are stored in the variant. The Standard
// requires them to be observed as a handle.
template <class Context, class T>
void test_handle(T value)
{
	auto store = hamon::make_format_args<Context>(value);
	hamon::basic_format_args<Context> format_args{store};

	auto visitor = [](auto a)
		{
			(void)a;
			EXPECT_TRUE((hamon::is_same_v<decltype(a), typename hamon::basic_format_arg<Context>::handle>));
		};
#if 1//TEST_STD_VER >= 26 && defined(TEST_HAS_EXPLICIT_THIS_PARAMETER)
	format_args.get(0).visit(visitor);
#else
//	std::visit_format_arg(visitor, format_args.get(0));
#endif
}

// Test specific for string and string_view.
//
// Since both result in a string_view there's no need to pass this as a
// template argument.
template <class Context, class From>
void test_string_view(From value)
{
	auto store = hamon::make_format_args<Context>(value);
	const hamon::basic_format_args<Context> format_args{store};

	using CharT = typename Context::char_type;
	using To = hamon::basic_string_view<CharT>;
	using V = hamon::basic_string<CharT>;

	auto visitor = [v = V(value.begin(), value.end())](auto a)
		{
			if constexpr (hamon::is_same_v<To, decltype(a)>)
			{
				EXPECT_TRUE(v == a);
			}
			else
			{
				EXPECT_TRUE(false);
			}
		};
#if 1//TEST_STD_VER >= 26 && defined(TEST_HAS_EXPLICIT_THIS_PARAMETER)
	format_args.get(0).visit(visitor);
#else
//	std::visit_format_arg(visitor, format_args.get(0));
#endif
}

template <typename CharT>
void get_test()
{
	using Context   = hamon::basic_format_context<CharT*, CharT>;
	using char_type = typename Context::char_type;
	hamon::basic_string<char_type> empty;
	hamon::basic_string<char_type> str = HAMON_STATICALLY_WIDEN(char_type, "abc");

	// Test boolean types.

	test<Context, bool>(true);
	test<Context, bool>(false);

	// Test char_type types.

	test<Context, char_type, char_type>('a');
	test<Context, char_type, char_type>('z');
	test<Context, char_type, char_type>('0');
	test<Context, char_type, char_type>('9');

	// Test char types.

	if (hamon::is_same_v<char_type, char>)
	{
		// char to char -> char
		test<Context, char_type, char>('a');
		test<Context, char_type, char>('z');
		test<Context, char_type, char>('0');
		test<Context, char_type, char>('9');
	}
	else
	{
		if (hamon::is_same_v<char_type, wchar_t>)
		{
			// char to wchar_t -> wchar_t
			test<Context, wchar_t, char>('a');
			test<Context, wchar_t, char>('z');
			test<Context, wchar_t, char>('0');
			test<Context, wchar_t, char>('9');
		}
		else if (hamon::is_signed_v<char>)
		{
			// char to char_type -> int
			// This happens when Context::char_type is a char8_t, char16_t, or
			// char32_t and char is a signed type.
			// Note if sizeof(char_type) > sizeof(int) this test fails. If there are
			// platforms where that occurs extra tests need to be added for char32_t
			// testing it against a long long.
			test<Context, int, char>('a');
			test<Context, int, char>('z');
			test<Context, int, char>('0');
			test<Context, int, char>('9');
		}
		else
		{
			// char to char_type -> unsigned
			// This happens when Context::char_type is a char8_t, char16_t, or
			// char32_t and char is an unsigned type.
			// Note if sizeof(char_type) > sizeof(unsigned) this test fails. If there
			// are platforms where that occurs extra tests need to be added for
			// char32_t testing it against an unsigned long long.
			test<Context, unsigned, char>('a');
			test<Context, unsigned, char>('z');
			test<Context, unsigned, char>('0');
			test<Context, unsigned, char>('9');
		}
	}

	// Test signed integer types.

	test<Context, int, signed char>(hamon::numeric_limits<signed char>::min());
	test<Context, int, signed char>(0);
	test<Context, int, signed char>(hamon::numeric_limits<signed char>::max());

	test<Context, int, short>(hamon::numeric_limits<short>::min());
	test<Context, int, short>(hamon::numeric_limits<signed char>::min());
	test<Context, int, short>(0);
	test<Context, int, short>(hamon::numeric_limits<signed char>::max());
	test<Context, int, short>(hamon::numeric_limits<short>::max());

	test<Context, int, int>(hamon::numeric_limits<int>::min());
	test<Context, int, int>(hamon::numeric_limits<short>::min());
	test<Context, int, int>(hamon::numeric_limits<signed char>::min());
	test<Context, int, int>(0);
	test<Context, int, int>(hamon::numeric_limits<signed char>::max());
	test<Context, int, int>(hamon::numeric_limits<short>::max());
	test<Context, int, int>(hamon::numeric_limits<int>::max());

	using LongToType =
		hamon::conditional_t<sizeof(long) == sizeof(int), int, long long>;

	test<Context, LongToType, long>(hamon::numeric_limits<long>::min());
	test<Context, LongToType, long>(hamon::numeric_limits<int>::min());
	test<Context, LongToType, long>(hamon::numeric_limits<short>::min());
	test<Context, LongToType, long>(hamon::numeric_limits<signed char>::min());
	test<Context, LongToType, long>(0);
	test<Context, LongToType, long>(hamon::numeric_limits<signed char>::max());
	test<Context, LongToType, long>(hamon::numeric_limits<short>::max());
	test<Context, LongToType, long>(hamon::numeric_limits<int>::max());
	test<Context, LongToType, long>(hamon::numeric_limits<long>::max());

	test<Context, long long, long long>(hamon::numeric_limits<long long>::min());
	test<Context, long long, long long>(hamon::numeric_limits<long>::min());
	test<Context, long long, long long>(hamon::numeric_limits<int>::min());
	test<Context, long long, long long>(hamon::numeric_limits<short>::min());
	test<Context, long long, long long>(hamon::numeric_limits<signed char>::min());
	test<Context, long long, long long>(0);
	test<Context, long long, long long>(hamon::numeric_limits<signed char>::max());
	test<Context, long long, long long>(hamon::numeric_limits<short>::max());
	test<Context, long long, long long>(hamon::numeric_limits<int>::max());
	test<Context, long long, long long>(hamon::numeric_limits<long>::max());
	test<Context, long long, long long>(hamon::numeric_limits<long long>::max());

	// Test unsigned integer types.

	test<Context, unsigned, unsigned char>(0);
	test<Context, unsigned, unsigned char>(
		hamon::numeric_limits<unsigned char>::max());

	test<Context, unsigned, unsigned short>(0);
	test<Context, unsigned, unsigned short>(
		hamon::numeric_limits<unsigned char>::max());
	test<Context, unsigned, unsigned short>(
		hamon::numeric_limits<unsigned short>::max());

	test<Context, unsigned, unsigned>(0);
	test<Context, unsigned, unsigned>(hamon::numeric_limits<unsigned char>::max());
	test<Context, unsigned, unsigned>(hamon::numeric_limits<unsigned short>::max());
	test<Context, unsigned, unsigned>(hamon::numeric_limits<unsigned>::max());

	using UnsignedLongToType =
		hamon::conditional_t<sizeof(unsigned long) == sizeof(unsigned), unsigned,
		unsigned long long>;

	test<Context, UnsignedLongToType, unsigned long>(0);
	test<Context, UnsignedLongToType, unsigned long>(
		hamon::numeric_limits<unsigned char>::max());
	test<Context, UnsignedLongToType, unsigned long>(
		hamon::numeric_limits<unsigned short>::max());
	test<Context, UnsignedLongToType, unsigned long>(
		hamon::numeric_limits<unsigned>::max());
	test<Context, UnsignedLongToType, unsigned long>(
		hamon::numeric_limits<unsigned long>::max());

	test<Context, unsigned long long, unsigned long long>(0);
	test<Context, unsigned long long, unsigned long long>(
		hamon::numeric_limits<unsigned char>::max());
	test<Context, unsigned long long, unsigned long long>(
		hamon::numeric_limits<unsigned short>::max());
	test<Context, unsigned long long, unsigned long long>(
		hamon::numeric_limits<unsigned>::max());
	test<Context, unsigned long long, unsigned long long>(
		hamon::numeric_limits<unsigned long>::max());
	test<Context, unsigned long long, unsigned long long>(
		hamon::numeric_limits<unsigned long long>::max());

	// Test floating point types.

	test<Context, float, float>(-hamon::numeric_limits<float>::max());
	test<Context, float, float>(-hamon::numeric_limits<float>::min());
	test<Context, float, float>(-0.0);
	test<Context, float, float>(0.0);
	test<Context, float, float>(hamon::numeric_limits<float>::min());
	test<Context, float, float>(hamon::numeric_limits<float>::max());

	test<Context, double, double>(-hamon::numeric_limits<double>::max());
	test<Context, double, double>(-hamon::numeric_limits<double>::min());
	test<Context, double, double>(-0.0);
	test<Context, double, double>(0.0);
	test<Context, double, double>(hamon::numeric_limits<double>::min());
	test<Context, double, double>(hamon::numeric_limits<double>::max());

	test<Context, long double, long double>(
		-hamon::numeric_limits<long double>::max());
	test<Context, long double, long double>(
		-hamon::numeric_limits<long double>::min());
	test<Context, long double, long double>(-0.0);
	test<Context, long double, long double>(0.0);
	test<Context, long double, long double>(
		hamon::numeric_limits<long double>::min());
	test<Context, long double, long double>(
		hamon::numeric_limits<long double>::max());

	// Test const char_type pointer types.

	test<Context, const char_type*, const char_type*>(empty.c_str());
	test<Context, const char_type*, const char_type*>(str.c_str());

	// Test string_view types.

	test<Context, hamon::basic_string_view<char_type>>(
		hamon::basic_string_view<char_type>());
	test<Context, hamon::basic_string_view<char_type>,
		hamon::basic_string_view<char_type>>(empty);
	test<Context, hamon::basic_string_view<char_type>,
		hamon::basic_string_view<char_type>>(str);

	// Test string types.

	test<Context, hamon::basic_string_view<char_type>>(
		hamon::basic_string<char_type>());
	test<Context, hamon::basic_string_view<char_type>,
		hamon::basic_string<char_type>>(empty);
	test<Context, hamon::basic_string_view<char_type>,
		hamon::basic_string<char_type>>(str);

	// Test pointer types.

	test<Context, const void*>(nullptr);
}

#undef VERIFY

GTEST_TEST(FormatTest, BasicFormatArgsTest)
{
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(ctor_test<char>());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(ctor_test<wchar_t>());

	get_test<char>();
	get_test<wchar_t>();
}

}	// namespace basic_format_args_test

}	// namespace hamon_format_test
