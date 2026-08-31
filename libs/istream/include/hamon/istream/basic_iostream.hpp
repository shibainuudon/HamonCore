/**
 *	@file	basic_iostream.hpp
 *
 *	@brief	basic_iostream の定義
 */

#ifndef HAMON_ISTREAM_BASIC_IOSTREAM_HPP
#define HAMON_ISTREAM_BASIC_IOSTREAM_HPP

#include <istream>

namespace hamon
{

using std::basic_iostream;

#if 0	// TODO
// [iostreamclass], class template basic_iostream
template <typename charT, typename traits = char_traits<charT>>
class basic_iostream;
#endif

}	// namespace hamon

#endif // HAMON_ISTREAM_BASIC_IOSTREAM_HPP
