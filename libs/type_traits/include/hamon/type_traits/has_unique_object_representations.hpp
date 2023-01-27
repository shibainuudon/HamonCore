/**
 *	@file	has_unique_object_representations.hpp
 *
 *	@brief	has_unique_object_representations の定義
 */

#ifndef HAMON_TYPE_TRAITS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP
#define HAMON_TYPE_TRAITS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP

#include <hamon/config.hpp>
#include <type_traits>

#if defined(__cpp_lib_has_unique_object_representations) && (__cpp_lib_has_unique_object_representations >= 201606)

namespace hamon
{

using std::has_unique_object_representations;

}	// namespace hamon

#elif (defined(HAMON_MSVC) && HAMON_MSVC >= 1920) ||	\
	HAMON_HAS_BUILTIN(__has_unique_object_representations)

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

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
		__has_unique_object_representations(T)
	>
{};

}	// namespace hamon

#else
#  define HAMON_NO_HAS_UNIQUE_OBJECT_REPRESENTATIONS
#endif

#if !defined(HAMON_NO_HAS_UNIQUE_OBJECT_REPRESENTATIONS)

#define HAMON_HAS_HAS_UNIQUE_OBJECT_REPRESENTATIONS

namespace hamon
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool has_unique_object_representations_v = has_unique_object_representations<T>::value;
#endif

}	// namespace hamon

#endif

#endif // HAMON_TYPE_TRAITS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP
