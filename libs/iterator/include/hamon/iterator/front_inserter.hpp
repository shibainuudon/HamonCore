/**
 *	@file	front_inserter.hpp
 *
 *	@brief	front_inserter の定義
 */

#ifndef HAMON_ITERATOR_FRONT_INSERTER_HPP
#define HAMON_ITERATOR_FRONT_INSERTER_HPP

#include <hamon/iterator/front_insert_iterator.hpp>
#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_ITERATOR)

#include <iterator>

namespace hamon
{

using std::front_inserter;

}	// namespace hamon

#else

#include <hamon/config.hpp>

namespace hamon
{

// 25.5.2.3.2 front_inserter[front.inserter]

template <typename Container>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
hamon::front_insert_iterator<Container>
front_inserter(Container& x) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [front.inserter]/1
	return hamon::front_insert_iterator<Container>(x);
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_FRONT_INSERTER_HPP
