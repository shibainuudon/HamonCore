/**
 *	@file	wistringstream.hpp
 *
 *	@brief	wistringstream の定義
 */

#ifndef HAMON_SSTREAM_WISTRINGSTREAM_HPP
#define HAMON_SSTREAM_WISTRINGSTREAM_HPP

#include <hamon/sstream/basic_istringstream.hpp>

namespace hamon
{

// [istringstream], class template basic_istringstream

using wistringstream = hamon::basic_istringstream<wchar_t>;

}	// namespace hamon

#endif // HAMON_SSTREAM_WISTRINGSTREAM_HPP
