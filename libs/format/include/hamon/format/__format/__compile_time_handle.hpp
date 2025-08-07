/**
 *	@file	__compile_time_handle.hpp
 *
 *	@brief	__compile_time_handle の定義
 */

#ifndef HAMON_FORMAT___FORMAT___COMPILE_TIME_HANDLE_HPP
#define HAMON_FORMAT___FORMAT___COMPILE_TIME_HANDLE_HPP

#include <hamon/format/basic_format_parse_context.hpp>
#include <hamon/format/formatter.hpp>
#include <hamon/format/format_error.hpp>

namespace hamon
{

namespace __format
{

/// Helper class parse and handle argument.
///
/// When parsing a handle which is not enabled the code is ill-formed.
/// This helper uses the parser of the appropriate formatter for the stored type.
template <class _CharT>
class __compile_time_handle
{
public:
	template <class _ParseContext>
	constexpr void __parse(_ParseContext& __ctx) const
	{
		__parse_(__ctx);
	}

	template <class _Tp>
	constexpr void __enable()
	{
		__parse_ = [](hamon::basic_format_parse_context<_CharT>& __ctx) {
			hamon::formatter<_Tp, _CharT> __f;
			__ctx.advance_to(__f.parse(__ctx));
		};
	}

	// Before calling __parse the proper handler needs to be set with __enable.
	// The default handler isn't a core constant expression.
	constexpr __compile_time_handle()
		: __parse_(
			[](hamon::basic_format_parse_context<_CharT>&) {
				hamon::detail::throw_format_error("Not a handle");
			})
	{}

private:
	void (*__parse_)(hamon::basic_format_parse_context<_CharT>&);
};

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___COMPILE_TIME_HANDLE_HPP
