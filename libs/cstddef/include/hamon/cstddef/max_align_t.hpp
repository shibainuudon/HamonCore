/**
 *	@file	max_align_t.hpp
 *
 *	@brief	max_align_t の定義
 */

#ifndef HAMON_CSTDDEF_MAX_ALIGN_T_HPP
#define HAMON_CSTDDEF_MAX_ALIGN_T_HPP

namespace hamon
{

namespace detail
{

template <typename T, typename U, bool = (alignof(T) > alignof(U))>
struct greater_align
{
	using type = T;
};

template <typename T, typename U>
struct greater_align<T, U, false>
{
	using type = U;
};

template <typename T, typename U>
using greater_align_t =
	typename greater_align<T, U>::type;

}	// namespace detail

// [support.types.layout]/5
using max_align_t =
	// long long, long double, ポインタ型 のうち、最もアライメントが大きい型を選ぶ
	hamon::detail::greater_align_t<
		hamon::detail::greater_align_t<long long, long double>,
		void*
	>;

}	// namespace hamon

#endif // HAMON_CSTDDEF_MAX_ALIGN_T_HPP
