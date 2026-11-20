/**
 *	@file	exact_width_type.hpp
 *
 *	@brief	exact_width_type の定義
 */

#ifndef HAMON_CSTDINT_DETAIL_EXACT_WIDTH_TYPE_HPP
#define HAMON_CSTDINT_DETAIL_EXACT_WIDTH_TYPE_HPP

namespace hamon
{
namespace detail
{

template <int N, typename... Types>
struct exact_width_type;

template <int N, int M, typename T0, typename... Types>
struct exact_width_type_helper
	: public exact_width_type<N, Types...>
{};

template <int N, typename T0, typename... Types>
struct exact_width_type_helper<N, N, T0, Types...>
{
	using type = T0;
};

template <int N, typename T0, typename... Types>
struct exact_width_type<N, T0, Types...>
	: public exact_width_type_helper<N, sizeof(T0), T0, Types...>
{};

template <int N, typename... Types>
using exact_width_type_t =
	typename exact_width_type<N, Types...>::type;

}	// namespace detail
}	// namespace hamon

#endif // HAMON_CSTDINT_DETAIL_EXACT_WIDTH_TYPE_HPP
