/**
 *	@file	range_formatter.hpp
 *
 *	@brief	range_formatter の定義
 */

#ifndef HAMON_FORMAT_RANGE_FORMATTER_HPP
#define HAMON_FORMAT_RANGE_FORMATTER_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::range_formatter;

}	// namespace hamon

#else

#include <hamon/format/formattable.hpp>
#include <hamon/format/formatter.hpp>
#include <hamon/format/format_error.hpp>
#include <hamon/format/basic_format_context.hpp>
#include <hamon/format/__format_spec/__fields_range.hpp>
#include <hamon/format/__format_spec/__parsed_specifications.hpp>
#include <hamon/format/__format_spec/__type.hpp>
#include <hamon/format/__format_spec/__parser.hpp>
#include <hamon/format/__format_spec/__alignment.hpp>
#include <hamon/format/__format/__retarget_buffer.hpp>
#include <hamon/format/__formatter/__write_string_no_precision.hpp>
#include <hamon/format/detail/__fmt_pair_like.hpp>
#include <hamon/algorithm/ranges/copy.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/detail/statically_widen.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/contiguous_range.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/ranges/data.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits/remove_cvref.hpp>

namespace hamon
{

// 28.5.7.2 Class template range_formatter[format.range.formatter]

template <class _Tp, class _CharT = char>
	requires hamon::same_as<hamon::remove_cvref_t<_Tp>, _Tp>&& hamon::formattable<_Tp, _CharT>
struct range_formatter
{
	constexpr void
	set_separator(hamon::basic_string_view<_CharT> __separator) noexcept
	{
		__separator_ = __separator;
	}

	constexpr void
	set_brackets(hamon::basic_string_view<_CharT> __opening_bracket, hamon::basic_string_view<_CharT> __closing_bracket) noexcept
	{
		__opening_bracket_ = __opening_bracket;
		__closing_bracket_ = __closing_bracket;
	}

	constexpr hamon::formatter<_Tp, _CharT>& underlying() noexcept { return __underlying_; }
	constexpr const hamon::formatter<_Tp, _CharT>& underlying() const noexcept { return __underlying_; }

	template <class _ParseContext>
	constexpr typename _ParseContext::iterator parse(_ParseContext& __ctx)
	{
		auto __begin = __parser_.__parse(__ctx, __format_spec::__fields_range);
		auto __end = __ctx.end();
		// Note the cases where __begin == __end in this code only happens when the
		// replacement-field has no terminating }, or when the parse is manually
		// called with a format-spec. The former is an error and the latter means
		// using a formatter without the format functions or print.
		if (__begin == __end) [[unlikely]]
		{
			return __parse_empty_range_underlying_spec(__ctx, __begin);
		}

		// The n field overrides a possible m type, therefore delay applying the
		// effect of n until the type has been procesed.
		__parse_type(__begin, __end);
		if (__parser_.__clear_brackets_)
		{
			set_brackets({}, {});
		}

		if (__begin == __end) [[unlikely]]
		{
			return __parse_empty_range_underlying_spec(__ctx, __begin);
		}

		bool __has_range_underlying_spec = *__begin == _CharT(':');
		if (__has_range_underlying_spec)
		{
			// range-underlying-spec:
			//   :  format-spec
			++__begin;
		}
		else if (__begin != __end && *__begin != _CharT('}'))
		{
			// When there is no underlaying range the current parse should have
			// consumed the format-spec. If not, the not consumed input will be
			// processed by the underlying. For example {:-} for a range in invalid,
			// the sign field is not present. Without this check the underlying_ will
			// get -} as input which my be valid.
			hamon::detail::throw_format_error("The format specifier should consume the input or end with a '}'");
		}

		__ctx.advance_to(__begin);
		__begin = __underlying_.parse(__ctx);

		// This test should not be required if __has_range_underlying_spec is false.
		// However this test makes sure the underlying formatter left the parser in
		// a valid state. (Note this is not a full protection against evil parsers.
		// For example
		//   } this is test for the next argument {}
		//   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^
		// could consume more than it should.
		if (__begin != __end && *__begin != _CharT('}'))
		{
			hamon::detail::throw_format_error("The format specifier should consume the input or end with a '}'");
		}

		if (__parser_.__type_ != __format_spec::__type::__default)
		{
			// [format.range.formatter]/6
			//   If the range-type is s or ?s, then there shall be no n option and no
			//   range-underlying-spec.
			if (__parser_.__clear_brackets_)
			{
				if (__parser_.__type_ == __format_spec::__type::__string)
				{
					hamon::detail::throw_format_error("The n option and type s can't be used together");
				}
				hamon::detail::throw_format_error("The n option and type ?s can't be used together");
			}
			if (__has_range_underlying_spec)
			{
				if (__parser_.__type_ == __format_spec::__type::__string)
				{
					hamon::detail::throw_format_error("Type s and an underlying format specification can't be used together");
				}
				hamon::detail::throw_format_error("Type ?s and an underlying format specification can't be used together");
			}
		}
		else if (!__has_range_underlying_spec)
		{
			hamon::__set_debug_format(__underlying_);
		}

		return __begin;
	}

