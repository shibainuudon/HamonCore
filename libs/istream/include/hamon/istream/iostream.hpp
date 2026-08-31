/**
 *	@file	iostream.hpp
 *
 *	@brief	iostream の定義
 */

#ifndef HAMON_ISTREAM_IOSTREAM_HPP
#define HAMON_ISTREAM_IOSTREAM_HPP

#include <hamon/istream/basic_iostream.hpp>

namespace hamon
{

// 31.7.1 Header <istream> synopsis[istream.syn]

using iostream = hamon::basic_iostream<char>;

}	// namespace hamon

#endif // HAMON_ISTREAM_IOSTREAM_HPP
