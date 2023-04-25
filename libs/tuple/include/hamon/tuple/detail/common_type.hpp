/**
 *	@file	common_type.hpp
 *
 *	@brief	common_type の定義
 */

#ifndef HAMON_TUPLE_DETAIL_COMMON_TYPE_HPP
#define HAMON_TUPLE_DETAIL_COMMON_TYPE_HPP

#include <hamon/tuple/tuple_fwd.hpp>
#include <hamon/tuple/tuple_element.hpp>
#include <hamon/tuple/concepts/tuple_like.hpp>
#include <hamon/concepts/detail/is_specialization_of_tuple.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/index_sequence.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename TTuple, typename UTuple,
    typename Indices = hamon::make_index_sequence<std::tuple_size<TTuple>::value>,
	typename = void>
struct tuple_like_common_type;

template <typename TTuple, typename UTuple, hamon::size_t... I>
struct tuple_like_common_type<TTuple, UTuple,
	hamon::index_sequence<I...>,
	hamon::void_t<hamon::tuple<hamon::common_type_t<
		hamon::tuple_element_t<I, TTuple>,
		hamon::tuple_element_t<I, UTuple>
	>...>>>
{
    using type = hamon::tuple<hamon::common_type_t<
		hamon::tuple_element_t<I, TTuple>,
		hamon::tuple_element_t<I, UTuple>
	>...>;
};

}	// namespace detail

}	// namespace hamon

namespace HAMON_COMMON_TYPE_NAMESPACE
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

// common_reference related specializations	[tuple.common.ref]
template <hamon::tuple_like TTuple, hamon::tuple_like UTuple>
requires
	(hamon::detail::is_specialization_of_tuple<TTuple>::value ||	// [tuple.common.ref]/3.1
	 hamon::detail::is_specialization_of_tuple<UTuple>::value) &&
	hamon::is_same_v<TTuple, hamon::decay_t<TTuple>> &&				// [tuple.common.ref]3.2
	hamon::is_same_v<UTuple, hamon::decay_t<UTuple>> &&				// [tuple.common.ref]3.3
	(std::tuple_size_v<TTuple> == std::tuple_size_v<UTuple>) &&		// [tuple.common.ref]3.4
	requires { typename hamon::detail::tuple_like_common_type<TTuple, UTuple>::type; }	// [tuple.common.ref]3.5
struct common_type<TTuple, UTuple>
{
	using type = typename hamon::detail::tuple_like_common_type<TTuple, UTuple>::type;
};

#else

namespace detail
{

template <
	typename TTuple,
	typename UTuple,
	typename = void,
	typename = void
>
struct tuple_common_type_impl
{};

template <
	typename TTuple,
	typename UTuple
>
struct tuple_common_type_impl<TTuple, UTuple,
	hamon::enable_if_t<
		hamon::is_same<TTuple, hamon::decay_t<TTuple>>::value &&			// [tuple.common.ref]3.2
		hamon::is_same<UTuple, hamon::decay_t<UTuple>>::value &&			// [tuple.common.ref]3.3
		(std::tuple_size<TTuple>::value == std::tuple_size<UTuple>::value)	// [tuple.common.ref]3.4
	>,
	hamon::void_t<typename hamon::detail::tuple_like_common_type<TTuple, UTuple>::type>	// [tuple.common.ref]3.5
>
{
	using type = typename hamon::detail::tuple_like_common_type<TTuple, UTuple>::type;
};

template <
	typename TTuple,
	typename UTuple,
	typename = void
>
struct tuple_common_type
{};

template <
	typename TTuple,
	typename UTuple
>
struct tuple_common_type<TTuple, UTuple,
	hamon::enable_if_t<hamon::conjunction<
		hamon::tuple_like_t<hamon::decay_t<TTuple>>,
		hamon::tuple_like_t<hamon::decay_t<UTuple>>
	>::value>
>
	: public tuple_common_type_impl<hamon::decay_t<TTuple>, hamon::decay_t<UTuple>>
{};

}	// namespace detail

template <typename... TTypes, typename UTuple>
struct common_type<hamon::tuple<TTypes...>, UTuple>
	: public detail::tuple_common_type<hamon::tuple<TTypes...>, UTuple>
{};

template <typename TTuple, typename... UTypes>
struct common_type<TTuple, hamon::tuple<UTypes...>>
	: public detail::tuple_common_type<TTuple, hamon::tuple<UTypes...>>
{};

template <typename... TTypes, typename... UTypes>
struct common_type<hamon::tuple<TTypes...>, hamon::tuple<UTypes...>>
	: public detail::tuple_common_type<hamon::tuple<TTypes...>, hamon::tuple<UTypes...>>
{};

#endif

}	// namespace HAMON_COMMON_TYPE_NAMESPACE

#endif // HAMON_TUPLE_DETAIL_COMMON_TYPE_HPP
