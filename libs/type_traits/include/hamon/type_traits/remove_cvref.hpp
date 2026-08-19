/**
 *	@file	remove_cvref.hpp
 *
 *	@brief	remove_cvref
 */

#ifndef HAMON_TYPE_TRAITS_REMOVE_CVREF_HPP
#define HAMON_TYPE_TRAITS_REMOVE_CVREF_HPP

#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/remove_reference.hpp>

namespace hamon
{

// 21.3.8.7 Other transformations[meta.trans.other]

/**
 *	@brief		型TからCV修飾と参照を除去する。
 *
 *	@tparam		T
 */
template <typename T>
struct remove_cvref
	: public hamon::remove_cv<hamon::remove_reference_t<T>>
{};

/**
 *	@brief	remove_cvrefのエイリアステンプレート
 */
template <typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_REMOVE_CVREF_HPP
