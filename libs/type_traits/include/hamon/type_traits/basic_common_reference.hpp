/**
 *	@file	basic_common_reference.hpp
 *
 *	@brief	basic_common_reference の定義
 */

#ifndef HAMON_TYPE_TRAITS_BASIC_COMMON_REFERENCE_HPP
#define HAMON_TYPE_TRAITS_BASIC_COMMON_REFERENCE_HPP

#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS) && HAMON_HAS_INCLUDE(<concepts>)
#include <concepts>
#endif

#if defined(__cpp_lib_concepts) && (__cpp_lib_concepts >= 202002)

#include <type_traits>

namespace hamon
{

#define HAMON_BASIC_COMMON_REFERENCE_NAMESPACE std

using std::basic_common_reference;

}	// namespace hamon

#else

namespace hamon
{

#define HAMON_BASIC_COMMON_REFERENCE_NAMESPACE hamon

template <
	typename T,
	typename U,
	template <typename> class TQual,
	template <typename> class UQual
>
struct basic_common_reference
{};

}	// namespace hamon

#endif

#endif // HAMON_TYPE_TRAITS_BASIC_COMMON_REFERENCE_HPP
