/**
 *	@file	basic_format_context_fwd.hpp
 *
 *	@brief	basic_format_context の前方宣言
 */

#ifndef HAMON_FORMAT_BASIC_FORMAT_CONTEXT_FWD_HPP
#define HAMON_FORMAT_BASIC_FORMAT_CONTEXT_FWD_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::basic_format_context;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/output_iterator.hpp>

namespace hamon
{

// [format.context], class template basic_format_context
template <typename Out, typename charT>
	requires hamon::output_iterator<Out, charT const&>
class basic_format_context;

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_BASIC_FORMAT_CONTEXT_FWD_HPP
