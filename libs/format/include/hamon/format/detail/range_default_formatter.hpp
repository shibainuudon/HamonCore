/**
 *	@file	range_default_formatter.hpp
 *
 *	@brief	range_default_formatter の定義
 */

#ifndef HAMON_FORMAT_DETAIL_RANGE_DEFAULT_FORMATTER_HPP
#define HAMON_FORMAT_DETAIL_RANGE_DEFAULT_FORMATTER_HPP

#include <hamon/format/detail/fmt_maybe_const.hpp>
#include <hamon/format/detail/__fmt_pair_like.hpp>
#include <hamon/format/range_format.hpp>
#include <hamon/format/range_formatter.hpp>
#include <hamon/format/formatter.hpp>
#include <hamon/detail/statically_widen.hpp>
#include <hamon/ranges/concepts/contiguous_range.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/ranges/data.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/remove_cvref.hpp>

namespace hamon
{

namespace detail
{

template <hamon::range_format _Kp, hamon::ranges::input_range _Rp, class _CharT>
struct __range_default_formatter;


// 28.5.7.3 Class template range-default-formatter[format.range.fmtdef]
template <hamon::ranges::input_range _Rp, class _CharT>
struct __range_default_formatter<hamon::range_format::sequence, _Rp, _CharT>
{
private:
	using __maybe_const_r = hamon::detail::fmt_maybe_const<_Rp, _CharT>;
	hamon::range_formatter<hamon::remove_cvref_t<hamon::ranges::range_reference_t<__maybe_const_r>>, _CharT> __underlying_;

public:
	constexpr void
	set_separator(hamon::basic_string_view<_CharT> __separator) noexcept
	{
		__underlying_.set_separator(__separator);
	}

	constexpr void
	set_brackets(hamon::basic_string_view<_CharT> __opening_bracket, hamon::basic_string_view<_CharT> __closing_bracket) noexcept
	{
		__underlying_.set_brackets(__opening_bracket, __closing_bracket);
	}

	template <class _ParseContext>
	constexpr typename _ParseContext::iterator parse(_ParseContext& __ctx)
	{
		return __underlying_.parse(__ctx);
	}

	template <class _FormatContext>
	typename _FormatContext::iterator
	format(__maybe_const_r& __range, _FormatContext& __ctx) const
	{
		return __underlying_.format(__range, __ctx);
	}
};

// 28.5.7.4 Specialization of range-default-formatter for maps[format.range.fmtmap]
template <hamon::ranges::input_range _Rp, class _CharT>
struct __range_default_formatter<hamon::range_format::map, _Rp, _CharT>
{
private:
	using __maybe_const_map = hamon::detail::fmt_maybe_const<_Rp, _CharT>;
	using __element_type = hamon::remove_cvref_t<hamon::ranges::range_reference_t<__maybe_const_map>>;
	hamon::range_formatter<__element_type, _CharT> __underlying_;

public:
	constexpr __range_default_formatter()
		requires(hamon::detail::__fmt_pair_like<__element_type>)
	{
		__underlying_.set_brackets(HAMON_STATICALLY_WIDEN(_CharT, "{"), HAMON_STATICALLY_WIDEN(_CharT, "}"));
		__underlying_.underlying().set_brackets({}, {});
		__underlying_.underlying().set_separator(HAMON_STATICALLY_WIDEN(_CharT, ": "));
	}

	template <class _ParseContext>
	constexpr typename _ParseContext::iterator
	parse(_ParseContext& __ctx)
	{
		return __underlying_.parse(__ctx);
	}

	template <class _FormatContext>
	typename _FormatContext::iterator
	format(__maybe_const_map& __range, _FormatContext& __ctx) const
	{
		return __underlying_.format(__range, __ctx);
	}
};

// 28.5.7.5 Specialization of range-default-formatter for sets[format.range.fmtset]
template <hamon::ranges::input_range _Rp, class _CharT>
struct __range_default_formatter<hamon::range_format::set, _Rp, _CharT>
{
private:
	using __maybe_const_set = hamon::detail::fmt_maybe_const<_Rp, _CharT>;
	using __element_type = hamon::remove_cvref_t<hamon::ranges::range_reference_t<__maybe_const_set>>;
	hamon::range_formatter<__element_type, _CharT> __underlying_;

public:
	constexpr __range_default_formatter()
	{
		__underlying_.set_brackets(HAMON_STATICALLY_WIDEN(_CharT, "{"), HAMON_STATICALLY_WIDEN(_CharT, "}"));
	}

	template <class _ParseContext>
	constexpr typename _ParseContext::iterator
	parse(_ParseContext& __ctx)
	{
		return __underlying_.parse(__ctx);
	}

	template <class _FormatContext>
	typename _FormatContext::iterator
	format(__maybe_const_set& __range, _FormatContext& __ctx) const
	{
		return __underlying_.format(__range, __ctx);
	}
};

// 28.5.7.6 Specialization of range-default-formatter for strings[format.range.fmtstr]
template <hamon::range_format _Kp, hamon::ranges::input_range _Rp, class _CharT>
	requires(_Kp == hamon::range_format::string || _Kp == hamon::range_format::debug_string)
struct __range_default_formatter<_Kp, _Rp, _CharT>
{
private:
	// This deviates from the Standard, there the exposition only type is
	//   formatter<basic_string<charT>, charT> underlying_;
	// Using a string_view allows the format function to avoid a copy of the
	// input range when it is a contigious range.
	hamon::formatter<hamon::basic_string_view<_CharT>, _CharT> __underlying_;

public:
	template <class _ParseContext>
	constexpr typename _ParseContext::iterator
	parse(_ParseContext& __ctx)
	{
		typename _ParseContext::iterator __i = __underlying_.parse(__ctx);
		if constexpr (_Kp == hamon::range_format::debug_string)
		{
			__underlying_.set_debug_format();
		}
		return __i;
	}

	template <class _FormatContext>
	typename _FormatContext::iterator
	format(hamon::conditional_t<hamon::ranges::input_range<const _Rp>, const _Rp&, _Rp&> __range, _FormatContext& __ctx) const
	{
		// When the range is contiguous use a hamon::basic_string_view instead to avoid a
		// copy of the underlying data. The hamon::basic_string_view formatter
		// specialization is the "basic" string formatter in libc++.
		if constexpr (hamon::ranges::contiguous_range<_Rp> && hamon::ranges::sized_range<_Rp>)
		{
			return __underlying_.format(hamon::basic_string_view<_CharT>{hamon::ranges::data(__range), hamon::ranges::size(__range)}, __ctx);
		}
		else
		{
			return __underlying_.format(hamon::basic_string<_CharT>{hamon::from_range, __range}, __ctx);
		}
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FORMAT_DETAIL_RANGE_DEFAULT_FORMATTER_HPP
