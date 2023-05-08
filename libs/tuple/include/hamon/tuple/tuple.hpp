/**
 *	@file	tuple.hpp
 *
 *	@brief	tuple クラステンプレートの定義
 */

#ifndef HAMON_TUPLE_TUPLE_HPP
#define HAMON_TUPLE_TUPLE_HPP

#include <hamon/tuple/config.hpp>

#if defined(HAMON_USE_STD_TUPLE)

namespace hamon
{

using std::tuple;

}	// namespace hamon

#else

#include <hamon/tuple/tuple_fwd.hpp>
#include <hamon/tuple/tuple_element.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/tuple/concepts/tuple_like.hpp>
#include <hamon/compare/common_comparison_category.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/compare/detail/synth3way.hpp>
#include <hamon/concepts/detail/is_specialization_of_subrange.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/memory/allocator_arg_t.hpp>
#include <hamon/memory/detail/uses_allocator_construction_type.hpp>
#include <hamon/memory/detail/is_uses_allocator_constructible.hpp>
#include <hamon/memory/detail/is_implicitly_uses_allocator_constructible.hpp>
#include <hamon/memory/detail/is_nothrow_uses_allocator_constructible.hpp>
#include <hamon/pair/pair.hpp>
#include <hamon/ranges/detail/different_from.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_assignable.hpp>
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
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_swappable.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/nth.hpp>
#include <hamon/type_traits/reference_constructs_from_temporary.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/unwrap_ref_decay.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/utility/index_sequence_for.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace tuple_detail
{

struct ctor_from_elems_tag {};
struct ctor_from_tuple_tag {};

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)
HAMON_WARNING_DISABLE_CLANG("-Wimplicit-int-conversion")
HAMON_WARNING_DISABLE_CLANG("-Wimplicit-float-conversion")
HAMON_WARNING_DISABLE_CLANG("-Wimplicit-int-float-conversion")
HAMON_WARNING_DISABLE_GCC("-Wconversion")
HAMON_WARNING_DISABLE_GCC("-Wfloat-conversion")

template <hamon::size_t I, typename T>
struct tuple_leaf
{
private:
	T	m_value;

public:
	HAMON_CXX11_CONSTEXPR
	tuple_leaf()
		: m_value() {}

	template <typename U,
		typename = hamon::enable_if_t<
			hamon::is_constructible<T, U>::value>>
	HAMON_CXX11_CONSTEXPR
	tuple_leaf(U&& u)
		: m_value(hamon::forward<U>(u)) {}

	template <typename Alloc, typename... Args>
	HAMON_CXX11_CONSTEXPR
	tuple_leaf(hamon::allocator_arg_t, Alloc const& alloc, Args&&... args)
		: tuple_leaf(
			hamon::detail::uses_allocator_construction_type_t<T, Alloc, Args...>{},
			alloc,
			hamon::forward<Args>(args)...)
	{}

private:
	template <typename Alloc, typename... Args>
	HAMON_CXX11_CONSTEXPR
	tuple_leaf(hamon::detail::uses_allocator_construction_type::NoAlloc, Alloc const&, Args&&... args) noexcept
		: m_value(hamon::forward<Args>(args)...) {}

	template <typename Alloc, typename... Args>
	HAMON_CXX11_CONSTEXPR
	tuple_leaf(hamon::detail::uses_allocator_construction_type::FirstAlloc, Alloc const& alloc, Args&&... args) noexcept
		: m_value(hamon::allocator_arg_t{}, alloc, hamon::forward<Args>(args)...) {}

	template <typename Alloc, typename... Args>
	HAMON_CXX11_CONSTEXPR
	tuple_leaf(hamon::detail::uses_allocator_construction_type::LastAlloc, Alloc const& alloc, Args&&... args) noexcept
		: m_value(hamon::forward<Args>(args)..., alloc) {}

public:
	HAMON_CXX14_CONSTEXPR T &       get() &       { return m_value; }
	HAMON_CXX11_CONSTEXPR T const&  get() const&  { return m_value; }
	HAMON_CXX14_CONSTEXPR T &&      get() &&      { return hamon::forward<T>(m_value); }
	HAMON_CXX11_CONSTEXPR T const&& get() const&& { return hamon::forward<T const>(m_value); }
};

template <typename IndexSequence, typename... Types>
struct tuple_impl;

template <hamon::size_t... Is, typename... Types>
struct tuple_impl<hamon::index_sequence<Is...>, Types...>
	: tuple_leaf<Is, Types>...
{
	HAMON_CXX11_CONSTEXPR
	tuple_impl()
	{}

	template <typename... UTypes>
	HAMON_CXX11_CONSTEXPR
	tuple_impl(ctor_from_elems_tag, UTypes&&... args)
		: tuple_leaf<Is, Types>(hamon::forward<UTypes>(args))...
	{}

	template <typename UTuple>
	HAMON_CXX11_CONSTEXPR
	tuple_impl(ctor_from_tuple_tag, UTuple&& u)
		: tuple_leaf<Is, Types>(hamon::adl_get<Is>(hamon::forward<UTuple>(u)))...
	{}

	template <typename Alloc>
	HAMON_CXX11_CONSTEXPR
	tuple_impl(hamon::allocator_arg_t, Alloc const& a)
		: tuple_leaf<Is, Types>(hamon::allocator_arg_t{}, a)...
	{}

	template <typename Alloc, typename... UTypes>
	HAMON_CXX11_CONSTEXPR
	tuple_impl(hamon::allocator_arg_t, Alloc const& a, ctor_from_elems_tag, UTypes&&... args)
		: tuple_leaf<Is, Types>(hamon::allocator_arg_t{}, a, hamon::forward<UTypes>(args))...
	{}

	template <typename Alloc, typename UTuple>
	HAMON_CXX11_CONSTEXPR
	tuple_impl(hamon::allocator_arg_t, Alloc const& a, ctor_from_tuple_tag, UTuple&& u)
		: tuple_leaf<Is, Types>(hamon::allocator_arg_t{}, a, hamon::adl_get<Is>(hamon::forward<UTuple>(u)))...
	{}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR
	static void swallow(Args&&...) HAMON_NOEXCEPT {}

	template <typename TTuple, typename... UTypes>
	HAMON_CXX14_CONSTEXPR
	static void assign(TTuple& lhs, tuple<UTypes...> const& rhs)
	{
		swallow(((hamon::adl_get<Is>(lhs) = hamon::adl_get<Is>(rhs)), 0)...);
	}

	template <typename TTuple, typename... UTypes>
	HAMON_CXX14_CONSTEXPR
	static void assign(TTuple& lhs, tuple<UTypes...>&& rhs)
	{
		swallow(((hamon::adl_get<Is>(lhs) = hamon::forward<UTypes>(hamon::adl_get<Is>(rhs))), 0)...);
	}

	template <typename TTuple, typename U1, typename U2>
	HAMON_CXX14_CONSTEXPR
	static void assign(TTuple& lhs, pair<U1, U2> const& rhs)
	{
		hamon::adl_get<0>(lhs) = rhs.first;
		hamon::adl_get<1>(lhs) = rhs.second;
	}

	template <typename TTuple, typename U1, typename U2>
	HAMON_CXX14_CONSTEXPR
	static void assign(TTuple& lhs, pair<U1, U2>&& rhs)
	{
		hamon::adl_get<0>(lhs) = hamon::forward<U1>(rhs.first);
		hamon::adl_get<1>(lhs) = hamon::forward<U2>(rhs.second);
	}
	
	template <typename TTuple, typename UTuple>
	HAMON_CXX14_CONSTEXPR
	static void assign(TTuple& lhs, UTuple&& rhs)
	{
		swallow(((hamon::adl_get<Is>(lhs) = hamon::adl_get<Is>(hamon::forward<UTuple>(rhs))), 0)...);
	}

	template <typename TTuple, typename UTuple>
	HAMON_CXX14_CONSTEXPR
	static void swap(TTuple& lhs, UTuple& rhs)
	{
		using std::swap;
		swallow((swap(hamon::adl_get<Is>(lhs), hamon::adl_get<Is>(rhs)), 0)...);
	}
};

