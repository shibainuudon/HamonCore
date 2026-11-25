/**
 *	@file	istream_fwd.hpp
 *
 *	@brief	istream の前方宣言
 */

#ifndef HAMON_ISTREAM_ISTREAM_FWD_HPP
#define HAMON_ISTREAM_ISTREAM_FWD_HPP

#include <hamon/istream/basic_istream_fwd.hpp>

namespace hamon
{

// 31.7.1 Header <istream> synopsis[istream.syn]

using istream = hamon::basic_istream<char>;

}	// namespace hamon

#endif // HAMON_ISTREAM_ISTREAM_FWD_HPP
