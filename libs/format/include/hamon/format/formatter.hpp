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

#include <hamon/format/formatter_fwd.hpp>
#include <hamon/format/__format/__fmt_char_type.hpp>
#include <hamon/format/__format/__formatter_bool.hpp>
#include <hamon/format/__format/__formatter_char.hpp>
#include <hamon/format/__format/__formatter_floating_point.hpp>
#include <hamon/format/__format/__formatter_integer.hpp>
#include <hamon/format/__format/__formatter_pointer.hpp>
#include <hamon/format/__format/__formatter_string.hpp>
#include <hamon/format/enable_nonlocking_formatter_optimization.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>

namespace hamon
{

struct __disabled_formatter
{
	__disabled_formatter()                                       = delete;
	__disabled_formatter(const __disabled_formatter&)            = delete;
	__disabled_formatter& operator=(const __disabled_formatter&) = delete;
};

/// The default formatter template.
///
/// [format.formatter.spec]/5
/// If F is a disabled specialization of formatter, these values are false:
/// - is_default_constructible_v<F>,
/// - is_copy_constructible_v<F>,
/// - is_move_constructible_v<F>,
/// - is_copy_assignable_v<F>, and
/// - is_move_assignable_v<F>.
template <class _Tp, class _CharT>
struct formatter : __disabled_formatter {};

template <class _Tp>
constexpr void __set_debug_format(_Tp& __formatter)
{
	if constexpr (requires { __formatter.set_debug_format(); })
	{
		__formatter.set_debug_format();
	}
}



template <__format::__fmt_char_type _CharT>
struct formatter<bool, _CharT> : public __format::__formatter_bool<_CharT> {};

template <>
inline constexpr bool enable_nonlocking_formatter_optimization<bool> = true;


template <>
struct formatter<char, char> : public __format::__formatter_char<char> {};

template <>
struct formatter<char, wchar_t> : public __format::__formatter_char<wchar_t> {};

template <>
struct formatter<wchar_t, wchar_t> : public __format::__formatter_char<wchar_t> {};

template <>
inline constexpr bool enable_nonlocking_formatter_optimization<char> = true;
template <>
inline constexpr bool enable_nonlocking_formatter_optimization<wchar_t> = true;

template <__format::__fmt_char_type _CharT>
struct formatter<float, _CharT> : public __format::__formatter_floating_point<_CharT> {};
template <__format::__fmt_char_type _CharT>
struct formatter<double, _CharT> : public __format::__formatter_floating_point<_CharT> {};
template <__format::__fmt_char_type _CharT>
struct formatter<long double, _CharT> : public __format::__formatter_floating_point<_CharT> {};

template <>
inline constexpr bool enable_nonlocking_formatter_optimization<float> = true;
template <>
inline constexpr bool enable_nonlocking_formatter_optimization<double> = true;
template <>
inline constexpr bool enable_nonlocking_formatter_optimization<long double> = true;

// Signed integral types.
template <__format::__fmt_char_type _CharT>
struct formatter<signed char, _CharT> : public __format::__formatter_integer<_CharT> {};
template <__format::__fmt_char_type _CharT>
struct formatter<short, _CharT> : public __format::__formatter_integer<_CharT> {};
template <__format::__fmt_char_type _CharT>
struct formatter<int, _CharT> : public __format::__formatter_integer<_CharT> {};
template <__format::__fmt_char_type _CharT>
struct formatter<long, _CharT> : public __format::__formatter_integer<_CharT> {};
template <__format::__fmt_char_type _CharT>
struct formatter<long long, _CharT> : public __format::__formatter_integer<_CharT> {};

// Unsigned integral types.
template <__format::__fmt_char_type _CharT>
struct formatter<unsigned char, _CharT> : public __format::__formatter_integer<_CharT> {};
template <__format::__fmt_char_type _CharT>
struct formatter<unsigned short, _CharT> : public __format::__formatter_integer<_CharT> {};
template <__format::__fmt_char_type _CharT>
struct formatter<unsigned, _CharT> : public __format::__formatter_integer<_CharT> {};
template <__format::__fmt_char_type _CharT>
struct formatter<unsigned long, _CharT> : public __format::__formatter_integer<_CharT> {};
template <__format::__fmt_char_type _CharT>
struct formatter<unsigned long long, _CharT> : public __format::__formatter_integer<_CharT> {};

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

// [format.formatter.spec]/2.4
// For each charT, the pointer type specializations template<>
// - struct formatter<nullptr_t, charT>;
// - template<> struct formatter<void*, charT>;
// - template<> struct formatter<const void*, charT>;
template <__format::__fmt_char_type _CharT>
struct formatter<nullptr_t, _CharT> : public __format::__formatter_pointer<_CharT> {};
template <__format::__fmt_char_type _CharT>
struct formatter<void*, _CharT> : public __format::__formatter_pointer<_CharT> {};
template <__format::__fmt_char_type _CharT>
struct formatter<const void*, _CharT> : public __format::__formatter_pointer<_CharT> {};

template <>
inline constexpr bool enable_nonlocking_formatter_optimization<nullptr_t> = true;
template <>
inline constexpr bool enable_nonlocking_formatter_optimization<void*> = true;
template <>
inline constexpr bool enable_nonlocking_formatter_optimization<const void*> = true;

// Formatter const char*.
template <__format::__fmt_char_type _CharT>
struct formatter<const _CharT*, _CharT> : public __format::__formatter_string<_CharT>
{
	using _Base = __format::__formatter_string<_CharT>;

