/**
 *	@file	fmt_pair_like.hpp
 *
 *	@brief	fmt_pair_like の定義
 */

#ifndef HAMON_FORMAT_DETAIL_FMT_PAIR_LIKE_HPP
#define HAMON_FORMAT_DETAIL_FMT_PAIR_LIKE_HPP

#include <hamon/concepts/detail/is_specialization_of_pair.hpp>
#include <hamon/concepts/detail/is_specialization_of_tuple.hpp>
#include <hamon/tuple/tuple_size.hpp>
#include <hamon/type_traits/remove_cvref.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
concept fmt_pair_like =
	hamon::detail::is_specialization_of_pair<hamon::remove_cvref_t<T>>::value ||
	(hamon::detail::is_specialization_of_tuple<hamon::remove_cvref_t<T>>::value &&
	 hamon::tuple_size<hamon::remove_cvref_t<T>>::value == 2);

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FORMAT_DETAIL_FMT_PAIR_LIKE_HPP
