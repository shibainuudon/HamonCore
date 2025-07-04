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
#include <hamon/tuple/tuple_size.hpp>
#include <hamon/tuple/detail/tuple_impl.hpp>
#include <hamon/tuple/detail/tuple_constraint.hpp>
#include <hamon/tuple/concepts/tuple_like.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/memory/allocator_arg_t.hpp>
#include <hamon/pair/pair.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <hamon/type_traits/is_nothrow_assignable.hpp>
#include <hamon/type_traits/is_nothrow_copy_assignable.hpp>
#include <hamon/type_traits/is_nothrow_move_assignable.hpp>
#include <hamon/type_traits/is_nothrow_swappable.hpp>
#include <hamon/type_traits/nth.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace tuple_detail
{

struct access;

}	// namespace tuple_detail

// Class template tuple	[tuple.tuple]
template <typename... Types>
class tuple
{
private:
	using impl_type = tuple_detail::tuple_impl_t<Types...>;
	using constraint_type = tuple_detail::tuple_constraint_t<Types...>;

	impl_type	m_impl;

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

	friend struct tuple_detail::access;

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
		hamon::enable_if_t<UTypesCtor<UTypes...>::constructible>* = nullptr,
		hamon::enable_if_t<!UTypesCtor<UTypes...>::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!UTypesCtor<UTypes...>::implicitly)
	tuple(UTypes&&... args)
	HAMON_NOEXCEPT_IF((UTypesCtor<UTypes...>::nothrow))
		: m_impl(tuple_detail::ctor_from_elems_tag{}, hamon::forward<UTypes>(args)...)
	{}

	template <typename... UTypes,
		hamon::enable_if_t<UTypesCtor<UTypes...>::constructible>* = nullptr,
		hamon::enable_if_t<UTypesCtor<UTypes...>::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!UTypesCtor<UTypes...>::implicitly)
	tuple(UTypes&&...) = delete;

	// tuple(tuple<UTypes...>& u)
	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...>&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(tuple<UTypes...>& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, u)
	{}
	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...>&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(tuple<UTypes...>&) = delete;

	// tuple(tuple<UTypes...> const& u)
	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...> const&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(tuple<UTypes...> const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...> const&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(tuple<UTypes...> const&) = delete;

	// tuple(tuple<UTypes...>&& u)
	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...>&&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(tuple<UTypes...>&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...>&&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(tuple<UTypes...>&&) = delete;

	// tuple(tuple<UTypes...> const&& u)
	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...> const&&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(tuple<UTypes...> const&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...> const&&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(tuple<UTypes...> const&&) = delete;

	// tuple(pair<U1, U2>& u)
	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2>&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(pair<U1, U2>& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2>&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(pair<U1, U2>&) = delete;

	// tuple(pair<U1, U2> const& u)
	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2> const&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(pair<U1, U2> const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2> const&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(pair<U1, U2> const&) = delete;

	// tuple(pair<U1, U2>&& u)
	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2>&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(pair<U1, U2>&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2>&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(pair<U1, U2>&&) = delete;

	// tuple(pair<U1, U2> const&& u)
	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2> const&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(pair<U1, U2> const&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2> const&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	tuple(pair<U1, U2> const&&) = delete;

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
		hamon::enable_if_t<!UTypesCtor<UTypes...>::dangles>* = nullptr,
		hamon::enable_if_t<!UTypesCtor<UTypes...>::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(UTypes&&... args)
	HAMON_NOEXCEPT_IF((UTypesCtor<UTypes...>::nothrow))
		: m_impl(tuple_detail::ctor_from_elems_tag{}, hamon::forward<UTypes>(args)...)
	{}

	template <typename... UTypes,
		hamon::enable_if_t<UTypesCtor<UTypes...>::constructible>* = nullptr,
		hamon::enable_if_t<!UTypesCtor<UTypes...>::dangles>* = nullptr,
		hamon::enable_if_t<UTypesCtor<UTypes...>::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(UTypes&&... args)
	HAMON_NOEXCEPT_IF((UTypesCtor<UTypes...>::nothrow))
		: m_impl(tuple_detail::ctor_from_elems_tag{}, hamon::forward<UTypes>(args)...)
	{}

	template <typename... UTypes,
		hamon::enable_if_t<UTypesCtor<UTypes...>::constructible>* = nullptr,
		hamon::enable_if_t<UTypesCtor<UTypes...>::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(UTypes&&...) = delete;

	// tuple(tuple<UTypes...>& u)
	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...>&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::dangles>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...>& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...>&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::dangles>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...>& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...>&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...>&) = delete;

	// tuple(tuple<UTypes...> const& u)
	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...> const&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::dangles>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...> const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...> const&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::dangles>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...> const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...> const&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...> const&) = delete;

	// tuple(tuple<UTypes...>&& u)
	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...>&&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::dangles>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...>&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...>&&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::dangles>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...>&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...>&&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...>&&) = delete;

	// tuple(tuple<UTypes...> const&& u)
	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...> const&&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::dangles>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...> const&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...> const&&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::dangles>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...> const&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	template <typename... UTypes,
		typename Constraint = UTupleCtor<tuple<UTypes...> const&&, UTypes...>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(tuple<UTypes...> const&&) = delete;

	// tuple(pair<U1, U2>& u)
	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2>&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::dangles>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2>& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2>&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::dangles>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2>& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2>&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2>&) = delete;

	// tuple(pair<U1, U2> const& u)
	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2> const&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::dangles>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2> const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2> const&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::dangles>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2> const& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, u)
	{}

	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2> const&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2> const&) = delete;

	// tuple(pair<U1, U2>&& u)
	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2>&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::dangles>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2>&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2>&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::dangles>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2>&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2>&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2>&&) = delete;

	// tuple(pair<U1, U2> const&& u)
	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2> const&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::dangles>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2> const&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2> const&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::dangles>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2> const&& u)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: m_impl(tuple_detail::ctor_from_tuple_tag{}, hamon::move(u))
	{}

	template <typename U1, typename U2,
		typename Constraint = PairCtor<pair<U1, U2> const&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::dangles>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	tuple(pair<U1, U2> const&&) = delete;

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
			hamon::tuple_size<hamon::remove_cvref_t<UTuple>>::value == 0>>
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

