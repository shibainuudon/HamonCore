/**
 *	@file	tuple_constraint.hpp
 *
 *	@brief	tuple_constraint の定義
 */

#ifndef HAMON_TUPLE_DETAIL_TUPLE_CONSTRAINT_HPP
#define HAMON_TUPLE_DETAIL_TUPLE_CONSTRAINT_HPP

#include <hamon/tuple/tuple_fwd.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/tuple/concepts/tuple_like.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/detail/is_specialization_of_subrange.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/memory/allocator_arg_t.hpp>
#include <hamon/memory/detail/is_uses_allocator_constructible.hpp>
#include <hamon/memory/detail/is_implicitly_uses_allocator_constructible.hpp>
#include <hamon/memory/detail/is_nothrow_uses_allocator_constructible.hpp>
#include <hamon/ranges/utility/detail/different_from.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_implicitly_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_assignable.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/nth.hpp>
#include <hamon/type_traits/reference_constructs_from_temporary.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/index_sequence.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace tuple_detail {

template <typename IndexSequence, typename... Types>
struct tuple_constraint;

template <hamon::size_t... Is, typename... Types>
struct tuple_constraint<hamon::index_sequence<Is...>, Types...>
{
private:
	template <typename>
	struct always_true : public hamon::true_type{};

public:
	template <typename Dummy>
	struct DefaultCtor
	{
		// [tuple.cnstr]/6
		static const bool constructible =
			hamon::conjunction<
				always_true<Dummy>,
				hamon::is_default_constructible<Types>...
			>::value;

		// [tuple.cnstr]/8
		static const bool implicitly =
			hamon::conjunction<
				always_true<Dummy>,
				hamon::is_implicitly_default_constructible<Types>...
			>::value;

		// [tuple.cnstr]/2
		static const bool nothrow =
			hamon::conjunction<
				always_true<Dummy>,
				hamon::is_nothrow_default_constructible<Types>...
			>::value;
	};

	template <typename Dummy>
	struct ElementCtor
	{
		// [tuple.cnstr]/9
		static const bool constructible =
			hamon::conjunction<
				always_true<Dummy>,
				hamon::bool_constant<(sizeof...(Types) >= 1)>,
				hamon::is_copy_constructible<Types>...
			>::value;

		// [tuple.cnstr]/11
		static const bool implicitly =
			hamon::conjunction<
				always_true<Dummy>,
				hamon::is_convertible<Types const&, Types>...
			>::value;

		// [tuple.cnstr]/2
		static const bool nothrow =
			hamon::conjunction<
				always_true<Dummy>,
				hamon::is_nothrow_copy_constructible<Types>...
			>::value;
	};

private:
	// [tuple.cnstr]/12
	template <typename T0, typename U0, hamon::size_t>
	struct disambiguating_constraint
		: public hamon::true_type {};	// [tuple.cnstr]/12.3

	// [tuple.cnstr]/12.1
	template <typename T0, typename U0>
	struct disambiguating_constraint<T0, U0, 1>
		: public hamon::negation<hamon::is_same<hamon::remove_cvref_t<U0>, tuple<Types...>>> {};

	// [tuple.cnstr]/12.2
	template <typename T0, typename U0>
	struct disambiguating_constraint<T0, U0, 2>
		: public hamon::bool_constant<
			!hamon::is_same<hamon::remove_cvref_t<U0>, hamon::allocator_arg_t>::value ||
			 hamon::is_same<hamon::remove_cvref_t<T0>, hamon::allocator_arg_t>::value> {};
	// [tuple.cnstr]/12.2
	template <typename T0, typename U0>
	struct disambiguating_constraint<T0, U0, 3>
		: public disambiguating_constraint<T0, U0, 2> {};

	template <bool, typename... UTypes>
	struct UTypesCtorImpl
	{
		// [tuple.cnstr]/13
		static const bool constructible =
			hamon::conjunction<
				disambiguating_constraint<					// [tuple.cnstr]/13.3
					hamon::nth_t<0, Types...>,
					hamon::nth_t<0, UTypes...>,
					sizeof...(Types)
				>,
				hamon::is_constructible<Types, UTypes>...	// [tuple.cnstr]/13.3
			>::value;

		// [tuple.cnstr]/15
#if defined(HAMON_HAS_REFERENCE_CONSTRUCTS_FROM_TEMPORARY)
		static const bool dangles =
			hamon::disjunction<
				hamon::reference_constructs_from_temporary<Types, UTypes&&>...
			>::value;
#else
		static const bool dangles = false;
#endif

