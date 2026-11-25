/**
 *	@file	wistream_fwd.hpp
 *
 *	@brief	wistream の前方宣言
 */

#ifndef HAMON_ISTREAM_WISTREAM_FWD_HPP
#define HAMON_ISTREAM_WISTREAM_FWD_HPP

#include <hamon/istream/basic_istream_fwd.hpp>

namespace hamon
{

// 31.7.1 Header <istream> synopsis[istream.syn]

using wistream = hamon::basic_istream<wchar_t>;

}	// namespace hamon

#endif // HAMON_ISTREAM_WISTREAM_FWD_HPP