#include <hamon/tuple/tuple_element.hpp>
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

#include <hamon/tuple/detail/tuple_compare.hpp>

namespace hamon
{

// Relational operators	[tuple.rel]
template <typename... TTypes, typename... UTypes>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR bool
operator==(tuple<TTypes...> const& t, tuple<UTypes...> const& u)
{
	return tuple_detail::tuple_eq(t, u);
}

template <typename... TTypes, HAMON_CONSTRAINED_PARAM(hamon::tuple_like, UTuple)>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR bool
operator==(tuple<TTypes...> const& t, UTuple const& u)
{
	return tuple_detail::tuple_eq(t, u);
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename... TTypes, typename... UTypes>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR auto
operator<=>(tuple<TTypes...> const& t, tuple<UTypes...> const& u)
->decltype(tuple_detail::tuple_3way(t, u))
{
	return tuple_detail::tuple_3way(t, u);
}

template <typename... TTypes, HAMON_CONSTRAINED_PARAM(hamon::tuple_like, UTuple)>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR auto
operator<=>(tuple<TTypes...> const& t, UTuple const& u)
->decltype(tuple_detail::tuple_3way(t, u))
{
	return tuple_detail::tuple_3way(t, u);
}

#else

template <typename... TTypes, typename... UTypes>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR bool
operator<(tuple<TTypes...> const& t, tuple<UTypes...> const& u)
{
	return tuple_detail::tuple_less(t, u);
}

template <typename... TTypes, typename... UTypes>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR bool
operator!=(tuple<TTypes...> const& t, tuple<UTypes...> const& u)
{
	return !(t == u);
}

template <typename... TTypes, typename... UTypes>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR bool
operator>(tuple<TTypes...> const& t, tuple<UTypes...> const& u)
{
	return u < t;
}

template <typename... TTypes, typename... UTypes>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR bool
operator<=(tuple<TTypes...> const& t, tuple<UTypes...> const& u)
{
	return !(u < t);
}

template <typename... TTypes, typename... UTypes>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR bool
operator>=(tuple<TTypes...> const& t, tuple<UTypes...> const& u)
{
	return !(t < u);
}

template <typename... TTypes, HAMON_CONSTRAINED_PARAM(hamon::tuple_like, UTuple)>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR bool
operator<(tuple<TTypes...> const& t, UTuple const& u)
{
	return tuple_detail::tuple_less(t, u);
}

template <typename... TTypes, HAMON_CONSTRAINED_PARAM(hamon::tuple_like, UTuple)>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR bool
operator!=(tuple<TTypes...> const& t, UTuple const& u)
{
	return !(t == u);
}

template <typename... TTypes, HAMON_CONSTRAINED_PARAM(hamon::tuple_like, UTuple)>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR bool
operator>(tuple<TTypes...> const& t, UTuple const& u)
{
	return tuple_detail::tuple_less(u, t);
}

template <typename... TTypes, HAMON_CONSTRAINED_PARAM(hamon::tuple_like, UTuple)>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR bool
operator<=(tuple<TTypes...> const& t, UTuple const& u)
{
	return !(t > u);
}

template <typename... TTypes, HAMON_CONSTRAINED_PARAM(hamon::tuple_like, UTuple)>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR bool
operator>=(tuple<TTypes...> const& t, UTuple const& u)
{
	return !(t < u);
}

#endif

}	// namespace hamon

#include <hamon/type_traits/is_swappable.hpp>

namespace hamon
{

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
