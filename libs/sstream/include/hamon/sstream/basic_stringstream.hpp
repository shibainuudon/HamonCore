/**
 *	@file	basic_stringstream.hpp
 *
 *	@brief	basic_stringstream の定義
 */

#ifndef HAMON_SSTREAM_BASIC_STRINGSTREAM_HPP
#define HAMON_SSTREAM_BASIC_STRINGSTREAM_HPP

#include <sstream>

namespace hamon
{

using std::basic_stringstream;

#if 0	// TODO
// [stringstream], class template basic_stringstream
template <typename charT, typename traits = char_traits<charT>, typename Allocator = allocator<charT>>
class basic_stringstream;

template <typename charT, typename traits, typename Allocator>
void swap(
	basic_stringstream<charT, traits, Allocator>& x,
	basic_stringstream<charT, traits, Allocator>& y);
#endif

}	// namespace hamon

#endif // HAMON_SSTREAM_BASIC_STRINGSTREAM_HPP
