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

template <typename Key, typename... Args>
struct map_in_place_key_extractor
	: public hamon::false_type {};

template <typename Key, typename Value>
struct map_in_place_key_extractor<Key, Key, Value>
	: public hamon::true_type
{
	static constexpr Key const& extract(Key const& v, Value const&) noexcept
	{
		return v;
	}
};

template <typename Key, typename PairLike>
struct map_in_place_key_extractor<Key, PairLike>
	: public hamon::pair_like_t<PairLike>
{
	static constexpr Key const& extract(PairLike const& v) noexcept
	{
		return hamon::get<0>(v);
	}
};

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
			hamon::is_same<Key, hamon::remove_cvref_t<Arg>>,
			hamon::pair_like_t<Arg>
		>;
	//template <typename... Args>
	//using in_place_key_extractor = map_in_place_key_extractor<Key, hamon::remove_cvref_t<Args>...>;
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MAP_DETAIL_MAP_TRAITS_HPP
