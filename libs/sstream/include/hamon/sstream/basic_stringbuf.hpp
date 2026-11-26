/**
 *	@file	basic_stringbuf.hpp
 *
 *	@brief	basic_stringbuf の定義
 */

#ifndef HAMON_SSTREAM_BASIC_STRINGBUF_HPP
#define HAMON_SSTREAM_BASIC_STRINGBUF_HPP

#include <hamon/sstream/basic_stringbuf_fwd.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/string/char_traits.hpp>

namespace hamon
{

#if 0	// TODO
// [stringbuf], class template basic_stringbuf
template <typename charT, typename traits = char_traits<charT>, typename Allocator = allocator<charT>>
class basic_stringbuf;

template <typename charT, typename traits, typename Allocator>
void swap(
	basic_stringbuf<charT, traits, Allocator>& x,
	basic_stringbuf<charT, traits, Allocator>& y)
	noexcept(noexcept(x.swap(y)));
#endif

}	// namespace hamon

#endif // HAMON_SSTREAM_BASIC_STRINGBUF_HPP
