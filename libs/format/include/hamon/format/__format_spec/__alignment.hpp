/**
 *	@file	__alignment.hpp
 *
 *	@brief	__alignment の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___ALIGNMENT_HPP
#define HAMON_FORMAT___FORMAT_SPEC___ALIGNMENT_HPP


namespace hamon
{

namespace __format_spec
{

enum class __alignment : uint8_t
{
	/// No alignment is set in the format string.
	__default,
	__left,
	__center,
	__right,
	__zero_padding
};

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___ALIGNMENT_HPP
