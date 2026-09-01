/**
 *	@file	istringstream.hpp
 *
 *	@brief	istringstream の定義
 */

#ifndef HAMON_SSTREAM_ISTRINGSTREAM_HPP
#define HAMON_SSTREAM_ISTRINGSTREAM_HPP

#include <hamon/sstream/basic_istringstream.hpp>

namespace hamon
{

// [istringstream], class template basic_istringstream

using istringstream = hamon::basic_istringstream<char>;

}	// namespace hamon

#endif // HAMON_SSTREAM_ISTRINGSTREAM_HPP
