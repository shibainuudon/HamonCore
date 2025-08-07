/**
 *	@file	__formatter_tuple.hpp
 *
 *	@brief	__formatter_tuple の定義
 */

#ifndef HAMON_FORMAT_DETAIL___FORMATTER_TUPLE_HPP
#define HAMON_FORMAT_DETAIL___FORMATTER_TUPLE_HPP

#include <hamon/format/__format/__fmt_char_type.hpp>
#include <hamon/format/__format/__retarget_buffer.hpp>
#include <hamon/format/__format_spec/__fields_tuple.hpp>
#include <hamon/format/__format_spec/__parsed_specifications.hpp>
#include <hamon/format/__format_spec/__parser.hpp>
#include <hamon/format/__formatter/__write_string_no_precision.hpp>
#include <hamon/format/basic_format_context.hpp>
#include <hamon/format/formattable.hpp>
#include <hamon/format/formatter.hpp>
#include <hamon/format/format_error.hpp>
#include <hamon/algorithm/ranges/copy.hpp>
#include <hamon/detail/statically_widen.hpp>
#include <hamon/string_view.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/make_index_sequence.hpp>

namespace hamon
{

namespace detail
{

template <size_t... _Index, class _Function>
constexpr void __for_each_index_sequence(hamon::index_sequence<_Index...>, _Function __func)
{
	(__func.template operator() < _Index > (), ...);
}

// 28.5.9 Tuple formatter[format.tuple]

template <__format::__fmt_char_type _CharT, class _Tuple, hamon::formattable<_CharT>... _Args>
struct __formatter_tuple
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

	template <class _ParseContext>
	constexpr typename _ParseContext::iterator parse(_ParseContext& __ctx)
	{
		auto __begin = __parser_.__parse(__ctx, __format_spec::__fields_tuple);

		auto __end = __ctx.end();
		// Note 'n' is part of the type here
		if (__parser_.__clear_brackets_)
		{
			set_brackets({}, {});
		}
		else if (__begin != __end && *__begin == _CharT('m'))
		{
			if constexpr (sizeof...(_Args) == 2)
			{
				set_separator(HAMON_STATICALLY_WIDEN(_CharT, ": "));
				set_brackets({}, {});
				++__begin;
			}
			else
			{
				hamon::detail::throw_format_error("Type m requires a pair or a tuple with two elements");
			}
		}

		if (__begin != __end && *__begin != _CharT('}'))
		{
			hamon::detail::throw_format_error("The format specifier should consume the input or end with a '}'");
		}

		__ctx.advance_to(__begin);

		// [format.tuple]/7
		//   ... For each element e in underlying_, if e.set_debug_format()
		//   is a valid expression, calls e.set_debug_format().
		hamon::detail::__for_each_index_sequence(hamon::make_index_sequence<sizeof...(_Args)>(), [&]<size_t _Index> {
			auto& __formatter = hamon::get<_Index>(__underlying_);
			__formatter.parse(__ctx);
			// Unlike the range_formatter we don't guard against evil parsers. Since
			// this format-spec never has a format-spec for the underlying type
			// adding the test would give additional overhead.
			hamon::__set_debug_format(__formatter);
		});

		return __begin;
	}

	template <class _FormatContext>
	typename _FormatContext::iterator
	format(hamon::conditional_t<(hamon::formattable<const _Args, _CharT> && ...), const _Tuple&, _Tuple&> __tuple, _FormatContext& __ctx) const
	{
		__format_spec::__parsed_specifications<_CharT> __specs = __parser_.__get_parsed_std_specifications(__ctx);

		if (!__specs.__has_width())
		{
			return __format_tuple(__tuple, __ctx);
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
		__format::__retarget_buffer<_CharT> __buffer{ 8 * tuple_size_v<_Tuple> };
		hamon::basic_format_context<typename __format::__retarget_buffer<_CharT>::__iterator, _CharT> __c{__buffer.__make_output_iterator(), __ctx };

		__format_tuple(__tuple, __c);

		return __formatter::__write_string_no_precision(hamon::basic_string_view{ __buffer.__view() }, __ctx.out(), __specs);
	}

	template <class _FormatContext>
	typename _FormatContext::iterator __format_tuple(auto&& __tuple, _FormatContext& __ctx) const
	{
		__ctx.advance_to(hamon::ranges::copy(__opening_bracket_, __ctx.out()).out);

		hamon::detail::__for_each_index_sequence(hamon::make_index_sequence<sizeof...(_Args)>(), [&]<size_t _Index> {
			if constexpr (_Index)
			{
				__ctx.advance_to(hamon::ranges::copy(__separator_, __ctx.out()).out);
			}
			__ctx.advance_to(hamon::get<_Index>(__underlying_).format(hamon::get<_Index>(__tuple), __ctx));
		});

		return hamon::ranges::copy(__closing_bracket_, __ctx.out()).out;
	}

	__format_spec::__parser<_CharT> __parser_{ .__alignment_ = __format_spec::__alignment::__left };

private:
	hamon::tuple<hamon::formatter<hamon::remove_cvref_t<_Args>, _CharT>...> __underlying_;
	hamon::basic_string_view<_CharT> __separator_ = HAMON_STATICALLY_WIDEN(_CharT, ", ");
	hamon::basic_string_view<_CharT> __opening_bracket_ = HAMON_STATICALLY_WIDEN(_CharT, "(");
	hamon::basic_string_view<_CharT> __closing_bracket_ = HAMON_STATICALLY_WIDEN(_CharT, ")");
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FORMAT_DETAIL___FORMATTER_TUPLE_HPP
