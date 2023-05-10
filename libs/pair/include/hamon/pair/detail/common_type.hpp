/**
 *	@file	common_type.hpp
 *
 *	@brief	common_type の定義
 */

#ifndef HAMON_PAIR_DETAIL_COMMON_TYPE_HPP
#define HAMON_PAIR_DETAIL_COMMON_TYPE_HPP

#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace detail {

template <typename T1, typename T2, typename U1, typename U2>
using pair_common_type_impl =
	hamon::pair<
		hamon::common_type_t<T1, U1>,
		hamon::common_type_t<T2, U2>
	>;

}	// namespace detail
}	// namespace hamon

namespace HAMON_COMMON_TYPE_NAMESPACE
{

// [utility.syn]

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T1, typename T2, typename U1, typename U2>
requires requires
{
	typename hamon::detail::pair_common_type_impl<T1, T2, U1, U2>;
}
struct common_type<hamon::pair<T1, T2>, hamon::pair<U1, U2>>
{
	using type = hamon::detail::pair_common_type_impl<T1, T2, U1, U2>;
};

#else

namespace detail
{

template <typename Pair1, typename Pair2, typename = void>
struct pair_common_type {};

template <typename T1, typename T2, typename U1, typename U2>
struct pair_common_type<hamon::pair<T1, T2>, hamon::pair<U1, U2>,
	hamon::void_t<hamon::detail::pair_common_type_impl<T1, T2, U1, U2>>>
{
	using type = hamon::detail::pair_common_type_impl<T1, T2, U1, U2>;
};

}	// namespace detail

template <typename T1, typename T2, typename U1, typename U2>
struct common_type<hamon::pair<T1, T2>, hamon::pair<U1, U2>>
	: public detail::pair_common_type<hamon::pair<T1, T2>, hamon::pair<U1, U2>>
{};

#endif

}	// namespace HAMON_COMMON_TYPE_NAMESPACE

#endif // HAMON_PAIR_DETAIL_COMMON_TYPE_HPP
