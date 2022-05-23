/**
 *	@file	common_type_fold.hpp
 *
 *	@brief	common_type_fold の定義
 */

#ifndef HAMON_TYPE_TRAITS_DETAIL_COMMON_TYPE_FOLD_HPP
#define HAMON_TYPE_TRAITS_DETAIL_COMMON_TYPE_FOLD_HPP

#include <hamon/type_traits/void_t.hpp>

namespace hamon
{

namespace detail
{

template <typename, typename, typename = hamon::void_t<>>
struct common_type_fold
{};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_DETAIL_COMMON_TYPE_FOLD_HPP
