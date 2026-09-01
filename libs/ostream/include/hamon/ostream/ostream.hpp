/**
 *	@file	ostream.hpp
 *
 *	@brief	ostream の定義
 */

#ifndef HAMON_OSTREAM_OSTREAM_HPP
#define HAMON_OSTREAM_OSTREAM_HPP

#include <hamon/ostream/basic_ostream.hpp>

namespace hamon
{

// 31.7.2 Header <ostream> synopsis[ostream.syn]

using ostream = hamon::basic_ostream<char>;

}	// namespace hamon

#endif // HAMON_OSTREAM_OSTREAM_HPP
