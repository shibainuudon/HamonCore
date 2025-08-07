/**
 *	@file	__create_type_mask.hpp
 *
 *	@brief	__create_type_mask の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___CREATE_TYPE_MASK_HPP
#define HAMON_FORMAT___FORMAT_SPEC___CREATE_TYPE_MASK_HPP

#include <hamon/format/format_error.hpp>

namespace hamon
{

namespace __format_spec
{

inline constexpr uint32_t __create_type_mask(__type __t)
{
	uint32_t __shift = static_cast<uint32_t>(__t);
	if (__shift == 0)
	{
		return 1;
	}

	if (__shift > 31)
	{
		hamon::detail::throw_format_error("The type does not fit in the mask");
	}

	return 1 << __shift;
}

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___CREATE_TYPE_MASK_HPP
