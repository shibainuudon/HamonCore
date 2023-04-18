﻿/**
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
using std::make_tuple;
using std::forward_as_tuple;
using std::tie;
using std::ignore;

}	// namespace hamon

#else

#include <hamon/tuple/tuple_fwd.hpp>
#include <hamon/tuple/tuple_element.hpp>
#include <hamon/compare/common_comparison_category.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/compare/detail/synth3way.hpp>
#include <hamon/pair/pair.hpp>
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
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/unwrap_ref_decay.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/utility/index_sequence_for.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>
#include <memory>	// allocator_arg_t

namespace hamon
{

// TODO
template <typename T>
void get(T const&);

namespace tuple_detail
{

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
			hamon::is_constructible<T, U>::value
		>
	>
	HAMON_CXX11_CONSTEXPR
	tuple_leaf(U&& u)
		: m_value(hamon::forward<U>(u)) {}

	HAMON_CXX14_CONSTEXPR T &       get() &       { return m_value; }
	HAMON_CXX11_CONSTEXPR T const&  get() const&  { return m_value; }
	HAMON_CXX14_CONSTEXPR T &&      get() &&      { return hamon::move(m_value); }
	HAMON_CXX11_CONSTEXPR T const&& get() const&& { return hamon::move(m_value); }
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
	tuple_impl(hamon::integral_constant<int, 0>, UTypes&&... args)
		: tuple_leaf<Is, Types>(hamon::forward<UTypes>(args))...
	{}

#define FWD(u)	static_cast<decltype(u)>(u)

	template <typename UTuple>
	HAMON_CXX11_CONSTEXPR
	tuple_impl(hamon::integral_constant<int, 1>, UTuple&& u)
		: tuple_leaf<Is, Types>(get<Is>(FWD(u)))...
	{}

#undef FWD

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR
	static void swallow(Args&&...) HAMON_NOEXCEPT {}

	template <typename TTuple, typename... UTypes>
	HAMON_CXX14_CONSTEXPR
	static void copy_assign(TTuple& lhs, tuple<UTypes...> const& rhs)
	{
		swallow(((get<Is>(lhs) = get<Is>(rhs)), 0)...);
	}

	template <typename TTuple, typename... UTypes>
	HAMON_CXX14_CONSTEXPR
	static void forward_assign(TTuple& lhs, tuple<UTypes...>&& rhs)
	{
		swallow(((get<Is>(lhs) = hamon::forward<UTypes>(get<Is>(rhs))), 0)...);
	}

	template <typename TTuple, typename U1, typename U2>
	HAMON_CXX14_CONSTEXPR
	static void copy_assign(TTuple& lhs, pair<U1, U2> const& rhs)
	{
		get<0>(lhs) = rhs.first;
		get<1>(lhs) = rhs.second;
	}

	template <typename TTuple, typename U1, typename U2>
	HAMON_CXX14_CONSTEXPR
	static void forward_assign(TTuple& lhs, pair<U1, U2>&& rhs)
	{
		get<0>(lhs) = hamon::forward<U1>(rhs.first);
		get<1>(lhs) = hamon::forward<U2>(rhs.second);
	}

	template <typename TTuple, typename UTuple>
	HAMON_CXX14_CONSTEXPR
	static void swap(TTuple& lhs, UTuple& rhs)
	{
		using std::swap;
		swallow((swap(get<Is>(lhs), get<Is>(rhs)), 0)...);
	}
};

HAMON_WARNING_POP()

template <typename... Types>
struct tuple_constraint
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
			!hamon::is_same<hamon::remove_cvref_t<U0>, std::allocator_arg_t>::value ||
			 hamon::is_same<hamon::remove_cvref_t<T0>, std::allocator_arg_t>::value> {};
	// [tuple.cnstr]/12.2
	template <typename T0, typename U0>
	struct disambiguating_constraint<T0, U0, 3>
		: public disambiguating_constraint<T0, U0, 2> {};

	template <bool, typename... UTypes>
	struct UTypesCtorImpl
	{
		// [tuple.cnstr]/13
		// TODO [tuple.cnstr]/15
		// This constructor is defined as deleted if
		// (reference_constructs_from_temporary_v<Types, UTypes&&> || ...)
		// is true.
		static const bool constructible =
			hamon::conjunction<
				hamon::bool_constant<(sizeof...(Types) >= 1)>,					// [tuple.cnstr]/13.2
				disambiguating_constraint<										// [tuple.cnstr]/13.3
					hamon::nth_t<0, Types...>,
					hamon::nth_t<0, UTypes...>,
					sizeof...(Types)
				>,
				hamon::is_constructible<Types, UTypes>...						// [tuple.cnstr]/13.3
			>::value;

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
		sizeof...(Types) == sizeof...(UTypes), // [tuple.cnstr]/13.1
		UTypes...
	>{};

#define FWD(u)	static_cast<decltype(u)>(u)

private:
	template <bool, typename IndexSequence, typename UTuple, typename... UTypes>
	struct UTupleCtorImpl;

	template <hamon::size_t... Is, typename UTuple, typename... UTypes>
	struct UTupleCtorImpl<true, hamon::index_sequence<Is...>, UTuple, UTypes...>
	{
		// [tuple.cnstr]/21
		// TODO [tuple.cnstr]/23
		// The constructor is defined as deleted if
		// (reference_constructs_from_temporary_v<Types, decltype(get<I>(FWD(u)))> || ...)
		// is true.
		static const bool constructible =
			hamon::conjunction<
				// [tuple.cnstr]/21.2
				hamon::is_constructible<
					Types, decltype(get<Is>(FWD(hamon::declval<UTuple>())))
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
		static const bool implicitly =
			hamon::conjunction<
				hamon::is_convertible<
					decltype(get<Is>(FWD(hamon::declval<UTuple>()))), Types
				>...
			>::value;

		// [tuple.cnstr]/2
		static const bool nothrow =
			hamon::conjunction<
				hamon::is_nothrow_constructible<
					Types, decltype(get<Is>(FWD(hamon::declval<UTuple>())))
				>...
			>::value;
	};

	template <typename IndexSequence, typename UTuple, typename... UTypes>
	struct UTupleCtorImpl<false, IndexSequence, UTuple, UTypes...>
	{
		static const bool constructible = false;
		static const bool implicitly = false;
		static const bool nothrow = false;
	};

public:
	template <typename UTuple, typename... UTypes>
	struct UTupleCtor : public UTupleCtorImpl<
		sizeof...(Types) == sizeof...(UTypes),	// [tuple.cnstr]/21.1
		hamon::make_index_sequence<sizeof...(Types)>,
		UTuple,
		UTypes...
	>{};

private:
	template <bool, typename Pair>
	struct PairCtorImpl
	{
	private:
		using T0 = hamon::nth_t<0, Types...>;
		using T1 = hamon::nth_t<1, Types...>;

		using U0 = decltype(get<0>(FWD(hamon::declval<Pair>())));
		using U1 = decltype(get<1>(FWD(hamon::declval<Pair>())));

	public:
		// [tuple.cnstr]/25
		// TODO [tuple.cnstr]/27
		// The constructor is defined as deleted if
		// reference_constructs_from_temporary_v<T0, decltype(get<0>(FWD(u)))> ||
		// reference_constructs_from_temporary_v<T1, decltype(get<1>(FWD(u)))>
		// is true.
		static const bool constructible =
			hamon::conjunction<
				hamon::is_constructible<T0, U0>,	// [tuple.cnstr]/25.2
				hamon::is_constructible<T1, U1>		// [tuple.cnstr]/25.3
			>::value;

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

#undef FWD
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

	using constraint_type = tuple_detail::tuple_constraint<Types...>;

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

	template <typename Pair>
	using PairCtor = typename constraint_type::template PairCtor<Pair>;

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
		: m_impl(hamon::integral_constant<int, 0>{}, args...)
	{}

	// tuple(UTypes&&... args)
	template <typename... UTypes,
		hamon::enable_if_t<UTypesCtor<UTypes...>::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!UTypesCtor<UTypes...>::implicitly)
	tuple(UTypes&&... args)
	HAMON_NOEXCEPT_IF((UTypesCtor<UTypes...>::nothrow))
		: m_impl(hamon::integral_constant<int, 0>{}, hamon::forward<UTypes>(args)...)
	{}

	// tuple(tuple<UTypes...>& u)
	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...>&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(tuple<UTypes...>& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::integral_constant<int, 1>{}, u)
	{}

	// tuple(tuple<UTypes...> const& u)
	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...> const&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(tuple<UTypes...> const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::integral_constant<int, 1>{}, u)
	{}

	// tuple(tuple<UTypes...>&& u)
	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...>&&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(tuple<UTypes...>&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::integral_constant<int, 1>{}, hamon::move(u))
	{}

	// tuple(tuple<UTypes...> const&& u)
	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...> const&&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(tuple<UTypes...> const&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::integral_constant<int, 1>{}, hamon::move(u))
	{}

	// tuple(pair<U1, U2>& u)
	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2>&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(pair<U1, U2>& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::integral_constant<int, 1>{}, u)
	{}

	// tuple(pair<U1, U2> const& u)
	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2> const&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(pair<U1, U2> const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::integral_constant<int, 1>{}, u)
	{}

	// tuple(pair<U1, U2>&& u)
	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2>&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(pair<U1, U2>&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::integral_constant<int, 1>{}, hamon::move(u))
	{}

	// tuple(pair<U1, U2> const&& u)
	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2> const&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(pair<U1, U2> const&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::integral_constant<int, 1>{}, hamon::move(u))
	{}

#if 0	// TODO
	template <tuple-like UTuple>
	constexpr explicit/*(see below)*/
	tuple(UTuple&&);

	// allocator-extended constructors
	template <typename Alloc>
	constexpr explicit/*(see below)*/
	tuple(std::allocator_arg_t, Alloc const& a);

	template <typename Alloc>
	constexpr explicit/*(see below)*/
	tuple(std::allocator_arg_t, Alloc const& a, Types const&...);

	template <typename Alloc, typename... UTypes>
	constexpr explicit/*(see below)*/
	tuple(std::allocator_arg_t, Alloc const& a, UTypes&&...);

	template <typename Alloc>
	constexpr
	tuple(std::allocator_arg_t, Alloc const& a, tuple const&);

	template <typename Alloc>
	constexpr
	tuple(std::allocator_arg_t, Alloc const& a, tuple&&);

	template <typename Alloc, typename... UTypes>
	constexpr explicit/*(see below)*/
	tuple(std::allocator_arg_t, Alloc const& a, tuple<UTypes...>&);

	template <typename Alloc, typename... UTypes>
	constexpr explicit/*(see below)*/
	tuple(std::allocator_arg_t, Alloc const& a, tuple<UTypes...> const&);

	template <typename Alloc, typename... UTypes>
	constexpr explicit/*(see below)*/
	tuple(std::allocator_arg_t, Alloc const& a, tuple<UTypes...>&&);

	template <typename Alloc, typename... UTypes>
	constexpr explicit/*(see below)*/
	tuple(std::allocator_arg_t, Alloc const& a, tuple<UTypes...> const&&);

	template <typename Alloc, typename U1, typename U2>
	constexpr explicit/*(see below)*/
	tuple(std::allocator_arg_t, Alloc const& a, pair<U1, U2>&);

	template <typename Alloc, typename U1, typename U2>
	constexpr explicit/*(see below)*/
	tuple(std::allocator_arg_t, Alloc const& a, pair<U1, U2> const&);

	template <typename Alloc, typename U1, typename U2>
	constexpr explicit/*(see below)*/
	tuple(std::allocator_arg_t, Alloc const& a, pair<U1, U2>&&);

	template <typename Alloc, typename U1, typename U2>
	constexpr explicit/*(see below)*/
	tuple(std::allocator_arg_t, Alloc const& a, pair<U1, U2> const&&);

	template <typename Alloc, tuple-like UTuple>
	constexpr explicit/*(see below)*/
	tuple(std::allocator_arg_t, Alloc const& a, UTuple&&);
