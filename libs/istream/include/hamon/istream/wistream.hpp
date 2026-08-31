/**
 *	@file	wistream.hpp
 *
 *	@brief	wistream の定義
 */

#ifndef HAMON_ISTREAM_WISTREAM_HPP
#define HAMON_ISTREAM_WISTREAM_HPP

#include <hamon/istream/basic_istream.hpp>

namespace hamon
{

// 31.7.1 Header <istream> synopsis[istream.syn]

using wistream = hamon::basic_istream<wchar_t>;

}	// namespace hamon

#endif // HAMON_ISTREAM_WISTREAM_HPP
