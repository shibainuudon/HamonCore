/**
 *	@file	__copy.hpp
 *
 *	@brief	__copy の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___COPY_HPP
#define HAMON_FORMAT___FORMATTER___COPY_HPP

#include <hamon/format/__format/__fmt_char_type.hpp>
#include <hamon/format/__format/__output_buffer.hpp>
#include <hamon/format/__format/__retarget_buffer.hpp>
#include <hamon/algorithm/ranges/copy.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/back_insert_iterator.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/memory/to_address.hpp>
#include <hamon/string_view.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{

namespace __formatter
{

/// Copy wrapper.
///
/// This uses a "mass output function" of __format::__output_buffer when possible.
template <__format::__fmt_char_type _CharT, __format::__fmt_char_type _OutCharT = _CharT>
auto
__copy(hamon::basic_string_view<_CharT> __str, hamon::output_iterator<const _OutCharT&> auto __out_it)
-> decltype(__out_it)
{
	// TODO
	/*if constexpr (hamon::same_as<decltype(__out_it), hamon::back_insert_iterator<__format::__output_buffer<_OutCharT>>>)
	{
		__out_it.__get_container()->__copy(__str);
		return __out_it;
	}
	else*/ if constexpr (hamon::same_as<decltype(__out_it), typename __format::__retarget_buffer<_OutCharT>::__iterator>)
	{
		__out_it.__buffer_->__copy(__str);
		return __out_it;
	}
	else
	{
		return hamon::ranges::copy(__str, hamon::move(__out_it)).out;
	}
}

template <hamon::contiguous_iterator _Iterator,
	__format::__fmt_char_type _CharT    = typename hamon::iterator_traits<_Iterator>::value_type,
	__format::__fmt_char_type _OutCharT = _CharT>
auto
__copy(_Iterator __first, _Iterator __last, hamon::output_iterator<const _OutCharT&> auto __out_it) -> decltype(__out_it)
{
	return __formatter::__copy(hamon::basic_string_view{__first, __last}, hamon::move(__out_it));
}

template <hamon::contiguous_iterator _Iterator,
	__format::__fmt_char_type _CharT    = typename hamon::iterator_traits<_Iterator>::value_type,
	__format::__fmt_char_type _OutCharT = _CharT>
auto
__copy(_Iterator __first, size_t __n, hamon::output_iterator<const _OutCharT&> auto __out_it) -> decltype(__out_it)
{
	return __formatter::__copy(hamon::basic_string_view{hamon::to_address(__first), __n}, hamon::move(__out_it));
}

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___COPY_HPP