		// [tuple.cnstr]/15
		static const bool implicitly =
			hamon::conjunction<
				hamon::is_convertible<UTypes, Types>...
			>::value;

		// [tuple.cnstr]/2
		static const bool nothrow =
			hamon::conjunction<
				hamon::is_nothrow_constructible<Types, UTypes>...
			>::value;
	};
	
	template <typename... UTypes>
	struct UTypesCtorImpl<false, UTypes...>
	{
		static const bool constructible = false;
		static const bool dangles = false;
		static const bool implicitly = false;
		static const bool nothrow = false;
	};

public:
	template <typename... UTypes>
	struct UTypesCtor : public UTypesCtorImpl<
		sizeof...(Types) == sizeof...(UTypes) &&	// [tuple.cnstr]/13.1
		(sizeof...(Types) >= 1),					// [tuple.cnstr]/13.2
		UTypes...
	>{};

private:
	template <bool, typename UTuple, typename... UTypes>
	struct UTupleCtorImpl
	{
		// [tuple.cnstr]/21
		static const bool constructible =
			hamon::conjunction<
				// [tuple.cnstr]/21.2
				hamon::is_constructible<
					Types, decltype(hamon::adl_get<Is>(hamon::declval<UTuple>()))
				>...,
				// [tuple.cnstr]/21.3
				hamon::disjunction<
					hamon::bool_constant<sizeof...(Types) != 1>,
					hamon::conjunction<
						hamon::negation<hamon::is_convertible<UTuple, Types>>...,
						hamon::negation<hamon::is_constructible<Types, UTuple>>...,
						hamon::negation<hamon::is_same<Types, UTypes>>...
					>
				>
			>::value;

		// [tuple.cnstr]/23
#if defined(HAMON_HAS_REFERENCE_CONSTRUCTS_FROM_TEMPORARY)
		static const bool dangles =
			hamon::disjunction<
				hamon::reference_constructs_from_temporary<
					Types, decltype(hamon::adl_get<Is>(hamon::declval<UTuple>()))
				>...
			>::value;
#else
		static const bool dangles = false;
#endif

		// [tuple.cnstr]/23
		static const bool implicitly =
			hamon::conjunction<
				hamon::is_convertible<
					decltype(hamon::adl_get<Is>(hamon::declval<UTuple>())), Types
				>...
			>::value;

		// [tuple.cnstr]/2
		static const bool nothrow =
			hamon::conjunction<
				hamon::is_nothrow_constructible<
					Types, decltype(hamon::adl_get<Is>(hamon::declval<UTuple>()))
				>...
			>::value;
	};

	template <typename UTuple, typename... UTypes>
	struct UTupleCtorImpl<false, UTuple, UTypes...>
	{
		static const bool constructible = false;
		static const bool dangles = false;
		static const bool implicitly = false;
		static const bool nothrow = false;
	};

public:
	template <typename UTuple, typename... UTypes>
	struct UTupleCtor : public UTupleCtorImpl<
		sizeof...(Types) == sizeof...(UTypes),	// [tuple.cnstr]/21.1
		UTuple,
		UTypes...
	>{};

private:
	template <bool, typename UTuple>
	struct TupleLikeCtorImpl
	{
		static const bool constructible =
			hamon::conjunction<
				// [tuple.cnstr]/29.4
				hamon::is_constructible<
					Types, decltype(hamon::adl_get<Is>(hamon::declval<UTuple>()))
				>...,
				// [tuple.cnstr]/29.5
				hamon::disjunction<
					hamon::bool_constant<sizeof...(Types) != 1>,
					hamon::conjunction<
						hamon::negation<hamon::is_convertible<UTuple, Types>>...,
						hamon::negation<hamon::is_constructible<Types, UTuple>>...
					>
				>
			>::value;

		// [tuple.cnstr]/31
		static const bool implicitly =
			hamon::conjunction<
				hamon::is_convertible<
					decltype(hamon::adl_get<Is>(hamon::declval<UTuple>())), Types
				>...
			>::value;

		// [tuple.cnstr]/2
		static const bool nothrow =
			hamon::conjunction<
				hamon::is_nothrow_constructible<
					Types, decltype(hamon::adl_get<Is>(hamon::declval<UTuple>()))
				>...
			>::value;
	};