#endif

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
		: m_impl(hamon::integral_constant<int, 0>{}, args...)
	{}

	template <typename Dummy = void,
		hamon::enable_if_t<ElementCtor<Dummy>::constructible>* = nullptr,
		hamon::enable_if_t<ElementCtor<Dummy>::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(Types const&... args)
	HAMON_NOEXCEPT_IF((ElementCtor<Dummy>::nothrow))
		: m_impl(hamon::integral_constant<int, 0>{}, args...)
	{}

	// tuple(UTypes&&... args)
	template <typename... UTypes,
		hamon::enable_if_t<UTypesCtor<UTypes...>::constructible>* = nullptr,
		hamon::enable_if_t<!UTypesCtor<UTypes...>::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(UTypes&&... args)
	HAMON_NOEXCEPT_IF((UTypesCtor<UTypes...>::nothrow))
		: m_impl(hamon::integral_constant<int, 0>{}, hamon::forward<UTypes>(args)...)
	{}

	template <typename... UTypes,
		hamon::enable_if_t<UTypesCtor<UTypes...>::constructible>* = nullptr,
		hamon::enable_if_t<UTypesCtor<UTypes...>::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(UTypes&&... args)
	HAMON_NOEXCEPT_IF((UTypesCtor<UTypes...>::nothrow))
		: m_impl(hamon::integral_constant<int, 0>{}, hamon::forward<UTypes>(args)...)
	{}

	// tuple(tuple<UTypes...>& u)
	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...>&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...>& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::integral_constant<int, 1>{}, u)
	{}

	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...>&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...>& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::integral_constant<int, 1>{}, u)
	{}

	// tuple(tuple<UTypes...> const& u)
	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...> const&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...> const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::integral_constant<int, 1>{}, u)
	{}

	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...> const&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...> const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::integral_constant<int, 1>{}, u)
	{}

	// tuple(tuple<UTypes...>&& u)
	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...>&&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...>&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::integral_constant<int, 1>{}, hamon::move(u))
	{}

	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...>&&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...>&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::integral_constant<int, 1>{}, hamon::move(u))
	{}

	// tuple(tuple<UTypes...> const&& u)
	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...> const&&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...> const&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::integral_constant<int, 1>{}, hamon::move(u))
	{}

	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...> const&&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...> const&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::integral_constant<int, 1>{}, hamon::move(u))
	{}

	// tuple(pair<U1, U2>& u)
	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2>&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2>& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::integral_constant<int, 1>{}, u)
	{}

	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2>&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2>& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::integral_constant<int, 1>{}, u)
	{}

	// tuple(pair<U1, U2> const& u)
	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2> const&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2> const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::integral_constant<int, 1>{}, u)
	{}

	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2> const&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2> const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::integral_constant<int, 1>{}, u)
	{}

	// tuple(pair<U1, U2>&& u)
	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2>&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2>&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::integral_constant<int, 1>{}, hamon::move(u))
	{}

	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2>&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2>&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::integral_constant<int, 1>{}, hamon::move(u))
	{}

	// tuple(pair<U1, U2> const&& u)
	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2> const&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2> const&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::integral_constant<int, 1>{}, hamon::move(u))
	{}

	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2> const&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2> const&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(hamon::integral_constant<int, 1>{}, hamon::move(u))
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
		impl_type::copy_assign(*this, u);		// [tuple.assign]/2
		return *this;							// [tuple.assign]/3
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
		impl_type::copy_assign(*this, u);		// [tuple.assign]/6
		return *this;							// [tuple.assign]/7
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
		impl_type::forward_assign(*this, hamon::move(u));	// [tuple.assign]/9
		return *this;										// [tuple.assign]/10
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
		impl_type::forward_assign(*this, hamon::move(u));	// [tuple.assign]/13
		return *this;										// [tuple.assign]/14
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
		impl_type::copy_assign(*this, u);		// [tuple.assign]/16
		return *this;							// [tuple.assign]/17
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
		impl_type::copy_assign(*this, u);		// [tuple.assign]/19
		return *this;							// [tuple.assign]/20
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
		impl_type::forward_assign(*this, hamon::move(u));	// [tuple.assign]/22
		return *this;										// [tuple.assign]/23
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
		impl_type::forward_assign(*this, hamon::move(u));	// [tuple.assign]/25
		return *this;										// [tuple.assign]/26
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
		impl_type::copy_assign(*this, u);		// [tuple.assign]/28
		return *this;							// [tuple.assign]/29
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
		impl_type::copy_assign(*this, u);		// [tuple.assign]/31
		return *this;							// [tuple.assign]/32
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
		impl_type::forward_assign(*this, hamon::move(u));	// [tuple.assign]/34
		return *this;										// [tuple.assign]/35
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
		impl_type::forward_assign(*this, hamon::move(u));	// [tuple.assign]/37
		return *this;										// [tuple.assign]/38
	}

