/**
 *	@file	__create_packed_storage.hpp
 *
 *	@brief	__create_packed_storage の定義
 */

#ifndef HAMON_FORMAT___FORMAT___CREATE_PACKED_STORAGE_HPP
#define HAMON_FORMAT___FORMAT___CREATE_PACKED_STORAGE_HPP

#include <hamon/format/detail/__basic_format_arg_value.hpp>
#include <hamon/format/__format/__create_format_arg.hpp>
#include <hamon/format/__format/__packed_arg_t_bits.hpp>
#include <hamon/format/basic_format_arg.hpp>

namespace hamon
{

namespace __format
{

template <class _Context, class... _Args>
void
__create_packed_storage(uint64_t& __types, hamon::detail::__basic_format_arg_value<_Context>* __values, _Args&... __args) noexcept
{
	int __shift = 0;
	(
		[&] {
			  hamon::basic_format_arg<_Context> __arg = __format::__create_format_arg<_Context>(__args);
			  if (__shift != 0)
			  {
				  __types |= static_cast<uint64_t>(__arg.__type_) << __shift;
			  }
			  else
			  {
				  // Assigns the initial value.
				  __types = static_cast<uint64_t>(__arg.__type_);
			  }
			  __shift += __format::__packed_arg_t_bits;
			  *__values++ = __arg.__value_;
		}(),
		...);
}

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___CREATE_PACKED_STORAGE_HPP
