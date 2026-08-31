/**
 *	@file	wiostream.hpp
 *
 *	@brief	wiostream の定義
 */

#ifndef HAMON_ISTREAM_WIOSTREAM_HPP
#define HAMON_ISTREAM_WIOSTREAM_HPP

#include <hamon/istream/basic_iostream.hpp>

namespace hamon
{

// 31.7.1 Header <istream> synopsis[istream.syn]

using wiostream = hamon::basic_iostream<wchar_t>;

}	// namespace hamon

#endif // HAMON_ISTREAM_WIOSTREAM_HPP
