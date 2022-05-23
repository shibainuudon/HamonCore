/**
 *	@file	copy_cv.hpp
 *
 *	@brief	copy_cv の定義
 */

#ifndef HAMON_TYPE_TRAITS_COPY_CV_HPP
#define HAMON_TYPE_TRAITS_COPY_CV_HPP

#include <type_traits>

namespace hamon
{

/**
 *	@brief	cv修飾をコピーする
 *
 *	@tparam	T	基本となる型
 *	@tparam	U	cv修飾のコピー元
 *
 *	Uのcv修飾をTにコピーした型をメンバ型typeとして定義する。
 *
 *	例)
 *	copy_cv<int, void>::type                -> int
 *	copy_cv<int const, void>::type          -> int const
 *	copy_cv<int, void const>::type          -> int const
 *	copy_cv<int volatile, void const>::type -> int const volatile
 *	copy_cv<int&, void const>::type         -> int&
 *	copy_cv<int*, void volatile>::type      -> int* volatile
 */
template <typename T, typename U>
struct copy_cv;

/**
 *	@brief	copy_cvのエイリアス
 */
template <typename T, typename U>
using copy_cv_t = typename copy_cv<T, U>::type;

namespace detail
{

template <typename T, bool, bool>
struct copy_cv_impl
{
	using type = T;
};

template <typename T>
struct copy_cv_impl<T, true, false>
{
	using type = typename std::add_const<T>::type;
};

template <typename T>
struct copy_cv_impl<T, false, true>
{
	using type = typename std::add_volatile<T>::type;
};

template <typename T>
struct copy_cv_impl<T, true, true>
{
	using type = typename std::add_const<
		typename std::add_volatile<T>::type
	>::type;
};

} // namespace detail

template <typename T, typename U>
struct copy_cv
{
	using type = typename detail::copy_cv_impl<
		T,
		std::is_const<U>::value,
		std::is_volatile<U>::value
	>::type;
};

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_COPY_CV_HPP
