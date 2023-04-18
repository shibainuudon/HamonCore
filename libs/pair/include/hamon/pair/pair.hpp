/**
 *	@file	pair.hpp
 *
 *	@brief	pair の定義
 */

#ifndef HAMON_PAIR_PAIR_HPP
#define HAMON_PAIR_PAIR_HPP

#include <hamon/pair/config.hpp>

#if defined(HAMON_USE_STD_PAIR)

#include <utility>

namespace hamon
{

using std::pair;
using std::make_pair;

}	// namespace hamon

#else

#include <hamon/compare/common_comparison_category.hpp>
#include <hamon/compare/detail/synth3way.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
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
#include <hamon/type_traits/is_swappable.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/unwrap_ref_decay.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

// Piecewise construction	[pair.piecewise]
struct piecewise_construct_t
{
	explicit piecewise_construct_t() = default;
};

HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR piecewise_construct_t piecewise_construct{};

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)
HAMON_WARNING_DISABLE_CLANG("-Wimplicit-int-conversion")
HAMON_WARNING_DISABLE_CLANG("-Wimplicit-float-conversion")
HAMON_WARNING_DISABLE_CLANG("-Wimplicit-int-float-conversion")
HAMON_WARNING_DISABLE_GCC("-Wconversion")
HAMON_WARNING_DISABLE_GCC("-Wfloat-conversion")

// TODO
template <typename T>
void get(T const&);

// Class template pair	[pairs.pair]
template <typename T1, typename T2>
struct pair
{
private:
	template <typename>
	struct always_true : public hamon::true_type{};

	// [pairs.pair]/5
	template <typename Dummy>
	using DefaultConstructible =
		hamon::conjunction<
			always_true<Dummy>,
			hamon::is_default_constructible<T1>,
			hamon::is_default_constructible<T2>
		>;

	// [pairs.pair]/7
	template <typename Dummy>
	using ImplicitlyDefaultConstructible =
		hamon::conjunction<
			always_true<Dummy>,
			hamon::is_implicitly_default_constructible<T1>,
			hamon::is_implicitly_default_constructible<T2>
		>;

	// [pairs.pair]/1
	using NothrowDefaultConstructible =
		hamon::conjunction<
			hamon::is_nothrow_default_constructible<T1>,
			hamon::is_nothrow_default_constructible<T2>
		>;

	// [pairs.pair]/8
	template <typename Dummy>
	using ElementConstructible =
		hamon::conjunction<
			always_true<Dummy>,
			hamon::is_copy_constructible<T1>,
			hamon::is_copy_constructible<T2>
		>;

	// [pairs.pair]/10
	template <typename Dummy>
	using ImplicitlyElementConstructible =
		hamon::conjunction<
			always_true<Dummy>,
			hamon::is_convertible<T1 const&, T1>,
			hamon::is_convertible<T2 const&, T2>
		>;

	// [pairs.pair]/1
	using NothrowElementConstructible =
		hamon::conjunction<
			hamon::is_nothrow_copy_constructible<T1>,
			hamon::is_nothrow_copy_constructible<T2>
		>;

	// [pairs.pair]/11
	// TODO
	// [pairs.pair]/13
	// This constructor is defined as deleted if
	// reference_constructs_from_temporary_v<first_type, U1&&> is true or
	// reference_constructs_from_temporary_v<second_type, U2&&> is true.
	template <typename U1, typename U2>
	using Constructible =
		hamon::conjunction<
			hamon::is_constructible<T1, U1>,		// [pairs.pair]/11.1
			hamon::is_constructible<T2, U2>			// [pairs.pair]/11.2
		>;

	// [pairs.pair]/13
	template <typename U1, typename U2>
	using ImplicitlyConstructible =
		hamon::conjunction<
			hamon::is_convertible<U1, T1>,
			hamon::is_convertible<U2, T2>
		>;

	// [pairs.pair]/1
	template <typename U1, typename U2>
	using NothrowConstructible =
		hamon::conjunction<
			hamon::is_nothrow_constructible<T1, U1>,
			hamon::is_nothrow_constructible<T2, U2>
		>;

	// [pairs.pair]/14
	#define FWD(u) static_cast<decltype(u)>(u)

	template <typename Pair>
	struct ConstructibleFromPairBase
	{
		using V1 = decltype(get<0>(FWD(hamon::declval<Pair>())));
		using V2 = decltype(get<1>(FWD(hamon::declval<Pair>())));
	};

