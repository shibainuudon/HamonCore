/**
 *	@file	iterator_category.hpp
 *
 *	@brief	iterator_category の定義
 */

#ifndef HAMON_ITERATOR_ITERATOR_CATEGORY_HPP
#define HAMON_ITERATOR_ITERATOR_CATEGORY_HPP

#include <hamon/iterator/iterator_traits.hpp>

namespace hamon
{

template <typename Iterator>
using iterator_category =
	typename hamon::iterator_traits<Iterator>::iterator_category;

}	// namespace hamon

#endif // HAMON_ITERATOR_ITERATOR_CATEGORY_HPP
