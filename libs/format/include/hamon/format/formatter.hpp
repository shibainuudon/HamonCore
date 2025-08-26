/**
 *	@file	formatter.hpp
 *
 *	@brief	formatter の定義
 */

#ifndef HAMON_FORMAT_FORMATTER_HPP
#define HAMON_FORMAT_FORMATTER_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::formatter;

}	// namespace hamon

#else

#if 0

#include <hamon/format/enable_nonlocking_formatter_optimization.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits/is_same.hpp>

namespace hamon
{

namespace detail
{

// [format.formatter.spec]/7
// If F is a disabled specialization of formatter, these values are false:
// - is_default_constructible_v<F>,
// - is_copy_constructible_v<F>,
// - is_move_constructible_v<F>,
// - is_copy_assignable_v<F>, and
// - is_move_assignable_v<F>.
struct disabled_formatter
{
	disabled_formatter()                                     = delete;
	disabled_formatter(const disabled_formatter&)            = delete;
	disabled_formatter& operator=(const disabled_formatter&) = delete;
};

template <typename charT>
struct formatter_char
{
	static_assert(hamon::is_same<charT, char>::value || hamon::is_same<charT, wchar_t>::value, "");
};

template <typename charT>
struct formatter_string
{
	static_assert(hamon::is_same<charT, char>::value || hamon::is_same<charT, wchar_t>::value, "");
};

template <typename charT>
struct formatter_integer
{
	static_assert(hamon::is_same<charT, char>::value || hamon::is_same<charT, wchar_t>::value, "");

	template <typename ParseContext>
	constexpr typename ParseContext::iterator
	parse(ParseContext& __ctx);/*
	{
		typename ParseContext::iterator __result = __parser_.__parse(__ctx, __format_spec::__fields_integral);
		__format_spec::__process_parsed_integer(__parser_, "an integer");
		return __result;
	}*/

