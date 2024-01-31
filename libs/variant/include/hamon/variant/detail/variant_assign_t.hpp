/**
 *	@file	variant_assign_t.hpp
 *
 *	@brief	variant_assign_t の定義
 */

#ifndef HAMON_VARIANT_DETAIL_VARIANT_ASSIGN_T_HPP
#define HAMON_VARIANT_DETAIL_VARIANT_ASSIGN_T_HPP

#include <hamon/variant/detail/variant_move_ctor.hpp>
#include <hamon/variant/detail/access.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/type_traits/nth.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/in_place_index_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace variant_detail
{

template <typename Variant>
struct emplace_visitor
{
public:
	Variant*      m_lhs;
	hamon::size_t m_index;

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。
	template <typename T, typename... Args>
	HAMON_CXX14_CONSTEXPR T& operator()(T& v, Args&&... args) const
	{
		m_lhs->destroy();

#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
		if (hamon::is_constant_evaluated())
		{
			m_lhs->begin_lifetime();
		}
#endif
		auto res = ctor_visitor{}(v, hamon::forward<Args>(args)...);
		m_lhs->index(m_index);
		return *res;
	}
HAMON_WARNING_POP()
};

template <typename Variant>
struct assign_or_emplace_visitor
{
public:
	Variant*      m_lhs;
	hamon::size_t m_index;

private:
	template <typename T, typename U>
	HAMON_CXX14_CONSTEXPR void impl2(T& v1, U&& v2) const
	{
		emplace_visitor<Variant>{m_lhs, m_index}(v1, hamon::forward<U>(v2));
	}

	template <typename T, typename U,
		typename = hamon::enable_if_t<
			 hamon::is_nothrow_constructible<T, U>::value ||
			!hamon::is_nothrow_move_constructible<T>::value
		>
	>
	HAMON_CXX14_CONSTEXPR void impl(T& v1, U&& v2, hamon::detail::overload_priority<1>) const
	{
		impl2(v1, hamon::forward<U>(v2));
	}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。
	template <typename T, typename U>
	HAMON_CXX14_CONSTEXPR void impl(T& v1, U&& v2, hamon::detail::overload_priority<0>) const
	{
		impl2(v1, T(hamon::forward<U>(v2)));
	}
HAMON_WARNING_POP()

public:
	template <typename T, typename U>
	HAMON_CXX14_CONSTEXPR void operator()(T& v1, U&& v2) const
	{
		impl(v1, hamon::forward<U>(v2), hamon::detail::overload_priority<1>{});
	}
};

template <typename... Types>
struct variant_assign_t : variant_move_ctor<Types...>
{
	using this_type = variant_assign_t<Types...>;

	using variant_move_ctor<Types...>::variant_move_ctor;

	template <hamon::size_t I, typename... Args>
	HAMON_CXX14_CONSTEXPR hamon::nth_t<I, Types...>&
	emplace(hamon::in_place_index_t<I>, Args&&... args)
	{
		return emplace_visitor<this_type>{this, I}(
			variant_detail::access::get<I>(*this),
			hamon::forward<Args>(args)...);
	}

	template <hamon::size_t I, typename Arg>
	HAMON_CXX14_CONSTEXPR void
	assign(hamon::in_place_index_t<I>, Arg&& arg)
	{
		if (this->index() == I)
		{
			variant_detail::access::get<I>(*this) = hamon::forward<Arg>(arg);
		}
		else
		{
			return assign_or_emplace_visitor<this_type>{this, I}(
				variant_detail::access::get<I>(*this),
				hamon::forward<Arg>(arg));
		}
	}
};

}	// namespace variant_detail

}	// namespace hamon

#endif // HAMON_VARIANT_DETAIL_VARIANT_ASSIGN_T_HPP