	// [pairs.pair]/15
	template <typename Pair>
	struct ConstructibleFromPair
	{
		using Base = ConstructibleFromPairBase<Pair>;
		static const bool value = hamon::conjunction<
			hamon::is_constructible<T1, typename Base::V1>,		// [pairs.pair]/15.2
			hamon::is_constructible<T2, typename Base::V2>		// [pairs.pair]/15.3
		>::value;

		// TODO
		// [pairs.pair]/17
		// The constructor is defined as deleted if
		// reference_constructs_from_temporary_v<first_type, decltype(get<0>(FWD(p)))> ||
		// reference_constructs_from_temporary_v<second_type, decltype(get<1>(FWD(p)))>
		// is true.
	};

	// [pairs.pair]/17
	template <typename Pair>
	struct ImplicitlyConstructibleFromPair
	{
		using Base = ConstructibleFromPairBase<Pair>;
		static const bool value = hamon::conjunction<
			hamon::is_convertible<typename Base::V1, T1>,
			hamon::is_convertible<typename Base::V2, T2>
		>::value;
	};

	// [pairs.pair]/1
	template <typename Pair>
	struct NothrowConstructibleFromPair
	{
		using Base = ConstructibleFromPairBase<Pair>;
		static const bool value = hamon::conjunction<
			hamon::is_nothrow_constructible<T1, typename Base::V1>,
			hamon::is_nothrow_constructible<T2, typename Base::V2>
		>::value;
	};

	struct nat;

public:
	using first_type  = T1;
	using second_type = T2;

	T1 first;
	T2 second;

	// Destructor
	// [pairs.pair]/3
	//~pair();

	// Copy constructor
	// [pairs.pair]/2
	pair(pair const&) = default;

	// Move constructor
	// [pairs.pair]/2
	pair(pair&&) = default;

#if defined(HAMON_HAS_CXX20_CONDITIONAL_EXPLICIT)

	// pair()
	template <typename Dummy = void,
		hamon::enable_if_t<DefaultConstructible<Dummy>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!ImplicitlyDefaultConstructible<Dummy>::value)
	pair()
	HAMON_NOEXCEPT_IF((NothrowDefaultConstructible::value))
		: first(), second()	{}				// [pairs.pair]/6

	// pair(T1 const& x, T2 const& y)
	template <typename Dummy = void,
		hamon::enable_if_t<ElementConstructible<Dummy>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!ImplicitlyElementConstructible<Dummy>::value)
	pair(T1 const& x, T2 const& y)
	HAMON_NOEXCEPT_IF((NothrowElementConstructible::value))
		: first(x), second(y) {}			// [pairs.pair]/9

	// pair(U1&& x, U2&& y)
	template <
		typename U1 = T1,
		typename U2 = T2,
		hamon::enable_if_t<Constructible<U1, U2>::value>* = nullptr
	>
	HAMON_CXX11_CONSTEXPR
	explicit(!ImplicitlyConstructible<U1, U2>::value)
	pair(U1&& x, U2&& y)
	HAMON_NOEXCEPT_IF((NothrowConstructible<U1, U2>::value))
		: first (hamon::forward<U1>(x))		// [pairs.pair]/12
		, second(hamon::forward<U2>(y))
	{}

	// pair(pair<U1, U2>& p)
	template <
		typename U1, typename U2,
		typename P = pair<U1, U2>&,
		hamon::enable_if_t<ConstructibleFromPair<P>::value>* = nullptr
	>
	HAMON_CXX11_CONSTEXPR
	explicit(!ImplicitlyConstructibleFromPair<P>::value)
	pair(pair<U1, U2>& p)
	HAMON_NOEXCEPT_IF((NothrowConstructibleFromPair<P>::value))
		: first (get<0>(FWD(p)))	// [pairs.pair]/16
		, second(get<1>(FWD(p)))
	{}

	// pair(pair<U1, U2> const& p)
	template <
		typename U1, typename U2,
		typename P = pair<U1, U2> const&,
		hamon::enable_if_t<ConstructibleFromPair<P>::value>* = nullptr
	>
	HAMON_CXX11_CONSTEXPR
	explicit(!ImplicitlyConstructibleFromPair<P>::value)
	pair(pair<U1, U2> const& p)
	HAMON_NOEXCEPT_IF((NothrowConstructibleFromPair<P>::value))
		: first (get<0>(FWD(p)))	// [pairs.pair]/16
		, second(get<1>(FWD(p)))
	{}

	// pair(pair<U1, U2>&& p)
	template <
		typename U1, typename U2,
		typename P = pair<U1, U2>&&,
		hamon::enable_if_t<ConstructibleFromPair<P>::value>* = nullptr
	>
	HAMON_CXX11_CONSTEXPR
	explicit(!ImplicitlyConstructibleFromPair<P>::value)
	pair(pair<U1, U2>&& p)
	HAMON_NOEXCEPT_IF((NothrowConstructibleFromPair<P>::value))
		: first (get<0>(FWD(p)))	// [pairs.pair]/16
		, second(get<1>(FWD(p)))
	{}

	// pair(pair<U1, U2> const&& p)
	template <
		typename U1, typename U2,
		typename P = pair<U1, U2> const&&,
		hamon::enable_if_t<ConstructibleFromPair<P>::value>* = nullptr
	>
	HAMON_CXX11_CONSTEXPR
	explicit(!ImplicitlyConstructibleFromPair<P>::value)
	pair(pair<U1, U2> const&& p)
	HAMON_NOEXCEPT_IF((NothrowConstructibleFromPair<P>::value))
		: first (get<0>(FWD(p)))	// [pairs.pair]/16
		, second(get<1>(FWD(p)))
	{}

