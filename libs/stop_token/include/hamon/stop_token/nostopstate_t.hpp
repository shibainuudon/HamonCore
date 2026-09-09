/**
 *	@file	nostopstate_t.hpp
 *
 *	@brief	nostopstate_t の定義
 */

#ifndef HAMON_STOP_TOKEN_NOSTOPSTATE_T_HPP
#define HAMON_STOP_TOKEN_NOSTOPSTATE_T_HPP

#include <hamon/config.hpp>

namespace hamon
{

// no-shared-stop-state indicator
struct nostopstate_t
{
	explicit nostopstate_t() = default;
};

HAMON_INLINE_VAR constexpr nostopstate_t nostopstate{};

}	// namespace hamon

#endif // HAMON_STOP_TOKEN_NOSTOPSTATE_T_HPP
