/**
 *	@file	basic_istringstream.hpp
 *
 *	@brief	basic_istringstream の定義
 */

#ifndef HAMON_SSTREAM_BASIC_ISTRINGSTREAM_HPP
#define HAMON_SSTREAM_BASIC_ISTRINGSTREAM_HPP

#include <sstream>

namespace hamon
{

using std::basic_istringstream;

#if 0	// TODO
// [istringstream], class template basic_istringstream
template <typename charT, typename traits = char_traits<charT>, typename Allocator = allocator<charT>>
class basic_istringstream;

template <typename charT, typename traits, typename Allocator>
void swap(
	basic_istringstream<charT, traits, Allocator>& x,
	basic_istringstream<charT, traits, Allocator>& y);
#endif

}	// namespace hamon

#endif // HAMON_SSTREAM_BASIC_ISTRINGSTREAM_HPP