#if 0	// TODO
	template <tuple-like UTuple>
	constexpr tuple& operator=(UTuple&&);

	template <tuple-like UTuple>
	constexpr tuple const& operator=(UTuple&&) const;
#endif

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
};


#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename... UTypes>
tuple(UTypes...) -> tuple<UTypes...>;

template <typename T1, typename T2>
tuple(pair<T1, T2>) -> tuple<T1, T2>;

#if 0	// TODO
template <typename Alloc, typename... UTypes>
tuple(std::allocator_arg_t, Alloc, UTypes...) -> tuple<UTypes...>;

template <typename Alloc, typename T1, typename T2>
tuple(std::allocator_arg_t, Alloc, pair<T1, T2>) -> tuple<T1, T2>;

template <typename Alloc, typename... UTypes>
tuple(std::allocator_arg_t, Alloc, tuple<UTypes...>) -> tuple<UTypes...>;
#endif

#endif

// Tuple creation functions	[tuple.creation]

template <typename... TTypes>
inline HAMON_CXX11_CONSTEXPR tuple<hamon::unwrap_ref_decay_t<TTypes>...>
make_tuple(TTypes&&... t)
{
	// [tuple.creation]/1
	return tuple<hamon::unwrap_ref_decay_t<TTypes>...>(hamon::forward<TTypes>(t)...);
}

