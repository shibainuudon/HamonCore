/**
 *	@file	ostream_fwd.hpp
 *
 *	@brief	ostream の前方宣言
 */

#ifndef HAMON_OSTREAM_OSTREAM_FWD_HPP
#define HAMON_OSTREAM_OSTREAM_FWD_HPP

#include <hamon/ostream/basic_ostream_fwd.hpp>

namespace hamon
{

// 31.7.2 Header <ostream> synopsis[ostream.syn]

using ostream = hamon::basic_ostream<char>;

}	// namespace hamon

#endif // HAMON_OSTREAM_OSTREAM_FWD_HPP
