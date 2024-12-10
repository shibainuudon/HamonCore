/**
 *	@file	map_traits.hpp
 *
 *	@brief
 */

#ifndef HAMON_MAP_DETAIL_MAP_TRAITS_HPP
#define HAMON_MAP_DETAIL_MAP_TRAITS_HPP

#include <hamon/tuple/concepts/pair_like.hpp>
#include <hamon/tuple.hpp>
#include <hamon/pair.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/conjunction.hpp>

namespace hamon
{

namespace detail
{

template <typename Key, typename T, bool = hamon::pair_like_t<T>::value>
struct is_same_key_pair
	: public hamon::false_type{};

template <typename Key, typename T>
struct is_same_key_pair<Key, T, true>
	: public hamon::is_same<Key, hamon::remove_cvref_t<hamon::tuple_element_t<0, T>>>{};

template <typename Key, typename ValueType, typename SizeType, typename DifferenceType, bool Multi>
struct map_traits
{
	using value_type = ValueType;
	using size_type = SizeType;
	using difference_type = DifferenceType;
	static const bool multi = Multi;

	template <typename Arg>
	using in_place_comparable =
		hamon::disjunction<
			hamon::is_same<hamon::remove_cvref_t<Key>, hamon::remove_cvref_t<Arg>>,
			hamon::detail::is_same_key_pair<hamon::remove_cvref_t<Key>, hamon::remove_cvref_t<Arg>>
		>;
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MAP_DETAIL_MAP_TRAITS_HPP