#else

	// pair()
	template <
		typename Dummy = void,
		hamon::enable_if_t<DefaultConstructible<Dummy>::value>* = nullptr,
		hamon::enable_if_t<!ImplicitlyDefaultConstructible<Dummy>::value>* = nullptr
	>
	explicit HAMON_CXX11_CONSTEXPR
	pair()
	HAMON_NOEXCEPT_IF((NothrowDefaultConstructible::value))
		: first(), second() {}		// [pairs.pair]/6

	template <
		typename Dummy = void,
		hamon::enable_if_t<DefaultConstructible<Dummy>::value>* = nullptr,
		hamon::enable_if_t<ImplicitlyDefaultConstructible<Dummy>::value>* = nullptr
	>
	HAMON_CXX11_CONSTEXPR
	pair()
	HAMON_NOEXCEPT_IF((NothrowDefaultConstructible::value))
		: first(), second() {}		// [pairs.pair]/6

	// pair(T1 const& x, T2 const& y)
	template <
		typename Dummy = void,
		hamon::enable_if_t<ElementConstructible<Dummy>::value>* = nullptr,
		hamon::enable_if_t<!ImplicitlyElementConstructible<Dummy>::value>* = nullptr
	>
	explicit HAMON_CXX11_CONSTEXPR
	pair(T1 const& x, T2 const& y)
	HAMON_NOEXCEPT_IF((NothrowElementConstructible::value))
		: first(x), second(y) {}	// [pairs.pair]/9

	template <
		typename Dummy = void,
		hamon::enable_if_t<ElementConstructible<Dummy>::value>* = nullptr,
		hamon::enable_if_t<ImplicitlyElementConstructible<Dummy>::value>* = nullptr
	>
	HAMON_CXX11_CONSTEXPR
	pair(T1 const& x, T2 const& y)
	HAMON_NOEXCEPT_IF((NothrowElementConstructible::value))
		: first(x), second(y) {}	// [pairs.pair]/9

	// pair(U1&& x, U2&& y)
	template <
		typename U1 = T1,
		typename U2 = T2,
		hamon::enable_if_t<Constructible<U1, U2>::value>* = nullptr,
		hamon::enable_if_t<!ImplicitlyConstructible<U1, U2>::value>* = nullptr
	>
	explicit HAMON_CXX11_CONSTEXPR
	pair(U1&& x, U2&& y)
	HAMON_NOEXCEPT_IF((NothrowConstructible<U1, U2>::value))
		: first (hamon::forward<U1>(x))		// [pairs.pair]/12
		, second(hamon::forward<U2>(y))
	{}

	template <
		typename U1 = T1,
		typename U2 = T2,
		hamon::enable_if_t<Constructible<U1, U2>::value>* = nullptr,
		hamon::enable_if_t<ImplicitlyConstructible<U1, U2>::value>* = nullptr
	>
	HAMON_CXX11_CONSTEXPR
	pair(U1&& x, U2&& y)
	HAMON_NOEXCEPT_IF((NothrowConstructible<U1, U2>::value))
		: first (hamon::forward<U1>(x))		// [pairs.pair]/12
		, second(hamon::forward<U2>(y))
	{}

	// pair(pair<U1, U2>& p)
	template <
		typename U1, typename U2,
		typename P = pair<U1, U2>&,
		hamon::enable_if_t<ConstructibleFromPair<P>::value>* = nullptr,
		hamon::enable_if_t<!ImplicitlyConstructibleFromPair<P>::value>* = nullptr
	>
	explicit HAMON_CXX11_CONSTEXPR
	pair(pair<U1, U2>& p)
	HAMON_NOEXCEPT_IF((NothrowConstructibleFromPair<P>::value))
		: first (get<0>(FWD(p)))			// [pairs.pair]/16
		, second(get<1>(FWD(p)))
	{}

	template <
		typename U1, typename U2,
		typename P = pair<U1, U2>&,
		hamon::enable_if_t<ConstructibleFromPair<P>::value>* = nullptr,
		hamon::enable_if_t<ImplicitlyConstructibleFromPair<P>::value>* = nullptr
	>
	HAMON_CXX11_CONSTEXPR
	pair(pair<U1, U2>& p)
	HAMON_NOEXCEPT_IF((NothrowConstructibleFromPair<P>::value))
		: first (get<0>(FWD(p)))			// [pairs.pair]/16
		, second(get<1>(FWD(p)))
	{}

	// pair(pair<U1, U2> const& p)
	template <
		typename U1, typename U2,
		typename P = pair<U1, U2> const&,
		hamon::enable_if_t<ConstructibleFromPair<P>::value>* = nullptr,
		hamon::enable_if_t<!ImplicitlyConstructibleFromPair<P>::value>* = nullptr
	>
	explicit HAMON_CXX11_CONSTEXPR
	pair(pair<U1, U2> const& p)
	HAMON_NOEXCEPT_IF((NothrowConstructibleFromPair<P>::value))
		: first (get<0>(FWD(p)))			// [pairs.pair]/16
		, second(get<1>(FWD(p)))
	{}

	template <
		typename U1, typename U2,
		typename P = pair<U1, U2> const&,
		hamon::enable_if_t<ConstructibleFromPair<P>::value>* = nullptr,
		hamon::enable_if_t<ImplicitlyConstructibleFromPair<P>::value>* = nullptr
	>
	HAMON_CXX11_CONSTEXPR
	pair(pair<U1, U2> const& p)
	HAMON_NOEXCEPT_IF((NothrowConstructibleFromPair<P>::value))
		: first (get<0>(FWD(p)))			// [pairs.pair]/16
		, second(get<1>(FWD(p)))
	{}

	// pair(pair<U1, U2>&& p)
	template <
		typename U1, typename U2,
		typename P = pair<U1, U2>&&,
		hamon::enable_if_t<ConstructibleFromPair<P>::value>* = nullptr,
		hamon::enable_if_t<!ImplicitlyConstructibleFromPair<P>::value>* = nullptr
	>
	explicit HAMON_CXX11_CONSTEXPR
	pair(pair<U1, U2>&& p)
	HAMON_NOEXCEPT_IF((NothrowConstructibleFromPair<P>::value))
		: first (get<0>(FWD(p)))			// [pairs.pair]/16
		, second(get<1>(FWD(p)))
	{}

	template <
		typename U1, typename U2,
		typename P = pair<U1, U2>&&,
		hamon::enable_if_t<ConstructibleFromPair<P>::value>* = nullptr,
		hamon::enable_if_t<ImplicitlyConstructibleFromPair<P>::value>* = nullptr
	>
	HAMON_CXX11_CONSTEXPR
	pair(pair<U1, U2>&& p)
	HAMON_NOEXCEPT_IF((NothrowConstructibleFromPair<P>::value))
		: first (get<0>(FWD(p)))			// [pairs.pair]/16
		, second(get<1>(FWD(p)))
	{}

	// pair(pair<U1, U2> const&& p)
	template <
		typename U1, typename U2,
		typename P = pair<U1, U2> const&&,
		hamon::enable_if_t<ConstructibleFromPair<P>::value>* = nullptr,
		hamon::enable_if_t<!ImplicitlyConstructibleFromPair<P>::value>* = nullptr
	>
	explicit HAMON_CXX11_CONSTEXPR
	pair(pair<U1, U2> const&& p)
	HAMON_NOEXCEPT_IF((NothrowConstructibleFromPair<P>::value))
		: first (get<0>(FWD(p)))			// [pairs.pair]/16
		, second(get<1>(FWD(p)))
	{}

	template <
		typename U1, typename U2,
		typename P = pair<U1, U2> const&&,
		hamon::enable_if_t<ConstructibleFromPair<P>::value>* = nullptr,
		hamon::enable_if_t<ImplicitlyConstructibleFromPair<P>::value>* = nullptr
	>
	HAMON_CXX11_CONSTEXPR
	pair(pair<U1, U2> const&& p)
	HAMON_NOEXCEPT_IF((NothrowConstructibleFromPair<P>::value))
		: first (get<0>(FWD(p)))			// [pairs.pair]/16
		, second(get<1>(FWD(p)))
	{}

