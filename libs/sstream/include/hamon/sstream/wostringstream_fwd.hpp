/**
 *	@file	wostringstream_fwd.hpp
 *
 *	@brief	wostringstream の前方宣言
 */

#ifndef HAMON_SSTREAM_WOSTRINGSTREAM_FWD_HPP
#define HAMON_SSTREAM_WOSTRINGSTREAM_FWD_HPP

#include <hamon/sstream/basic_ostringstream_fwd.hpp>

namespace hamon
{

// [ostringstream], class template basic_ostringstream

using wostringstream = hamon::basic_ostringstream<wchar_t>;

}	// namespace hamon

#endif // HAMON_SSTREAM_WOSTRINGSTREAM_FWD_HPP
