/**
 *	@file	__compile_time_basic_format_context.hpp
 *
 *	@brief	__compile_time_basic_format_context の定義
 */

#ifndef HAMON_FORMAT___FORMAT___COMPILE_TIME_BASIC_FORMAT_CONTEXT_HPP
#define HAMON_FORMAT___FORMAT___COMPILE_TIME_BASIC_FORMAT_CONTEXT_HPP

#include <hamon/format/__format/__compile_time_handle.hpp>
#include <hamon/format/__format/__arg_t.hpp>
#include <hamon/format/format_error.hpp>

namespace hamon
{

namespace __format
{

// Dummy format_context only providing the parts used during constant
// validation of the basic_format_string.
template <class _CharT>
struct __compile_time_basic_format_context
{
public:
	using char_type = _CharT;

	constexpr explicit
	__compile_time_basic_format_context(
		const __arg_t* __args, const __compile_time_handle<_CharT>* __handles, size_t __size)
		: __args_(__args), __handles_(__handles), __size_(__size) {}

	// During the compile-time validation nothing needs to be written.
	// Therefore all operations of this iterator are a NOP.
	struct iterator
	{
		constexpr iterator& operator=(_CharT) { return *this; }
		constexpr iterator& operator*() { return *this; }
		constexpr iterator operator++(int) { return *this; }
	};

	constexpr __arg_t arg(size_t __id) const
	{
		if (__id >= __size_)
		{
			hamon::detail::throw_format_error("The argument index value is too large for the number of arguments supplied");
		}

		return __args_[__id];
	}

	constexpr const __compile_time_handle<_CharT>& __handle(size_t __id) const
	{
		if (__id >= __size_)
		{
			hamon::detail::throw_format_error("The argument index value is too large for the number of arguments supplied");
		}

		return __handles_[__id];
	}

	constexpr iterator out() { return {}; }
	constexpr void advance_to(iterator) {}

private:
	const __arg_t* __args_;
	const __compile_time_handle<_CharT>* __handles_;
	size_t __size_;
};

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___COMPILE_TIME_BASIC_FORMAT_CONTEXT_HPP
