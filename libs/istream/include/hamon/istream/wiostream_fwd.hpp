/**
 *	@file	wiostream_fwd.hpp
 *
 *	@brief	wiostream の前方宣言
 */

#ifndef HAMON_ISTREAM_WIOSTREAM_FWD_HPP
#define HAMON_ISTREAM_WIOSTREAM_FWD_HPP

#include <hamon/istream/basic_iostream_fwd.hpp>

namespace hamon
{

// 31.7.1 Header <istream> synopsis[istream.syn]

using wiostream = hamon::basic_iostream<wchar_t>;

}	// namespace hamon

#endif // HAMON_ISTREAM_WIOSTREAM_FWD_HPP
