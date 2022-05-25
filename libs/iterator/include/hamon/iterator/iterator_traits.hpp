/**
 *	@file	iterator_traits.hpp
 *
 *	@brief	iterator_traits の定義
 */

#ifndef HAMON_ITERATOR_ITERATOR_TRAITS_HPP
#define HAMON_ITERATOR_ITERATOR_TRAITS_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::iterator_traits;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/detail/iterator_traits_base.hpp>
#include <hamon/iterator/concepts/detail/is_iterator_traits_specialized.hpp>
#include <hamon/iterator/contiguous_iterator_tag.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <cstddef>

namespace hamon
{

// primary template
template <typename Iterator>
struct iterator_traits
	: public detail::iterator_traits_base<Iterator> {};

namespace detail
{

template <typename T, typename>
using enable_iterator_traits_helper = T;

}	// namespace detail

template <typename T>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
requires std::is_object<T>::value
#endif
struct iterator_traits<
	detail::enable_iterator_traits_helper<
		T*,
		hamon::enable_if_t<std::is_object<T>::value>>>
{
	using iterator_concept  = hamon::contiguous_iterator_tag;
	using iterator_category = std::random_access_iterator_tag;
	using value_type	    = hamon::remove_cv_t<T>;
	using difference_type   = std::ptrdiff_t;
	using pointer	        = T*;
	using reference	        = T&;
};

namespace detail
{

template <typename T>
struct is_iterator_traits_specialized<
	detail::enable_iterator_traits_helper<
		T*,
		hamon::enable_if_t<std::is_object<T>::value>>>
{
	static const bool value = true;
};

}	// namespace detail

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_ITERATOR_TRAITS_HPP
