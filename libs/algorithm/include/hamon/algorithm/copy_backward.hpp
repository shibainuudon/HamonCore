/**
 *	@file	copy_backward.hpp
 *
 *	@brief	copy_backward の定義
 */

#ifndef HAMON_ALGORITHM_COPY_BACKWARD_HPP
#define HAMON_ALGORITHM_COPY_BACKWARD_HPP

//#include <hamon/type_traits/enable_if.hpp>
//#include <hamon/type_traits/remove_const.hpp>
//#include <hamon/type_traits/is_same.hpp>
//#include <hamon/type_traits/is_trivially_copy_assignable.hpp>
//#include <hamon/cstddef/size_t.hpp>
//#include <hamon/cstring/memmove.hpp>
#include <hamon/config.hpp>
//#include <cstddef>

namespace hamon
{

namespace detail
{

template <typename BidirectionalIterator, typename OutputIterator>
inline HAMON_CXX14_CONSTEXPR OutputIterator
copy_backward_impl(
	BidirectionalIterator first,
	BidirectionalIterator last,
	OutputIterator result)
{
	while (first != last)
	{
		*--result = *--last;
	}

	return result;
}

#if 0
template <typename T, typename U>
inline HAMON_CXX14_CONSTEXPR
hamon::enable_if_t<
	hamon::is_same<hamon::remove_const_t<T>, U>::value &&
	hamon::is_trivially_copy_assignable<U>::value,
	U*
>
copy_backward_impl(T* first, T* last, U* result)
{
	auto const n = static_cast<hamon::size_t>(last - first);

	if (n > 0)
	{
		result -= n;
		hamon::memmove(result, first, n * sizeof(U));
	}

	return result;
}
#endif

}	// namespace detail

/**
 *	@brief		指定された範囲の要素を後ろからコピーする
 *
 *	@tparam		BidirectionalIterator1
 *	@tparam		BidirectionalIterator2
 *
 *	@param		first
 *	@param		last
 *	@param		result
 *
 *	@require	result は (first,last] の範囲に含まれてはならない
 *
 *	@return		result + (last - first)
 *
 *	@effect		[first,last) 内にある要素を、それぞれ [result - (last-first),result) へコピーする。
 *				コピーは last - 1 から順番に行い、1 以上 last - first 以下であるそれぞれの n について、
 *				*(result - n) = *(last - n) を行う。
 *
 *	@complexity	正確に last - first 回代入が行われる。
 *
 *	@note		last が [result - (last-first), result) の範囲内にあるときには、
 *				copy() の代わりに copy_backward() を使うべきである。
 */
template <
	typename BidirectionalIterator1,
	typename BidirectionalIterator2
>
inline HAMON_CXX14_CONSTEXPR BidirectionalIterator2
copy_backward(
	BidirectionalIterator1 first,
	BidirectionalIterator1 last,
	BidirectionalIterator2 result)
{
	return hamon::detail::copy_backward_impl(first, last, result);
}

}	// namespace hamon

#endif // HAMON_ALGORITHM_COPY_BACKWARD_HPP
