/**
 *	@file	__padding_size.hpp
 *
 *	@brief	__padding_size の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___PADDING_SIZE_HPP
#define HAMON_FORMAT___FORMATTER___PADDING_SIZE_HPP

#include <hamon/format/__format_spec/__alignment.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace __formatter
{

struct __padding_size_result
{
	size_t __before_;
	size_t __after_;
};

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4715)	// 値を返さないコントロール パスがあります。

constexpr __padding_size_result
__padding_size(size_t __size, size_t __width, __format_spec::__alignment __align)
{
//	_LIBCPP_ASSERT_INTERNAL(__width > __size, "don't call this function when no padding is required");
//	_LIBCPP_ASSERT_INTERNAL(__align != __format_spec::__alignment::__zero_padding, "the caller should have handled the zero-padding");

	size_t __fill = __width - __size;
	switch (__align)
	{
	case __format_spec::__alignment::__zero_padding:
		HAMON_UNREACHABLE();

	case __format_spec::__alignment::__left:
		return {0, __fill};

	case __format_spec::__alignment::__center:
		{
			// The extra padding is divided per [format.string.std]/3
			// __before = floor(__fill, 2);
			// __after = ceil(__fill, 2);
			size_t __before = __fill / 2;
			size_t __after  = __fill - __before;
			return {__before, __after};
		}
	case __format_spec::__alignment::__default:
	case __format_spec::__alignment::__right:
		return {__fill, 0};
	}
	HAMON_UNREACHABLE();
}

HAMON_WARNING_POP()

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___PADDING_SIZE_HPP
