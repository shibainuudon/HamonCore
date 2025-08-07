/**
 *	@file	__enable_direct_output.hpp
 *
 *	@brief	__enable_direct_output の定義
 */

#ifndef HAMON_FORMAT___FORMAT___ENABLE_DIRECT_OUTPUT_HPP
#define HAMON_FORMAT___FORMAT___ENABLE_DIRECT_OUTPUT_HPP

#include <hamon/format/__format/__fmt_char_type.hpp>
#include <hamon/concepts/same_as.hpp>

namespace hamon
{

namespace __format
{

template <class _OutIt, class _CharT>
concept __enable_direct_output =
	__format::__fmt_char_type<_CharT> &&
	(hamon::same_as<_OutIt, _CharT*>
	// TODO(hardening): the following check might not apply to hardened iterators and might need to be wrapped in an
	// `#ifdef`.
/*	|| hamon::same_as<_OutIt, __wrap_iter<_CharT*>>*/);

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___ENABLE_DIRECT_OUTPUT_HPP