	template <class _FormatContext>
	typename _FormatContext::iterator format(const _CharT* __str, _FormatContext& __ctx) const
	{
//		_LIBCPP_ASSERT_INTERNAL(__str, "The basic_format_arg constructor should have prevented an invalid pointer.");

		// Converting the input to a basic_string_view means the data is looped over twice;
		// - once to determine the length, and
		// - once to process the data.
		//
		// This sounds slower than writing the output directly. However internally
		// the output algorithms have optimizations for "bulk" operations, which
		// makes this faster than a single-pass character-by-character output.
		return _Base::format(hamon::basic_string_view<_CharT>(__str), __ctx);
	}
};

// Formatter char*.
template <__format::__fmt_char_type _CharT>
struct formatter<_CharT*, _CharT> : public formatter<const _CharT*, _CharT>
{
	using _Base = formatter<const _CharT*, _CharT>;

	template <class _FormatContext>
	typename _FormatContext::iterator format(_CharT* __str, _FormatContext& __ctx) const
	{
		return _Base::format(__str, __ctx);
	}
};

// Formatter char[].
template <__format::__fmt_char_type _CharT, size_t _Size>
struct formatter<_CharT[_Size], _CharT> : public __format::__formatter_string<_CharT>
{
	using _Base = __format::__formatter_string<_CharT>;

	template <class _FormatContext>
	typename _FormatContext::iterator
	format(const _CharT (&__str)[_Size], _FormatContext& __ctx) const
	{
		const _CharT* const __pzero = char_traits<_CharT>::find(__str, _Size, _CharT {});
//		_LIBCPP_ASSERT_VALID_INPUT_RANGE(__pzero != nullptr, "formatting a non-null-terminated array");
		return _Base::format(hamon::basic_string_view<_CharT>(__str, static_cast<size_t>(__pzero - __str)), __ctx);
	}
};

// Formatter std::string.
template <__format::__fmt_char_type _CharT, class _Traits, class _Allocator>
struct formatter<hamon::basic_string<_CharT, _Traits, _Allocator>, _CharT> : public __format::__formatter_string<_CharT>
{
	using _Base = __format::__formatter_string<_CharT>;

	template <class _FormatContext>
	typename _FormatContext::iterator
	format(const hamon::basic_string<_CharT, _Traits, _Allocator>& __str, _FormatContext& __ctx) const
	{
		// Drop _Traits and _Allocator to have one std::basic_string formatter.
		return _Base::format(hamon::basic_string_view<_CharT>(__str.data(), __str.size()), __ctx);
	}
};

// Formatter std::string_view.
template <__format::__fmt_char_type _CharT, class _Traits>
struct formatter<hamon::basic_string_view<_CharT, _Traits>, _CharT> : public __format::__formatter_string<_CharT>
{
	using _Base = __format::__formatter_string<_CharT>;

