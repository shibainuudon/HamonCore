/**
 *	@file	__format_context_create.hpp
 *
 *	@brief	__format_context_create の定義
 */

#ifndef HAMON_FORMAT_OTHER___FORMAT_CONTEXT_CREATE_HPP
#define HAMON_FORMAT_OTHER___FORMAT_CONTEXT_CREATE_HPP

#include <hamon/format/basic_format_context.hpp>
#include <hamon/format/basic_format_args.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{

/**
 * Helper to create a basic_format_context.
 *
 * This is needed since the constructor is private.
 */
template <class _OutIt, class _CharT>
hamon::basic_format_context<_OutIt, _CharT>
__format_context_create(
	_OutIt __out_it,
	hamon::basic_format_args<hamon::basic_format_context<_OutIt, _CharT>> __args,
	std::locale const& __loc)
{
	return hamon::basic_format_context(hamon::move(__out_it), __args, __loc);
}

template <class _OutIt, class _CharT>
hamon::basic_format_context<_OutIt, _CharT>
__format_context_create(
	_OutIt __out_it,
	hamon::basic_format_args<hamon::basic_format_context<_OutIt, _CharT>> __args)
{
	return hamon::basic_format_context(hamon::move(__out_it), __args);
}

}	// namespace hamon

#endif // HAMON_FORMAT_OTHER___FORMAT_CONTEXT_CREATE_HPP
