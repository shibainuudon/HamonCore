/**
 *	@file	basic_stringbuf_fwd.hpp
 *
 *	@brief	basic_stringbuf の前方宣言
 */

#ifndef HAMON_SSTREAM_BASIC_STRINGBUF_FWD_HPP
#define HAMON_SSTREAM_BASIC_STRINGBUF_FWD_HPP

#include <hamon/memory/allocator_fwd.hpp>
#include <hamon/string/char_traits_fwd.hpp>
#include <sstream>

namespace hamon
{

using std::basic_stringbuf;

#if 0	// TODO
// [stringbuf], class template basic_stringbuf
template <typename charT, typename traits = char_traits<charT>, typename Allocator = allocator<charT>>
class basic_stringbuf;
#endif

}	// namespace hamon

#endif // HAMON_SSTREAM_BASIC_STRINGBUF_FWD_HPP
