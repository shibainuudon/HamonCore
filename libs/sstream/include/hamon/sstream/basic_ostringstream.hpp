/**
 *	@file	basic_ostringstream.hpp
 *
 *	@brief	basic_ostringstream の定義
 */

#ifndef HAMON_SSTREAM_BASIC_OSTRINGSTREAM_HPP
#define HAMON_SSTREAM_BASIC_OSTRINGSTREAM_HPP

#include <sstream>

namespace hamon
{

using std::basic_ostringstream;

#if 0	// TODO
// [ostringstream], class template basic_ostringstream
template <typename charT, typename traits = char_traits<charT>, typename Allocator = allocator<charT>>
class basic_ostringstream;

template <typename charT, typename traits, typename Allocator>
void swap(
	basic_ostringstream<charT, traits, Allocator>& x,
	basic_ostringstream<charT, traits, Allocator>& y);
#endif

}	// namespace hamon

#endif // HAMON_SSTREAM_BASIC_OSTRINGSTREAM_HPP
