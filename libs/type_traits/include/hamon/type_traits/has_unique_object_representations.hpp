/**
 *	@file	has_unique_object_representations.hpp
 *
 *	@brief	has_unique_object_representations の定義
 */

#ifndef HAMON_TYPE_TRAITS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP
#define HAMON_TYPE_TRAITS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.4 Type properties[meta.unary.prop]

/**
 *	@brief		同じ値を持つT型のオブジェクトが同じオブジェクト表現を持つか
 *
 *	@tparam		T	チェックする型
 *
 *	has_unique_object_representationsは、
 *	型TがTriviallyCopyableかつ、
 *	同じ値を持つT型のオブジェクトが同じオブジェクト表現を持つ場合、
 *	true_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *
 *	@note		T型が、不完全型であるか、
 *				void(cv修飾を含む)であるか、
 *				要素数不明の配列である場合、動作は未定義。
 */
template <typename T>
struct has_unique_object_representations
	: public hamon::bool_constant<
#if HAMON_HAS_BUILTIN(__has_unique_object_representations) || defined(HAMON_MSVC)
		__has_unique_object_representations(T)
#else
		// TODO
#endif
	>
{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool has_unique_object_representations_v = has_unique_object_representations<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP
