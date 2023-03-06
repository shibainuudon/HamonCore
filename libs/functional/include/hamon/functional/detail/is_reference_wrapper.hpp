/**
 *	@file	is_reference_wrapper.hpp
 *
 *	@brief	is_reference_wrapper クラステンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_DETAIL_IS_REFERENCE_WRAPPER_HPP
#define HAMON_FUNCTIONAL_DETAIL_IS_REFERENCE_WRAPPER_HPP

#include <hamon/functional/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

#if !defined(HAMON_USE_STD_REFERENCE_WRAPPER)
template <typename T>
class reference_wrapper;
#else
using std::reference_wrapper;
#endif

namespace detail
{

template <typename T>
struct is_reference_wrapper
	: public hamon::false_type
{};

template <typename T>
struct is_reference_wrapper<hamon::reference_wrapper<T>>
	: public hamon::true_type
{};

template <typename T>
struct is_reference_wrapper<T const>
	: public is_reference_wrapper<T>
{};

template <typename T>
struct is_reference_wrapper<T volatile>
	: public is_reference_wrapper<T>
{};

template <typename T>
struct is_reference_wrapper<T const volatile>
	: public is_reference_wrapper<T>
{};

template <typename T>
struct is_reference_wrapper<T&>
	: public is_reference_wrapper<T>
{};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FUNCTIONAL_DETAIL_IS_REFERENCE_WRAPPER_HPP
