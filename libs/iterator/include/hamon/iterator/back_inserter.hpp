/**
 *	@file	back_inserter.hpp
 *
 *	@brief	back_inserter の定義
 */

#ifndef HAMON_ITERATOR_BACK_INSERTER_HPP
#define HAMON_ITERATOR_BACK_INSERTER_HPP

#include <hamon/iterator/back_insert_iterator.hpp>
#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_ITERATOR)

#include <iterator>

namespace hamon
{

using std::back_inserter;

}	// namespace hamon

#else

#include <hamon/config.hpp>

namespace hamon
{

// 25.5.2.2.2 back_inserter[back.inserter]

template <typename Container>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
hamon::back_insert_iterator<Container>
back_inserter(Container& x) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [back.inserter]/1
	return hamon::back_insert_iterator<Container>(x);
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_BACK_INSERTER_HPP
