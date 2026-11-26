/**
 *	@file	wistringstream_fwd.hpp
 *
 *	@brief	wistringstream の前方宣言
 */

#ifndef HAMON_SSTREAM_WISTRINGSTREAM_FWD_HPP
#define HAMON_SSTREAM_WISTRINGSTREAM_FWD_HPP

#include <hamon/sstream/basic_istringstream_fwd.hpp>

namespace hamon
{

// [istringstream], class template basic_istringstream

using wistringstream = hamon::basic_istringstream<wchar_t>;

}	// namespace hamon

#endif // HAMON_SSTREAM_WISTRINGSTREAM_FWD_HPP
