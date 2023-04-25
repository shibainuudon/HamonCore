/**
 *	@file	basic_common_reference.hpp
 *
 *	@brief	basic_common_reference の定義
 */

#ifndef HAMON_TUPLE_DETAIL_BASIC_COMMON_REFERENCE_HPP
#define HAMON_TUPLE_DETAIL_BASIC_COMMON_REFERENCE_HPP

#include <hamon/tuple/tuple_fwd.hpp>
#include <hamon/tuple/tuple_element.hpp>
#include <hamon/tuple/concepts/tuple_like.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/concepts/detail/is_specialization_of_tuple.hpp>
#include <hamon/type_traits/basic_common_reference.hpp>
#include <hamon/type_traits/common_reference.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/index_sequence.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace detail {

template <
	typename TTuple,
	typename UTuple,
	template <typename> class TQual,
	template <typename> class UQual,
    typename Indices = hamon::make_index_sequence<std::tuple_size<TTuple>::value>,
	typename = void>
struct tuple_like_common_reference;

template <
	typename TTuple,
	typename UTuple,
	template <typename> class TQual,
	template <typename> class UQual,
    hamon::size_t... I>
struct tuple_like_common_reference<TTuple, UTuple, TQual, UQual,
	hamon::index_sequence<I...>,
	hamon::void_t<hamon::tuple<hamon::common_reference_t<
		TQual<hamon::tuple_element_t<I, TTuple>>,
		UQual<hamon::tuple_element_t<I, UTuple>>
	>...>>
>
{
    using type = hamon::tuple<hamon::common_reference_t<
		TQual<hamon::tuple_element_t<I, TTuple>>,
		UQual<hamon::tuple_element_t<I, UTuple>>
	>...>;
};

}	// namespace detail
}	// namespace hamon

namespace HAMON_BASIC_COMMON_REFERENCE_NAMESPACE
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

// common_reference related specializations	[tuple.common.ref]
template <
	hamon::tuple_like TTuple,
	hamon::tuple_like UTuple,
	template <typename> class TQual,
	template <typename> class UQual>
requires
	(hamon::detail::is_specialization_of_tuple<TTuple>::value ||
	 hamon::detail::is_specialization_of_tuple<UTuple>::value) &&	// [tuple.common.ref]/2.1
	hamon::is_same_v<TTuple, hamon::decay_t<TTuple>> &&		// [tuple.common.ref]2.2
	hamon::is_same_v<UTuple, hamon::decay_t<UTuple>> &&		// [tuple.common.ref]2.3
	(std::tuple_size_v<TTuple> == std::tuple_size_v<UTuple>) &&	// [tuple.common.ref]2.4
	requires { typename hamon::detail::tuple_like_common_reference<TTuple, UTuple, TQual, UQual>::type; }	// [tuple.common.ref]2.5
struct basic_common_reference<TTuple, UTuple, TQual, UQual>
{
	using type = typename hamon::detail::tuple_like_common_reference<TTuple, UTuple, TQual, UQual>::type;
};

#else

namespace detail
{

template <
	typename TTuple,
	typename UTuple,
	template <typename> class TQual,
	template <typename> class UQual,
	typename = void,
	typename = void
>
struct tuple_basic_common_reference_impl
{};

template <
	typename TTuple,
	typename UTuple,
	template <typename> class TQual,
	template <typename> class UQual
>
struct tuple_basic_common_reference_impl<TTuple, UTuple, TQual, UQual,
	hamon::enable_if_t<
		hamon::is_same<TTuple, hamon::decay_t<TTuple>>::value &&		// [tuple.common.ref]2.2
		hamon::is_same<UTuple, hamon::decay_t<UTuple>>::value &&		// [tuple.common.ref]2.3
		(std::tuple_size<TTuple>::value == std::tuple_size<UTuple>::value)	// [tuple.common.ref]2.4
	>,
	hamon::void_t<typename hamon::detail::tuple_like_common_reference<TTuple, UTuple, TQual, UQual>::type>	// [tuple.common.ref]2.5
>
{
	using type = typename hamon::detail::tuple_like_common_reference<TTuple, UTuple, TQual, UQual>::type;
};

template <
	typename TTuple,
	typename UTuple,
	template <typename> class TQual,
	template <typename> class UQual,
	typename = void
>
struct tuple_basic_common_reference
{};

template <
	typename TTuple,
	typename UTuple,
	template <typename> class TQual,
	template <typename> class UQual
>
struct tuple_basic_common_reference<TTuple, UTuple, TQual, UQual,
	hamon::enable_if_t<hamon::conjunction<
		hamon::tuple_like_t<TTuple>,
		hamon::tuple_like_t<UTuple>
	>::value>
>
	: public tuple_basic_common_reference_impl<TTuple, UTuple, TQual, UQual>
{};

}	// namespace detail

template <
	typename... TTypes,
	typename UTuple,
	template <typename> class TQual,
	template <typename> class UQual>
struct basic_common_reference<hamon::tuple<TTypes...>, UTuple, TQual, UQual>
	: public detail::tuple_basic_common_reference<hamon::tuple<TTypes...>, UTuple, TQual, UQual>
{};

template <
	typename TTuple,
	typename... UTypes,
	template <typename> class TQual,
	template <typename> class UQual>
struct basic_common_reference<TTuple, hamon::tuple<UTypes...>, TQual, UQual>
	: public detail::tuple_basic_common_reference<TTuple, hamon::tuple<UTypes...>, TQual, UQual>
{};

template <
	typename... TTypes,
	typename... UTypes,
	template <typename> class TQual,
	template <typename> class UQual>
struct basic_common_reference<hamon::tuple<TTypes...>, hamon::tuple<UTypes...>, TQual, UQual>
	: public detail::tuple_basic_common_reference<hamon::tuple<TTypes...>, hamon::tuple<UTypes...>, TQual, UQual>
{};

#endif

}	// namespace HAMON_BASIC_COMMON_REFERENCE_NAMESPACE

#endif // HAMON_TUPLE_DETAIL_BASIC_COMMON_REFERENCE_HPP
