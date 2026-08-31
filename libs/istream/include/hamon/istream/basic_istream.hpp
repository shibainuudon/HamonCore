/**
 *	@file	basic_istream.hpp
 *
 *	@brief	basic_istream の定義
 */

#ifndef HAMON_ISTREAM_BASIC_ISTREAM_HPP
#define HAMON_ISTREAM_BASIC_ISTREAM_HPP

#include <istream>

namespace hamon
{

using std::basic_istream;

#if 0	// TODO
// [istream], class template basic_istream
template <typename charT, typename traits = char_traits<charT>>
class basic_istream;

// [istream.rvalue], rvalue stream extraction
template <typename Istream, typename T>
Istream&& operator>>(Istream&& is, T&& x);
#endif

}	// namespace hamon

#endif // HAMON_ISTREAM_BASIC_ISTREAM_HPP
