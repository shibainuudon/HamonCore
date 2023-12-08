/**
 *	@file	make_move_sentinel.hpp
 *
 *	@brief	make_move_sentinel の定義
 */

#ifndef HAMON_ITERATOR_MAKE_MOVE_SENTINEL_HPP
#define HAMON_ITERATOR_MAKE_MOVE_SENTINEL_HPP

#include <hamon/iterator/move_sentinel.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename S>
HAMON_CXX14_CONSTEXPR hamon::move_sentinel<S>
make_move_sentinel(S sent)
HAMON_NOEXCEPT_IF_EXPR(hamon::move_sentinel<S>(hamon::move(sent)))
{
    return hamon::move_sentinel<S>(hamon::move(sent));
}

}	// namespace hamon

#endif // HAMON_ITERATOR_MAKE_MOVE_SENTINEL_HPP