	template <class _FormatContext>
	typename _FormatContext::iterator
	format(hamon::basic_string_view<_CharT, _Traits> __str, _FormatContext& __ctx) const
	{
		// Drop _Traits to have one std::basic_string_view formatter.
		return _Base::format(hamon::basic_string_view<_CharT>(__str.data(), __str.size()), __ctx);
	}
};

template <>
struct formatter<char*, wchar_t> : __disabled_formatter {};
template <>
struct formatter<const char*, wchar_t> : __disabled_formatter {};
template <size_t _Size>
struct formatter<char[_Size], wchar_t> : __disabled_formatter {};
template <class _Traits, class _Allocator>
struct formatter<hamon::basic_string<char, _Traits, _Allocator>, wchar_t> : __disabled_formatter {};
template <class _Traits>
struct formatter<hamon::basic_string_view<char, _Traits>, wchar_t> : __disabled_formatter {};

template <>
inline constexpr bool enable_nonlocking_formatter_optimization<char*> = true;
template <>
inline constexpr bool enable_nonlocking_formatter_optimization<const char*> = true;
template <size_t _Size>
inline constexpr bool enable_nonlocking_formatter_optimization<char[_Size]> = true;
template <class _Traits, class _Allocator>
inline constexpr bool enable_nonlocking_formatter_optimization<hamon::basic_string<char, _Traits, _Allocator>> = true;
template <class _Traits>
inline constexpr bool enable_nonlocking_formatter_optimization<hamon::basic_string_view<char, _Traits>> = true;

template <>
inline constexpr bool enable_nonlocking_formatter_optimization<wchar_t*> = true;
template <>
inline constexpr bool enable_nonlocking_formatter_optimization<const wchar_t*> = true;
template <size_t _Size>
inline constexpr bool enable_nonlocking_formatter_optimization<wchar_t[_Size]> = true;
template <class _Traits, class _Allocator>
inline constexpr bool enable_nonlocking_formatter_optimization<hamon::basic_string<wchar_t, _Traits, _Allocator>> = true;
template <class _Traits>
inline constexpr bool enable_nonlocking_formatter_optimization<hamon::basic_string_view<wchar_t, _Traits>> = true;

}	// namespace hamon

#include <hamon/format/format_kind.hpp>
#include <hamon/format/range_format.hpp>
#include <hamon/format/formattable.hpp>
#include <hamon/format/enable_nonlocking_formatter_optimization.hpp>
#include <hamon/format/detail/range_default_formatter.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/range_reference_t.hpp>

namespace hamon
{

template <hamon::ranges::input_range _Rp, class _CharT>
	requires(hamon::format_kind<_Rp> != hamon::range_format::disabled &&
		hamon::formattable<hamon::ranges::range_reference_t<_Rp>, _CharT>)
struct formatter<_Rp, _CharT> : hamon::detail::__range_default_formatter<hamon::format_kind<_Rp>, _Rp, _CharT>
{};

template <hamon::ranges::input_range R>
	requires (hamon::format_kind<R> != hamon::range_format::disabled)
constexpr bool enable_nonlocking_formatter_optimization<R> = false;

}	// namespace hamon

#include <hamon/format/__format/__fmt_char_type.hpp>
#include <hamon/format/detail/__formatter_tuple.hpp>
#include <hamon/format/formattable.hpp>
#include <hamon/pair.hpp>
#include <hamon/tuple.hpp>

namespace hamon
{

// 28.5.9 Tuple formatter[format.tuple]

template <__format::__fmt_char_type _CharT, hamon::formattable<_CharT>... _Args>
struct formatter<hamon::pair<_Args...>, _CharT> : public hamon::detail::__formatter_tuple<_CharT, hamon::pair<_Args...>, _Args...> {};

template <__format::__fmt_char_type _CharT, hamon::formattable<_CharT>... _Args>
struct formatter<hamon::tuple<_Args...>, _CharT> : public hamon::detail::__formatter_tuple<_CharT, hamon::tuple<_Args...>, _Args...> {};

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_FORMATTER_HPP
