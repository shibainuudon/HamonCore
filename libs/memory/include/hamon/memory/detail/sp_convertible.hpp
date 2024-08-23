/**
 *	@file	sp_convertible.hpp
 *
 *	@brief	sp_convertible を定義
 */

#ifndef HAMON_MEMORY_DETAIL_SP_CONVERTIBLE_HPP
#define HAMON_MEMORY_DETAIL_SP_CONVERTIBLE_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/type_traits/negation.hpp>

namespace hamon
{

namespace detail
{

// [util.smartptr.shared.const]/9
// If T is an array type, then either T is U[N] and Y(*)[N] is convertible to T*,
// or T is U[] and Y(*)[] is convertible to T*.
// If T is not an array type, then Y* is convertible to T*.

template <typename Y, typename T, typename = void>
struct sp_convertible : public hamon::conjunction<
	hamon::negation<hamon::is_array<T>>,
	hamon::is_convertible<Y*, T*>
>{};

template <typename Y, typename U>
struct sp_convertible<Y, U[], hamon::enable_if_t<hamon::conjunction<
	hamon::negation<hamon::is_void<Y>>,
	hamon::is_convertible<Y(*)[], U(*)[]>>::value>>
	: public hamon::true_type {};

template <typename Y, typename U, hamon::size_t N>
struct sp_convertible<Y, U[N], hamon::enable_if_t<hamon::conjunction<
	hamon::negation<hamon::is_void<Y>>,
	hamon::is_convertible<Y(*)[N], U(*)[N]>>::value>>
	: public hamon::true_type {};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_SP_CONVERTIBLE_HPP
