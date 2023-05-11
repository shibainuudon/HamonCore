/**
 *	@file	pair.hpp
 *
 *	@brief	pair の定義
 */

#ifndef HAMON_PAIR_PAIR_HPP
#define HAMON_PAIR_PAIR_HPP

#include <hamon/pair/config.hpp>
#include <hamon/pair/piecewise_construct.hpp>
#include <hamon/pair/pair_fwd.hpp>

#if defined(HAMON_USE_STD_PAIR)

#include <utility>

namespace hamon
{

using std::pair;

}	// namespace hamon

#else

#include <hamon/pair/detail/pair_constraint.hpp>
#include <hamon/compare/common_comparison_category.hpp>
#include <hamon/compare/detail/synth3way.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/tuple/tuple_fwd.hpp>
#include <hamon/tuple/concepts/pair_like.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_nothrow_copy_assignable.hpp>
#include <hamon/type_traits/is_swappable.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/index_sequence.hpp>
#include <hamon/utility/index_sequence_for.hpp>
#include <hamon/config.hpp>
#include <utility>	// std::swap

namespace hamon
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)
HAMON_WARNING_DISABLE_CLANG("-Wimplicit-int-conversion")
HAMON_WARNING_DISABLE_CLANG("-Wimplicit-float-conversion")
HAMON_WARNING_DISABLE_CLANG("-Wimplicit-int-float-conversion")
HAMON_WARNING_DISABLE_GCC("-Wconversion")
HAMON_WARNING_DISABLE_GCC("-Wfloat-conversion")

// Class template pair	[pairs.pair]
template <typename T1, typename T2>
struct pair
{
private:
	using constraint_type = pair_detail::pair_constraint<T1, T2>;

	template <typename Dummy>
	using DefaultCtor = typename constraint_type::template DefaultCtor<Dummy>;
	template <typename Dummy>
	using ElementCtor = typename constraint_type::template ElementCtor<Dummy>;
	template <typename U1, typename U2>
	using UTypesCtor = typename constraint_type::template UTypesCtor<U1, U2>;
	template <typename UPair>
	using UPairCtor = typename constraint_type::template UPairCtor<UPair>;
	template <typename UPair>
	using PairLikeCtor = typename constraint_type::template PairLikeCtor<UPair>;
	template <typename Dummy>
	using CopyAssignConst = typename constraint_type::template CopyAssignConst<Dummy>;
	template <typename Dummy>
	using MoveAssign = typename constraint_type::template MoveAssign<Dummy>;
	template <typename Dummy>
	using MoveAssignConst = typename constraint_type::template MoveAssignConst<Dummy>;
	template <typename U1, typename U2>
	using UPairCopyAssign = typename constraint_type::template UPairCopyAssign<U1, U2>;
	template <typename U1, typename U2>
	using UPairCopyAssignConst = typename constraint_type::template UPairCopyAssignConst<U1, U2>;
	template <typename U1, typename U2>
	using UPairMoveAssign = typename constraint_type::template UPairMoveAssign<U1, U2>;
	template <typename U1, typename U2>
	using UPairMoveAssignConst = typename constraint_type::template UPairMoveAssignConst<U1, U2>;
	template <typename UPair>
	using PairLikeAssign = typename constraint_type::template PairLikeAssign<UPair>;
	template <typename UPair>
	using PairLikeAssignConst = typename constraint_type::template PairLikeAssignConst<UPair>;
	template <typename Dummy>
	using Swap = typename constraint_type::template Swap<Dummy>;
	template <typename Dummy>
	using SwapConst = typename constraint_type::template SwapConst<Dummy>;

	struct nat;

	struct ctor_from_pair_tag{};

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
		typename Constraint = DefaultCtor<Dummy>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	pair()
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: first(), second()	{}				// [pairs.pair]/6

	// pair(T1 const& x, T2 const& y)
	template <typename Dummy = void,
		typename Constraint = ElementCtor<Dummy>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	pair(T1 const& x, T2 const& y)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: first(x), second(y) {}			// [pairs.pair]/9

	// pair(U1&& x, U2&& y)
	template <
		typename U1 = T1,
		typename U2 = T2,
		typename Constraint = UTypesCtor<U1, U2>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	pair(U1&& x, U2&& y)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: first (hamon::forward<U1>(x))		// [pairs.pair]/12
		, second(hamon::forward<U2>(y))
	{}