	template <hamon::ranges::input_range _Rp, class _FormatContext>
		requires hamon::formattable<hamon::ranges::range_reference_t<_Rp>, _CharT>&&
	hamon::same_as<hamon::remove_cvref_t<hamon::ranges::range_reference_t<_Rp>>, _Tp>
	typename _FormatContext::iterator format(_Rp&& __range, _FormatContext& __ctx) const
	{
		__format_spec::__parsed_specifications<_CharT> __specs = __parser_.__get_parsed_std_specifications(__ctx);

		if (!__specs.__has_width())
		{
			return __format_range(__range, __ctx, __specs);
		}

		// The size of the buffer needed is:
		// - open bracket characters
		// - close bracket character
		// - n elements where every element may have a different size
		// - (n -1) separators
		// The size of the element is hard to predict, knowing the type helps but
		// it depends on the format-spec. As an initial estimate we guess 6
		// characters.
		// Typically both brackets are 1 character and the separator is 2
		// characters. Which means there will be
		//   (n - 1) * 2 + 1 + 1 = n * 2 character
		// So estimate 8 times the range size as buffer.
		std::size_t __capacity_hint = 0;
		if constexpr (hamon::ranges::sized_range<_Rp>)
		{
			__capacity_hint = 8 * hamon::ranges::size(__range);
		}
		__format::__retarget_buffer<_CharT> __buffer{ __capacity_hint };
		hamon::basic_format_context<typename __format::__retarget_buffer<_CharT>::__iterator, _CharT> __c{
			__buffer.__make_output_iterator(), __ctx };

		__format_range(__range, __c, __specs);

		return __formatter::__write_string_no_precision(__buffer.__view(), __ctx.out(), __specs);
	}

	template <hamon::ranges::input_range _Rp, class _FormatContext>
	typename _FormatContext::iterator
	__format_range(_Rp&& __range, _FormatContext& __ctx, __format_spec::__parsed_specifications<_CharT> __specs) const
	{
		if constexpr (hamon::same_as<_Tp, _CharT>)
		{
			switch (__specs.__std_.__type_)
			{
			case __format_spec::__type::__string:
			case __format_spec::__type::__debug:
				return __format_as_string(__range, __ctx, __specs.__std_.__type_ == __format_spec::__type::__debug);
			default:
				return __format_as_sequence(__range, __ctx);
			}
		}
		else
		{
			return __format_as_sequence(__range, __ctx);
		}
	}

