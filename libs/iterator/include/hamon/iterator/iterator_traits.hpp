/**
 *	@file	iterator_traits.hpp
 *
 *	@brief	iterator_traits の定義
 */

#ifndef HAMON_ITERATOR_ITERATOR_TRAITS_HPP
#define HAMON_ITERATOR_ITERATOR_TRAITS_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

#define HAMON_ITERATOR_TRAITS_NAMESPACE  std

namespace hamon
{

using std::iterator_traits;

}	// namespace hamon

#else

#include <hamon/iterator/detail/iterator_traits_base.hpp>
#include <hamon/iterator/contiguous_iterator_tag.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/is_object.hpp>
#include <hamon/config.hpp>

#define HAMON_ITERATOR_TRAITS_NAMESPACE  hamon

namespace hamon
{

namespace detail
{

template <typename T, typename>
using enable_iterator_traits_helper = T;

template <typename T>
struct is_iterator_traits_primary;

}	// namespace detail

// 25.3.2.3 Iterator traits	[iterator.traits]

template <typename I>
struct iterator_traits
	: public detail::iterator_traits_base<I>
{
private:
	// iterator_traits<I>が、プライマリテンプレートから生成されたかどうかを判定するためのタグ。
	// ユーザーがiterator_traitsを特殊化するときに、このタグを *定義してはいけない* 。
	using primary_template_tag = void;
	friend hamon::detail::is_iterator_traits_primary<I>;
};

// [iterator.traits]/5
template <typename T>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
requires hamon::is_object<T>::value
struct iterator_traits<T*>
#else
struct iterator_traits<
	detail::enable_iterator_traits_helper<
		T*,
		hamon::enable_if_t<hamon::is_object<T>::value>>>
#endif
{
	using iterator_concept  = hamon::contiguous_iterator_tag;
	using iterator_category = hamon::random_access_iterator_tag;
	using value_type	    = hamon::remove_cv_t<T>;
	using difference_type   = hamon::ptrdiff_t;
	using pointer	        = T*;
	using reference	        = T&;
};

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_ITERATOR_TRAITS_HPP