	// pair(pair<U1, U2>& p)
	template <typename U1, typename U2,
		typename Constraint = UPairCtor<pair<U1, U2>&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	pair(pair<U1, U2>& p)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: pair(ctor_from_pair_tag{}, p)
	{}

	// pair(pair<U1, U2> const& p)
	template <typename U1, typename U2,
		typename Constraint = UPairCtor<pair<U1, U2> const&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	pair(pair<U1, U2> const& p)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: pair(ctor_from_pair_tag{}, p)
	{}

	// pair(pair<U1, U2>&& p)
	template <typename U1, typename U2,
		typename Constraint = UPairCtor<pair<U1, U2>&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	pair(pair<U1, U2>&& p)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: pair(ctor_from_pair_tag{}, hamon::move(p))
	{}

	// pair(pair<U1, U2> const&& p)
	template <typename U1, typename U2,
		typename Constraint = UPairCtor<pair<U1, U2> const&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	pair(pair<U1, U2> const&& p)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: pair(ctor_from_pair_tag{}, hamon::move(p))
	{}

	// pair(PairLike&& p)
	template <HAMON_CONSTRAINED_PARAM(hamon::pair_like, P),
		typename Constraint = PairLikeCtor<P>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	pair(P&& p)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: pair(ctor_from_pair_tag{}, hamon::forward<P>(p))
	{}

#else

	// pair()
	template <typename Dummy = void,
		typename Constraint = DefaultCtor<Dummy>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	pair()
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: first(), second() {}		// [pairs.pair]/6

	template <typename Dummy = void,
		typename Constraint = DefaultCtor<Dummy>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	pair()
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: first(), second() {}		// [pairs.pair]/6

	// pair(T1 const& x, T2 const& y)
	template <typename Dummy = void,
		typename Constraint = ElementCtor<Dummy>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	pair(T1 const& x, T2 const& y)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: first(x), second(y) {}	// [pairs.pair]/9

	template <typename Dummy = void,
		typename Constraint = ElementCtor<Dummy>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	pair(T1 const& x, T2 const& y)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: first(x), second(y) {}	// [pairs.pair]/9

	// pair(U1&& x, U2&& y)
	template <
		typename U1 = T1,
		typename U2 = T2,
		typename Constraint = UTypesCtor<U1, U2>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	pair(U1&& x, U2&& y)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: first (hamon::forward<U1>(x))		// [pairs.pair]/12
		, second(hamon::forward<U2>(y))
	{}

	template <
		typename U1 = T1,
		typename U2 = T2,
		typename Constraint = UTypesCtor<U1, U2>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	pair(U1&& x, U2&& y)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: first (hamon::forward<U1>(x))		// [pairs.pair]/12
		, second(hamon::forward<U2>(y))
	{}

	// pair(pair<U1, U2>& p)
	template <typename U1, typename U2,
		typename Constraint = UPairCtor<pair<U1, U2>&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	pair(pair<U1, U2>& p)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: pair(ctor_from_pair_tag{}, p)
	{}

	template <typename U1, typename U2,
		typename Constraint = UPairCtor<pair<U1, U2>&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	pair(pair<U1, U2>& p)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: pair(ctor_from_pair_tag{}, p)
	{}

	// pair(pair<U1, U2> const& p)
	template <typename U1, typename U2,
		typename Constraint = UPairCtor<pair<U1, U2> const&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	pair(pair<U1, U2> const& p)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: pair(ctor_from_pair_tag{}, p)
	{}

	template <typename U1, typename U2,
		typename Constraint = UPairCtor<pair<U1, U2> const&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	pair(pair<U1, U2> const& p)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: pair(ctor_from_pair_tag{}, p)
	{}

	// pair(pair<U1, U2>&& p)
	template <typename U1, typename U2,
		typename Constraint = UPairCtor<pair<U1, U2>&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	pair(pair<U1, U2>&& p)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: pair(ctor_from_pair_tag{}, hamon::move(p))
	{}

	template <typename U1, typename U2,
		typename Constraint = UPairCtor<pair<U1, U2>&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	pair(pair<U1, U2>&& p)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: pair(ctor_from_pair_tag{}, hamon::move(p))
	{}

	// pair(pair<U1, U2> const&& p)
	template <typename U1, typename U2,
		typename Constraint = UPairCtor<pair<U1, U2> const&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	pair(pair<U1, U2> const&& p)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: pair(ctor_from_pair_tag{}, hamon::move(p))
	{}

