/**
 *	@file	is_iterator_traits_primary.hpp
 *
 *	@brief	is_iterator_traits_primary の定義
 */

#ifndef HAMON_ITERATOR_DETAIL_IS_ITERATOR_TRAITS_PRIMARY_HPP
#define HAMON_ITERATOR_DETAIL_IS_ITERATOR_TRAITS_PRIMARY_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>

namespace hamon
{

template <typename I>
struct iterator_traits;

namespace detail
{

template <typename T>
struct is_iterator_traits_primary
{
private:
	template <typename T2,
		typename = typename hamon::iterator_traits<T2>::primary_template_tag>
	static auto test(int) -> hamon::true_type;

	template <typename>
	static auto test(...) -> hamon::false_type;

	using type = decltype(test<T>(0));

public:
	static const bool value = type::value;
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_DETAIL_IS_ITERATOR_TRAITS_PRIMARY_HPP