	template <hamon::ranges::input_range _Rp, class _FormatContext>
	typename _FormatContext::iterator
	__format_as_string(_Rp&& __range, _FormatContext& __ctx, bool __debug_format) const
	{
		// When the range is contiguous use a basic_string_view instead to avoid a
		// copy of the underlying data. The basic_string_view formatter
		// specialization is the "basic" string formatter in libc++.
		if constexpr (hamon::ranges::contiguous_range<_Rp> && hamon::ranges::sized_range<_Rp>)
		{
			hamon::formatter<hamon::basic_string_view<_CharT>, _CharT> __formatter;
			if (__debug_format)
			{
				__formatter.set_debug_format();
			}
			return __formatter.format(
				hamon::basic_string_view<_CharT>{
					hamon::ranges::data(__range),
					hamon::ranges::size(__range),
				},
				__ctx);
		}
		else
		{
			hamon::formatter<hamon::basic_string<_CharT>, _CharT> __formatter;
			if (__debug_format)
			{
				__formatter.set_debug_format();
			}
			return __formatter.format(hamon::basic_string<_CharT>{hamon::from_range, __range}, __ctx);
		}
	}

	template <hamon::ranges::input_range _Rp, class _FormatContext>
	typename _FormatContext::iterator
	__format_as_sequence(_Rp&& __range, _FormatContext& __ctx) const
	{
		__ctx.advance_to(hamon::ranges::copy(__opening_bracket_, __ctx.out()).out);
		bool __use_separator = false;
		for (auto&& __e : __range)
		{
			if (__use_separator)
			{
				__ctx.advance_to(hamon::ranges::copy(__separator_, __ctx.out()).out);
			}
			else
			{
				__use_separator = true;
			}

			__ctx.advance_to(__underlying_.format(__e, __ctx));
		}

		return hamon::ranges::copy(__closing_bracket_, __ctx.out()).out;
	}

	__format_spec::__parser<_CharT> __parser_{ .__alignment_ = __format_spec::__alignment::__left };

private:
	template <hamon::contiguous_iterator _Iterator>
	constexpr void __parse_type(_Iterator& __begin, _Iterator __end)
	{
		switch (*__begin)
		{
		case _CharT('m'):
			if constexpr (hamon::detail::__fmt_pair_like<_Tp>)
			{
				set_brackets(HAMON_STATICALLY_WIDEN(_CharT, "{"), HAMON_STATICALLY_WIDEN(_CharT, "}"));
				set_separator(HAMON_STATICALLY_WIDEN(_CharT, ", "));
				++__begin;
			}
			else
			{
				hamon::detail::throw_format_error("Type m requires a pair or a tuple with two elements");
			}
			break;

		case _CharT('s'):
			if constexpr (hamon::same_as<_Tp, _CharT>)
			{
				__parser_.__type_ = __format_spec::__type::__string;
				++__begin;
			}
			else
			{
				hamon::detail::throw_format_error("Type s requires character type as formatting argument");
			}
			break;

		case _CharT('?'):
			++__begin;
			if (__begin == __end || *__begin != _CharT('s'))
			{
				hamon::detail::throw_format_error("The format specifier should consume the input or end with a '}'");
			}

			if constexpr (hamon::same_as<_Tp, _CharT>)
			{
				__parser_.__type_ = __format_spec::__type::__debug;
				++__begin;
			}
			else
			{
				hamon::detail::throw_format_error("Type ?s requires character type as formatting argument");
			}
		}
	}

	template <class _ParseContext>
	constexpr typename _ParseContext::iterator
	__parse_empty_range_underlying_spec(_ParseContext& __ctx, typename _ParseContext::iterator __begin)
	{
		__ctx.advance_to(__begin);
		[[maybe_unused]] typename _ParseContext::iterator __result = __underlying_.parse(__ctx);
//		_LIBCPP_ASSERT_INTERNAL(__result == __begin,
//			"the underlying's parse function should not advance the input beyond the end of the input");
		return __begin;
	}

	hamon::formatter<_Tp, _CharT> __underlying_;
	hamon::basic_string_view<_CharT> __separator_ = HAMON_STATICALLY_WIDEN(_CharT, ", ");
	hamon::basic_string_view<_CharT> __opening_bracket_ = HAMON_STATICALLY_WIDEN(_CharT, "[");
	hamon::basic_string_view<_CharT> __closing_bracket_ = HAMON_STATICALLY_WIDEN(_CharT, "]");
};

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_RANGE_FORMATTER_HPP
