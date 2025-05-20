/**
 *	@file	unexpected_fwd.hpp
 *
 *	@brief	unexpected の前方宣言
 */

#ifndef HAMON_EXPECTED_UNEXPECTED_FWD_HPP
#define HAMON_EXPECTED_UNEXPECTED_FWD_HPP

#include <hamon/expected/config.hpp>

#if defined(HAMON_USE_STD_EXPECTED)

#include <expected>

namespace hamon
{

using std::unexpected;

}	// namespace hamon

#else

namespace hamon
{

// [expected.unexpected], class template unexpected
template <typename E>
class unexpected;

}	// namespace hamon

#endif

#endif // HAMON_EXPECTED_UNEXPECTED_FWD_HPP
