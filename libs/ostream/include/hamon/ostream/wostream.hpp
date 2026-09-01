/**
 *	@file	wostream.hpp
 *
 *	@brief	wostream の定義
 */

#ifndef HAMON_OSTREAM_WOSTREAM_HPP
#define HAMON_OSTREAM_WOSTREAM_HPP

#include <hamon/ostream/basic_ostream.hpp>

namespace hamon
{

// 31.7.2 Header <ostream> synopsis[ostream.syn]

using wostream = hamon::basic_ostream<wchar_t>;

}	// namespace hamon

#endif // HAMON_OSTREAM_WOSTREAM_HPP