template <typename... TTypes>
inline HAMON_CXX11_CONSTEXPR tuple<TTypes&&...>
forward_as_tuple(TTypes&&... t) HAMON_NOEXCEPT
{
	// [tuple.creation]/4
	return tuple<TTypes&&...>(hamon::forward<TTypes>(t)...);
}

template <typename... TTypes>
inline HAMON_CXX11_CONSTEXPR tuple<TTypes&...>
tie(TTypes&... t) HAMON_NOEXCEPT
{
	// [tuple.creation]/5
	return tuple<TTypes&...>(t...);
}

namespace tuple_detail
{

struct ignore_t
{
	template <typename T>
	HAMON_CXX11_CONSTEXPR ignore_t const&
	operator=(T const&) const HAMON_NOEXCEPT
	{
		return *this;
	}
};

}	// namespace tuple_detail

HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
tuple_detail::ignore_t ignore{};

#if 0
template <tuple-like... Tuples>
constexpr tuple<CTypes...>
tuple_cat(Tuples&&... tpls);

// Calling a function with a tuple of arguments	[tuple.apply]
template <typename F, tuple-like Tuple>
constexpr decltype(auto)
apply(F&& f, Tuple&& t) noexcept(see below);

template <typename T, tuple-like Tuple>
constexpr T
make_from_tuple(Tuple&& t);
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

