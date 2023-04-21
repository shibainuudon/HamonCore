/**
 *	@file	basic_common_reference.hpp
 *
 *	@brief	basic_common_reference の定義
 */

#ifndef HAMON_TYPE_TRAITS_BASIC_COMMON_REFERENCE_HPP
#define HAMON_TYPE_TRAITS_BASIC_COMMON_REFERENCE_HPP

#include <hamon/type_traits/config.hpp>

#if defined(HAMON_USE_STD_COMMON_REFERENCE)

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