#endif

	#undef FWD

	// TODO
	//template <pair-like P>
	//HAMON_CXX11_CONSTEXPR explicit/*(see below)*/ pair(P&& p);

	// TODO
	//template <typename... Args1, typename... Args2>
	//HAMON_CXX11_CONSTEXPR pair(piecewise_construct_t, tuple<Args1...> first_args, tuple<Args2...> second_args);

	HAMON_CXX14_CONSTEXPR pair&
	operator=(
		hamon::conditional_t<
			hamon::conjunction<						// [pairs.pair]/22
				hamon::is_copy_assignable<T1>,
				hamon::is_copy_assignable<T2>
			>::value,
			pair,
			nat
		> const& p)
	HAMON_NOEXCEPT_IF((hamon::conjunction<			// [pairs.pair]/1
		hamon::is_nothrow_copy_assignable<T1>,
		hamon::is_nothrow_copy_assignable<T2>
	>::value))
	{
		// [pairs.pair]/20
		first  = p.first;
		second = p.second;
		// [pairs.pair]/21
		return *this;
	}

	template <
		typename Dummy = void,
		hamon::enable_if_t<hamon::conjunction<		// [pairs.pair]/23
			always_true<Dummy>,
			hamon::is_copy_assignable<T1 const>,
			hamon::is_copy_assignable<T2 const>
		>::value>* = nullptr
	>
	HAMON_CXX14_CONSTEXPR pair const&
	operator=(pair const& p) const
	HAMON_NOEXCEPT_IF((hamon::conjunction<			// [pairs.pair]/1
		hamon::is_nothrow_copy_assignable<T1 const>,
		hamon::is_nothrow_copy_assignable<T2 const>
	>::value))
	{
		// [pairs.pair]/24
		first  = p.first;
		second = p.second;
		// [pairs.pair]/25
		return *this;
	}

	template <
		typename U1, typename U2,
		hamon::enable_if_t<hamon::conjunction<		// [pairs.pair]/26
			hamon::is_assignable<T1&, U1 const&>,
			hamon::is_assignable<T2&, U2 const&>
		>::value>* = nullptr
	>
	HAMON_CXX14_CONSTEXPR pair&
	operator=(pair<U1, U2> const& p)
	HAMON_NOEXCEPT_IF((hamon::conjunction<			// [pairs.pair]/1
		hamon::is_nothrow_assignable<T1&, U1 const&>,
		hamon::is_nothrow_assignable<T2&, U2 const&>
	>::value))
	{
		// [pairs.pair]/27
		first  = p.first;
		second = p.second;
		// [pairs.pair]/28
		return *this;
	}

	template <
		typename U1, typename U2,
		hamon::enable_if_t<hamon::conjunction<		// [pairs.pair]/29
			hamon::is_assignable<T1 const&, U1 const&>,
			hamon::is_assignable<T2 const&, U2 const&>
		>::value>* = nullptr
	>
	HAMON_CXX14_CONSTEXPR pair const&
	operator=(pair<U1, U2> const& p) const
	HAMON_NOEXCEPT_IF((hamon::conjunction<			// [pairs.pair]/1
		hamon::is_nothrow_assignable<T1 const&, U1 const&>,
		hamon::is_nothrow_assignable<T2 const&, U2 const&>
	>::value))
	{
		// [pairs.pair]/30
		first  = p.first;
		second = p.second;
		// [pairs.pair]/31
		return *this;
	}

	template <
		typename Dummy = void,
		hamon::enable_if_t<hamon::conjunction<		// [pairs.pair]/32
			always_true<Dummy>,
			hamon::is_move_assignable<T1>,
			hamon::is_move_assignable<T2>
		>::value>* = nullptr
	>
	HAMON_CXX14_CONSTEXPR pair&
	operator=(pair&& p)
	HAMON_NOEXCEPT_IF((hamon::conjunction<			// [pairs.pair]/35
		hamon::is_nothrow_move_assignable<T1>,
		hamon::is_nothrow_move_assignable<T2>
	>::value))
	{
		// [pairs.pair]/33
		first  = hamon::forward<T1>(p.first);
		second = hamon::forward<T2>(p.second);
		// [pairs.pair]/34
		return *this;
	}

	template <
		typename Dummy = void,
		hamon::enable_if_t<hamon::conjunction<		// [pairs.pair]/36
			always_true<Dummy>,
			hamon::is_assignable<T1 const&, T1>,
			hamon::is_assignable<T2 const&, T2>
		>::value>* = nullptr
	>
	HAMON_CXX14_CONSTEXPR pair const&
	operator=(pair&& p) const
	HAMON_NOEXCEPT_IF((hamon::conjunction<
		hamon::is_nothrow_assignable<T1 const&, T1>,
		hamon::is_nothrow_assignable<T2 const&, T2>
	>::value))
	{
		// [pairs.pair]/37
		first  = hamon::forward<T1>(p.first);
		second = hamon::forward<T2>(p.second);
		// [pairs.pair]/38
		return *this;
	}

	template <
		typename U1, typename U2,
		hamon::enable_if_t<hamon::conjunction<		// [pairs.pair]/39
			hamon::is_assignable<T1&, U1>,
			hamon::is_assignable<T2&, U2>
		>::value>* = nullptr
	>
	HAMON_CXX14_CONSTEXPR pair&
	operator=(pair<U1, U2>&& p)
	HAMON_NOEXCEPT_IF((hamon::conjunction<
		hamon::is_nothrow_assignable<T1&, U1>,
		hamon::is_nothrow_assignable<T2&, U2>
	>::value))
	{
		// [pairs.pair]/40
		first  = hamon::forward<U1>(p.first);
		second = hamon::forward<U2>(p.second);
		// [pairs.pair]/41
		return *this;
	}

	template <
		typename U1, typename U2,
		hamon::enable_if_t<hamon::conjunction<		// [pairs.pair]/48
			hamon::is_assignable<T1 const&, U1>,
			hamon::is_assignable<T2 const&, U2>
		>::value>* = nullptr
	>
	HAMON_CXX14_CONSTEXPR pair const&
	operator=(pair<U1, U2>&& p) const
	HAMON_NOEXCEPT_IF((hamon::conjunction<
		hamon::is_nothrow_assignable<T1 const&, U1>,
		hamon::is_nothrow_assignable<T2 const&, U2>
	>::value))
	{
		// [pairs.pair]/49
		first  = hamon::forward<U1>(p.first);
		second = hamon::forward<U2>(p.second);
		// [pairs.pair]/50
		return *this;
	}

	// TODO
	//template <pair-like P>
	//HAMON_CXX14_CONSTEXPR pair& operator=(P&& p);

	// TODO
	//template <pair-like P>
	//HAMON_CXX14_CONSTEXPR pair const& operator=(P&& p) const;

	template <
		typename Dummy = void,
		hamon::enable_if_t<hamon::conjunction<		// [pairs.pair]/51.1
			always_true<Dummy>,
			hamon::is_swappable<T1>,
			hamon::is_swappable<T2>
		>::value>* = nullptr
	>
	HAMON_CXX14_CONSTEXPR void
	swap(pair& p)
	HAMON_NOEXCEPT_IF((hamon::conjunction<			// [pairs.pair]/54.1
		hamon::is_nothrow_swappable<T1>,
		hamon::is_nothrow_swappable<T2>
	>::value))
	{
		// [pairs.pair]/53
		using std::swap;
		swap(first,  p.first);
		swap(second, p.second);
	}

	template <
		typename Dummy = void,
		hamon::enable_if_t<hamon::conjunction<		// [pairs.pair]/51.2
			always_true<Dummy>,
			hamon::is_swappable<T1 const>,
			hamon::is_swappable<T2 const>
		>::value>* = nullptr
	>
	HAMON_CXX14_CONSTEXPR void
	swap(pair const& p) const
	HAMON_NOEXCEPT_IF((hamon::conjunction<			// [pairs.pair]/54.2
		hamon::is_nothrow_swappable<T1 const>,
		hamon::is_nothrow_swappable<T2 const>
	>::value))
	{
		// [pairs.pair]/53
		using std::swap;
		swap(first,  p.first);
		swap(second, p.second);
	}
};