namespace hamon
{

namespace tuple_detail
{

struct access
{
	template <hamon::size_t I, typename... Types>
	static HAMON_CXX11_CONSTEXPR tuple_element_t<I, tuple<Types...>>&
	get(tuple<Types...>& t) HAMON_NOEXCEPT
	{
		using type = tuple_element_t<I, tuple<Types...>>;
		return static_cast<hamon::tuple_detail::tuple_leaf<I, type>&>(t.m_impl).get();
	}

	template <hamon::size_t I, typename... Types>
	static HAMON_CXX11_CONSTEXPR tuple_element_t<I, tuple<Types...>>&&
	get(tuple<Types...>&& t) HAMON_NOEXCEPT
	{
		using type = tuple_element_t<I, tuple<Types...>>;
		return static_cast<hamon::tuple_detail::tuple_leaf<I, type>&&>(t.m_impl).get();
	}

	template <hamon::size_t I, typename... Types>
	static HAMON_CXX11_CONSTEXPR tuple_element_t<I, tuple<Types...>> const&
	get(tuple<Types...> const& t) HAMON_NOEXCEPT
	{
		using type = tuple_element_t<I, tuple<Types...>>;
		return static_cast<hamon::tuple_detail::tuple_leaf<I, type> const&>(t.m_impl).get();
	}