HAMON_WARNING_POP()

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
		// [tuple.cnstr]/15
#if defined(HAMON_HAS_REFERENCE_CONSTRUCTS_FROM_TEMPORARY)
		static const bool reference_from_temporary =
			hamon::disjunction<
				hamon::reference_constructs_from_temporary<Types, UTypes&&>...
			>::value;
#else
		static const bool reference_from_temporary = false;
#endif

		// [tuple.cnstr]/13
		static const bool constructible =
			hamon::conjunction<
				disambiguating_constraint<					// [tuple.cnstr]/13.3
					hamon::nth_t<0, Types...>,
					hamon::nth_t<0, UTypes...>,
					sizeof...(Types)
				>,
				hamon::is_constructible<Types, UTypes>...	// [tuple.cnstr]/13.3
			>::value
			&& !reference_from_temporary;					// [tuple.cnstr]/15

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
		// [tuple.cnstr]/23
#if defined(HAMON_HAS_REFERENCE_CONSTRUCTS_FROM_TEMPORARY)
		static const bool reference_from_temporary =
			hamon::disjunction<
				hamon::reference_constructs_from_temporary<
					Types, decltype(hamon::adl_get<Is>(hamon::declval<UTuple>()))
				>...
			>::value;
#else
		static const bool reference_from_temporary = false;
#endif

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
			>::value
			&& !reference_from_temporary;	// [tuple.cnstr]/23

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
		// [tuple.cnstr]/27
#if defined(HAMON_HAS_REFERENCE_CONSTRUCTS_FROM_TEMPORARY)
		static const bool reference_from_temporary =
			hamon::disjunction<
				hamon::reference_constructs_from_temporary<T0, U0>,
				hamon::reference_constructs_from_temporary<T1, U1>
			>::value;
#else
		static const bool reference_from_temporary = false;
#endif

		// [tuple.cnstr]/25
		static const bool constructible =
			hamon::conjunction<
				hamon::is_constructible<T0, U0>,	// [tuple.cnstr]/25.2
				hamon::is_constructible<T1, U1>		// [tuple.cnstr]/25.3
			>::value
			&& !reference_from_temporary;			// [tuple.cnstr]/27

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

struct access;

}	// namespace tuple_detail

// Class template tuple	[tuple.tuple]
template <typename... Types>
class tuple
{
private:
	using impl_type = tuple_detail::tuple_impl<
		hamon::make_index_sequence<sizeof...(Types)>,
		Types...
	>;

	using constraint_type = tuple_detail::tuple_constraint<
		hamon::make_index_sequence<sizeof...(Types)>,
		Types...
	>;

	impl_type	m_impl;

	friend struct tuple_detail::access;

private:
	template <typename>
	struct always_true : public hamon::true_type{};

	template <typename Dummy>
	using DefaultCtor = typename constraint_type::template DefaultCtor<Dummy>;

	template <typename Dummy>
	using ElementCtor = typename constraint_type::template ElementCtor<Dummy>;

	template <typename... UTypes>
	using UTypesCtor = typename constraint_type::template UTypesCtor<UTypes...>;

	template <typename UTuple, typename... UTypes>
	using UTupleCtor = typename constraint_type::template UTupleCtor<UTuple, UTypes...>;

	template <typename UTuple>
	using TupleLikeCtor = typename constraint_type::template TupleLikeCtor<UTuple>;

	template <typename Pair>
	using PairCtor = typename constraint_type::template PairCtor<Pair>;

	template <typename UTuple>
	using TupleLikeAssign = typename constraint_type::template TupleLikeAssign<UTuple>;

	template <typename UTuple>
	using TupleLikeAssignConst = typename constraint_type::template TupleLikeAssignConst<UTuple>;

	template <typename Alloc>
	using AllocDefaultCtor = typename constraint_type::template AllocDefaultCtor<Alloc>;

	template <typename Alloc, typename... UTypes>
	using AllocUTypesCtor = typename constraint_type::template AllocUTypesCtor<Alloc, UTypes...>;

	template <typename Alloc, typename UTuple>
	using AllocUTupleCtor = typename constraint_type::template AllocUTupleCtor<Alloc, UTuple>;

	struct nat;

public:
	// [tuple.cnstr], tuple construction

	tuple(tuple const&) = default;

