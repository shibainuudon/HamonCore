/**
 *	@file	wostringstream.hpp
 *
 *	@brief	wostringstream の定義
 */

#ifndef HAMON_SSTREAM_WOSTRINGSTREAM_HPP
#define HAMON_SSTREAM_WOSTRINGSTREAM_HPP

#include <hamon/sstream/basic_ostringstream.hpp>

namespace hamon
{

// [ostringstream], class template basic_ostringstream

using wostringstream = hamon::basic_ostringstream<wchar_t>;

}	// namespace hamon

#endif // HAMON_SSTREAM_WOSTRINGSTREAM_HPP