	template <hamon::size_t I, typename... Types>
	static HAMON_CXX11_CONSTEXPR tuple_element_t<I, tuple<Types...>> const&&
	get(tuple<Types...> const&& t) HAMON_NOEXCEPT
	{
		using type = tuple_element_t<I, tuple<Types...>>;
		return static_cast<hamon::tuple_detail::tuple_leaf<I, type> const&&>(t.m_impl).get();
	}
};

template <typename T, typename... Types>
struct exactly_once
{
private:
	template <typename U, typename... UTypes>
	struct count_same_type;

	template <typename U>
	struct count_same_type<U>
		: public hamon::integral_constant<hamon::size_t, 0>
	{};

	template <typename U, typename Head, typename... Tail>
	struct count_same_type<U, Head, Tail...>
		: public hamon::integral_constant<hamon::size_t,
			(hamon::is_same<U, Head>::value ? 1 : 0) +
			count_same_type<U, Tail...>::value
		>
	{};

public:
	static const bool value = (count_same_type<T, Types...>::value == 1);
};

template <typename T, typename... Types>
struct find_index
{
private:
	template <hamon::size_t I, typename U, typename... UTypes>
	struct find_index_impl;

	template <hamon::size_t I, typename U>
	struct find_index_impl<I, U>
	{
		static const hamon::size_t value = static_cast<hamon::size_t>(-1);
	};

	template <hamon::size_t I, typename U, typename Head, typename... Tail>
	struct find_index_impl<I, U, Head, Tail...>
	{
		static const hamon::size_t value =
			hamon::is_same<U, Head>::value ?
			I :
			find_index_impl<I+1, U, Tail...>::value;
	};

public:
	static const hamon::size_t value =
		find_index_impl<0, T, Types...>::value;
};

}	// namespace tuple_detail

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

namespace tuple_detail
{

template <hamon::size_t N, hamon::size_t I = 0>
struct tuple_compare
{
	template <typename T, typename U>
	static HAMON_CXX11_CONSTEXPR bool
	equal(T const& t, U const& u)
	{
		return bool(hamon::get<I>(t) == hamon::get<I>(u)) &&
			tuple_compare<N, I + 1>::equal(t, u);
	}

	template <typename T, typename U>
	static HAMON_CXX11_CONSTEXPR bool
	less(T const& t, U const& u)
	{
		return
			  bool(hamon::get<I>(t) < hamon::get<I>(u)) ||
			(!bool(hamon::get<I>(u) < hamon::get<I>(t)) &&
			tuple_compare<N, I + 1>::less(t, u));
	}

