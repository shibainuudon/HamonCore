/**
 *	@file	__write.hpp
 *
 *	@brief	__write の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___WRITE_HPP
#define HAMON_FORMAT___FORMATTER___WRITE_HPP

#include <hamon/format/__formatter/__copy.hpp>
#include <hamon/format/__formatter/__fill.hpp>
#include <hamon/format/__formatter/__padding_size.hpp>
#include <hamon/format/__format_spec/__parsed_specifications.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/string_view.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{

namespace __formatter
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wsign-conversion")

/// Writes the input to the output with the required padding.
///
/// Since the output column width is specified the function can be used for
/// ASCII and Unicode output.
///
/// \pre \a __size <= \a __width. Using this function when this pre-condition
///      doesn't hold incurs an unwanted overhead.
///
/// \param __str       The string to write.
/// \param __out_it    The output iterator to write to.
/// \param __specs     The parsed formatting specifications.
/// \param __size      The (estimated) output column width. When the elements
///                    to be written are ASCII the following condition holds
///                    \a __size == \a __last - \a __first.
///
/// \returns           An iterator pointing beyond the last element written.
///
/// \note The type of the elements in range [\a __first, \a __last) can differ
/// from the type of \a __specs. Integer output uses \c std::to_chars for its
/// conversion, which means the [\a __first, \a __last) always contains elements
/// of the type \c char.
template <class _CharT, class _ParserCharT>
auto
__write(hamon::basic_string_view<_CharT> __str,
		hamon::output_iterator<const _CharT&> auto __out_it,
		__format_spec::__parsed_specifications<_ParserCharT> __specs,
		ptrdiff_t __size) -> decltype(__out_it)
{
	if (__size >= __specs.__width_)
	{
		return __formatter::__copy(__str, hamon::move(__out_it));
	}

	__padding_size_result __padding = __formatter::__padding_size(__size, __specs.__width_, __specs.__std_.__alignment_);
	__out_it                        = __formatter::__fill(hamon::move(__out_it), __padding.__before_, __specs.__fill_);
	__out_it                        = __formatter::__copy(__str, hamon::move(__out_it));
	return __formatter::__fill(hamon::move(__out_it), __padding.__after_, __specs.__fill_);
}

HAMON_WARNING_POP()

template <hamon::contiguous_iterator _Iterator, class _ParserCharT>
auto
__write(_Iterator __first,
		_Iterator __last,
		hamon::output_iterator<const hamon::iter_value_t<_Iterator>&> auto __out_it,
		__format_spec::__parsed_specifications<_ParserCharT> __specs,
		ptrdiff_t __size) -> decltype(__out_it)
{
//	_LIBCPP_ASSERT_VALID_INPUT_RANGE(__first <= __last, "Not a valid range");
	return __formatter::__write(hamon::basic_string_view{__first, __last}, hamon::move(__out_it), __specs, __size);
}

/// \overload
///
/// Calls the function above where \a __size = \a __last - \a __first.
template <hamon::contiguous_iterator _Iterator, class _ParserCharT>
auto
__write(_Iterator __first,
		_Iterator __last,
		hamon::output_iterator<const hamon::iter_value_t<_Iterator>&> auto __out_it,
		__format_spec::__parsed_specifications<_ParserCharT> __specs) -> decltype(__out_it)
{
//	_LIBCPP_ASSERT_VALID_INPUT_RANGE(__first <= __last, "Not a valid range");
	return __formatter::__write(__first, __last, hamon::move(__out_it), __specs, __last - __first);
}

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___WRITE_HPP
