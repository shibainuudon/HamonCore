/**
 *	@file	iostream_fwd.hpp
 *
 *	@brief	iostream の前方宣言
 */

#ifndef HAMON_ISTREAM_IOSTREAM_FWD_HPP
#define HAMON_ISTREAM_IOSTREAM_FWD_HPP

#include <hamon/istream/basic_iostream_fwd.hpp>

namespace hamon
{

// 31.7.1 Header <istream> synopsis[istream.syn]

using iostream = hamon::basic_iostream<char>;

}	// namespace hamon

#endif // HAMON_ISTREAM_IOSTREAM_FWD_HPP