	template <typename Result, typename T, typename U>
	static HAMON_CXX14_CONSTEXPR Result
	three_way(T const& t, U const& u)
	{
		auto c = hamon::detail::synth3way(hamon::get<I>(t), hamon::get<I>(u));
		if (c != 0)
		{
			return c;
		}
		return tuple_compare<N, I + 1>::template three_way<Result>(t, u);
	}
};

template <hamon::size_t N>
struct tuple_compare<N, N>
{
	template <typename T, typename U>
	static HAMON_CXX11_CONSTEXPR bool
	equal(T const&, U const&)
	{
		return true;
	}

	template <typename T, typename U>
	static HAMON_CXX11_CONSTEXPR bool
	less(T const&, U const&)
	{
		return false;
	}

	template <typename Result, typename T, typename U>
	static HAMON_CXX14_CONSTEXPR Result
	three_way(T const&, U const&)
	{
		return hamon::strong_ordering::equal;
	}
};

}	// namespace tuple_detail


// Relational operators	[tuple.rel]
template <typename... TTypes, typename... UTypes>
inline HAMON_CXX11_CONSTEXPR bool
operator==(tuple<TTypes...> const& t, tuple<UTypes...> const& u)
{
	static_assert(sizeof...(TTypes) == sizeof...(UTypes), "[tuple.rel]/2");
	return tuple_detail::tuple_compare<sizeof...(TTypes)>::equal(t, u);
}

#if 0	// TODO
template <typename... TTypes, tuple-like UTuple>
constexpr bool operator==(tuple<TTypes...> const& t, UTuple const& u);
#endif

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename... TTypes, typename... UTypes>
inline HAMON_CXX11_CONSTEXPR
hamon::common_comparison_category_t<hamon::detail::synth3way_t<TTypes, UTypes>...>
operator<=>(tuple<TTypes...> const& t, tuple<UTypes...> const& u)
{
	using result_t = hamon::common_comparison_category_t<hamon::detail::synth3way_t<TTypes, UTypes>...>;
	return tuple_detail::tuple_compare<sizeof...(TTypes)>::template three_way<result_t>(t, u);
}

#if 0	// TODO
template <typename... TTypes, tuple-like UTuple>
constexpr hamon::common_comparison_category_t<hamon::detail::synth3way_t<TTypes, Elems>...>
operator<=>(tuple<TTypes...> const& t, UTuple const& u);
#endif

#else

template <typename... TTypes, typename... UTypes>
inline HAMON_CXX11_CONSTEXPR bool
operator<(tuple<TTypes...> const& t, tuple<UTypes...> const& u)
{
	static_assert(sizeof...(TTypes) == sizeof...(UTypes), "");
	return tuple_detail::tuple_compare<sizeof...(TTypes)>::less(t, u);
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

#endif


#if 0	// TODO
// common_reference related specializations	[tuple.common.ref]
template <tuple-like TTuple, tuple-like UTuple,
	template <typename> class TQual, template <typename> class UQual>
struct basic_common_reference<TTuple, UTuple, TQual, UQual>
{
	using type = see below;
};

template <tuple-like TTuple, tuple-like UTuple>
struct common_type<TTuple, UTuple>
{
	using type = see below;
};
#endif

#if 0	// TODO
// Tuple traits	[tuple.traits]
template <typename... Types, typename Alloc>
struct uses_allocator<tuple<Types...>, Alloc> : true_type {};
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

#include <hamon/concepts/detail/is_specialization_of_tuple.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon {
namespace detail {

// is_specialization_of_tuple の特殊化
template <typename... Types>
struct is_specialization_of_tuple<hamon::tuple<Types...>>
	: public hamon::true_type {};

}	// namespace detail
}	// namespace hamon

#endif

#endif // HAMON_TUPLE_TUPLE_HPP