	template <typename UTuple>
	struct TupleLikeCtorImpl<false, UTuple>
	{
		static const bool constructible = false;
		static const bool implicitly = false;
		static const bool nothrow = false;
	};

public:
	template <HAMON_CONSTRAINED_PARAM(hamon::tuple_like, UTuple)>
	struct TupleLikeCtor : public TupleLikeCtorImpl<
		hamon::ranges::detail::different_from_t<UTuple, hamon::tuple<Types...>>::value &&		// [tuple.cnstr]/29.1
		!hamon::detail::is_specialization_of_subrange<hamon::remove_cvref_t<UTuple>>::value &&	// [tuple.cnstr]/29.2
		sizeof...(Types) == std::tuple_size<hamon::remove_cvref_t<UTuple>>::value,				// [tuple.cnstr]/29.3
		UTuple
	>{};

private:
	template <bool, typename Pair>
	struct PairCtorImpl
	{
	private:
		using T0 = hamon::nth_t<0, Types...>;
		using T1 = hamon::nth_t<1, Types...>;

		using U0 = decltype(hamon::adl_get<0>(hamon::declval<Pair>()));
		using U1 = decltype(hamon::adl_get<1>(hamon::declval<Pair>()));

	public:
		// [tuple.cnstr]/25
		static const bool constructible =
			hamon::conjunction<
				hamon::is_constructible<T0, U0>,	// [tuple.cnstr]/25.2
				hamon::is_constructible<T1, U1>		// [tuple.cnstr]/25.3
			>::value;

		// [tuple.cnstr]/27
#if defined(HAMON_HAS_REFERENCE_CONSTRUCTS_FROM_TEMPORARY)
		static const bool dangles =
			hamon::disjunction<
				hamon::reference_constructs_from_temporary<T0, U0>,
				hamon::reference_constructs_from_temporary<T1, U1>
			>::value;
#else
		static const bool dangles = false;
#endif

		// [tuple.cnstr]/27
		static const bool implicitly =
			hamon::conjunction<
				hamon::is_convertible<U0, T0>,
				hamon::is_convertible<U1, T1>
			>::value;

		// [tuple.cnstr]/2
		static const bool nothrow =
			hamon::conjunction<
				hamon::is_nothrow_constructible<T0, U0>,
				hamon::is_nothrow_constructible<T1, U1>
			>::value;
	};

	template <typename Pair>
	struct PairCtorImpl<false, Pair>
	{
		static const bool constructible = false;
		static const bool dangles = false;
		static const bool implicitly = false;
		static const bool nothrow = false;
	};

public:
	template <typename Pair>
	struct PairCtor : public PairCtorImpl<
		sizeof...(Types) == 2,		// [tuple.cnstr]/25.1
		Pair
	>{};

private:
	template <bool, typename UTuple>
	struct TupleLikeAssignImpl
	{
		static const bool assignable =
			hamon::conjunction<
				// [tuple.cnstr]/39.4
				hamon::is_assignable<
					Types&, decltype(hamon::adl_get<Is>(hamon::declval<UTuple>()))
				>...
			>::value;

		// [tuple.cnstr]/2
		static const bool nothrow =
			hamon::conjunction<
				hamon::is_nothrow_assignable<
					Types&, decltype(hamon::adl_get<Is>(hamon::declval<UTuple>()))
				>...
			>::value;
	};

	template <typename UTuple>
	struct TupleLikeAssignImpl<false, UTuple>
	{
		static const bool assignable = false;
		static const bool nothrow = false;
	};

public:
	template <HAMON_CONSTRAINED_PARAM(hamon::tuple_like, UTuple)>
	struct TupleLikeAssign : public TupleLikeAssignImpl<
		hamon::ranges::detail::different_from_t<UTuple, hamon::tuple<Types...>>::value &&		// [tuple.cnstr]/39.1
		!hamon::detail::is_specialization_of_subrange<hamon::remove_cvref_t<UTuple>>::value &&	// [tuple.cnstr]/39.2
		sizeof...(Types) == std::tuple_size<hamon::remove_cvref_t<UTuple>>::value,				// [tuple.cnstr]/39.3
		UTuple
	>{};

private:
	template <bool, typename UTuple>
	struct TupleLikeAssignConstImpl
	{
		static const bool assignable =
			hamon::conjunction<
				// [tuple.cnstr]/42.4
				hamon::is_assignable<
					Types const&, decltype(hamon::adl_get<Is>(hamon::declval<UTuple>()))
				>...
			>::value;

