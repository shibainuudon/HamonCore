/**
 *	@file	__visit_format_arg.hpp
 *
 *	@brief	__visit_format_arg の定義
 */

#ifndef HAMON_FORMAT_OTHER___VISIT_FORMAT_ARG_HPP
#define HAMON_FORMAT_OTHER___VISIT_FORMAT_ARG_HPP

#include <hamon/format/__format/__arg_t.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/functional/invoke_r.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename Context>
class basic_format_arg;


HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4715)	// 値を返さないコントロール パスがあります。

// This function is not user observable, so it can directly use the non-standard
// types of the "variant". See __arg_t for more details.
template <class _Visitor, class _Context>
decltype(auto) __visit_format_arg(_Visitor&& __vis, hamon::basic_format_arg<_Context> __arg)
{
	switch (__arg.__type_)
	{
	case __format::__arg_t::__none:
		return hamon::invoke(hamon::forward<_Visitor>(__vis), __arg.__value_.__monostate_);
	case __format::__arg_t::__boolean:
		return hamon::invoke(hamon::forward<_Visitor>(__vis), __arg.__value_.__boolean_);
	case __format::__arg_t::__char_type:
		return hamon::invoke(hamon::forward<_Visitor>(__vis), __arg.__value_.__char_type_);
	case __format::__arg_t::__int:
		return hamon::invoke(hamon::forward<_Visitor>(__vis), __arg.__value_.__int_);
	case __format::__arg_t::__long_long:
		return hamon::invoke(hamon::forward<_Visitor>(__vis), __arg.__value_.__long_long_);
	case __format::__arg_t::__unsigned:
		return hamon::invoke(hamon::forward<_Visitor>(__vis), __arg.__value_.__unsigned_);
	case __format::__arg_t::__unsigned_long_long:
		return hamon::invoke(hamon::forward<_Visitor>(__vis), __arg.__value_.__unsigned_long_long_);
	case __format::__arg_t::__float:
		return hamon::invoke(hamon::forward<_Visitor>(__vis), __arg.__value_.__float_);
	case __format::__arg_t::__double:
		return hamon::invoke(hamon::forward<_Visitor>(__vis), __arg.__value_.__double_);
	case __format::__arg_t::__long_double:
		return hamon::invoke(hamon::forward<_Visitor>(__vis), __arg.__value_.__long_double_);
	case __format::__arg_t::__const_char_type_ptr:
		return hamon::invoke(hamon::forward<_Visitor>(__vis), __arg.__value_.__const_char_type_ptr_);
	case __format::__arg_t::__string_view:
		return hamon::invoke(hamon::forward<_Visitor>(__vis), __arg.__value_.__string_view_);
	case __format::__arg_t::__ptr:
		return hamon::invoke(hamon::forward<_Visitor>(__vis), __arg.__value_.__ptr_);
	case __format::__arg_t::__handle:
		return hamon::invoke(hamon::forward<_Visitor>(__vis), typename hamon::basic_format_arg<_Context>::handle {__arg.__value_.__handle_});
	}

	HAMON_UNREACHABLE();
}

template <class _Rp, class _Visitor, class _Context>
_Rp __visit_format_arg(_Visitor&& __vis, hamon::basic_format_arg<_Context> __arg)
{
	switch (__arg.__type_)
	{
	case __format::__arg_t::__none:
		return hamon::invoke_r<_Rp>(hamon::forward<_Visitor>(__vis), __arg.__value_.__monostate_);
	case __format::__arg_t::__boolean:
		return hamon::invoke_r<_Rp>(hamon::forward<_Visitor>(__vis), __arg.__value_.__boolean_);
	case __format::__arg_t::__char_type:
		return hamon::invoke_r<_Rp>(hamon::forward<_Visitor>(__vis), __arg.__value_.__char_type_);
	case __format::__arg_t::__int:
		return hamon::invoke_r<_Rp>(hamon::forward<_Visitor>(__vis), __arg.__value_.__int_);
	case __format::__arg_t::__long_long:
		return hamon::invoke_r<_Rp>(hamon::forward<_Visitor>(__vis), __arg.__value_.__long_long_);
	case __format::__arg_t::__unsigned:
		return hamon::invoke_r<_Rp>(hamon::forward<_Visitor>(__vis), __arg.__value_.__unsigned_);
	case __format::__arg_t::__unsigned_long_long:
		return hamon::invoke_r<_Rp>(hamon::forward<_Visitor>(__vis), __arg.__value_.__unsigned_long_long_);
	case __format::__arg_t::__float:
		return hamon::invoke_r<_Rp>(hamon::forward<_Visitor>(__vis), __arg.__value_.__float_);
	case __format::__arg_t::__double:
		return hamon::invoke_r<_Rp>(hamon::forward<_Visitor>(__vis), __arg.__value_.__double_);
	case __format::__arg_t::__long_double:
		return hamon::invoke_r<_Rp>(hamon::forward<_Visitor>(__vis), __arg.__value_.__long_double_);
	case __format::__arg_t::__const_char_type_ptr:
		return hamon::invoke_r<_Rp>(hamon::forward<_Visitor>(__vis), __arg.__value_.__const_char_type_ptr_);
	case __format::__arg_t::__string_view:
		return hamon::invoke_r<_Rp>(hamon::forward<_Visitor>(__vis), __arg.__value_.__string_view_);
	case __format::__arg_t::__ptr:
		return hamon::invoke_r<_Rp>(hamon::forward<_Visitor>(__vis), __arg.__value_.__ptr_);
	case __format::__arg_t::__handle:
		return hamon::invoke_r<_Rp>(hamon::forward<_Visitor>(__vis), typename hamon::basic_format_arg<_Context>::handle{ __arg.__value_.__handle_ });
	}

	HAMON_UNREACHABLE();
}

HAMON_WARNING_POP()

}	// namespace hamon

#include <hamon/format/basic_format_arg.hpp>

#endif // HAMON_FORMAT_OTHER___VISIT_FORMAT_ARG_HPP
