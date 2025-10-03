/**
 *	@file	unit_test_format_basic_format_arg.cpp
 *
 *	@brief	basic_format_arg のテスト
 *
 *	template<class Context>
 *	class basic_format_arg;
 */

#include <hamon/format/basic_format_arg.hpp>
#include <hamon/format/basic_format_args.hpp>
#include <hamon/format/basic_format_context.hpp>
#include <hamon/format/make_format_args.hpp>
#include <hamon/algorithm/equal.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/detail/statically_widen.hpp>
#include <hamon/limits.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_signed.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"
#include "format_test_helper.hpp"

namespace hamon_format_test
{

namespace basic_format_arg_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
/*HAMON_CXX20_CONSTEXPR*/ bool test()
{
	using Context = hamon::basic_format_context<CharT*, CharT>;
	{
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::basic_format_arg<Context>{});
		hamon::basic_format_arg<Context> format_arg{};
		HAMON_ASSERT_NOEXCEPT_TRUE(!format_arg);
		VERIFY(!format_arg);
		HAMON_ASSERT_NOEXCEPT_TRUE(static_cast<bool>(format_arg));
		VERIFY(!static_cast<bool>(format_arg));
	}
	return true;
}

namespace visit_test
{

template <class Context, class To, class From>
void test(From value)
{
	auto store = hamon::make_format_args<Context>(value);
	hamon::basic_format_args<Context> format_args{ store };

	//LIBCPP_ASSERT(format_args.__size() == 1);
	EXPECT_TRUE(format_args.get(0));

	auto result = format_args.get(0).visit(
		[v = To(value)](auto a) -> To
		{
			if constexpr (hamon::is_same_v<To, decltype(a)>)
			{
				EXPECT_TRUE(v == a);
				return a;
			}
			else
			{
				EXPECT_TRUE(false);
				return {};
			}
		});

	using ct = hamon::common_type_t<From, To>;
	EXPECT_TRUE(static_cast<ct>(result) == static_cast<ct>(value));
}

// Some types, as an extension, are stored in the variant. The Standard
// requires them to be observed as a handle.
template <class Context, class T>
void test_handle(T value)
{
	auto store = hamon::make_format_args<Context>(value);
	hamon::basic_format_args<Context> format_args{ store };

	//LIBCPP_ASSERT(format_args.__size() == 1);
	EXPECT_TRUE(format_args.get(0));

	format_args.get(0).visit(
		[](auto a)
		{
			EXPECT_TRUE((hamon::is_same_v<decltype(a), typename hamon::basic_format_arg<Context>::handle>));
		});
}

// Test specific for string and string_view.
//
// Since both result in a string_view there's no need to pass this as a
// template argument.
template <class Context, class From>
void test_string_view(From value)
{
	auto store = hamon::make_format_args<Context>(value);
	hamon::basic_format_args<Context> format_args{ store };

	//LIBCPP_ASSERT(format_args.__size() == 1);
	EXPECT_TRUE(format_args.get(0));

	using CharT = typename Context::char_type;
	using To = hamon::basic_string_view<CharT>;
	using V = hamon::basic_string<CharT>;

	auto result = format_args.get(0).visit(
		[v = V(value.begin(), value.end())](auto a) -> To
		{
			if constexpr (hamon::is_same_v<To, decltype(a)>)
			{
				EXPECT_TRUE(v == a);
				return a;
			}
			else
			{
				EXPECT_TRUE(false);
				return {};
			}
		});

	EXPECT_TRUE(hamon::equal(value.begin(), value.end(), result.begin(), result.end()));
}

template <class CharT>
void test()
{
	using Context = hamon::basic_format_context<CharT*, CharT>;
	hamon::basic_string<CharT> empty;
	hamon::basic_string<CharT> str = HAMON_STATICALLY_WIDEN(CharT, "abc");

	// Test boolean types.

	test<Context, bool>(true);
	test<Context, bool>(false);

	// Test CharT types.

	test<Context, CharT, CharT>('a');
	test<Context, CharT, CharT>('z');
	test<Context, CharT, CharT>('0');
	test<Context, CharT, CharT>('9');

	// Test char types.

	if (hamon::is_same_v<CharT, char>)
	{
		// char to char -> char
		test<Context, CharT, char>('a');
		test<Context, CharT, char>('z');
		test<Context, CharT, char>('0');
		test<Context, CharT, char>('9');
	}
	else
	{
		if (hamon::is_same_v<CharT, wchar_t>)
		{
			// char to wchar_t -> wchar_t
			test<Context, wchar_t, char>('a');
			test<Context, wchar_t, char>('z');
			test<Context, wchar_t, char>('0');
			test<Context, wchar_t, char>('9');
		}
		else if (hamon::is_signed_v<char>)
		{
			// char to CharT -> int
			// This happens when CharT is a char8_t, char16_t, or char32_t and char
			// is a signed type.
			// Note if sizeof(CharT) > sizeof(int) this test fails. If there are
			// platforms where that occurs extra tests need to be added for char32_t
			// testing it against a long long.
			test<Context, int, char>('a');
			test<Context, int, char>('z');
			test<Context, int, char>('0');
			test<Context, int, char>('9');
		}
		else
		{
			// char to CharT -> unsigned
			// This happens when CharT is a char8_t, char16_t, or char32_t and char
			// is an unsigned type.
			// Note if sizeof(CharT) > sizeof(unsigned) this test fails. If there are
			// platforms where that occurs extra tests need to be added for char32_t
			// testing it against an unsigned long long.
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

	using LongToType = hamon::conditional_t<sizeof(long) == sizeof(int), int, long long>;

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
	test<Context, unsigned, unsigned char>(hamon::numeric_limits<unsigned char>::max());

	test<Context, unsigned, unsigned short>(0);
	test<Context, unsigned, unsigned short>(hamon::numeric_limits<unsigned char>::max());
	test<Context, unsigned, unsigned short>(hamon::numeric_limits<unsigned short>::max());

	test<Context, unsigned, unsigned>(0);
	test<Context, unsigned, unsigned>(hamon::numeric_limits<unsigned char>::max());
	test<Context, unsigned, unsigned>(hamon::numeric_limits<unsigned short>::max());
	test<Context, unsigned, unsigned>(hamon::numeric_limits<unsigned>::max());

	using UnsignedLongToType =
		hamon::conditional_t<sizeof(unsigned long) == sizeof(unsigned), unsigned, unsigned long long>;

	test<Context, UnsignedLongToType, unsigned long>(0);
	test<Context, UnsignedLongToType, unsigned long>(hamon::numeric_limits<unsigned char>::max());
	test<Context, UnsignedLongToType, unsigned long>(hamon::numeric_limits<unsigned short>::max());
	test<Context, UnsignedLongToType, unsigned long>(hamon::numeric_limits<unsigned>::max());
	test<Context, UnsignedLongToType, unsigned long>(hamon::numeric_limits<unsigned long>::max());

	test<Context, unsigned long long, unsigned long long>(0);
	test<Context, unsigned long long, unsigned long long>(hamon::numeric_limits<unsigned char>::max());
	test<Context, unsigned long long, unsigned long long>(hamon::numeric_limits<unsigned short>::max());
	test<Context, unsigned long long, unsigned long long>(hamon::numeric_limits<unsigned>::max());
	test<Context, unsigned long long, unsigned long long>(hamon::numeric_limits<unsigned long>::max());
	test<Context, unsigned long long, unsigned long long>(hamon::numeric_limits<unsigned long long>::max());

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

	test<Context, long double, long double>(-hamon::numeric_limits<long double>::max());
	test<Context, long double, long double>(-hamon::numeric_limits<long double>::min());
	test<Context, long double, long double>(-0.0);
	test<Context, long double, long double>(0.0);
	test<Context, long double, long double>(hamon::numeric_limits<long double>::min());
	test<Context, long double, long double>(hamon::numeric_limits<long double>::max());

	// Test const CharT pointer types.

	test<Context, const CharT*, const CharT*>(empty.c_str());
	test<Context, const CharT*, const CharT*>(str.c_str());

	// Test string_view types.

	{
		using From = hamon::basic_string_view<CharT>;

		test_string_view<Context>(From());
		test_string_view<Context>(From(empty.c_str()));
		test_string_view<Context>(From(str.c_str()));
	}

	//{
	//	using From = hamon::basic_string_view<CharT, constexpr_char_traits<CharT>>;

	//	test_string_view<Context>(From());
	//	test_string_view<Context>(From(empty.c_str()));
	//	test_string_view<Context>(From(str.c_str()));
	//}

	// Test string types.

	{
		using From = hamon::basic_string<CharT>;

		test_string_view<Context>(From());
		test_string_view<Context>(From(empty.c_str()));
		test_string_view<Context>(From(str.c_str()));
	}

	//{
	//	using From = hamon::basic_string<CharT, constexpr_char_traits<CharT>, hamon::allocator<CharT>>;

	//	test_string_view<Context>(From());
	//	test_string_view<Context>(From(empty.c_str()));
	//	test_string_view<Context>(From(str.c_str()));
	//}

	//{
	//	using From = hamon::basic_string<CharT, hamon::char_traits<CharT>, min_allocator<CharT>>;

	//	test_string_view<Context>(From());
	//	test_string_view<Context>(From(empty.c_str()));
	//	test_string_view<Context>(From(str.c_str()));
	//}

	//{
	//	using From = hamon::basic_string<CharT, constexpr_char_traits<CharT>, min_allocator<CharT>>;

	//	test_string_view<Context>(From());
	//	test_string_view<Context>(From(empty.c_str()));
	//	test_string_view<Context>(From(str.c_str()));
	//}

	// Test pointer types.

	test<Context, const void*>(nullptr);
	int i = 0;
	test<Context, const void*>(static_cast<void*>(&i));
	const int ci = 0;
	test<Context, const void*>(static_cast<const void*>(&ci));

	// Test handle types
	test_handle<Context>(status::foo);
}

}	// namespace visit_test

namespace visit_r_test
{

// The expected result type shouldn't matter,therefore use a hardcoded value for simplicity.
using ExpectedResultType = bool;
constexpr ExpectedResultType visited{ true };

template <class ExpectedR>
ExpectedR make_expected_result()
{
	if constexpr (hamon::is_same_v<ExpectedR, bool>)
	{
		return true;
	}
	else if constexpr (hamon::is_same_v<ExpectedR, long>)
	{
		return 192812079084L;
	}
	else
	{
		return "visited";
	}
}

template <class Context, class To, class ExpectedR, class From>
void test(From value, const ExpectedR& expectedValue)
{
	auto store = hamon::make_format_args<Context>(value);
	hamon::basic_format_args<Context> format_args{ store };

	//LIBCPP_ASSERT(format_args.__size() == 1);
	EXPECT_TRUE(format_args.get(0));

	// member
	{
		hamon::same_as<ExpectedR> decltype(auto) result =
			format_args.get(0).template visit<ExpectedR>([v = To(value)](auto a) -> ExpectedR {
			if constexpr (hamon::is_same_v<To, decltype(a)>) {
				EXPECT_TRUE(v == a);
				return make_expected_result<ExpectedR>();
			}
			else {
				EXPECT_TRUE(false);
				return {};
			}
		});

		EXPECT_TRUE(result == expectedValue);
	}
}

// Some types, as an extension, are stored in the variant. The Standard
// requires them to be observed as a handle.
template <class Context, class T, class ExpectedR>
void test_handle(T value, ExpectedR expectedValue)
{
	auto store = hamon::make_format_args<Context>(value);
	hamon::basic_format_args<Context> format_args{ store };

	//LIBCPP_ASSERT(format_args.__size() == 1);
	EXPECT_TRUE(format_args.get(0));

	hamon::same_as<ExpectedR> decltype(auto) result = format_args.get(0).template visit<ExpectedR>([](auto a) -> ExpectedR {
		EXPECT_TRUE((hamon::is_same_v<decltype(a), typename hamon::basic_format_arg<Context>::handle>));

		return make_expected_result<ExpectedR>();
	});

	EXPECT_TRUE(result == expectedValue);
}

// Test specific for string and string_view.
//
// Since both result in a string_view there's no need to pass this as a
// template argument.
template <class Context, class ExpectedR, class From>
void test_string_view(From value, ExpectedR expectedValue)
{
	auto store = hamon::make_format_args<Context>(value);
	hamon::basic_format_args<Context> format_args{ store };

	//LIBCPP_ASSERT(format_args.__size() == 1);
	EXPECT_TRUE(format_args.get(0));

	using CharT = typename Context::char_type;
	using To = hamon::basic_string_view<CharT>;
	using V = hamon::basic_string<CharT>;

	hamon::same_as<ExpectedR> decltype(auto) result =
		format_args.get(0).template visit<ExpectedR>([v = V(value.begin(), value.end())](auto a) -> ExpectedR {
		if constexpr (hamon::is_same_v<To, decltype(a)>) {
			EXPECT_TRUE(v == a);
			return make_expected_result<ExpectedR>();
		}
		else {
			EXPECT_TRUE(false);
			return {};
		}
	});

	EXPECT_TRUE(result == expectedValue);
}

template <class CharT>
void test()
{
	using Context = hamon::basic_format_context<CharT*, CharT>;
	hamon::basic_string<CharT> empty;
	hamon::basic_string<CharT> str = HAMON_STATICALLY_WIDEN(CharT, "abc");

	// Test boolean types.

	test<Context, bool, ExpectedResultType>(true, visited);
	test<Context, bool, ExpectedResultType>(false, visited);

	test<Context, bool, hamon::string>(true, "visited");
	test<Context, bool, hamon::string>(false, "visited");

	// Test CharT types.

	test<Context, CharT, ExpectedResultType, CharT>('a', visited);
	test<Context, CharT, ExpectedResultType, CharT>('z', visited);
	test<Context, CharT, ExpectedResultType, CharT>('0', visited);
	test<Context, CharT, ExpectedResultType, CharT>('9', visited);

	// Test char types.

	if (hamon::is_same_v<CharT, char>)
	{
		// char to char -> char
		test<Context, CharT, ExpectedResultType, char>('a', visited);
		test<Context, CharT, ExpectedResultType, char>('z', visited);
		test<Context, CharT, ExpectedResultType, char>('0', visited);
		test<Context, CharT, ExpectedResultType, char>('9', visited);
	}
	else
	{
		if (hamon::is_same_v<CharT, wchar_t>)
		{
			// char to wchar_t -> wchar_t
			test<Context, wchar_t, ExpectedResultType, char>('a', visited);
			test<Context, wchar_t, ExpectedResultType, char>('z', visited);
			test<Context, wchar_t, ExpectedResultType, char>('0', visited);
			test<Context, wchar_t, ExpectedResultType, char>('9', visited);
		}
		else if (hamon::is_signed_v<char>)
		{
			// char to CharT -> int
			// This happens when CharT is a char8_t, char16_t, or char32_t and char
			// is a signed type.
			// Note if sizeof(CharT) > sizeof(int) this test fails. If there are
			// platforms where that occurs extra tests need to be added for char32_t
			// testing it against a long long.
			test<Context, int, ExpectedResultType, char>('a', visited);
			test<Context, int, ExpectedResultType, char>('z', visited);
			test<Context, int, ExpectedResultType, char>('0', visited);
			test<Context, int, ExpectedResultType, char>('9', visited);
		}
		else
		{
			// char to CharT -> unsigned
			// This happens when CharT is a char8_t, char16_t, or char32_t and char
			// is an unsigned type.
			// Note if sizeof(CharT) > sizeof(unsigned) this test fails. If there are
			// platforms where that occurs extra tests need to be added for char32_t
			// testing it against an unsigned long long.
			test<Context, unsigned, ExpectedResultType, char>('a', visited);
			test<Context, unsigned, ExpectedResultType, char>('z', visited);
			test<Context, unsigned, ExpectedResultType, char>('0', visited);
			test<Context, unsigned, ExpectedResultType, char>('9', visited);
		}
	}

	// Test signed integer types.

	test<Context, int, ExpectedResultType, signed char>(hamon::numeric_limits<signed char>::min(), visited);
	test<Context, int, ExpectedResultType, signed char>(0, visited);
	test<Context, int, ExpectedResultType, signed char>(hamon::numeric_limits<signed char>::max(), visited);

	test<Context, int, ExpectedResultType, short>(hamon::numeric_limits<short>::min(), visited);
	test<Context, int, ExpectedResultType, short>(hamon::numeric_limits<signed char>::min(), visited);
	test<Context, int, ExpectedResultType, short>(0, visited);
	test<Context, int, ExpectedResultType, short>(hamon::numeric_limits<signed char>::max(), visited);
	test<Context, int, ExpectedResultType, short>(hamon::numeric_limits<short>::max(), visited);

	test<Context, int, ExpectedResultType, int>(hamon::numeric_limits<int>::min(), visited);
	test<Context, int, ExpectedResultType, int>(hamon::numeric_limits<short>::min(), visited);
	test<Context, int, ExpectedResultType, int>(hamon::numeric_limits<signed char>::min(), visited);
	test<Context, int, ExpectedResultType, int>(0, visited);
	test<Context, int, ExpectedResultType, int>(hamon::numeric_limits<signed char>::max(), visited);
	test<Context, int, ExpectedResultType, int>(hamon::numeric_limits<short>::max(), visited);
	test<Context, int, ExpectedResultType, int>(hamon::numeric_limits<int>::max(), visited);

	using LongToType = hamon::conditional_t<sizeof(long) == sizeof(int), int, long long>;

	test<Context, LongToType, ExpectedResultType, long>(hamon::numeric_limits<long>::min(), visited);
	test<Context, LongToType, ExpectedResultType, long>(hamon::numeric_limits<int>::min(), visited);
	test<Context, LongToType, ExpectedResultType, long>(hamon::numeric_limits<short>::min(), visited);
	test<Context, LongToType, ExpectedResultType, long>(hamon::numeric_limits<signed char>::min(), visited);
	test<Context, LongToType, ExpectedResultType, long>(0, visited);
	test<Context, LongToType, ExpectedResultType, long>(hamon::numeric_limits<signed char>::max(), visited);
	test<Context, LongToType, ExpectedResultType, long>(hamon::numeric_limits<short>::max(), visited);
	test<Context, LongToType, ExpectedResultType, long>(hamon::numeric_limits<int>::max(), visited);
	test<Context, LongToType, ExpectedResultType, long>(hamon::numeric_limits<long>::max(), visited);

	test<Context, long long, ExpectedResultType, long long>(hamon::numeric_limits<long long>::min(), visited);
	test<Context, long long, ExpectedResultType, long long>(hamon::numeric_limits<long>::min(), visited);
	test<Context, long long, ExpectedResultType, long long>(hamon::numeric_limits<int>::min(), visited);
	test<Context, long long, ExpectedResultType, long long>(hamon::numeric_limits<short>::min(), visited);
	test<Context, long long, ExpectedResultType, long long>(hamon::numeric_limits<signed char>::min(), visited);
	test<Context, long long, ExpectedResultType, long long>(0, visited);
	test<Context, long long, ExpectedResultType, long long>(hamon::numeric_limits<signed char>::max(), visited);
	test<Context, long long, ExpectedResultType, long long>(hamon::numeric_limits<short>::max(), visited);
	test<Context, long long, ExpectedResultType, long long>(hamon::numeric_limits<int>::max(), visited);
	test<Context, long long, ExpectedResultType, long long>(hamon::numeric_limits<long>::max(), visited);
	test<Context, long long, ExpectedResultType, long long>(hamon::numeric_limits<long long>::max(), visited);

	// Test unsigned integer types.

	test<Context, unsigned, ExpectedResultType, unsigned char>(0, visited);
	test<Context, unsigned, ExpectedResultType, unsigned char>(hamon::numeric_limits<unsigned char>::max(), visited);

	test<Context, unsigned, ExpectedResultType, unsigned short>(0, visited);
	test<Context, unsigned, ExpectedResultType, unsigned short>(hamon::numeric_limits<unsigned char>::max(), visited);
	test<Context, unsigned, ExpectedResultType, unsigned short>(hamon::numeric_limits<unsigned short>::max(), visited);

	test<Context, unsigned, ExpectedResultType, unsigned>(0, visited);
	test<Context, unsigned, ExpectedResultType, unsigned>(hamon::numeric_limits<unsigned char>::max(), visited);
	test<Context, unsigned, ExpectedResultType, unsigned>(hamon::numeric_limits<unsigned short>::max(), visited);
	test<Context, unsigned, ExpectedResultType, unsigned>(hamon::numeric_limits<unsigned>::max(), visited);

	using UnsignedLongToType =
		hamon::conditional_t<sizeof(unsigned long) == sizeof(unsigned), unsigned, unsigned long long>;

	test<Context, UnsignedLongToType, ExpectedResultType, unsigned long>(0, visited);
	test<Context, UnsignedLongToType, ExpectedResultType, unsigned long>(
		hamon::numeric_limits<unsigned char>::max(), visited);
	test<Context, UnsignedLongToType, ExpectedResultType, unsigned long>(
		hamon::numeric_limits<unsigned short>::max(), visited);
	test<Context, UnsignedLongToType, ExpectedResultType, unsigned long>(hamon::numeric_limits<unsigned>::max(), visited);
	test<Context, UnsignedLongToType, ExpectedResultType, unsigned long>(
		hamon::numeric_limits<unsigned long>::max(), visited);

	test<Context, unsigned long long, ExpectedResultType, unsigned long long>(0, visited);
	test<Context, unsigned long long, ExpectedResultType, unsigned long long>(
		hamon::numeric_limits<unsigned char>::max(), visited);
	test<Context, unsigned long long, ExpectedResultType, unsigned long long>(
		hamon::numeric_limits<unsigned short>::max(), visited);
	test<Context, unsigned long long, ExpectedResultType, unsigned long long>(
		hamon::numeric_limits<unsigned>::max(), visited);
	test<Context, unsigned long long, ExpectedResultType, unsigned long long>(
		hamon::numeric_limits<unsigned long>::max(), visited);
	test<Context, unsigned long long, ExpectedResultType, unsigned long long>(
		hamon::numeric_limits<unsigned long long>::max(), visited);

	// Test floating point types.

	test<Context, float, ExpectedResultType, float>(-hamon::numeric_limits<float>::max(), visited);
	test<Context, float, ExpectedResultType, float>(-hamon::numeric_limits<float>::min(), visited);
	test<Context, float, ExpectedResultType, float>(-0.0, visited);
	test<Context, float, ExpectedResultType, float>(0.0, visited);
	test<Context, float, ExpectedResultType, float>(hamon::numeric_limits<float>::min(), visited);
	test<Context, float, ExpectedResultType, float>(hamon::numeric_limits<float>::max(), visited);

	test<Context, double, ExpectedResultType, double>(-hamon::numeric_limits<double>::max(), visited);
	test<Context, double, ExpectedResultType, double>(-hamon::numeric_limits<double>::min(), visited);
	test<Context, double, ExpectedResultType, double>(-0.0, visited);
	test<Context, double, ExpectedResultType, double>(0.0, visited);
	test<Context, double, ExpectedResultType, double>(hamon::numeric_limits<double>::min(), visited);
	test<Context, double, ExpectedResultType, double>(hamon::numeric_limits<double>::max(), visited);

	test<Context, long double, ExpectedResultType, long double>(-hamon::numeric_limits<long double>::max(), visited);
	test<Context, long double, ExpectedResultType, long double>(-hamon::numeric_limits<long double>::min(), visited);
	test<Context, long double, ExpectedResultType, long double>(-0.0, visited);
	test<Context, long double, ExpectedResultType, long double>(0.0, visited);
	test<Context, long double, ExpectedResultType, long double>(hamon::numeric_limits<long double>::min(), visited);
	test<Context, long double, ExpectedResultType, long double>(hamon::numeric_limits<long double>::max(), visited);

	// Test const CharT pointer types.

	test<Context, const CharT*, ExpectedResultType, const CharT*>(empty.c_str(), visited);
	test<Context, const CharT*, ExpectedResultType, const CharT*>(str.c_str(), visited);

	// Test string_view types.

	{
		using From = hamon::basic_string_view<CharT>;

		test_string_view<Context, ExpectedResultType>(From(), visited);
		test_string_view<Context, ExpectedResultType>(From(empty.c_str()), visited);
		test_string_view<Context, ExpectedResultType>(From(str.c_str()), visited);
	}
	//{
	//	using From = hamon::basic_string_view<CharT, constexpr_char_traits<CharT>>;

	//	test_string_view<Context, ExpectedResultType>(From(), visited);
	//	test_string_view<Context, ExpectedResultType>(From(empty.c_str()), visited);
	//	test_string_view<Context, ExpectedResultType>(From(str.c_str()), visited);
	//}

	// Test string types.

	{
		using From = hamon::basic_string<CharT>;

		test_string_view<Context, ExpectedResultType>(From(), visited);
		test_string_view<Context, ExpectedResultType>(From(empty.c_str()), visited);
		test_string_view<Context, ExpectedResultType>(From(str.c_str()), visited);
	}

	//{
	//	using From = hamon::basic_string<CharT, constexpr_char_traits<CharT>, hamon::allocator<CharT>>;

	//	test_string_view<Context, ExpectedResultType>(From(), visited);
	//	test_string_view<Context, ExpectedResultType>(From(empty.c_str()), visited);
	//	test_string_view<Context, ExpectedResultType>(From(str.c_str()), visited);
	//}

	//{
	//	using From = hamon::basic_string<CharT, hamon::char_traits<CharT>, min_allocator<CharT>>;

	//	test_string_view<Context, ExpectedResultType>(From(), visited);
	//	test_string_view<Context, ExpectedResultType>(From(empty.c_str()), visited);
	//	test_string_view<Context, ExpectedResultType>(From(str.c_str()), visited);
	//}

	//{
	//	using From = hamon::basic_string<CharT, constexpr_char_traits<CharT>, min_allocator<CharT>>;

	//	test_string_view<Context, ExpectedResultType>(From(), visited);
	//	test_string_view<Context, ExpectedResultType>(From(empty.c_str()), visited);
	//	test_string_view<Context, ExpectedResultType>(From(str.c_str()), visited);
	//}

	// Test pointer types.

	test<Context, const void*, ExpectedResultType>(nullptr, visited);
	int i = 0;
	test<Context, const void*, ExpectedResultType>(static_cast<void*>(&i), visited);
	const int ci = 0;
	test<Context, const void*, ExpectedResultType>(static_cast<const void*>(&ci), visited);

	// Test handle types
	test_handle<Context, status, ExpectedResultType>(status::foo, visited);
}

}	// namespace visit_r_test

#undef VERIFY

GTEST_TEST(FormatTest, BasicFormatArgTest)
{
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<char>());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<wchar_t>());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<char8_t>());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<char16_t>());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<char32_t>());

	visit_test::test<char>();
	visit_test::test<wchar_t>();

	visit_r_test::test<char>();
	visit_r_test::test<wchar_t>();
}

}	// namespace basic_format_arg_test

}	// namespace hamon_format_test
