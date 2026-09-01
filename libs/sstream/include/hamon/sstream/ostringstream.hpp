/**
 *	@file	ostringstream.hpp
 *
 *	@brief	ostringstream の定義
 */

#ifndef HAMON_SSTREAM_OSTRINGSTREAM_HPP
#define HAMON_SSTREAM_OSTRINGSTREAM_HPP

#include <hamon/sstream/basic_ostringstream.hpp>

namespace hamon
{

// [ostringstream], class template basic_ostringstream

using ostringstream = hamon::basic_ostringstream<char>;

}	// namespace hamon

#endif // HAMON_SSTREAM_OSTRINGSTREAM_HPP
