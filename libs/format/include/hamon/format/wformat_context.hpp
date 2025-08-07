/**
 *	@file	wformat_context.hpp
 *
 *	@brief	wformat_context の定義
 */

#ifndef HAMON_FORMAT_WFORMAT_CONTEXT_HPP
#define HAMON_FORMAT_WFORMAT_CONTEXT_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::wformat_context;

}	// namespace hamon

#else

#include <hamon/format/basic_format_context.hpp>
#include <hamon/format/__format/__output_buffer.hpp>
#include <hamon/iterator/back_insert_iterator.hpp>

namespace hamon
{

// [format.context], class template basic_format_context

using wformat_context = hamon::basic_format_context<hamon::back_insert_iterator<__format::__output_buffer<wchar_t>>, wchar_t>;

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_WFORMAT_CONTEXT_HPP