HAMON_WARNING_POP()

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename T1, typename T2>
pair(T1, T2) -> pair<T1, T2>;

#endif

// Specialized algorithms	[pairs.sprc]

template <typename T1, typename T2, typename U1, typename U2>
inline HAMON_CXX11_CONSTEXPR bool
operator==(pair<T1, T2> const& x, pair<U1, U2> const& y)
{
	// [pairs.sprc]/2
	return x.first == y.first && x.second == y.second;
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename T1, typename T2, typename U1, typename U2>
inline HAMON_CXX11_CONSTEXPR
hamon::common_comparison_category_t<
	hamon::detail::synth3way_t<T1, U1>,
	hamon::detail::synth3way_t<T2, U2>>
operator<=>(pair<T1, T2> const& x, pair<U1, U2> const& y)
{
	// [pairs.sprc]/3
	if (auto c = hamon::detail::synth3way(x.first, y.first); c != 0)
	{
		return c;
	}
	return hamon::detail::synth3way(x.second, y.second);
}

#else

template <typename T1, typename T2>
inline HAMON_CXX11_CONSTEXPR bool
operator<(pair<T1, T2> const& x, pair<T1, T2> const& y)
{
	return x.first < y.first ||
		(!(y.first < x.first) && x.second < y.second);
}

template <typename T1, typename T2>
inline HAMON_CXX11_CONSTEXPR bool
operator!=(pair<T1, T2> const& x, pair<T1, T2> const& y)
{
	return !(x == y);
}

template <typename T1, typename T2>
inline HAMON_CXX11_CONSTEXPR bool
operator>(pair<T1, T2> const& x, pair<T1, T2> const& y)
{
	return y < x;
}

template <typename T1, typename T2>
inline HAMON_CXX11_CONSTEXPR bool
operator<=(pair<T1, T2> const& x, pair<T1, T2> const& y)
{
	return !(y < x);
}

template <typename T1, typename T2>
inline HAMON_CXX11_CONSTEXPR bool
operator>=(pair<T1, T2> const& x, pair<T1, T2> const& y)
{
	return !(x < y);
}

#endif	// defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <
	typename T1, typename T2,
	hamon::enable_if_t<hamon::conjunction<	// [pairs.spec]/4.1
		hamon::is_swappable<T1>,
		hamon::is_swappable<T2>
	>::value>* = nullptr
>
inline HAMON_CXX14_CONSTEXPR void
swap(pair<T1, T2>& x, pair<T1, T2>& y)
	HAMON_NOEXCEPT_IF_EXPR(x.swap(y))
{
	// [pairs.spec]/5
	x.swap(y);
}

template <
	typename T1, typename T2,
	hamon::enable_if_t<hamon::conjunction<	// [pairs.spec]/4.2
		hamon::is_swappable<T1 const>,
		hamon::is_swappable<T2 const>
	>::value>* = nullptr
>
inline HAMON_CXX14_CONSTEXPR void
swap(pair<T1, T2> const& x, pair<T1, T2> const& y)
	HAMON_NOEXCEPT_IF_EXPR(x.swap(y))
{
	// [pairs.spec]/5
	x.swap(y);
}

template <typename T1, typename T2>
inline HAMON_CXX11_CONSTEXPR
pair<hamon::unwrap_ref_decay_t<T1>, hamon::unwrap_ref_decay_t<T2>>
make_pair(T1&& x, T2&& y)
{
	// [pairs.spec]/6
	return pair<hamon::unwrap_ref_decay_t<T1>, hamon::unwrap_ref_decay_t<T2>>(
		hamon::forward<T1>(x), hamon::forward<T2>(y));
}

}	// namespace hamon