	tuple(tuple&&) = default;

#if defined(HAMON_HAS_CXX20_CONDITIONAL_EXPLICIT)

	// tuple()
	template <typename Dummy = void,
		hamon::enable_if_t<DefaultCtor<Dummy>::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!DefaultCtor<Dummy>::implicitly)
	tuple()
	HAMON_NOEXCEPT_IF((DefaultCtor<Dummy>::nothrow))
		: m_impl()
	{}

	// tuple(Types const&... args)
	template <typename Dummy = void,
		hamon::enable_if_t<ElementCtor<Dummy>::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!ElementCtor<Dummy>::implicitly)
	tuple(Types const&... args)
	HAMON_NOEXCEPT_IF((ElementCtor<Dummy>::nothrow))
		: m_impl(tuple_detail::ctor_from_elems_tag{}, args...)
	{}

	// tuple(UTypes&&... args)
	template <typename... UTypes,
		hamon::enable_if_t<UTypesCtor<UTypes...>::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!UTypesCtor<UTypes...>::implicitly)
	tuple(UTypes&&... args)
	HAMON_NOEXCEPT_IF((UTypesCtor<UTypes...>::nothrow))
		: m_impl(tuple_detail::ctor_from_elems_tag{}, hamon::forward<UTypes>(args)...)
	{}

	// tuple(tuple<UTypes...>& u)
	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...>&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(tuple<UTypes...>& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	// tuple(tuple<UTypes...> const& u)
	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...> const&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(tuple<UTypes...> const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	// tuple(tuple<UTypes...>&& u)
	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...>&&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(tuple<UTypes...>&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	// tuple(tuple<UTypes...> const&& u)
	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...> const&&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(tuple<UTypes...> const&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	// tuple(pair<U1, U2>& u)
	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2>&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(pair<U1, U2>& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	// tuple(pair<U1, U2> const& u)
	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2> const&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(pair<U1, U2> const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	// tuple(pair<U1, U2>&& u)
	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2>&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(pair<U1, U2>&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	// tuple(pair<U1, U2> const&& u)
	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2> const&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(pair<U1, U2> const&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	// tuple(UTuple&& u)
	template <typename UTuple,
		hamon::enable_if_t<hamon::tuple_like_t<UTuple>::value>* = nullptr,
		typename Constraint = TupleLikeCtor<UTuple>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(UTuple&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::forward<UTuple>(u))
	{}

	// allocator-extended constructors

	// tuple(allocator_arg_t, Alloc const& a)
	template <typename Alloc,
		typename Constraint = AllocDefaultCtor<Alloc>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(hamon::allocator_arg_t, Alloc const& a)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a)
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, Types const&... args);
	template <typename Alloc,
		typename Constraint = AllocUTypesCtor<Alloc, Types const&...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(hamon::allocator_arg_t, Alloc const& a, Types const&... args)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_elems_tag{}, args...)
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, UTypes&&... args);
	template <typename Alloc, typename... UTypes,
		typename Constraint = AllocUTypesCtor<Alloc, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(hamon::allocator_arg_t, Alloc const& a, UTypes&&... args)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_elems_tag{}, hamon::forward<UTypes>(args)...)
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, tuple const& u)
	template <typename Alloc,
		typename Constraint = AllocUTupleCtor<Alloc, tuple const&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, tuple const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, tuple&& u)
	template <typename Alloc,
		typename Constraint = AllocUTupleCtor<Alloc, tuple&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, tuple&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, tuple<UTypes...>& u)
	template <typename Alloc, typename... UTypes,
		typename Constraint = AllocUTupleCtor<Alloc, tuple<UTypes...>&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(hamon::allocator_arg_t, Alloc const& a, tuple<UTypes...>& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, tuple<UTypes...> const& u)
	template <typename Alloc, typename... UTypes,
		typename Constraint = AllocUTupleCtor<Alloc, tuple<UTypes...> const&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(hamon::allocator_arg_t, Alloc const& a, tuple<UTypes...> const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, tuple<UTypes...>&& u)
	template <typename Alloc, typename... UTypes,
		typename Constraint = AllocUTupleCtor<Alloc, tuple<UTypes...>&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(hamon::allocator_arg_t, Alloc const& a, tuple<UTypes...>&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, tuple<UTypes...> const&& u)
	template <typename Alloc, typename... UTypes,
		typename Constraint = AllocUTupleCtor<Alloc, tuple<UTypes...> const&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(hamon::allocator_arg_t, Alloc const& a, tuple<UTypes...> const&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, pair<U1, U2>& u)
	template <typename Alloc, typename U1, typename U2,
		typename Constraint = AllocUTupleCtor<Alloc, pair<U1, U2>&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(hamon::allocator_arg_t, Alloc const& a, pair<U1, U2>& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, pair<U1, U2> const& u)
	template <typename Alloc, typename U1, typename U2,
		typename Constraint = AllocUTupleCtor<Alloc, pair<U1, U2> const&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(hamon::allocator_arg_t, Alloc const& a, pair<U1, U2> const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, pair<U1, U2>&& u)
	template <typename Alloc, typename U1, typename U2,
		typename Constraint = AllocUTupleCtor<Alloc, pair<U1, U2>&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(hamon::allocator_arg_t, Alloc const& a, pair<U1, U2>&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, pair<U1, U2> const&& u)
	template <typename Alloc, typename U1, typename U2,
		typename Constraint = AllocUTupleCtor<Alloc, pair<U1, U2> const&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(hamon::allocator_arg_t, Alloc const& a, pair<U1, U2> const&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, UTuple&& u)
	template <typename Alloc, typename UTuple,
		hamon::enable_if_t<hamon::tuple_like_t<UTuple>::value>* = nullptr,
		typename Constraint = AllocUTupleCtor<Alloc, UTuple>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(hamon::allocator_arg_t, Alloc const& a, UTuple&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, hamon::forward<UTuple>(u))
	{}

