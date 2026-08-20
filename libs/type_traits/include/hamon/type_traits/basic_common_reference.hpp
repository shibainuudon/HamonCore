/**
 *	@file	basic_common_reference.hpp
 *
 *	@brief	basic_common_reference の定義
 */

#ifndef HAMON_TYPE_TRAITS_BASIC_COMMON_REFERENCE_HPP
#define HAMON_TYPE_TRAITS_BASIC_COMMON_REFERENCE_HPP

namespace hamon
{

template <
	typename T,
	typename U,
	template <typename> class TQual,
	template <typename> class UQual,
	typename = void
>
struct basic_common_reference
{};

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_BASIC_COMMON_REFERENCE_HPP