// Tuple-like access to pair	[pair.astuple]

#include <hamon/type_traits/integral_constant.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <tuple>

namespace std
{

template <typename T1, typename T2>
struct tuple_size<hamon::pair<T1, T2>>
	: public hamon::integral_constant<hamon::size_t, 2> {};

template <typename T1, typename T2>
struct tuple_element<0, hamon::pair<T1, T2>>
{
	using type = T1;
};

template <typename T1, typename T2>
struct tuple_element<1, hamon::pair<T1, T2>>
{
	using type = T2;
};

}	// namespace std

#include <hamon/tuple/tuple_element.hpp>

namespace hamon
{

namespace detail
{

template <hamon::size_t I>
struct pair_get;

// [pair.astuple]/4.1
template <>
struct pair_get<0>
{
    template <typename T1, typename T2>
    static HAMON_CXX11_CONSTEXPR T1&
    get(pair<T1, T2>& p) HAMON_NOEXCEPT
	{
		return p.first;
	}

    template <typename T1, typename T2>
    static HAMON_CXX11_CONSTEXPR T1 const&
    get(pair<T1, T2> const& p) HAMON_NOEXCEPT
	{
		return p.first;
	}

    template <typename T1, typename T2>
    static HAMON_CXX11_CONSTEXPR T1&&
    get(pair<T1, T2>&& p) HAMON_NOEXCEPT
	{
		return hamon::forward<T1>(p.first);
	}