#else

	// tuple()
	template <typename Dummy = void,
		hamon::enable_if_t<DefaultCtor<Dummy>::constructible>* = nullptr,
		hamon::enable_if_t<!DefaultCtor<Dummy>::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple()
	HAMON_NOEXCEPT_IF((DefaultCtor<Dummy>::nothrow))
	{}

	template <typename Dummy = void,
		hamon::enable_if_t<DefaultCtor<Dummy>::constructible>* = nullptr,
		hamon::enable_if_t<DefaultCtor<Dummy>::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple()
	HAMON_NOEXCEPT_IF((DefaultCtor<Dummy>::nothrow))
	{}

	// tuple(Types const&... args)
	template <typename Dummy = void,
		hamon::enable_if_t<ElementCtor<Dummy>::constructible>* = nullptr,
		hamon::enable_if_t<!ElementCtor<Dummy>::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(Types const&... args)
	HAMON_NOEXCEPT_IF((ElementCtor<Dummy>::nothrow))
		: m_impl(tuple_detail::ctor_from_elems_tag{}, args...)
	{}

	template <typename Dummy = void,
		hamon::enable_if_t<ElementCtor<Dummy>::constructible>* = nullptr,
		hamon::enable_if_t<ElementCtor<Dummy>::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(Types const&... args)
	HAMON_NOEXCEPT_IF((ElementCtor<Dummy>::nothrow))
		: m_impl(tuple_detail::ctor_from_elems_tag{}, args...)
	{}

	// tuple(UTypes&&... args)
	template <typename... UTypes,
		hamon::enable_if_t<UTypesCtor<UTypes...>::constructible>* = nullptr,
		hamon::enable_if_t<!UTypesCtor<UTypes...>::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(UTypes&&... args)
	HAMON_NOEXCEPT_IF((UTypesCtor<UTypes...>::nothrow))
		: m_impl(tuple_detail::ctor_from_elems_tag{}, hamon::forward<UTypes>(args)...)
	{}

	template <typename... UTypes,
		hamon::enable_if_t<UTypesCtor<UTypes...>::constructible>* = nullptr,
		hamon::enable_if_t<UTypesCtor<UTypes...>::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(UTypes&&... args)
	HAMON_NOEXCEPT_IF((UTypesCtor<UTypes...>::nothrow))
		: m_impl(tuple_detail::ctor_from_elems_tag{}, hamon::forward<UTypes>(args)...)
	{}

	// tuple(tuple<UTypes...>& u)
	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...>&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...>& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...>&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...>& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	// tuple(tuple<UTypes...> const& u)
	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...> const&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...> const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...> const&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...> const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	// tuple(tuple<UTypes...>&& u)
	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...>&&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...>&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...>&&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...>&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	// tuple(tuple<UTypes...> const&& u)
	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...> const&&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...> const&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...> const&&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...> const&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	// tuple(pair<U1, U2>& u)
	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2>&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2>& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2>&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2>& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	// tuple(pair<U1, U2> const& u)
	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2> const&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2> const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2> const&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2> const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	// tuple(pair<U1, U2>&& u)
	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2>&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2>&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2>&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2>&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	// tuple(pair<U1, U2> const&& u)
	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2> const&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2> const&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2> const&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2> const&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	// 	tuple(UTuple&& u)
	template <typename UTuple,
		hamon::enable_if_t<hamon::tuple_like_t<UTuple>::value>* = nullptr,
		typename Constraint = TupleLikeCtor<UTuple>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(UTuple&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::forward<UTuple>(u))
	{}

	template <typename UTuple,
		hamon::enable_if_t<hamon::tuple_like_t<UTuple>::value>* = nullptr,
		typename Constraint = TupleLikeCtor<UTuple>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(UTuple&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::forward<UTuple>(u))
	{}
	
	// allocator-extended constructors

	// tuple(allocator_arg_t, Alloc const& a)
	template <typename Alloc,
		typename Constraint = AllocDefaultCtor<Alloc>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a)
	{}

	template <typename Alloc,
		typename Constraint = AllocDefaultCtor<Alloc>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a)
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, Types const&... args);
	template <typename Alloc,
		typename Constraint = AllocUTypesCtor<Alloc, Types const&...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, Types const&... args)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_elems_tag{}, args...)
	{}

	template <typename Alloc,
		typename Constraint = AllocUTypesCtor<Alloc, Types const&...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, Types const&... args)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_elems_tag{}, args...)
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, UTypes&&... args);
	template <typename Alloc, typename... UTypes,
		typename Constraint = AllocUTypesCtor<Alloc, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, UTypes&&... args)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_elems_tag{}, hamon::forward<UTypes>(args)...)
	{}

	template <typename Alloc, typename... UTypes,
		typename Constraint = AllocUTypesCtor<Alloc, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, UTypes&&... args)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_elems_tag{}, hamon::forward<UTypes>(args)...)
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, tuple const& u)
	template <typename Alloc,
		typename Constraint = AllocUTupleCtor<Alloc, tuple const&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, tuple const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, tuple&& u)
	template <typename Alloc,
		typename Constraint = AllocUTupleCtor<Alloc, tuple&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, tuple&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, tuple<UTypes...>& u)
	template <typename Alloc, typename... UTypes,
		typename Constraint = AllocUTupleCtor<Alloc, tuple<UTypes...>&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, tuple<UTypes...>& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	template <typename Alloc, typename... UTypes,
		typename Constraint = AllocUTupleCtor<Alloc, tuple<UTypes...>&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, tuple<UTypes...>& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, tuple<UTypes...> const& u)
	template <typename Alloc, typename... UTypes,
		typename Constraint = AllocUTupleCtor<Alloc, tuple<UTypes...> const&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, tuple<UTypes...> const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	template <typename Alloc, typename... UTypes,
		typename Constraint = AllocUTupleCtor<Alloc, tuple<UTypes...> const&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, tuple<UTypes...> const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, tuple<UTypes...>&& u)
	template <typename Alloc, typename... UTypes,
		typename Constraint = AllocUTupleCtor<Alloc, tuple<UTypes...>&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, tuple<UTypes...>&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	template <typename Alloc, typename... UTypes,
		typename Constraint = AllocUTupleCtor<Alloc, tuple<UTypes...>&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, tuple<UTypes...>&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, tuple<UTypes...> const&& u)
	template <typename Alloc, typename... UTypes,
		typename Constraint = AllocUTupleCtor<Alloc, tuple<UTypes...> const&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, tuple<UTypes...> const&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	template <typename Alloc, typename... UTypes,
		typename Constraint = AllocUTupleCtor<Alloc, tuple<UTypes...> const&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, tuple<UTypes...> const&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, pair<U1, U2>& u)
	template <typename Alloc, typename U1, typename U2,
		typename Constraint = AllocUTupleCtor<Alloc, pair<U1, U2>&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, pair<U1, U2>& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	template <typename Alloc, typename U1, typename U2,
		typename Constraint = AllocUTupleCtor<Alloc, pair<U1, U2>&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, pair<U1, U2>& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, pair<U1, U2> const& u)
	template <typename Alloc, typename U1, typename U2,
		typename Constraint = AllocUTupleCtor<Alloc, pair<U1, U2> const&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, pair<U1, U2> const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	template <typename Alloc, typename U1, typename U2,
		typename Constraint = AllocUTupleCtor<Alloc, pair<U1, U2> const&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, pair<U1, U2> const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, pair<U1, U2>&& u)
	template <typename Alloc, typename U1, typename U2,
		typename Constraint = AllocUTupleCtor<Alloc, pair<U1, U2>&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, pair<U1, U2>&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	template <typename Alloc, typename U1, typename U2,
		typename Constraint = AllocUTupleCtor<Alloc, pair<U1, U2>&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, pair<U1, U2>&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, pair<U1, U2> const&& u)
	template <typename Alloc, typename U1, typename U2,
		typename Constraint = AllocUTupleCtor<Alloc, pair<U1, U2> const&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, pair<U1, U2> const&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	template <typename Alloc, typename U1, typename U2,
		typename Constraint = AllocUTupleCtor<Alloc, pair<U1, U2> const&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, pair<U1, U2> const&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	// tuple(hamon::allocator_arg_t, Alloc const& a, UTuple&& u)
	template <typename Alloc, typename UTuple,
		hamon::enable_if_t<hamon::tuple_like_t<UTuple>::value>* = nullptr,
		typename Constraint = AllocUTupleCtor<Alloc, UTuple>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, UTuple&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, hamon::forward<UTuple>(u))
	{}

	template <typename Alloc, typename UTuple,
		hamon::enable_if_t<hamon::tuple_like_t<UTuple>::value>* = nullptr,
		typename Constraint = AllocUTupleCtor<Alloc, UTuple>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const& a, UTuple&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::allocator_arg_t{}, a, tuple_detail::ctor_from_tuple_tag{}, hamon::forward<UTuple>(u))
	{}

