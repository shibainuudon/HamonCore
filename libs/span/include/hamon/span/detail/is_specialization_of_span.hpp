/**
 *	@file	is_specialization_of_span.hpp
 *
 *	@brief	is_specialization_of_span の定義
 */

#ifndef HAMON_SPAN_DETAIL_IS_SPECIALIZATION_OF_SPAN_HPP
#define HAMON_SPAN_DETAIL_IS_SPECIALIZATION_OF_SPAN_HPP

#include <hamon/span/span_fwd.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
struct is_specialization_of_span
	: public hamon::false_type {};

template <typename T, hamon::size_t N>
struct is_specialization_of_span<hamon::span<T, N>>
	: public hamon::true_type {};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_SPAN_DETAIL_IS_SPECIALIZATION_OF_SPAN_HPP