		// [tuple.cnstr]/2
		static const bool nothrow =
			hamon::conjunction<
				hamon::is_nothrow_assignable<
					Types const&, decltype(hamon::adl_get<Is>(hamon::declval<UTuple>()))
				>...
			>::value;
	};

	template <typename UTuple>
	struct TupleLikeAssignConstImpl<false, UTuple>
	{
		static const bool assignable = false;
		static const bool nothrow = false;
	};

public:
	template <HAMON_CONSTRAINED_PARAM(hamon::tuple_like, UTuple)>
	struct TupleLikeAssignConst : public TupleLikeAssignConstImpl<
		hamon::ranges::detail::different_from_t<UTuple, hamon::tuple<Types...>>::value &&		// [tuple.cnstr]/42.1
		!hamon::detail::is_specialization_of_subrange<hamon::remove_cvref_t<UTuple>>::value &&	// [tuple.cnstr]/42.2
		sizeof...(Types) == std::tuple_size<hamon::remove_cvref_t<UTuple>>::value,				// [tuple.cnstr]/42.3
		UTuple
	>{};

	template <typename Alloc>
	struct AllocDefaultCtor
	{
		static const bool constructible =
			hamon::conjunction<
				hamon::detail::is_uses_allocator_constructible<Types, Alloc>...
			>::value;

		static const bool implicitly =
			hamon::conjunction<
				hamon::detail::is_implicitly_uses_allocator_constructible<Types, Alloc>...
			>::value;

		static const bool nothrow =
			hamon::conjunction<
				hamon::detail::is_nothrow_uses_allocator_constructible<Types, Alloc>...
			>::value;
	};

private:
	template <bool, typename Alloc, typename... UTypes>
	struct AllocUTypesCtorImpl
	{
		static const bool constructible =
			hamon::conjunction<
				hamon::detail::is_uses_allocator_constructible<Types, Alloc, UTypes>...
			>::value;

		static const bool implicitly =
			hamon::conjunction<
				hamon::detail::is_implicitly_uses_allocator_constructible<Types, Alloc, UTypes>...
			>::value;

		static const bool nothrow =
			hamon::conjunction<
				hamon::detail::is_nothrow_uses_allocator_constructible<Types, Alloc, UTypes>...
			>::value;
	};
	
	template <typename Alloc, typename... UTypes>
	struct AllocUTypesCtorImpl<false, Alloc, UTypes...>
	{
		static const bool constructible = false;
		static const bool implicitly = false;
		static const bool nothrow = false;
	};

public:
	template <typename Alloc, typename... UTypes>
	struct AllocUTypesCtor : public AllocUTypesCtorImpl<
		sizeof...(Types) == sizeof...(UTypes),
		Alloc,
		UTypes...
	>{};

private:
	template <bool, typename Alloc, typename UTuple>
	struct AllocUTupleCtorImpl
	{
		static const bool constructible =
			hamon::conjunction<
				hamon::detail::is_uses_allocator_constructible<
					Types, Alloc, decltype(hamon::adl_get<Is>(hamon::declval<UTuple>()))
				>...
			>::value;

		static const bool implicitly =
			hamon::conjunction<
				hamon::detail::is_implicitly_uses_allocator_constructible<
					Types, Alloc, decltype(hamon::adl_get<Is>(hamon::declval<UTuple>()))
				>...
			>::value;

		static const bool nothrow =
			hamon::conjunction<
				hamon::detail::is_nothrow_uses_allocator_constructible<
					Types, Alloc, decltype(hamon::adl_get<Is>(hamon::declval<UTuple>()))
				>...
			>::value;
	};

	template <typename Alloc, typename UTuple>
	struct AllocUTupleCtorImpl<false, Alloc, UTuple>
	{
		static const bool constructible = false;
		static const bool implicitly = false;
		static const bool nothrow = false;
	};

public:
	template <typename Alloc, HAMON_CONSTRAINED_PARAM(hamon::tuple_like, UTuple)>
	struct AllocUTupleCtor : public AllocUTupleCtorImpl<
		!hamon::detail::is_specialization_of_subrange<hamon::remove_cvref_t<UTuple>>::value &&
		sizeof...(Types) == std::tuple_size<hamon::remove_cvref_t<UTuple>>::value,
		Alloc,
		UTuple
	>{};
};

template <typename... Types>
using tuple_constraint_t =
	tuple_constraint<hamon::make_index_sequence<sizeof...(Types)>, Types...>;

}	// namespace tuple_detail
}	// namespace hamon

#endif // HAMON_TUPLE_DETAIL_TUPLE_CONSTRAINT_HPP
