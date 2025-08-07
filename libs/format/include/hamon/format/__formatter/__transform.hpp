/**
 *	@file	__transform.hpp
 *
 *	@brief	__transform の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___TRANSFORM_HPP
#define HAMON_FORMAT___FORMATTER___TRANSFORM_HPP

#include <hamon/format/__format/__fmt_char_type.hpp>
#include <hamon/format/__format/__output_buffer.hpp>
#include <hamon/format/__format/__retarget_buffer.hpp>
#include <hamon/algorithm/ranges/transform.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/iterator/back_insert_iterator.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{

namespace __formatter
{

/// Transform wrapper.
///
/// This uses a "mass output function" of __format::__output_buffer when possible.
template <hamon::contiguous_iterator _Iterator,
	__format::__fmt_char_type _CharT    = typename hamon::iterator_traits<_Iterator>::value_type,
	__format::__fmt_char_type _OutCharT = _CharT,
	class _UnaryOperation>
auto
__transform(_Iterator __first,
			_Iterator __last,
			hamon::output_iterator<const _OutCharT&> auto __out_it,
			_UnaryOperation __operation) -> decltype(__out_it)
{
	// TODO
	/*if constexpr (hamon::same_as<decltype(__out_it), hamon::back_insert_iterator<__format::__output_buffer<_OutCharT>>>)
	{
		__out_it.__get_container()->__transform(__first, __last, hamon::move(__operation));
		return __out_it;
	}
	else*/ if constexpr (hamon::same_as<decltype(__out_it), typename __format::__retarget_buffer<_OutCharT>::__iterator>)
	{
		__out_it.__buffer_->__transform(__first, __last, hamon::move(__operation));
		return __out_it;
	}
	else
	{
		return hamon::ranges::transform(__first, __last, hamon::move(__out_it), __operation).out;
	}
}

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___TRANSFORM_HPP
