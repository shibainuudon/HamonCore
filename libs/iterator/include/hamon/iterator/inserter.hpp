/**
 *	@file	inserter.hpp
 *
 *	@brief	inserter の定義
 */

#ifndef HAMON_ITERATOR_INSERTER_HPP
#define HAMON_ITERATOR_INSERTER_HPP

#include <hamon/iterator/insert_iterator.hpp>

#if defined(HAMON_USE_STD_INSERT_ITERATOR)

#include <iterator>

namespace hamon
{

using std::inserter;

}	// namespace hamon

#else

#include <hamon/ranges/iterator_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 25.5.2.4.2 inserter[inserter]

template <typename Container>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
hamon::insert_iterator<Container>
inserter(Container& x, hamon::ranges::iterator_t<Container> i)
	HAMON_NOEXCEPT	// noexcept as an extension
{
	// [inserter]/1
	return hamon::insert_iterator<Container>(x, i);
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_INSERTER_HPP