	template <typename U1, typename U2,
		typename Constraint = UPairCtor<pair<U1, U2> const&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	pair(pair<U1, U2> const&& p)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: pair(ctor_from_pair_tag{}, hamon::move(p))
	{}

	// pair(PairLike&& p)
	template <HAMON_CONSTRAINED_PARAM(hamon::pair_like, P),
		typename Constraint = PairLikeCtor<P>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	pair(P&& p)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: pair(ctor_from_pair_tag{}, hamon::forward<P>(p))
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::pair_like, P),
		typename Constraint = PairLikeCtor<P>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	pair(P&& p)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: pair(ctor_from_pair_tag{}, hamon::forward<P>(p))
	{}
#endif

	// pair(piecewise_construct_t, hamon::tuple<Args1...> first_args, hamon::tuple<Args2...> second_args)
	template <typename... Args1, typename... Args2>
	HAMON_CXX11_CONSTEXPR
	pair(hamon::piecewise_construct_t, hamon::tuple<Args1...> first_args, hamon::tuple<Args2...> second_args)
		: pair(first_args, second_args,
			hamon::index_sequence_for<Args1...>{},
			hamon::index_sequence_for<Args2...>{})
	{}

private:
	// [pairs.pair]/16
	template <typename Pair>
	HAMON_CXX11_CONSTEXPR
	pair(ctor_from_pair_tag, Pair&& p)
		: first (hamon::adl_get<0>(hamon::forward<Pair>(p)))
		, second(hamon::adl_get<1>(hamon::forward<Pair>(p)))
	{}

	// [pairs.pair]/19
	template <typename... Args1, typename... Args2, hamon::size_t... I, hamon::size_t... J>
	HAMON_CXX11_CONSTEXPR pair(
		hamon::tuple<Args1...>& t1,
		hamon::tuple<Args2...>& t2,
		hamon::index_sequence<I...>,
		hamon::index_sequence<J...>)
		: first (hamon::forward<Args1>(hamon::adl_get<I>(t1))...)
		, second(hamon::forward<Args2>(hamon::adl_get<J>(t2))...)
	{}