#endif

	// [tuple.assign], tuple assignment

	// operator=(tuple const& u)
	HAMON_CXX14_CONSTEXPR tuple&
	operator=(
		hamon::conditional_t<
			hamon::conjunction<					// [tuple.assign]/4
				hamon::is_copy_assignable<Types>...
			>::value,
			tuple,
			nat
		> const& u)
	HAMON_NOEXCEPT_IF((hamon::conjunction<
		hamon::is_nothrow_copy_assignable<Types>...
	>::value))
	{
		impl_type::assign(*this, u);		// [tuple.assign]/2
		return *this;						// [tuple.assign]/3
	}

	// operator=(tuple const& u) const
	template <typename Dummy = void,
		hamon::enable_if_t<hamon::conjunction<	// [tuple.assign]/5
			always_true<Dummy>,
			hamon::is_copy_assignable<Types const>...
		>::value>* = nullptr>
	HAMON_CXX14_CONSTEXPR tuple const&
	operator=(tuple const& u) const
	HAMON_NOEXCEPT_IF((hamon::conjunction<
		hamon::is_nothrow_copy_assignable<Types const>...
	>::value))
	{
		impl_type::assign(*this, u);		// [tuple.assign]/6
		return *this;						// [tuple.assign]/7
	}

	// operator=(tuple&& u)
	template <typename Dummy = void,
		hamon::enable_if_t<hamon::conjunction<	// [tuple.assign]/8
			always_true<Dummy>,
			hamon::is_move_assignable<Types>...
		>::value>* = nullptr>
	HAMON_CXX14_CONSTEXPR tuple&
	operator=(tuple&& u)
	HAMON_NOEXCEPT_IF((hamon::conjunction<		// [tuple.assign]/11
		hamon::is_nothrow_move_assignable<Types>...
	>::value))
	{
		impl_type::assign(*this, hamon::move(u));	// [tuple.assign]/9
		return *this;								// [tuple.assign]/10
	}

	// operator=(tuple&& u) const
	template <typename Dummy = void,
		hamon::enable_if_t<hamon::conjunction<	// [tuple.assign]/12
			always_true<Dummy>,
			hamon::is_assignable<Types const&, Types>...
		>::value>* = nullptr>
	HAMON_CXX14_CONSTEXPR tuple
	const& operator=(tuple&& u) const
	HAMON_NOEXCEPT_IF((hamon::conjunction<
		hamon::is_nothrow_assignable<Types const&, Types>...
	>::value))
	{
		impl_type::assign(*this, hamon::move(u));	// [tuple.assign]/13
		return *this;								// [tuple.assign]/14
	}

	// operator=(tuple<UTypes...> const& u)
	template <typename... UTypes,
		hamon::enable_if_t<hamon::conjunction<
			hamon::bool_constant<sizeof...(Types) == sizeof...(UTypes)>,// [tuple.assign]/15.1
			hamon::is_assignable<Types&, UTypes const&>...				// [tuple.assign]/15.2
		>::value>* = nullptr
	>
	HAMON_CXX14_CONSTEXPR tuple&
	operator=(tuple<UTypes...> const& u)
	HAMON_NOEXCEPT_IF((hamon::conjunction<
		hamon::is_nothrow_assignable<Types&, UTypes const&>...
	>::value))
	{
		impl_type::assign(*this, u);		// [tuple.assign]/16
		return *this;						// [tuple.assign]/17
	}

	// operator=(tuple<UTypes...> const& u) const
	template <typename... UTypes,
		hamon::enable_if_t<						// [tuple.assign]/18.1
			sizeof...(Types) == sizeof...(UTypes)>* = nullptr,
		hamon::enable_if_t<hamon::conjunction<	// [tuple.assign]/18.2
			hamon::is_assignable<Types const&, UTypes const&>...
		>::value>* = nullptr
	>
	HAMON_CXX14_CONSTEXPR tuple const&
	operator=(tuple<UTypes...> const& u) const
	HAMON_NOEXCEPT_IF((hamon::conjunction<
		hamon::is_nothrow_assignable<Types const&, UTypes const&>...
	>::value))
	{
		impl_type::assign(*this, u);		// [tuple.assign]/19
		return *this;						// [tuple.assign]/20
	}

	// operator=(tuple<UTypes...>&& u)
	template <typename... UTypes,
		hamon::enable_if_t<						// [tuple.assign]/21.1
			sizeof...(Types) == sizeof...(UTypes)>* = nullptr,
		hamon::enable_if_t<hamon::conjunction<	// [tuple.assign]/21.2
			hamon::is_assignable<Types&, UTypes>...
		>::value>* = nullptr
	>
	HAMON_CXX14_CONSTEXPR tuple&
	operator=(tuple<UTypes...>&& u)
	HAMON_NOEXCEPT_IF((hamon::conjunction<
		hamon::is_nothrow_assignable<Types&, UTypes>...
	>::value))
	{
		impl_type::assign(*this, hamon::move(u));	// [tuple.assign]/22
		return *this;								// [tuple.assign]/23
	}

	// operator=(tuple<UTypes...>&& u) const
	template <typename... UTypes,
		hamon::enable_if_t<						// [tuple.assign]/24.1
			sizeof...(Types) == sizeof...(UTypes)>* = nullptr,
		hamon::enable_if_t<hamon::conjunction<	// [tuple.assign]/24.2
			hamon::is_assignable<Types const&, UTypes>...
		>::value>* = nullptr
	>
	HAMON_CXX14_CONSTEXPR tuple const&
	operator=(tuple<UTypes...>&& u) const
	HAMON_NOEXCEPT_IF((hamon::conjunction<
		hamon::is_nothrow_assignable<Types const&, UTypes>...
	>::value))
	{
		impl_type::assign(*this, hamon::move(u));	// [tuple.assign]/25
		return *this;								// [tuple.assign]/26
	}

	// operator=(pair<U1, U2> const& u)
	template <typename U1, typename U2,
		typename T0 = hamon::nth<0, Types...>,
		typename T1 = hamon::nth<1, Types...>,
		hamon::enable_if_t<hamon::conjunction<
			hamon::bool_constant<sizeof...(Types) == 2>,		// [tuple.assign]/27.1
			hamon::is_assignable<typename T0::type&, U1 const&>,// [tuple.assign]/27.2
			hamon::is_assignable<typename T1::type&, U2 const&>	// [tuple.assign]/27.3
		>::value>* = nullptr
	>
	HAMON_CXX14_CONSTEXPR tuple&
	operator=(pair<U1, U2> const& u)
	HAMON_NOEXCEPT_IF((hamon::conjunction<
		hamon::is_nothrow_assignable<typename T0::type&, U1 const&>,
		hamon::is_nothrow_assignable<typename T1::type&, U2 const&>
	>::value))
	{
		impl_type::assign(*this, u);		// [tuple.assign]/28
		return *this;						// [tuple.assign]/29
	}

	// operator=(pair<U1, U2> const&) const
	template <typename U1, typename U2,
		typename T0 = hamon::nth<0, Types...>,
		typename T1 = hamon::nth<1, Types...>,
		hamon::enable_if_t<hamon::conjunction<
			hamon::bool_constant<sizeof...(Types) == 2>,				// [tuple.assign]/30.1
			hamon::is_assignable<typename T0::type const&, U1 const&>,	// [tuple.assign]/30.2
			hamon::is_assignable<typename T1::type const&, U2 const&>	// [tuple.assign]/30.3
		>::value>* = nullptr
	>
	HAMON_CXX14_CONSTEXPR tuple const&
	operator=(pair<U1, U2> const& u) const
	HAMON_NOEXCEPT_IF((hamon::conjunction<
		hamon::is_nothrow_assignable<typename T0::type const&, U1 const&>,
		hamon::is_nothrow_assignable<typename T1::type const&, U2 const&>
	>::value))
	{
		impl_type::assign(*this, u);		// [tuple.assign]/31
		return *this;						// [tuple.assign]/32
	}

	// operator=(pair<U1, U2>&&)
	template <typename U1, typename U2,
		typename T0 = hamon::nth<0, Types...>,
		typename T1 = hamon::nth<1, Types...>,
		hamon::enable_if_t<hamon::conjunction<
			hamon::bool_constant<sizeof...(Types) == 2>,	// [tuple.assign]/33.1
			hamon::is_assignable<typename T0::type&, U1>,	// [tuple.assign]/33.2
			hamon::is_assignable<typename T1::type&, U2>	// [tuple.assign]/33.3
		>::value>* = nullptr
	>
	HAMON_CXX14_CONSTEXPR tuple&
	operator=(pair<U1, U2>&& u)
	HAMON_NOEXCEPT_IF((hamon::conjunction<
		hamon::is_nothrow_assignable<typename T0::type&, U1>,
		hamon::is_nothrow_assignable<typename T1::type&, U2>
	>::value))
	{
		impl_type::assign(*this, hamon::move(u));	// [tuple.assign]/34
		return *this;								// [tuple.assign]/35
	}

	// operator=(pair<U1, U2>&&) const
	template <typename U1, typename U2,
		typename T0 = hamon::nth<0, Types...>,
		typename T1 = hamon::nth<1, Types...>,
		hamon::enable_if_t<hamon::conjunction<
			hamon::bool_constant<sizeof...(Types) == 2>,		// [tuple.assign]/36.1
			hamon::is_assignable<typename T0::type const&, U1>,	// [tuple.assign]/36.2
			hamon::is_assignable<typename T1::type const&, U2>	// [tuple.assign]/36.3
		>::value>* = nullptr
	>
	HAMON_CXX14_CONSTEXPR tuple const&
	operator=(pair<U1, U2>&& u) const
	HAMON_NOEXCEPT_IF((hamon::conjunction<
		hamon::is_nothrow_assignable<typename T0::type const&, U1>,
		hamon::is_nothrow_assignable<typename T1::type const&, U2>
	>::value))
	{
		impl_type::assign(*this, hamon::move(u));	// [tuple.assign]/37
		return *this;								// [tuple.assign]/38
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::tuple_like, UTuple),
		typename Constraint = TupleLikeAssign<UTuple>,
		hamon::enable_if_t<Constraint::assignable>* = nullptr
	>
	HAMON_CXX14_CONSTEXPR tuple&
	operator=(UTuple&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
	{
		impl_type::assign(*this, hamon::forward<UTuple>(u));	// [tuple.assign]/40
		return *this;											// [tuple.assign]/41
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::tuple_like, UTuple),
		typename Constraint = TupleLikeAssignConst<UTuple>,
		hamon::enable_if_t<Constraint::assignable>* = nullptr
	>
	HAMON_CXX14_CONSTEXPR tuple const&
	operator=(UTuple&& u) const
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
	{
		impl_type::assign(*this, hamon::forward<UTuple>(u));	// [tuple.assign]/43
		return *this;											// [tuple.assign]/44
	}

	// [tuple.swap], tuple swap
	HAMON_CXX14_CONSTEXPR void
	swap(tuple& rhs)
	HAMON_NOEXCEPT_IF((hamon::conjunction<
		hamon::is_nothrow_swappable<Types>...>::value))
	{
		impl_type::swap(*this, rhs);
	}

	HAMON_CXX14_CONSTEXPR void
	swap(tuple const& rhs) const
	HAMON_NOEXCEPT_IF((hamon::conjunction<
		hamon::is_nothrow_swappable<Types const>...>::value))
	{
		impl_type::swap(*this, rhs);
	}
};

