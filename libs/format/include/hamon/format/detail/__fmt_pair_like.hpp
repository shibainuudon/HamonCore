/**
 *	@file	__fmt_pair_like.hpp
 *
 *	@brief	__fmt_pair_like の定義
 */

#ifndef HAMON_FORMAT_DETAIL___FMT_PAIR_LIKE_HPP
#define HAMON_FORMAT_DETAIL___FMT_PAIR_LIKE_HPP

#include <hamon/concepts/detail/is_specialization_of_pair.hpp>
#include <hamon/concepts/detail/is_specialization_of_tuple.hpp>
#include <hamon/tuple/tuple_size.hpp>

namespace hamon
{

namespace detail
{

// [format.range.fmtkind]/2.2.1 and [tab:formatter.range.type]:
// "U is either a specialization of pair or a specialization of tuple such that tuple_size_v<U> is 2."
template <class _Tp>
concept __fmt_pair_like =
	hamon::detail::is_specialization_of_pair<_Tp>::value ||
	(hamon::detail::is_specialization_of_tuple<_Tp>::value && hamon::tuple_size<_Tp>::value == 2);

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FORMAT_DETAIL___FMT_PAIR_LIKE_HPP
