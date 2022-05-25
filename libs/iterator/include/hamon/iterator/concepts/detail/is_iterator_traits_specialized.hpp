/**
 *	@file	is_iterator_traits_specialized.hpp
 *
 *	@brief	is_iterator_traits_specialized の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_DETAIL_IS_ITERATOR_TRAITS_SPECIALIZED_HPP
#define HAMON_ITERATOR_CONCEPTS_DETAIL_IS_ITERATOR_TRAITS_SPECIALIZED_HPP

namespace hamon
{

namespace detail
{

template <typename Iter>
struct is_iterator_traits_specialized
{
	static const bool value = false;
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_DETAIL_IS_ITERATOR_TRAITS_SPECIALIZED_HPP
