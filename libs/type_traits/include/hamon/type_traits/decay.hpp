/**
 *	@file	decay.hpp
 *
 *	@brief	decay の定義
 */

#ifndef HAMON_TYPE_TRAITS_DECAY_HPP
#define HAMON_TYPE_TRAITS_DECAY_HPP

#include <hamon/type_traits/add_pointer.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/type_traits/is_function.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/remove_extent.hpp>
#include <hamon/type_traits/remove_reference.hpp>

namespace hamon
{

// 21.3.8.7 Other transformations[meta.trans.other]

/**
 *	@brief	配列と関数ポインタに関して、関数テンプレートと同様に推論された型を取得する。
 *
 *	@tparam	T
 *
 *	このクラステンプレートは、関数テンプレートにおける以下の推論ルールを適用する：
 *	・左辺値から右辺値への変換
 *	・配列からポインタへの変換
 *	・関数の左辺値から関数ポインタへの変換
 *
 *	remove_reference<T>::typeした型をUとする。
 *	型Uが配列型U[N]であれば、U*型をメンバ型typeとして定義する。
 *	型Uが関数型R(Args...)であれば、R(*)(Args...)型をメンバ型typeとして定義する。
 *	それ以外の場合は、remove_cv<U>::typeした型を、メンバ型typeとして定義する。
 */
template <typename T>
struct decay
{
private:
	using U = hamon::remove_reference_t<T>;

public:
	using type = hamon::conditional_t<
		hamon::is_array_v<U>,
		hamon::remove_extent_t<U>*,
		hamon::conditional_t<
			hamon::is_function_v<U>,
			hamon::add_pointer_t<U>,
			hamon::remove_cv_t<U>
		>
	>;
};

template <typename T>
using decay_t = typename decay<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_DECAY_HPP
