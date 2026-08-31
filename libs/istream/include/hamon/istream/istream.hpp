/**
 *	@file	istream.hpp
 *
 *	@brief	istream の定義
 */

#ifndef HAMON_ISTREAM_ISTREAM_HPP
#define HAMON_ISTREAM_ISTREAM_HPP

#include <hamon/istream/basic_istream.hpp>

namespace hamon
{

// 31.7.1 Header <istream> synopsis[istream.syn]

using istream = hamon::basic_istream<char>;

}	// namespace hamon

#endif // HAMON_ISTREAM_ISTREAM_HPP
