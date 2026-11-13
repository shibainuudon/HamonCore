/**
 *	@file	is_specialization_of_shared_ptr.hpp
 *
 *	@brief	is_specialization_of_shared_ptr を定義
 */

#ifndef HAMON_MEMORY_DETAIL_IS_SPECIALIZATION_OF_SHARED_PTR_HPP
#define HAMON_MEMORY_DETAIL_IS_SPECIALIZATION_OF_SHARED_PTR_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_NO_STD)
#include <memory>
#endif

namespace hamon
{

namespace detail
{

template <typename T>
struct is_specialization_of_shared_ptr
	: public hamon::false_type {};

#if !defined(HAMON_NO_STD)
template <typename T>
struct is_specialization_of_shared_ptr<std::shared_ptr<T>>
	: public hamon::true_type {};
#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_IS_SPECIALIZATION_OF_SHARED_PTR_HPP
