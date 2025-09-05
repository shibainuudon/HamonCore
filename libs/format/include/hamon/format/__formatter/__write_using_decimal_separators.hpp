/**
 *	@file	__write_using_decimal_separators.hpp
 *
 *	@brief	__write_using_decimal_separators の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___WRITE_USING_DECIMAL_SEPARATORS_HPP
#define HAMON_FORMAT___FORMATTER___WRITE_USING_DECIMAL_SEPARATORS_HPP

#include <hamon/format/__format_spec/__parsed_specifications.hpp>
#include <hamon/format/__format_spec/__alignment.hpp>
#include <hamon/format/__format_spec/__type.hpp>
#include <hamon/format/__formatter/__padding_size.hpp>
#include <hamon/format/__formatter/__copy.hpp>
#include <hamon/format/__formatter/__fill.hpp>
#include <hamon/format/__formatter/__transform.hpp>
#include <hamon/format/other/__hex_to_upper.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/string.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{

namespace __formatter
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4267)	// '' から '' に変換しました。データが失われているかもしれません。
HAMON_WARNING_DISABLE_GCC("-Wconversion")
HAMON_WARNING_DISABLE_CLANG("-Wsign-conversion")
HAMON_WARNING_DISABLE_CLANG("-Wshorten-64-to-32")

template <class _OutIt, hamon::contiguous_iterator _Iterator, class _CharT>
	requires hamon::same_as<char, hamon::iter_value_t<_Iterator>>
_OutIt __write_using_decimal_separators(
	_OutIt __out_it,
	_Iterator __begin,
	_Iterator __first,
	_Iterator __last,
	hamon::string&& __grouping,
	_CharT __sep,
	__format_spec::__parsed_specifications<_CharT> __specs)
{
	int __size = (__first - __begin) +    // [sign][prefix]
		(__last - __first) +     // data
		(__grouping.size() - 1); // number of separator characters

	__formatter::__padding_size_result __padding = {0, 0};
	if (__specs.__alignment_ == __format_spec::__alignment::__zero_padding)
	{
		// Write [sign][prefix].
		__out_it = __formatter::__copy(__begin, __first, hamon::move(__out_it));

		if (__specs.__width_ > __size)
		{
			// Write zero padding.
			__padding.__before_ = __specs.__width_ - __size;
			__out_it            = __formatter::__fill(hamon::move(__out_it), __specs.__width_ - __size, _CharT('0'));
		}
	}
	else
	{
		if (__specs.__width_ > __size)
		{
			// Determine padding and write padding.
			__padding = __formatter::__padding_size(__size, __specs.__width_, __specs.__alignment_);

			__out_it = __formatter::__fill(hamon::move(__out_it), __padding.__before_, __specs.__fill_);
		}
		// Write [sign][prefix].
		__out_it = __formatter::__copy(__begin, __first, hamon::move(__out_it));
	}

	auto __r = __grouping.rbegin();
	auto __e = __grouping.rend() - 1;
//	_LIBCPP_ASSERT_INTERNAL(
//		__r != __e, "The slow grouping formatting is used while there will be no separators written.");

	// The output is divided in small groups of numbers to write:
	// - A group before the first separator.
	// - A separator and a group, repeated for the number of separators.
	// - A group after the last separator.
	// This loop achieves that process by testing the termination condition
	// midway in the loop.
	//
	// TODO FMT This loop evaluates the loop invariant `__parser.__type !=
	// _Flags::_Type::__hexadecimal_upper_case` for every iteration. (This test
	// happens in the __write call.) Benchmark whether making two loops and
	// hoisting the invariant is worth the effort.
	while (true)
	{
		if (__specs.__std_.__type_ == __format_spec::__type::__hexadecimal_upper_case)
		{
			__last   = __first + *__r;
			__out_it = __formatter::__transform(__first, __last, hamon::move(__out_it), hamon::__hex_to_upper);
			__first  = __last;
		}
		else
		{
			__out_it = __formatter::__copy(__first, *__r, hamon::move(__out_it));
			__first += *__r;
		}

		if (__r == __e)
		{
			break;
		}

		++__r;
		*__out_it++ = __sep;
	}

	return __formatter::__fill(hamon::move(__out_it), __padding.__after_, __specs.__fill_);
}

HAMON_WARNING_POP()

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___WRITE_USING_DECIMAL_SEPARATORS_HPP
