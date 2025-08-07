/**
 *	@file	__buffer_selector.hpp
 *
 *	@brief	__buffer_selector の定義
 */

#ifndef HAMON_FORMAT___FORMAT___BUFFER_SELECTOR_HPP
#define HAMON_FORMAT___FORMAT___BUFFER_SELECTOR_HPP

#include <hamon/format/__format/__fmt_char_type.hpp>
#include <hamon/format/__format/__back_insert_iterator_container.hpp>
#include <hamon/format/__format/__container_inserter_buffer.hpp>
#include <hamon/format/__format/__enable_direct_output.hpp>
#include <hamon/format/__format/__direct_iterator_buffer.hpp>
#include <hamon/format/__format/__iterator_buffer.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/type_traits/conditional.hpp>

namespace hamon
{

namespace __format
{

// Selects the type of the buffer used for the output iterator.
template <class _OutIt, __format::__fmt_char_type _CharT>
class __buffer_selector
{
	using _Container = typename __format::__back_insert_iterator_container<_OutIt>::type;

public:
	using type =
		hamon::conditional_t<!hamon::same_as<_Container, void>,
		__format::__container_inserter_buffer<_OutIt, _CharT>,
		hamon::conditional_t<__format::__enable_direct_output<_OutIt, _CharT>,
		__format::__direct_iterator_buffer<_OutIt, _CharT>,
		__format::__iterator_buffer<_OutIt, _CharT>>>;
};

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___BUFFER_SELECTOR_HPP
