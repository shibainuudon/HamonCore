/**
 *	@file	make_move_iterator.hpp
 *
 *	@brief	make_move_iterator の定義
 */

#ifndef HAMON_ITERATOR_MAKE_MOVE_ITERATOR_HPP
#define HAMON_ITERATOR_MAKE_MOVE_ITERATOR_HPP

#include <hamon/iterator/move_iterator.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

#include <iterator>

namespace hamon
{

using std::make_move_iterator;

}	// namespace hamon

#else

#include <hamon/utility/move.hpp>

namespace hamon
{

template <typename Iterator>
inline HAMON_CXX14_CONSTEXPR hamon::move_iterator<Iterator>
make_move_iterator(Iterator it)
HAMON_NOEXCEPT_IF_EXPR(hamon::move_iterator<Iterator>(hamon::move(it)))
{
    return hamon::move_iterator<Iterator>(hamon::move(it));
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_MAKE_MOVE_ITERATOR_HPP
