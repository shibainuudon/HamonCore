/**
 *	@file	unexpect.hpp
 *
 *	@brief	unexpect の定義
 */

#ifndef HAMON_EXPECTED_UNEXPECT_HPP
#define HAMON_EXPECTED_UNEXPECT_HPP

#include <hamon/expected/config.hpp>

#if defined(HAMON_USE_STD_EXPECTED)

#include <expected>

namespace hamon
{

using std::unexpect_t;
using std::unexpect;

}	// namespace hamon

#else

#include <hamon/config.hpp>

namespace hamon
{

// in-place construction of unexpected values
struct unexpect_t
{
	explicit unexpect_t() = default;
};

HAMON_INLINE_VAR HAMON_CONSTEXPR unexpect_t unexpect {};

}	// namespace hamon

#endif

#endif // HAMON_EXPECTED_UNEXPECT_HPP
