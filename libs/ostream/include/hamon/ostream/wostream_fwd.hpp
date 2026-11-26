/**
 *	@file	wostream_fwd.hpp
 *
 *	@brief	wostream の前方宣言
 */

#ifndef HAMON_OSTREAM_WOSTREAM_FWD_HPP
#define HAMON_OSTREAM_WOSTREAM_FWD_HPP

#include <hamon/ostream/basic_ostream_fwd.hpp>

namespace hamon
{

// 31.7.2 Header <ostream> synopsis[ostream.syn]

using wostream = hamon::basic_ostream<wchar_t>;

}	// namespace hamon

#endif // HAMON_OSTREAM_WOSTREAM_FWD_HPP
