/**
 *	@file	__iterator_buffer.hpp
 *
 *	@brief	__iterator_buffer の定義
 */

#ifndef HAMON_FORMAT___FORMAT___ITERATOR_BUFFER_HPP
#define HAMON_FORMAT___FORMAT___ITERATOR_BUFFER_HPP

#include <hamon/format/__format/__fmt_char_type.hpp>
#include <hamon/format/__format/__allocating_buffer.hpp>
#include <hamon/format/__format/__max_output_size.hpp>
#include <hamon/algorithm/ranges/copy.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{

namespace __format
{

// A buffer that writes to an iterator.
//
// Unlike the __container_inserter_buffer this class' performance does benefit
// from allocating and then inserting.
template <class _OutIt, __format::__fmt_char_type _CharT>
class __iterator_buffer : public __format::__allocating_buffer<_CharT> {
public:
	[[nodiscard]] explicit __iterator_buffer(_OutIt __out_it)
		: __allocating_buffer<_CharT> {}, __out_it_ {hamon::move(__out_it)} {}

	[[nodiscard]] explicit __iterator_buffer(_OutIt __out_it, __format::__max_output_size* __max_output_size)
		: __allocating_buffer<_CharT> {__max_output_size}, __out_it_ {hamon::move(__out_it)} {}

	[[nodiscard]] auto __out_it() &&
	{
		return hamon::ranges::copy(this->__view(), hamon::move(__out_it_)).out;
	}

private:
	_OutIt __out_it_;
};

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___ITERATOR_BUFFER_HPP
