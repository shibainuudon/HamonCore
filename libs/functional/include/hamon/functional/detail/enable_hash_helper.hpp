/**
 *	@file	enable_hash_helper.hpp
 *
 *	@brief	enable_hash_helper の定義
 */

#ifndef HAMON_FUNCTIONAL_DETAIL_ENABLE_HASH_HELPER_HPP
#define HAMON_FUNCTIONAL_DETAIL_ENABLE_HASH_HELPER_HPP

#include <hamon/concepts/detail/cpp17_hash.hpp>
#include <hamon/functional/hash_fwd.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/detail/all.hpp>

namespace hamon
{

namespace detail
{

template <typename T, typename>
using enable_hash_helper_imp = T;

template <typename T, typename... Keys>
using enable_hash_helper = enable_hash_helper_imp<T,
	hamon::enable_if_t<hamon::detail::all_v<
		hamon::detail::cpp17_hash<
			hamon::hash<Keys>, Keys
		>...
	>>
>;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FUNCTIONAL_DETAIL_ENABLE_HASH_HELPER_HPP