template <>
class tuple<>
{
public:
	// [tuple.cnstr]/5
	HAMON_CXX11_CONSTEXPR tuple() = default;

	template <typename Alloc>
	HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const&) HAMON_NOEXCEPT
	{}

	template <typename Alloc>
	HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const&, tuple const&) HAMON_NOEXCEPT
	{}

	template <typename Alloc>
	HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const&, tuple&&) HAMON_NOEXCEPT
	{}

	template <typename Alloc, HAMON_CONSTRAINED_PARAM(hamon::tuple_like, UTuple),
		typename = hamon::enable_if_t<
			std::tuple_size<hamon::remove_cvref_t<UTuple>>::value == 0>>
	HAMON_CXX11_CONSTEXPR
	tuple(hamon::allocator_arg_t, Alloc const&, UTuple&&) HAMON_NOEXCEPT
	{}

	HAMON_CXX14_CONSTEXPR void
	swap(tuple&) HAMON_NOEXCEPT
	{}

	HAMON_CXX14_CONSTEXPR void
	swap(tuple const&) const HAMON_NOEXCEPT
	{}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename... UTypes>
tuple(UTypes...) -> tuple<UTypes...>;

template <typename T1, typename T2>
tuple(pair<T1, T2>) -> tuple<T1, T2>;