	template <integral _Tp, typename FormatContext>
	typename FormatContext::iterator
	format(_Tp __value, FormatContext& __ctx) const;/*
	{
		__format_spec::__parsed_specifications<_CharT> __specs = __parser_.__get_parsed_std_specifications(__ctx);

		if (__specs.__std_.__type_ == __format_spec::__type::__char)
		{
			return __formatter::__format_char(__value, __ctx.out(), __specs);
		}

		using _Type = __make_32_64_or_128_bit_t<_Tp>;
		static_assert(!is_void<_Type>::value, "unsupported integral type used in __formatter_integer::__format");

		// Reduce the number of instantiation of the integer formatter
		return __formatter::__format_integer(static_cast<_Type>(__value), __ctx, __specs);
	}*/

//	__format_spec::__parser<_CharT> __parser_;
};

template <typename charT>
struct formatter_floating_point
{
	static_assert(hamon::is_same<charT, char>::value || hamon::is_same<charT, wchar_t>::value, "");
};

}	// namespace detail

// 28.5.6 Formatter[format.formatter]

// 28.5.6.4 Formatter specializations[format.formatter.spec]

template <typename T, typename charT = char>
struct formatter : hamon::detail::disabled_formatter{};

// [format.formatter.spec]/2.1
template <>
struct formatter<char, char>
	: public hamon::detail::formatter_char<char> {};

template <>
struct formatter<char, wchar_t>
	: public hamon::detail::formatter_char<wchar_t> {};

template <>
struct formatter<wchar_t, wchar_t>
	: public hamon::detail::formatter_char<wchar_t> {};

template <>
inline constexpr bool enable_nonlocking_formatter_optimization<char> = true;
template <>
inline constexpr bool enable_nonlocking_formatter_optimization<wchar_t> = true;

// [format.formatter.spec]/2.2
template <>
struct formatter<char*, char>
	: public hamon::detail::formatter_string<char>
{
};

template <>
struct formatter<const char*, char>
	: public hamon::detail::formatter_string<char>
{
};

template <hamon::size_t N>
struct formatter<char[N], char>
	: public hamon::detail::formatter_string<char>
{
};

template <typename traits, typename Allocator>
struct formatter<hamon::basic_string<char, traits, Allocator>, char>
	: public hamon::detail::formatter_string<char>
{
};

template <typename traits>
struct formatter<hamon::basic_string_view<char, traits>, char>
	: public hamon::detail::formatter_string<char>
{
};

template <>
struct formatter<wchar_t*, wchar_t>
	: public hamon::detail::formatter_string<wchar_t>
{
};

template <>
struct formatter<const wchar_t*, wchar_t>
	: public hamon::detail::formatter_string<wchar_t>
{
};

template <hamon::size_t N>
struct formatter<wchar_t[N], wchar_t>
	: public hamon::detail::formatter_string<wchar_t>
{
};

template <typename traits, typename Allocator>
struct formatter<hamon::basic_string<wchar_t, traits, Allocator>, wchar_t>
	: public hamon::detail::formatter_string<wchar_t>
{
};

template <typename traits>
struct formatter<hamon::basic_string_view<wchar_t, traits>, wchar_t>
	: public hamon::detail::formatter_string<wchar_t>
{
};


// [format.formatter.spec]/4.1
template <>
struct formatter<char*, wchar_t>
	: hamon::detail::disabled_formatter{};

template <>
struct formatter<const char*, wchar_t>
	: hamon::detail::disabled_formatter{};

template <hamon::size_t N>
struct formatter<char[N], wchar_t>
	: hamon::detail::disabled_formatter{};

template <typename traits, typename Allocator>
struct formatter<hamon::basic_string<char, traits, Allocator>, wchar_t>
	: hamon::detail::disabled_formatter{};

template <typename traits>
struct formatter<hamon::basic_string_view<char, traits>, wchar_t>
	: hamon::detail::disabled_formatter{};


template <>
inline constexpr bool enable_nonlocking_formatter_optimization<char*> = true;
template <>
inline constexpr bool enable_nonlocking_formatter_optimization<const char*> = true;
template <hamon::size_t N>
inline constexpr bool enable_nonlocking_formatter_optimization<char[N]> = true;
template <typename traits, typename Allocator>
inline constexpr bool enable_nonlocking_formatter_optimization<hamon::basic_string<char, traits, Allocator>> = true;
template <typename traits>
inline constexpr bool enable_nonlocking_formatter_optimization<hamon::basic_string_view<char, traits>> = true;

template <>
inline constexpr bool enable_nonlocking_formatter_optimization<wchar_t*> = true;
template <>
inline constexpr bool enable_nonlocking_formatter_optimization<const wchar_t*> = true;
template <hamon::size_t N>
inline constexpr bool enable_nonlocking_formatter_optimization<wchar_t[N]> = true;
template <typename traits, typename Allocator>
inline constexpr bool enable_nonlocking_formatter_optimization<hamon::basic_string<wchar_t, traits, Allocator>> = true;
template <typename traits>
inline constexpr bool enable_nonlocking_formatter_optimization<hamon::basic_string_view<wchar_t, traits>> = true;

// [format.formatter.spec]/2.3

template <>
struct formatter<signed char, char> : public hamon::detail::formatter_integer<char> {};
template <>
struct formatter<short, char> : public hamon::detail::formatter_integer<char> {};
template <>
struct formatter<int, char> : public hamon::detail::formatter_integer<char> {};
template <>
struct formatter<long, char> : public hamon::detail::formatter_integer<char> {};
template <>
struct formatter<long long, char> : public hamon::detail::formatter_integer<char> {};

template <>
struct formatter<unsigned char, char> : public hamon::detail::formatter_integer<char> {};
template <>
struct formatter<unsigned short, char> : public hamon::detail::formatter_integer<char> {};
template <>
struct formatter<unsigned, char> : public hamon::detail::formatter_integer<char> {};
template <>
struct formatter<unsigned long, char> : public hamon::detail::formatter_integer<char> {};
template <>
struct formatter<unsigned long long, char> : public hamon::detail::formatter_integer<char> {};

template <>
struct formatter<signed char, wchar_t> : public hamon::detail::formatter_integer<wchar_t> {};
template <>
struct formatter<short, wchar_t> : public hamon::detail::formatter_integer<wchar_t> {};
template <>
struct formatter<int, wchar_t> : public hamon::detail::formatter_integer<wchar_t> {};
template <>
struct formatter<long, wchar_t> : public hamon::detail::formatter_integer<wchar_t> {};
template <>
struct formatter<long long, wchar_t> : public hamon::detail::formatter_integer<wchar_t> {};

template <>
struct formatter<unsigned char, wchar_t> : public hamon::detail::formatter_integer<wchar_t> {};
template <>
struct formatter<unsigned short, wchar_t> : public hamon::detail::formatter_integer<wchar_t> {};
template <>
struct formatter<unsigned, wchar_t> : public hamon::detail::formatter_integer<wchar_t> {};
template <>
struct formatter<unsigned long, wchar_t> : public hamon::detail::formatter_integer<wchar_t> {};
template <>
struct formatter<unsigned long long, wchar_t> : public hamon::detail::formatter_integer<wchar_t> {};

template <>
inline constexpr bool enable_nonlocking_formatter_optimization<signed char> = true;
template <>
inline constexpr bool enable_nonlocking_formatter_optimization<short> = true;
template <>
inline constexpr bool enable_nonlocking_formatter_optimization<int> = true;
template <>
inline constexpr bool enable_nonlocking_formatter_optimization<long> = true;
template <>
inline constexpr bool enable_nonlocking_formatter_optimization<long long> = true;

template <>
inline constexpr bool enable_nonlocking_formatter_optimization<unsigned char> = true;
template <>
inline constexpr bool enable_nonlocking_formatter_optimization<unsigned short> = true;
template <>
inline constexpr bool enable_nonlocking_formatter_optimization<unsigned> = true;
template <>
inline constexpr bool enable_nonlocking_formatter_optimization<unsigned long> = true;
template <>
inline constexpr bool enable_nonlocking_formatter_optimization<unsigned long long> = true;

template <>
struct formatter<float, char> : public hamon::detail::formatter_floating_point<char> {};
template <>
struct formatter<double, char> : public hamon::detail::formatter_floating_point<char> {};
template <>
struct formatter<long double, char> : public hamon::detail::formatter_floating_point<char> {};

template <>
struct formatter<float, wchar_t> : public hamon::detail::formatter_floating_point<wchar_t> {};
template <>
struct formatter<double, wchar_t> : public hamon::detail::formatter_floating_point<wchar_t> {};
template <>
struct formatter<long double, wchar_t> : public hamon::detail::formatter_floating_point<wchar_t> {};

template <>
inline constexpr bool enable_nonlocking_formatter_optimization<float> = true;
template <>
inline constexpr bool enable_nonlocking_formatter_optimization<double> = true;
template <>
inline constexpr bool enable_nonlocking_formatter_optimization<long double> = true;

}	// namespace hamon

#endif

#endif

#endif // HAMON_FORMAT_FORMATTER_HPP
