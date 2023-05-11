/**
 *	@file	pair_constraint.hpp
 *
 *	@brief	pair_constraint の定義
 */

#ifndef HAMON_PAIR_DETAIL_PAIR_CONSTRAINT_HPP
#define HAMON_PAIR_DETAIL_PAIR_CONSTRAINT_HPP

#include <hamon/pair/pair_fwd.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/detail/is_specialization_of_subrange.hpp>
#include <hamon/ranges/detail/different_from.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/tuple/concepts/pair_like.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_implicitly_default_constructible.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <hamon/type_traits/is_nothrow_assignable.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_assignable.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_assignable.hpp>
#include <hamon/type_traits/is_nothrow_swappable.hpp>
#include <hamon/type_traits/is_swappable.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/reference_constructs_from_temporary.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace pair_detail
{

template <typename T1, typename T2>
struct pair_constraint
{
	template <typename>
	struct always_true : public hamon::true_type{};

	template <typename Dummy>
	struct DefaultCtor
	{
		// [pairs.pair]/5
		static const bool constructible =
			hamon::conjunction<
				always_true<Dummy>,
				hamon::is_default_constructible<T1>,
				hamon::is_default_constructible<T2>
			>::value;

		// [pairs.pair]/7
		static const bool implicitly =
			hamon::conjunction<
				always_true<Dummy>,
				hamon::is_implicitly_default_constructible<T1>,
				hamon::is_implicitly_default_constructible<T2>
			>::value;

		// [pairs.pair]/1
		static const bool nothrow =
			hamon::conjunction<
				always_true<Dummy>,
				hamon::is_nothrow_default_constructible<T1>,
				hamon::is_nothrow_default_constructible<T2>
			>::value;
	};

	template <typename Dummy>
	struct ElementCtor
	{
		// [pairs.pair]/8
		static const bool constructible =
			hamon::conjunction<
				always_true<Dummy>,
				hamon::is_copy_constructible<T1>,
				hamon::is_copy_constructible<T2>
			>::value;

		// [pairs.pair]/10
		static const bool implicitly =
			hamon::conjunction<
				always_true<Dummy>,
				hamon::is_convertible<T1 const&, T1>,
				hamon::is_convertible<T2 const&, T2>
			>::value;

		// [pairs.pair]/1
		static const bool nothrow =
			hamon::conjunction<
				always_true<Dummy>,
				hamon::is_nothrow_copy_constructible<T1>,
				hamon::is_nothrow_copy_constructible<T2>
			>::value;
	};

	template <typename U1, typename U2>
	struct UTypesCtor
	{
		// [pairs.pair]/13
#if defined(HAMON_HAS_REFERENCE_CONSTRUCTS_FROM_TEMPORARY)
		static const bool reference_from_temporary =
			hamon::disjunction<
				hamon::reference_constructs_from_temporary<T1, U1&&>,
				hamon::reference_constructs_from_temporary<T2, U2&&>
			>::value;
#else
		static const bool reference_from_temporary = false;
#endif

		// [pairs.pair]/11
		static const bool constructible =
			hamon::conjunction<
				hamon::is_constructible<T1, U1>,		// [pairs.pair]/11.1
				hamon::is_constructible<T2, U2>			// [pairs.pair]/11.2
			>::value
			&& !reference_from_temporary;				// [pairs.pair]/13

		// [pairs.pair]/13
		static const bool implicitly =
			hamon::conjunction<
				hamon::is_convertible<U1, T1>,
				hamon::is_convertible<U2, T2>
			>::value;

		// [pairs.pair]/1
		static const bool nothrow =
			hamon::conjunction<
				hamon::is_nothrow_constructible<T1, U1>,
				hamon::is_nothrow_constructible<T2, U2>
			>::value;
	};

	template <typename UPair>
	struct UPairCtor
	{
		using V1 = decltype(hamon::adl_get<0>(hamon::declval<UPair>()));
		using V2 = decltype(hamon::adl_get<1>(hamon::declval<UPair>()));

		// [pairs.pair]/17
#if defined(HAMON_HAS_REFERENCE_CONSTRUCTS_FROM_TEMPORARY)
		static const bool reference_from_temporary =
			hamon::disjunction<
				hamon::reference_constructs_from_temporary<T1, V1>,
				hamon::reference_constructs_from_temporary<T2, V2>
			>::value;
#else
		static const bool reference_from_temporary = false;
#endif

		// [pairs.pair]/15
		static const bool constructible =
			hamon::conjunction<
				hamon::is_constructible<T1, V1>,	// [pairs.pair]/15.2
				hamon::is_constructible<T2, V2>		// [pairs.pair]/15.3
			>::value
			&& !reference_from_temporary;			// [pairs.pair]/17

		// [pairs.pair]/17
		static const bool implicitly =
			hamon::conjunction<
				hamon::is_convertible<V1, T1>,
				hamon::is_convertible<V2, T2>
			>::value;

		// [pairs.pair]/1
		static const bool nothrow =
			hamon::conjunction<
				hamon::is_nothrow_constructible<T1, V1>,
				hamon::is_nothrow_constructible<T2, V2>
			>::value;
	};
	
	template <HAMON_CONSTRAINED_PARAM(hamon::pair_like, PairLike)>
	struct PairLikeCtor
	{
		// [pairs.pair]/15
		static const bool constructible =
			UPairCtor<PairLike>::constructible &&
			// [pairs.pair]/15.1
			!hamon::detail::is_specialization_of_subrange<
				hamon::remove_cvref_t<PairLike>
			>::value;

		// [pairs.pair]/17
		static const bool implicitly = UPairCtor<PairLike>::implicitly;

		// [pairs.pair]/1
		static const bool nothrow = UPairCtor<PairLike>::nothrow;
	};

	template <typename Dummy>
	struct CopyAssignConst
	{
		// [pairs.pair]/23
		static const bool assignable =
			hamon::conjunction<
				always_true<Dummy>,
				hamon::is_copy_assignable<T1 const>,
				hamon::is_copy_assignable<T2 const>
			>::value;

		// [pairs.pair]/1
		static const bool nothrow =
			hamon::conjunction<
				always_true<Dummy>,
				hamon::is_nothrow_copy_assignable<T1 const>,
				hamon::is_nothrow_copy_assignable<T2 const>
			>::value;
	};

	template <typename Dummy>
	struct MoveAssign
	{
		// [pairs.pair]/32
		static const bool assignable =
			hamon::conjunction<
				always_true<Dummy>,
				hamon::is_move_assignable<T1>,
				hamon::is_move_assignable<T2>
			>::value;

		// [pairs.pair]/35
		static const bool nothrow =
			hamon::conjunction<
				always_true<Dummy>,
				hamon::is_nothrow_move_assignable<T1>,
				hamon::is_nothrow_move_assignable<T2>
			>::value;
	};

	template <typename Dummy>
	struct MoveAssignConst
	{
		// [pairs.pair]/36
		static const bool assignable =
			hamon::conjunction<
				always_true<Dummy>,
				hamon::is_assignable<T1 const&, T1>,
				hamon::is_assignable<T2 const&, T2>
			>::value;

		static const bool nothrow =
			hamon::conjunction<
				always_true<Dummy>,
				hamon::is_nothrow_assignable<T1 const&, T1>,
				hamon::is_nothrow_assignable<T2 const&, T2>
			>::value;
	};

	template <typename U1, typename U2>
	struct UPairCopyAssign
	{
		// [pairs.pair]/26
		static const bool assignable =
			hamon::conjunction<
				hamon::is_assignable<T1&, U1 const&>,
				hamon::is_assignable<T2&, U2 const&>
			>::value;

		// [pairs.pair]/1
		static const bool nothrow =
			hamon::conjunction<
				hamon::is_nothrow_assignable<T1&, U1 const&>,
				hamon::is_nothrow_assignable<T2&, U2 const&>
			>::value;
	};

	template <typename U1, typename U2>
	struct UPairCopyAssignConst
	{
		// [pairs.pair]/29
		static const bool assignable =
			hamon::conjunction<
				hamon::is_assignable<T1 const&, U1 const&>,
				hamon::is_assignable<T2 const&, U2 const&>
			>::value;

		// [pairs.pair]/1
		static const bool nothrow =
			hamon::conjunction<
				hamon::is_nothrow_assignable<T1 const&, U1 const&>,
				hamon::is_nothrow_assignable<T2 const&, U2 const&>
			>::value;
	};

	template <typename U1, typename U2>
	struct UPairMoveAssign
	{
		// [pairs.pair]/39
		static const bool assignable =
			hamon::conjunction<
				hamon::is_assignable<T1&, U1>,
				hamon::is_assignable<T2&, U2>
			>::value;

		static const bool nothrow =
			hamon::conjunction<
				hamon::is_nothrow_assignable<T1&, U1>,
				hamon::is_nothrow_assignable<T2&, U2>
			>::value;
	};

	template <typename U1, typename U2>
	struct UPairMoveAssignConst
	{
		// [pairs.pair]/48
		static const bool assignable =
			hamon::conjunction<
				hamon::is_assignable<T1 const&, U1>,
				hamon::is_assignable<T2 const&, U2>
			>::value;

		static const bool nothrow =
			hamon::conjunction<
				hamon::is_nothrow_assignable<T1 const&, U1>,
				hamon::is_nothrow_assignable<T2 const&, U2>
			>::value;
	};

	template <HAMON_CONSTRAINED_PARAM(hamon::pair_like, PairLike)>
	struct PairLikeAssign
	{
		using U1 = decltype(hamon::adl_get<0>(hamon::declval<PairLike>()));
		using U2 = decltype(hamon::adl_get<1>(hamon::declval<PairLike>()));

		static const bool assignable =
			hamon::conjunction<
				hamon::ranges::detail::different_from_t<PairLike, hamon::pair<T1, T2>>,	// [pairs.pair]/42.1
				hamon::negation<											// [pairs.pair]/42.2
					hamon::detail::is_specialization_of_subrange<hamon::remove_cvref_t<PairLike>>>,
				hamon::is_assignable<T1&, U1>,								// [pairs.pair]/42.3
				hamon::is_assignable<T2&, U2>								// [pairs.pair]/42.4
			>::value;

		static const bool nothrow =
			hamon::conjunction<
				hamon::is_nothrow_assignable<T1&, U1>,
				hamon::is_nothrow_assignable<T2&, U2>
			>::value;
	};

	template <HAMON_CONSTRAINED_PARAM(hamon::pair_like, PairLike)>
	struct PairLikeAssignConst
	{
		using U1 = decltype(hamon::adl_get<0>(hamon::declval<PairLike>()));
		using U2 = decltype(hamon::adl_get<1>(hamon::declval<PairLike>()));

		static const bool assignable =
			hamon::conjunction<
				hamon::ranges::detail::different_from_t<PairLike, hamon::pair<T1, T2>>,	// [pairs.pair]/45.1
				hamon::negation<									// [pairs.pair]/45.2
					hamon::detail::is_specialization_of_subrange<hamon::remove_cvref_t<PairLike>>>,
				hamon::is_assignable<T1 const&, U1>,				// [pairs.pair]/45.3
				hamon::is_assignable<T2 const&, U2>					// [pairs.pair]/45.4
			>::value;

		static const bool nothrow =
			hamon::conjunction<
				hamon::is_nothrow_assignable<T1 const&, U1>,
				hamon::is_nothrow_assignable<T2 const&, U2>
			>::value;
	};

	template <typename Dummy>
	struct Swap
	{
		// [pairs.pair]/51.1
		static const bool swappable =
			hamon::conjunction<
				always_true<Dummy>,
				hamon::is_swappable<T1>,
				hamon::is_swappable<T2>
			>::value;

		// [pairs.pair]/54.1
		static const bool nothrow =
			hamon::conjunction<
				always_true<Dummy>,
				hamon::is_nothrow_swappable<T1>,
				hamon::is_nothrow_swappable<T2>
			>::value;
	};

	template <typename Dummy>
	struct SwapConst
	{
		// [pairs.pair]/51.2
		static const bool swappable =
			hamon::conjunction<
				always_true<Dummy>,
				hamon::is_swappable<T1 const>,
				hamon::is_swappable<T2 const>
			>::value;

		// [pairs.pair]/54.2
		static const bool nothrow =
			hamon::conjunction<
				always_true<Dummy>,
				hamon::is_nothrow_swappable<T1 const>,
				hamon::is_nothrow_swappable<T2 const>
			>::value;
	};
};

}	// namespace pair_detail

}	// namespace hamon

#endif // HAMON_PAIR_DETAIL_PAIR_CONSTRAINT_HPP