// for clang
template <typename Alloc>
tuple(hamon::allocator_arg_t, Alloc) -> tuple<>;

template <typename Alloc, typename... UTypes>
tuple(hamon::allocator_arg_t, Alloc, UTypes...) -> tuple<UTypes...>;

template <typename Alloc, typename T1, typename T2>
tuple(hamon::allocator_arg_t, Alloc, pair<T1, T2>) -> tuple<T1, T2>;

template <typename Alloc, typename... UTypes>
tuple(hamon::allocator_arg_t, Alloc, tuple<UTypes...>) -> tuple<UTypes...>;

#endif

}	// namespace hamon

#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/add_const.hpp>
#include <hamon/type_traits/integral_constant.hpp>
#include <hamon/type_traits/nth.hpp>

namespace std
{

// Tuple helper classes[tuple.helper]
template <typename... Types>
struct tuple_size<hamon::tuple<Types...>>
	: public hamon::integral_constant<hamon::size_t, sizeof...(Types)> {};

template <hamon::size_t I, typename... Types>
struct tuple_element<I, hamon::tuple<Types...>>
{
	using type = hamon::nth_t<I, Types...>;
};

}	// namespace std

#include <hamon/tuple/detail/access.hpp>
#include <hamon/tuple/detail/exactly_once.hpp>
#include <hamon/tuple/detail/find_index.hpp>

namespace hamon
{

// Element access	[tuple.elem]
template <hamon::size_t I, typename... Types>
inline HAMON_CXX11_CONSTEXPR tuple_element_t<I, tuple<Types...>>&
get(tuple<Types...>& t) HAMON_NOEXCEPT
{
	static_assert(I < sizeof...(Types), "[tuple.elem]/1");
	return tuple_detail::access::get<I>(t);
}

template <hamon::size_t I, typename... Types>
inline HAMON_CXX11_CONSTEXPR tuple_element_t<I, tuple<Types...>>&&
get(tuple<Types...>&& t) HAMON_NOEXCEPT
{
	static_assert(I < sizeof...(Types), "[tuple.elem]/1");
	return tuple_detail::access::get<I>(hamon::move(t));
}

template <hamon::size_t I, typename... Types>
inline HAMON_CXX11_CONSTEXPR tuple_element_t<I, tuple<Types...>> const&
get(tuple<Types...> const& t) HAMON_NOEXCEPT
{
	static_assert(I < sizeof...(Types), "[tuple.elem]/1");
	return tuple_detail::access::get<I>(t);
}

template <hamon::size_t I, typename... Types>
inline HAMON_CXX11_CONSTEXPR tuple_element_t<I, tuple<Types...>> const&&
get(tuple<Types...> const&& t) HAMON_NOEXCEPT
{
	static_assert(I < sizeof...(Types), "[tuple.elem]/1");
	return tuple_detail::access::get<I>(hamon::move(t));
}

template <typename T, typename... Types>
inline HAMON_CXX11_CONSTEXPR T&
get(tuple<Types...>& t) HAMON_NOEXCEPT
{
	static_assert(tuple_detail::exactly_once<T, Types...>::value, "[tuple.elem]/5");
	return hamon::get<tuple_detail::find_index<T, Types...>::value>(t);
}

template <typename T, typename... Types>
inline HAMON_CXX11_CONSTEXPR T&&
get(tuple<Types...>&& t) HAMON_NOEXCEPT
{
	static_assert(tuple_detail::exactly_once<T, Types...>::value, "[tuple.elem]/5");
	return hamon::get<tuple_detail::find_index<T, Types...>::value>(hamon::move(t));
}

template <typename T, typename... Types>
inline HAMON_CXX11_CONSTEXPR T const&
get(tuple<Types...> const& t) HAMON_NOEXCEPT
{
	static_assert(tuple_detail::exactly_once<T, Types...>::value, "[tuple.elem]/5");
	return hamon::get<tuple_detail::find_index<T, Types...>::value>(t);
}

template <typename T, typename... Types>
inline HAMON_CXX11_CONSTEXPR T const&&
get(tuple<Types...> const&& t) HAMON_NOEXCEPT
{
	static_assert(tuple_detail::exactly_once<T, Types...>::value, "[tuple.elem]/5");
	return hamon::get<tuple_detail::find_index<T, Types...>::value>(hamon::move(t));
}

}	// namespace hamon