public:
	// operator=(pair const&)
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

	// operator=(pair const&) const
	template <typename Dummy = void,
		typename Constraint = CopyAssignConst<Dummy>,
		hamon::enable_if_t<Constraint::assignable>* = nullptr>
	HAMON_CXX14_CONSTEXPR pair const&
	operator=(pair const& p) const
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
	{
		// [pairs.pair]/24
		first  = p.first;
		second = p.second;
		// [pairs.pair]/25
		return *this;
	}

	// operator=(pair<U1, U2> const&)
	template <typename U1, typename U2,
		typename Constraint = UPairCopyAssign<U1, U2>,
		hamon::enable_if_t<Constraint::assignable>* = nullptr>
	HAMON_CXX14_CONSTEXPR pair&
	operator=(pair<U1, U2> const& p)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
	{
		// [pairs.pair]/27
		first  = p.first;
		second = p.second;
		// [pairs.pair]/28
		return *this;
	}

	// operator=(pair<U1, U2> const&) const
	template <typename U1, typename U2,
		typename Constraint = UPairCopyAssignConst<U1, U2>,
		hamon::enable_if_t<Constraint::assignable>* = nullptr>
	HAMON_CXX14_CONSTEXPR pair const&
	operator=(pair<U1, U2> const& p) const
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
	{
		// [pairs.pair]/30
		first  = p.first;
		second = p.second;
		// [pairs.pair]/31
		return *this;
	}

	// operator=(pair&&)
	template <typename Dummy = void,
		typename Constraint = MoveAssign<Dummy>,
		hamon::enable_if_t<Constraint::assignable>* = nullptr>
	HAMON_CXX14_CONSTEXPR pair&
	operator=(pair&& p)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
	{
		// [pairs.pair]/33
		first  = hamon::forward<T1>(p.first);
		second = hamon::forward<T2>(p.second);
		// [pairs.pair]/34
		return *this;
	}

	// operator=(pair&&) const
	template <typename Dummy = void,
		typename Constraint = MoveAssignConst<Dummy>,
		hamon::enable_if_t<Constraint::assignable>* = nullptr>
	HAMON_CXX14_CONSTEXPR pair const&
	operator=(pair&& p) const
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
	{
		// [pairs.pair]/37
		first  = hamon::forward<T1>(p.first);
		second = hamon::forward<T2>(p.second);
		// [pairs.pair]/38
		return *this;
	}

	// operator=(pair<U1, U2>&&)
	template <typename U1, typename U2,
		typename Constraint = UPairMoveAssign<U1, U2>,
		hamon::enable_if_t<Constraint::assignable>* = nullptr>
	HAMON_CXX14_CONSTEXPR pair&
	operator=(pair<U1, U2>&& p)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
	{
		// [pairs.pair]/40
		first  = hamon::forward<U1>(p.first);
		second = hamon::forward<U2>(p.second);
		// [pairs.pair]/41
		return *this;
	}

	// operator=(pair<U1, U2>&&) const
	template <typename U1, typename U2,
		typename Constraint = UPairMoveAssignConst<U1, U2>,
		hamon::enable_if_t<Constraint::assignable>* = nullptr>
	HAMON_CXX14_CONSTEXPR pair const&
	operator=(pair<U1, U2>&& p) const
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
	{
		// [pairs.pair]/49
		first  = hamon::forward<U1>(p.first);
		second = hamon::forward<U2>(p.second);
		// [pairs.pair]/50
		return *this;
	}

	// operator=(P&&)
	template <HAMON_CONSTRAINED_PARAM(hamon::pair_like, P),
		typename Constraint = PairLikeAssign<P>,
		hamon::enable_if_t<Constraint::assignable>* = nullptr>
	HAMON_CXX14_CONSTEXPR pair&
	operator=(P&& p)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
	{
		// [pairs.pair]/43
		first  = hamon::adl_get<0>(hamon::forward<P>(p));
		second = hamon::adl_get<1>(hamon::forward<P>(p));
		// [pairs.pair]/44
		return *this;
	}

	// operator=(P&&) const
	template <HAMON_CONSTRAINED_PARAM(hamon::pair_like, P),
		typename Constraint = PairLikeAssignConst<P>,
		hamon::enable_if_t<Constraint::assignable>* = nullptr>
	HAMON_CXX14_CONSTEXPR pair const&
	operator=(P&& p) const
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
	{
		// [pairs.pair]/46
		first  = hamon::adl_get<0>(hamon::forward<P>(p));
		second = hamon::adl_get<1>(hamon::forward<P>(p));
		// [pairs.pair]/47
		return *this;
	}

	// swap(pair&)
	template <typename Dummy = void,
		typename Constraint = Swap<Dummy>,
		hamon::enable_if_t<Constraint::swappable>* = nullptr>
	HAMON_CXX14_CONSTEXPR void
	swap(pair& p)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
	{
		// [pairs.pair]/53
		using std::swap;
		swap(first,  p.first);
		swap(second, p.second);
	}

	// swap(pair const&) const
	template <typename Dummy = void,
		typename Constraint = SwapConst<Dummy>,
		hamon::enable_if_t<Constraint::swappable>* = nullptr>
	HAMON_CXX14_CONSTEXPR void
	swap(pair const& p) const
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
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

#include <hamon/pair/detail/pair_get.hpp>
#include <hamon/tuple/tuple_element.hpp>

namespace hamon
{

template <hamon::size_t I, typename T1, typename T2>
inline HAMON_CXX11_CONSTEXPR hamon::tuple_element_t<I, pair<T1, T2>>&
get(pair<T1, T2>& p) HAMON_NOEXCEPT
{
	return pair_detail::pair_get<I>::get(p);
}

template <hamon::size_t I, typename T1, typename T2>
inline HAMON_CXX11_CONSTEXPR hamon::tuple_element_t<I, pair<T1, T2>> const&
get(pair<T1, T2> const& p) HAMON_NOEXCEPT
{
	return pair_detail::pair_get<I>::get(p);
}

template <hamon::size_t I, typename T1, typename T2>
inline HAMON_CXX11_CONSTEXPR hamon::tuple_element_t<I, pair<T1, T2>>&&
get(pair<T1, T2>&& p) HAMON_NOEXCEPT
{
	return pair_detail::pair_get<I>::get(hamon::move(p));
}

template <hamon::size_t I, typename T1, typename T2>
inline HAMON_CXX11_CONSTEXPR hamon::tuple_element_t<I, pair<T1, T2>> const&&
get(pair<T1, T2> const&& p) HAMON_NOEXCEPT
{
	return pair_detail::pair_get<I>::get(hamon::move(p));
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

// basic_common_reference の特殊化
#include <hamon/pair/detail/basic_common_reference.hpp>

// common_type の特殊化
#include <hamon/pair/detail/common_type.hpp>

#endif

#endif // HAMON_PAIR_PAIR_HPP
