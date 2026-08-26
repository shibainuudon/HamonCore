/**
 *	@file	unexpect.hpp
 *
 *	@brief	unexpect の定義
 */

#ifndef HAMON_EXPECTED_UNEXPECT_HPP
#define HAMON_EXPECTED_UNEXPECT_HPP

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

#endif // HAMON_EXPECTED_UNEXPECT_HPP
