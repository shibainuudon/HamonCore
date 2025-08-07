/**
 *	@file	format_context.hpp
 *
 *	@brief	format_context の定義
 */

#ifndef HAMON_FORMAT_FORMAT_CONTEXT_HPP
#define HAMON_FORMAT_FORMAT_CONTEXT_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::format_context;

}	// namespace hamon

#else

#include <hamon/format/basic_format_context.hpp>
#include <hamon/format/__format/__output_buffer.hpp>
#include <hamon/iterator/back_insert_iterator.hpp>

namespace hamon
{

// [format.context], class template basic_format_context

using format_context = hamon::basic_format_context<hamon::back_insert_iterator<__format::__output_buffer<char>>, char>;

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_FORMAT_CONTEXT_HPP