#include <hamon/tuple/detail/tuple_compare.hpp>

namespace hamon
{

// Relational operators	[tuple.rel]
template <typename... TTypes, typename... UTypes>
inline HAMON_CXX11_CONSTEXPR bool
operator==(tuple<TTypes...> const& t, tuple<UTypes...> const& u)
{
	return tuple_detail::tuple_eq(t, u);
}

template <typename... TTypes, HAMON_CONSTRAINED_PARAM(hamon::tuple_like, UTuple)>
inline HAMON_CXX11_CONSTEXPR bool
operator==(tuple<TTypes...> const& t, UTuple const& u)
{
	return tuple_detail::tuple_eq(t, u);
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename... TTypes, typename... UTypes>
inline HAMON_CXX11_CONSTEXPR auto
operator<=>(tuple<TTypes...> const& t, tuple<UTypes...> const& u)
->decltype(tuple_detail::tuple_3way(t, u))
{
	return tuple_detail::tuple_3way(t, u);
}

template <typename... TTypes, HAMON_CONSTRAINED_PARAM(hamon::tuple_like, UTuple)>
inline HAMON_CXX11_CONSTEXPR auto
operator<=>(tuple<TTypes...> const& t, UTuple const& u)
->decltype(tuple_detail::tuple_3way(t, u))
{
	return tuple_detail::tuple_3way(t, u);
}

#else

template <typename... TTypes, typename... UTypes>
inline HAMON_CXX11_CONSTEXPR bool
operator<(tuple<TTypes...> const& t, tuple<UTypes...> const& u)
{
	return tuple_detail::tuple_less(t, u);
}

template <typename... TTypes, typename... UTypes>
inline HAMON_CXX11_CONSTEXPR bool
operator!=(tuple<TTypes...> const& t, tuple<UTypes...> const& u)
{
	return !(t == u);
}

template <typename... TTypes, typename... UTypes>
inline HAMON_CXX11_CONSTEXPR bool
operator>(tuple<TTypes...> const& t, tuple<UTypes...> const& u)
{
	return u < t;
}

template <typename... TTypes, typename... UTypes>
inline HAMON_CXX11_CONSTEXPR bool
operator<=(tuple<TTypes...> const& t, tuple<UTypes...> const& u)
{
	return !(u < t);
}

template <typename... TTypes, typename... UTypes>
inline HAMON_CXX11_CONSTEXPR bool
operator>=(tuple<TTypes...> const& t, tuple<UTypes...> const& u)
{
	return !(t < u);
}

template <typename... TTypes, HAMON_CONSTRAINED_PARAM(hamon::tuple_like, UTuple)>
inline HAMON_CXX11_CONSTEXPR bool
operator<(tuple<TTypes...> const& t, UTuple const& u)
{
	return tuple_detail::tuple_less(t, u);
}

template <typename... TTypes, HAMON_CONSTRAINED_PARAM(hamon::tuple_like, UTuple)>
inline HAMON_CXX11_CONSTEXPR bool
operator!=(tuple<TTypes...> const& t, UTuple const& u)
{
	return !(t == u);
}

template <typename... TTypes, HAMON_CONSTRAINED_PARAM(hamon::tuple_like, UTuple)>
inline HAMON_CXX11_CONSTEXPR bool
operator>(tuple<TTypes...> const& t, UTuple const& u)
{
	return tuple_detail::tuple_less(u, t);
}

template <typename... TTypes, HAMON_CONSTRAINED_PARAM(hamon::tuple_like, UTuple)>
inline HAMON_CXX11_CONSTEXPR bool
operator<=(tuple<TTypes...> const& t, UTuple const& u)
{
	return !(t > u);
}

template <typename... TTypes, HAMON_CONSTRAINED_PARAM(hamon::tuple_like, UTuple)>
inline HAMON_CXX11_CONSTEXPR bool
operator>=(tuple<TTypes...> const& t, UTuple const& u)
{
	return !(t < u);
}

#endif

// Tuple specialized algorithms	[tuple.special]
template <typename... Types,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::is_swappable<Types>...
	>::value>
>
inline HAMON_CXX14_CONSTEXPR void
swap(tuple<Types...>& x, tuple<Types...>& y)
HAMON_NOEXCEPT_IF_EXPR((x.swap(y)))
{
	x.swap(y);
}

template <typename... Types,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::is_swappable<Types const>...
	>::value>
>
inline HAMON_CXX14_CONSTEXPR void
swap(tuple<Types...> const& x, tuple<Types...> const& y)
HAMON_NOEXCEPT_IF_EXPR((x.swap(y)))
{
	x.swap(y);
}

}	// namespace hamon

// is_specialization_of_tuple の特殊化
#include <hamon/concepts/detail/is_specialization_of_tuple.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon {
namespace detail {

template <typename... Types>
struct is_specialization_of_tuple<hamon::tuple<Types...>>
	: public hamon::true_type {};

}	// namespace detail
}	// namespace hamon

// basic_common_reference の特殊化
#include <hamon/tuple/detail/basic_common_reference.hpp>

// common_type の特殊化
#include <hamon/tuple/detail/common_type.hpp>

// uses_allocator の特殊化
#include <memory>

namespace std
{

// Tuple traits	[tuple.traits]
template <typename... Types, typename Alloc>
struct uses_allocator<hamon::tuple<Types...>, Alloc> : std::true_type {};

}	// namespace std

#endif

#endif // HAMON_TUPLE_TUPLE_HPP
