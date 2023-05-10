/**
 *	@file	basic_common_reference.hpp
 *
 *	@brief	basic_common_reference の定義
 */

#ifndef HAMON_PAIR_DETAIL_BASIC_COMMON_REFERENCE_HPP
#define HAMON_PAIR_DETAIL_BASIC_COMMON_REFERENCE_HPP

#include <hamon/type_traits/basic_common_reference.hpp>
#include <hamon/type_traits/common_reference.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace detail {

template <
	typename T1, typename T2,
	typename U1, typename U2,
	template <typename> class TQual,
	template <typename> class UQual
>
using pair_basic_common_reference_impl =
	hamon::pair<
		hamon::common_reference_t<TQual<T1>, UQual<U1>>,
		hamon::common_reference_t<TQual<T2>, UQual<U2>>
	>;

}	// namespace detail
}	// namespace hamon

namespace HAMON_BASIC_COMMON_REFERENCE_NAMESPACE
{

// [utility.syn]

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <
	typename T1, typename T2,
	typename U1, typename U2,
	template <typename> class TQual,
	template <typename> class UQual
>
requires requires
{
	typename hamon::detail::pair_basic_common_reference_impl<
		T1, T2, U1, U2, TQual, UQual>;
}
struct basic_common_reference<
	hamon::pair<T1, T2>, hamon::pair<U1, U2>, TQual, UQual>
{
	using type = hamon::detail::pair_basic_common_reference_impl<
		T1, T2, U1, U2, TQual, UQual>;
};

#else

namespace detail
{

template <
	typename Pair1, typename Pair2,
	template <typename> class TQual,
	template <typename> class UQual,
	typename = void
>
struct pair_basic_common_reference {};

template <
	typename T1, typename T2,
	typename U1, typename U2,
	template <typename> class TQual,
	template <typename> class UQual
>
struct pair_basic_common_reference<
	hamon::pair<T1, T2>, hamon::pair<U1, U2>, TQual, UQual,
	hamon::void_t<hamon::detail::pair_basic_common_reference_impl<
		T1, T2, U1, U2, TQual, UQual>>>
{
	using type = hamon::detail::pair_basic_common_reference_impl<
		T1, T2, U1, U2, TQual, UQual>;
};

}	// namespace detail

template <
	typename T1, typename T2,
	typename U1, typename U2,
	template <typename> class TQual,
	template <typename> class UQual
>
struct basic_common_reference<hamon::pair<T1, T2>, hamon::pair<U1, U2>, TQual, UQual>
	: public detail::pair_basic_common_reference<hamon::pair<T1, T2>, hamon::pair<U1, U2>, TQual, UQual>
{};

#endif

}	// namespace HAMON_BASIC_COMMON_REFERENCE_NAMESPACE

#endif // HAMON_PAIR_DETAIL_BASIC_COMMON_REFERENCE_HPP