    template <typename T1, typename T2>
    static HAMON_CXX11_CONSTEXPR T1 const&&
    get(pair<T1, T2> const&& p) HAMON_NOEXCEPT
	{
		return hamon::forward<T1 const>(p.first);
	}
};

// [pair.astuple]/4.2
template <>
struct pair_get<1>
{
    template <typename T1, typename T2>
    static HAMON_CXX11_CONSTEXPR T2&
    get(pair<T1, T2>& p) HAMON_NOEXCEPT
	{
		return p.second;
	}

    template <typename T1, typename T2>
    static HAMON_CXX11_CONSTEXPR T2 const&
    get(pair<T1, T2> const& p) HAMON_NOEXCEPT
	{
		return p.second;
	}

    template <typename T1, typename T2>
    static HAMON_CXX11_CONSTEXPR T2&&
    get(pair<T1, T2>&& p) HAMON_NOEXCEPT
	{
		return hamon::forward<T2>(p.second);
	}

    template <typename T1, typename T2>
    static HAMON_CXX11_CONSTEXPR T2 const&&
    get(pair<T1, T2> const&& p) HAMON_NOEXCEPT
	{
		return hamon::forward<T2 const>(p.second);
	}
};

}	// namespace detail

template <hamon::size_t I, typename T1, typename T2>
inline HAMON_CXX11_CONSTEXPR hamon::tuple_element_t<I, pair<T1, T2>>&
get(pair<T1, T2>& p) HAMON_NOEXCEPT
{
	return detail::pair_get<I>::get(p);
}

template <hamon::size_t I, typename T1, typename T2>
inline HAMON_CXX11_CONSTEXPR hamon::tuple_element_t<I, pair<T1, T2>> const&
get(pair<T1, T2> const& p) HAMON_NOEXCEPT
{
	return detail::pair_get<I>::get(p);
}

template <hamon::size_t I, typename T1, typename T2>
inline HAMON_CXX11_CONSTEXPR hamon::tuple_element_t<I, pair<T1, T2>>&&
get(pair<T1, T2>&& p) HAMON_NOEXCEPT
{
	return detail::pair_get<I>::get(hamon::move(p));
}

template <hamon::size_t I, typename T1, typename T2>
inline HAMON_CXX11_CONSTEXPR hamon::tuple_element_t<I, pair<T1, T2>> const&&
get(pair<T1, T2> const&& p) HAMON_NOEXCEPT
{
	return detail::pair_get<I>::get(hamon::move(p));
}

// [pair.astuple]/6
template <typename T1, typename T2>
inline HAMON_CXX11_CONSTEXPR T1&
get(pair<T1, T2>& p) HAMON_NOEXCEPT
{
	return p.first;
}

template <typename T1, typename T2>
inline HAMON_CXX11_CONSTEXPR T1 const&
get(pair<T1, T2> const& p) HAMON_NOEXCEPT
{
	return p.first;
}

template <typename T1, typename T2>
inline HAMON_CXX11_CONSTEXPR T1&&
get(pair<T1, T2>&& p) HAMON_NOEXCEPT
{
	return hamon::move(p.first);
}

template <typename T1, typename T2>
inline HAMON_CXX11_CONSTEXPR T1 const&&
get(pair<T1, T2> const&& p) HAMON_NOEXCEPT
{
	return hamon::move(p.first);
}

// [pair.astuple]/8
template <typename T2, typename T1>
inline HAMON_CXX11_CONSTEXPR T2&
get(pair<T1, T2>& p) HAMON_NOEXCEPT
{
	return p.second;
}

template <typename T2, typename T1>
inline HAMON_CXX11_CONSTEXPR T2 const&
get(pair<T1, T2> const& p) HAMON_NOEXCEPT
{
	return p.second;
}

template <typename T2, typename T1>
inline HAMON_CXX11_CONSTEXPR T2&&
get(pair<T1, T2>&& p) HAMON_NOEXCEPT
{
	return hamon::move(p.second);
}

template <typename T2, typename T1>
inline HAMON_CXX11_CONSTEXPR T2 const&&
get(pair<T1, T2> const&& p) HAMON_NOEXCEPT
{
	return hamon::move(p.second);
}

}	// namespace hamon

#include <hamon/concepts/detail/is_specialization_of_pair.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon {
namespace detail {

// is_specialization_of_pair の特殊化
template <typename T1, typename T2>
struct is_specialization_of_pair<hamon::pair<T1, T2>>
	: public hamon::true_type {};

}	// namespace detail
}	// namespace hamon

#endif

#endif // HAMON_PAIR_PAIR_HPP
